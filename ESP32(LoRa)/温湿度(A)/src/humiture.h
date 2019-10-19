#ifndef __HUMITURE_H_
#define __HUMITURE_H_
#include "stm32f10x.h"

float get_temp(void);
float get_humi(void);
void humiture_init(void);
void read_humiture(void);
void uart2_set_input_call(int (*c)(char ch));
int uart2_rec_handle(char ch);


#endif
