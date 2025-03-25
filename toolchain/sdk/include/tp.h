/**
@if Chinese
 * @brief       该模块用于描述 <strong>触摸屏模块</strong> 相关的接口
 * @author      leely
 * @date        2019-01-22
 * @version     V1.0
 *
 * @remarks Change History:
 * 日期          | 版本          | 作者            | 描述
 * ------------- | ------------- | --------------- | ----
 * 2019/01/22    | 1.0.0         | leely           | 创建文件
 * 2022/04/20    | 1.0.1         | Wenming         | 增加英文注释
@else  
 * @brief       This module is used to describe <strong>TouchScreen</strong>  interfaces module
 * @author      leely
 * @date        2019-01-22
 * @version     V1.0
 *
 * @remarks Change History:
 * Date          | Version       | Author          | Desc
 * ------------- | ------------- | --------------- | ----
 * 2019/01/22    | 1.0.0         | leely           | Create file
 * 2022/04/20    | 1.0.1         | Wenming         | Add English description
@endif
 */

/**
@if Chinese
 * @defgroup tp 触摸屏
@else 
 * @defgroup tp TouchScreen
@endif 
 * @{
*/


#ifndef __TP_H__
#define __TP_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if 0
/* 这个接口是否有必要导出到应用层 ? */
struct input_event {
    //struct timeval time;
    uint16_t type;
    uint16_t code;
    int value;
};
#endif

/* 这个接口是否有必要导出到应用层: 校准的时候需要使用到，即download程序会使用，其他应用不关心 */
struct cal_info_t {
    int chx;
    int distancex;
    int orig_pointx;
    int chy;
    int distancey;
    int orig_pointy;
    uint8_t state;
};

/**
@if Chinese
  * @brief  用于描述TP触点信息
@else  
  * @brief  Information about TP contacts
@endif  
  */
struct ts_sample {
    int             x;              /**<@if Chinese TP触点的x坐标(以绝对零点(0,0)为参考) 	@else	X coordinate of TP contact (with absolute zero (0,0) as reference)	@endif*/
    int             y;              /**<@if Chinese TP触点的y坐标(以绝对零点(0,0)为参考) 	@else	Y coordinate of TP contact (with absolute zero (0,0) as reference)	@endif*/
    unsigned int    pressure;       /**<@if Chinese TP触点的压力值 							@else	TP contact pressure value											@endif*/
    //struct timeval    tv;
};

/**
@if Chinese
	* @brief 打开TS设备
	* @param[in] filename	-	文件驱动名:"dev/input0"
	* @param[in] oflags		-	打开标志(暂未使用)
	* @return int
	*
	*          >= 0  打开成功, fd 作为打开ts设备后的句柄
	*          < 0   打卡失败, 请检查“errno”的实际错误码
@else
	* @brief open tp device
	* @param[in] filename	-	device name:"dev/input0"
	* @param[in] oflags		-	open flag(Not used yet)
	* @return int
	*
	*          >= 0  open successful, fd for tp operation
	*          < 0   failed, please check "errno" for actual error code
@endif	
*/
int ts_open(const char *filename, int oflags);

/**
@if Chinese
	 * @brief          关闭tp设备
	 * @param          fd	-	打开设备的句柄
	 * @return         int
	 *
	 *          = 0    成功
	 *          < 0    失败, 请检查“errno”的实际错误码
	 * @note
@else
	 * @brief          close tp device
	 * @param          fd	-	open device fd
	 * @return         int
	 *
	 *          = 0    close successful
	 *          < 0    failed, please check "errno" for actual error code
	 * @note
@endif		 
*/
int ts_close(int fd);

/**
@if Chinese
	* @brief 读取tp信息
	* @param[in]	fd		-	fd是打开TP设备返回的句柄
	* @param[in]	nr		-	读坐标数
	* @param[out]	samp	-	事件位置
	 * @return         int
	 *
	 *          > 0     获取TP数据
	 *          < 0     没有任何输入事件
@else	 
	* @brief read tp coordinate
	* @param[in]	fd		-	fd which open return
	* @param[in]	nr		-	read coordinate number
	* @param[out]	samp	-	coordinate
	 * @return         int
	 *
	 *          > 0     read coordinate munber
	 *          < 0     do not have any input event
@endif	 
*/

int ts_read(int fd, struct ts_sample *samp, int nr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TP_H__ */

/** @}*/

