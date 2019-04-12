#include<math.h>        // needed for sin wave
#include"startup.h"     // general initialisation code
#include"spi.h"         // spi initialisation code

#define LEN 1000        // 1000 samples per second
#define HALF_PERIOD_B 100   // at 5Hz, 1 cycle = 200 values
#define PI 3.1415       // pi

void setVoltage(char a, unsigned int v);

int main(void) {
    init();
    spi_init(); 
    
    int i = 0;
    unsigned int a[LEN], b[LEN];
    
    // set output of A
    for(i=0; i<LEN; i++){
        // w = 2*pi*f, f = 10Hz, t = i/1000
        // w*t = 2*pi*i/100 = pi*i/50
        a[i] = (unsigned int) (2048 + 2048 * sin(i*PI/50.0));  
    }
    
    //set output of B
    for(i=0; i<LEN; i++){
        if ((i/HALF_PERIOD_B)%2 == 0){    
            b[i] = (unsigned int)(4096 * (i%HALF_PERIOD_B)/100.0);
        }
        else {
            b[i] = (unsigned int)(4096 - (4096/100.0)*(i%HALF_PERIOD_B));
        }
    }
    
    i = 0;
    while(1) {
        _CP0_SET_COUNT(0);
        
        setVoltage(0,a[i]);		// set output A
        setVoltage(1,b[i]);		// set output B
        
        i++;
        if (i == LEN){          // reset every 1000 points
            i = 0;
        }
        
        while(_CP0_GET_COUNT() < 24000000/1000) {;}  // delay for 1ms
    }
  return 0;
}


void setVoltage(char channel, unsigned int v) {
	unsigned short t = 0;
	t = channel << 15; // channel is at the very start of the data transfer
	t = t | 0b0111000000000000;
	t = t | (v & 0b111111111111); // add 12-bit voltage to the end of t
	
	CS = 0;
    spi_io(t);
    /*
	spi_io(t >> 8);          // send first 8 bits
    spi_io(t & 0b11111111);  // send last 8 bits
    */
    CS = 1;
}