/**
 @if Chinese
 * @brief  此模块用于描述 <strong>打印机模块</strong> 相关的接口
 * @note   打印机相关的接口
 *
 *
 *
 * @version 1.0.1
 * @remarks        Change History:
 * 日期          | 作者            | 描述
 * ------------- | --------------- | ----
 * 2010/07/14    | Li.Hua          | 创建文件
 * 2022/04/20    | Wenming         | 增加英文注释
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
 * @defgroup printer 打印机
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
 * @brief 打印机参数结构
 * @note
 *  ro_xxxx :该参数只能读，不能修改
 *  rw_xxxx :该参数可读写
@else
 * @brief Printer parameter structure
 * @note
 *  ro_xxxx : read only
 *  rw_xxxx : read write
@endif 
 */
typedef struct printer_param {
    uint32_t        ro_width;           /**<@if Chinese 打印宽度 				@else	Print width									@endif*/
    uint32_t        ro_bits_per_pixel;  /**<@if Chinese 一个像素用多少位表示 	@else	How many bits are used to represent a pixel	@endif*/
    uint32_t        rw_gray;            /**<@if Chinese 打印灰度 				@else	Print grayscale								@endif*/
    int32_t         rw_hi_temp;         /**<@if Chinese 打印头温度 				@else	Print head temperature						@endif*/
    int32_t         rw_lo_temp;         /**<@if Chinese 最大允许打印温度 		@else	Maximum allowable print temperature			@endif*/
} printer_param_t;


/**
 @if Chinese
* @brief 针式打印机寿命数据结构体
 @else
* @brief Needle printer lifetime data structure
 @endif
*/
typedef struct st_printer_lifetime_data {
    int char_steps;                     /**<@if Chinese 字符步长 	@else	Character step		@endif*/
    int feed_steps;                     /**<@if Chinese 进纸步长 	@else	Step into the paper	@endif*/
    int pin_shots[9];                   /**<@if Chinese 针脚 		@else	stitching			@endif*/
} printer_lifetime_data_t;

/**
@if Chinese
 * @brief 打印机状态参数结构
 * @note 打印机状态，所有参数都只能读取
@else 
 * @brief Printer status parameter structure
 * @note Printer status, all parameters can only be read
@endif 
 */
typedef struct printer_status {
    unsigned long   status;             /**<@if Chinese 打印机状态 		@else	Printer status					@endif*/
    int32_t         voltage;            /**<@if Chinese 打印电压 		@else	Print the voltage				@endif*/
    int32_t         temperature;        /**<@if Chinese 当前打印头温度 	@else	Current print head temperature	@endif*/
} printer_status_t;


/**
@if Chinese
 * @name 打印机状态
@else 
 * @name Printer status
@endif 
 * @{
 */

/**
 * @def PRINTER_STATUS_BUSY
 @if Chinese
 * @brief 打印机状态 printer_status.status 中代表忙的数据位
  @else
 * @brief Printer status printer_status.status indicates the busy data bits
 @endif
 */
/**
 * @def PRINTER_STATUS_HIGHT_TEMP
 @if Chinese
 * @brief 打印机状态 printer_status.status 中代表高温的数据位
 @else 
 * @brief Printer status printer_status.status data bits that represent high temperature
 @endif
 */
/**
 * @def PRINTER_STATUS_PAPER_LACK
 @if Chinese
 * @brief 打印机状态 printer_status.status 中代表缺纸的数据位 
  @else
 * @brief Printer status printer_status.status represents the data bits that are paperless
 @endif
 */
/**
 * @def PRINTER_STATUS_NO_BATTERY
 @if Chinese
 * @brief 打印机状态 printer_status.status 中代表无电池的数据位
  @else
 * @brief Printer status printer_status.status indicates data bits without batteries
 @endif
 */
/**
 * @def PRINTER_STATUS_FEED
 @if Chinese
 * @brief 打印机状态 printer_status.status 中代表进纸的数据位 
  @else
 * @brief Printer status printer_status.status data bits that represent paper feed
 @endif
 */
/**
 * @def PRINTER_STATUS_PRINT
 @if Chinese
 * @brief 打印机状态 printer_status.status 中代表打印中的数据位
  @else
 * @brief Printer status printer_status.status represents the data bits in printing
 @endif
 */
/**
 * @def PRINTER_STATUS_FORCE_FEED
 @if Chinese
 * @brief 打印机状态 printer_status.status 中代表强制进纸的数据位
  @else
 * @brief Printer status printer_status represents the data bit forced into paper
 @endif
 */
/**
 * @def PRINTER_STATUS_POWER_ON
 @if Chinese
 * @brief 打印机状态 printer_status.status 中代表上电中的数据位
  @else
 * @brief Printer status printer_status.status indicates the data bit in power-on
 @endif
 */
/**
 * @def PRINTER_STATUS_ERROR_MASK
 @if Chinese
 * @brief 打印机状态 printer_status.status 错误掩码
@else
 * @brief Printer status printer_status.status Error mask
  @endif
 */
/* 数据位 */
#define PRINTER_STATUS_BUSY             0               /**<@if Chinese 设备忙 			@else	Device is busy					@endif*/
#define PRINTER_STATUS_HIGHT_TEMP       1               /**<@if Chinese 错误，温度过高 @else	Error, temperature is too high	@endif**/
#define PRINTER_STATUS_PAPER_LACK       2               /**<@if Chinese 错误，缺纸 		@else	Wrong, lack of paper			@endif**/
#define PRINTER_STATUS_NO_BATTERY       3               /**<@if Chinese 无电池 			@else	No battery						@endif**/
#define PRINTER_STATUS_FEED             8               /**<@if Chinese 正在走纸 		@else	Are walking paper				@endif**/
#define PRINTER_STATUS_PRINT            9               /**<@if Chinese 正在打印数据 	@else	Printing data					@endif**/
#define PRINTER_STATUS_FORCE_FEED       30              /**<@if Chinese 强制走纸 		@else	Mandatory go paper				@endif**/
#define PRINTER_STATUS_POWER_ON         31              /**<@if Chinese 电源打开 		@else	The power to open				@endif**/

#define PRINTER_STATUS_ERROR_MASK       0xFE            /**<@if Chinese 状态错误掩码 	@else	Status error mask				@endif**/
/** @} */

/**
@if Chinese
 * @brief          打开打印机设备
 * @param          filename  - 打印设备名："/dev/printer0","/dev/printer1"……
 * @param          oflags    - 打开设备的方式:
 *
 *              只读：  O_WRONLY
 *              可读可写：O_WRONLY | O_NONBLOCK
 * @return         int
 *
 *              >=0    打开设备OK，返回值用来操作打印机的文件号
 *              其他   失败
 * @note
 *              打印机设备的数量最多为16，其设备名为 /dev/printer?（?=0,1,2,…,15），默认情况下NEW8210热敏打印机设备名称为/dev/printer0;
 *              当打印机工作完毕时，必须关闭打印机设备，否则会由硬件关闭。
@else
 * @brief          open printer device
 * @param          filename  - printer device name："/dev/printer0","/dev/printer1"……
 * @param          oflags    - Way to open the device:
 *
 *              blocking mode use：  O_WRONLY
 *              non-blocking mode use：O_WRONLY | O_NONBLOCK
 * @return         int
 *
 *              >=0     open device OK, return value is used to operate printer's file number
 *              other   other error code
 * @note
 *              Printer device's number is up to 16, its device name is /dev/printer?（?=0,1,2,…,15），in default condition NEW8210 thermal printer device name is/dev/printer0;
 *              When printer work finished, you must close the printer device, otherwise it can be shutdown by hardware.
@endif
 */
int printer_open(const char *filename, int oflags);

/**
@if Chinese
 * @brief          关闭打印机设备
 * @param          fd  - 打开设备的句柄 @link printer_open @endlink 函数返回值
 * @return         int
 *              0      关闭成功
 *              其他   失败
 * @note        调用此函数后fd将无效，在再次打开打印机设备之前，不能使用此无效fd来操作打印机。
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

#if 0 //去掉，删掉此接口
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
 * @brief          把要打印的数据传入Printer设备
 * @param          fd      - 打开设备的句柄 @link printer_open @endlink 函数返回值
 * @param          buf     - 指向要打印的数据缓冲区
 * @param          nbytes  - 打印数据的字节数
 * @return         int
 *
 *              >=0     打印机设备实际接受的直接数量
 *              其他   失败
 * @note
 *      调用此函数后，打印机将自动开始打印。
 * @note
*		在阻塞模式下，该功能可能会阻塞，直到打印机可以接受数据，
*		在没有例外情况下，打印机将完成打印提交的数据，
*		如出现异常(如打印出纸、打印头温度过高)，
*		函数将立即返回。
 * @note
*		在非阻塞模式下，打印机将尝试接受要打印的数据，
*		如果打印机内部打印缓冲区已满，该函数将立即返回已接收的类型的数量，
*		在内部打印缓冲区已满的情况下，继续调用此函数将返回错误(不是由打印机故障引起的)。
* @note
 *		注意，在调用此函数时，打印机可能无法一次性接受所有数据，因此应用程序应该循环调用printer_write，直到打印出所有数据。
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
 * @brief          获取打印机状态
 * @param          fd      - 打开设备的句柄 @link printer_open @endlink 函数返回值
 * @param          status  -
 *-#                printer_status_t.status 状态由32位表示:\n
 *                      @link PRINTER_STATUS_BUSY       @endlink  bit：打印设备忙标志.\n
 *                      @link PRINTER_STATUS_HIGHT_TEMP @endlink  bit：温度过高 \n
 *                      @link PRINTER_STATUS_PAPER_LACK @endlink  bit：缺纸标志 \n
 *                      @link PRINTER_STATUS_FEED       @endlink  bit：FEED标志\n
 *                      @link PRINTER_STATUS_PRINT      @endlink  bit：印刷标志\n
 *                      @link PRINTER_STATUS_FORCE_FEED @endlink  bit：FORCE_FEED 标志\n
 *                      @link PRINTER_STATUS_POWER_ON   @endlink  bit：打印电源开启标志\n
 *-#                printer_status_t.voltage 打印电流的电压
 *-#                printer_status_t.temperature 当前打印头温度
 * @return         int
 *
 *              0       获取状态成功，返回的参数可用
 *              其他   	失败
 * @note        打印机的获取状态是按位定义的，你应该测试 status->status &（1<<PRINTER_STATUS_BUSY）来确定打印机是否空闲

@else
 * @brief          To get the status of the printer
 * @param          fd      - opened device file number that @link printer_open @endlink function returns
 * @param          status  -
 *-#                printer_status_t.status State is represented by the 32-bit:\n
 *                      @link PRINTER_STATUS_BUSY       @endlink  bit：printing device busy flag.\n
 *                      @link PRINTER_STATUS_HIGHT_TEMP @endlink  bit：temperature is too high \n
 *                      @link PRINTER_STATUS_PAPER_LACK @endlink  bit：out of paper \n
 *                      @link PRINTER_STATUS_FEED       @endlink  bit：feeding\n
 *                      @link PRINTER_STATUS_PRINT      @endlink  bit：printing flag\n
 *                      @link PRINTER_STATUS_FORCE_FEED @endlink  bit：force feed flag\n
 *                      @link PRINTER_STATUS_POWER_ON   @endlink  bit：print power on flag\n
 *-#                printer_status_t.voltage voltage of the current print
 *-#                printer_status_t.temperature temperature of current print head
 * @return         int
 *
 *              0       get status successfully, the returned parameter is available
 *              other   other error code
 * @note           The got status of printer is defined by bit, you should test status->status &（1<<PRINTER_STATUS_BUSY）to determine wether the printer is ldle
@endif
 */
int printer_get_status(int fd, printer_status_t *status);

/**
 @if Chinese
 * @brief          启动打印机送纸功能
 * @param          fd    - 打开设备的句柄 @link printer_open @endlink 函数返回值
 * @param          step  - 送纸步骤
 * @return         int
 *
 *              0       设置成功
 *              其他   	失败
 * @note        调用此函数后，如果打印机处于空闲状态，则打印机开始进料，打印机内部有一个最大进料步长限制，如果设置的步长大于该步长，则它将根据内部最大步长进料。
 *              进料时，如果开发人员调用printer_feed_stop，打印机将停止进料。
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
 * @brief          停止打印机进料
 * @param          fd  - 打开设备的句柄 @link printer_open @endlink 函数返回值
 * @return         int
 *
 *              0       操作成功
 *              其他  	失败
 * @note        如果应用程序开发人员已经调用了printer_feed_start，那么调用该函数将停止打印机进料;如果打印机已停止送料，调用此函数将不对打印机做任何工作。
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
 * @brief          重置所有打印机状态，清除所有打印机内部数据
 * @param          fd  - 打开设备的句柄 @link printer_open @endlink 函数返回值
 * @return         int
 *
 *              0       成功
 *              其他   	失败
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
 * @brief          获取当前打印参数
 * @param          fd     - 打开设备的句柄 @link printer_open @endlink 函数返回值
 * @param          param  -
 *-#                printer_param_t.ro_width 打印机每一行点阵的点号
 *-#                printer_param_t.ro_bits_per_pixel 每个像素表示多少位
 *-#                printer_param_t.rw_gray 设置打印灰，范围:50~500，表示打印灰正常为50%~500%
 *-#                printer_param_t.rw_hi_temp 打印头允许的最高工作温度
 *-#                printer_param_t.rw_lo_temp 过温打印后再次打印时，打印头允许的最高温度
 * @return         int
 *
 *              0      获取状态成功，返回参数可用
 *              其他   失败
 * @note           When printing , if print head up to the value that rw_hi_temp setted it will be status of "over-temperature", print will stop, until temperature reduce to under rw_lo_temp it will continue to print. If over-temperature occurs , data that have not been printed will all be discarded.

@else 
 * @brief          get the current print parameters
 * @param          fd     - opened device file number that @link printer_open @endlink function returns
 * @param          param  -
 *-#                printer_param_t.ro_width the dot number of each line dot matrix of printer
 *-#                printer_param_t.ro_bits_per_pixel how many bits to expressed each pixel
 *-#                printer_param_t.rw_gray Set print gray, scope: 50~500, represent that print gray is normal 50%～500%
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
 * @brief          设置打印机参数
 * @param          fd     - 打开设备的句柄 @link printer_open @endlink 函数返回值
 * @param          param  -
 *-#                printer_param_t.ro_width 打印机每一行点阵的点号
 *-#                printer_param_t.ro_bits_per_pixel 每个像素表示多少位
 *-#                printer_param_t.rw_gray 设置打印灰，范围:50~500，表示打印灰正常为50%~500%
 *-#                printer_param_t.rw_hi_temp 打印头允许的最高工作温度
 *-#                printer_param_t.rw_lo_temp 过温打印后再次打印时，打印头允许的最高温度
 * @return         int
 *
 *              	0      设置成功
 *              	其他   返回错误代码
 * @note           在param中，以“ro_”开头的参数表示该参数不能设置，设置后将无法工作。以“rw_”开头的参数表示该参数可以设置。
@else
 * @brief          set current print parameter
 * @param          fd     - opened device file number that @link printer_open @endlink function returns
 * @param          param  -
 *-#                printer_param_t.ro_width the number of each line dot matrix of printer
 *-#                printer_param_t.ro_bits_per_pixel how many bits to expressed each pixel
 *-#                printer_param_t.rw_gray Set print gray, scope: 50~500, represent that print gray is normal 50%～500%
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

