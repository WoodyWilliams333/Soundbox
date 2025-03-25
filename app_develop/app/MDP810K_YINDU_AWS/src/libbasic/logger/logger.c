
#include "init.h"

#define LOGGER_CFG          LOGGER_LEVEL_ERROR | LOGGER_TIMESTAMP | LOGGER_LEVEL | LOGGER_MODULE
#define LOGGER_MODULE_NAME  "logger"
#include "logger.h"

#if defined(CFG_LOGGER_ON)

#include <stdarg.h>
#include <string.h>
#include <system.h>

#include "errno.h"

static const LoggerOps_t *g_LoggerOps_t = NULL;

typedef struct 
{
    int level;
    const char *tag;
} logger_level_t;

static const logger_level_t g_logger_cfg_list[] = 
{
    {   LOGGER_LEVEL_FATAL,     "<1>",  },
    {   LOGGER_LEVEL_ERROR,     "<2>",  },
    {   LOGGER_LEVEL_WARN,      "<3>",  },
    {   LOGGER_LEVEL_INFO,      "<4>",  },
    {   LOGGER_LEVEL_DEBUG,     "<5>",  },   
};

static char * print_tick(unsigned long tks, char *tick, int limit)
{
    int low, hi;

#ifndef HZ
#define HZ  1000  /* 1个tick表示1ms */
#endif

    hi  = tks / HZ;
    low = (tks - hi * HZ) * 1000 / HZ;
    snprintf(tick, limit, "[%5d.%03d]", hi, low);

#undef HZ

    return tick;
}

static char *logger_title_init(int         logger_level, 
                                int         logger_cfg, 
                                const char *module, 
                                const char *file, 
                                int         line,
                                unsigned long tks, 
                                char        *title)
{
    title[0] = '\0';
    if ((logger_cfg & LOGGER_TIMESTAMP) == LOGGER_TIMESTAMP) {
        char tick[32];                
        strcat(title, (const char *)print_tick(tks, tick, sizeof(tick)));
    }

    if ((logger_cfg & LOGGER_LEVEL) == LOGGER_LEVEL) {
        strcat(title, g_logger_cfg_list[logger_level-1].tag);
    }

    if ((logger_cfg & LOGGER_MODULE) == LOGGER_MODULE) {
        strcat(title, "[");
        strcat(title, module);
        strcat(title, "]");
    }

    if ((logger_cfg & LOGGER_FILE) == LOGGER_FILE) {
        const char *p = strrchr(file, '/');
        strcat(title, "[");
        strcat(title, p ? (++p) : p);
        strcat(title, "]");
    }

    if ((logger_cfg & LOGGER_LINE) == LOGGER_LINE) {
        char line_str[16];
        snprintf(line_str, sizeof(line_str), "[%d]", line);
        strcat(title, line_str);
    }

    strcat(title, " "); 

    return title;
}

static int logger_inner_printf(int fd, const char *msg)
{
    if (g_LoggerOps_t->write) {
        //printf("************%s**************", msg);
        g_LoggerOps_t->write(fd, msg, 0); /* 0 means it's long string msg !!! */
    }

    return 0;   
}

int logger_level_printf(  int        logger_level, 
                            int         logger_cfg, 
                            const char *module, 
                            const char *file, 
                            int         line, 
                            const char *fmt, ...)
{
    if (logger_level <= (logger_cfg & LOGGER_LEVEL_VALUE) && !(logger_cfg & LOGGER_OFF)) {
#define LOGGER_MAX_LEN          2048
#define LOGGER_TITLE_MAX_LEN    128

        char msg[LOGGER_MAX_LEN];
        char title[LOGGER_TITLE_MAX_LEN];
        char *tmp;
        va_list ap;
        int n, i;
        int fd = -1;
        unsigned long tks = sys_get_timer_count();
        static int newline = 1;
        int copy_index = 0;
        char msg_bak_r;
        char msg_bak_0;

        va_start(ap, fmt);        
        n = vsnprintf(msg, sizeof(msg), fmt, ap);
        va_end(ap);

        if(n >= LOGGER_MAX_LEN-2){//防止打印buf溢出。
            n = LOGGER_MAX_LEN-2;
        }
        logger_title_init(logger_level, logger_cfg, module, file, line, tks, title);

        if (g_LoggerOps_t->open) {
            fd = g_LoggerOps_t->open(g_LoggerOps_t->name);
        }
        
        for (i = 0; i < n; i++) {

            if (newline) {  

#if defined(LOGGER_PRINT_COLOR_ENABLE)
                /* compare the rest msg is "CLOSE" ? */ 
                if (!memcmp(CLOSE, &msg[copy_index], n-copy_index)) {
                    break;
                }
#endif                
                logger_inner_printf(fd, title);
                newline = 0;
            }

            if ((msg[i] == '\n')) {       
                tmp = &msg[copy_index]; 
                msg_bak_r = msg[i+1];
                msg_bak_0 = msg[i+1+1];
                msg[i+1] = '\r';
                msg[i+1+1] = '\0';
                logger_inner_printf(fd, tmp);
                msg[i+1] = msg_bak_r;
                msg[i+1+1] = msg_bak_0;
                              
                copy_index = i + 1;
                newline = 1;                
            }
        }

        if (copy_index != n) { /* print rest non-change-line msg !!! */                                  
            tmp = &msg[copy_index];
            msg[n] = '\0';
            logger_inner_printf(fd, tmp);
        }

        if (g_LoggerOps_t->close && fd >= 0) {
            g_LoggerOps_t->close(fd);
        }

        return n;
        
#undef LOGGER_TITLE_MAX_LEN
#undef LOGGER_MAX_LEN
    }

    return 0;
}

void logger_level_hexdump(    int         logger_level, 
                                    int         logger_cfg, 
                                    const char *module, 
                                    const char *file, 
                                    int         line, 
                                    const char *title,
                                    const void *data, 
                                    unsigned int len)
{
	char str[160], octet[10];
	int ofs, i, k, d;
	const unsigned char *buf = (const unsigned char *)data;
	const char dimm[]   = "+------------------------------------------------------------------------------+";
    const char offset[] = "| Offset  : 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F   0123456789ABCDEF |";
 
#define logger_printf(fmt, arg...) logger_level_printf(logger_level, logger_cfg, module, file, line, fmt, ##arg)

    logger_printf("%s (%d bytes)\n%s\r\n%s\r\n%s\r\n", title, len, dimm, offset, dimm);

	for (ofs = 0; ofs < (int)len; ofs += 16) {
		d = snprintf( str, sizeof(str), "| %08x: ", ofs );

		for (i = 0; i < 16; i++) {
			if ((i + ofs) < (int)len)
				snprintf( octet, sizeof(octet), "%02x ", buf[ofs + i] );
			else
				snprintf( octet, sizeof(octet), "   " );

			d += snprintf( &str[d], sizeof(str) - d, "%s", octet );
		}
		d += snprintf( &str[d], sizeof(str) - d, "  " );
		k = d;

		for (i = 0; i < 16; i++) {
			if ((i + ofs) < (int)len)
				str[k++] = (0x20 <= (buf[ofs + i]) && (buf[ofs + i]) <= 0x7E) ? buf[ofs + i] : '.';
			else
				str[k++] = ' ';
		}

		str[k] = '\0';
		logger_printf("%s |\r\n", str);
	}

    logger_printf("%s\r\n", dimm);

#undef logger_printf
}

static int logger_default_printf(int fd, const void *buf, int count)
{
    if (count == 1) {
        printf("%c", *(const char*)buf);
    } else {
        printf("%s", (const char*)buf);
    }
    UNUSE(fd);
    return 0;    
}

#endif

static int logger_init(void)
{
#if defined(CFG_LOGGER_ON)

    const LoggerOps_t *logger_ops;
    int retval = -1;

    for (logger_ops = APP_LOGGER_INIT_START; logger_ops < APP_LOGGER_INIT_END; logger_ops ++) {
        if (!strncmp(logger_ops->name, LOGGER_CHANNEL, strlen(LOGGER_CHANNEL))) {
            g_LoggerOps_t = logger_ops;
            retval = 0;
            break;
        }
    }

    if (retval) { /* 启用默认的logger通道 */
#define LOGGER_DEFAULT_CHANNEL  "default"
        static LoggerOps_t g_default_logger_ops = {0}; /* 使用静态定义才能保证这段空间在整个运行周期都可用 */

        g_default_logger_ops.name = LOGGER_DEFAULT_CHANNEL".log";
        g_default_logger_ops.write = logger_default_printf;
        g_LoggerOps_t = &g_default_logger_ops;
        
        logger_warn("LOGGER_CHANNEL=%s, g_LoggerOps_t=%p, %s\n", 
            LOGGER_CHANNEL, g_LoggerOps_t, g_LoggerOps_t ? g_LoggerOps_t->name : LOGGER_DEFAULT_CHANNEL);
        
#undef LOGGER_DEFAULT_CHANNEL
    } 

#if 1 //dump log file !!!
    if (strstr(g_LoggerOps_t->name, "file")) {        
        extern int file_log_dump(const char *filename);
        file_log_dump(g_LoggerOps_t->name);
    }
#endif
    
    return retval;
#else
    return 0;
#endif
}

app_frist_initcall(logger_init)

