/*********************************************************************************************
* 文件：zxbee.c
* 作者：xuzhy 
* 说明：
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
#include "zxbee-inf.h"

static char wbuf[128];

void on_command_begin();
void on_command_end();
/*********************************************************************************************
* 名称：ZXBeeBegin
* 功能：ZXBee指令合成开始
* 参数：
* 返回：
* 修改：
* 注释：
*********************************************************************************************/
void ZXBeeBegin(void)
{
  wbuf[0] = '{';
  wbuf[1] = '\0';
}
/*********************************************************************************************
* 名称：ZXBeeAdd
* 功能：添加一条数据到zxbee指令
* 参数：tag：传感器标识
        val：传感器值
* 返回：
* 修改：
* 注释：
*********************************************************************************************/
int ZXBeeAdd(char* tag, char* val)
{
  int offset = strlen(wbuf);
  sprintf(&wbuf[offset],"%s=%s,", tag, val);
  return 0;
}
/*********************************************************************************************
* 名称：ZXBeeEnd
* 功能：zxbee指令添加结束
* 参数：
* 返回：
* 修改：
* 注释：
*********************************************************************************************/
char* ZXBeeEnd(void)
{
  int offset = strlen(wbuf);
  wbuf[offset-1] = '}';
  wbuf[offset] = '\0';
  if (offset > 2) return wbuf;
  return NULL;
}

/*********************************************************************************************
* 名称：ZXBeeDecodePackage
* 功能：zxbee指令解析
* 参数：
* 返回：
* 修改：
* 注释：
*********************************************************************************************/
char* ZXBeeDecodePackage(char *pkg, int len)
{
   char *p;
  char *ptag = NULL;
  char *pval = NULL;

  if (pkg[0] != '{' || pkg[len-1] != '}') return NULL;
  
  ZXBeeBegin();
  on_command_begin();           //为支持拨打电话和发送短信而增加zxbee接口
  pkg[len-1] = 0;
  p = pkg+1;
  do {
    ptag = p;
    p = strchr(p, '=');
    if (p != NULL) {
      *p++ = 0;
      pval = p;
      p = strchr(p, ',');
      if (p != NULL) *p++ = 0;
      int ret;
      ret = ZXBeeSysCommandProc(ptag, pval);
      if (ret < 0) {
        ret = ZXBeeUserProcess(ptag, pval);
      }
    }
  } while (p != NULL);
  on_command_begin();
  p = ZXBeeEnd();

  return p;
}
