#include <stdio.h>
#include <string.h>
#include <getopt.h>

#include "syscall.h"
#include "init.h"

#define LOGGER_CFG          (LOGGER_LEVEL_DEBUG | LOGGER_TIMESTAMP | LOGGER_LEVEL | LOGGER_MODULE | LOGGER_FILE | LOGGER_LINE)
#define LOGGER_MODULE_NAME  "main-test"
#include "logger.h"

static int do_initcall(const initcall_t *start, const initcall_t *end)
{
    const initcall_t *initcall;
    int retval, errcnt = 0;
    
    for (initcall = start;
         initcall < end;
         initcall ++) {
        retval = initcall->init();
        if (retval)
            errcnt++;
        
        if (retval) {
            logger_error("%-24s[%s] with error = %d\n", initcall->name, "FAIL", retval);
        } else {
            logger_debug("%-24s[%s]\n", initcall->name, " OK ");
        }
    }

    logger_info("start=%p, end=%p\n", start, end);

    return errcnt;
}


/**
 * @fn          do_app_early_initcall
 * @brief       做应用层前期初始化，例如初始化logger，系统级初始化等
 * @param in    none
 * @param out   noe
 * @return      0-success   else-failed
 * @note
 */
static int do_app_early_initcall(void)
{    
    return do_initcall(APP_EARLY_INITCALL_START, APP_EARLY_INITCALL_END);
}

/**
 * @fn          do_app_late_initcall
 * @brief       做应用层后期初始化，例如加载参数文件等
 * @param in    none
 * @param out   noe
 * @return      0-success   else-failed
 * @note
 */
static int do_app_late_initcall(void)
{    
    return do_initcall(APP_LATE_INITCALL_START, APP_LATE_INITCALL_END);
}

#if defined(CFG_TESTS_CASE_ON)
#include "test_case_cfg.h"
static int main_test_cases_run(void)
{
    return test_cases_entry();
}
#endif

extern int npmain(int argc, char *argv[]);

int main(int argc, char *argv[])
{        
    do_app_early_initcall();
    do_app_late_initcall();

#if defined(CFG_TESTS_CASE_ON)
    main_test_cases_run();
#endif    

	npmain(argc, argv);

    printf("<<<==================== ++++++++ %s()\r\n", __func__);

    return 0;
}
