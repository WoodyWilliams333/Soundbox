/**
 @if Chinese
* @brief    此模块用于描述 <strong>磁条卡模块</strong> 相关的接口
* @details  支持三个磁道的非阻塞式读取，读取出来的数据会在3S内清空以保证安全性
* @author   Victor
* @date     2018-10-26
* @version  V1.0
* 日期          | 版本          | 作者            | 描述
* ------------- | ------------- | --------------- | ----
* 2018/10/26    | 1.0.0         | Victor          | 创建文件
* 2022/04/19    | 1.0.1         | Wenming         | 增加英文注释
@else
* @brief     This module is used to describe <strong>Magstripe</strong> interfaces module
* @details  It supports non-blocking reading of three tracks, and the read data will be emptied within 3S to ensure safety
* @author   Victor
* @date     2018-10-26
* @version  V1.0
* Date          | Version       | Author          | Desc
* ------------- | ------------- | --------------- | ----
* 2018/10/26    | 1.0.0         | Victor          | Create file
* 2022/04/19    | 1.0.1         | Wenming         | Add English description
@endif
*/

/**
 @if Chinese
* @defgroup magstripe 磁卡
@else
* @defgroup magstripe Magstripe
@endif
* @{
*/

#ifndef __MAGSTRIPE_H__
#define __MAGSTRIPE_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define MAGCARD_READER_DEVICE_NAME          "/dev/magcard0"     /**<@if Chinese 设备名 			@else	The device name			@endif*/
#define MAGCARD_DECODE_OK                   0                   /**<@if Chinese 解码正确 		@else	Decode correctly		@endif*/
#define MAGCARD_DECODE_ERR_RAW              1                   /**<@if Chinese 原始数据错误 	@else	Original data error	@endif*/
#define MAGCARD_DECODE_ERR_LRC              2                   /**<@if Chinese LRC校验错误 	@else	LRC verification error	@endif*/
#define MAGCARD_DECODE_ERR_ODD              4                   /**<@if Chinese 奇偶校验错误 	@else	Parity error			@endif*/
#define MAGCARD_DECODE_NODATA               5                   /**<@if Chinese 无磁道数据 		@else	No track data			@endif*/
#define MAGCARD_TRACK_NUM                   3                   /**<@if Chinese 磁道个数 		@else	Track number			@endif*/


/**
 @if Chinese
* @brief 磁卡单个磁道信息
 @else
* @brief Magnetic card Information about a single track
 @endif
*/
typedef struct track_info {
    int                 bit_pre_code;                           /**<@if Chinese 编码位长度 	@else	Bit length		@endif*/
    uint8_t             start_flag;                             /**<@if Chinese 起始标志 	@else	Starting logo	@endif*/
    uint8_t             end_flag;                               /**<@if Chinese 结束标志 	@else	End mark		@endif*/
    uint8_t             base;                                   /**<@if Chinese 基值 		@else	Base value		@endif*/
} track_info_t;

/**
 @if Chinese
* @brief 磁卡每个磁道对应的数据及状态码
 @else
* @brief The data and status code corresponding to each track of the magnetic card
 @endif
*/
typedef struct magcard_info {
    int                 trackno;                                /**<@if Chinese 磁道号 				@else	Track number				@endif*/
    int                 status;                                 /**<@if Chinese 磁道状态：错误码 	@else	Track status: error code	@endif*/
    int                 size;                                   /**<@if Chinese 数据大小 			@else	Data size					@endif*/
    uint8_t             data[120];                              /**<@if Chinese 磁道数据 			@else	Track data					@endif*/
} magcard_info_t;

/**
 @if Chinese
* @brief 磁卡3个磁道数据
 @else
* @brief Magnetic card 3 track data
@endif
*/
typedef struct user_track_info {
    track_info_t        trackinfo[MAGCARD_TRACK_NUM];           /**<@if Chinese 3个磁道数据 @else	Three track data	@endif*/
} user_track_info_t;

/**
 @if Chinese
* @brief 磁卡数据
@else
* @brief Magnetic card data
@endif
*/
typedef struct user_magcard_info {
    magcard_info_t      magcardtrack[MAGCARD_TRACK_NUM];        /**<@if Chinese 3个磁道数据 @else	Three track data	@endif*/
} user_magcard_info_t ;

/**
@if Chinese
* @brief 打开磁卡设备
* @param[in]	filename	-	磁卡解码设备名：“/dev/magcard0”,“/dev/magcard1”……
* @param[in]	oflags		-	打开设备的模式，阻塞模式: O_RDONLY ,非阻塞模式:(O_RDONLY | O_NONBLOCK)
* @return 打开的设备文件描述符 <br>
*   <em> >= 0 </em>	-	成功,返回值用于操作磁卡解码设备的文件号<br>
*   <em> < 0 </em>	-	失败
@else
* @brief Open the magnetic card device
* @param[in]	filename	-	stripe reader name：“/dev/magcard0”,“/dev/magcard1”……
* @param[in]	oflags		-	Way to open the device,blocking mode :O_RDONLY;non-blocking mode:(O_RDONLY | O_NONBLOCK)
* @return Open device file descriptor<br>
*   <em> >= 0 </em>	-	success, return value is used to operate card decoding device’s file number <br>
*   <em> < 0 </em>	-	failed
@endif
*/
int magstripe_open(const char *filename, int oflags);

/**
@if Chinese
* @brief 关闭磁卡设备
* @param[in]	fd	-	磁卡设备文件描述符
* @return 
*   <em> 0 </em>	-	成功<br>
*   <em> 非0 </em>	-	失败
@else
* @brief Close the magnetic card device
* @param[in]	fd	-	Magnetic card device file descriptor
* @return 
*   <em> 0 </em>	-	success<br>
*   <em> !0 </em>	-	failed
@endif
*/
int magstripe_close(int fd);

/**
@if Chinese
* @brief 读取磁卡数据
* @param[in]	fd			-	磁卡设备文件描述符
* @param[out]	cardinfo	-	磁卡数据
* @return 获取的磁卡数据信息总大小<br>
*   -<em> 其值等于sizeof(user_magcard_info_t): </em> 成功<br>
*   -<em> 其值不等于sizeof(user_magcard_info_t): </em> 失败
@else
* @brief Read the magnetic card data
* @param[in]	fd			-	Magnetic card device file descriptor
* @param[out]	cardinfo	-	Magnetic card data
* @return Total size of magnetic card data information obtained<br>
*   -<em> Its value is equal to the sizeof(user_magcard_info_t): </em> success<br>
*   -<em> Its value is not equal to the sizeof(user_magcard_info_t):</em> failed
@endif
*/
int magstripe_read(int fd, user_magcard_info_t *cardinfo);

/**
 @if Chinese
* @brief 查看当前是否有刷卡动作
* @param[in]	fd	-	磁卡设备文件描述符
* @return 返回是否有刷卡动作<br>
*   <em> 1 </em>	-	有刷卡动作<br>
*   <em> 0 </em>	-	无刷卡动作
@else
* @brief Check whether the card is swiped
* @param[in]	fd	-	Magnetic card device file descriptor
* @return Returns whether there is a swipe action<br>
*   <em> 1 </em>	-	card swiped<br>
*   <em> 0 </em>	-	No swipe action
@endif
*/
int magstripe_swiped(int fd);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* end for __MAGSTRIPE_H__ */

/** @}*/

