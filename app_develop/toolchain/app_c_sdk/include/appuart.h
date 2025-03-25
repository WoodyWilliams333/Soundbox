/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app uartģ��</strong> ��صĽӿ�
	 * @par �ļ�    appuart.h
	 * @author		yangjing
	 * @date        2020-04-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-04-09    | 1.0.0        | yanjing       | �����ļ�
	 * 2022-04-27    | 1.0.1        | wenming       | ����Ӣ��ע��  
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
	* @addtogroup app_uart ����
 @else 
	* @addtogroup app_uart uart
 @endif 
 * @{
*/

#ifndef _APP_UART_H_
#define _APP_UART_H_

/*!
@if Chinese
  * @brief  ��ö�������г��˴���ִ�д���״̬����.
@else  
  * @brief  This enumerated type lists the serial port execution error status definition.
@endif
*/
typedef enum{
	UART_OK = 0,
	UART_OPEN_FAILED = -1,		/**<@if Chinese ���ڴ�ʧ�� @else	Serial port opening failure	@endif*/
	UART_SEND_FAILED = -2,		/**<@if Chinese ���ڷ���ʧ�� @else	Serial port sending failure	@endif*/
	UART_SEND_TIMEOUT = -3,		/**<@if Chinese ���ڷ��ͳ�ʱ @else	Serial port sending Timeout	@endif*/
	UART_RECV_FAILED = -4,		/**<@if Chinese ���ڽ���ʧ�� @else	Serial port receiving failure	@endif*/
	UART_RECV_TIMEOUT = -5,		/**<@if Chinese ���ڽ��ճ�ʱ @else	Serial port receiving Timeout	@endif*/
	UART_CLOSE_FAIELD = -6,		/**<@if Chinese ���ڹر�ʧ�� @else	Serial port Shutdown failure	@endif*/
	UART_FAILED = -7			/**<@if Chinese ���ڲ���ʧ�ܣ�δ֪���� @else	Serial port operation failed. Unknown error	@endif*/
}E_UART_ERR;

#ifndef UART_DEV_NAME
#define UART_DEV_NAME   "/dev/ttyUSB0"		/**<@if Chinese  ���崮���豸���Ƶĺ� @else	A macro that defines the name of a serial port device	@endif*/
#endif


typedef void (*pRecvBlockCallBack)(void *);

/**
@if Chinese
 * @brief  �򿪴���
 * @param[in]	port		-	�����豸���ƣ�Ŀǰ��֧��UART_DEV_NAME
 * @return  �ο�E_UART_ERR����
@else 
 * @brief  Open port
 * @param[in]	port		-	Name of the serial port device. Currently, only UART_DEV_NAME is supported
 * @return  See E_UART_ERR definition
@endif 
 */
extern int app_uart_open(const char *port);

/**
@if Chinese
 * @brief  �رմ���
 * @param[in]	fd			-	�����豸������
 * @return  �ο�E_UART_ERR����
@else 
 * @brief  Close port
 * @param[in]	fd			-	Serial port device descriptor
 * @return  See E_UART_ERR definition
@endif 
 */
extern int app_uart_close(int fd);

/**
@if Chinese
 * @brief  �������ã�����������ʵ����;,�������⴮�ڣ��Զ�ƥ�䣬����Ҫ���ò���
@else 
 * @brief  Serial port configuration, reserved only, no practical use, use the virtual serial port, automatic matching, do not need to set parameters
@endif 
 */
extern int app_uart_config(int fd, int baud, int bits, char parity, int stop);

/**
@if Chinese
 * @brief  ���ڷ�������
 * @param[in]	fd			-	�����豸������
 * @param[in]	pdata		-	��������ָ��
 * @param[in]	len			-	�������ݳ���
 * @param[in]	mstimeout	-	���ͳ�ʱʱ��(ms)
 * @return  �ο�E_UART_ERR����
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
 * @brief  ���ڽ�������
 * @param[in]	fd			-	�����豸������
 * @param[in]	mstimeout	-	���ͳ�ʱʱ��(ms)
 * @param[in]	len			-	�����������ݳ���
 * @param[in]	cbfc		-	���������ص�
 * @param[in]	cbparam		-	���������ص�����
 * @param[out]	pdata		-	�������ݱ����ַ
 * @return  �ο�E_UART_ERR����
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
 * @brief	��մ��ڻ���
@else 
 * @brief	Clearing serial Port Cache
@endif 
 */
extern int app_uart_clear_buff(int fd);

#endif


