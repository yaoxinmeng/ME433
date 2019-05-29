#include"startup.h"     // general initialisation code
#include"lcd.h"         // lcd helper file
#include <time.h>

#define BACKGROUND ILI9341_ORANGE
#define PLOT_LINE ILI9341_WHITE
#define RED_BACKGROUND ILI9341_MAROON
#define GREEN_BACKGROUND ILI9341_DARKGREEN
#define BLUE_BACKGROUND ILI9341_BLUE
#define DIRECTION LATBbits.LATB13
#define _TIMER3_VECTOR 12

int counter = 0;

void __ISR(_TIMER3_VECTOR, IPL5SOFT) Timer3ISR(void) {
    IFS0bits.T3IF = 0;  // clear interrupt flag
    counter++;          // counts number of times interrupt is called
    
    // set the duty cycle 
    OC1RS = (float)(2399)/100 * counter;
    
    // set direction pin
    if (counter == 100){
        DIRECTION = !DIRECTION; 
        counter = 0;
    }
}

int main(void) {
    init();
    SPI2_init();
    LCD_init();
    LCD_clearScreen(BACKGROUND);        // reset background
    TRISBbits.TRISB13 = 0;  // set B13 as output
    DIRECTION = 0;          // turn off direction pin (B13)     
    
    // Set Timer2 for PWM
    T2CONbits.TCKPS = 0;    // Timer2 prescaler N=1 (1:1)
    PR2 = 2399;             // PR = 48MHz/20kHz/1 - 1
    TMR2 = 0;               // initial TMR2 count is 0
    OC1CONbits.OCM = 0b110; // PWM mode without fault pin; other OC1CON bits are defaults
    OC1RS = 0;              // duty cycle
    OC1R = 0;               // initialize before turning OC1 on; afterward it is read-only
    T2CONbits.ON = 1;       // turn on Timer2
    OC1CONbits.ON = 1;      // turn on OC1
    RPB4R = 0b0101;         // set RB4 to be OC1
    
    // Set Timer3 for interrupt
    __builtin_disable_interrupts();     // disable interrupts
    T3CONbits.TCKPS = 5;    // Timer3 prescaler N=5 (1:32)
    PR3 = 14999;            // PR = 48MHz/100Hz/32 - 1
    TMR2 = 0;               // initial TMR3 count is 0
    T3CONbits.ON = 1;       // turn on Timer3
    IPC3bits.T3IP = 5;      // interrupt priority is 5
    IPC3bits.T3IS = 0;      // subpriority is 0, which is the default
    IFS0bits.T3IF = 0;      // clear CT interrupt flag
    IEC0bits.T3IE = 1;      // enable core timer interrupt
    __builtin_enable_interrupts();    // CPU interrupts enabled
    
    // generate random unsigned char array and plot it
    srand(time(0));
    int i = 0;
    unsigned char data1[240], data2[240], data3[240];
    for (i = 0; i < 240; i++){
        data1[i] = rand() % 256; // return number between 0-255 
        data2[i] = i;
        data3[i] = 240 - i; 
    }
    LCD_print("RED", 5, 5, RED_BACKGROUND, BACKGROUND);
    LCD_plot(15, data1, PLOT_LINE, RED_BACKGROUND);
    LCD_print("GREEN", 5, 30, GREEN_BACKGROUND, BACKGROUND);
    LCD_plot(40, data2, PLOT_LINE, GREEN_BACKGROUND);
    LCD_print("BLUE", 5, 55, BLUE_BACKGROUND, BACKGROUND);
    LCD_plot(65, data3, PLOT_LINE, BLUE_BACKGROUND);
    
    while (1){ ; }      // do nothing
    
  return 0;
}
