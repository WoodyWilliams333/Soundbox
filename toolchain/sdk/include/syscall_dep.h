/**
 * @file    syscall_dep.h
 *
 * @author  Li.Hua <lihua_338@163.com>.
 *
 * @date    2017-12-05
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

#ifndef __SYSCALL_DEPEND_H__
#define __SYSCALL_DEPEND_H__

#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>


#include "dirent.h"
#include "sys/vfs.h"
#include "linuxtypes.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define SCI_FAILER  -1

//priority inherit mode for mutex
#define SCI_NO_INHERIT 0
#define SCI_INHERIT 1
// Wait option.
#define SCI_NO_WAIT                 0x0
#define SCI_WAIT_FOREVER            0xFFFFFFFF
// Auto start option on thread
#define SCI_DONT_START              0
#define SCI_AUTO_START              1
// Option used to set/get event.
#define SCI_OR                      0
#define SCI_OR_CLEAR                1
#define SCI_AND                     2
#define SCI_AND_CLEAR               3

//---------------------------------------------
// API return values.
//---------------------------------------------
//Success, no error.
#define SCI_SUCCESS                 0x00
//Object was deleted.
#define SCI_DELETED                 0x01
//Invalid pool pointer.
#define SCI_POOL_ERROR              0x02
//Invalid pointer.
#define SCI_PTR_ERROR               0x03
//A wait option other than TX_NO_WAIT was specified on call from a non-thread.
#define SCI_WAIT_ERROR              0x04
//Size is invalid.
#define SCI_SIZE_ERROR              0x05
//Invalid event group pointer.
#define SCI_GROUP_ERROR             0x06
//Service was unable to get the specified events.
#define SCI_NO_EVENTS               0x07
//Invalid option was specified.
#define SCI_OPTION_ERROR            0x08
//Invalid queue pointer.
#define SCI_QUEUE_ERROR             0x09
//Service was unable to retrieve a message because the queue was empty.
#define SCI_QUEUE_EMPTY             0x0A
//Service was unable to send message because the queue was full.
#define SCI_QUEUE_FULL              0x0B
//Invalid counting semaphore pointer.
#define SCI_SEMAPHORE_ERROR         0x0C
//Service was unable to retrieve an instance of the counting semaphore (semaphore count is zero).
#define SCI_NO_INSTANCE             0x0D
//Invalid thread control pointer.
#define SCI_THREAD_ERROR            0x0E
//Invalid thread priority, which is a value outside the range of 0-31.
#define SCI_PRIORITY_ERROR          0x0F
//Service was unable to allocate memory.
#define SCI_NO_MEMORY               0x10
//Specified thread is not in a terminated or completed state.
#define SCI_DELETE_ERROR            0x11
//Specified thread is not suspended.
#define SCI_RESUME_ERROR            0x12
//Invalid caller of this service.
#define SCI_CALLER_ERROR            0x13
//Specified thread is in a terminated or completed state.
#define SCI_SUSPEND_ERROR           0x14
//Invalid application timer pointer.
#define SCI_TIMER_ERROR             0x15
//Invalid value (a zero) supplied for initial ticks.
#define SCI_TICK_ERROR              0x16
//Timer was already active./Invalid activation selected.
#define SCI_ACTIVATE_ERROR          0x17
//Invalid preemption threshold specified.
//This value must be a valid priority less than or equal to the initial priority of the thread.
#define SCI_THRESH_ERROR            0x18
//Previously set delayed suspension was lifted.
#define SCI_SUSPEND_LIFTED          0x19
//Suspension was aborted by another thread, timer, or ISR.
#define SCI_WAIT_ABORTED            0x1A
//Specified thread is not in a waiting state.
#define SCI_WAIT_ABORT_ERROR        0x1B
//Invalid mutex pointer.
#define SCI_MUTEX_ERROR             0x1C
//Service was unable to get ownership of the mutex.
#define SCI_NOT_AVAILABLE           0x1D
//Mutex is not owned by caller.
#define SCI_NOT_OWNED               0x1E
//Invalid priority inherit parameter.
#define SCI_INHERIT_ERROR           0x1F
//Invalid auto-start selection.
#define SCI_START_ERROR             0x20
//Parameter is invalid.
#define SCI_PARAM_ERROR             0x21
//Normal error.
#define SCI_ERROR                   0xFF


#define TRUE   1   /* Boolean true value. */
#define FALSE  0   /* Boolean false value. */

//---------------------------------------------
// API input parameters.
//---------------------------------------------
// Boolean value
#define SCI_TRUE                    TRUE       // Boolean true value
#define SCI_FALSE                   FALSE       // Boolean false value
#define SCI_NULL                    0x0

// Auto start option on timer.
#define SCI_NO_ACTIVATE             0
#define SCI_AUTO_ACTIVATE           1

struct file_stat {
    long    size;
    long    mode;
    long    atime;
    long    mtime;
    long    ctime;
    long    blksize;
    long    blocks;
    char    name[32];
};

//---------------------------------------------
// Type define.
//---------------------------------------------
typedef uint32_t BLOCK_ID;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t  uint8;
typedef int  BOOLEAN;

typedef void    *SCI_EVENT_GROUP_PTR;
typedef void    *SCI_THREAD_PTR;
typedef void    *SCI_TIMER_PTR;

//Zhemin.Lin, add, 09/12/2003, CR:MS00004678,
typedef void    *SCI_MUTEX_PTR;
typedef void    *SCI_SEMAPHORE_PTR;

// The prototype of C funtion which execute when timer expires.
typedef void (*TIMER_FUN)(unsigned long);

// The prototype of C function for thread execution.
typedef void (*THREAD_FUN)(uint32 id, void *arg);
typedef struct SCI_TICK_TIME_Tag {
    uint32 milliseconds;
    uint32 second;
} SCI_TICK_TIME_T;
/*! \brief mmi signal struct */
typedef struct SignalSTag {
    uint16                      signalCode;         /*!< the signalCode */
    uint16                      signalSize;         /*!< signal size */
    uint32                      pre;                /*!< previous signal */
    uint32                      succ;               /*!< succ signal */
    uint32                      send;               /*!< send */
//  uint16                      dummy;              // reserver
    uint8                      *sig;                /*!< signal data */
} Signal_t;

typedef Signal_t *xSignalHeader;

#define MN_MAX_IMEI_LENGTH             8

typedef uint8 MN_IMEI_T[MN_MAX_IMEI_LENGTH];

typedef struct _MN_IMEISVN_T {
    MN_IMEI_T   imei;
    BOOLEAN     svn_flag; //true--svn exit;false--svn not exit
    uint8       svn;
} MN_IMEISVN_T;


typedef struct {
    void *name;
    void *addr;
} kernel_symbol_t;

#define EXPORT_SYMBOL(func_ret, func_name, func_args) \
    func_ret func_name func_args; \
    static const kernel_symbol_t sym_item_##func_name \
    __attribute__((__used__, __section__("export_symbol"))) = { \
        (void *)#func_ret " " #func_name #func_args, \
        (void *)&func_name, \
    }; \
    func_ret func_name func_args

#define EXPORT_SYMBOL_USR(func_ret, func_name, func_args) \
    static const kernel_symbol_t sym_item_##func_name \
    __attribute__((__used__, __section__("export_symbol"))) = { \
        (void *)#func_ret " " #func_name #func_args, \
        (void *)&func_name, \
    };

typedef enum CHGMNG_StateCode_enum {
    CHGMNG_IDLE = 0,
    CHGMNG_STARTING,
    CHGMNG_CHARGING,
    CHGMNG_PULSECHARGING,
    CHGMNG_STOPPING
} CHGMNG_STATE_E;

typedef enum {
    CHGMNG_ADP_UNKNOW,
    CHGMNG_ADP_STANDARD,
    CHGMNG_ADP_NONSTANDARD,
    CHGMNG_ADP_USB,
}
CHGMNG_ADAPTER_TYPE_E;

typedef enum CHGMNG_StopReason_enum {
    CHGMNG_INVALIDREASON = 0,
    CHGMNG_CHARGERUNPLUG = 1,
    CHGMNG_TIMEOUT,
    CHGMNG_VBATEND,
    CHGMNG_CHARGEDONE,
    CHGMNG_OVERVOLTAGE,  //add by paul for charge:over voltage
    CHGMNG_OVERTEMP,
    CHGMNG_PESUDO_CHARGERUNPLUG
} CHGMNG_STOPREASON_E;

typedef enum {
    FILE_SERVICE = 1,               // File service, Reserved
    AUDIO_SERVICE,                  // Audio service
    KEYPAD_SERVICE,                 // Keypad service
    UPM_SERVICE,                    // Udisk service
    CHR_SERVICE,                    // Charge service
    TIME_SERVICE,                   // RTC service
    INTERNAL_USER_SERVICE = 7,		// For MN and such service
    MAX_SERVICE = 256
} SRV_ID_E;
typedef enum {
    // Charge message.
    CHR_CAP_IND = (CHR_SERVICE << 8) | 0x1,  // 0x1,    // Notify the battery's capacity ///test jeremy

    CHR_CHARGE_START_IND,   // start the charge process.
    CHR_CHARGE_END_IND,     // the charge ended.

    CHR_WARNING_IND,        // the capacity is low, should charge.
    CHR_SHUTDOWN_IND,       // the capacity is very low and must shutdown.
#ifdef BATTERY_DETECT_SUPPORT
    CHR_BATTERY_OFF_IND,      // the battery is off
#endif

    CHR_CHARGE_FINISH,      // the charge has been completed.
    CHR_CHARGE_DISCONNECT,  // the charge be disconnect
    CHR_CHARGE_FAULT,       // the charge fault, maybe the voltage of charge is too low.
    CHR_CANCEL_SHUTDOWN_IND,    // battery voltage get normal
    CHR_MSG_MAX_NUM
} CHR_SVR_MSG_SERVICE_E;
typedef struct {
    CHGMNG_STATE_E          chgmng_state;          //charge module state
    uint32                  bat_statistic_vol;          //statistic voltage,
    uint32                  bat_cur_vol;                //current voltage, twinkling value
    uint32                  bat_remain_cap;         //remain battery capacity
    uint32                  charging_current;       //charging current value,reserved
    uint32                  charging_temperature;   ///statistic vbat temperature.
    CHGMNG_ADAPTER_TYPE_E   adp_type;               //adapter type when chargeing,reserved
    CHGMNG_STOPREASON_E     charging_stop_reason;
    uint32                  chg_vol;
} CHGMNG_STATE_INFO_T;

typedef enum GPIO_INT_tag {
    GPIO_INT_DISABLE = 0,   // Disable the relative gpio interrupt.
    GPIO_INT_LEVEL_HIGH,    // detect high level.
    GPIO_INT_LEVEL_LOW,     // detect low level.
    GPIO_INT_EDGES_BOTH,    // detect the rising edges and falling edges.
    GPIO_INT_EDGES_RISING,  // detect the rising edges.
    GPIO_INT_EDGES_FALLING  // detect the falling edges.
}
GPIO_INT_TYPE;
typedef void (* GPIO_CALLBACK)(uint32 gpio_id, uint32 gpio_state);

// Socket state bits
#define SS_NOFDREF          0x0001  /* no file table ref any more */
#define SS_ISCONNECTED      0x0002  /* socket connected to a peer */
#define SS_ISCONNECTING     0x0004  /* in process of connecting to peer */
#define SS_ISDISCONNECTING  0x0008  /*  in process  of disconnecting */
#define SS_CANTSENDMORE     0x0010  /* can't send more data to peer */
#define SS_CANTRCVMORE      0x0020  /* can't receive more data from peer */
#define SS_RCVATMARK        0x0040  /* at mark on input */
#define SS_PRIV             0x0080  /* privileged for broadcast, raw... */
#define SS_NBIO             0x0100  /* non-blocking ops */
#define SS_ASYNC            0x0200  /* async i/o notify */
#define SS_UPCALLED         0x0400  /* zerocopy data has been upcalled (for select) */
#define SS_INUPCALL         0x0800  /* inside zerocopy upcall (reentry guard) */
#define SS_UPCFIN           0x1000  /* inside zerocopy upcall (reentry guard) */
#define SS_WASCONNECTING    0x2000  /* SS_ISCONNECTING w/possible pending error */

// socket error code
// #define ENOBUFS            1
// #define ETIMEDOUT        2
// #define EISCONN            3
// #define EOPNOTSUPP      4
// #define ECONNABORTED    5
// #define EWOULDBLOCK     6
// #define ECONNREFUSED    7
// #define ECONNRESET      8
// #define ENOTCONN        9
// #define EALREADY        10
// #define EINVAL          11
// #define EMSGSIZE        12
// #define EPIPE           13
// #define EDESTADDRREQ    14
// #define ESHUTDOWN       15
// #define ENOPROTOOPT     16
// #define EHAVEOOB        17
// #define ENOMEM          18
// #define EADDRNOTAVAIL   19
// #define EADDRINUSE      20
// #define EAFNOSUPPORT    21
// #define EINPROGRESS     22
// #define ELOWER          23          /* lower layer (IP) error */
// #define ENOTSOCK        24          /* Includes sockets which closed while blocked */
// #define EIEIO           27          /* bad input/output on Old Macdonald's farm :-) */
// #define ETOOMANYREFS    28
// #define EFAULT          29
// #define ENETUNREACH     30

typedef int TCPIP_SOCKET_T;
typedef  unsigned int     TCPIP_IPADDR_T;
typedef  uint32     TCPIP_HOST_HANDLE;          /* async gethostbyname request handle */
typedef int    BOOL;

typedef enum {
    SOCKET_TYPE_TCP = 0,
    SOCKET_TYPE_UDP,
    SOCKET_TYPE_NULL
} SOCKET_TYPE_E;

typedef enum {
    SOCKET_TXDATA = 0, /* get count of bytes in sb_snd */
    SOCKET_RXDATA,     /* get count of bytes in sb_rcv */
    SOCKET_MYADDR,              /* return my IP address */
    SOCKET_OPT_MAX
} SOCKET_OPT_E;

typedef enum {
    PDP_ID0 = 1,
    PDP_ID1,
    PDP_ID2
} PDP_ID_E;

typedef struct {
    unsigned short  port;           /* port number */
    unsigned long   ip_addr;        /* ip address */
} SOCKET_ADDR_S;

typedef struct tm SCI_TM_T;

typedef enum {
    USB_IOCTL_READ_WAITING,
    USB_IOCTL_WRITE_WAITING,
    USB_IOCTL_CLEAN_BUFFER,
    USB_IOCTL_MAX
} USBDrvIoctl_e;


typedef struct {
    uint8 id_num[10];
} MNSIM_ICCID_T;


typedef struct {
    int cur_values;
    int status;
} battery_info_t;


typedef enum {
    MN_DUAL_SYS_1 = 0,
    MN_DUAL_SYS_MAX
} MN_DUAL_SYS_E;

typedef int EPORT_PINx ;

typedef struct tagDigLed {
    EPORT_PINx  cs;
    EPORT_PINx  dio;
    EPORT_PINx  clk;
    uint32_t    bright;

    int (*set_brightness)(struct tagDigLed *obj, int level);
    int (*read)(struct tagDigLed *obj, char *str, uint8_t maxnr);
    int (*write)(struct tagDigLed *obj, uint32_t offset, const char *str);
    int (*write_raw)(struct tagDigLed *obj, uint32_t offset, uint32_t data);
} DigLed_t;

typedef struct tagDigLed *LED_t;

typedef struct sci_fd_set { /* the select socket array manager */
    unsigned        fd_count;       /* how many are SET? */
    long            fd_array[12];   /* an array of SOCKETs, define FD_SETSIZE 12 tcpip internal definition */
} sci_fd_set;

typedef uint8 MN_IMEI_T[MN_MAX_IMEI_LENGTH];

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SYSCALL_DEPEND_H__ */

