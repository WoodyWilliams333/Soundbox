
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

/* ϵͳͨѶ����ö�٣���ʹ��Ƶ�ʴӸߵ��͵ķ�ʽ���� */
typedef enum {
    CT_WIFI                         = 0x01,                         // WIFIͨѶ
    CT_GPRS                         = 0x02,                         // GPRSͨѶ
    CT_CDMA                         = 0x04,                         // CDMAͨѶ
    CT_TCPIP                        = 0x08,                         // TCP/IPͨѶ
    CT_RS232                        = 0x10,                         // RS232/UARTͨѶ
    CT_BT                           = 0x20,                         // BLUETOOTHͨѶ
    CT_MODEM                        = 0x40,                         // ModemͨѶ
    CT_MODEMPPP                     = 0x80,                         // ModemPPPͨѶ
    CT_ALLCOMM                      = 0xFF,                         // ���е�ͨѶ����
} CommType_e;

/** ϵͳͨѶģ���ͨ��ѡ��ö�� */
typedef enum {
    CS_GPRS                         = 0x00,                         // ����ͨѶʹ��GPRSͨ��
    CS_WIFI                         = 0x01,                         // ����ͨѶʹ��WIFIͨ��
} CommSolt_e;

/** SSL�İ汾ö�� */
typedef enum {
    SV_SSL_V2_3                     = 0x00,                         // SSLv23_method (SSL3.0 but can rollback to v2), //factually is TLS1.2
    SV_SSL_V3_0                     = 0x01,                         // SSLv3_client_method (SSL V3.0) //The SSLv3 protocol is deprecated.
    SV_TLS_V1_0                     = 0x02,                         // TLSv1_client_method (TLS V1.0)
    SV_TLS_V1_1                     = 0x03,                         // TLSv1_1_client_method (TLS V1.1) //default 
    SV_TLS_V1_2                     = 0x04,                         // TLSv1_2_client_method (TLS V1.2)
    SV_TLS_V1_3                     = 0x05,                         // TLSv1_3_client_method (TLS V1.3) //reserved !!!
} SSLVersion_e;

/** SSL��֤ģʽ */
typedef enum {
    SVM_VERIFY_NONE                 = 0x00,                         // SSL���ֺ���֤��У��
    SVM_VERIFY_SINGLE               = 0x01,                         // SSL������֤
    SVM_VERIFY_PEER                 = 0x02,                         // SSL˫����֤
} SSLVerifyMode_e;

/** SLL����ģʽ*/
typedef enum {
    SDM_DEBUG_OFF                   = 0x00,                         // SSL���Թر�
    SDM_DEBUG_ON                    = 0x01,                         // SSL���Դ�
} SSLDebugMode_e;

/** ����ͨѶЭ������ö�� */
typedef enum {
    SOCK_TCP                        = 0x01,                         // TCPͨѶ
    SOCK_UDP                        = 0x02,                         // UDPͨѶ
    SOCK_SSL                        = 0x04 | 0x01,                  // SSLͨѶ
} SockType_e;

/** ���ʷ������ķ�ʽö�� */
typedef enum {
    HOST_IN_IP                      = 0x00,                         // IP��ʽ����
    HOST_IN_DNS                     = 0x01,                         // DNS��ʽ(������ʽ)����        
} HostInType_e;

/** �첽���ӵ�״̬ö��(APP) */
typedef enum {
    // ���ӿ���״̬���ȶ�״̬���յ����Ӷ�����ִ��״̬�л�
    ASYNC_APP_ST_CONNECT_IDLE       = 0x00,                         // ���ӿ���

    // ����״̬�����ȶ�״̬������ʱ�л�
    ASYNC_APP_ST_PPP_CONNECT        = 0x01,                         // PPP����
    ASYNC_APP_ST_DNS                = 0x02,                         // DNS��������
    ASYNC_APP_ST_TCP_CONNECT        = 0x03,                         // TCP����
    ASYNC_APP_ST_SSL_CONNECT        = 0x04,                         // SSL����

    // ���ӽ���״̬���ȶ�״̬���յ��رն�����ִ��״̬�л�
    ASYNC_APP_ST_CONNECT_FAIL       = 0x05,                         // ����ʧ��
    ASYNC_APP_ST_CONNECT_OK         = 0x06,                         // ���ӳɹ�
    ASYNC_APP_CONNECT_CLOSE_DONE	= 0x08,							// ���ӹر����
} AsyncConnectStateAPP_e;

//SSL�첽����Ĭ��֧�ֵļ����׼��б�
#define SSL_APP_DEFAULT_CIPHER_LIST     "AES256-SHA:AES128-SHA:DES-CBC3-SHA:AES256-SHA256:AES128-SHA256"

/** Ŀǰ��֧�ֵļ����׼��б��Ƽ�Ӧ�ò㲻�����ã�ʹ��Ĭ�ϼ����׼����� */
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

/** ��֧��IPV4Э�� */
#define MAX_HOST_CNT                2                               // ���֧��2����������������
#define MAX_IP_CNT                  2                               // 1���������֧�ֽ�����2��ip
#define MAX_IP_LEN                  16                              // 255.255.255.255�����16�ֽ�  
#define MAX_PORT_LEN                6                               // �������˿���󳤶�
#define MAX_HOST_NAME               48                              // ������������ַ��󳤶�
#define MAX_SIM_PIN_LEN             16                              // SIM����PIN��󳤶�
#define MAX_PWD_LEN                 16                              // SIM����PWD��󳤶�
#define MAX_UID_LEN                 64                              // SIM����UID��󳤶�
#define MAX_APN_LEN                 64                              // SIM����APN��󳤶�
#define MAX_SSL_CERT_DEPTH          5                               // ���֧��5��֤������У��
#define MAX_CIPHER_LIST_LEN         64                              // �ַ�����ʽ�ļ����׼�����󳤶�
#define MAX_CA_CERT_CNT             3                               // ���֧��3��CA֤������
#define MAX_FILE_NAME_LEN           48                              // �ļ�ȫ·���ַ�����󳤶�
#define MAX_PWD_LEN                 16                              // PEM�ļ��������󳤶�
#define MIN_VERSION_LEN             64                              // ��ȡ�汾��Ϣ��buffer���ٳ���

/** GPRS������ģ�鲦�Ų������� */
typedef struct {
    char                            apn[MAX_APN_LEN];               // ���ź��� CDMA: #777; GPRS: cmnet
    char                            uid[MAX_UID_LEN];               // �����û�id
    char                            pwd[MAX_PWD_LEN];               // �����û�����
    char                            sim_pin[MAX_SIM_PIN_LEN];       // SIM card PIN   
} ST_WIRELESS_PARAM;

/** ������������IP�Ͷ˿���Ϣ */
typedef struct {
    char                            ip[MAX_IP_LEN];                 // ����ip��ַ
    char                            port[MAX_PORT_LEN];             // �����˿�  
} ST_HOST_IP_PARAM;

/** �����������Ĳ�����Ϣ */
typedef struct {
    char                            name[MAX_HOST_NAME];            // ����������ַ 
    ST_HOST_IP_PARAM                ip_port;                        // ����IP�Ͷ˿���Ϣ 
} ST_HOST_PARAM;

/** SSLͨѶ�����ò��� */
typedef struct {
    uint8_t         version;                                        // SSLͨѶ�İ汾
    uint8_t         depth;                                          // ֤����У��֧�ֵ�������
    uint8_t         mode;                                           // SSL���ֵķ�ʽ��������֤��˫����֤
    uint8_t         debug;                                          // �Ƿ���SSL���ԣ�Ϊ1��ʾ�򿪣�Ĭ�Ϲر�                                                                                                                                      
    const char      cipher_list[MAX_CIPHER_LIST_LEN];               // SSL����ָ�������׼���������Ϊ""����ʾʹ��Ĭ�ϼ����׼�                                                                                   
    const char      ca_cert[MAX_CA_CERT_CNT][MAX_FILE_NAME_LEN];    // SSL������Ҫ��CA֤���б� (PEM��ʽ�ı�׼X509֤��) [�ļ�ϵͳȫ·��]                                                                        
    const char      user_cert[MAX_FILE_NAME_LEN];                   // �ͻ��˹�Կ֤�� (PEM��ʽ�ı�׼X509֤��) [�ļ�ϵͳȫ·��]
    const char      user_key[MAX_FILE_NAME_LEN];                    // �ͻ���˽Կ�ļ� (PEM��ʽ) [�ļ�ϵͳȫ·��]
    const char      user_key_pwd[MAX_PWD_LEN];                      // �ͻ���˽Կ�ļ������� (����������) [�ļ�ϵͳȫ·��]
} ST_SSL_PARAM;

/** �첽���ӵ�������� */
typedef struct {
    uint32_t                        timeout_ms;                     // ���ӳ�ʱʱ�䣬��λ�Ǻ���
    uint8_t                         protocol_type;                  // ͨѶЭ������(tcp/ssl/udp...)
    uint8_t                         dns_ip;                         // �Ƿ�ʹ���������ʣ�Ϊ1��ʾ������ʽ��Ϊ0��ʾIP��ʽ
    ST_WIRELESS_PARAM               wireless;                       // ���߲��Ų���
    ST_HOST_PARAM                   host;                           // ��������
    ST_SSL_PARAM                    ssl;                            // SSL����
} ST_ASYNC_CONNECT_PARAM;

/** ϵͳͨѶ�������� */
typedef struct {
    uint8_t                         comm_type;                      // ͨѶ����(wifi/gprs/cdma...)
    uint8_t                         protocol_type;                  // ͨѶЭ������(tcp/ssl/udp...)
    uint8_t                         dns_ip;                         // �Ƿ�ʹ���������ʣ�Ϊ1��ʾ������ʽ��Ϊ0��ʾIP��ʽ
    uint32_t                        timeout_ms;                     // ���ͳ�ʱʱ�䣬��λ: ����
    ST_WIRELESS_PARAM               wireless;                       // ���߲��Ų���
    ST_HOST_PARAM                   host[MAX_HOST_CNT];             // ��������������2��
    ST_SSL_PARAM                    ssl;                            // SSL����
} ST_COMM_CONFIG;

/** ʹ�ýṹ�岻��ȫ����ķ�ʽ��ǰ���壬��Ч����� CommOps_t �ṹ�岻�������������� */
struct _SysCommOps_t;
typedef struct _SysCommOps_t SysCommOps_t;

/** ϵͳͨѶ�����ṹ���ڲ� */
typedef struct _CommOps_t {
    const char *                    name;                           /** ͨѶ�������� */
    const uint8_t                   id;                             /** ͨѶ����id */
    const void *                    udp;                            /** ͨѶʹ�õ�udpЭ��ͨ�� */
    const void *                    tcp;                            /** ͨѶʹ�õ�tcpЭ��ͨ�� */
    const void *                    ssl;                            /** ͨѶʹ�õ�sslЭ��ͨ�� */

    /** 
      * Ԥ���ӣ���GPRS�е�Ԥ���Ų��� 
      * param����������Ϊ: ST_WIRELESS_PARAM
      */
    int (*predial)(const void *param); 

    /**
      * ������������
      * name: ��������������ַ
      * ip: Ӧ����һ����ά���飬���ڴ洢����name���������ip�б�
      * ip_cnt: ����name��������ip����
      */
    int (*dns)(const SysCommOps_t *ops, const char *name, char ip[MAX_IP_CNT][MAX_IP_LEN], int *ip_cnt);

	/** 
      * ����ͨѶ�첽���Ӳ���������PPP����
      * param����������Ϊ: ST_ASYNC_CONNECT_PARAM
      */
    int (*async_predial)(const SysCommOps_t *ops, const void *param);
	
    /** 
      * ����ͨѶ�첽���Ӳ���������PPP���ӡ�tcp���ӡ�SSL����(���������SSL)
      * param����������Ϊ: ST_ASYNC_CONNECT_PARAM
      * ---- �첽��������ʹ��IP��ʽ����DNS��ʽ���ɲ���connect�ӿڵ����˵��
      */
    int (*async_connect)(const SysCommOps_t *ops, const void *param);

    /** 
      * ����ͨѶ�첽���ӹرղ��� 
      */
    int (*async_disconnect)(const SysCommOps_t *ops);

    /** 
      * ����ͨѶ�첽����״̬��ѯ��
      * fd: ���ص���ЧͨѶ���ͨ��fd���ݳ�ȥ���˾����������ͨѶ�շ�����
      * ip: �첽�������������ɹ��󷵻ص�IP�б������2��IP
      * wait: ��waitΪ��0ʱ����ʾ����ʽ��ѯ 
      */
    int (*async_state_chk)(const SysCommOps_t *ops, int *fd, char ip[MAX_IP_CNT][MAX_IP_LEN], int *ip_cnt, int wait);

	
	/** 
	  * ����ͨѶ�첽����״̬��ѯ��
	  * fd: ���ص���ЧͨѶ���ͨ��fd���ݳ�ȥ���˾����������ͨѶ�շ�����
	  * ip: �첽�������������ɹ��󷵻ص�IP�б������2��IP
	  * wait: ��waitΪ��0ʱ����ʾ����ʽ��ѯ 
	  */
	int (*async_ppp_state_chk)(void);
	
    /** 
      * ����ͨѶͬ�����Ӳ���������tcp���ӻ�SSL����(���������SSL) 
      * host����������Ϊ: ST_HOST_IP_PARAM
      * ---- ���ӿڽ�����IP��ʽ������������Ӧ�ò���Ҫʹ��������ʽ��������ʱ��
      * ---- Ӧ����Ӧ�ò������DNS������IPִ������
      * ssl����������Ϊ: ST_SSL_PARAM��������ҪTCPͨѶʱ����ֵ�ɴ���NULL
      * timeout_msΪͨѶ���ӳ�ʱʱ�䣬��λΪ����
      */
    int (*connect)(const SysCommOps_t *ops, const void *host, const void *ssl, int timeout_ms);

    /** 
      * ����ͨѶ���ݷ��Ͳ��� 
      * host����������Ϊ: ST_HOST_IP_PARAM��һ��ʹ��UDPͨѶʱ����Ҫ����
      * fdΪconnect��async_state_chk��ȡ����Чfd
      * bufΪӦ�÷������ݵĻ�����
      * countӦ�÷������ݵĳ���
      * timeout_msΪӦ�÷������ݳ�ʱʱ�䣬��λΪ����
      */
    int (*write)(const SysCommOps_t *ops, const void *host, int fd, const void *buf, int count, int timeout_ms);

    /** 
      * ����ͨѶ���ݽ��ղ���
      * fdΪconnect��async_state_chk��ȡ����Чfd
      * bufΪӦ�ý������ݵĻ�����
      * countӦ�ý������ݵ���󳤶ȣ���ֵҲ��buf��Ӧ�洢�ռ�Ĵ�С
      * timeout_msΪӦ�ý������ݳ�ʱʱ�䣬��λΪ����
      */
    int (*read)(const SysCommOps_t *ops, int fd, void *buf, int count, int timeout_ms);

    /** 
      * ����socketͨѶ�Ĳ�������
      * fdΪconnect��async_state_chk��ȡ����Чfd      
      * levelΪѡ���Ĳ�Σ�֧��SOL_SOCKET
      * optname�������õ�ѡ�
      * optval��ָ�룬ָ����ѡ������õ���ֵ�Ļ�������
      * optlen��optval����������
      * ע��: ����ر�֤���ڴ���
      */
    int (*getsockopt)(const SysCommOps_t *ops, int fd, int level, int optname, void *optval, int *optlen);

    /** 
      * ����ͨѶ���ݽ��ղ���
      * fdΪconnect��async_state_chk��ȡ����Чfd
      * bufΪӦ�ý������ݵĻ�����
      * levelΪѡ���Ĳ�Σ�֧��SOL_SOCKET
      * optname�����ȡ��ѡ�
      * optval��ָ�룬ָ����ѡ�����ȡֵ�Ļ�������
      * optlen��optval����������
      * ע��: ����ر�֤���ڴ���
      */
    int (*setsockopt)(const SysCommOps_t *ops, int fd, int level, int optname, const void *optval, int optlen);

    /** 
      * ͨѶ�رղ����������ǹر�ϵͳ��� 
      * fdΪconnect��async_state_chk��ȡ����Чfd
      */
    int (*close)(const SysCommOps_t *ops, int fd);   

    /** 
      * ͨѶ�˳���������GPRS�е�ppp logout���� 
      */
    int (*exit)(const void *arg);   
    
} CommOps_t;

/** ϵͳͨѶ�����ṹ��(����) */
typedef struct _SysCommOps_t {
    const void *                    protocol;                       /** ͨѶʹ�õ�Э��ͨ������ѡ����: tcp/udp/ssl ... */
    const CommOps_t *               comm;                           /** ͨѶ�����ӿ� */
} SysCommOps_t;

/** extern APIS */

/**
* @brief Ӧ��ͨѶ������ʼ��(����ȡӦ��ͨѶ�Ĳ�������)
* @param[in] comm_type      ͨѶ���ͱ�ţ���CT_WIFI/CT_GPRS ...
* @param[in] protocol_type  ����ͨѶЭ�����ͣ���SOCK_TCP/SOCK_SSL/SOCK_UDP
* @return Ӧ��ͨѶ�����Ķ���ָ��
*	-<em> != NULL </em>  success
*	-<em> == NULL </em>	 failed
*/
extern SysCommOps_t *wnet_comm_ops_init(uint8_t comm_type, uint8_t protocol_type, SysCommOps_t *ops);

/**
* @brief ����wnet�����־���أ�Ĭ���������־�رյ�
* @param[in] on     �����õ���־����״̬����0��ʾ�򿪣�Ϊ0��ʾ�رգ��� LOGGER_MODULE_ON ö�ٶ���
* @return ���ú����־����״̬
*	-<em> != 0 </em>  logger on
*	-<em> == 0 </em>  logger off
*/
extern int wnet_logger_on(int on);

/**
* @brief ��ȡlibwnet��İ汾��Ϣ
* @param[out] version��libwnet��İ汾��Ϣ���   
* @param[in]  size��versionִ�е�buffer���ȣ���������64�ֽ�    
* @return ��ȡ�Ľ��
*	-<em> == 0  </em>  �ɹ�
*	-<em> == -1 </em>  ʧ��
*/
extern int wnet_get_version(char *version, int size);


/**
* @brief �ն��첽�߳�  
* @return ��ȡ�Ľ��
*	-<em> == 0  </em>  �ɹ�
*	-<em> == -1 </em>  ʧ��
*/
extern int async_thread_stop(void);

#ifdef __cplusplus
}
#endif

#endif


