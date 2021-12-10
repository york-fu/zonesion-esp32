/*********************************************************************************************
* 文件：relay.c
* 作者：Lixm 2017.10.17
* 说明：继电器驱动代码
* 修改：
* 注释：
*********************************************************************************************/

/*********************************************************************************************
* 头文件
*********************************************************************************************/
#include "relay.h"

/*********************************************************************************************
* 名称：relay_init()
* 功能：继电器传感器初始化
* 参数：无
* 返回：无
* 修改：
* 注释：
*********************************************************************************************/
void relay_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5 | GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
  
  relay_control(0x00);
}

/*********************************************************************************************
* 名称：relay_control()
* 功能：继电器传感器控制函数
* 参数：无
* 返回：无
* 修改：
* 注释：
*********************************************************************************************/
void relay_control(unsigned char cmd)
{
  if(cmd & 0x01){
    GPIO_ResetBits(GPIOA,  GPIO_Pin_5);
  }
  else{
    GPIO_SetBits(GPIOA,  GPIO_Pin_5);
  }
  if(cmd & 0x02){
    GPIO_ResetBits(GPIOA,  GPIO_Pin_4);
  }
  else{
    GPIO_SetBits(GPIOA,  GPIO_Pin_4);
  }
}
