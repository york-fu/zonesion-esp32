#ifndef __SOIL_H_
#define __SOIL_H_
#include "stm32f10x.h"

void soil_init(void);
void read_soil(void);
int uart2_rec_handle(char ch);
float get_soilHumi(void);
float get_soilTemp(void);

#endif
