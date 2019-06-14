#ifndef _CAMERA_H    /* Guard against multiple inclusion */
#define _CAMERA_H

#include <xc.h>                     // processor SFR definitions
#include <sys/attribs.h>            // __ISR macro

#define OV7670_SCCB_ADDRESS 0x21
// Image format: "QCIF" (the standard defines QCIF as 176 x 144)
// However my OV7670 outputs 174 x 144 frames
#define WIDTH 174
#define HEIGHT 144
#define BYTES_PER_PIXEL 2

char outputBuffer[WIDTH * HEIGHT * BYTES_PER_PIXEL];

void camera_init();
void ov7670_setup();
void writeCameraRegister(unsigned char reg, unsigned char val);
int ov7670_count_horz(unsigned char * d);
int ov7670_count_vert(unsigned char * d);

#endif