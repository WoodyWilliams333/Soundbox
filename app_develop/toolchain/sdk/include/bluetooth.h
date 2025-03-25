/**
 * @file    bt.h
 *          
 * @author  Brian.Yang <brian.yang@newpostech.com>.
 *          
 * @date    2018-06-21
 *          
 * @brief  Bluetooth api   
 *          
 * @note    
 *          
 * Modification history
 * ----------------------------------------------------------------------------
 * Date         Version  Author       History
 * 2019-08-06   1.0.1   Milton.Wu     Add doxygen comment
 * ----------------------------------------------------------------------------
 *
 */
/** 
* @defgroup bluetooth ����
* @{
*/ 
#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name BT_PARIING_MODE �������ģʽ
 * @{
 */ 
#define PAIRING_MODE_PINCODE        (0x00)
#define PAIRING_MODE_JUSTWORK       (0x01)
#define PAIRING_MODE_PASSKEY        (0x02)
#define PAIRING_MODE_CONFIRM        (0x03)
/**
 * @}
 */

/**
 * @name BT_VISIBLE_MODE ������ʶ��ģʽ 
 * @{
 */ 
#define VISIBLE_BT                  (0x03)      /**< bit0:BT3.0 �ɷ���;bit1::BT3.0 ������ */
#define VISIBLE_BLE                 (0x04)      /**< bit2:BLE �ɷ��֣�ADV �㲥��*/
#define VISIBLE_ALL                 (VISIBLE_BT | VISIBLE_BLE) 
/**
 * @}
 */

#define BT_ON                       (0x01)    /**< �򿪵�ѹ���*/  
#define BT_OFF                      (0x00)    /**< �رյ�ѹ���*/

#define BT_MATCH_OK                 (0x00)    /**< CONFIRM_GKEY��Կƥ�� */
#define BT_MATCH_ERR                (0x01)    /**< CONFIRM_GKEY��Կ��ƥ�� */

/**
 *@if CN
	* @name BT_PAIRING_STATUS �������״̬
 *@else
	* @name BT_PAIRING_STATUS bluetooth Bluetooth pairing status
 * @{
 */
#define PAIRING_IDLE                (0x0) /**< @if CN  ����� @else pairing idle @endif*/
#define PAIRING_FAIL                (0x1) /**< @if CN  ���ʧ�� @else pairing fail @endif*/
#define PAIRING_SUCCESS             (0x2) /**< @if CN  ��Գɹ� @else pairing succcess @endif*/
#define PAIRING_SET_PASSKEY         (0x3) /**< @if CN  �ֻ�����ʾPASSKEY @else The PASSKEY is displayed on mobile phone @endif*/
#define PAIRING_GET_PASSKEY         (0x4) /**< @if CN  ��ȡ��PASSKEYֵ�����ֻ������Ӧ��PASSKEYֵ������� @else Gets the PASSKEY value, input the corresponding PASSKEY value into the phone for pairing @endif*/
#define PAIRING_BT_COMFIRM          (0x5) /**< @if CN  BT����COMFIRM @else BT request COMFIRM @endif*/
#define PAIRING_BLE_COMFIRM         (0x6) /**< @if CN  BLE����COMFIRM @else BLE request COMFIRM @endif*/

/**
 * @brief     �������豸���������豸�ļ�������
 * @param[in] filename �豸�ļ��� "/dev/bt"
 * @param[in] oflags   ��ѡ��
 * @return   �豸���ļ������� <br>
 *   <em> >= 0 </em>     ----success <br>
 *   <em> else </em>     ----failed, �ɸ���errno��ȡ������
 */
int bt_open(const char *filename, int oflags);

/**
 * @brief     �ر������豸
 * @param[in] fd �豸���ļ�������
 * @return    ����ֵ<br>
 *   <em> >= 0 </em>     ----success <br>
 *   <em> else </em>     ----failed, �ɸ���errno��ȡ������
 */
int bt_close(int fd);

/**
 * @brief     �������ݷ���
 * @param[in] fd �豸���ļ�������
 * @param[in] data ��������
 * @param[in] data_len �������ݳ���
 * @return    ����ֵ<br>
 *   <em> >= 0 </em>     ----�������ݳ��� <br>
 *   <em> else </em>     ----failed, �ɸ���errno��ȡ������
 */
int bt_send(int fd, const void *data, uint32_t data_len);

/**
 * @brief     ������������
 * @param[in] fd �豸���ļ�������
 * @param[in/out] data ��������
 * @param[in] data_len ���������ݳ���
 * @return    ����ֵ<br>
 *   <em> >= 0 </em>     ----�������ݳ��� <br>
 *   <em> else </em>     ----failed, �ɸ���errno��ȡ������
 */
int bt_recv(int fd, void *data, uint32_t data_len);

/**
 * @brief     ��������
 * @param[in] fd �豸���ļ�������
 * @return    ����ֵ<br>
 *   <em> >= 0 </em>     ----success <br>
 *   <em> else </em>     ----failed, �ɸ���errno��ȡ������
 */
int bt_reset(int fd);

/**
 * @brief     ��������״̬ 
 * @param[in] fd �豸���ļ�������
 * @return    ģ��״̬<br>
 *   <em> bit5: </em>     BLE ������
 */
int bt_get_status(int fd);

/**
 * @brief     �Ͽ���������
 * @param[in] fd �豸���ļ�������
 * @return    ����ֵ<br>
 *   <em> >= 0 </em>     ----success <br>
 *   <em> else </em>     ----failed, �ɸ���errno��ȡ������
 */
int bt_disconnect(int fd);

/*��֧��bt_standby_enable��bt_standby_disable*/
int bt_standby_enable(int fd);
int bt_standby_disable(int fd);

/**
 * @brief    ��ȡ��������  
 * @param[in] fd         �豸���ļ������� 
 * @param[in/out] name_str   ���ڴ洢name��buffer
 * @param[in] str_len    buffer��С��������С33�ֽ�, ��ΪҪ�洢��β��'\0'
 * @return    �������Ƴ���<br>
 *   <em> >= 0 </em>     ----strlen(name_str) <br>
 *   <em> <0 </em>     ----failed, �ɸ���errno��ȡ������
 */
int bt_get_name(int fd, char *name_str, int str_len);

/**
 * @brief     ������������  
 * @param[in] fd         �豸���ļ������� 
 * @param[in] name_str   ���ڴ洢name��buffer
 * @param[in] str_len    strlen(name_str)
 * @return    ����ֵ<br>
 *   <em> >= 0 </em>     ----success <br>
 *   <em> else </em>     ----failed, �ɸ���errno��ȡ������
 */ 
int bt_set_name(int fd, const char *name_str, int str_len);

/*��֧�ֻ�ȡpincode*/
int bt_get_pincode(int fd, void *data, int len);

/**
 * @brief     ��������PIN��
 * @param[in] fd         �豸���ļ������� 
 * @param[in] data       ���ڴ洢PIN���buffer
 * @param[in] len        PIN����
 * @return    ����ֵ<br>
 *   <em> >= 0 </em>     ----success <br>
 *   <em> else </em>     ----failed, �ɸ���errno��ȡ������
 */ 
/*��֧��bt_set_pincode*/
int bt_set_pincode(int fd, const void *data, int len);

/**
 * @brief     ��ѯ�����̼��汾��
 * @param[in] fd         �豸���ļ������� 
 * @param[in/out] data   ���ڴ洢�̼���buffer
 * @param[in] len        data��С,���2�ֽ�
 * @return    ����ֵ<br>
 *   <em> >= 0 </em>     ----�汾��Ϣʵ�ʳ��� <br>
 *   <em> else </em>     ----failed, �ɸ���errno��ȡ������
 */
/*��֧��bt_get_version*/
int bt_get_version(int fd, void *data, int len);

/**
 * @brief     ��ѯ�����̼��汾�ź�@ref bt_get_version() ��ѯ�����ͬ
 * @param[in] fd         �豸���ļ������� 
 * @param[in/out] data   ���ڴ洢�̼���buffer
 * @param[in] len        data��С,���2�ֽ�
 * @return    ����ֵ<br>
 *   <em> >= 0 </em>     ----�汾��Ϣʵ�ʳ��� <br>
 *   <em> else </em>     ----failed, �ɸ���errno��ȡ������
 */ 
/*��֧��bt_eeprom_version*/
int bt_eeprom_version(int fd, void *data, int len);

/**
 * @brief     ��ȡ����MAC��ַ 
 * @param[in] fd         �豸���ļ������� 
 * @param[in/out] data   MAC��ַ��buffer
 * @param[in] len        data��С,���6�ֽ�
 * @return    ����ֵ<br>
 *   <em> >= 0 </em>     ----MACʵ�ʳ���<br>
 *   <em> else </em>     ----failed, �ɸ���errno��ȡ������
 */ 
int bt_local_addr(int fd, void *data, int len);

/**
 * @brief     ��������MAC��ַ 
 * @param[in] fd         �豸���ļ������� 
 * @param[in] data       MAC����
 * @param[in] len        MAC���ݴ�С��6�ֽ�
 * @return    ����ֵ<br>
 *   <em> = 0 </em>     ----success <br>
 *   <em> < 0 </em>     ----failed, �ɸ���errno��ȡ������
 */ 
/*��֧��bt_set_local_addr*/
int bt_set_local_addr(int fd, const void *data, int len);

/**
 * @brief     ��ȡ�����Ϣ
 * @param[in] fd         �豸���ļ������� 
 * @param[in/out] data   �洢�����Ϣ��buffer
 * @param[in] len        buffer��С����ȫ�����Ҫ�����170�ֽ�
 * @return    ����ֵ<br>
 *   <em> > 0 </em>     ----��ȡ�����ݴ�С<br>
 *   <em> < 0 </em>     ----failed, �ɸ���errno��ȡ������
 */  
int bt_paired_info_get(int fd, void *data, int len);

/**
 * @brief     ���������Ϣ,�������ȡ�������Ϣ����Ϊ120�ֽڻ�170�ֽڣ���������Ӧ��Ϊȫ0
 * @param[in] fd         �豸���ļ������� 
 * @return    ����ֵ<br>
 *   <em> >= 0 </em>     ----success <br>
 *   <em> < 0 </em>     ----failed, �ɸ���errno��ȡ������
 */   
int bt_paired_info_erase(int fd);

/**
 * @brief     �������ģʽ
 * @param[in] fd         �豸���ļ������� 
 * @param[in] mode       ���ģʽ,ȡֵ�ο�@ref BT_PARIING_MODE
 * @return    ����ֵ<br>
 *   <em> >=0 </em>     ----success <br>
 *   <em> < 0 </em>     ----failed, �ɸ���errno��ȡ������
 */  
int bt_pairing_mode_set(int fd, uint8_t mode);

/**
 * @brief     ��ȡ���ģʽ
 * @param[in] fd         �豸���ļ������� 
 * @param[in] mode       ���ģʽ,ȡֵ�ο�@ref BT_PARIING_MODE
 * @return    ����ֵ<br>
 *   <em> >=0 </em>     ----���ģʽ ȡֵ�ο�@ref BT_PARIING_MODE<br>
 *   <em> < 0 </em>     ----failed, �ɸ���errno��ȡ������
 */
int bt_pairing_mode_get(int fd);

/**
 * @brief     ����passkey���̶�4�ֽ�
 * @param[in] fd         �豸���ļ������� 
 * @param[in] data       �洢passkey��buffer
 * @param[in] len        passkey���ȣ�4�ֽ�
 * @return    ����ֵ<br>
 *   <em> =0 </em>      ----success<br>
 *   <em> < 0 </em>     ----failed, �ɸ���errno��ȡ������
 * @note    passkeyΪ���ʱ�ֻ���Ҫ�����6λ���� <br>
 *      ��uint32_t passkey = 123456���ֻ���Ҫ����123456
 */
int bt_entry_passkey(int fd, const void *data, int len);

/**
 * @brief     �����ȴ�(timeout_sec)��,ֱ������PASSKEYģʽ��ȴ���ʱ
 * @param[in] fd         �豸���ļ������� 
 * @param[in] timeout_sec  �ȴ���ʱʱ�䣬��λ:��
 * @return    ����ֵ<br>
 *   <em> =0 </em>      ----�ɹ�����PASSKEY���״̬����һ����������PASSKEY<br>
 *   <em> < 0 </em>     ----failed, �ɸ���errno��ȡ������
 * @note    ����PASSKEY���ģʽ<br>
 *      1.�ȵ���@ref bt_pairing_mode_set() �������ģʽΪ@ref PAIRING_MODE_PASSKEY
 *      2.�ٵ��ýӿ�@ref bt_entry_passkey_paired()��Ȼ���ֻ�������ԣ��˽ӿڷ���
 *      3.����@ref bt_entry_passkey() �����ֻ�����ʾ��PASSKEY��������
 */ 
int bt_entry_passkey_paired(int fd, unsigned long timeout_sec);

/**
 * @brief     ���������Ŀɷ��ֺ͹㲥״̬
 * @param[in] fd         �豸���ļ������� 
 * @param[in] visible_mode  �ɼ�ģʽ,ȡֵ�ο�@ref BT_VISIBLE_MODE
 * @return    ����ֵ<br>
 *   <em> =0 </em>      ----success<br>
 *   <em> < 0 </em>     ----failed, �ɸ���errno��ȡ������
 */ 
/*��֧��bt_set_visible*/
int bt_set_visible(int fd, uint8_t visible_mode);
/*��֧��bt_set_uart_baud*/
int bt_set_uart_baud(int fd, const char *baud_str);

/**
 * @brief     ��������BT3.0 class of device
 * @param[in] fd         �豸���ļ������� 
 * @param[in] data       ���ڴ洢cod��buffer
 * @param[in] len        cod����, 3�ֽ�
 * @return    ����ֵ<br>
 *   <em> =0 </em>      ----success<br>
 *   <em> < 0 </em>     ----failed, �ɸ���errno��ȡ������
 */ 
 /*��֧��bt_set_cod*/
int bt_set_cod(int fd, const void *data, int len);

/**
 * @brief     ����������˯��ģʽ
 * @param[in] fd         �豸���ļ������� 
 * @return    ����ֵ<br>
 *   <em> =0 </em>      ----success<br>
 *   <em> < 0 </em>     ----failed, �ɸ���errno��ȡ������
 */ 
/*��֧��bt_enter_sleep*/
int bt_enter_sleep(int fd);

/**
 * @brief     ����BLE ADV DATA(�͹��������㲥����)
 * @param[in] fd         �豸���ļ������� 
 * @param[in] data       ���ڴ洢ADV��buffer
 * @param[in] len        ADV����,��Χ:1-62
 * @return    ����ֵ<br>
 *   <em> =0 </em>      ----success<br>
 *   <em> < 0 </em>     ----failed, �ɸ���errno��ȡ������
 */
/*��֧��bt_set_adv_data*/
int bt_set_adv_data(int fd, const void *data, int len);

/**
 * @brief     ��ѯģ���Դ��ѹ
 * @param[in] fd         �豸���ļ������� 
 * @param[in/out] data    ���ڴ洢��ѹ��buffer
 * @param[in] len         buffer��С,��СΪ2
 * @return    ����ֵ<br>
 *   <em> >=0 </em>      ----�洢��ѹbuffer����<br>
 *   <em> < 0 </em>     ----failed, �ɸ���errno��ȡ������
 * @note    ��ȡ��ѹ��2 ���� byte �ĵ�ѹֵ
 *          2 �� byte Ϊ����������һ�� byte Ϊ��ѹֵ���������֣�
 *          �ڶ��� byte Ϊ��ѹֵ��С�����֣�2 �� byte ��Ϊʮ�����ơ�
 *          �� 03 22 Ϊ 3.34V 
 */
/*��֧��bt_get_volatge*/
int bt_get_volatge(int fd, void *data, int len);

/**
 * @brief     ����ģ���ȡ��Դ��ѹ���ܿ���
 * @param[in] fd         �豸���ļ������� 
 * @param[in] on_off     ��ѹ����Ƿ��
 *  <em> BT_ON </em>      ----�򿪵�ѹ���<br>
 *  <em> BT_OFF </em>     ----�رյ�ѹ���<br>
 * @return    ����ֵ<br>
 *   <em> =0 </em>      ----success<br>
 *   <em>else </em>     ----failed, �ɸ���errno��ȡ������
 */
/*��֧��bt_set_voltage_detect*/
int bt_set_voltage_detect(int fd, uint8_t on_off);

 /**
 * @brief     ȷ��GKEY�Ƿ���ȷ
 * @param[in] fd         �豸���ļ������� 
 * @param[in] confirm     
 *  <em> BT_MATCH_OK </em>      ----��Կƥ��<br>
 *  <em> BT_MATCH_ERR </em>     ----��Կ��ƥ��<br>
 * @return    ����ֵ<br>
 *   <em> =0 </em>      ----success<br>
 *   <em>else </em>     ----failed, �ɸ���errno��ȡ������
 */
int bt_user_confirm(int fd, int confirm);

/** 
 * @brief       ��������ȡGKEY
 * @param[in] fd         �豸���ļ�������  
 * @param[in/out] data : �洢GKEY��buffer
 * @param[in] len  :     buffer��С������С��GKEY����4�ֽ�
 * @return ����ֵ<br>
 *   <em> >=0 </em>      ��ȡGKEY��ʵ�ʳ���<br>
 *   <em>else </em>     ----failed, �ɸ���errno��ȡ������ 
 * @note        : �������ֵΪ-EAGAIN(-11),��ʾ��Ҫ��һ�����Ի�ȡ<br>
 *               CONFIRM GKEY��Է�ʽΪ <br>
 *               1.�ȵ���@ref bt_pairing_mode_set() �������ģʽΪ@ref PAIRING_MODE_CONFIRM <br>
 *               2.�ٷ�������@ref bt_user_confirm_passkey() ��ȡGKEY <br>
 *               3.�ֻ��˷�����������bt_user_confirm_passkey() ��ȡGKEY�ɹ� <br>
 *               4.�Ա��ֻ�����ʾ��GKEY���ȡ��GKEY, ����@ref bt_user_confirm() ȷ�ϻ�ȡ��GKEY�Ƿ���ȷ<br>
 *               5.ȷ��GKEY��������Գɹ�������ʧ��
 */
int bt_user_confirm_passkey(int fd, void *data, int len);

/** 
 * @brief       �ı���������, ÿ�δ�������������Ч�������棬�����رջ�reset��ʧЧ 
 * @param[in] fd         �豸���ļ�������  
 * @param[in] name_str : �����name
 * @param[in] str_len  :  strlen(name_str)
 * @return ����ֵ<br>
 *   <em> =0 </em>      ----success <br>
 *   <em>else </em>     ----failed, �ɸ���errno��ȡ������
 * @note    :    ����Ӧ�ó����޸��������ƣ�������
 *               ϵͳ�޸��������ƣ�ʹ��@ref bt_set_name(), ���ñ��� 
 */
int bt_change_name(int fd, const char *name_str, int str_len);

/** 
 * @brief       �鿴�������ջ����ж�������
 * @param[in] fd         �豸���ļ�������  
 * @return ����ֵ<br>
 *   <em> >=0 </em>      ----�������ջ������ݳ��� <br>
 *   <em>else </em>      ----failed, �ɸ���errno��ȡ������
 */ 
int bt_peek_rx_len(int fd);

/** 
 * @brief       ����ble justwork/comfirm���ģʽ��ʼ���
 * @param[in] fd         �豸���ļ�������  
 * @return ����ֵ<br>
 *   <em> =0 </em>      ----success<br>
 *   <em>else </em>     ----failed, �ɸ���errno��ȡ������
 */ 
int bt_ble_start_pairing(int fd);

/**
 *@if CN
	 * @brief     �����������״̬ 
	 * @param[in] fd �豸���ļ�������
	 * @param[out] status ���״̬@ref BT_PAIRING_STATUS
	 * @param[out] nvcnt nv��������Գɹ�nv��������
	 * @return ����ֵ<br>
	 *	 <em> =0 </em>		----success<br>
	 *	 <em>else </em> 	----failed, �ɸ���errno��ȡ������
 *@else
	* @brief     get bluetooth status
	* @param[in] fd file description of device
	* @param[out] status pairing status@ref BT_PAIRING_STATUS
	* @param[out] nvcnt nv count,NV count increases with successful pairing
	* @return ����ֵ<br>
	 *	 <em> =0 </em>		----success<br>
	 *	 <em>else </em>     ----failed, errno is set appropriately
 *@endif	 
 */
int bt_get_pairing_status(int fd, uint32_t *status, uint32_t *nvcnt);



#ifdef __cplusplus
}
#endif

#endif /* __BT_H__ */
/** @} */

