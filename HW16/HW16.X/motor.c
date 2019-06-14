#include "motor.h"

unsigned short speed = 0;   // 0 is fastest, 2399 is slowest

void motor_init(){
    // OC1 is B15, goes with DIR1 (left)
    RPB15R = 0b0101;         // set RB15 to be OC1
    TRISAbits.TRISA10 = 0;   // DIR1
    DIR1 = 1;
    // OC4 is A4, goes with DIR2 (right)
    RPA4R = 0b0101;         // set RA4 to be OC4
    TRISAbits.TRISA7 = 0;   // DIR2
    DIR2 = 1;
    
    // Set Timer2 for PWM
    T2CONbits.TCKPS = 0;    // Timer2 prescaler N=1 (1:1)
    PR2 = 2399;             // PR = 48MHz/20kHz/1 - 1
    TMR2 = 0;               // initial TMR2 count is 0
    OC1CONbits.OCM = 0b110; // PWM mode without fault pin; other OC1CON bits are defaults
    OC1RS = PR2;              // duty cycle
    OC1R = PR2;               // initialize before turning OC1 on; afterward it is read-only
    OC4CONbits.OCM = 0b110; // PWM mode without fault pin; other OC1CON bits are defaults
    OC4RS = PR2;              // duty cycle
    OC4R = PR2;               // initialize before turning OC1 on; afterward it is read-only
    T2CONbits.ON = 1;       // turn on Timer2
    OC1CONbits.ON = 1;      // turn on OC1
    OC4CONbits.ON = 1;      // turn on OC4
}

void set_speed(unsigned char x){
    // takes in a percentage between 0 and 100
    if (x > 100){
        x = 100;
    }
    x = 100 - x;    // inverts the percentage
    speed = (PR2*x)/100;
}

void turn(short direction){
    // takes in a value between -100 to 100
    if (direction < -100){
        direction = -100;
    }
    if (direction > 100){
        direction = 100;
    }
    
    if (direction < 0){     // turn left
        OC1RS = (-1 * direction) * (PR2 - speed) / 100 + speed;
        OC4RS = speed;
    }
    else if (direction > 0){     // turn right
        OC1RS = speed;
        OC4RS = direction * (PR2 - speed) / 100 + speed;
    }
    else {      // go straight
        OC1RS = speed; 
        OC4RS = speed;
    }
}