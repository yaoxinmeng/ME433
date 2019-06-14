#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include <stdio.h>
#include "startup.h"   
#include "lcd.h"
#include "motor.h"
#include "camera.h"
#include "i2c.h"

#define BACKGROUND ILI9341_ORANGE
#define TEXT ILI9341_DARKGREY
#define _TIMER4_VECTOR 16
#define TRACK_THICKNESS 20  // half of the thickness of the track in pixels
#define TRACKLINE 10        // threshold dimness of track
#define GAIN 1.0            // gain from deviation to turn magnitude
    
// 10Hz ISR
void __ISR(_TIMER4_VECTOR, IPL5SOFT) Timer4ISR(void) {
    static int I = 0;
    char message[100];
    unsigned char d[2000];
    
    // read camera data
    I++;
    sprintf(message,"I = %d   ", I);
    LCD_print(message,140,82,TEXT,BACKGROUND);

    // horizontal read
    /*
    int c = ov7670_count_horz(d);
    sprintf(message, "c = %d   ",c);
    drawString(140,92,message); // there are 290 rows

    int x = 0, x2 = 1;
    int y = 0;
    int dim = 0;
    for(x = 0; x < c/2; x++, x2=x2+2){
        dim = d[x2]>>3;
        for(y=0;y<32;y++){
            if (y == dim){
                LCD_drawPixel(y+30,x,ILI9341_BLACK);
            }
            else {
                LCD_drawPixel(y+30,x,ILI9341_WHITE);
            }
        }
    }
    */

    // vertical read
    int c = ov7670_count_vert(d);
    sprintf(message, "c = %d   ",c);
    LCD_print(message,140,92,TEXT,BACKGROUND); // there are 290 rows

    int x = 0, x2 = 0;
    int y = 0;
    int dim = 0;
    for(x = 0; x < c/2; x++, x2=x2+2){
        dim = d[x2]>>3;
        for(y=0;y<32;y++){
            if (y == dim){
                LCD_drawPixel(x,y+30,ILI9341_BLACK);
            }
            else {
                LCD_drawPixel(x,y+30,ILI9341_WHITE);
            }
        }
    }

    // at this point, every other index of d[] is a brightness
    // loop through d[] and calculate where the middle of the dip or bump is
    // then set the motor speed and direction to follow the line
    // change motor settings
    int x_mid = c/4;    // middle of track
    x2 = 0;
    for(x = 0; x < c/2; x++, x2=x2+2){
        dim = d[x2]>>3;
        if (dim <= TRACKLINE){
            if (x < (x_mid-TRACK_THICKNESS)){   // compare with left bound of track
                set_speed(40);  // slow down
                // turn left
                short turn_mag = GAIN * (x - x_mid + TRACK_THICKNESS);
                turn(turn_mag);
            }
            else if (x > (x_mid+TRACK_THICKNESS)){  // compare with right bound of track
                set_speed(40);  // slow down
                // turn right
                short turn_mag = GAIN * (x - x_mid - TRACK_THICKNESS);
                turn(turn_mag);
            }
            else{
                set_speed(80);  // speed up
            }
        }
    }
    
    IFS0bits.T4IF = 0;  // clear interrupt flag
}

int main() {
    // initialise pins
    init();
    motor_init();
    camera_init();
    i2c_init();
    //ov7670_setup();
    SPI1_init();
    LCD_init();
    LCD_clearScreen(BACKGROUND);
    
    // Set Timer4 for interrupt
    __builtin_disable_interrupts();     // disable interrupts
    T4CONbits.TCKPS = 7;    // Timer3 prescaler N=0b111 (1:256)
    PR4 = 18749;            // PR = 48MHz/10Hz/256 - 1
    TMR4 = 0;               // initial TMR3 count is 0
    T4CONbits.ON = 1;       // turn on Timer3
    IPC4bits.T4IP = 5;      // interrupt priority is 5
    IPC4bits.T4IS = 0;      // subpriority is 0, which is the default
    IFS0bits.T4IF = 0;      // clear CT interrupt flag
    IEC0bits.T4IE = 1;      // enable core timer interrupt
    __builtin_enable_interrupts();    // CPU interrupts enabled
    
    set_speed(20);
       
    while(1) {;}
}

