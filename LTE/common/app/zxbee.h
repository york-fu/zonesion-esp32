#ifndef __ZXBEE_H__
#define __ZXBEE_H__

void ZXBeeBegin(void);
int ZXBeeAdd(char* tag, char* val);
char* ZXBeeEnd(void);

char* ZXBeeDecodePackage(char *pkg, int len);
int ZXBeeSysCommandProc(char* ptag, char* pval);
int ZXBeeUserProcess(char* ptag, char* pval);
#endif