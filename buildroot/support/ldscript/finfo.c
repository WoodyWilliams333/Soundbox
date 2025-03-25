/**
 * @file    finfo.c
 *
 * @author  Li.Hua <lihua_338@163.com>.
 *
 * @date    2014-10-02
 *
 * @brief
 *
 * @note
 *
 * Modification history
 * ----------------------------------------------------------------------------
 * Date         Version  Author       History
 * ----------------------------------------------------------------------------
 *
 */

#include <stdint.h>

#define FILE_TYPE       0x50504155
#define SP_ADDRESS      (DATA_BASE + DATA_SIZE)
#define LOAD_TYPE       0x5A76E3F1
#ifndef CFG_APP_STACK_SIZE
#define CFG_APP_STACK_SIZE CFG_MAIN_STACK_SIZE
#endif
#ifndef CFG_APP_NAME
#define CFG_APP_NAME "appname"
#endif
#ifndef CFG_APP_VERSION
#define CFG_APP_VERSION "1.0.0"
#endif
#ifndef CFG_COMPILE_SVN
#define CFG_COMPILE_SVN ""
#endif
#ifndef CFG_COMPILE_TIME
#define CFG_COMPILE_TIME ""
#endif
#ifndef CFG_COMPILE_NAME
#define CFG_COMPILE_NAME ""
#endif

#undef  SECTION
#define SECTION(name)   __attribute__((section(#name), used))

typedef struct {
    char        flag[4];
    uint32_t    filetype;
    uint32_t    Filelen;
    uint32_t    loadadd;
    uint32_t    entryadd;
    char        name[32];
    char        version[8];
    uint32_t    load_type;
    uint32_t    app_type;
    uint32_t    __data_start;
    uint32_t    __bss_start;
    uint32_t    __bss_end;
    uint32_t    __text_start;
    uint32_t    __text_end;
    uint32_t    __stack_size;
    char        svn[8];
    char        compile_time[24];
    char        compile_name[20];
} UserFileInfo_t;

extern int _startapp(uint32_t relocate_func, uint32_t argv);
extern unsigned long etext;
extern unsigned long __data_start__;
extern unsigned long __bss_start__;
extern unsigned long __bss_end__;
extern unsigned long __text_start__, __text_end__;

static const unsigned long VectorTable[0x20 / sizeof(unsigned long)] SECTION(.vectors) = {
    (unsigned long)SP_ADDRESS,          /*  0, SP start value.  */
    (unsigned long)_startapp,           /*  1, PC start value.  */
    (unsigned long)0,                   /*  Reserved .          */
    (unsigned long)0,                   /*  Reserved .          */
    (unsigned long)0,                   /*  Reserved .          */
    (unsigned long)0,                   /*  Reserved .          */
    (unsigned long)0,                   /*  Reserved .          */
    (unsigned long)sizeof(VectorTable), /*  Offset of Fileinfo  */
};

static const UserFileInfo_t FileInfo SECTION(.FILEINFO) = {
    "MPOS",                             /* flag,    notice: don't change                        */
    FILE_TYPE,                          /* filetype notice: don't change                        */
    0,                                  /* Filelen  notice: will changed later by tool          */
    TEXT_BASE,                          /* loadadd  notice: don't change                        */
    TEXT_BASE + 4,                      /* runadd   notice: don't change                        */
    CFG_APP_NAME,                          /* name     notice: you can change it                   */
    CFG_APP_VERSION,                         /* version  notice: self-defined, can change            */
#if 0
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
#else
    LOAD_TYPE,
    CFG_APP_TYPE,
    (uint32_t) &__data_start__,
    (uint32_t) &__bss_start__,
    (uint32_t) &__bss_end__,
    (uint32_t) &__text_start__,
    (uint32_t) &__text_end__,
    CFG_APP_STACK_SIZE,
#endif
    CFG_COMPILE_SVN,
    CFG_COMPILE_TIME,
    CFG_COMPILE_NAME,
};

