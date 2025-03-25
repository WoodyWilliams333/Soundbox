#include <syscall.h>
#include <sys/ioctl.h>
#include "system.h"
#include "ped.h" //����������ɲ�������
#include "uart.h"
#include "lcd.h"
#include "basicext.h"

typedef enum {
    UART_IOCTL_GET,
    UART_IOCTL_SET,
    UART_IOCTL_READ_NONBLOCK,
} UART_IOCTL_CMD_E;

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
#if 0
// �򿪴����豸
int uart_open(const char *filename)
{
    return open(filename, O_RDWR);
}

// ͨ�������豸��������
int uart_send(int fd, const void *data, uint32_t data_len)
{
    return write(fd, data, data_len);
}

// ͨ�������豸��������
int uart_recv(int fd, void *data, uint32_t data_len)
{
    return read(fd, data, data_len);
}

// �����Ѵ򿪵Ĵ����豸
int uart_config(int fd, int baud, int bits, char parity, int stop)
{
    #if 0 //�ݲ�֧������ ������/����λ/У��λ/ֹͣλ (USBת�����γɵ����⴮�ڣ�������������Ч)
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

// �رմ����豸
int uart_close(int fd)
{
    return close(fd);
}

// �����豸��дˢ�£��ײ��ݲ�֧�ִ˲���
int uart_flush(int fd)
{
    //return ioctl(fd, IOC_SERIAL_GET_RXRESET, 0);
    return 0;
}

// ���ô����豸����һ�εĳ�ʱʱ�䣬��λΪ���룬����ֵΪ10ms
int uart_set_read_timeout(int fd, int ms)
{
    return ioctl(fd, USB_IOCTL_READ_WAITING, ms);
}

// ����ʽ���մ������ݣ�ע��: ��ʹû�����ݵ�����Ҳ�ᳬʱtimeoutms��ô��
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

    // �������õ��ν��ճ�ʱΪ10ms����ͨ��һ��whileѭ�����ﵽtimeoutms���ܳ�ʱʱ��
    uart_set_read_timeout(fd, 10);

    tickcount = sys_get_timer_count(); //��ȡ��ǰʱ��

    while (1) {
        if (totalsize == nbytes) {  //�ɹ�����
            retval = totalsize;
            break;
        }

        if (sys_get_timer_count() > tickcount + timeoutms){ //��ʱ����
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

// ����ʽ��ȡ�������ݣ������ڲ�Ĭ�ϵĽ��ճ�ʱʱ��Ϊ1000ms
int serial_read(int fd, void * pvbuff, unsigned int * pisize)
{
    int error = 0;
    int ireaded = 0;

    ireaded = read_timeout(fd, pvbuff, *pisize, 1000); // �ܳ�ʱʱ��Ϊ 1000ms
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

// ͨ�������豸���ⷢ�����ݣ��������������ʱ���ֳ�512�ֽ�һ�ζεط���
int serial_write(int fd, const void * pvData, unsigned int isize)
{
    int error;
    int k, m, s;

    for (k=0; k<(int)isize; ) {
        m = min(512, (int)(isize-k)); // �ֶη���
        s = uart_send(fd, (uint8_t *)pvData+k, m);
        if (s >= 0)
            k += s;
        else
            break;
    }
    error = (k == (int)isize) ? 0 : -1;
    return error;
}

// ���ڲ����������
int uart_module_test(void)
{
#define UART_DEV_NAME   "/dev/ttyS2"  // USB�����豸����
#define UART_BAUDRATE   115200          // Ĭ�ϲ����ʣ������ʶ���USBת���⴮������Ч��

    int retval;
    int fd;
    int i = 0;
    int cnt = 100;
    uint8_t send_buf[128];
    uint8_t recv_buf[128];
    unsigned int recv_len = 0;
	int count = 0;
	
	app_lcd_clear_all();
	app_lcd_display(0, 4, DISP_CFONT, (char *)"--UART TEST--");
	app_lcd_flip();
	
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

#if 1
    for (i = 0; i < cnt; i++) {
		memset(send_buf,0,sizeof(send_buf));
		strcpy(send_buf,"hello world!");
        retval = serial_write(fd, send_buf, sizeof(send_buf));
        if (retval < 0) {
            printf("uart send fail, ret=%d,errno=%d\n", retval, errno);
            retval = -3;
            goto exit_entry;
        }

        memset(recv_buf, 0, sizeof(recv_buf));
        recv_len = sizeof(recv_buf);
		
        retval = serial_read(fd, recv_buf, &recv_len);

		#if 1
		if (retval < 0 ) {
            retval = -4;
        } else {
           app_lcd_clear_all();
			app_lcd_display(0, 4, DISP_CFONT, (char *)UART_DEV_NAME);
			app_lcd_display(0, 6, DISP_CFONT, (char *)"UART RECEIVED!!!!!");
	        app_lcd_display(0, 8, DISP_CFONT, (char *)"recv_len=%d",recv_len);
        	app_lcd_flip();
        }

        if (recv_len == sizeof(send_buf) && !memcmp(recv_buf, send_buf, recv_len)) {
            printf("uart comm test %03d [ OK ] !!!!!!!!!!!!!!!!!!!\n", i+1);
        } else {
            printf("uart comm test %03d [FAIL] *******************\n", i+1);
        }
		#endif
        recv_len = 0;
        printf("\n\n");

        sys_msleep(100);
        uart_flush(fd); //��մ��ڻ�����

    }
#endif

exit_entry:

    if (fd >= 0) {
        uart_close(fd);
    }

    return retval;
}

#else


int uart_open(const char *filename)
{
    return open(filename, O_RDWR);
}

int uart_recv(int fd, void *data, int * pisize)
{
    //return read(fd, data, data_len);
    return read(fd, data, *pisize);
}
int uart_close(int fd)
{
    return close(fd);
}
int _uart_set_read_timeout(int fd, int ms)
{
    //return ioctl(fd, USB_IOCTL_READ_WAITING, ms);
    return ioctl(fd, UART_IOCTL_READ_NONBLOCK, ms);
}

#endif



