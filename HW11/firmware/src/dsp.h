#ifndef _DSP_H    /* Guard against multiple inclusion */
#define _DSP_H

#define FIR_LEN 5
#define MAF_LEN 8
#define IIR_A 0.6
#define IIR_B 0.4

void update_IIR(short old_data);
void update_MAF(short new_data);
void update_FIR(short new_data);
short get_IIR(short new_data);
short get_MAF(void);
short get_FIR(void);

#endif