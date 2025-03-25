/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app uart模块</strong> 相关的接口
	 * @par 文件    appuart.h
	 * @author		yangjing
	 * @date        2020-04-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-04-09    | 1.0.0        | yanjing       | 创建文件
	 * 2022-04-27    | 1.0.1        | wenming       | 增加英文注释  
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app uart </strong>  module
	 * @par file    appuart.h
	 * @author		yangjing
	 * @date        2020-04-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-04-09    | 1.0.0        | yanjing       | create file
	 * 2022-04-27    | 1.0.1        | wenming       | Add English description
 @endif 
*/
/**
 @if Chinese
	* @addtogroup app_uart 串口
 @else 
	* @addtogroup app_uart uart
 @endif 
 * @{
*/

#ifndef _APP_UART_H_
#define _APP_UART_H_

/*!
@if Chinese
  * @brief  该枚举类型列出了串口执行错误状态定义.
@else  
  * @brief  This enumerated type lists the serial port execution error status definition.
@endif
*/
typedef enum{
	UART_OK = 0,
	UART_OPEN_FAILED = -1,		/**<@if Chinese 串口打开失败 @else	Serial port opening failure	@endif*/
	UART_SEND_FAILED = -2,		/**<@if Chinese 串口发送失败 @else	Serial port sending failure	@endif*/
	UART_SEND_TIMEOUT = -3,		/**<@if Chinese 串口发送超时 @else	Serial port sending Timeout	@endif*/
	UART_RECV_FAILED = -4,		/**<@if Chinese 串口接收失败 @else	Serial port receiving failure	@endif*/
	UART_RECV_TIMEOUT = -5,		/**<@if Chinese 串口接收超时 @else	Serial port receiving Timeout	@endif*/
	UART_CLOSE_FAIELD = -6,		/**<@if Chinese 串口关闭失败 @else	Serial port Shutdown failure	@endif*/
	UART_FAILED = -7			/**<@if Chinese 串口操作失败，未知错误 @else	Serial port operation failed. Unknown error	@endif*/
}E_UART_ERR;

#ifndef UART_DEV_NAME
#define UART_DEV_NAME   "/dev/ttyUSB0"		/**<@if Chinese  定义串口设备名称的宏 @else	A macro that defines the name of a serial port device	@endif*/
#endif


typedef void (*pRecvBlockCallBack)(void *);

/**
@if Chinese
 * @brief  打开串口
 * @param[in]	port		-	串口设备名称，目前仅支持UART_DEV_NAME
 * @return  参考E_UART_ERR定义
@else 
 * @brief  Open port
 * @param[in]	port		-	Name of the serial port device. Currently, only UART_DEV_NAME is supported
 * @return  See E_UART_ERR definition
@endif 
 */
extern int app_uart_open(const char *port);

/**
@if Chinese
 * @brief  关闭串口
 * @param[in]	fd			-	串口设备描述符
 * @return  参考E_UART_ERR定义
@else 
 * @brief  Close port
 * @param[in]	fd			-	Serial port device descriptor
 * @return  See E_UART_ERR definition
@endif 
 */
extern int app_uart_close(int fd);

/**
@if Chinese
 * @brief  串口配置，仅保留，无实际用途,采用虚拟串口，自动匹配，不需要设置参数
@else 
 * @brief  Serial port configuration, reserved only, no practical use, use the virtual serial port, automatic matching, do not need to set parameters
@endif 
 */
extern int app_uart_config(int fd, int baud, int bits, char parity, int stop);

/**
@if Chinese
 * @brief  串口发送数据
 * @param[in]	fd			-	串口设备描述符
 * @param[in]	pdata		-	发送数据指针
 * @param[in]	len			-	发送数据长度
 * @param[in]	mstimeout	-	发送超时时间(ms)
 * @return  参考E_UART_ERR定义
@else 
 * @brief  Serial port sending data
 * @param[in]	fd			-	Serial port device descriptor
 * @param[in]	pdata		-	Send data pointer
 * @param[in]	len			-	Length of send data
 * @param[in]	mstimeout	-	Send timeout (ms)
 * @return  See E_UART_ERR definition
@endif 
 */
extern int app_uart_send(int fd, uint8_t *pdata, int len, int mstimeout);

/**
@if Chinese
 * @brief  串口接收数据
 * @param[in]	fd			-	串口设备描述符
 * @param[in]	mstimeout	-	发送超时时间(ms)
 * @param[in]	len			-	期望接收数据长度
 * @param[in]	cbfc		-	接收阻塞回调
 * @param[in]	cbparam		-	接收阻塞回调参数
 * @param[out]	pdata		-	接收数据保存地址
 * @return  参考E_UART_ERR定义
@else 
 * @brief  Serial port receiving data
 * @param[in]	fd			-	Serial port device descriptor
 * @param[in]	mstimeout	-	Send timeout (ms)
 * @param[in]	len			-	Length of data expected to be received
 * @param[in]	cbfc		-	Receive blocking callback
 * @param[in]	cbparam		-	Receives blocking callback parameters
 * @param[out]	pdata		-	Storage address for receiving data
 * @return  See E_UART_ERR definition
@endif 
 */
extern int app_uart_recv(int fd, uint8_t *pdata, int len, int mstimeout,
	pRecvBlockCallBack cbfc, void *cbparam);


/**
@if Chinese
 * @brief	清空串口缓存
@else 
 * @brief	Clearing serial Port Cache
@endif 
 */
extern int app_uart_clear_buff(int fd);

#endif


