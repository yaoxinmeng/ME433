#include <xc.h>                     // processor SFR definitions
#include <sys/attribs.h>            // __ISR macro
#include "dsp.h"
  
short FIR_BUF[FIR_LEN] = {0,0,0,0,0}, MAF_BUF[MAF_LEN] = {0,0,0,0,0}, IIR_BUF = 0;
float FIR_COEFFICIENTS[FIR_LEN] = {0.0338, 0.2401, 0.4522, 0.2401, 0.0338};
int fir_index = 0, maf_index = 0;

void update_IIR(short old_data){
    IIR_BUF = old_data;
}

void update_MAF(short new_data){
    MAF_BUF[maf_index] = new_data;
    maf_index++;
    if(maf_index == MAF_LEN){
        maf_index = 0;
    }
}

void update_FIR(short new_data){
    FIR_BUF[fir_index] = new_data;
    fir_index++;
    if(fir_index == FIR_LEN){
        fir_index = 0;
    }
}

short get_IIR(short new_data){
    float temp = IIR_A * IIR_BUF + IIR_B * new_data;
    return (short)temp;
}

short get_MAF(void){
    float temp = 0;
    int i;
    for (i=0;i<MAF_LEN;i++){
        temp = temp + MAF_BUF[i];       // sum of all values in array
    }
    return (short)(temp / MAF_LEN);     // return moving average 
}

short get_FIR(void){
    float temp = 0;                             
    int i, current_index = fir_index - 1;
    if (current_index < 0){current_index = 4;}  // checks that latest index exists
    for (i=0;i<FIR_LEN;i++){
        temp = temp + FIR_BUF[current_index] * FIR_COEFFICIENTS[i];   // sum of weighted values
        current_index++;
        if(current_index == FIR_LEN){
            current_index = 0;
        }
    }
    return (short)temp;
}
