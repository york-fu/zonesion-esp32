#ifndef __ZXBEE_INF_H__
#define __ZXBEE_INF_H__

void ZXBeeInfInit(void);
void  ZXBeeInfSend(char *p, int len);
void ZXBeeInfRecv(char *pkg, int len);
#endif
