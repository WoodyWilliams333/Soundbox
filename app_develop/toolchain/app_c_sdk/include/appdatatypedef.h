/*
 * @Description: Ӧ�ò㳣���������Ͷ���
 * @Author: YangJing
 * @Date: 2020-04-03 09:04:00
 * @LastEditors: YangJing
 * @LastEditTime: 2020-04-08 11:18:30
 */


#ifndef _APP_DATA_TYPE_DEF_H_
#define _APP_DATA_TYPE_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif


/**<�����������Ͷ���>*/
#ifndef byte
typedef unsigned char    byte;
#endif
#ifndef cchar
typedef const char       cchar;
#endif
#ifndef uint
typedef unsigned int     uint;
#endif
#ifndef cint
typedef const int        cint;
#endif
#ifndef ushort
typedef unsigned short   ushort;
#endif
#ifndef ulong
typedef unsigned long    ulong;
#endif

typedef enum{
	app_false = 0,
	app_true = 1,

	app_off = 0,
	app_on = 1,

	app_no = 0,
	app_yes = 1,
}appbool;	//app��bool�����ݶ��壬ע�����ﶨ���bool������ö�٣�ռ�ڴ��СΪsizeof(int)!!!

typedef enum{
	para_on 	= '1',
	para_off 	= '0',
}appsw; //app��on/off���ض���


typedef struct _POINT {
    uint32_t x;
    uint32_t y;
}APPPOINT, *PAPPPOINT; //app��point���Ͷ���


#ifdef __cplusplus
}
#endif

#endif
