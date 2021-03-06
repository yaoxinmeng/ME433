#ifndef _I2C_H    /* Guard against multiple inclusion */
#define _I2C_H
  
#define ADDR 0b1101011              // hardware address of MCP23008

void i2c_init(void);                // set up I2C2 as a master, at 400 kHz           

void i2c_master_start(void);              // send a START signal
void i2c_master_restart(void);            // send a RESTART signal
void i2c_master_send(unsigned char byte); // send a byte (either an address or data)
unsigned char i2c_master_recv(void);      // receive a byte of data
void i2c_master_ack(int val);             // send an ACK (0) or NACK (1)
void i2c_master_stop(void);               // send a stop
void I2C_read_multiple(unsigned char address, unsigned char register_address, unsigned char *data, int length);    // read multiple data

#endif
