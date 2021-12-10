#include "soil.h"
#include "usart.h"

char readDataBuf[8] = {0xfa,0x03,0x00,0x00,0x00,0x02,0xd1,0x80};// 读取土壤温湿度传感器数据指令
char setZoomFactor[8] = {0xfa,0x06,0x0a,0x00,0x27,0x10,0x85,0xa5};//设置缩放系数：1
float soilHumi = 0;
float soilTemp = 0;

/*********************************************************************************************
* 名称：uart2_set_input_call()
* 功能：设置串口2回调函数
* 参数：无
* 返回：无
* 修改：
* 注释：
*********************************************************************************************/
void uart2_set_input_call(int (*c)(char ch))
{
  uart2_set_input(c);
}

/*********************************************************************************************
* 名称：uart2_send_data()
* 功能：串口2发送数据
* 参数：buf-需要发送的数据/len-数据长度
* 返回：无
* 修改：
* 注释：
*********************************************************************************************/
void uart2_send_data(char* buf, unsigned int len)
{
  for(unsigned int i=0; i<len; i++)
    uart2_putc(buf[i]);
}

float get_soilHumi(void)
{
  return soilHumi;
}

float get_soilTemp(void)
{
  return soilTemp;
}

/*********************************************************************************************
* 名称：soil_init()
* 功能：空气质量传感器初始化
* 参数：无
* 返回：无
* 修改：
* 注释：
*********************************************************************************************/
void soil_init(void)
{
  uart2_init(9600);
  uart2_set_input_call(uart2_rec_handle);
  uart2_send_data(setZoomFactor, sizeof(setZoomFactor));
}

void read_soil(void)
{
  uart2_send_data(readDataBuf, sizeof(readDataBuf));
}

/*********************************************************************************************
* 名称：uart2_rec_handle()
* 功能：串口2回调函数
* 参数：ch-串口接收的数据
* 返回：无
* 修改：
* 注释：
*********************************************************************************************/
int uart2_rec_handle(char ch)
{
#define BUFSIZE 128
  static unsigned int recLen = 0;
  static char recBuf[BUFSIZE];
  static unsigned char flag = 0;
  if(flag == 1)
  {
    recBuf[recLen++] = ch;
    if(recLen >= 7)
    {
      soilHumi = (recBuf[3]*256 + recBuf[4]) * 0.1;         // 计算出土壤水分值
      soilTemp = (recBuf[5]*256 + recBuf[6]) * 0.1;         // 计算出土壤温度值
      recLen = 0;
      flag = 0;
    }
  }
  else
  {
    recBuf[0] = recBuf[1];
    recBuf[1] = recBuf[2];
    recBuf[2] = ch;
    if((recBuf[0] == 0x01) && (recBuf[1] == 0x03)&&(recBuf[2] == 0x04))
    {
      recLen = 3;
      flag = 1;
    }
  }
  return 1;
}




