#ifndef _CODES_TOOL_H_
#define _CODES_TOOL_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	unsigned int itemLen;
	char *items_value;
}proto_Items;

/**
* @brief        日期结构体对象
*/
typedef struct {
    uint16_t year;
    uint16_t month;
    uint16_t day;
    uint16_t hour;
    uint16_t min;
    uint16_t sec;
}date_time_t;



//从末尾获取字符串中的金额字符串
int GetTtsStrAudioAmt(char* srcStr,char* AmtStr,char *audioStr);

int strSplit(const char *psrc,int psrc_len,char sign,proto_Items **proto_Item,int pdest_Num);

void free_SplitSpace(proto_Items **proto_Item,int pdest_Num);


char* strRepl(char *srcStr,const char *str1,const char *str2);

//删除字符串中所有该字符
char * deleteSubString(char * srcString, const char * subString);

//只删除一次就退出
char * deleteSubString_1(char * srcString, const char * subString);

//从文件中读取出二进制流数据 encry_flag->是否解密读取
int get_datastream_from_file(const char *audio_fullpath,char **dstaudio_data,uint8_t encry_flag);


//保存内存数据到文件中 encry_flag->是否追加保存
int write_datastream_to_file(const char *audio_fullpath,uint8_t *dstaudio_data,uint32_t datalen,uint8_t append_flag);


void np_hex_to_string(uint8_t const *data, uint16_t length, char *hexString);


//字符串转16进制
void np_Str_To_Hex(unsigned char *pbDest, unsigned char *pbSrc, int nLen);



void np_upper(char *s);

void np_lower(char *s);

char char_upper(char s);

char char_lower(char s);


uint32_t np_hex2long(uint8_t *psHex, int iHexLen);


uint32_t fml_stamp_to_time( uint32_t timep, date_time_t *date,uint8_t CN_flag);


//解析URL链接获取数据
int deal_url(char *url,char*path,char*host,int *port,int dns_with_port_flag);


//获取纯单词和数字版本号用于播报(//AWS01.07.56_APP >> version|1|7|56   V1.00.01 >> version|1|0|1 )
int get_voice_version(char *srcVersion,char *databuf);


//原文件拷贝到新文件
int file_copy_to_newpath(char* srcpath,char* dstpath);


void get_yyyy_MM_dd_HH_mm_ss_ms_time_ex(char *indata,int size,char*date_str,int data_size);



#ifdef __cplusplus
}
#endif

#endif 

