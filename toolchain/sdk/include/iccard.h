/**
@if Chinese
 * @brief  ��ģ���������� <strong>�Ӵ�ʽIC��ģ��</strong> ��صĽӿ�
 * @author      jeffery
 * @date        2019-01-22
 * @version     V1.0
 *
 * @remarks Change History:
 * ����          | �汾          | ����            | ����
 * ------------- | ------------- | --------------- | ----
 * 2019/01/22    | 1.0.0         | jeffery         | �����ļ�
 * 2022/04/20    | 1.0.1         | Wenming         | ����Ӣ��ע��
@else 
 * @brief  This module is used to describe <strong>IC Card</strong> interfaces module
 * @author      jeffery
 * @date        2019-01-22
 * @version     V1.0
 *
 * @remarks Change History:
 * Date          | Version       | Author          | Desc
 * ------------- | ------------- | --------------- | ----
 * 2019/01/22    | 1.0.0         | jeffery         | Create file
 * 2022/04/20    | 1.0.1         | Wenming         | Add English description
@endif
 */


/**
@if Chinese
 * @defgroup iccard IC��
@else
 * @defgroup iccard IC Card
@endif 
 * @{
*/


#ifndef __ICCARD_H__
#define __ICCARD_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define CVCC_1_8_VOLT       1   /**<@if Chinese IC��VCC����: 1.8v 		@else IC card VCC mode: 1.8v 			@endif*/
#define CVCC_3_VOLT         2   /**<@if Chinese IC��VCC����: 3v 		@else IC card VCC mode: 3v 				@endif*/
#define CVCC_5_VOLT         3   /**<@if Chinese IC��VCC����: 5v 		@else IC card VCC mode: 5v 				@endif*/

#define EMV_MODE            0   /**<@if Chinese ����ģʽ: EMV 			@else operation mode: EMV 				@endif*/
#define ISO_MODE            1   /**<@if Chinese ����ģʽ: ISO standard 	@else operation mode: ISO standard 		@endif*/
#define ISO_19200           2   /**<@if Chinese ����ģʽ: ISO 19200 	@else operation mode: ISO 19200 		@endif*/
#define ISO_38400           3   /**<@if Chinese ����ģʽ: ISO 38400 	@else operation mode: ISO 38400 		@endif*/

#define ISO_SPEED_NORMAL   0
#define ISO_SPEED_HIGH   (3<<30)

/**
@if Chinese
 * @brief          ��IC��������
 * @param[in]	filename	-	���۵�����
 * @return	>=0		-	�豸id�����ڶ�ȡIC����Ϣ��API����ʹ��
 * @return	-1		-	ʧ�ܣ����顰errno����ʵ�ʴ�����
@else 
 * @brief          open ic card reader device
 * @param[in]	filename	-	card slot name
 * @return	>=0	-	device id, used by following reader api function
 * @return	-1	-	failed, please check "errno" for actual error code
@endif 
*/
int iccard_open_cardslot(const char *filename);


/**
@if Chinese
 * @brief         �ر�IC��������
 * @param[in]     fd	-	�򿪶������ľ��, ���� @link iccard_open_cardslot iccard_open_cardslot @endlink�ķ���ֵ
 * @return	0	-	�ɹ�
 * @return	-1	-	ʧ�ܣ����顰errno����ʵ�ʴ�����
@else 
 * @brief         close ic card reader device
 * @param[in]     fd	-	device id, return from @link iccard_open_cardslot iccard_open_cardslot @endlink
 * @return	0	-	success
 * @return	-1	-	failed, please check "errno" for actual error code
@endif 
*/
int iccard_close_cardslot(int fd);


/**
@if Chinese
 * @brief          ��鿨�Ƿ�����ڿ�����
 * @param[in]      fd	-	�򿪶������ľ��, ���� @link iccard_open_cardslot iccard_open_cardslot @endlink�ķ���ֵ
 * @return	0		-	���ڿ�����
 * @return	-1		-	ʧ�ܣ����顰errno����ʵ�ʴ�����
 * @return	ENXIO	-	��δ�ڿ�����
@else 
 * @brief          check if card existed in slot
 * @param[in]      fd	-	device id, return from @link iccard_open_cardslot iccard_open_cardslot @endlink
 * @return	0		-	card in slot
 * @return	-1		-	failed, please check "errno" for actual error code
 * @return	ENXIO	-	card not in slot
@endif 
*/
int iccard_check_card_in_slot(int fd);


/**
@if Chinese
 * @brief         IC���ϵ�
 * @param[in]     fd	-	�򿪶������ľ��, ���� @link iccard_open_cardslot iccard_open_cardslot @endlink�ķ���ֵ
 * @param[in]     vcc	-	VCC����ֵ:
 *          		-	CVCC_1_8_VOLT  
 *          		-	CVCC_3_VOLT   
 *         			-	CVCC_5_VOLT  
 * @param[in]     mode	-	����������:
 *          		-	ISO_MODE        ----- iso7816 ���� 
 *          		-	EMV_MODE        ----- EMV specification ����  
 *          		-	ISO_19200       ----- ���ٿ� iso7816 ����, 19200bps
 *          		-	ISO_38400       ----- ���ٿ� iso7816 ����, 38400bps
 * @param[out]    len	-	atr��Ϣ����
 * @param[out]    atr	-	atr��Ϣ
 * @return         
 *          0		-�ɹ�<br>
 *          -1      -ʧ�ܣ����顰errno����ʵ�ʴ�����<br>
 *          ENXIO   -��δ�ڿ���<br>
 *          EINVAL  -��Ч�Ĳ���<br>
 *          ETIME   -������ʱ<br>
 *          ECOMM   -��żУ������edc����<br>
 *          EPROTO  -����iccard����Ч��Ϣ
 
@else
 * @brief         reset cpucard and get the atr information
 * @param[in]     fd	-	device id, return from @link iccard_open_cardslot iccard_open_cardslot @endlink
 * @param[in]     vcc	-	card operation vcc value:
 *          		-	CVCC_1_8_VOLT    ----- 1.8v voltage
 *          		-	CVCC_3_VOLT      ----- 3v voltage
 *          		-	CVCC_5_VOLT      ----- 5v voltage
 * @param[in]     mode	-	card operation mode:
 *          		-	ISO_MODE        ----- iso7816 mode
 *          		-	EMV_MODE        ----- EMV specification mode
 *          		-	ISO_19200       ----- higher rate iso7816 mode, 19200bps
 *          		-	ISO_38400       ----- higher rate iso7816 mode, 38400bps
 * @param[out]    len	-	length of atr information
 * @param[out]    atr	-	atr information
 * @return         
 *          0       -success<br>
 *          -1      -failed, please check "errno" for actual error code<br>
 *          ENXIO   -card  not in slot<br>
 *          EINVAL  -invalid argument<br>
 *          ETIME   -timeout<br>
 *          ECOMM   -parity error or edc error<br>
 *          EPROTO  -invalid information from iccard<br>
@endif 
*/
int iccard_power_up(int fd, int vcc, int mode, int *len, void *atr);


/**
@if Chinese
 * @brief        �ڶ�������iccard֮�佻��apdu������������IC�����н�����Ϣ��
 * @param[in]    fd        
				- �򿪶������ľ��, ���� @link iccard_open_cardslot iccard_open_cardslot @endlink�ķ���ֵ
 * @param[in]    sendlen   
				- APDU�������ݵĳ���
 * @param[in]    senddata  
				- APDU�������ݵ�ֵ
 * @param[out]   recvlen   
				- APDU�������ݵĳ���
 * @param[out]   recvdata  
				- APDU�������ݵ�ֵ
 * @return        
 *          - 0       �ɹ�
 *          - -1      ʧ�ܣ����顰errno����ʵ�ʴ�����
 *          - ENXIO   ��δ�ڿ���
 *          - EINVAL  ��Ч�Ĳ���
 *          - ETIME   ��ʱ
 *          - ECOMM   ��żУ������edc����
 *          - EPROTO  ��Ч��Ϣ
 *          - EACCES  ��Ƭ��Ҫ������
@else 
 * @brief         Send C-APDU to ICCard, and receive R-APDU from ICCard
 * @param[in]     fd        
				- device id, return from @link iccard_open_cardslot iccard_open_cardslot @endlink
 * @param[in]     sendlen   
				- length of c-apdu information
 * @param[in]     senddata  
				- c-apdu information
 * @param[out]    recvlen   
				- length of r-apdu information from iccard
 * @param[out]    recvdata  
				- r-apdu information from iccard
 * @return     
 *          - 0       success
 *          - -1      failed, please check "errno" for actual error code
 *          - ENXIO   card  not in slot
 *          - EINVAL  invalid argument
 *          - ETIME   timeout
 *          - ECOMM   parity error or edc error
 *          - EPROTO  invalid information from iccard
 *          - EACCES  card need be reset first
@endif 
*/
int iccard_exchange_apdu(int fd, uint32_t sendlen, const void *senddata, uint32_t *recvlen, void *recvdata);


/**
@if Chinese
 * @brief          IC���µ�
 * @param[in]      fd  
				- �򿪶������ľ��, ���� @link iccard_open_cardslot iccard_open_cardslot @endlink�ķ���ֵ
 * @return        
 *          	- 0       �ɹ�
 *          	- -1      ʧ�ܣ����顰errno����ʵ�ʴ�����
@else 
 * @brief          power down iccard
 * @param[in]      fd  
				- device id, return from @link iccard_open_cardslot iccard_open_cardslot @endlink
 * @return         
 *          - 0       success
 *          - -1      failed, please check "errno" for actual error code
@endif 
*/
int iccard_power_down(int fd);

#if 0 //����ӿڹ�����ped��ȡ�����ŵĽӿ����غϣ�����ɾ��
/**
 * @brief          obtain the number of slot, this function used by ped
 * @param          fd  - device id, return from @link iccard_open_cardslot iccard_open_cardslot @endlink
 * @return        
 *          >=0     ----- slot number
 *          -1      ----- failed, please check "errno" for actual error code
*/
int iccard_get_slotnum(int fd);
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ICCARD_H__ */

/** @} */

