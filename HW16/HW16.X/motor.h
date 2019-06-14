#ifndef _MOTOR_H    /* Guard against multiple inclusion */
#define _MOTOR_H

#include <xc.h>                     // processor SFR definitions

#define DIR1 LATAbits.LATA10    // LEFT
#define DIR2 LATAbits.LATA7     // RIGHT

void motor_init();
void set_speed(unsigned char x);
void turn(short direction);

#endif