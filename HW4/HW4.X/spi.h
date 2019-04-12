#ifndef _SPI_H    /* Guard against multiple inclusion */
#define _SPI_H

#include <xc.h>                     // processor SFR definitions
#include <sys/attribs.h>            // __ISR macro

#define CS LATAbits.LATA0       // chip select pin

void spi_init();
unsigned char spi_io(unsigned char o);

#endif
