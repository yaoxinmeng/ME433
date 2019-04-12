#include"spi.h"     

// initialize spi1 and the ram module
void spi_init() {
    // set up the chip select pin as an output
    // the chip select pin is used by the sram to indicate
    // when a command is beginning (clear CS to low) and when it
    // is ending (set CS high)
    TRISAbits.TRISA0 = 0;
    CS = 1;
    
    // Master - SPI41, pins are: SDI1(RA1), SDO1(RB8), SCK1(RB14), SS1(RB15)  
    // since the pic is just starting, we know that spi is off. We rely on defaults here
 
    // setup SPI1
    SPI1CON = 0;                // turn off the spi module and reset it
    SPI1BUF;                    // clear the rx buffer by reading from it
    SPI1BRG = 0x2;              // baud rate to 8 MHz [SPI1BRG = (48000000/(2*desired))-1]
    SPI1STATbits.SPIROV = 0;    // clear the overflow bit
    SPI1CONbits.CKE = 1;        // data changes when clock goes from hi to lo (since CKP is 0)
    SPI1CONbits.MODE32 = 0;
    SPI1CONbits.MODE16 = 1;     // 16 bits mode
    SPI1CONbits.MSTEN = 1;      // master operation
    SPI1CONbits.ON = 1;         // turn on spi 1
    SDI1Rbits.SDI1R = 0b0000;   // assign SDI1 to RPA1 (not used)
    RPB15Rbits.RPB15R = 0b0011; // assign SS1 to RPB15 (not used)
    RPB8Rbits.RPB8R = 0b0011;   // assign SDO1 to RPB8  
}

// send a byte via spi and return the response
unsigned char spi_io(unsigned char o) {
  SPI1BUF = o;
  while(!SPI1STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  return SPI1BUF;
}


