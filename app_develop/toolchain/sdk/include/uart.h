
/**
@if Chinese
 * @brief    此模块用于描述 <strong>串口模块</strong> 相关的接口
 * @author   liluchang
 * @date     2019-01-24
 * @version  V1.0
 * @remarks Change History:
 * 日期          | 版本          | 作者            | 描述
 * ------------- | ------------- | --------------- | ----
 * 2019/01/24    | 1.0.0         | liluchang       | 创建文件
 * 2022/04/20    | 1.0.1         | Wenming         | 增加英文注释
@else 
 * @brief    This module is used to describe <strong>Uart</strong> interfaces module
 * @author   liluchang
 * @date     2019-01-24
 * @version  V1.0
 * @remarks Change History:
 * Date          | Version       | Author          | Desc
 * ------------- | ------------- | --------------- | ----
 * 2019/01/24    | 1.0.0         | liluchang       | Create file
 * 2022/04/20    | 1.0.1         | Wenming         | Add English description
 @endif 
 */

/**
@if Chinese
 * @defgroup UART 串口
@else 
 * @defgroup UART Uart
@endif  
 * @{
 */

#ifndef __UART_H__
#define __UART_H__

#include "sys/types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
@if Chinese
 * @name USB串口设备的名称
@else 
 * @name Name of the USB serial port device
@endif  
 * @{
 */
#ifndef UART_DEV_NAME
#define UART_DEV_NAME       "/dev/ttyUSB0"
#endif
/** @} */

/**
@if Chinese
 * @brief   <strong> 串口操作<span style="color:red">示例</span>代码<span style="color:red">(请勿调用此接口)</span></strong>
 * @retval  none
 * @note    <span style="color:red"> <strong> 非正常应用调用接口，仅供示例代码参考，请勿调用 </strong> </span>
 * @par 示例:
 * @code

#include <syscall.h>
#include <sys/ioctl.h>
#include "system.h"
#include "ped.h" //用于随机生成测试数据
#include "uart.h"

#ifndef     min
#define min(X, Y)                   \
    ({ typeof (X) __x = (X);        \
        typeof (Y) __y = (Y);       \
        (__x < __y) ? __x : __y; })
#endif

#ifndef     max
#define max(X, Y)                   \
    ({ typeof (X) __x = (X);        \
        typeof (Y) __y = (Y);       \
        (__x > __y) ? __x : __y; })
#endif

// 打开串口设备
int uart_open(const char *filename)
{
    return open(filename, O_RDWR);
}

// 通过串口设备发送数据
int uart_send(int fd, const void *data, uint32_t data_len)
{
    return write(fd, data, data_len);
}

// 通过串口设备接收数据
int uart_recv(int fd, void *data, uint32_t data_len)
{
    return read(fd, data, data_len);
}

// 配置已打开的串口设备
int uart_config(int fd, int baud, int bits, char parity, int stop)
{
    #if 0 //暂不支持设置 波特率/数据位/校验位/停止位 (USB转串口形成的虚拟串口，波特率设置无效)
    struct uart_ioctl struUartIoctl;

    struUartIoctl.baudrate  = baud;
    struUartIoctl.databits  = bits;
    struUartIoctl.stopbit   = stop;

    switch (parity) {
        case 'n':
        case 'N': { // NONE
            struUartIoctl.paritybit = 0;
            break;
        }

        case 'o':
        case 'O': { // ODD
            struUartIoctl.paritybit = 1;
            break;
        }

        case 'e':
        case 'E': { //EVEN
            struUartIoctl.paritybit = 2;
            break;
        }

        default: {
            return -EINVAL; ;
            break;
        }
    }

    return ioctl(fd, IOC_SERIAL_SET_PROPERTY, ((unsigned long)&struUartIoctl));
    #endif
    (void)baud; (void)bits ;(void)parity; (void)stop;
    return 0;
}

// 关闭串口设备
int uart_close(int fd)
{
    return close(fd);
}

// 串口设备读写刷新，底层暂不支持此操作
int uart_flush(int fd)
{
    //return ioctl(fd, IOC_SERIAL_GET_RXRESET, 0);
    return 0;
}

// 设置串口设备接收一次的超时时间，单位为毫秒，建议值为10ms
int uart_set_read_timeout(int fd, int ms)
{
    return ioctl(fd, USB_IOCTL_READ_WAITING, ms);
}

// 阻塞式接收串口数据，注意: 即使没有数据到来，也会超时timeoutms这么久
static ssize_t read_timeout(int fd, void *buf, size_t nbytes, uint32_t timeoutms)
{
    unsigned long tickcount;
    uint32_t    totalsize=0;
    int size;
    int retval = 0;

    if (fd < 0 || !buf) {
        retval = -EINVAL;
        goto exit_entry;
    }

    // 这里设置单次接收超时为10ms，再通过一个while循环，达到timeoutms的总超时时间
    uart_set_read_timeout(fd, 10);

    tickcount = sys_get_timer_count(); //获取当前时间

    while (1) {
        if (totalsize == nbytes) {  //成功返回
            retval = totalsize;
            break;
        }

        if (sys_get_timer_count() > tickcount + timeoutms){ //超时返回
            retval = totalsize ? totalsize : 0;
            break;
        }
        size = uart_recv(fd, (void *)((uint8_t*)buf+totalsize), nbytes-totalsize);
        if (size == -1) {
            if (errno != EAGAIN) {
                retval = totalsize ? totalsize : 0;
                break;
            }
            continue;
        }
        totalsize += size;
    }

exit_entry:
    return retval;
}

// 阻塞式读取串口数据，函数内部默认的接收超时时间为1000ms
int serial_read(int fd, void * pvbuff, unsigned int * pisize)
{
    int error = 0;
    int ireaded = 0;

    ireaded = read_timeout(fd, pvbuff, *pisize, 1000); // 总超时时间为 1000ms
    if (ireaded >=0){
        if ((*pisize != 0)&& (ireaded == 0))
            error = -1;
        else{
            *pisize = (unsigned int)ireaded;
        }

    } else {
        error = -1;
        *pisize = 0;
    }

    return error;
}

// 通过串口设备对外发送数据，当遇到大段数据时，分成512字节一段段地发送
int serial_write(int fd, const void * pvData, unsigned int isize)
{
    int error;
    int k, m, s;

    for (k=0; k<(int)isize; ) {
        m = min(512, (int)(isize-k)); // 分段发送
        s = uart_send(fd, (uint8_t *)pvData+k, m);
        if (s >= 0)
            k += s;
        else
            break;
    }
    error = (k == (int)isize) ? 0 : -1;
    return error;
}

// 串口操作范例入口
int uart_module_test(void)
{
#define UART_DEV_NAME   "/dev/ttyUSB0"  // USB串口设备名称
#define UART_BAUDRATE   115200          // 默认波特率，波特率对于USB转虚拟串口是无效的

    int retval;
    int fd;
    int i = 0;
    int cnt = 100;
    uint8_t send_buf[128];
    uint8_t recv_buf[128];
    unsigned int recv_len = 0;

    fd = uart_open(UART_DEV_NAME);
    if (fd < 0) {
        printf("uart open fail, ret=%d, errno=%d\n", fd, errno);
        retval = -1;
        goto exit_entry;
    }

    retval = uart_config(fd, UART_BAUDRATE, 8, 'n', 1);
    if (retval < 0) {
        printf("uart config fail, ret=%d, errno=%d\n", retval, errno);
        retval = -2;
        goto exit_entry;
    }

    uart_flush(fd);

    for (i = 0; i < cnt; i++) {

        ped_get_random_nr(sizeof(send_buf), send_buf);
        retval = serial_write(fd, send_buf, sizeof(send_buf));
        if (retval < 0) {
            printf("uart send fail, ret=%d,errno=%d\n", retval, errno);
            retval = -3;
            goto exit_entry;
        }

        memset(recv_buf, 0, sizeof(recv_buf));
        recv_len = sizeof(recv_buf);
        logger_debug("recv0\n");
        retval = serial_read(fd, recv_buf, &recv_len);
        logger_debug("recv1-------\n");
        if (retval < 0 ) {
            printf("uart recv fail, ret=%d, recv_len=%d, exp-len=%d, errno=%d\n",
                        retval, recv_len, sizeof(send_buf), errno);
            retval = -4;
        } else {
            printf("uart recv %d bytes\n", recv_len);
        }

        if (recv_len == sizeof(send_buf) && !memcmp(recv_buf, send_buf, recv_len)) {
            printf("uart comm test %03d [ OK ] !!!!!!!!!!!!!!!!!!!\n", i+1);
        } else {
            printf("uart comm test %03d [FAIL] *******************\n", i+1);
        }
        recv_len = 0;
        printf("\n\n");

        sys_msleep(100);
        uart_flush(fd); //清空串口缓存区

    }

exit_entry:

    if (fd >= 0) {
        uart_close(fd);
    }

    return retval;
}
@endcode

@else
 * @brief   <strong> Serial port operation<span style="color:red">The sample </span>code<span style="color:red">(Do not call this interface)</span></strong>
 * @retval  none
 * @note    <span style="color:red"> <strong> Abnormal application call interface, only for example code reference, do not call</strong> </span>
 * @par 示例:
 * @code

#include <syscall.h>
#include <sys/ioctl.h>
#include "system.h"
#include "ped.h" //Used to randomly generate test data
#include "uart.h"

#ifndef     min
#define min(X, Y)                   \
    ({ typeof (X) __x = (X);        \
        typeof (Y) __y = (Y);       \
        (__x < __y) ? __x : __y; })
#endif

#ifndef     max
#define max(X, Y)                   \
    ({ typeof (X) __x = (X);        \
        typeof (Y) __y = (Y);       \
        (__x > __y) ? __x : __y; })
#endif

// Starting the Serial port Device
int uart_open(const char *filename)
{
    return open(filename, O_RDWR);
}

// Send data through a serial port device
int uart_send(int fd, const void *data, uint32_t data_len)
{
    return write(fd, data, data_len);
}

// Receives data through a serial port device
int uart_recv(int fd, void *data, uint32_t data_len)
{
    return read(fd, data, data_len);
}

// Configure the serial port device that has been enabled
int uart_config(int fd, int baud, int bits, char parity, int stop)
{
    #if 0 //The baud rate, data bit, parity bit, and stop bit cannot be set. (The baud rate is invalid if the serial port is converted from USB to serial port.)
    struct uart_ioctl struUartIoctl;

    struUartIoctl.baudrate  = baud;
    struUartIoctl.databits  = bits;
    struUartIoctl.stopbit   = stop;

    switch (parity) {
        case 'n':
        case 'N': { // NONE
            struUartIoctl.paritybit = 0;
            break;
        }

        case 'o':
        case 'O': { // ODD
            struUartIoctl.paritybit = 1;
            break;
        }

        case 'e':
        case 'E': { //EVEN
            struUartIoctl.paritybit = 2;
            break;
        }

        default: {
            return -EINVAL; ;
            break;
        }
    }

    return ioctl(fd, IOC_SERIAL_SET_PROPERTY, ((unsigned long)&struUartIoctl));
    #endif
    (void)baud; (void)bits ;(void)parity; (void)stop;
    return 0;
}

// Stop the serial port device
int uart_close(int fd)
{
    return close(fd);
}

// The serial port device is refreshed. The underlying layer does not support this operation
int uart_flush(int fd)
{
    //return ioctl(fd, IOC_SERIAL_GET_RXRESET, 0);
    return 0;
}

// Set the timeout period for the serial port device to receive data once. The unit is ms. The recommended value is 10ms
int uart_set_read_timeout(int fd, int ms)
{
    return ioctl(fd, USB_IOCTL_READ_WAITING, ms);
}

//Block receiving serial port data, note: even if no data arrives, it will timeout for this long time
static ssize_t read_timeout(int fd, void *buf, size_t nbytes, uint32_t timeoutms)
{
    unsigned long tickcount;
    uint32_t    totalsize=0;
    int size;
    int retval = 0;

    if (fd < 0 || !buf) {
        retval = -EINVAL;
        goto exit_entry;
    }

    // The single receive timeout is set to 10ms, followed by a while loop to reach the total timeoutms
    uart_set_read_timeout(fd, 10);

    tickcount = sys_get_timer_count(); //Get the current time

    while (1) {
        if (totalsize == nbytes) {  //Successfully returns
            retval = totalsize;
            break;
        }

        if (sys_get_timer_count() > tickcount + timeoutms){ //Timeout return
            retval = totalsize ? totalsize : 0;
            break;
        }
        size = uart_recv(fd, (void *)((uint8_t*)buf+totalsize), nbytes-totalsize);
        if (size == -1) {
            if (errno != EAGAIN) {
                retval = totalsize ? totalsize : 0;
                break;
            }
            continue;
        }
        totalsize += size;
    }

exit_entry:
    return retval;
}

// Blocking reads serial port data. The default internal timeout is 1000ms
int serial_read(int fd, void * pvbuff, unsigned int * pisize)
{
    int error = 0;
    int ireaded = 0;

    ireaded = read_timeout(fd, pvbuff, *pisize, 1000); // The total timeout duration is 1000ms
    if (ireaded >=0){
        if ((*pisize != 0)&& (ireaded == 0))
            error = -1;
        else{
            *pisize = (unsigned int)ireaded;
        }

    } else {
        error = -1;
        *pisize = 0;
    }

    return error;
}

// Data is sent externally through a serial port device. When encountering a large chunk of data, the data is divided into 512 bytes
int serial_write(int fd, const void * pvData, unsigned int isize)
{
    int error;
    int k, m, s;

    for (k=0; k<(int)isize; ) {
        m = min(512, (int)(isize-k)); // Segmented send
        s = uart_send(fd, (uint8_t *)pvData+k, m);
        if (s >= 0)
            k += s;
        else
            break;
    }
    error = (k == (int)isize) ? 0 : -1;
    return error;
}

// Serial port operation example entry
int uart_module_test(void)
{
#define UART_DEV_NAME   "/dev/ttyUSB0"  // USB serial port device name
#define UART_BAUDRATE   115200          // Default baud rate. Baud rate is invalid for USB-to-vSERIAL port

    int retval;
    int fd;
    int i = 0;
    int cnt = 100;
    uint8_t send_buf[128];
    uint8_t recv_buf[128];
    unsigned int recv_len = 0;

    fd = uart_open(UART_DEV_NAME);
    if (fd < 0) {
        printf("uart open fail, ret=%d, errno=%d\n", fd, errno);
        retval = -1;
        goto exit_entry;
    }

    retval = uart_config(fd, UART_BAUDRATE, 8, 'n', 1);
    if (retval < 0) {
        printf("uart config fail, ret=%d, errno=%d\n", retval, errno);
        retval = -2;
        goto exit_entry;
    }

    uart_flush(fd);

    for (i = 0; i < cnt; i++) {

        ped_get_random_nr(sizeof(send_buf), send_buf);
        retval = serial_write(fd, send_buf, sizeof(send_buf));
        if (retval < 0) {
            printf("uart send fail, ret=%d,errno=%d\n", retval, errno);
            retval = -3;
            goto exit_entry;
        }

        memset(recv_buf, 0, sizeof(recv_buf));
        recv_len = sizeof(recv_buf);
        logger_debug("recv0\n");
        retval = serial_read(fd, recv_buf, &recv_len);
        logger_debug("recv1-------\n");
        if (retval < 0 ) {
            printf("uart recv fail, ret=%d, recv_len=%d, exp-len=%d, errno=%d\n",
                        retval, recv_len, sizeof(send_buf), errno);
            retval = -4;
        } else {
            printf("uart recv %d bytes\n", recv_len);
        }

        if (recv_len == sizeof(send_buf) && !memcmp(recv_buf, send_buf, recv_len)) {
            printf("uart comm test %03d [ OK ] !!!!!!!!!!!!!!!!!!!\n", i+1);
        } else {
            printf("uart comm test %03d [FAIL] *******************\n", i+1);
        }
        recv_len = 0;
        printf("\n\n");

        sys_msleep(100);
        uart_flush(fd); //Clear the serial port cache

    }

exit_entry:

    if (fd >= 0) {
        uart_close(fd);
    }

    return retval;
}
@endcode

@endif
 */
void uart_module_demo_code_never_call_this_api_please(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __UART_H__ */

/** @} */

