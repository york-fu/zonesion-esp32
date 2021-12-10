#include "EXTI/exti.h"
#include "delay.h"


//外部中断初始化函数
void EXTI0_Init(uint8_t GPIO_PortSourceX)
{
  
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
  //中断线以及中断初始化配置
  GPIO_EXTILineConfig(GPIO_PortSourceX,GPIO_PinSource0);
  
  EXTI_InitStructure.EXTI_Line = GPIO_PinSource0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}

void EXTI0_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line0);  //清除EXTI0线路挂起位
}



//外部中断初始化函数
void EXTI9_5_Init(uint8_t GPIO_PortSourceX,uint8_t GPIO_PinSourceX)
{
  uint32_t EXTI_Line_x = 0;
  
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
  //中断线以及中断初始化配置
  EXTI_DeInit();
  
  GPIO_EXTILineConfig(GPIO_PortSourceX,GPIO_PinSourceX);
  
  switch(GPIO_PinSourceX)
  {
  case GPIO_PinSource5:EXTI_Line_x = EXTI_Line5;
    break;
  case GPIO_PinSource6:EXTI_Line_x = EXTI_Line6;
    break;
  case GPIO_PinSource7:EXTI_Line_x = EXTI_Line7;
    break;
  case GPIO_PinSource8:EXTI_Line_x = EXTI_Line8;
    break;
  case GPIO_PinSource9:EXTI_Line_x = EXTI_Line9;
    break;
  }
  
  EXTI_InitStructure.EXTI_Line = EXTI_Line_x;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}


void (*EXTI9_5_IrqCall[5])(void) = {NULL};

short EXTI9_5_IrqCallSet(uint8_t index,void(*func)(void))
{
  if((index < 5) || (index > 9)) return 1;
  EXTI9_5_IrqCall[index-5] = func;
  return 0;
}


void EXTI9_5_IRQHandler(void)
{			
  if(EXTI_GetITStatus(EXTI_Line5) == SET)
  {
    EXTI_ClearITPendingBit(EXTI_Line5);    //清除中断标志位  
    if(EXTI9_5_IrqCall[0] != NULL)
      EXTI9_5_IrqCall[0]();
  }
  if(EXTI_GetITStatus(EXTI_Line6) == SET)
  {
    EXTI_ClearITPendingBit(EXTI_Line6);    //清除中断标志位  
    if(EXTI9_5_IrqCall[1] != NULL)
      EXTI9_5_IrqCall[1]();
  }
  if(EXTI_GetITStatus(EXTI_Line7) == SET)
  {
    EXTI_ClearITPendingBit(EXTI_Line7);    //清除中断标志位 
    if(EXTI9_5_IrqCall[2] != NULL)
      EXTI9_5_IrqCall[2](); 
  }
  if(EXTI_GetITStatus(EXTI_Line8) == SET)
  {
    EXTI_ClearITPendingBit(EXTI_Line8);    //清除中断标志位  
    if(EXTI9_5_IrqCall[3] != NULL)
      EXTI9_5_IrqCall[3]();
  }
  if(EXTI_GetITStatus(EXTI_Line9) == SET)
  {
    EXTI_ClearITPendingBit(EXTI_Line9);    //清除中断标志位 
    if(EXTI9_5_IrqCall[4] != NULL)
      EXTI9_5_IrqCall[4](); 
  }
}


//外部中断初始化函数
void EXTI15_10_Init(uint8_t GPIO_PortSourceX,uint8_t GPIO_PinSourceX)
{
  
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
  //中断线以及中断初始化配置
  GPIO_EXTILineConfig(GPIO_PortSourceX,GPIO_PinSourceX);
  
  EXTI_InitStructure.EXTI_Line = GPIO_PinSourceX;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能按键所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}

void EXTI15_10_IRQHandler(void)
{
  EXTI_ClearITPendingBit(EXTI_Line15);  //清除LINE15线路挂起位
}
