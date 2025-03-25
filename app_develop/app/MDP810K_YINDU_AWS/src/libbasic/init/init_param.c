#include "init.h"

#define LOGGER_CFG          LOGGER_OFF
#define LOGGER_MODULE_NAME  "param"
#include "logger.h"

/* ��ȡӦ�õ������ļ���Ϣ */
static int param_init(void)
{
    logger_fatal("enter %s() >>>\n", __func__);
    logger_error("enter %s() >>>\n", __func__);
    logger_warn("enter %s() >>>\n", __func__);
    logger_info("enter %s() >>>\n", __func__);
    logger_debug("enter %s() >>>\n", __func__);
    return 0;
}

app_late_initcall(param_init)
    