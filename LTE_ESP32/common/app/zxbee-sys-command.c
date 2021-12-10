/*********************************************************************************************
* 文件：zxbee-sys-command.c
* 作者：xuzhy 2018.1.12
* 说明：lte 模块公共zxbee指令处理模块
*       
*       
*       
* 修改：
* 注释：
*********************************************************************************************/
#include "contiki.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stimer.h>
#include "zxbee.h"
#include "gsm.h"
#include "usart.h"
#include "sensor.h"

static int action = 0; //
static char phone[16];
static char msg[128];

/*********************************************************************************************
* 名称：on_command_begin
* 功能：zxbee指令处理开始调用，为了支持lte模板拨打电话和发送短信功能而增加
* 参数：
* 返回：
* 修改：
* 注释：
*********************************************************************************************/
void on_command_begin()
{
  action = 0;
}
/*********************************************************************************************
* 名称：on_command_end
* 功能：zxbee指令处理完毕调用，为了支持lte模板拨打电话和发送短信功能而增加
* 参数：
* 返回：
* 修改：
* 注释：
*********************************************************************************************/
void on_command_end()
{
  if (action == 1) {
    /*拨打电话*/
    gsm_request_call(phone);
  }
  if (action == 2) {
    gsm_send_message(phone, msg);
  }
}
/*********************************************************************************************
* 名称：zxbee_sys_process_command_call
* 功能：lte模块公共zxbee指令处理
* 参数：
* 返回：
* 修改：
* 注释：
*********************************************************************************************/
int ZXBeeSysCommandProc(char* ptag, char* pval)
{
  int ret = -1;
  if (memcmp(ptag, "ECHO", 4) == 0) {
    ZXBeeAdd(ptag, pval);
    return 1;
  }
  if (memcmp(ptag, "TYPE", 4) == 0) {
    if (pval[0] == '?') {
 
      int radio_type = CONFIG_RADIO_TYPE; //lora
      int dev_type = CONFIG_DEV_TYPE; //lora ed
      char buf[16];
      ret = sprintf(buf, "%d%d%s", radio_type, dev_type, NODE_NAME);
      ZXBeeAdd("TYPE", buf);
      return 1;
    }
  }
  
  if (memcmp(ptag, "Action", 6) == 0) {
    if (memcmp(pval, "Tel", 3) == 0) {
      action = 1;
    }
    if (memcmp(pval, "SendSMS", 3) == 0) {
      action = 2;
    }
    return 1;
  }
  if (memcmp(ptag, "Number", 6) == 0) {
    strcpy(phone, pval);
    return 1;
  }
  if (memcmp(ptag, "Content", 7) == 0) {
    strcpy(msg, pval);
    return 1;
  }
  return ret;
}



