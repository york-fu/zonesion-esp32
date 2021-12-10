#ifndef _KEY_H_
#define _KEY_H_
#include "stm32f10x.h"

void key_init(void);
unsigned char get_key_status(void);

#endif