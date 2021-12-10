#ifndef __EXTI_H
#define __EXIT_H	 

#include "stm32f10x.h"
#include "contiki.h"
	 
void EXTI9_5_Init(uint8_t GPIO_PortSourceX,uint8_t GPIO_PinSourceX);
short EXTI9_5_IrqCallSet(uint8_t index,void(*func)(void));
		 					    
#endif

