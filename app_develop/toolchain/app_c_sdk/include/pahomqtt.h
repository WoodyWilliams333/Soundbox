/*
 * @Description: 
 * @Author: YangJing
 * @Date: 2019-11-11 09:23:06
 * @LastEditors: YangJing
 * @LastEditTime: 2021-05-11 16:06:08
 */
#ifndef _PAHO_MQTT_H_
#define _PAHO_MQTT_H_

#ifndef MIN_VERSION_LEN
#define MIN_VERSION_LEN             64                  // 获取版本信息的buffer最少长度
#endif

#define MAX_TOPIC_NUM 10

typedef void* MqttObj;

enum Mqtt_QoS { Mqtt_QOS0, Mqtt_QOS1, Mqtt_QOS2, Mqtt_SUBFAIL=0x80 };

enum Ssl_Mode { 
	MQTT_SSL_NOUSED = 0,        // 不使用SSL
	MQTT_SSL_VERIFY_NONE,       // SSL不验证方式
	MQTT_SSL_VERIFY_SINGLE,     // SSL单向验证
	MQTT_SSL_VERIFY_PEER        // SSL双向验证
};

typedef struct{
	enum Mqtt_QoS qos;		        
	char* clientid;         
	char* username;
	char* password;

	char *topic[MAX_TOPIC_NUM];     // 订阅主题
	int heartbeat_sec;              // 保活时间
	int clean_session;          
}mqtt_protocol_t;

typedef struct{
	const char *addr;
	int port;

    // ssl参数
	enum Ssl_Mode sslmode;
	char *cacert[3];
	char *usercert;
	char *userkey;
	char *userpw;
}mqtt_server_t;

typedef enum {
	E_MQTT_UNSTART = -1,    // 未启动服务
	E_MQTT_IDEL = 0,        // 空闲状态，下一步自动进入连接
	E_MQTT_CONNECTING,      // 正在连接MQTT服务
	E_MQTT_CONNECTED,       // 已连接MQTT服务
	E_MQTT_YIELD,           // MQTT事务监测
    E_MQTT_DISCONNECTED,    // MQTT服务断开
    E_MQTT_RELEASE,         // MQTT释放
    E_MQTT_WAIT_CMD         // MQTT已停止，命令等待
}E_MQTT_STATUS;

/*
mqtt服务启动参数结构
check_net_ok 
	描述：
		网络检查回调函数，如PPP是否连接，wifi热点连接
		只有网络正常才会建立MQTT连接。
	返回：
		 0 - 网络未连接好 
		 1 - 网络已连接好
recv_message_proc
	描述：
		接收到MQTT推送消息处理回调函数
	参数：
	 	msg [in] 接收的消息数据
	 	msg_len 接收的消息长度
notify_mqtt_action
    描述：
        MQTT状态变更回调
    参数：
        status【in] 当前MQTT状态，详见E_MQTT_STATUS
        code   [in] 执行结果
        para   [in] 状态数据，暂无用
*/
typedef struct{
    int (*check_net_ok)(void);
 	void (*recv_message_proc)(void *msg, int msg_len, const char* topic); 
	void (*notify_mqtt_action)(int status, int code, void *para);   
    int (*get_keepAliveInterval)(void);
	//int (*play_mqtt_status_proc)(E_MQTT_STATUS status);
	//int (*check_ack_fail)(char *content);
	//void (*reboot_net_server)(void);
	mqtt_protocol_t protocol;       // MQTT协议参数
	mqtt_server_t sever;            // 服务端参数
    int use_default_msg_handler;	//是否使用默认消息处理句柄，即mqttctx->c->defaultMessageHandler，0-不使用，1-使用
}mqtt_param_t;


typedef struct {
    void (*succ)(void *para);
    void (*fail)(int errcode, void *para);
} mqtt_result_t;

/**
* @brief 创建并启动MQTT
* @param[in]  mqttpara 详见mqtt_param_t结构描述
* @return 执行结果
*	-<em> 非NULL  </em>  MQTT实例，不代表MQTT连接成功
*	-<em> NULL </em>  实例创建失败
*/
extern MqttObj StartMqttService(mqtt_param_t *mqttpara);


/**
 * @brief: 停止MQTT服务，MQTT实例将释放
 * @param[in] MqttObj MQTT实例
 * @param[out] 
 * @return
 *	-<em> == 0  </em>  成功
 *	-<em> == -1 </em>  失败
 */
//extern int StopMqttService(MqttObj obj);

/**
* @brief QTT发布
* @param[in] obj MQTT实例
* @param[in] qos 服务质量，MQTT消息参数之一
* @param[in] topicName 发布主题   
* @param[in]  message 发布内容 
* @return 锟斤拷取锟侥斤拷锟?
*	-<em> == 0  </em>  锟缴癸拷
*	-<em> == -1 </em>  失锟斤拷
*/
extern int AppMQTTPublish(MqttObj obj, int qos, const char* topicName, char* message);

/**
* @brief 获取MQTT状态
* @param[in] obj MQTT实例
* @return 获取到的状态
*	参考E_MQTT_STATUS
*/
extern E_MQTT_STATUS AppGetMQTTStatus(MqttObj mqttObj);

/**
* @brief MQTT断开链路
* @param[in]  obj MQTT实例
* @return 执行结果
*	-<em> == 0  </em>  成功
*	-<em> == -1 </em>  失败
*/
extern int AppMQTTDisconnect(MqttObj mqttObj, int closeMqtt);

/**
* @brief 库日志开关
* @param[in] on	0-关 非0-开
* @return 
*	-<em> 0 </em>  success
*	-<em> 非0 </em>	 failed
*/
extern int pahomqtt_logger_on(int on);

/**
* @brief 获取liblotsdk库的版本信息
* @param[out] version，liblotsdk库的版本信息输出   
* @param[in]  size，version执行的buffer长度，建议至少64字节
* @return 获取的结果
*	-<em> == 0  </em>  成功
*	-<em> == -1 </em>  失败
*/
extern int pahomqtt_get_version(char *version, int size);

extern int AppMQTTReconnect(MqttObj obj);
#endif
