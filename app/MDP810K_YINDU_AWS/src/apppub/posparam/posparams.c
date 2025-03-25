#include <stdio.h>
#include <string.h>

#include "basicext.h"
#include "libapiext.h"
#include "appbasicext.h"

#include "terfilecomm.h"
#include "posparams.h"
/*

static const char gszParamFileName[] = "appparam.txt";
static char gszTpdu[10+1];
static char gucCommType;

static const PARAMS Params[]=
{
	{"商户号",		STR_PARAMS(stTransPara.szUnitNum),	  STRING_ITEM},	
	{"终端号",		STR_PARAMS(stTransPara.szPosId),	      STRING_ITEM},
	{"商户名称",    STR_PARAMS(stTransPara.szUnitChnName), STRING_ITEM},
	{"POS初始流水号",	LONG_PARAMS(stTransCtrl.lNowTraceNo),  BIN_ITEM},
	{"POS初始批次号",	LONG_PARAMS(stTransCtrl.lNowBatchNum), BIN_ITEM},
	{"参数设置密码", 	STR_PARAMS(stSysPara.szParamsPwd),	STRING_ITEM},
	{"安全设置密码", 	STR_PARAMS(stSysPara.szSafepwd),	STRING_ITEM},
	{"交易重发次数",    INT_PARAMS(stSysPara.iResendTime), BIN_ITEM},
	{"TPDU",		STR_PARAMS(gszTpdu),	STRING_ITEM},
	{"通讯最长等待时间", 	CHAR_PARAMS(stCommPara.ucCommWaitTime), BIN_ITEM},
	{"服务器远端IP地址一",	STR_PARAMS(stCommPara.stHost[0].szHostIP),	STRING_ITEM},
	{"服务器端口号一", 	STR_PARAMS(stCommPara.stHost[0].szHostPort),	    STRING_ITEM},
	{"服务器远端IP地址二",	STR_PARAMS(stCommPara.stHost[1].szHostIP),	STRING_ITEM},
	{"服务器端口号二", 	STR_PARAMS(stCommPara.stHost[1].szHostPort),	STRING_ITEM},
	{"通讯方式", 	    CHAR_PARAMS(gucCommType), ASSCII_ITEM},
	{"是否支持扫码预授权", 	CHAR_PARAMS(stSysPara.swSupScanPreauth), ASSCII_ITEM},
	{"押金金额",		STR_PARAMS(stTransPara.ucDepositAmt),STRING_ITEM},
	{"product_key",		STR_PARAMS(stSysPara.product_key),STRING_ITEM},
	{"device_secret",		STR_PARAMS(stSysPara.device_secret),STRING_ITEM},
	{"device_name",		STR_PARAMS(stSysPara.device_name),STRING_ITEM},
	{"*****************", NULL, 0,							0}
};

static void str_convert(uint8_t *dest, uint8_t *srcStr, uint8_t len)
{
	memset(dest, 0x00, len);
	if( strlen((char *)srcStr)<len )
	{
		strcpy((char *)dest, (char *)srcStr);
	}
	else
	{
		memcpy((char *)dest, (char *)srcStr, len-1);
	}
}

static void ascii_convert(uint8_t *dest, uint8_t *srcStr, uint8_t len)
{
	memset(dest, 0x00, len);
	memcpy(dest, srcStr, len);
}
*/

#if 0
static void bcd_convert(uint8_t *dest, uint8_t *srcStr, uint8_t len)
{
	memset(dest, 0x00, len);
	pub_asc2bcd((char *)srcStr, strlen((char *)srcStr), dest);
}
#endif


static uint8_t char_to_bin(uint8_t bchar)
{
	
	if( (bchar>='0')&&(bchar<='9') )
	{
		return(bchar-'0');
	}
	else if( (bchar>='A')&&(bchar<='F') )
	{
		return(bchar-'A'+10);
	}
	else if( (bchar>='a')&&(bchar<='f') )
	{
		return(bchar-'a'+10);
	}
	else
	{
		return 0;
	}
}

char hex_convert(uint8_t *dest, uint8_t *srcStr, uint8_t len)
{
	uint8_t buff[5];
	uint8_t i, k, *ptr, bin[2], achar;
	uint8_t srclen;

	srclen = strlen((char *)srcStr);
	if( srclen==0 )
	{
		memset(dest, 0x00, len);
		return 0;
	}
	ptr = srcStr;
	for(i=0; (i<len)&&(ptr<srcStr+srclen); )
	{
		memset(buff, 0x00, 5);
		for(k=0; (k<4)&&(ptr<srcStr+srclen); ptr++)
		{
			if( (*ptr!=',') && (*ptr!=' ') )
			{
				buff[k++] = *ptr;
			}
		}
		if( strlen((char *)buff)!=4 )
		{
			continue;
		}
		if( memcmp(buff, "0x", 2) )
		{
			continue;
		}
		bin[0] = char_to_bin(buff[2]);
		bin[0] = bin[0]<< 4;
		bin[1] = char_to_bin(buff[3]);
		achar = bin[0] + bin[1];
		dest[i++] = achar;
	}
	return 0;
}

void bin_convert(uint8_t *dest, uint8_t *srcStr, uint8_t len)
{
	uint8_t  achar;
	int16_t  i;
	int  l;

	switch(len)
	{
	case sizeof(achar):
		achar = (uint8_t)atoi((char *)srcStr);
		*dest = achar;
		break;
	case sizeof(i):
		i = atoi((char *)srcStr); 
		memcpy(dest, (uint8_t *)&i, len); 
		break;
	case sizeof(l):
		l = atol((char *)srcStr);
		memcpy(dest, (uint8_t *)&l, len);
		break;
	default:
		break;
	}
}

#if 0

static void AllTrim(uint8_t *str)
{
	int len, count;
	uint8_t *p_str;

	len = strlen((char *)str);
	if (0 == len) return;

	p_str = str;
	p_str += len-1;
	while( (*p_str==' ')||(*p_str==0x09)||(*p_str==0x0d)||(*p_str==0x0a) )
	{	
		*p_str = 0x00;
		if(p_str == str)
		{
			break;
		}
		else
		{
			--p_str;
		}
	}
	p_str = str;
	len = strlen((char *)str);
	count = 0;
	while( (*p_str==' ')||(*p_str==0x09)||(*p_str==0x0d)||(*p_str==0x0a) )
	{
		if( p_str<(str+len) )
		{
			p_str++;
			count++;
		}
		else
		{
			break;
		}
	}
	if( count>0 )
	{
		memmove(str, p_str, len-count);
		memset(str+(len-count), 0x00, count);
	}
}


static int read_cnt;
static int readline(int fd, void *vptr, int maxlen)
{
	int n;
	uint8_t c, *ptr;
	static uint8_t *read_ptr, read_buf[400];

	ptr = vptr;
	for(n=1; n<maxlen; n++)
	{
		if( read_cnt<=0 )
		{
			if( (read_cnt=app_file_read(fd, read_buf, sizeof(read_buf)))<0 )
			{
				return -1;
			} 
			else if( read_cnt==0 )
			{
				return 0;
			}
			read_ptr = read_buf;
		}
		read_cnt--;
		c = *read_ptr++;
	
		*ptr++ = c;
		if( c==0x0a )
		{
			break;
		}
	}
	*ptr = 0x00;
	return (n);
}



static int NextParam(int fid, uint8_t *name, uint8_t *value)
{
	uint8_t aline[200+1];
	uint8_t *ptr;
	int ret;

	memset(aline, 0x00, sizeof(aline));
	ret = readline(fid, aline, sizeof(aline)-1);
	if( ret<=0 )
	{
		return -1;
	}
	if( aline[0]=='&' )
	{
		return -1;
	}

	ptr = memchr(aline, '#', strlen((char *)aline));
	if ( ptr!=NULL )
	{
		if( aline[0]=='#')
    	{
   			*ptr = 0x00;
    	}
	}
	
	AllTrim(aline);
	ptr = memchr(aline, '=', strlen((char *)aline));
	if( ptr==NULL )
	{
		return 1;
	}

	memcpy(name, aline, ptr-aline);
	strcpy((char *)value, (char *)(ptr+1));
	AllTrim(name);
	AllTrim(value);
	return 0;	
}


static int GetParams(char *filename, PARAMS *myParams)
{
	int i, j;
	PARAMS *q;
	uint8_t name[80], value[80];
	int ParamsFid;	

	ParamsFid = app_file_open(filename, O_RDWR);
	if( ParamsFid<0 )
	{
		disp_win_msg_mul_lan("文件打开错误", NULL, "Open File Fail", NULL,MSG_FAILED, RESULT_DISP_TIME);
		return 1;
	}
	read_cnt = 0;//very important.

	for(;;)
	{
		memset(name, 0x00, sizeof(name));
		memset(value, 0x00, sizeof(value));
		j = NextParam(ParamsFid, name, value);
		if( j<0 )
		{
			break;
		}
		if( j>0 )
		{
			continue;
		}
		if( value[0]==0x0a )
		{
			continue;
		}
		for(i=0, q=myParams; ;i++, q++)
		{
			if( q->name[0]=='*' )
			{
				break;
			}
			if( strcmp((char *)name, (char *)q->name) )
			{
				continue;
			}

			switch(q->type)
			{
			case STRING_ITEM:	
				str_convert((uint8_t *)q->ini_ptr, value, q->len);
				break;
			case ASSCII_ITEM:
				ascii_convert((uint8_t *)q->ini_ptr, value, q->len);
				break;
			case HEX_ITEM:
				hex_convert((uint8_t *)q->ini_ptr, value, q->len);
				break;
			case BIN_ITEM:	
				bin_convert((uint8_t *)q->ini_ptr, value, q->len);
				break;
			default:
				break;
			}
			break;
		}
	}
	app_file_close(ParamsFid);
	return 0;
}

// 注意: 这个函数建议只用在读取参数文件并保存到系统参数结构中的后面
static void  AdjustAppParam(void)
{
	if (stSysPara.ucOprtLimitTime < 5)
	{
		stSysPara.ucOprtLimitTime = 5;
	}

	if (strlen(gszTpdu)) {
		pub_asc2bcd(gszTpdu, MIN(10, strlen(gszTpdu)), stCommPara.ucTpdu); 
	}
		
	switch (gucCommType)
	{
	case 'G':
	case 'g':
		stCommPara.commType = CT_GPRS;
		break;

	case 'C':
	case 'c':
		stCommPara.commType = CT_CDMA;
		break;
	
	case 'w':
	case 'W':
		stCommPara.commType = CT_WIFI;
		break;
	
	default:
		break;
	}

	return ;
}


static int  ReadParamsFile(void)
{
	int  ret;

	memset(gszTpdu, 0, sizeof(gszTpdu));
	gucCommType = 0;
	
	ret = GetParams((char *)gszParamFileName, (PARAMS *)Params);
	if( ret!=0 ){
		return ret;
	}
	
	return 0;
}


static int TxtToEnv(void)
{
	int iRet;
	
	if( app_file_exists(gszParamFileName)<0 )
	{
		return 0;
	}
	
	iRet = ReadParamsFile();
	if( iRet!=0 )
	{
		disp_win_msg_mul_lan("读取参数文件失败", NULL,"Read Param File Fail", NULL, MSG_FAILED, RESULT_DISP_TIME);		
		return 1;
	}

	logger_debug("+++product_key:%s\n",stSysPara.product_key);
	logger_debug("+++device_secret:%s\n",stSysPara.device_secret);
	logger_debug("+++device_name:%s\n",stSysPara.device_name);
	
	AdjustAppParam();
	SaveTransPara();
	SaveCommunicationPara();
	SaveCtrlPara();
	SaveSysPara();

	disp_win_msg_mul_lan("读取参数成功!", NULL,"Read Param Success!", NULL, MSG_SUCC, RESULT_DISP_TIME);

	return 0;	
}

uint8_t loadPosExtAppFile(void)
{
	uint8_t ucRet = 0;
	
	if (app_file_exists(gszParamFileName) >= 0){	
		TxtToEnv();
		app_file_remove(gszParamFileName);

		//defaut no auto power off when bootup
		stSysPara.swAutoPowerOff=para_off;
		SaveSysPara();
	}
	
	return ucRet;
}
#endif
//end of line

