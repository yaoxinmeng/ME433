#include<math.h>        // needed for sin wave
#include"startup.h"     // general initialisation code
#include"lcd.h"         // lcd helper file

#define BACKGROUND ILI9341_DARKGREEN
#define FONT ILI9341_ORANGE
#define INTERVAL 2400000    // 24MHz/10Hz = 2400000
#define LENGTH 100          // counter length, also affects bar length
#define BAR_HEIGHT 9        // bar height with border of 2px

int main(void) {
    init();
    SPI1_init(); 
    LCD_init();
    LCD_clearScreen(BACKGROUND);     // reset background
    
    // define bar boundary
    LCD_makeBar(28, 42, BAR_HEIGHT, LENGTH+4, ILI9341_BLACK, BACKGROUND);
    char m[100];
    unsigned char i = 0;
    float fps = 0;
    
    while(1) {
        _CP0_SET_COUNT(0);
        sprintf(m, "Hello world %d!", i);
        LCD_print(m, 28, 32, FONT, BACKGROUND);     // print text
        LCD_drawBar(30, 44, i, FONT, BACKGROUND);   // print bar
        i++;
        if(i == LENGTH){       // reset i to loop back to 0
            i = 0;
            LCD_print(m, 28, 32, BACKGROUND, BACKGROUND);  // clear text
        }
        fps = 1/(((float)_CP0_GET_COUNT())/24000000);
        sprintf(m, "FPS: %f", fps);
        LCD_print(m, 28, 100, FONT, BACKGROUND);    // print fps
        while(_CP0_GET_COUNT() < INTERVAL) {;}      // wait 1ms
    }
  return 0;
}
