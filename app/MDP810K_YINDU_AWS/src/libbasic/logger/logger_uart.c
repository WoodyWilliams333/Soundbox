
#if defined(CFG_LOGGER_ON)

#include <fcntl.h>
#include <unistd.h>

#include "logger.h"
#include "common.h"

static int uart_log_open(const char *filename)
{
    UNUSE(filename);
    return 0;
}

static int uart_log_write(int fd, const void *buf, int count)
{
    if (count == 1) {
        printf("%c", *(const char*)buf);
    } else {
        printf("%s", (const char*)buf);
    }
    UNUSE(fd);
    return 0; 
}

static int uart_log_read(int fd, void *buf, int count)
{
    UNUSE(fd);
    UNUSE(buf);
    UNUSE(count);
    return 0; 
}

static int uart_log_close(int fd)
{
    UNUSE(fd);
    return 0;  
}

logger_register(uart)

#endif

