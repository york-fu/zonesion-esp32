/*********************************************************************************************
* 文件：sensor.h
* 作者：Xuzhy 2018.5.16
* 说明：sensor头文件
* 修改：
* 注释：
*********************************************************************************************/
#ifndef __SENSOR_H__
#define __SENSOR_H__
/*********************************************************************************************
* 宏定义
*********************************************************************************************/
#define NODE_NAME "601"
extern void sensorInit(void);
extern void sensorLinkOn(void);
extern void sensorUpdate(void);
extern void sensorCheck(void);
extern void sensorControl(uint8_t cmd);
#endif
