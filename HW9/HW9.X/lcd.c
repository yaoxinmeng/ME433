#include <xc.h>
#include "lcd.h"

static unsigned short bar_length, bar_width;

void LCD_init() {
    int time = 0;
    
    CS_SCREEN = 0; // CS_SCREEN of LCD
   
    LCD_command(ILI9341_SWRESET);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 7200000) {} // 300ms

    LCD_command(0xEF);
  	LCD_data(0x03);
	LCD_data(0x80);
	LCD_data(0x02);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xCF);
  	LCD_data(0x00);
	LCD_data(0xC1);
	LCD_data(0x30);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xED);
  	LCD_data(0x64);
	LCD_data(0x03);
	LCD_data(0x12);
    LCD_data(0x81);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xE8);
  	LCD_data(0x85);
	LCD_data(0x00);
	LCD_data(0x78);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xCB);
  	LCD_data(0x39);
	LCD_data(0x2C);
	LCD_data(0x00);
    LCD_data(0x34);
    LCD_data(0x02);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xF7);
  	LCD_data(0x20);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xEA);
  	LCD_data(0x00);
	LCD_data(0x00);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_PWCTR1);
  	LCD_data(0x23);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_PWCTR2);
  	LCD_data(0x10);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_VMCTR1 );
  	LCD_data(0x3e);
    LCD_data(0x28);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_VMCTR2);
  	LCD_data(0x86);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_MADCTL);
  	LCD_data(0x48);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
/*    
    LCD_command(ILI9341_VSCRSADD);
  	LCD_data(0x00);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
 */   
    LCD_command(ILI9341_PIXFMT);
  	LCD_data(0x55);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_FRMCTR1);
  	LCD_data(0x00);
    LCD_data(0x18);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command( ILI9341_DFUNCTR);
  	LCD_data(0x08);
    LCD_data(0x82);
    LCD_data(0x27);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xF2);
  	LCD_data(0); // 1
    LCD_data(0x00);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_GAMMASET);
  	LCD_data(0x01);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_GMCTRP1);
  	LCD_data(0x0F);
    LCD_data(0x31);
    LCD_data(0x2B);
    LCD_data(0x0C);
    LCD_data(0x0E);
    LCD_data(0x08);
    LCD_data(0x4E);
    LCD_data(0xF1);
    LCD_data(0x37);
    LCD_data(0x07);
    LCD_data(0x10);
    LCD_data(0x03);
    LCD_data(0x0E);
    LCD_data(0x09);
    LCD_data(0x00);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_GMCTRN1);
  	LCD_data(0x00);
    LCD_data(0x0E);
    LCD_data(0x14);
    LCD_data(0x03);
    LCD_data(0x11);
    LCD_data(0x07);
    LCD_data(0x31);
    LCD_data(0xC1);
    LCD_data(0x48);
    LCD_data(0x08);
    LCD_data(0x0F);
    LCD_data(0x0C);
    LCD_data(0x31);
    LCD_data(0x36);
    LCD_data(0x0F);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(0xB1);
  	LCD_data(0x00);
    LCD_data(0x10);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_SLPOUT);
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    LCD_command(ILI9341_DISPON);
    
    CS_SCREEN = 1; // CS_SCREEN
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    
    CS_SCREEN = 0; // CS_SCREEN
    
    LCD_command(ILI9341_MADCTL);
    LCD_data(MADCTL_MX | MADCTL_BGR); // rotation
    time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms
    
    CS_SCREEN = 1; // CS_SCREEN
}

void SPI2_init() {
    // SCK2(B15), SDO2(A1), SDI2(A4), CS_SCREEN(B7), DC(B14), CS_TOUCH(B2)
  SDI2Rbits.SDI2R = 0b0010; // A4 is SDI2
  RPA1Rbits.RPA1R = 0b0100; // A1 is SDO2
  TRISBbits.TRISB7 = 0;     // CS_SCREEN is B7
  TRISBbits.TRISB2 = 0;     // CS_TOUCH is B2
  CS_SCREEN = 1;            // CS_SCREEN starts high
  CS_TOUCH = 1;             // CS_TOUCH starts high
  TRISBbits.TRISB14 = 0;    // DC pin
  DC = 1;                   // DC starts high
  
  SPI2CON = 0;              // turn off the spi module and reset it
  SPI2BUF;                  // clear the rx buffer by reading from it
  SPI2BRG = 3;              // baud rate to 12 MHz [SPI2BRG = (48000000/(2*desired))-1]
  SPI2STATbits.SPIROV = 0;  // clear the overflow bit
  SPI2CONbits.CKE = 1;      // data changes when clock goes from hi to lo (since CKP is 0)
  SPI2CONbits.MSTEN = 1;    // master operation
  SPI2CONbits.ON = 1;       // turn on spi2
}

unsigned char spi_io(unsigned char o) {
  SPI2BUF = o;
  while(!SPI2STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  return SPI2BUF;
}

void LCD_command(unsigned char com) {
    DC = 0; // DC
    spi_io(com);
    DC = 1; // DC
}

void LCD_data(unsigned char dat) {
    spi_io(dat);
}

void LCD_data16(unsigned short dat) {
    spi_io(dat>>8);
    spi_io(dat);
}

void LCD_setAddr(unsigned short x, unsigned short y, unsigned short w, unsigned short h) {
    LCD_command(ILI9341_CASET); // Column
    LCD_data16(x);
	LCD_data16(x+w-1);

	LCD_command(ILI9341_PASET); // Page
	LCD_data16(y);
	LCD_data16(y+h-1);

	LCD_command(ILI9341_RAMWR); // Into RAM
}

void LCD_drawPixel(unsigned short x, unsigned short y, unsigned short color) {
  // check boundary
    if (x < 240 && y < 320){
        CS_SCREEN = 0; // CS_SCREEN
    
        LCD_setAddr(x,y,1,1);
        LCD_data16(color);
    
        CS_SCREEN = 1; // CS_SCREEN
    }
}

void LCD_clearScreen(unsigned short color) {
    int i;
    
    CS_SCREEN = 0; // CS_SCREEN
    
    LCD_setAddr(0,0,ILI9341_TFTWIDTH,ILI9341_TFTHEIGHT);
	for (i = 0;i < ILI9341_TFTWIDTH*ILI9341_TFTHEIGHT; i++){
		LCD_data16(color);
	}
    
    CS_SCREEN = 1; // CS_SCREEN
}
void LCD_clearLine(unsigned short y, unsigned short b_color){
    unsigned short x;
    for(x = 0; x < ILI9341_TFTWIDTH; x++){
        LCD_drawChar(' ', x, y, b_color, b_color);
    }
}

void LCD_drawChar(char c, unsigned short x, unsigned short y, unsigned short f_color, unsigned short b_color){
    unsigned short col, row;
    for (col = 0; col < 5; col++){
        char byte_col = ASCII[c - 0x20][col];   // get the byte of each column
        for (row = 0; row < 8; row++){
            if (((byte_col >> row) & 1) == 1){           // get the bit on that row
                LCD_drawPixel(x+col, y+row, f_color);  // draw in font colour      
            }
            else{
                LCD_drawPixel(x+col, y+row, b_color);   // draw in background colour
            }
        }
    }
}

void LCD_print(char* m, unsigned short x, unsigned short y, unsigned short f_color, unsigned short b_color){
    int i = 0;
    unsigned short x_char;
    while(m[i] != 0){
        // position of new character
        x_char = x + i*5;   
        LCD_drawChar(m[i], x_char, y, f_color, b_color);
        i++;
    }
}

void LCD_makeBar(unsigned short width, unsigned short length, unsigned short f_color, unsigned short b_color){
    unsigned short row, col, x, y, half_width, half_length;
    
    x = ILI9341_TFTWIDTH/2;
    y = ILI9341_TFTHEIGHT/2;
    half_width = (width-1)/2;
    half_length = (length-1)/2;
    
    // draw horizontal bar
    // draw left and right margins
    for(col = 0; col < 2; col++){
        for(row = 0; row < width; row++){   
            LCD_drawPixel(x-half_length+col, y+half_width-row, f_color);
            LCD_drawPixel(x+half_length-col, y+half_width-row, f_color);
        }
    }
    // draw top and bottom margins
    for(col = 0; col < length; col++){
        for(row = 0; row < 2; row++){   
            LCD_drawPixel(x-half_length+col, y+half_width-row, f_color);
            LCD_drawPixel(x-half_length+col, y-half_width+row, f_color);
        }
    }
    
    // draw vertical bar
    // draw left and right margins
    for(col = 0; col < 2; col++){
        for(row = 0; row < length; row++){   
            LCD_drawPixel(x-half_width+col, y-half_length+row, f_color);
            LCD_drawPixel(x+half_width-col, y-half_length+row, f_color);
        }
    }
    // draw top and bottom margins
    for(col = 0; col < width; col++){
        for(row = 0; row < 2; row++){   
            LCD_drawPixel(x-half_width+col, y+half_length-row, f_color);
            LCD_drawPixel(x-half_width+col, y-half_length+row, f_color);
        }
    }
    
    // draw middle section with background color
    for (col = 0; col < (length-4); col++){
        for (row = 0; row < (width-4); row++){
            LCD_drawPixel(x+col-(half_length-2), y+row-(half_width-2), b_color);
        }
    }
    for (col = 0; col < (width-4); col++){
        for (row = 0; row < (length-4); row++){
            LCD_drawPixel(x+col-(half_width-2), y+row-(half_length-2), b_color);
        }
    }
    
    // set bar_height and bar_width for LCD_drawBar
    bar_width = width - 4;
    bar_length = length - 4;
}

void LCD_drawBarX(short length, unsigned short f_color, unsigned short b_color){
    unsigned short col, row, x, y, half_width, half_length;
    x = ILI9341_TFTWIDTH/2;
    y = ILI9341_TFTHEIGHT/2;
    half_width = (bar_width-1)/2;
    half_length = (bar_length-1)/2;
    
    if (length >= 0){       // positive acceleration
        for(col = 0; col < half_length; col++){
            for(row = 0; row < bar_width; row++){
                if (col < length){
                    LCD_drawPixel(x+col, y-half_width+row, f_color);
                }
                else{
                    LCD_drawPixel(x+col, y-half_width+row, b_color);
                }
                LCD_drawPixel(x-col, y-half_width+row, b_color);
            }
        }
    }
    else{                   // negative acceleration
        for(col = 0; col < half_length; col++){
            for(row = 0; row < bar_width; row++){
                if (col < (-1*length)){
                    LCD_drawPixel(x-col, y-half_width+row, f_color);
                }
                else{
                    LCD_drawPixel(x-col, y-half_width+row, b_color);
                }
                LCD_drawPixel(x+col, y-half_width+row, b_color);
            }
        }
    }
}

void LCD_drawBarY(short length, unsigned short f_color, unsigned short b_color){
    unsigned short col, row, x, y, half_width, half_length;
    x = ILI9341_TFTWIDTH/2;
    y = ILI9341_TFTHEIGHT/2;
    half_width = (bar_width-1)/2;
    half_length = (bar_length-1)/2;
    
    if (length >= 0){       // positive acceleration
        for(col = 0; col < bar_width; col++){
            for(row = 0; row < half_length; row++){
                if (row < length){
                    LCD_drawPixel(x-half_width+col, y+row, f_color);
                }
                else{
                    LCD_drawPixel(x-half_width+col, y+row, b_color);
                }
                LCD_drawPixel(x-half_width+col, y-row, b_color);
            }
        }
    }
    else{                   // negative acceleration
        for(col = 0; col < bar_width; col++){
            for(row = 0; row < half_length; row++){
                if (row < (-1*length)){
                    LCD_drawPixel(x-half_width+col, y-row, f_color);
                }
                else{
                    LCD_drawPixel(x-half_width+col, y-row, b_color);
                }
                LCD_drawPixel(x-half_width+col, y+row, b_color);
            }
        }
    }
}

void XPT2046_read(unsigned short *x, unsigned short *y, unsigned int *z){
    unsigned char com_x = 0b11010001;
    unsigned char com_y = 0b10010001;
    unsigned char com_z1 = 0b10110001;
    unsigned char com_z2 = 0b11000001;
    unsigned short x_temp, y_temp, z1_temp, z2_temp;
    
    CS_TOUCH = 0;
    spi_io(com_x);      // send command for x-position
    x_temp = spi_io(0x00);         
    x_temp = (x_temp << 8) | spi_io(0x00);
    
    spi_io(com_y);      // send command for y-position
    y_temp = spi_io(0x00);         
    y_temp = (y_temp << 8) | spi_io(0x00);
    
    spi_io(com_z1);      // send command for z1
    z1_temp = spi_io(0x00);         
    z1_temp = (z1_temp << 8) | spi_io(0x00);
    
    spi_io(com_z2);      // send command for z2
    z2_temp = spi_io(0x00);         
    z2_temp = (z2_temp << 8) | spi_io(0x00);
    CS_TOUCH = 1;
    
    *x = x_temp >> 3;
    *y = y_temp >> 3;
    *z = (z1_temp >> 3) - (z2_temp >> 3) + 4095;
}

void LCD_makeButton(unsigned short x, unsigned short y, unsigned short width, unsigned short length, unsigned short color){
    int row, col;
    for (row=0;row<width;row++){
        for (col=0;col<length;col++){
            LCD_drawPixel(x+col,y+row,color);
        }
    }
}