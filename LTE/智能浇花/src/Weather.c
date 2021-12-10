#include "Weather.h"
#include "EXTI/exti.h"
#include "TIMER/timeInt.h" 

#define Pi      3.1415

unsigned short windSpeedCount=0,rainfallCount=0;
float windSpeed,rainfall;


float WindSpeed_Get()
{
  return windSpeed;
}

void WindSpeed_ExtIntIrq()
{
  windSpeedCount++;
}

void Weather_TimeIrq()
{
  //计算风速:s=r*w,w=2*pi*f
  windSpeed = (2.0*Pi*0.09*(float)(windSpeedCount/2.0)); 
  windSpeedCount = 0;
}


void Weather_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
  
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORT时钟
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
  
  EXTI9_5_Init(GPIO_PortSourceGPIOA,GPIO_PinSource7);
  EXTI9_5_IrqCallSet(7,WindSpeed_ExtIntIrq);
  
  TIM3_Int_Init(10000-1,7200-1);//5s
  TIM3_IrqCallSet(Weather_TimeIrq);
}
