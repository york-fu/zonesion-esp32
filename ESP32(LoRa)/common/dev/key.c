/*********************************************************************************************
*文件: key.c
*作者: zonesion   2015.12.18
*说明: 按键处理程序
*修改:
*注释:
*********************************************************************************************/
#include "key.h"

void key_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  
  GPIO_Init(GPIOB, &GPIO_InitStructure);  
}

unsigned char get_key_status(void)
{
  unsigned char key_status = 0;
  if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 0){
    key_status |= 0x01;
  }
  else{
    key_status &= ~0x01;
  }
  if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 0){
    key_status |= 0x02;
  }
  else{
    key_status &= ~0x02;
  }
  return key_status;
}