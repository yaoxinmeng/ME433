#ifndef _STARTUP_H    /* Guard against multiple inclusion */
#define _STARTUP_H

#include <xc.h>                     // processor SFR definitions
#include <sys/attribs.h>            // __ISR macro

#define USER PORTBbits.RB4

void init();

#endif