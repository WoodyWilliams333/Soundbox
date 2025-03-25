#ifndef _EASYXML_H
#define _EASYXML_H

int NewXmlInit(char* data,int datalen);
void NewXmlRealse(void);
void NewXmldata(char* innodespace,char* nodename,char* nodevalue,int valueinlen);
void getXMLData(char* outdata, int* outlen);

int getXMLValuefromnode(char* innodespace, const char* searchnode, char* outbuf,int innodespacelen,int* searchnodelen);

#endif


