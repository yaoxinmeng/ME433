#include"startup.h"     // general initialisation code
#include"lcd.h"         // lcd helper file

#define BACKGROUND ILI9341_DARKGREEN
#define FONT ILI9341_ORANGE
#define INTERVAL 1200000    // 24MHz/20Hz = 1200000
#define LENGTH 75           // button length (x)
#define WIDTH 50            // button width (y)

int main(void) {
    init();
    SPI2_init();
    LCD_init();
    LCD_clearScreen(BACKGROUND);        // reset background
    
    char m[100], pressed = 0;
    unsigned short x, y;
    unsigned int z;
    int i = 0;
    
    // draw buttons and counter
    LCD_makeButton(120, 40, WIDTH, LENGTH, ILI9341_BLACK);
    LCD_print("I + +", 145, 61, FONT, ILI9341_BLACK);
    sprintf(m, "I = %d  ", i);
    LCD_print(m, 140, 135, FONT, BACKGROUND);
    LCD_makeButton(120, 180, WIDTH, LENGTH, ILI9341_BLACK);
    LCD_print("I - -", 145, 201, FONT, ILI9341_BLACK);
    
    while(1) {
        XPT2046_read(&x,&y,&z);
        sprintf(m,"X-raw: %d  ",x);
        LCD_print(m,15,15,ILI9341_RED,BACKGROUND);
        sprintf(m,"Y-raw: %d  ",y);
        LCD_print(m,15,25,ILI9341_RED,BACKGROUND);
        sprintf(m,"Pressure: %d  ",z);
        LCD_print(m,15,35,ILI9341_RED,BACKGROUND);
        
        // calibrate x, y and z
        x = x/15 - 25;
        y = 357 - y/11;
        if (z < 1500){
            sprintf(m,"X-position: NIL");
            LCD_print(m,15,45,FONT,BACKGROUND);
            sprintf(m,"Y-position: NIL");
            LCD_print(m,15,55,FONT,BACKGROUND);
            pressed = 0;
        }
        else{
            sprintf(m,"X-position: %d  ",x);
            LCD_print(m,15,45,FONT,BACKGROUND);
            sprintf(m,"Y-position: %d  ",y);
            LCD_print(m,15,55,FONT,BACKGROUND);
            // update counter
            if (!pressed){       
                if (x >= 120 && x <= (120+LENGTH)){
                    if (y >= 40 && y <= (40+WIDTH)){     // I++
                        i++;
                        sprintf(m, "I = %d  ", i);
                        LCD_print(m, 140, 135, FONT, BACKGROUND);
                        pressed = 1;
                    }
                    if (y >= 180 && y <= (180+WIDTH)){     // I--
                        i--;
                        sprintf(m, "I = %d  ", i);
                        LCD_print(m, 140, 135, FONT, BACKGROUND);
                        pressed = 1;
                    }
                }
            }
        }
    }
  return 0;
}
