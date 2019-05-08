#include <xc.h>                     // processor SFR definitions
#include <sys/attribs.h>            // __ISR macro
#include"i2c.h"                     // i2c functions

// I2C Master utilities, 400 kHz, using polling rather than interrupts
// The functions must be called in the correct order as per the I2C protocol
// I2C pins need pull-up resistors, 2k-10k

void i2c_init(void){
    // SCL1(RB8), SDA1(RB9)
    I2C1BRG = 0x035;        // I2CBRG = [1/(2*Fsck) - PGD]*Pblck - 2 
                            // PGD = 104ns, Fsck = 400kHz, I2C1BRG = 0x035 
    I2C1CONbits.DISSLW = 1;
    I2C1CONbits.ON = 1;     // turn on the I2C1 module
    
    // Configure accelerometers
    i2c_master_start();             // send start bit
    i2c_master_send(ADDR << 1);     // bit 0 = 0 for write
    i2c_master_send(0x10);          // CTRL1_XL register address
    i2c_master_send(0b10000010);    // set ODR = 1000, FS = 00, BW = 10
    i2c_master_stop();              // send stop bit
    
    // Configure gyroscopes
    i2c_master_start();             // send start bit
    i2c_master_send(ADDR << 1);     // bit 0 = 0 for write
    i2c_master_send(0x11);          // CTRL2_G register address
    i2c_master_send(0b10001000);    // set ODR = 1000, FS_G = 10, FS_125 = 0 
    i2c_master_stop();              // send stop bit
    
    // Configure sequential R/W
    i2c_master_start();             // send start bit
    i2c_master_send(ADDR << 1);     // bit 0 = 0 for write
    i2c_master_send(0x12);          // CTRL3_C register address
    i2c_master_send(0b00000100);    // set IF-INC = 1 
    i2c_master_stop();              // send stop bit
}

// Start a transmission on the I2C bus
void i2c_master_start(void) {
    I2C1CONbits.SEN = 1;            // send the start bit
    while(I2C1CONbits.SEN) { ; }    // wait for the start bit to be sent
}

void i2c_master_restart(void) {     
    I2C1CONbits.RSEN = 1;           // send a restart 
    while(I2C1CONbits.RSEN) { ; }   // wait for the restart to clear
}

void i2c_master_send(unsigned char byte) { // send a byte to slave
    I2C1TRN = byte;                   // if an address, bit 0 = 0 for write, 1 for read
    while(I2C1STATbits.TRSTAT) { ; }  // wait for the transmission to finish
    while(I2C1STATbits.ACKSTAT) {        // if this is high, slave has not acknowledged
        // ("I2C1 Master: failed to receive ACK\r\n");
    }
}

unsigned char i2c_master_recv(void) { // receive a byte from the slave
    I2C1CONbits.RCEN = 1;             // start receiving data
    while(!I2C1STATbits.RBF) { ; }    // wait to receive the data
    return I2C1RCV;                   // read and return the data
}

void i2c_master_ack(int val) {        // sends ACK = 0 (slave should send another byte)
                                      // or NACK = 1 (no more bytes requested from slave)
    I2C1CONbits.ACKDT = val;          // store ACK/NACK in ACKDT
    I2C1CONbits.ACKEN = 1;            // send ACKDT
    while(I2C1CONbits.ACKEN) { ; }    // wait for ACK/NACK to be sent
}

void i2c_master_stop(void) {          // send a STOP:
  I2C1CONbits.PEN = 1;                // comm is complete and master relinquishes bus
  while(I2C1CONbits.PEN) { ; }        // wait for STOP to complete
}

void I2C_read_multiple(unsigned char address, unsigned char register_address, unsigned char *data, int length){
    int i=0;
    i2c_master_start();                     // send start bit
    i2c_master_send(address << 1);          // bit 0 = 0 for write
    i2c_master_send(register_address);      // register address 
    i2c_master_restart();                   // restart
    i2c_master_send((address << 1) | 1);    // bit 0 = 1 for write
    data[i] = i2c_master_recv();            // save the value returned
    for(i=1; i<length; i++){
        i2c_master_ack(0);                      // send ack bit
        data[i] = i2c_master_recv();            // save the value returned
    }
    i2c_master_ack(1);                      // send nack bit
    i2c_master_stop();                      // send stop bit
}