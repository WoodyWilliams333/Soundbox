
#include "init.h"

#define LOGGER_CFG          LOGGER_OFF
#define LOGGER_MODULE_NAME  "new7220"
#include "logger.h"

static int platform_init(void)
{
    logger_fatal("enter %s() >>>\n", __func__);
    logger_error("enter %s() >>>\n", __func__);
    logger_warn("enter %s() >>>\n", __func__);
    logger_info("enter %s() >>>\n", __func__);
    logger_debug("enter %s() >>>\n", __func__);
    return 0;
}

app_late_initcall(platform_init)
    