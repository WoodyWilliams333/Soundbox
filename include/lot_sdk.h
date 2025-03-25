#ifndef _SDK_INCLUDE_H_
#define _SDK_INCLUDE_H_

#ifndef MIN_VERSION_LEN
#define MIN_VERSION_LEN             64                  // 获取版本信息的buffer最少长度
#endif


/*
mqtt服务启动参数结构
check_net_ok 
	描述：
		网络检查回调函数，如PPP连接，wifi热点连接。可以实现ppp连接，以便异常时重连ppp
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

char topic[256] 
	描述：
		订阅的主题
*/
typedef struct{
	int (*check_net_ok)(void);		//
	void (*recv_message_proc)(void *msg, int msg_len); //
	//int (*check_cancel_wait_msg)(void);
	char topic[256];
	char *productkey;
	char *devname;
	char *devsercetkey;
}mqtt_serv_param_t;


/**
* @brief 库日志开关
* @param[in] on	0-关 非0-开
* @return 
*	-<em> 0 </em>  success
*	-<em> 非0 </em>	 failed
*/
extern int lotsdk_logger_on(int on);

/**
* @brief 获取liblotsdk库的版本信息
* @param[out] version，liblotsdk库的版本信息输出   
* @param[in]  size，version执行的buffer长度，建议至少64字节    
* @return 获取的结果
*	-<em> == 0  </em>  成功
*	-<em> == -1 </em>  失败
*/
extern int lotsdk_get_version(char *version, int size);

/**
* @brief 启动MQTT服务线程  
* @param[in]  servpara 详见mqtt_serv_param_t结构描述
* @return 执行结果
*	-<em> == 0  </em>  成功
*	-<em> == -1 </em>  失败
*/
extern int StartMqttService(mqtt_serv_param_t *servpara);


#endif
