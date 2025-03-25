/**
 @if Chinese
 * @brief  ��ģ���������� <strong>��ӡ��ģ��</strong> ��صĽӿ�
 * @note   ��ӡ����صĽӿ�
 *
 *
 *
 * @version 1.0.1
 * @remarks        Change History:
 * ����          | ����            | ����
 * ------------- | --------------- | ----
 * 2010/07/14    | Li.Hua          | �����ļ�
 * 2022/04/20    | Wenming         | ����Ӣ��ע��
 @else 
 * @brief  This module is used to describe <strong>Printer</strong> interfaces module
 * @note   Printer related interfaces
 *
 *
 *
 * @version 1.0.1
 * @remarks        Change History:
 * Date          | Author          | Desc
 * ------------- | --------------- | ----
 * 2010/07/14    | Li.Hua          | Create file
 * 2022/04/20    | Wenming         | Add English description
 @endif
*/


/**
 @if Chinese
 * @defgroup printer ��ӡ��
 @else 
 * @defgroup printer Printer
 @endif 
 * @{
*/
// caution, doxygen defgroup header and footer and been both auto generated!!!

/******************************************************************************
 * printer.h
 *
 * Copyright (c) 2010 by Li.Hua <lihua_338@163.com>.
 *
 * DESCRIPTION: -
 *
 * Modification history
 * ----------------------------------------------------------------------------
 * Date         Version  Author       History
 * ----------------------------------------------------------------------------
 * 2010-07-14   1.0.0    Li.Hua       written
 ******************************************************************************/

#ifndef LINUX_PRINTER_H
#define LINUX_PRINTER_H

#include <stdint.h>
#include <stdlib.h>
#include "sys/ioctl.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
@if Chinese
 * @brief ��ӡ�������ṹ
 * @note
 *  ro_xxxx :�ò���ֻ�ܶ��������޸�
 *  rw_xxxx :�ò����ɶ�д
@else
 * @brief Printer parameter structure
 * @note
 *  ro_xxxx : read only
 *  rw_xxxx : read write
@endif 
 */
typedef struct printer_param {
    uint32_t        ro_width;           /**<@if Chinese ��ӡ��� 				@else	Print width									@endif*/
    uint32_t        ro_bits_per_pixel;  /**<@if Chinese һ�������ö���λ��ʾ 	@else	How many bits are used to represent a pixel	@endif*/
    uint32_t        rw_gray;            /**<@if Chinese ��ӡ�Ҷ� 				@else	Print grayscale								@endif*/
    int32_t         rw_hi_temp;         /**<@if Chinese ��ӡͷ�¶� 				@else	Print head temperature						@endif*/
    int32_t         rw_lo_temp;         /**<@if Chinese ��������ӡ�¶� 		@else	Maximum allowable print temperature			@endif*/
} printer_param_t;


/**
 @if Chinese
* @brief ��ʽ��ӡ���������ݽṹ��
 @else
* @brief Needle printer lifetime data structure
 @endif
*/
typedef struct st_printer_lifetime_data {
    int char_steps;                     /**<@if Chinese �ַ����� 	@else	Character step		@endif*/
    int feed_steps;                     /**<@if Chinese ��ֽ���� 	@else	Step into the paper	@endif*/
    int pin_shots[9];                   /**<@if Chinese ��� 		@else	stitching			@endif*/
} printer_lifetime_data_t;

/**
@if Chinese
 * @brief ��ӡ��״̬�����ṹ
 * @note ��ӡ��״̬�����в�����ֻ�ܶ�ȡ
@else 
 * @brief Printer status parameter structure
 * @note Printer status, all parameters can only be read
@endif 
 */
typedef struct printer_status {
    unsigned long   status;             /**<@if Chinese ��ӡ��״̬ 		@else	Printer status					@endif*/
    int32_t         voltage;            /**<@if Chinese ��ӡ��ѹ 		@else	Print the voltage				@endif*/
    int32_t         temperature;        /**<@if Chinese ��ǰ��ӡͷ�¶� 	@else	Current print head temperature	@endif*/
} printer_status_t;


/**
@if Chinese
 * @name ��ӡ��״̬
@else 
 * @name Printer status
@endif 
 * @{
 */

/**
 * @def PRINTER_STATUS_BUSY
 @if Chinese
 * @brief ��ӡ��״̬ printer_status.status �д���æ������λ
  @else
 * @brief Printer status printer_status.status indicates the busy data bits
 @endif
 */
/**
 * @def PRINTER_STATUS_HIGHT_TEMP
 @if Chinese
 * @brief ��ӡ��״̬ printer_status.status �д�����µ�����λ
 @else 
 * @brief Printer status printer_status.status data bits that represent high temperature
 @endif
 */
/**
 * @def PRINTER_STATUS_PAPER_LACK
 @if Chinese
 * @brief ��ӡ��״̬ printer_status.status �д���ȱֽ������λ 
  @else
 * @brief Printer status printer_status.status represents the data bits that are paperless
 @endif
 */
/**
 * @def PRINTER_STATUS_NO_BATTERY
 @if Chinese
 * @brief ��ӡ��״̬ printer_status.status �д����޵�ص�����λ
  @else
 * @brief Printer status printer_status.status indicates data bits without batteries
 @endif
 */
/**
 * @def PRINTER_STATUS_FEED
 @if Chinese
 * @brief ��ӡ��״̬ printer_status.status �д����ֽ������λ 
  @else
 * @brief Printer status printer_status.status data bits that represent paper feed
 @endif
 */
/**
 * @def PRINTER_STATUS_PRINT
 @if Chinese
 * @brief ��ӡ��״̬ printer_status.status �д����ӡ�е�����λ
  @else
 * @brief Printer status printer_status.status represents the data bits in printing
 @endif
 */
/**
 * @def PRINTER_STATUS_FORCE_FEED
 @if Chinese
 * @brief ��ӡ��״̬ printer_status.status �д���ǿ�ƽ�ֽ������λ
  @else
 * @brief Printer status printer_status represents the data bit forced into paper
 @endif
 */
/**
 * @def PRINTER_STATUS_POWER_ON
 @if Chinese
 * @brief ��ӡ��״̬ printer_status.status �д����ϵ��е�����λ
  @else
 * @brief Printer status printer_status.status indicates the data bit in power-on
 @endif
 */
/**
 * @def PRINTER_STATUS_ERROR_MASK
 @if Chinese
 * @brief ��ӡ��״̬ printer_status.status ��������
@else
 * @brief Printer status printer_status.status Error mask
  @endif
 */
/* ����λ */
#define PRINTER_STATUS_BUSY             0               /**<@if Chinese �豸æ 			@else	Device is busy					@endif*/
#define PRINTER_STATUS_HIGHT_TEMP       1               /**<@if Chinese �����¶ȹ��� @else	Error, temperature is too high	@endif**/
#define PRINTER_STATUS_PAPER_LACK       2               /**<@if Chinese ����ȱֽ 		@else	Wrong, lack of paper			@endif**/
#define PRINTER_STATUS_NO_BATTERY       3               /**<@if Chinese �޵�� 			@else	No battery						@endif**/
#define PRINTER_STATUS_FEED             8               /**<@if Chinese ������ֽ 		@else	Are walking paper				@endif**/
#define PRINTER_STATUS_PRINT            9               /**<@if Chinese ���ڴ�ӡ���� 	@else	Printing data					@endif**/
#define PRINTER_STATUS_FORCE_FEED       30              /**<@if Chinese ǿ����ֽ 		@else	Mandatory go paper				@endif**/
#define PRINTER_STATUS_POWER_ON         31              /**<@if Chinese ��Դ�� 		@else	The power to open				@endif**/

#define PRINTER_STATUS_ERROR_MASK       0xFE            /**<@if Chinese ״̬�������� 	@else	Status error mask				@endif**/
/** @} */

/**
@if Chinese
 * @brief          �򿪴�ӡ���豸
 * @param          filename  - ��ӡ�豸����"/dev/printer0","/dev/printer1"����
 * @param          oflags    - ���豸�ķ�ʽ:
 *
 *              ֻ����  O_WRONLY
 *              �ɶ���д��O_WRONLY | O_NONBLOCK
 * @return         int
 *
 *              >=0    ���豸OK������ֵ����������ӡ�����ļ���
 *              ����   ʧ��
 * @note
 *              ��ӡ���豸���������Ϊ16�����豸��Ϊ /dev/printer?��?=0,1,2,��,15����Ĭ�������NEW8210������ӡ���豸����Ϊ/dev/printer0;
 *              ����ӡ���������ʱ������رմ�ӡ���豸���������Ӳ���رա�
@else
 * @brief          open printer device
 * @param          filename  - printer device name��"/dev/printer0","/dev/printer1"����
 * @param          oflags    - Way to open the device:
 *
 *              blocking mode use��  O_WRONLY
 *              non-blocking mode use��O_WRONLY | O_NONBLOCK
 * @return         int
 *
 *              >=0     open device OK, return value is used to operate printer's file number
 *              other   other error code
 * @note
 *              Printer device's number is up to 16, its device name is /dev/printer?��?=0,1,2,��,15����in default condition NEW8210 thermal printer device name is/dev/printer0;
 *              When printer work finished, you must close the printer device, otherwise it can be shutdown by hardware.
@endif
 */
int printer_open(const char *filename, int oflags);

/**
@if Chinese
 * @brief          �رմ�ӡ���豸
 * @param          fd  - ���豸�ľ�� @link printer_open @endlink ��������ֵ
 * @return         int
 *              0      �رճɹ�
 *              ����   ʧ��
 * @note        ���ô˺�����fd����Ч�����ٴδ򿪴�ӡ���豸֮ǰ������ʹ�ô���Чfd��������ӡ����
@else
 * @brief          close printer device
 * @param          fd  - opened device file number that @link printer_open @endlink function returns
 * @return         int
 *              0       close printer device success
 *              other   other error code
 * @note        After calling this function fd will be invalid, before opening printer device again, can not use this invalid fd to operate printer.
@endif
 */
int printer_close(int fd);

#if 0 //ȥ����ɾ���˽ӿ�
/**
 * @brief          Meaningless printer just a input device
 * @param          fd      - opened device file number that @link printer_open @endlink function returns
 * @param          buf     -
 * @param          nbytes  -
 * @return         int
 * @note
*/
int printer_read(int fd, void *buf, size_t nbytes);
#endif

/**
 @if Chinese
 * @brief          ��Ҫ��ӡ�����ݴ���Printer�豸
 * @param          fd      - ���豸�ľ�� @link printer_open @endlink ��������ֵ
 * @param          buf     - ָ��Ҫ��ӡ�����ݻ�����
 * @param          nbytes  - ��ӡ���ݵ��ֽ���
 * @return         int
 *
 *              >=0     ��ӡ���豸ʵ�ʽ��ܵ�ֱ������
 *              ����   ʧ��
 * @note
 *      ���ô˺����󣬴�ӡ�����Զ���ʼ��ӡ��
 * @note
*		������ģʽ�£��ù��ܿ��ܻ�������ֱ����ӡ�����Խ������ݣ�
*		��û����������£���ӡ������ɴ�ӡ�ύ�����ݣ�
*		������쳣(���ӡ��ֽ����ӡͷ�¶ȹ���)��
*		�������������ء�
 * @note
*		�ڷ�����ģʽ�£���ӡ�������Խ���Ҫ��ӡ�����ݣ�
*		�����ӡ���ڲ���ӡ�������������ú��������������ѽ��յ����͵�������
*		���ڲ���ӡ����������������£��������ô˺��������ش���(�����ɴ�ӡ�����������)��
* @note
 *		ע�⣬�ڵ��ô˺���ʱ����ӡ�������޷�һ���Խ����������ݣ����Ӧ�ó���Ӧ��ѭ������printer_write��ֱ����ӡ���������ݡ�
 *
@else
 * @brief          put the data to be printed
 * @param          fd      - opened device file number that @link printer_open @endlink function returns
 * @param          buf     - point to data buffer to be printed
 * @param          nbytes  - the number of printed data's bytes
 * @return         int
 *
 *              >=0     the direct number of printer device actually accept
 *              other   other error code
 * @note
 *      After calling this function, the printer will automatically begin to print.
 * @note
 *      In the blocking mode, the function may block until the printer can accept data,
 *      on no exceptional condition, printer will complete print submitted data,
 *      if an exception occurs(such as printing out of paper,print head temperature is too high),
 *      function will return immediately.
 * @note
 *      In the non-blocking mode, the printer will try to accept the data to be printed,
 *      if the printer internal print buffer is full, this function will immediately return the number of types have been received,
 *      in the case of internal print buffer is full, continue to call this function will return error(not by the failure of the printer ).
 * @note
 *      Note that calling this function, the printer may not accept all of the data one time, so application should loop call printer_write, until all of data are printed.
 @endif
*/
int printer_write(int fd, const void *buf, size_t nbytes);

/**
 @if Chinese
 * @brief          ��ȡ��ӡ��״̬
 * @param          fd      - ���豸�ľ�� @link printer_open @endlink ��������ֵ
 * @param          status  -
 *-#                printer_status_t.status ״̬��32λ��ʾ:\n
 *                      @link PRINTER_STATUS_BUSY       @endlink  bit����ӡ�豸æ��־.\n
 *                      @link PRINTER_STATUS_HIGHT_TEMP @endlink  bit���¶ȹ��� \n
 *                      @link PRINTER_STATUS_PAPER_LACK @endlink  bit��ȱֽ��־ \n
 *                      @link PRINTER_STATUS_FEED       @endlink  bit��FEED��־\n
 *                      @link PRINTER_STATUS_PRINT      @endlink  bit��ӡˢ��־\n
 *                      @link PRINTER_STATUS_FORCE_FEED @endlink  bit��FORCE_FEED ��־\n
 *                      @link PRINTER_STATUS_POWER_ON   @endlink  bit����ӡ��Դ������־\n
 *-#                printer_status_t.voltage ��ӡ�����ĵ�ѹ
 *-#                printer_status_t.temperature ��ǰ��ӡͷ�¶�
 * @return         int
 *
 *              0       ��ȡ״̬�ɹ������صĲ�������
 *              ����   	ʧ��
 * @note        ��ӡ���Ļ�ȡ״̬�ǰ�λ����ģ���Ӧ�ò��� status->status &��1<<PRINTER_STATUS_BUSY����ȷ����ӡ���Ƿ����

@else
 * @brief          To get the status of the printer
 * @param          fd      - opened device file number that @link printer_open @endlink function returns
 * @param          status  -
 *-#                printer_status_t.status State is represented by the 32-bit:\n
 *                      @link PRINTER_STATUS_BUSY       @endlink  bit��printing device busy flag.\n
 *                      @link PRINTER_STATUS_HIGHT_TEMP @endlink  bit��temperature is too high \n
 *                      @link PRINTER_STATUS_PAPER_LACK @endlink  bit��out of paper \n
 *                      @link PRINTER_STATUS_FEED       @endlink  bit��feeding\n
 *                      @link PRINTER_STATUS_PRINT      @endlink  bit��printing flag\n
 *                      @link PRINTER_STATUS_FORCE_FEED @endlink  bit��force feed flag\n
 *                      @link PRINTER_STATUS_POWER_ON   @endlink  bit��print power on flag\n
 *-#                printer_status_t.voltage voltage of the current print
 *-#                printer_status_t.temperature temperature of current print head
 * @return         int
 *
 *              0       get status successfully, the returned parameter is available
 *              other   other error code
 * @note           The got status of printer is defined by bit, you should test status->status &��1<<PRINTER_STATUS_BUSY��to determine wether the printer is ldle
@endif
 */
int printer_get_status(int fd, printer_status_t *status);

/**
 @if Chinese
 * @brief          ������ӡ����ֽ����
 * @param          fd    - ���豸�ľ�� @link printer_open @endlink ��������ֵ
 * @param          step  - ��ֽ����
 * @return         int
 *
 *              0       ���óɹ�
 *              ����   	ʧ��
 * @note        ���ô˺����������ӡ�����ڿ���״̬�����ӡ����ʼ���ϣ���ӡ���ڲ���һ�������ϲ������ƣ�������õĲ������ڸò����������������ڲ���󲽳����ϡ�
 *              ����ʱ�����������Ա����printer_feed_stop����ӡ����ֹͣ���ϡ�
 @else
 * @brief          start the printer paper feed function
 * @param          fd    - opened device file number that @link printer_open @endlink function returns
 * @param          step  - Steps of feeding into the paper
 * @return         int
 *
 *              0       Set OK
 *              other   other error code
 * @note           After calling this function, if the printer is idle, then the printer will begin to feed, there has a largest number of feed steps limit inside the printer, if setted step is bigger than the step, then it will feed according the internal maximum steps.
 *                  When feeding ,if developer call printer_feed_stop , printer will stop feeding.
 @endif
 */
int printer_feed_start(int fd, uint32_t step);

/**
 @if Chinese
 * @brief          ֹͣ��ӡ������
 * @param          fd  - ���豸�ľ�� @link printer_open @endlink ��������ֵ
 * @return         int
 *
 *              0       �����ɹ�
 *              ����  	ʧ��
 * @note        ���Ӧ�ó��򿪷���Ա�Ѿ�������printer_feed_start����ô���øú�����ֹͣ��ӡ������;�����ӡ����ֹͣ���ϣ����ô˺��������Դ�ӡ�����κι�����
 @else
 * @brief          stop the printer feeding
 * @param          fd  - opened device file number that @link printer_open @endlink function returns
 * @return         int
 *
 *              0       Operate OK
 *              other   other error code
 * @note           If application developer have called printer_feed_start, then calling this function will stop the printer to feed; if printer have stopped feeding, call this function will do no work on the printer.
 @endif
 */
int printer_feed_stop(int fd);

/**
 @if Chinese
 * @brief          �������д�ӡ��״̬��������д�ӡ���ڲ�����
 * @param          fd  - ���豸�ľ�� @link printer_open @endlink ��������ֵ
 * @return         int
 *
 *              0       �ɹ�
 *              ����   	ʧ��
 * @note
  @else
 * @brief          Reset all status of printer, clear all the printer internal data
 * @param          fd  - opened device file number that @link printer_open @endlink function returns
 * @return         int
 *
 *              0       operate success
 *              other   other error code
 * @note
 @endif 
*/
int printer_reset(int fd);

/**
 @if Chinese
 * @brief          ��ȡ��ǰ��ӡ����
 * @param          fd     - ���豸�ľ�� @link printer_open @endlink ��������ֵ
 * @param          param  -
 *-#                printer_param_t.ro_width ��ӡ��ÿһ�е���ĵ��
 *-#                printer_param_t.ro_bits_per_pixel ÿ�����ر�ʾ����λ
 *-#                printer_param_t.rw_gray ���ô�ӡ�ң���Χ:50~500����ʾ��ӡ������Ϊ50%~500%
 *-#                printer_param_t.rw_hi_temp ��ӡͷ�������߹����¶�
 *-#                printer_param_t.rw_lo_temp ���´�ӡ���ٴδ�ӡʱ����ӡͷ���������¶�
 * @return         int
 *
 *              0      ��ȡ״̬�ɹ������ز�������
 *              ����   ʧ��
 * @note           When printing , if print head up to the value that rw_hi_temp setted it will be status of "over-temperature", print will stop, until temperature reduce to under rw_lo_temp it will continue to print. If over-temperature occurs , data that have not been printed will all be discarded.

@else 
 * @brief          get the current print parameters
 * @param          fd     - opened device file number that @link printer_open @endlink function returns
 * @param          param  -
 *-#                printer_param_t.ro_width the dot number of each line dot matrix of printer
 *-#                printer_param_t.ro_bits_per_pixel how many bits to expressed each pixel
 *-#                printer_param_t.rw_gray Set print gray, scope: 50~500, represent that print gray is normal 50%��500%
 *-#                printer_param_t.rw_hi_temp highest work temperature that print head allowed
 *-#                printer_param_t.rw_lo_temp highest temperature that print head allowed when printing again after  over-temperature printing
 * @return         int
 *
 *              0       get status successfully, the returned parameter is available
 *              other   other error code
 * @note           When printing , if print head up to the value that rw_hi_temp setted it will be status of "over-temperature", print will stop, until temperature reduce to under rw_lo_temp it will continue to print. If over-temperature occurs , data that have not been printed will all be discarded.
@endif
 */
int printer_get_param(int fd, printer_param_t *param);

/**
@if Chinese
 * @brief          ���ô�ӡ������
 * @param          fd     - ���豸�ľ�� @link printer_open @endlink ��������ֵ
 * @param          param  -
 *-#                printer_param_t.ro_width ��ӡ��ÿһ�е���ĵ��
 *-#                printer_param_t.ro_bits_per_pixel ÿ�����ر�ʾ����λ
 *-#                printer_param_t.rw_gray ���ô�ӡ�ң���Χ:50~500����ʾ��ӡ������Ϊ50%~500%
 *-#                printer_param_t.rw_hi_temp ��ӡͷ�������߹����¶�
 *-#                printer_param_t.rw_lo_temp ���´�ӡ���ٴδ�ӡʱ����ӡͷ���������¶�
 * @return         int
 *
 *              	0      ���óɹ�
 *              	����   ���ش������
 * @note           ��param�У��ԡ�ro_����ͷ�Ĳ�����ʾ�ò����������ã����ú��޷��������ԡ�rw_����ͷ�Ĳ�����ʾ�ò����������á�
@else
 * @brief          set current print parameter
 * @param          fd     - opened device file number that @link printer_open @endlink function returns
 * @param          param  -
 *-#                printer_param_t.ro_width the number of each line dot matrix of printer
 *-#                printer_param_t.ro_bits_per_pixel how many bits to expressed each pixel
 *-#                printer_param_t.rw_gray Set print gray, scope: 50~500, represent that print gray is normal 50%��500%
 *-#                printer_param_t.rw_hi_temp highest work temperature that print head allowed
 *-#                printer_param_t.rw_lo_temp highest temperature that print head allowed when printing again after printing over-temperature
 * @return         int
 *
 *              0       Set OK
 *              other   other error code
 * @note           In param, parameter begins with "ro_"means that this parameter can not be set, it will not work after setting up. Parameter begins with "rw_" means that this parameter can be set.
@endif
 */
int printer_set_param(int fd, const printer_param_t *param);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* end for LINUX_PRINTER_H */

/** @} */

