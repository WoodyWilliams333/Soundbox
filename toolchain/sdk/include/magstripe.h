/**
 @if Chinese
* @brief    ��ģ���������� <strong>������ģ��</strong> ��صĽӿ�
* @details  ֧�������ŵ��ķ�����ʽ��ȡ����ȡ���������ݻ���3S������Ա�֤��ȫ��
* @author   Victor
* @date     2018-10-26
* @version  V1.0
* ����          | �汾          | ����            | ����
* ------------- | ------------- | --------------- | ----
* 2018/10/26    | 1.0.0         | Victor          | �����ļ�
* 2022/04/19    | 1.0.1         | Wenming         | ����Ӣ��ע��
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
* @defgroup magstripe �ſ�
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

#define MAGCARD_READER_DEVICE_NAME          "/dev/magcard0"     /**<@if Chinese �豸�� 			@else	The device name			@endif*/
#define MAGCARD_DECODE_OK                   0                   /**<@if Chinese ������ȷ 		@else	Decode correctly		@endif*/
#define MAGCARD_DECODE_ERR_RAW              1                   /**<@if Chinese ԭʼ���ݴ��� 	@else	Original data error	@endif*/
#define MAGCARD_DECODE_ERR_LRC              2                   /**<@if Chinese LRCУ����� 	@else	LRC verification error	@endif*/
#define MAGCARD_DECODE_ERR_ODD              4                   /**<@if Chinese ��żУ����� 	@else	Parity error			@endif*/
#define MAGCARD_DECODE_NODATA               5                   /**<@if Chinese �޴ŵ����� 		@else	No track data			@endif*/
#define MAGCARD_TRACK_NUM                   3                   /**<@if Chinese �ŵ����� 		@else	Track number			@endif*/


/**
 @if Chinese
* @brief �ſ������ŵ���Ϣ
 @else
* @brief Magnetic card Information about a single track
 @endif
*/
typedef struct track_info {
    int                 bit_pre_code;                           /**<@if Chinese ����λ���� 	@else	Bit length		@endif*/
    uint8_t             start_flag;                             /**<@if Chinese ��ʼ��־ 	@else	Starting logo	@endif*/
    uint8_t             end_flag;                               /**<@if Chinese ������־ 	@else	End mark		@endif*/
    uint8_t             base;                                   /**<@if Chinese ��ֵ 		@else	Base value		@endif*/
} track_info_t;

/**
 @if Chinese
* @brief �ſ�ÿ���ŵ���Ӧ�����ݼ�״̬��
 @else
* @brief The data and status code corresponding to each track of the magnetic card
 @endif
*/
typedef struct magcard_info {
    int                 trackno;                                /**<@if Chinese �ŵ��� 				@else	Track number				@endif*/
    int                 status;                                 /**<@if Chinese �ŵ�״̬�������� 	@else	Track status: error code	@endif*/
    int                 size;                                   /**<@if Chinese ���ݴ�С 			@else	Data size					@endif*/
    uint8_t             data[120];                              /**<@if Chinese �ŵ����� 			@else	Track data					@endif*/
} magcard_info_t;

/**
 @if Chinese
* @brief �ſ�3���ŵ�����
 @else
* @brief Magnetic card 3 track data
@endif
*/
typedef struct user_track_info {
    track_info_t        trackinfo[MAGCARD_TRACK_NUM];           /**<@if Chinese 3���ŵ����� @else	Three track data	@endif*/
} user_track_info_t;

/**
 @if Chinese
* @brief �ſ�����
@else
* @brief Magnetic card data
@endif
*/
typedef struct user_magcard_info {
    magcard_info_t      magcardtrack[MAGCARD_TRACK_NUM];        /**<@if Chinese 3���ŵ����� @else	Three track data	@endif*/
} user_magcard_info_t ;

/**
@if Chinese
* @brief �򿪴ſ��豸
* @param[in]	filename	-	�ſ������豸������/dev/magcard0��,��/dev/magcard1������
* @param[in]	oflags		-	���豸��ģʽ������ģʽ: O_RDONLY ,������ģʽ:(O_RDONLY | O_NONBLOCK)
* @return �򿪵��豸�ļ������� <br>
*   <em> >= 0 </em>	-	�ɹ�,����ֵ���ڲ����ſ������豸���ļ���<br>
*   <em> < 0 </em>	-	ʧ��
@else
* @brief Open the magnetic card device
* @param[in]	filename	-	stripe reader name����/dev/magcard0��,��/dev/magcard1������
* @param[in]	oflags		-	Way to open the device,blocking mode :O_RDONLY;non-blocking mode:(O_RDONLY | O_NONBLOCK)
* @return Open device file descriptor<br>
*   <em> >= 0 </em>	-	success, return value is used to operate card decoding device��s file number <br>
*   <em> < 0 </em>	-	failed
@endif
*/
int magstripe_open(const char *filename, int oflags);

/**
@if Chinese
* @brief �رմſ��豸
* @param[in]	fd	-	�ſ��豸�ļ�������
* @return 
*   <em> 0 </em>	-	�ɹ�<br>
*   <em> ��0 </em>	-	ʧ��
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
* @brief ��ȡ�ſ�����
* @param[in]	fd			-	�ſ��豸�ļ�������
* @param[out]	cardinfo	-	�ſ�����
* @return ��ȡ�Ĵſ�������Ϣ�ܴ�С<br>
*   -<em> ��ֵ����sizeof(user_magcard_info_t): </em> �ɹ�<br>
*   -<em> ��ֵ������sizeof(user_magcard_info_t): </em> ʧ��
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
* @brief �鿴��ǰ�Ƿ���ˢ������
* @param[in]	fd	-	�ſ��豸�ļ�������
* @return �����Ƿ���ˢ������<br>
*   <em> 1 </em>	-	��ˢ������<br>
*   <em> 0 </em>	-	��ˢ������
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

