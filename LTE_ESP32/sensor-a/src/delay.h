#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f10x.h"  
#include <sys/clock.h>
void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

extern void clock_delay_us(unsigned short ut);
extern void clock_delay_ms(unsigned short ms);

#define delay_init()    clock_init()
#define delay_ms(x)     clock_delay_ms(x)
#define delay_us(x)     clock_delay_us(x)

#endif





























