#include <xc.h>
#include "lcd.h"

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

void SPI1_init(){
    // LCD uses SPI1: A1 is SDO1, B5 is CST, B14 is SCK1, A9 is DC, B7 is CS
    RPA1R = 0b0011;   
    TRISBbits.TRISB5 = 0;     
    TRISAbits.TRISA9 = 0;
    TRISBbits.TRISB7 = 0; 
    CS_SCREEN = 1;            // CS_SCREEN starts high
    CS_TOUCH = 1;             // CS_TOUCH starts high
    DC = 1;                   // DC starts high
    
    SPI1CON = 0;              // turn off the spi module and reset it
    SPI1BUF;                  // clear the rx buffer by reading from it
    SPI1BRG = 3;              // baud rate to 12 MHz [SPI1BRG = (48000000/(2*desired))-1]
    SPI1STATbits.SPIROV = 0;  // clear the overflow bit
    SPI1CONbits.CKE = 1;      // data changes when clock goes from hi to lo (since CKP is 0)
    SPI1CONbits.MSTEN = 1;    // master operation
    SPI1CONbits.ON = 1;       // turn on spi1
}

unsigned char spi_io(unsigned char o) {
  SPI1BUF = o;
  while(!SPI1STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  return SPI1BUF;
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

void LCD_plot(unsigned short y, unsigned char *data, unsigned short color, unsigned short b_color){
    int i = 0, n = 0;
    for (i = 0; i < 240; i++){
        data[i] = data[i] >> 5; // read only the 3 MSBs 
        for (n = 0; n < 8; n++){
            if (n == data[i]){
                LCD_drawPixel(i, y + 7 - n, color);
            }
            else{
                LCD_drawPixel(i, y + 7 - n, b_color);
            }
        }
    }
}