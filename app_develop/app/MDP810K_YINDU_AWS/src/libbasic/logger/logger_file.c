
#if defined(CFG_LOGGER_ON)

#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "saferw.h"
#include "logger.h"
#include "common.h"
#include "errno.h"

static int file_log_open(const char *filename)
{
    uint32_t flags = O_CREAT|O_NONBLOCK|O_APPEND|O_RDWR; 
    int mode = 0600;
    char file[64];

    snprintf(file, sizeof(file), "%s%s", CFG_APP_PATH, filename);    
    return open(file, flags, mode);    
}

static int file_log_write(int fd, const void *buf, int count)
{
    const char *msg = (const char *)buf;
    int n = (!count) ? strlen(msg) : count;
    int ret = safety_full_write(fd, buf, n);
    return ret;
}

static int file_log_read(int fd, void *buf, int count)
{
    int ret = safety_full_read(fd, buf, count);
    return ret;
}

static int file_log_close(int fd)
{
    return close(fd);  
}

int file_log_dump(const char *filename)
{
    #include <sys/stat.h>  
    
    int fd = -1;
    uint32_t flags = O_NONBLOCK|O_RDONLY; 
    int mode = 0600;
    char file[64];
    struct stat buf;
    int ret;
    int i = 0;
    char msg[512];

    snprintf(file, sizeof(file), "%s%s", CFG_APP_PATH, filename);
    
    ret = stat(file, &buf);
    printf("[debug] file=%s, stat ret=%d, errno=%d, file-size=%d\n", file, ret, errno, (int)buf.st_size);


    fd = open(file, flags, mode);
    if (fd < 0) {
        printf("[error] open file: %s, fail, ret=%d, errno=%d\n", file, fd, errno);
        ret = -1;
        goto exit_entry;
    }
    
    printf("\r\n---------------------------------------------------------------\r\n"); 
    for (i = 0; i < buf.st_size;) {
        ret = safety_full_read(fd, msg, sizeof(msg)-1);
        if (ret <= 0) {
            break;
        }

        msg[ret] = '\0';
        i += ret;
        printf("%s", msg);
    }
    printf("---------------------------------------------------------------\r\n\r\n");
    ret = 0;

exit_entry:
    
    if (fd >= 0) {
        close(fd);
    }
    
    return ret;
}


logger_register(file)

#endif
