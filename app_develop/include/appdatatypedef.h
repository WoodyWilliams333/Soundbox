

#ifndef _APP_DATA_TYPE_DEF_H_
#define _APP_DATA_TYPE_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif


/**<常用数据类型定义*/
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
}appbool;

typedef enum{
	para_on 	= '1',
	para_off 	= '0',
}appsw;


typedef enum{
	APP_ZH = 0,
	APP_EN 
}E_APP_LANGUAGE;

typedef struct _POINT {
    uint32_t x;
    uint32_t y;
}APPPOINT, *PAPPPOINT;


#ifdef __cplusplus
}
#endif

#endif
