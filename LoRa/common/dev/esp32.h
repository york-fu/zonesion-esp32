#ifndef __esp32_H__
#define __esp32_H__


int _request_at_3(char *at, unsigned int to, void (*fun)(char*));
int esp32_SendData(char *dat,int len);

#endif
