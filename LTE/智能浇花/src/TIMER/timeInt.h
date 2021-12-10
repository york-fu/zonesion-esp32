#ifndef __TIMERINT_H
#define __TIMERINT_H

#include "stm32f10x.h"
#include "contiki.h"


void TIM3_Int_Init(u16 arr,u16 psc); 
void TIM3_IrqCallSet(void(*func)(void));
 
#endif
