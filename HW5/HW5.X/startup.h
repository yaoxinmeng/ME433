#ifndef _STARTUP_H    /* Guard against multiple inclusion */
#define _STARTUP_H

#include <xc.h>                     // processor SFR definitions
#include <sys/attribs.h>            // __ISR macro

#define LED LATBbits.LATB7  // LED

void init();

#endif
