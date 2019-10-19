#include "stm32f10x.h"

static unsigned char led_status = 0;
void leds_arch_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13 | GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  
  GPIO_Init(GPIOB, &GPIO_InitStructure);  
  GPIO_SetBits(GPIOB,  GPIO_Pin_13 | GPIO_Pin_14);

} 
unsigned char leds_arch_get(void)
{
  return led_status;
}
void leds_arch_set(unsigned char leds)
{
  unsigned int pin_on = 0;
  unsigned int pin_off = 0;
  led_status = leds;
  if (leds & 0x01) pin_on |= GPIO_Pin_14;
  else pin_off |= GPIO_Pin_14;
  if (leds & 0x02) pin_on |= GPIO_Pin_13;
  else pin_off |= GPIO_Pin_13;
  //if (leds & 0x04) pin_on |= GPIO_Pin_5;
  //else pin_off |= GPIO_Pin_5;
  //if (leds & 0x08) pin_on |= GPIO_Pin_6;
  //else pin_off |= GPIO_Pin_6;
  GPIO_ResetBits(GPIOB, pin_on); //on
  GPIO_SetBits(GPIOB, pin_off); //off
  /*
  pin_on = pin_off = 0;
  if (leds & 0x04) pin_on |= GPIO_Pin_0;
  else pin_off |= GPIO_Pin_0;
  if (leds & 0x08) pin_on |= GPIO_Pin_1;
  else pin_off |= GPIO_Pin_1;
  if (leds & 0x10) pin_on |= GPIO_Pin_2;
  else pin_off |= GPIO_Pin_2;  
  GPIO_ResetBits(GPIOB, pin_on); //on
  GPIO_SetBits(GPIOB, pin_off); //off  
  */
}