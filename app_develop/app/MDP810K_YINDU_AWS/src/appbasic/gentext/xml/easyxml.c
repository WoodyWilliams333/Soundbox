#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "easyxml.h"

static char *XMLDataNodeHead = NULL;
static int XMLDataLen;

/**************************************************
���ܲ������ƣ������ڼ򵥵�xml��ʽ������Ͳ��wdf
**************************************************/

//���ǰ�ĳ�ʼ��, ע������xmlҪ�����ͷŽӿ�
int NewXmlInit(char* data,int datalen)
{
	if(datalen <0){
		//disp_info_err("xml��ʼ��ʧ��", NULL, OVER_TIME);
		return -1;
	}

	if(XMLDataNodeHead == NULL){
		XMLDataNodeHead = malloc(1024*2);
		if(XMLDataNodeHead == NULL) {
			//disp_info_err("xml�����ڴ�ʧ��", NULL, OVER_TIME);
			return -1;
		}
	}

	memset(XMLDataNodeHead, 0x00, 1024*2);
	XMLDataLen = 0;
	if(datalen > 0)		
		memcpy(XMLDataNodeHead ,data,datalen);
	XMLDataLen = datalen;
	return 0;
}

/**
 * @describe: �ͷŽӿ�
 */
void NewXmlRealse(void)
{
	if(XMLDataNodeHead)
		free(XMLDataNodeHead);

	XMLDataNodeHead = NULL;
}

//����Ӧ��value����tag��
//innodespace	������ĸ���
//nodename		���������
//nodevalue		�������Ϣ
//valueinlen		������Ϣ�ĳ���
void NewXmldata(char* innodespace,char* nodename,char* nodevalue,int valueinlen)
{
	
	char tempbuf[512] = {0};
	int tempbuflen = 0;

//	int nodespacelenstart = 0;
	int nodespacelenend = 0;
	char nodespacebuf[32+1] = {0};
	char* nodespaceP = NULL;

	
	//�������xmlnodename �� nodevalue ���һ���ַ���,������tempbuf��,�ַ�������tempbuflen.
	snprintf(tempbuf, sizeof(tempbuf)-1, "<%s>", nodename);
	tempbuflen+=strlen(tempbuf);
	memcpy(tempbuf+tempbuflen,nodevalue,valueinlen);
	tempbuflen+= valueinlen;
	snprintf(tempbuf+tempbuflen, sizeof(tempbuf)-tempbuflen, "</%s>",nodename);
	tempbuflen+= strlen(nodename)+3;

	if(!innodespace){
		memcpy(XMLDataNodeHead,tempbuf,tempbuflen);
		XMLDataLen = tempbuflen;
	}else{
		snprintf(nodespacebuf, sizeof(nodespacebuf)-1, "<%s>", innodespace);
		nodespaceP = strstr(XMLDataNodeHead,nodespacebuf);
//		nodespacelenstart = nodespaceP-XMLDataNodeHead + strlen(nodespacebuf);//��ȡ����������������		<innodespace>nodespacelenstart.....

		snprintf(nodespacebuf, sizeof(nodespacebuf)-1, "</%s>",innodespace);
		nodespaceP = strstr(XMLDataNodeHead,nodespacebuf);
		nodespacelenend = nodespaceP-XMLDataNodeHead ;//��ȡ��������������յ�			...nodespacelenend</innodespace>

		memmove(nodespaceP+tempbuflen,nodespaceP,XMLDataLen-nodespacelenend);
		memcpy(nodespaceP,tempbuf,tempbuflen);
		XMLDataLen+=tempbuflen;
	}
//	showDebugMessage(XMLDataLen,XMLDataNodeHead,"�������<%s>-XMLDATA",nodename);
	return;
}

//��XML�������
void getXMLData(char* outdata, int* outlen)
{
	memcpy(outdata,XMLDataNodeHead,XMLDataLen);
	*outlen = XMLDataLen;
	return;
}

/*
innodespace	���ҵ���
searchnode	�����ҵ�node
outbuf		���value
innodespacelen����Ĳ����򳤶�
*searchnodelen	�����ҵ�node����,����
*/
int getXMLValuefromnode(char* innodespace, const char* searchnode, char* outbuf,int innodespacelen,int* searchnodelen)
{
//	char tempbuf[2048] = {0};
//	int tempbuflen = 0;
	
	int samenodenum = 0;
	char* tempPstart = NULL;
	char* tempPend = NULL;
	char* tempP = NULL;
	int templen = 0;

	char searchbufstart[32] = {0};
	char searchbufend[32] = {0};
	int searchbuflen = 0;

	snprintf(searchbufstart, sizeof(searchbufstart)-1, "<%s>",searchnode);
	snprintf(searchbufend, sizeof(searchbufend)-1, "</%s>",searchnode);
	searchbuflen = strlen(searchbufstart)-2;
	if(innodespace == NULL||innodespacelen <= 0){
		innodespace = NULL;
		innodespacelen = 0;
		tempPstart = strstr(XMLDataNodeHead,searchbufstart);
	}else{
		tempPstart = strstr(innodespace,searchbufstart);
	}

		
		if(tempPstart == NULL){
			return -1;
		}
		tempPend = strstr(tempPstart+1,searchbufend);
		templen = tempPend-tempPstart;
		if(templen+searchbuflen+3>innodespacelen&&innodespacelen!=0){
			return -1;
		}
		tempP = strstr(tempPstart+1,searchbufstart);
		if(tempP != NULL){
			while(1){
				if(tempPend - tempP < 0)
					break;
				samenodenum++;
				tempP = strstr(tempP+1,searchbufend);
			}			
		}
		if(samenodenum > 0){
			return -1;
		}
		
//		showDebugMessage(templen-searchbuflen-2, tempPstart+searchbuflen+2, "���ز��test--%s",searchnode);

	*searchnodelen = tempPend-tempPstart-searchbuflen-2;
	memcpy(outbuf,tempPstart+searchbuflen+2,*searchnodelen);
	*(outbuf+*searchnodelen) = 0x00;

	return 0;

}
