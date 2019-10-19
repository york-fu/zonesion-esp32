#ifndef _delay_h_
#define _delay_h_

#include <sys/clock.h>

extern void clock_delay_us(unsigned short ut);
extern void clock_delay_ms(unsigned short ms);

#define delay_us(x)    clock_delay_us(x) 
#define delay_ms(x)    clock_delay_ms(x) 


void delay_init();

#endif