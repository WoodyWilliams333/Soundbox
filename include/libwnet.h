
#ifndef __LIBWNET_H__
#define __LIBWNET_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <sys/socket.h>

#ifndef MAYBE_UNUSE
#define MAYBE_UNUSE(x)              (void)(x)
#endif

#ifndef UNUSE
#define UNUSE(x)                    (void)(x)
#endif

#ifndef __attribute_used__
#define __attribute_used__          __attribute__((__used__))
#endif

/* 系统通讯类型枚举，按使用频率从高到低的方式排列 */
typedef enum {
    CT_WIFI                         = 0x01,                         // WIFI通讯
    CT_GPRS                         = 0x02,                         // GPRS通讯
    CT_CDMA                         = 0x04,                         // CDMA通讯
    CT_TCPIP                        = 0x08,                         // TCP/IP通讯
    CT_RS232                        = 0x10,                         // RS232/UART通讯
    CT_BT                           = 0x20,                         // BLUETOOTH通讯
    CT_MODEM                        = 0x40,                         // Modem通讯
    CT_MODEMPPP                     = 0x80,                         // ModemPPP通讯
    CT_ALLCOMM                      = 0xFF,                         // 所有的通讯类型
} CommType_e;

/** 系统通讯模块的通道选择枚举 */
typedef enum {
    CS_GPRS                         = 0x00,                         // 无线通讯使用GPRS通道
    CS_WIFI                         = 0x01,                         // 无线通讯使用WIFI通道
} CommSolt_e;

/** SSL的版本枚举 */
typedef enum {
    SV_SSL_V2_3                     = 0x00,                         // SSLv23_method (SSL3.0 but can rollback to v2), //factually is TLS1.2
    SV_SSL_V3_0                     = 0x01,                         // SSLv3_client_method (SSL V3.0) //The SSLv3 protocol is deprecated.
    SV_TLS_V1_0                     = 0x02,                         // TLSv1_client_method (TLS V1.0)
    SV_TLS_V1_1                     = 0x03,                         // TLSv1_1_client_method (TLS V1.1) //default 
    SV_TLS_V1_2                     = 0x04,                         // TLSv1_2_client_method (TLS V1.2)
    SV_TLS_V1_3                     = 0x05,                         // TLSv1_3_client_method (TLS V1.3) //reserved !!!
} SSLVersion_e;

/** SSL认证模式 */
typedef enum {
    SVM_VERIFY_NONE                 = 0x00,                         // SSL握手忽略证书校验
    SVM_VERIFY_SINGLE               = 0x01,                         // SSL单向认证
    SVM_VERIFY_PEER                 = 0x02,                         // SSL双向认证
} SSLVerifyMode_e;

/** SLL调试模式*/
typedef enum {
    SDM_DEBUG_OFF                   = 0x00,                         // SSL调试关闭
    SDM_DEBUG_ON                    = 0x01,                         // SSL调试打开
} SSLDebugMode_e;

/** 网络通讯协议类型枚举 */
typedef enum {
    SOCK_TCP                        = 0x01,                         // TCP通讯
    SOCK_UDP                        = 0x02,                         // UDP通讯
    SOCK_SSL                        = 0x04 | 0x01,                  // SSL通讯
} SockType_e;

/** 访问服务器的方式枚举 */
typedef enum {
    HOST_IN_IP                      = 0x00,                         // IP方式访问
    HOST_IN_DNS                     = 0x01,                         // DNS方式(域名方式)访问        
} HostInType_e;

/** 异步连接的状态枚举(APP) */
typedef enum {
    // 连接空闲状态，稳定状态，收到连接动作会执行状态切换
    ASYNC_APP_ST_CONNECT_IDLE       = 0x00,                         // 连接空闲

    // 连接状态，不稳定状态，会随时切换
    ASYNC_APP_ST_PPP_CONNECT        = 0x01,                         // PPP连接
    ASYNC_APP_ST_DNS                = 0x02,                         // DNS域名解析
    ASYNC_APP_ST_TCP_CONNECT        = 0x03,                         // TCP连接
    ASYNC_APP_ST_SSL_CONNECT        = 0x04,                         // SSL连接

    // 连接结束状态，稳定状态，收到关闭动作会执行状态切换
    ASYNC_APP_ST_CONNECT_FAIL       = 0x05,                         // 连接失败
    ASYNC_APP_ST_CONNECT_OK         = 0x06,                         // 连接成功
    ASYNC_APP_CONNECT_CLOSE_DONE	= 0x08,							// 连接关闭完成
} AsyncConnectStateAPP_e;

//SSL异步连接默认支持的加密套件列表
#define SSL_APP_DEFAULT_CIPHER_LIST     "AES256-SHA:AES128-SHA:DES-CBC3-SHA:AES256-SHA256:AES128-SHA256"

/** 目前可支持的加密套件列表，推荐应用层不做设置，使用默认加密套件即可 */
#if 0
"Cur version support 53 cipher:"
"RC4-SHA"
"RC4-MD5"
"DES-CBC3-SHA"
"AES128-SHA"
"AES256-SHA"
"NULL-SHA"
"NULL-SHA256"
"DHE-RSA-AES128-SHA"
"DHE-RSA-AES256-SHA"
"DHE-PSK-AES256-GCM-SHA384"
"DHE-PSK-AES128-GCM-SHA256"
"DHE-PSK-AES256-CBC-SHA384"
"DHE-PSK-AES128-CBC-SHA256"
"DHE-PSK-NULL-SHA384"
"DHE-PSK-NULL-SHA256"
"ECDHE-RSA-AES128-SHA"
"ECDHE-RSA-AES256-SHA"
"ECDHE-ECDSA-AES128-SHA"
"ECDHE-ECDSA-AES256-SHA"
"ECDHE-RSA-RC4-SHA"
"ECDHE-RSA-DES-CBC3-SHA"
"ECDHE-ECDSA-RC4-SHA"
"ECDHE-ECDSA-DES-CBC3-SHA"
"AES128-SHA256"
"AES256-SHA256"
"DHE-RSA-AES128-SHA256"
"DHE-RSA-AES256-SHA256"
"AES128-GCM-SHA256"
"AES256-GCM-SHA384"
"DHE-RSA-AES128-GCM-SHA256"
"DHE-RSA-AES256-GCM-SHA384"
"ECDHE-RSA-AES128-GCM-SHA256"
"ECDHE-RSA-AES256-GCM-SHA384"
"ECDHE-ECDSA-AES128-GCM-SHA256"
"ECDHE-ECDSA-AES256-GCM-SHA384"
"ECDHE-RSA-AES128-SHA256"
"ECDHE-ECDSA-AES128-SHA256"
"ECDHE-RSA-AES256-SHA384"
"ECDHE-ECDSA-AES256-SHA384"
"ECDHE-RSA-CHACHA20-POLY1305"
"ECDHE-ECDSA-CHACHA20-POLY1305"
"DHE-RSA-CHACHA20-POLY1305"
"ECDHE-RSA-CHACHA20-POLY1305-OLD"
"ECDHE-ECDSA-CHACHA20-POLY1305-OLD"
"DHE-RSA-CHACHA20-POLY1305-OLD"
"IDEA-CBC-SHA"
"ECDHE-ECDSA-NULL-SHA"
"ECDHE-PSK-NULL-SHA256"
"ECDHE-PSK-AES128-CBC-SHA256"
"PSK-CHACHA20-POLY1305"
"ECDHE-PSK-CHACHA20-POLY1305"
"DHE-PSK-CHACHA20-POLY1305"
"EDH-RSA-DES-CBC3-SHA"
#endif

/** 仅支持IPV4协议 */
#define MAX_HOST_CNT                2                               // 最多支持2个服务器主机参数
#define MAX_IP_CNT                  2                               // 1个域名最多支持解析出2个ip
#define MAX_IP_LEN                  16                              // 255.255.255.255，最多16字节  
#define MAX_PORT_LEN                6                               // 服务器端口最大长度
#define MAX_HOST_NAME               48                              // 服务器域名地址最大长度
#define MAX_SIM_PIN_LEN             16                              // SIM卡的PIN最大长度
#define MAX_PWD_LEN                 16                              // SIM卡的PWD最大长度
#define MAX_UID_LEN                 64                              // SIM卡的UID最大长度
#define MAX_APN_LEN                 64                              // SIM卡的APN最大长度
#define MAX_SSL_CERT_DEPTH          5                               // 最多支持5级证书链的校验
#define MAX_CIPHER_LIST_LEN         64                              // 字符串形式的加密套件的最大长度
#define MAX_CA_CERT_CNT             3                               // 最多支持3组CA证书输入
#define MAX_FILE_NAME_LEN           48                              // 文件全路径字符串最大长度
#define MAX_PWD_LEN                 16                              // PEM文件密码的最大长度
#define MIN_VERSION_LEN             64                              // 获取版本信息的buffer最少长度

/** GPRS等无线模块拨号参数配置 */
typedef struct {
    char                            apn[MAX_APN_LEN];               // 拨号号码 CDMA: #777; GPRS: cmnet
    char                            uid[MAX_UID_LEN];               // 拨号用户id
    char                            pwd[MAX_PWD_LEN];               // 拨号用户密码
    char                            sim_pin[MAX_SIM_PIN_LEN];       // SIM card PIN   
} ST_WIRELESS_PARAM;

/** 服务器主机的IP和端口信息 */
typedef struct {
    char                            ip[MAX_IP_LEN];                 // 主机ip地址
    char                            port[MAX_PORT_LEN];             // 主机端口  
} ST_HOST_IP_PARAM;

/** 服务器主机的参数信息 */
typedef struct {
    char                            name[MAX_HOST_NAME];            // 主机域名地址 
    ST_HOST_IP_PARAM                ip_port;                        // 主机IP和端口信息 
} ST_HOST_PARAM;

/** SSL通讯的配置参数 */
typedef struct {
    uint8_t         version;                                        // SSL通讯的版本
    uint8_t         depth;                                          // 证书链校验支持的最大深度
    uint8_t         mode;                                           // SSL握手的方式，单向认证或双向认证
    uint8_t         debug;                                          // 是否开启SSL调试，为1表示打开，默认关闭                                                                                                                                      
    const char      cipher_list[MAX_CIPHER_LIST_LEN];               // SSL握手指定加密套件，可配置为""，表示使用默认加密套件                                                                                   
    const char      ca_cert[MAX_CA_CERT_CNT][MAX_FILE_NAME_LEN];    // SSL握手需要的CA证书列表 (PEM格式的标准X509证书) [文件系统全路径]                                                                        
    const char      user_cert[MAX_FILE_NAME_LEN];                   // 客户端公钥证书 (PEM格式的标准X509证书) [文件系统全路径]
    const char      user_key[MAX_FILE_NAME_LEN];                    // 客户端私钥文件 (PEM格式) [文件系统全路径]
    const char      user_key_pwd[MAX_PWD_LEN];                      // 客户端私钥文件的密码 (可以无密码) [文件系统全路径]
} ST_SSL_PARAM;

/** 异步连接的输入参数 */
typedef struct {
    uint32_t                        timeout_ms;                     // 连接超时时间，单位是毫秒
    uint8_t                         protocol_type;                  // 通讯协议类型(tcp/ssl/udp...)
    uint8_t                         dns_ip;                         // 是否使用域名访问，为1表示域名方式，为0表示IP方式
    ST_WIRELESS_PARAM               wireless;                       // 无线拨号参数
    ST_HOST_PARAM                   host;                           // 主机参数
    ST_SSL_PARAM                    ssl;                            // SSL参数
} ST_ASYNC_CONNECT_PARAM;

/** 系统通讯参数配置 */
typedef struct {
    uint8_t                         comm_type;                      // 通讯类型(wifi/gprs/cdma...)
    uint8_t                         protocol_type;                  // 通讯协议类型(tcp/ssl/udp...)
    uint8_t                         dns_ip;                         // 是否使用域名访问，为1表示域名方式，为0表示IP方式
    uint32_t                        timeout_ms;                     // 发送超时时间，单位: 毫秒
    ST_WIRELESS_PARAM               wireless;                       // 无线拨号参数
    ST_HOST_PARAM                   host[MAX_HOST_CNT];             // 主机参数，最多存2组
    ST_SSL_PARAM                    ssl;                            // SSL参数
} ST_COMM_CONFIG;

/** 使用结构体不完全定义的方式提前定义，有效解决了 CommOps_t 结构体不能引用它的问题 */
struct _SysCommOps_t;
typedef struct _SysCommOps_t SysCommOps_t;

/** 系统通讯操作结构体内部 */
typedef struct _CommOps_t {
    const char *                    name;                           /** 通讯类型名称 */
    const uint8_t                   id;                             /** 通讯类型id */
    const void *                    udp;                            /** 通讯使用的udp协议通道 */
    const void *                    tcp;                            /** 通讯使用的tcp协议通道 */
    const void *                    ssl;                            /** 通讯使用的ssl协议通道 */

    /** 
      * 预连接，像GPRS中的预拨号操作 
      * param的完整类型为: ST_WIRELESS_PARAM
      */
    int (*predial)(const void *param); 

    /**
      * 域名解析操作
      * name: 服务器的域名地址
      * ip: 应传入一个二维数组，用于存储域名name被解析后的ip列表
      * ip_cnt: 域名name解析出的ip个数
      */
    int (*dns)(const SysCommOps_t *ops, const char *name, char ip[MAX_IP_CNT][MAX_IP_LEN], int *ip_cnt);

	/** 
      * 网络通讯异步连接操作，包括PPP连接
      * param的完整类型为: ST_ASYNC_CONNECT_PARAM
      */
    int (*async_predial)(const SysCommOps_t *ops, const void *param);
	
    /** 
      * 网络通讯异步连接操作，包括PPP连接、tcp连接、SSL连接(如果配置了SSL)
      * param的完整类型为: ST_ASYNC_CONNECT_PARAM
      * ---- 异步连接主机使用IP方式还是DNS方式，可参照connect接口的入参说明
      */
    int (*async_connect)(const SysCommOps_t *ops, const void *param);

    /** 
      * 网络通讯异步连接关闭操作 
      */
    int (*async_disconnect)(const SysCommOps_t *ops);

    /** 
      * 网络通讯异步连接状态查询，
      * fd: 返回的有效通讯句柄通过fd传递出去，此句柄可以用于通讯收发操作
      * ip: 异步连接域名解析成功后返回的IP列表，最多有2个IP
      * wait: 当wait为非0时，表示阻塞式查询 
      */
    int (*async_state_chk)(const SysCommOps_t *ops, int *fd, char ip[MAX_IP_CNT][MAX_IP_LEN], int *ip_cnt, int wait);

	
	/** 
	  * 网络通讯异步连接状态查询，
	  * fd: 返回的有效通讯句柄通过fd传递出去，此句柄可以用于通讯收发操作
	  * ip: 异步连接域名解析成功后返回的IP列表，最多有2个IP
	  * wait: 当wait为非0时，表示阻塞式查询 
	  */
	int (*async_ppp_state_chk)(void);
	
    /** 
      * 网络通讯同步连接操作，包括tcp连接或SSL连接(如果配置了SSL) 
      * host的完整类型为: ST_HOST_IP_PARAM
      * ---- 本接口仅采用IP方式连接主机，当应用层需要使用域名方式连接主机时，
      * ---- 应先由应用层解析完DNS，传入IP执行连接
      * ssl的完整类型为: ST_SSL_PARAM，当仅需要TCP通讯时，此值可传递NULL
      * timeout_ms为通讯连接超时时间，单位为毫秒
      */
    int (*connect)(const SysCommOps_t *ops, const void *host, const void *ssl, int timeout_ms);

    /** 
      * 网络通讯数据发送操作 
      * host的完整类型为: ST_HOST_IP_PARAM；一般使用UDP通讯时，需要传入
      * fd为connect或async_state_chk获取的有效fd
      * buf为应用发送数据的缓存区
      * count应用发送数据的长度
      * timeout_ms为应用发送数据超时时间，单位为毫秒
      */
    int (*write)(const SysCommOps_t *ops, const void *host, int fd, const void *buf, int count, int timeout_ms);

    /** 
      * 网络通讯数据接收操作
      * fd为connect或async_state_chk获取的有效fd
      * buf为应用接收数据的缓存区
      * count应用接收数据的最大长度，此值也是buf对应存储空间的大小
      * timeout_ms为应用接收数据超时时间，单位为毫秒
      */
    int (*read)(const SysCommOps_t *ops, int fd, void *buf, int count, int timeout_ms);

    /** 
      * 设置socket通讯的参数操作
      * fd为connect或async_state_chk获取的有效fd      
      * level为选项定义的层次；支持SOL_SOCKET
      * optname：需设置的选项。
      * optval：指针，指向存放选项待设置的新值的缓冲区。
      * optlen：optval缓冲区长度
      * 注意: 请务必保证是在创建
      */
    int (*getsockopt)(const SysCommOps_t *ops, int fd, int level, int optname, void *optval, int *optlen);

    /** 
      * 网络通讯数据接收操作
      * fd为connect或async_state_chk获取的有效fd
      * buf为应用接收数据的缓存区
      * level为选项定义的层次；支持SOL_SOCKET
      * optname：需获取的选项。
      * optval：指针，指向存放选项待获取值的缓冲区。
      * optlen：optval缓冲区长度
      * 注意: 请务必保证是在创建
      */
    int (*setsockopt)(const SysCommOps_t *ops, int fd, int level, int optname, const void *optval, int optlen);

    /** 
      * 通讯关闭操作，仅仅是关闭系统句柄 
      * fd为connect或async_state_chk获取的有效fd
      */
    int (*close)(const SysCommOps_t *ops, int fd);   

    /** 
      * 通讯退出操作，像GPRS中的ppp logout操作 
      */
    int (*exit)(const void *arg);   
    
} CommOps_t;

/** 系统通讯操作结构体(对外) */
typedef struct _SysCommOps_t {
    const void *                    protocol;                       /** 通讯使用的协议通道，可选项有: tcp/udp/ssl ... */
    const CommOps_t *               comm;                           /** 通讯操作接口 */
} SysCommOps_t;

/** extern APIS */

/**
* @brief 应用通讯操作初始化(仅获取应用通讯的操作方法)
* @param[in] comm_type      通讯类型编号，如CT_WIFI/CT_GPRS ...
* @param[in] protocol_type  网络通讯协议类型，如SOCK_TCP/SOCK_SSL/SOCK_UDP
* @return 应用通讯操作的对象指针
*	-<em> != NULL </em>  success
*	-<em> == NULL </em>	 failed
*/
extern SysCommOps_t *wnet_comm_ops_init(uint8_t comm_type, uint8_t protocol_type, SysCommOps_t *ops);

/**
* @brief 设置wnet库的日志开关，默认情况是日志关闭的
* @param[in] on     欲设置的日志开关状态，非0表示打开，为0表示关闭，见 LOGGER_MODULE_ON 枚举定义
* @return 设置后的日志开关状态
*	-<em> != 0 </em>  logger on
*	-<em> == 0 </em>  logger off
*/
extern int wnet_logger_on(int on);

/**
* @brief 获取libwnet库的版本信息
* @param[out] version，libwnet库的版本信息输出   
* @param[in]  size，version执行的buffer长度，建议至少64字节    
* @return 获取的结果
*	-<em> == 0  </em>  成功
*	-<em> == -1 </em>  失败
*/
extern int wnet_get_version(char *version, int size);


/**
* @brief 终端异步线程  
* @return 获取的结果
*	-<em> == 0  </em>  成功
*	-<em> == -1 </em>  失败
*/
extern int async_thread_stop(void);

#ifdef __cplusplus
}
#endif

#endif


