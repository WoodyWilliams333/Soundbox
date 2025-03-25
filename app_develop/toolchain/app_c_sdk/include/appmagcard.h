/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app magcard模块</strong> 相关的接口
	 * @par 文件    appmagcard.h
	 * @author		yangjing
	 * @date        2020-04-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-04-09    | 1.0.0        | yanjing       | 创建文件
	 * 2022-04-19    | 1.0.1        | lydia         | 增加英文注释  
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app magcard</strong>  module
	 * @par file    appmagcard.h
	 * @author		yangjing
	 * @date        2020-04-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-04-09    | 1.0.0        | yanjing       | create file
	 * 2022-04-19    | 1.0.1        | lydia         | Add English description
 @endif
*/

/*!
 @if Chinese
	@defgroup appmagcard 磁条卡
 @else
	@defgroup appmagcard magcard
 @endif
 * @{
*/
#ifndef _APP_MAG_CARD_H_
#define _APP_MAG_CARD_H_


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 @if Chinese
	@brief  磁道LRC校验枚举.
 @else
	@brief  This enumerated type lists track LRC verification.
 @endif
  */
typedef enum 
{ 
	LRC_TRACK1 = 0x01,		/**< @if Chinese 磁道1 LRC校验  @else track1 LRC verification @endif */
	LRC_TRACK2 = 0x02,		/**< @if Chinese 磁道2 LRC校验  @else track2 LRC verification @endif */
	LRC_TRACK3 = 0x04,		/**< @if Chinese 磁道3 LRC校验  @else track3 LRC verification @endif */
}TrackLrc;
  
/**
 @if Chinese
	@brief  磁条卡操作类函数返回值枚举.
 @else
	@brief  This enumerated type lists return value of magnetic stripe card.
 @endif
  */
typedef enum 
{ 
	UTRACK_MAG_FAIL		= -5,	/**< @if Chinese 磁条卡读卡器操作失败  @else magnetic stripe card reader operation failed @endif */ 
	UTRACK_NOEVENT		= -4,	/**< @if Chinese 不等待时才会返回，说明本次调用未检测到刷卡  @else return when no wait,indicating the card is not detected @endif */ 
	UTRACK_CONTROL		= -3,	/**< @if Chinese 用户退出  @else user exit @endif */   
	UTRACK_TIMEOUT		= -2,	/**< @if Chinese 刷卡超时  @else card swiping timeout @endif */  
	UTRACK_FAIL			= -1,	/**< @if Chinese 刷卡失败  @else card swiping fail @endif */  
	UTRACK_OK			= 0,	/**< @if Chinese 刷卡成功  @else card swiping success @endif */
	UTRACK_MAG_OK		= 1,	/**< @if Chinese 磁条卡读卡器操作成功 @else magnetic stripe card reader operation success @endif */
	UTRACK_NUM			= 2,	/**< @if Chinese 手输卡号(预留)  @else manual card number @endif */
}SwipCardRet; 

/*!
 @if Chinese
	@brief		磁条读卡器模块初始化
	@return		UTRACK_MAG_OK-成功，UTRACK_MAG_FAIL-失败
 @else
	@brief		magnetic stripe card reader init
	@return		UTRACK_MAG_OK-success，UTRACK_MAG_FAIL-fail
 @endif
*/ 
extern int app_mag_init(void);

/*!
 @if Chinese
	@brief		读取磁道信息
	@param[out]	CardBuf1	-	1磁道数据保存地址
	@param[out]	CardBuf2	-	2磁道数据保存地址
	@param[out]	CardBuf3	-	3磁道数据保存地址
	@param[in]	LrcFlag		-	是否启用lrc校验标识位(保留，暂未使用)
	@param[in]	WaitFlag	-	是否阻塞等待标识位(保留，暂未使用)
	@return		参考SwipCardRet枚举值
 @else
	@brief		read track information
	@param[out]	CardBuf1	-	track1 buffer
	@param[out]	CardBuf2	-	track2 buffer
	@param[out]	CardBuf3	-	track3 buffer
	@param[in]	LrcFlag		-	not used
	@param[in]	WaitFlag	-	not used
	@return		reference enum SwipCardRet
 @endif
*/  
extern int app_mag_get_alltrack(byte *CardBuf1, byte *CardBuf2, byte *CardBuf3, int LrcFlag, ushort WaitFlag);

/*!
 @if Chinese
	@brief		关闭磁条读卡器模块
	@return		参考SwipCardRet枚举值
 @else
	@brief		close magnetic stripe card reader
	@return		reference enum SwipCardRet
 @endif
*/ 
extern int app_mag_close(void);

/*!
 @if Chinese
	@brief		检测是否有刷卡
	@return		参考SwipCardRet枚举值
 @else
	@brief		check whether to swipe the card
	@return		reference enum SwipCardRet
 @endif
*/  
extern int app_mag_judge_swiped(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __UMS_MAG_H__ */


