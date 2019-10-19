/*********************************************************************************************
* 文件：iic.h
* 作者：zonesion
* 说明：iic头文件
* 修改：
* 注释：
*********************************************************************************************/
#ifndef _IIC_H_
#define _IIC_H_

#include <math.h>
#include <stdio.h>
#include "stm32f10x.h"


/*********************************************************************************************
* 宏定义
*********************************************************************************************/
//I2C
#define I2C_SCL_RCC     RCC_APB2Periph_GPIOB
#define I2C_SCL_GPIO    GPIOB
#define I2C_SCL_PIN     GPIO_Pin_1

#define I2C_SDA_RCC     RCC_APB2Periph_GPIOB
#define I2C_SDA_GPIO    GPIOB
#define I2C_SDA_PIN     GPIO_Pin_0

#define I2C_SDA_PIN_NUM 0

#if (I2C_SDA_PIN_NUM < 8)
#define SDA_IN()        {GPIOB->CRL &= (0x0000<<I2C_SDA_PIN_NUM);GPIOB->CRL |= (0x1000<<I2C_SDA_PIN_NUM);}
#define SDA_OUT()       {GPIOB->CRL &= (0x0000<<I2C_SDA_PIN_NUM);GPIOB->CRL |= (0x0011<<I2C_SDA_PIN_NUM);}
#else
#define SDA_IN()        {GPIOB->CRH &= (0x0000<<I2C_SDA_PIN_NUM);GPIOB->CRH |= (0x1000<<I2C_SDA_PIN_NUM);}
#define SDA_OUT()       {GPIOB->CRH &= (0x0000<<I2C_SDA_PIN_NUM);GPIOB->CRH |= (0x0011<<I2C_SDA_PIN_NUM);}
#endif


#define SCL_H           (I2C_SCL_GPIO->BSRR |= (I2C_SCL_PIN))
#define SCL_L           (I2C_SCL_GPIO->BSRR |= (I2C_SCL_PIN<<15))

#define SDA_H           (I2C_SDA_GPIO->BSRR |= (I2C_SDA_PIN))
#define SDA_L           (I2C_SCL_GPIO->BSRR |= (I2C_SDA_PIN<<15))

#define SDA_R           (I2C_SDA_GPIO->IDR&I2C_SDA_PIN)
/*********************************************************************************************
* 外部原型函数
*********************************************************************************************/
void iic_delay_us(unsigned int i);
void iic_init(void);
void iic_start(void);
void iic_stop(void);
void iic_send_ack(int ack);
int iic_recv_ack(void);
unsigned char iic_write_byte(unsigned char data);
unsigned char iic_read_byte(unsigned char ack);
void delay(unsigned int t);

#endif 