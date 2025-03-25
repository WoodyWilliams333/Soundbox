/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app wnetģ��</strong> ��صĽӿ�
	 * @par �ļ�    libwnet.h
	 * @author		yangjing
	 * @date        2020-03-30
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-03-30    | 1.0.0        | yangjing      | �����ļ�
	 * 2022-04-30    | 1.0.1        | lydia         | ����Ӣ��ע�� 
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app wnet </strong>  module
	 * @par file    libwnet.h
	 * @author		yangjing
	 * @date        2020-03-30
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-03-30    | 1.0.0        | yangjing      | create file
	 * 2022-04-30    | 1.0.1        | lydia         | Add English description
 @endif 
*/

/*!
 @if Chinese
	@defgroup libwnet ͨѶ
 @else
	@defgroup libwnet communication 
 @endif
 * @{
*/
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

struct wnet_event_cb_t { 
	int event; 
	int (*cb)(int event, int result);
};

#define wnet_register(event, callback) \
        static const struct wnet_event_cb_t wnet_cb_##callback \
        __attribute_used__ __attribute__((section(".wnet.event.handler"))) = {    \
        event, callback                                                            \
};

typedef enum {
    CHECK_SIM_EVENT                         = 0x00,                         
    CHECK_PPP_EVENT                         = 0x01,                         
} WnetStatus_e;

/**
 @if Chinese
	@brief  ��ö�������г���ͨѶ����.
 @else
	@brief  This enumerated type lists the communication types.
 @endif
  */
typedef enum {
    CT_WIFI                         = 0x01,                         
    CT_GPRS                         = 0x02,                         
    CT_CDMA                         = 0x04,                         
    CT_TCPIP                        = 0x08,                         
    CT_RS232                        = 0x10,                         
    CT_BT                           = 0x20,                         
    CT_MODEM                        = 0x40,                         
    CT_MODEMPPP                     = 0x80,                         
    CT_ALLCOMM                      = 0xFF,                        
} CommType_e;

/**
 @if Chinese
	@brief  ϵͳͨѶģ���ͨ��ѡ��ö��.
 @else
	@brief  communication type.
 @endif
  */
typedef enum {
    CS_GPRS                         = 0x00,                         
    CS_WIFI                         = 0x01,                         
} CommSolt_e;

/**
 @if Chinese
	@brief  ��ö�������г���SSL�汾.
 @else
	@brief  This enumerated type lists the SSL version.
 @endif
  */
typedef enum { 
    SV_TLS_V1_2                     = 0x04, /**< @if Chinese TLS V1.2 @else  TLS V1.2 @endif */
    SV_TLS_V1_3                     = 0x05, /**< @if Chinese TLS V1.3 @else  TLS V1.3 @endif */
} SSLVersion_e;

/**
 @if Chinese
	@brief  ��ö�������г���SSL��֤ģʽ.
 @else
	@brief  This enumerated type lists the SSL authentication mode.
 @endif
  */
typedef enum {
    SVM_VERIFY_NONE                 = 0x00,  /**< @if Chinese SSL���ֺ���֤��У�� @else  ignore SSL certificate verification @endif */      
    SVM_VERIFY_SINGLE               = 0x01,  /**< @if Chinese SSL������֤ @else  SSL single certificate verification @endif */  
    SVM_VERIFY_PEER                 = 0x02,  /**< @if Chinese SSL˫����֤ @else  SSL double certificate verification @endif */
} SSLVerifyMode_e;

/**
 @if Chinese
	@brief  SSL����ģʽ.
 @else
	@brief  SSL debug mode.
 @endif
  */
typedef enum {
    SDM_DEBUG_OFF                   = 0x00,                         
    SDM_DEBUG_ON                    = 0x01,                        
} SSLDebugMode_e;
/**
 @if Chinese
	@brief  ��ö�������г�������ͨѶЭ������.
 @else
	@brief  This enumerated type lists the communication protocol type.
 @endif
  */
typedef enum {
    SOCK_TCP                        = 0x01,                         
    SOCK_UDP                        = 0x02,                         
    SOCK_SSL                        = 0x04 | 0x01,                  
} SockType_e;

/**
 @if Chinese
	@brief  ��ö�������г��˷��ʷ������ķ�ʽ.
 @else
	@brief  This enumerated type lists the method to access the server.
 @endif
  */
typedef enum {
    HOST_IN_IP                      = 0x00,                         
    HOST_IN_DNS                     = 0x01,                               
} HostInType_e;

/**
 @if Chinese
	@brief  ��ö�������г����첽���ӵ�״̬.
 @else
	@brief  This enumerated type lists the status of asynchronous connection.
 @endif
  */
typedef enum {
    // ���ӿ���״̬���ȶ�״̬���յ����Ӷ�����ִ��״̬�л�
    ASYNC_APP_ST_CONNECT_IDLE       = 0x00,  /**< @if Chinese ���ӿ��� @else connect idle @endif */

    // ����״̬�����ȶ�״̬������ʱ�л�
    ASYNC_APP_ST_PPP_CONNECT        = 0x01,  /**< @if Chinese PPP���� @else PPP connect @endif */
    ASYNC_APP_ST_DNS                = 0x02,  /**< @if Chinese DNS�������� @else DNS domain name resolution @endif */ 
    ASYNC_APP_ST_TCP_CONNECT        = 0x03,  /**< @if Chinese TCP���� @else TCP connect @endif */
    ASYNC_APP_ST_SSL_CONNECT        = 0x04,  /**< @if Chinese SSL���� @else SSL connect @endif */

    // ���ӽ���״̬���ȶ�״̬���յ��رն�����ִ��״̬�л�
    ASYNC_APP_ST_CONNECT_FAIL       = 0x05,  /**< @if Chinese ����ʧ�� @else connect fail @endif */
    ASYNC_APP_ST_CONNECT_OK         = 0x06,  /**< @if Chinese ���ӳɹ� @else connect success @endif */
    ASYNC_APP_CONNECT_CLOSE_DONE	= 0x08,	 /**< @if Chinese ������� @else connect complete @endif */
} AsyncConnectStateAPP_e;

/* DNS ����״̬ */
typedef enum {
	ASYNC_DNS_PASER_FAIL				= -1,
	ASYNC_DNS_PASER_OK					= 0,
} AsyncDnsPaserState_e;

//SSL�첽����Ĭ��֧�ֵļ����׼��б�
#define SSL_APP_DEFAULT_CIPHER_LIST     "AES256-SHA:AES128-SHA:DES-CBC3-SHA:AES256-SHA256:AES128-SHA256"
/**< @if Chinese SSL�첽����Ĭ��֧�ֵļ����׼��б� @else default encryption suite for asynchronous connection @endif */

// Ŀǰ��֧�ֵļ����׼��б��Ƽ�Ӧ�ò㲻�����ã�ʹ��Ĭ�ϼ����׼�����
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

// ��֧��IPV4Э��
#define MAX_HOST_CNT                2                               // ���֧��2����������������
#define MAX_IP_CNT                  2                               // 1���������֧�ֽ�����2��ip
#define MAX_IP_LEN                  16                              // 255.255.255.255�����16�ֽ�  
#define MAX_PORT_LEN                6                               // �������˿���󳤶�
#define MAX_HOST_NAME               256                             // ������������ַ��󳤶�
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

/**
 @if Chinese
	@brief  GPRS������ģ�鲦�Ų�������.
 @else
	@brief  the param of wireless dialing.
 @endif
  */
typedef struct {
    char                            apn[MAX_APN_LEN+1];         /**< @if Chinese ���ź��� @else dial number @endif */
    char                            uid[MAX_UID_LEN+1];         /**< @if Chinese �����û�id @else dialing user ID @endif */     
    char                            pwd[MAX_PWD_LEN+1];         /**< @if Chinese �����û����� @else dialing user password @endif */      
    char                            sim_pin[MAX_SIM_PIN_LEN+1]; /**< @if Chinese SIM������ @else SIM card PIN @endif */   
} ST_WIRELESS_PARAM;

/**
 @if Chinese
	@brief  ������������IP�Ͷ˿���Ϣ.
 @else
	@brief  IP and port information of server host.
 @endif
  */
typedef struct {
    char                            ip[MAX_IP_LEN];                 
    char                            port[MAX_PORT_LEN];             
} ST_HOST_IP_PARAM;

/**
 @if Chinese
	@brief  �����������Ĳ�����Ϣ.
 @else
	@brief  the param information of server host.
 @endif
  */
typedef struct {
    char                            name[MAX_HOST_NAME];  /**< @if Chinese ����������ַ @else domain name address @endif */    
    ST_HOST_IP_PARAM                ip_port;              /**< @if Chinese ����IP�Ͷ˿���Ϣ @else IP and port @endif */            
} ST_HOST_PARAM;

/**
 @if Chinese
	@brief  SSLͨѶ�����ò���.
 @else
	@brief  the SSL configuration parameter.
 @endif
  */
typedef struct {
    uint8_t         version;                                    /**< @if Chinese SSLͨѶ�İ汾 @else SSL version @endif */  
    uint8_t         depth;                                      /**< @if Chinese ֤����У��֧�ֵ������� @else maximum depth supported by certificate chain verification @endif */
    uint8_t         mode;                                       /**< @if Chinese SSL���ֵķ�ʽ��������֤��˫����֤ @else SSL handshake method,single or double @endif */    
    uint8_t         debug;                                      /**< @if Chinese �Ƿ���SSL���ԣ�Ϊ1��ʾ�򿪣�Ĭ�Ϲر� @else SSL debug,1 is open, default is close @endif */                                                                                
    const char      cipher_list[MAX_CIPHER_LIST_LEN];           /**< @if Chinese SSL����ָ�������׼���������Ϊ""����ʾʹ��Ĭ�ϼ����׼� @else SSL cipher suite,configurable as "",indicates that the default suite is used @endif */                                                                                     
    const char      ca_cert[MAX_CA_CERT_CNT][MAX_FILE_NAME_LEN]; /**< @if Chinese SSL������Ҫ��CA֤���б�(PEM��ʽ�ı�׼X509֤��,�ļ�ϵͳȫ·��) @else CA certificate list(X509,full path) @endif */                                                                     
    const char      user_cert[MAX_FILE_NAME_LEN];                 /**< @if Chinese �ͻ��˹�Կ֤��(PEM��ʽ�ı�׼X509֤��,�ļ�ϵͳȫ·��) @else client public key(X509,full path) @endif */ 
    const char      user_key[MAX_FILE_NAME_LEN];                  /**< @if Chinese �ͻ���˽Կ�ļ�(�ļ�ϵͳȫ·��) @else client private key(full path) @endif */  
    const char      user_key_pwd[MAX_PWD_LEN];                    /**< @if Chinese �ͻ���˽Կ�ļ�������(����������,�ļ�ϵͳȫ·��) @else client private key password(full path,no password is allowed) @endif */   
} ST_SSL_PARAM;

/**
 @if Chinese
	@brief  �첽���ӵ��������.
 @else
	@brief  the input parameter for asynchronous connection.
 @endif
  */
typedef struct {
    uint32_t                        timeout_ms;          /**< @if Chinese ���ӳ�ʱʱ��(����) @else connect timeout(ms) @endif */ 
    uint8_t                         protocol_type;       /**< @if Chinese ͨѶЭ������(tcp/ssl/udp...) @else communication protocol types(tcp/ssl/udp...) @endif */   
    uint8_t                         dns_ip;              /**< @if Chinese �Ƿ�ʹ���������ʣ�Ϊ1��ʾ������ʽ��Ϊ0��ʾIP��ʽ @else use domain name access,1-DNS,0-IP @endif */     
    ST_WIRELESS_PARAM               wireless;            /**< @if Chinese ���߲��Ų��� @else the param of wireless dialing @endif */
    ST_HOST_PARAM                   host;                /**< @if Chinese �������� @else the param of server host @endif */       
    ST_SSL_PARAM                    ssl;                 /**< @if Chinese SSL���� @else the SSL param @endif */           
} ST_ASYNC_CONNECT_PARAM;

/**
 @if Chinese
	@brief  ϵͳͨѶ��������.
 @else
	@brief  the system communication param.
 @endif
  */
typedef struct {
    uint8_t                         comm_type;           /**< @if Chinese ͨѶ����(wifi/gprs...) @else communication types(wifi/gprs...) @endif */         
    uint8_t                         protocol_type;       /**< @if Chinese ͨѶЭ������(tcp/ssl/udp...) @else communication protocol types(tcp/ssl/udp...)  @endif */              
    uint8_t                         dns_ip;              /**< @if Chinese �Ƿ�ʹ���������ʣ�Ϊ1��ʾ������ʽ��Ϊ0��ʾIP��ʽ @else use domain name access,1-DNS,0-IP @endif */
    uint32_t                        timeout_ms;          /**< @if Chinese ���ӳ�ʱʱ��(����) @else connect timeout(ms) @endif */
    ST_WIRELESS_PARAM               wireless;            /**< @if Chinese ���߲��Ų��� @else the param of wireless dialing @endif */
    ST_HOST_PARAM                   host[MAX_HOST_CNT];  /**< @if Chinese ��������(���2��) @else the param of server host(up to 2 groups) @endif */
    ST_SSL_PARAM                    ssl;                 /**< @if Chinese SSL���� @else the SSL param @endif */
} ST_COMM_CONFIG;

/** ʹ�ýṹ�岻��ȫ����ķ�ʽ��ǰ���壬��Ч����� CommOps_t �ṹ�岻�������������� */
struct _SysCommOps_t;
typedef struct _SysCommOps_t SysCommOps_t;

/**
 @if Chinese
	@brief  ϵͳͨѶ�����ṹ���ڲ�.
 @else
	@brief  the system communication operate structure.
 @endif
  */
typedef struct _CommOps_t {
    const char *                    name;   /**< @if Chinese ͨѶ�������� @else the name of communication type @endif */               
    const uint8_t                   id;     /**< @if Chinese ͨѶ����id @else the id of communication type @endif */                   
    const void *                    udp;    /**< @if Chinese ͨѶʹ�õ�udpЭ��ͨ�� @else UDP protocol channel */                        
    const void *                    tcp;    /**< @if Chinese ͨѶʹ�õ�tcpЭ��ͨ�� @else tcp protocol channel */                    
    const void *                    ssl;    /**< @if Chinese ͨѶʹ�õ�sslЭ��ͨ�� @else ssl protocol channel */                      

	/*!
	 @if Chinese
		@brief		Ԥ���ӣ���GPRS�е�Ԥ���Ų���
		@param[in]	param����������Ϊ	-	ST_WIRELESS_PARAM
		@return		0			-	�ɹ�
		@return		����		-	ʧ��
	 @else
		@brief		pre connection
		@param[in]	param		-	the param from ST_WIRELESS_PARAM
		@return		0			-	success
		@return		other		-	fail
	 @endif
	*/  
    int (*predial)(const void *param); 

	/*!
	 @if Chinese
		@brief		������������
		@param[in]	ops			-	SysCommOps_t
		@param[in]	name		-	��������������ַ
		@param[out]	ip			-	Ӧ����һ����ά���飬���ڴ洢����name���������ip�б�
		@param[out]	ip_cnt		-	����name��������ip����
		@return		0			-	�ɹ�
		@return		����		-	ʧ��
		
	 @else
		@brief		domain name resolution
		@param[in]	ops			-	SysCommOps_t
		@param[in]	name		-	domain name
		@param[out]	ip			-	stores the IP list after the domain name is resolved
		@param[out]	ip_cnt		-	 the IP num after the domain name is resolved
		@return		0			-	success
		@return		other		-	fail
	 @endif
	*/  
    int (*dns)(const SysCommOps_t *ops, const char *name, char ip[MAX_IP_CNT][MAX_IP_LEN], int *ip_cnt);

	/*!
	 @if Chinese
		@brief		����ͨѶ�첽���Ӳ���������PPP����
		@param[in]	ops			-	SysCommOps_t
		@param[in]	param����������Ϊ	-	ST_ASYNC_CONNECT_PARAM
		@return		0			-	�ɹ�
		@return		����		-	ʧ��
	 @else
		@brief		asynchronous connection,include PPP connect
		@param[in]	ops			-	SysCommOps_t
		@param[in]	param		-	the param from ST_ASYNC_CONNECT_PARAM
		@return		0			-	success
		@return		other		-	fail
	 @endif
	*/ 
    int (*async_predial)(const SysCommOps_t *ops, const void *param);
	
	/*!
	 @if Chinese
		@brief 		����ͨѶ�첽���Ӳ���������PPP���ӡ�tcp���ӡ�SSL����(���������SSL)
		@param[in]	ops			-	SysCommOps_t
		@param[in]	param����������Ϊ	-	ST_ASYNC_CONNECT_PARAM
		@return		0			-	�ɹ�
		@return		����		-	ʧ��
	 @else
		@brief		asynchronous connection,include PPP��TCP��SSL connect
		@param[in]	ops			-	SysCommOps_t
		@param[in]	param		-	the param from ST_ASYNC_CONNECT_PARAM
		@return		0			-	success
		@return		other		-	fail
	 @endif
	*/  
    int (*async_connect)(const SysCommOps_t *ops, const void *param);

	/*!
	 @if Chinese
		@brief		����ͨѶ�첽���ӹرղ���
		@param[in]	ops			-	SysCommOps_t
		@return		0			-	�ɹ�
		@return		����		-	ʧ��
	 @else
		@brief		asynchronous connection,close connect
		@param[in]	ops			-	SysCommOps_t
		@return		0			-	success
		@return		other		-	fail
	 @endif
	*/    
    int (*async_disconnect)(const SysCommOps_t *ops);
    
	/*!
	 @if Chinese
		@brief		����ͨѶ�첽����״̬��ѯ,����PPP���ӡ�tcp���ӡ�SSL����(���������SSL)
		@param[in]	ops			-	SysCommOps_t
		@param[out]	fd			-	���ص���ЧͨѶ���ͨ��fd���ݳ�ȥ���˾����������ͨѶ�շ�����
		@param[out]	ip			-	���������������ɹ��󷵻ص�IP�б������1��IP
		@param[out]	ip_cnt		-	����name��������ip����
		@param[in]	wait		-	��waitΪ��0ʱ����ʾ����ʽ��ѯ
		@return:    ����״̬������AsyncConnectStateAPP_e
	 @else
		@brief		asynchronous connection��check status,include PPP��TCP��SSL connect
		@param[in]	ops			-	SysCommOps_t
		@param[out]	fd			-	communication handle
		@param[out]	ip			-	stores the IP list after the domain name is resolved��only have one IP
		@param[out]	ip_cnt		-	the IP num after the domain name is resolved
		@param[in]	wait		-	if wait is not 0��blocking check
		@return	    connect status��reference AsyncConnectStateAPP_e
	 @endif
	*/    
    int (*async_state_chk)(const SysCommOps_t *ops, int *fd, char ip[MAX_IP_CNT][MAX_IP_LEN], int *ip_cnt, int wait);

	/*!
	 @if Chinese
		@brief		����ͨѶ�첽����״̬��ѯ,����PPP����
		@return     ����״̬������AsyncConnectStateAPP_e
	 @else
		@brief		asynchronous connection��check status,include PPP
		@return     connect status��reference AsyncConnectStateAPP_e
	 @endif
	*/      
	int (*async_ppp_state_chk)(void);

	/*!
	 @if Chinese
		@brief		DNS���������ѯ
		@return     app_true/app_false
	 @else
		@brief		check dns paser result
		@return     app_true/app_false
	 @endif
	*/
	int (*async_dns_paser_chk)(void);

	/*!
	 @if Chinese
		@brief		����ͨѶͬ�����Ӳ���������tcp���ӻ�SSL����(���������SSL) 
		@param[in]	ops			-	SysCommOps_t
		@param[out]	rfd			-	���ص���ЧͨѶ������˾����������ͨѶ�շ�����
		@param[in]	host		-	IP�Ͷ˿ڣ�ST_HOST_IP_PARAM�ṹ��
		@param[in]	ssl			-	ssl������ST_SSL_PARAM�ṹ��
		@param[in]	timeout_ms	-	��ʱʱ��
		@return		>=0		-	�ɹ������
		@return		<0		-	ʧ��
	 @else
		@brief		synchronous connection��include TCP��SSL connect
		@param[in]	ops			-	SysCommOps_t
		@param[out]	rfd			-	communication handle
		@param[in]	host		-	IP and port,struct ST_HOST_IP_PARAM
		@param[in]	ssl			-	ssl param��struct  ST_SSL_PARAM
		@param[in]	timeout_ms	-	timeout
		@return		>=0	-	success,communication handle
		@return		<0	-	fail
	 @endif
	*/      
    int (*connect)(const SysCommOps_t *ops, int *rfd, const void *host, const void *ssl, int timeout_ms);

	/*!
	 @if Chinese
		@brief		����ͨѶ���ݷ��Ͳ���
		@param[in]	ops			-	SysCommOps_t
		@param[in]	host		-	IP�Ͷ˿ڣ�ST_HOST_IP_PARAM�ṹ��
		@param[in]	fd			-	connect��async_state_chk��ȡ����Чfd
		@param[in]	buf			-	Ӧ�÷������ݵĻ�����
		@param[in]	count		-	�������ݵĳ���
		@param[in]	timeout_ms	-	Ӧ�÷������ݳ�ʱʱ�䣬��λΪ����
		@return		>=0		-	�ɹ����ѷ������ݵĳ���
		@return		<0		-	ʧ��
	 @else
		@brief		Send data in TCP
		@param[in]	ops			-	SysCommOps_t
		@param[in]	host		-	IP and port,struct ST_HOST_IP_PARAM
		@param[in]	fd			-	valid socket handle by connect or async_state_chk
		@param[in]	buf			-	Buffer storing data to send
		@param[in]	count		-	Data length
		@param[in]	timeout_ms	-	timeout(ms)
		@return		>=0		-	success,length of sent data
		@return		<0		-	fail
	 @endif
	*/      
    int (*write)(const SysCommOps_t *ops, const void *host, int fd, const void *buf, int count, int timeout_ms);

	/*!
	 @if Chinese
		@brief		����ͨѶ���ݽ��ղ���
		@param[in]	ops			-	SysCommOps_t
		@param[in]	fd			-	connect��async_state_chk��ȡ����Чfd
		@param[out]	buf			-	Ӧ�ý������ݵĻ�����
		@param[in]	count		-	�����������ݵĳ���
		@param[in]	timeout_ms	-	Ӧ�ý������ݳ�ʱʱ�䣬��λΪ����
		@return		>=0		-	�ɹ����ѽ������ݵĳ���
		@return		<0		-	ʧ��
	 @else
		@brief		receive data in TCP
		@param[in]	ops			-	SysCommOps_t
		@param[in]	fd			-	valid socket handle by connect or async_state_chk
		@param[out]	buf			-	Buffer storing data to receive
		@param[in]	count		-	The expected length of string will be received
		@param[in]	timeout_ms	-	timeout(ms)
		@return		>=0		-	success,length of received data
		@return		<0		-	fail
	 @endif
	*/        
    int (*read)(const SysCommOps_t *ops, int fd, void *buf, int count, int timeout_ms);

	/*!
	 @if Chinese
		@brief		��ȡsocketͨѶ�Ĳ�������
		@param[in]	ops			-	SysCommOps_t
		@param[in]	fd			-	connect��async_state_chk��ȡ����Чfd
		@param[in]	level		-	ѡ���Ĳ�Σ�֧��SOL_SOCKET
		@param[in]	optname		-	���ȡ��ѡ��
		@param[out]	optval		-	ָ�룬ָ����ѡ���ȡ������ֵ�Ļ�����
		@param[out]	optlen		-	optval����������
		@return		0		-	�ɹ�
		@return		����	-	ʧ��
	 @else
		@brief		get the parameter operation of socket communication
		@param[in]	ops			-	SysCommOps_t
		@param[in]	fd			-	valid socket handle by connect or async_state_chk
		@param[in]	level		-	hierarchy of option definitions��support SOL_SOCKET
		@param[in]	optname		-	options to be get
		@param[out]	optval		-	obtained value
		@param[out]	optlen		-	optval length
		@return		0		-	success
		@return		other	-	fail
	 @endif
	*/          
    int (*getsockopt)(const SysCommOps_t *ops, int fd, int level, int optname, void *optval, int *optlen);

	/*!
	 @if Chinese
		@brief		����socketͨѶ�Ĳ�������
		@param[in]	ops			-	SysCommOps_t
		@param[in]	fd			-	connect��async_state_chk��ȡ����Чfd
		@param[in]	level		-	ѡ���Ĳ�Σ�֧��SOL_SOCKET
		@param[in]	optname		-	�����õ�ѡ��
		@param[in]	optval		-	ָ�룬�����õ�ֵ
		@param[in]	optlen		-	optval����������
		@return		0		-	�ɹ�
		@return		����	-	ʧ��
	 @else
		@brief		set the parameter operation of socket communication
		@param[in]	ops			-	SysCommOps_t
		@param[in]	fd			-	valid socket handle by connect or async_state_chk
		@param[in]	level		-	hierarchy of option definitions��support SOL_SOCKET
		@param[in]	optname		-	options to be set
		@param[in]	optval		-	value to be set
		@param[in]	optlen		-	optval length
		@return		0		-	success
		@return		other	-	fail
	 @endif
	*/     
    int (*setsockopt)(const SysCommOps_t *ops, int fd, int level, int optname, const void *optval, int optlen);

	/*!
	 @if Chinese
		@brief		ͨѶ�رղ����������ǹر�ϵͳ���
		@param[in]	ops			-	SysCommOps_t
		@param[in]	fd			-	connect��async_state_chk��ȡ����Чfd
		@return		0		-	�ɹ�
		@return		����	-	ʧ��
	 @else
		@brief		the communication closing operation is only to close the system handle
		@param[in]	ops			-	SysCommOps_t
		@param[in]	fd			-	valid socket handle by connect or async_state_chk
		@return		0		-	success
		@return		other	-	fail
	 @endif
	*/       
    int (*close)(const SysCommOps_t *ops, int fd);   

	/*!
	 @if Chinese
		@brief		ͨѶ�˳���������GPRS�е�ppp logout����
		@param[in]	arg			-	NULL
		@return		0			-	�ɹ�
		@return		����		-	ʧ��
	 @else
		@brief		communication exit,as GPRS ppp logout
		@param[in]	arg			-	NULL
		@return		0			-	success
		@return		other		-	fail
	 @endif
	*/  
    int (*exit)(const void *arg);   
} CommOps_t;

/**
 @if Chinese
	@brief  ϵͳͨѶ�����ṹ��(����).
 @else
	@brief  the system communication operate structure(external).
 @endif
  */
typedef struct _SysCommOps_t {
    const void *                    protocol;     /**< @if Chinese ͨѶЭ������(tcp/ssl/udp...) @else communication protocol types(tcp/ssl/udp...)  @endif */
    const CommOps_t *               comm;         /**< @if Chinese ͨѶ�����ӿ� @else communication operation interface  @endif */
} SysCommOps_t;

/** extern APIS */

/*!
 @if Chinese
	@brief		Ӧ��ͨѶ������ʼ��(����ȡӦ��ͨѶ�Ĳ�������)
	@param[in]	comm_type		-	ͨѶ���ͱ�ţ���CT_WIFI/CT_GPRS ...
	@param[in]	protocol_type	-	����ͨѶЭ�����ͣ���SOCK_TCP/SOCK_SSL/SOCK_UDP
	@param[out]	ops				-	Ӧ��ͨѶ�����Ķ���ָ�� 
	@return		!NULL	-	�ɹ�,Ӧ��ͨѶ�����Ķ���ָ�� 
	@return		NULL	-	ʧ��
 @else
	@brief		communication operation initialization
	@param[in]	comm_type		-	communication types,CT_WIFI/CT_GPRS ...
	@param[in]	protocol_type	-	communication protocol types(tcp/ssl/udp...)
	@param[out]	ops				-	object point to communication operation
	@return		!NULL	-	success,object point to communication operation
	@return		NULL	-	fail
 @endif
*/   
extern SysCommOps_t *wnet_comm_ops_init(uint8_t comm_type, uint8_t protocol_type, SysCommOps_t *ops);

/*!
 @if Chinese
	@brief		����wnet�����־���أ�Ĭ���������־�رյ�
	@param[in]	on			-	�����õ���־����״̬����0��ʾ�򿪣�Ϊ0��ʾ�رգ��� LOGGER_MODULE_ON ö�ٶ���
	@return		0				-	�ɹ�
	@return		����			-	ʧ��
 @else
	@brief		set the log switch of the wnet library. the log is off by default
	@param[in]	on			-	 0:close;!0:open
	@return		0				-	success
	@return		other			-	fail
		
 @endif
*/   
extern int wnet_logger_on(int on);
/*!
 @if Chinese
	@brief		��ȡlibwnet��İ汾��Ϣ
	@param[out]	version			-	libwnet��İ汾��Ϣ���
	@param[in]	size			-	versionִ�е�buffer���ȣ���������64�ֽ�
	@return		0				-	�ɹ�
	@return		����			-	ʧ��
 @else
	@brief		get libwent version information
	@param[out]	version			-	version information
	@param[in]	size			-	 the version length,At least 64 bytes are recommended
	@return		0				-	success
	@return		other			-	fail
		
 @endif
*/   
extern int wnet_get_version(char *version, int size);

/*!
 @if Chinese
	@brief		ֹͣ�ն��첽�߳� 
	@return		0				-	�ɹ�
	@return		����			-	ʧ��
 @else
	@brief		stop asynchronous thread
	@return		0				-	success
	@return		other			-	fail
	
 @endif
*/ 
extern int async_thread_stop(void);

//PPP��ʱʱ�䣬pppTimeout�����䷶Χ��10-60�����粻���������������PPP��ʱʱ��Ĭ��30��
/*!
 @if Chinese
	@brief		����PPP��ʱʱ�䣬pppTimeout�����䷶Χ��10-60�����粻���������������PPP��ʱʱ��Ĭ��30��
	@param[in]	pppTimeout		-	PPP��ʱʱ��
 @else
	@brief		set PPP timeout[10s-60s],default 30s
	@param[in]	pppTimeout		-	 PPP timeout(s)
 @endif
*/   
extern void gprs_set_ppp_timeout(uint8_t pppTimeout);

#ifdef __cplusplus
}
#endif

#endif


