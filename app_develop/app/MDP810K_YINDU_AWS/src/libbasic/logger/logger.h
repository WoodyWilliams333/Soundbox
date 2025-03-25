
#ifndef __LOGGER_H__
#define __LOGGER_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum 
{
    LOGGER_LEVEL_FATAL              = 1,    /* 严重错误，系统已不可食用，此时只能重启修复 */         
    LOGGER_LEVEL_ERROR              = 2,    /* 错误，系统出现了非预期的错误执行结果，直接影响程序逻辑无法往下执行 */
    LOGGER_LEVEL_WARN               = 3,    /* 警告，系统可能出现异常，进行修复后，系统可恢复到正常状态 */
    LOGGER_LEVEL_INFO               = 4,    /* 信息，反馈系统的当前状态，输出给最终用户查看 */
    LOGGER_LEVEL_DEBUG              = 5,    /* 调试，任何觉得有利于在调试时更详细的了解系统运行状态的输出 */
} logger_level_e;

/* 配置日志输出的格式，有以下信息可选: 时间戳、日志级别编号、模块名称、文件名、行号 */
/* config example 1: LOGGER_LEVEL_DEBUG | LOGGER_TIMESTAMP_ON | LOGGER_LEVEL_ON | LOGGER_MODULE_ON | LOGGER_FILE_ON | LOGGER_LINE_ON */
/* config example 2: LOGGER_ALL_ON */
#define LOGGER_LEVEL_VALUE          0x0000000F
#define LOGGER_TIMESTAMP            0x000000F0      /* timestamp on */
#define LOGGER_LEVEL                0x00000F00      /* logger level msg on */
#define LOGGER_MODULE               0x0000F000      /* module name on */
#define LOGGER_FILE                 0x000F0000      /* file name on */
#define LOGGER_LINE                 0x00F00000      /* line on */
#define LOGGER_OFF                  0x0F000000      /* logger off */
#define LOGGER_ALL_ON               (0x00FFFFF0 | LOGGER_LEVEL_DEBUG) // LOGGER_LEVEL_WARN

#if defined(CFG_LOGGER_ON)

#include "stdio.h"

/* 
每个include logger.h的.c文件，通过自定义LOGGER_CFG和LOGGER_MODULE_NAME
可以实现每个.c有不同的日志级别，以及不同的模块名称
*/

#define LOGGER_DEF_CFG              LOGGER_ALL_ON //LOGGER_OFF
#ifndef LOGGER_CFG
#define LOGGER_CFG                  LOGGER_DEF_CFG
#endif

#define LOGGER_DEF_MODULE_NAME      "xxx"
#ifndef LOGGER_MODULE_NAME
#define LOGGER_MODULE_NAME          LOGGER_DEF_MODULE_NAME
#endif

extern int logger_level_printf( int         logger_level, 
                                   int         logger_cfg, 
                                   const char *module, 
                                   const char *file, 
                                   int         line, 
                                   const char *fmt, ...);

#define _logger_level_printf(level_in, fmt, arg...)\
    logger_level_printf(level_in, LOGGER_CFG, LOGGER_MODULE_NAME, __FILE__, __LINE__, fmt, ##arg) 

extern void logger_level_hexdump( int         logger_level, 
                                        int         logger_cfg, 
                                        const char *module, 
                                        const char *file, 
                                        int         line, 
                                        const char *title,
                                        const void *data, 
                                        unsigned int len);

#define _logger_level_hexdump(level_in, title, data, len)\
    logger_level_hexdump(level_in, LOGGER_CFG, LOGGER_MODULE_NAME, __FILE__, __LINE__, title, data, len)

typedef struct {
    const char *name;   /* uart or fs-file like "/home/userx/file.log" */
    int (*open)(const char *filename);
    int (*write)(int fd, const void *buf, int count);
    int (*read)(int fd, void *buf, int count);
    int (*close)(int fd);
} LoggerOps_t;

#define logger_register(type) \
        static const LoggerOps_t logger_##type##_ops __attribute_used__ \
        __attribute__((section(".app.logger.init"))) = \
        {\
            STRUCT_MEMBER(name,     #type".log"),\
            STRUCT_MEMBER(open,     type##_log_open),\
            STRUCT_MEMBER(write,    type##_log_write),\
            STRUCT_MEMBER(read,     type##_log_read),\
            STRUCT_MEMBER(close,    type##_log_close),\
        };

#if defined(__GNUC__)
#define APP_LOGGER_INIT_START       __start_app_logger_init
#define APP_LOGGER_INIT_END         __stop_app_logger_init
#else
#define APP_LOGGER_INIT_START       Image$$APPLOGGERINIT$$Base
#define APP_LOGGER_INIT_END         Image$$APPLOGGERINIT$$Limit
#endif

extern const LoggerOps_t APP_LOGGER_INIT_START[], APP_LOGGER_INIT_END[];

#define TO_STRING(x)                #x
#define _LOGGER_CHANNEL(x)          TO_STRING(x) 
#define LOGGER_CHANNEL              _LOGGER_CHANNEL(CFG_LOGGER_CHANNEL)

#define LOGGER_PRINT_COLOR_ENABLE   1   // 使能logger打印彩色标记  

#if defined(LOGGER_PRINT_COLOR_ENABLE)
//以下颜色定义是针对标准的控制终端(白底黑字)来设定的，如果输出的控制终端设置过，可能呈现的颜色并不是这里设置的颜色
#define RED         "\033[0;32;31m"     // 红色，此颜色在有些控制终端打不出来
#define YELLOW      "\033[1;33m"        // 黄色
#define CLOSE       "\033[0m"           // 关闭所有属性

#define logger_fatal(fmt, arg...)                   _logger_level_printf(LOGGER_LEVEL_FATAL, YELLOW fmt CLOSE, ##arg) 
#define logger_error(fmt, arg...)                   _logger_level_printf(LOGGER_LEVEL_ERROR, YELLOW fmt CLOSE, ##arg)

#else

#define logger_fatal(fmt, arg...)                   _logger_level_printf(LOGGER_LEVEL_FATAL, fmt, ##arg)         
#define logger_error(fmt, arg...)                   _logger_level_printf(LOGGER_LEVEL_ERROR, fmt, ##arg) 

#endif

#define logger_warn(fmt, arg...)                    _logger_level_printf(LOGGER_LEVEL_WARN, fmt, ##arg) 
#define logger_info(fmt, arg...)                    _logger_level_printf(LOGGER_LEVEL_INFO, fmt, ##arg) 
#define logger_debug(fmt, arg...)                   _logger_level_printf(LOGGER_LEVEL_DEBUG, fmt, ##arg) 
#define logger_hexdump(title, data, len)            _logger_level_hexdump(LOGGER_LEVEL_DEBUG, title, data, len)

#else

#define logger_fatal(fmt, arg...)                   do {} while(0)
#define logger_error(fmt, arg...)                   do {} while(0)
#define logger_warn(fmt, arg...)                    do {} while(0)
#define logger_info(fmt, arg...)                    do {} while(0)
#define logger_debug(fmt, arg...)                   do {} while(0)
#define logger_hexdump(title, data, len)            do {} while(0)

#endif



enum {
	DBG_ERR		=1,	/* error conditions					*/
	DBG_NOTICE	=2,	/* normal but significant condition	*/
	DBG_INFO	=3,	/* informational					*/
	DBG_DEBUG	=4,	/* debug-level messages				*/
	DBG_API		=5,	/* show api enter and exit message  */
};

#define ums_debug(level, fmt, arg...)	do { } while (0)
#define ums_api_enter(fmt, arg...)		do { } while (0)//logger_info(fmt, ##arg)
#define ums_api_exit(fmt, arg...)		do { } while (0)//logger_info(fmt, ##arg)


#ifdef __cplusplus
}
#endif

#endif
