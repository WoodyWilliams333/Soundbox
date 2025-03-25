/**
@if Chinese
 * @brief       ��ģ���������� <strong>������ģ��</strong> ��صĽӿ�
 * @author      leely
 * @date        2019-01-22
 * @version     V1.0
 *
 * @remarks Change History:
 * ����          | �汾          | ����            | ����
 * ------------- | ------------- | --------------- | ----
 * 2019/01/22    | 1.0.0         | leely           | �����ļ�
 * 2022/04/20    | 1.0.1         | Wenming         | ����Ӣ��ע��
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
 * @defgroup tp ������
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
/* ����ӿ��Ƿ��б�Ҫ������Ӧ�ò� ? */
struct input_event {
    //struct timeval time;
    uint16_t type;
    uint16_t code;
    int value;
};
#endif

/* ����ӿ��Ƿ��б�Ҫ������Ӧ�ò�: У׼��ʱ����Ҫʹ�õ�����download�����ʹ�ã�����Ӧ�ò����� */
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
  * @brief  ��������TP������Ϣ
@else  
  * @brief  Information about TP contacts
@endif  
  */
struct ts_sample {
    int             x;              /**<@if Chinese TP�����x����(�Ծ������(0,0)Ϊ�ο�) 	@else	X coordinate of TP contact (with absolute zero (0,0) as reference)	@endif*/
    int             y;              /**<@if Chinese TP�����y����(�Ծ������(0,0)Ϊ�ο�) 	@else	Y coordinate of TP contact (with absolute zero (0,0) as reference)	@endif*/
    unsigned int    pressure;       /**<@if Chinese TP�����ѹ��ֵ 							@else	TP contact pressure value											@endif*/
    //struct timeval    tv;
};

/**
@if Chinese
	* @brief ��TS�豸
	* @param[in] filename	-	�ļ�������:"dev/input0"
	* @param[in] oflags		-	�򿪱�־(��δʹ��)
	* @return int
	*
	*          >= 0  �򿪳ɹ�, fd ��Ϊ��ts�豸��ľ��
	*          < 0   ��ʧ��, ���顰errno����ʵ�ʴ�����
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
	 * @brief          �ر�tp�豸
	 * @param          fd	-	���豸�ľ��
	 * @return         int
	 *
	 *          = 0    �ɹ�
	 *          < 0    ʧ��, ���顰errno����ʵ�ʴ�����
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
	* @brief ��ȡtp��Ϣ
	* @param[in]	fd		-	fd�Ǵ�TP�豸���صľ��
	* @param[in]	nr		-	��������
	* @param[out]	samp	-	�¼�λ��
	 * @return         int
	 *
	 *          > 0     ��ȡTP����
	 *          < 0     û���κ������¼�
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

