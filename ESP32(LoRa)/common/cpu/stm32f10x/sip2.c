#include "stm32f10x.h" 
	 
//以下是SPI模块的初始化代码，配置成主机模式 						  
/*********************************************************************************************
* 名称：SPI2_Init
* 功能：SPI2初始化
* 参数：
* 返回：
* 修改：
* 注释：
*********************************************************************************************/
void SPI2_Init(void)
{	 
  GPIO_InitTypeDef  GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能GPIOB时钟
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);//使能SPI2时钟
 
 /* Configure SPIy pins: SCK, MISO and MOSI ---------------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  /* Configure SCK and MOSI pins as Alternate Function Push Pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
 
  /* Configure MISO pin as Input Floating  */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  

  
  //这里只针对SPI口初始化
  //RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2,ENABLE);//复位SPI2
  //RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2,DISABLE);//停止复位SPI2

  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; //SPI_CPOL_High;		//串行同步时钟的空闲状态为高电平
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;//SPI_CPHA_2Edge;	//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;		//定义波特率预分频的值:波特率预分频值为8
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
  SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
  SPI_Init(SPI2, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
  SPI_Cmd(SPI2, ENABLE); //使能SPI外设

  //SPI2_ReadWriteByte(0xff);//启动传输		 
}   

/*********************************************************************************************
* 名称：SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
* 功能：SPI2速度设置函数
* 参数：SPI_BaudRatePrescaler
* 返回：
* 修改：
* 注释：SPI速度=fAPB2/分频系数
	SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256  
	fAPB2时钟一般为84Mhz
*********************************************************************************************/
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//判断有效性
	SPI2->CR1&=0XFFC7;//位3-5清零，用来设置波特率
	SPI2->CR1|=SPI_BaudRatePrescaler;	//设置SPI1速度 
	SPI_Cmd(SPI2,ENABLE); //使能SPI1
} 

/*********************************************************************************************
* 名称：SPI2_ReadWriteByte(u8 TxData)
* 功能：SPI2 读写一个字节
* 参数：TxData:要写入的字节
* 返回：读取到的字节
* 修改：
* 注释：
*********************************************************************************************/
u8 SPI2_ReadWriteByte(u8 TxData)
{		 			 
 
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET){}//等待发送区空  
	
	SPI_I2S_SendData(SPI2, TxData); //通过外设SPIx发送一个byte  数据
		
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET){} //等待接收完一个byte  
 
	return SPI_I2S_ReceiveData(SPI2); //返回通过SPIx最近接收的数据	
 		    
}
