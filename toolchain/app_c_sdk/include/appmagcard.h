/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app magcardģ��</strong> ��صĽӿ�
	 * @par �ļ�    appmagcard.h
	 * @author		yangjing
	 * @date        2020-04-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-04-09    | 1.0.0        | yanjing       | �����ļ�
	 * 2022-04-19    | 1.0.1        | lydia         | ����Ӣ��ע��  
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
	@defgroup appmagcard ������
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
	@brief  �ŵ�LRCУ��ö��.
 @else
	@brief  This enumerated type lists track LRC verification.
 @endif
  */
typedef enum 
{ 
	LRC_TRACK1 = 0x01,		/**< @if Chinese �ŵ�1 LRCУ��  @else track1 LRC verification @endif */
	LRC_TRACK2 = 0x02,		/**< @if Chinese �ŵ�2 LRCУ��  @else track2 LRC verification @endif */
	LRC_TRACK3 = 0x04,		/**< @if Chinese �ŵ�3 LRCУ��  @else track3 LRC verification @endif */
}TrackLrc;
  
/**
 @if Chinese
	@brief  �����������ຯ������ֵö��.
 @else
	@brief  This enumerated type lists return value of magnetic stripe card.
 @endif
  */
typedef enum 
{ 
	UTRACK_MAG_FAIL		= -5,	/**< @if Chinese ����������������ʧ��  @else magnetic stripe card reader operation failed @endif */ 
	UTRACK_NOEVENT		= -4,	/**< @if Chinese ���ȴ�ʱ�Ż᷵�أ�˵�����ε���δ��⵽ˢ��  @else return when no wait,indicating the card is not detected @endif */ 
	UTRACK_CONTROL		= -3,	/**< @if Chinese �û��˳�  @else user exit @endif */   
	UTRACK_TIMEOUT		= -2,	/**< @if Chinese ˢ����ʱ  @else card swiping timeout @endif */  
	UTRACK_FAIL			= -1,	/**< @if Chinese ˢ��ʧ��  @else card swiping fail @endif */  
	UTRACK_OK			= 0,	/**< @if Chinese ˢ���ɹ�  @else card swiping success @endif */
	UTRACK_MAG_OK		= 1,	/**< @if Chinese �����������������ɹ� @else magnetic stripe card reader operation success @endif */
	UTRACK_NUM			= 2,	/**< @if Chinese ���俨��(Ԥ��)  @else manual card number @endif */
}SwipCardRet; 

/*!
 @if Chinese
	@brief		����������ģ���ʼ��
	@return		UTRACK_MAG_OK-�ɹ���UTRACK_MAG_FAIL-ʧ��
 @else
	@brief		magnetic stripe card reader init
	@return		UTRACK_MAG_OK-success��UTRACK_MAG_FAIL-fail
 @endif
*/ 
extern int app_mag_init(void);

/*!
 @if Chinese
	@brief		��ȡ�ŵ���Ϣ
	@param[out]	CardBuf1	-	1�ŵ����ݱ����ַ
	@param[out]	CardBuf2	-	2�ŵ����ݱ����ַ
	@param[out]	CardBuf3	-	3�ŵ����ݱ����ַ
	@param[in]	LrcFlag		-	�Ƿ�����lrcУ���ʶλ(��������δʹ��)
	@param[in]	WaitFlag	-	�Ƿ������ȴ���ʶλ(��������δʹ��)
	@return		�ο�SwipCardRetö��ֵ
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
	@brief		�رմ���������ģ��
	@return		�ο�SwipCardRetö��ֵ
 @else
	@brief		close magnetic stripe card reader
	@return		reference enum SwipCardRet
 @endif
*/ 
extern int app_mag_close(void);

/*!
 @if Chinese
	@brief		����Ƿ���ˢ��
	@return		�ο�SwipCardRetö��ֵ
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


