#include<math.h>        // needed for sin wave
#include"startup.h"     // general initialisation code
#include"i2c.h"         // i2c functions

#define INTERVAL 2400000  // LED blink interval of 10Hz (24Mhz/1.2Mhz/2 = 5Hz)

void i2c_LED(int n);
int i2c_button(void);
void blink_LED();

int main(void) {
    init();
    i2c_init();
    i2c_LED(1);
    while(1) {          // button is not pressed
        blink_LED();
        if (i2c_button()){
            i2c_LED(0); // turn off i2c LED
        }
        else{
            i2c_LED(1); // turn on i2c LED
        }
    }
    return 0;
}

void blink_LED(){
    if (_CP0_GET_COUNT() >= INTERVAL){  // blinks light at 10Hz 
        LED = !LED;
        _CP0_SET_COUNT(0);
    }
}

void i2c_LED(int n){
    if (n){         // turn on LED
        i2c_master_start();             // send start bit
        i2c_master_send(ADDR << 1);     // bit 0 = 0 for write
        i2c_master_send(0x0A);          // OLAT register address
        i2c_master_send(0b00000001);    // turn off bit 0
        i2c_master_stop();              // send stop bit
    }
    else{           // turn off LED
        i2c_master_start();             // send start bit
        i2c_master_send(ADDR << 1);     // bit 0 = 0 for write
        i2c_master_send(0x0A);          // OLAT register address
        i2c_master_send(0b00000000);    // turn on bit 0
        i2c_master_stop();              // send stop bit
    }
}

int i2c_button(void){
    i2c_master_start();                 // send start bit
    i2c_master_send(ADDR << 1);         // bit 0 = 0 for write
    i2c_master_send(0x09);              // GPIO register address
    i2c_master_restart();               // send restart bit
    i2c_master_send((ADDR << 1) | 1);   // bit 0 = 1 for read
    char c = i2c_master_recv();         // save the value returned
    i2c_master_ack(1);                  // send ack bit
    i2c_master_stop();                  // send stop bit
    
    return c >> 7;                      // make GP7 the LSB
}