#ifndef _Weather_h_
#define _Weather_h_

#include "stm32f10x.h"
#include "contiki.h"

void Weather_Init();
float WindSpeed_Get();

#endif