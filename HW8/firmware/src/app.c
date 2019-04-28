/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include"lcd.h"         // lcd helper file
#include"i2c.h"         // i2c functions

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */
#define BACKGROUND ILI9341_DARKGREEN
#define FONT ILI9341_ORANGE
#define INTERVAL 1200000    // 24MHz/20Hz = 1200000
#define LENGTH 181          // counter length, also affects bar length
#define BAR_WIDTH 5         // bar width with border of 2px
#define WHO_AM_I 0b01101001 // WHO_AM_I value of IMU
#define LED LATBbits.LATB13 // LED pin

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
    __builtin_disable_interrupts();

    // set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);

    // 0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;

    // enable multi vector interrupts
    INTCONbits.MVEC = 0x1;

    // disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;
    
    __builtin_enable_interrupts();
    
    SPI2_init();
    LCD_init();
    i2c_init();
    LCD_clearScreen(BACKGROUND);        // reset background
    TRISBbits.TRISB13 = 0;              // set B13 as output for LED
    LED = 0;

    char m[100];
    unsigned char name;

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
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            bool appInitialized = true;
       
        
            if (appInitialized)
            {
            
                appData.state = APP_STATE_SERVICE_TASKS;
            }
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
            char m[100];
            unsigned char raw_data[14]; // 0-1 is temp, 2-3 is x_ang, 4-5 is y_ang, 6-7 is z_ang,
                                        // 8-9 is x_accel, 10-11 is y_accel, 12-13 is z_accel
            short x_accel, y_accel;
            float xf_accel, yf_accel;
            
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

            sprintf(m, "X-acceleration: %.2f ", xf_accel);
            LCD_print(m, 15, 15, FONT, BACKGROUND);     // print text
            sprintf(m, "Y-acceleration: %.2f ", yf_accel);
            LCD_print(m, 15, 25, FONT, BACKGROUND);     // print text

            while(_CP0_GET_COUNT() < INTERVAL) {;}      // wait 50ms
            break;
        }

        /* TODO: implement your application state machine.*/
        

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

 

/*******************************************************************************
 End of File
 */
