#include<math.h>        // needed for sin wave
#include"startup.h"     // general initialisation code
#include"lcd.h"         // lcd helper file
#include"i2c.h"         // i2c functions

#define BACKGROUND ILI9341_DARKGREEN
#define FONT ILI9341_ORANGE
#define INTERVAL 1200000    // 24MHz/20Hz = 1200000
#define LENGTH 181          // counter length, also affects bar length
#define BAR_WIDTH 5         // bar width with border of 2px
#define WHO_AM_I 0b01101001 // WHO_AM_I value of IMU
#define LED LATBbits.LATB13 // LED pin

int main(void) {
    init();
    SPI2_init(); 
    LCD_init();
    i2c_init();
    LCD_clearScreen(BACKGROUND);        // reset background
    TRISBbits.TRISB13 = 0;              // set B13 as output for LED
    LED = 0;
    
    char m[100];
    unsigned char name;
    unsigned char raw_data[14]; // 0-1 is temp, 2-3 is x_ang, 4-5 is y_ang, 6-7 is z_ang, 
                                // 8-9 is x_accel, 10-11 is y_accel, 12-13 is z_accel
    short x_accel, y_accel;
    float xf_accel, yf_accel;
    
    // Checks if IMU is ready to send data
    i2c_master_start();                 // send start bit
    i2c_master_send(ADDR << 1);         // bit 0 = 0 for write
    i2c_master_send(0x0F);              // WHO_AM_I register address
    i2c_master_restart();               // send restart bit
    i2c_master_send((ADDR << 1) | 1);   // bit 0 = 1 for read
    name = i2c_master_recv();           // save the value returned
    i2c_master_ack(1);                  // send ack bit
    i2c_master_stop();                  // send stop bit
    
    if(name != WHO_AM_I){
        sprintf(m, "Error! Restart PIC...");
        LCD_print(m, 28, 32, FONT, BACKGROUND);     // print text
        LED = 1;
        while(1){;}
    }
    
    // define bar boundary
    LCD_makeBar(BAR_WIDTH+4, LENGTH+4, ILI9341_BLACK, BACKGROUND);
    
    while(1) {
        _CP0_SET_COUNT(0);
        LED = !LED;
        
        I2C_read_multiple(ADDR, 0x20, raw_data, 14);    // read from i2c 14 times
        x_accel = (raw_data[9] << 8) | raw_data[8];     // combine 2 bytes to form short
        y_accel = (raw_data[11] << 8) | raw_data[10];   // combine 2 bytes to form short
        x_accel = (short)(((float)LENGTH)/32768 * x_accel);
        y_accel = (short)(((float)LENGTH)/32768 * y_accel);
        xf_accel = ((float)x_accel)/LENGTH * 2;
        yf_accel = ((float)y_accel)/LENGTH * 2;
        
        LCD_drawBarX(x_accel, FONT, BACKGROUND);    // print X bar
        LCD_drawBarY(y_accel, FONT, BACKGROUND);    // print Y bar
        
        sprintf(m, "X-acceleration: %.2f", xf_accel);
        LCD_print(m, 15, 15, FONT, BACKGROUND);     // print text
        sprintf(m, "Y-acceleration: %.2f", yf_accel);
        LCD_print(m, 15, 25, FONT, BACKGROUND);     // print text
        
        while(_CP0_GET_COUNT() < INTERVAL) {;}      // wait 50ms
    }
  return 0;
}
