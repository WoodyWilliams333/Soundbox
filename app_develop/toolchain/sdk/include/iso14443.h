/**
@if Chinese
* @brief    ��ģ���������� <strong>�ǽӿ�ģ��</strong> ��صĽӿ�
* @details  ֧��ISO14443Э��ķǽӿ�[TYPE A, TYPE B]
* @author   Neal
* @date     2010-10-14
* @version  V1.0
* @remarks Change History:
* ����          | �汾          | ����            | ����
* ------------- | ------------- | --------------- | ----
* 2010/10/14    | 1.0.0         | Neal            | �����ļ�
* 2018/10/26    | 1.0.1         | Victor          | ���doxygenע����Ϣ
* 2022/04/20    | 1.0.2         | Wenming         | ����Ӣ��ע��
@else
* @brief    This module is used to describe <strong>NFC Card</strong> interfaces module
* @details  Support the ISO14443 protocol non - access card[TYPE A, TYPE B]
* @author   Neal
* @date     2010-10-14
* @version  V1.0
* @remarks Change History:
* Date          | Version       | Author          | Desc
* ------------- | ------------- | --------------- | ----
* 2010/10/14    | 1.0.0         | Neal            | Create file
* 2018/10/26    | 1.0.1         | Victor          | Add doxyGen comment information
* 2022/04/20    | 1.0.2         | Wenming         | Add English description
@endif
*/

/**
@if Chinese
* @defgroup nfc �ǽӿ�
@else
* @defgroup nfc NFC Card
@endif
* @{
*/

#ifndef ISO14443_H_
#define ISO14443_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined(__KERNEL__)
enum {
    MIF_TYPE_A      = 0x00,                 /**<@if Chinese ����A 		@else TypeA              @endif*/
    MIF_TYPE_B,                             /**<@if Chinese ����B 		@else  TypeB              @endif*/
    MIF_TYPE_C1,                            /**<@if Chinese ����C1 		@else  FeliCa, 212kbits/s @endif*/
    MIF_TYPE_C2,                            /**<@if Chinese ����C2 		@else  FeliCa, 424kbits/s @endif*/
    MIF_TYPE_UNKNOWN,                       /**<@if Chinese δ֪���� 	@else  unknown type       @endif*/
};
#else

#define MIF_TYPE_A              0x00    /**<@if Chinese ����A 	@else TypeA              @endif*/
#define MIF_TYPE_B              0x01    /**<@if Chinese ����B 	@else TypeB              @endif*/
#define MIF_TYPE_C1             0x02    /**<@if Chinese ����C1 	@else FeliCa, 212kbits/s @endif*/
#define MIF_TYPE_C2             0x03    /**<@if Chinese ����C2 	@else FeliCa, 424kbits/s @endif*/
#define MIF_TYPE_UNKNOWN        0x04    /**<@if Chinese δ֪���� @else unknown type       @endif*/
#endif

#ifdef CFG_EMV_L1_TEST
/* @brief �����ڶԷǽ�EMV-L1��֤
 */
typedef struct {
    uint32_t    nfc_wait_tp_time;
    uint32_t	FWT_ATQB;
    uint32_t	FDT_a_picc_min;
    uint32_t	FDT_pcd_min;
}nfc_time_param_t;
#endif

/**
@if Chinese
* @brief �򿪷ǽӶ������豸���������豸�ļ�������
* @param[in]	filename	-	�豸�ļ��� "/dev/nfc"
* @return		fd  		-	�豸���ļ������� <br>
*   <em> >= 0 </em>     ----�ɹ� <br>
*   <em> ���� </em>     ----ʧ��, �ɸ���errno��ȡ������
@else
* @brief Opens MIF card reader device and returns the device file descriptor
* @param[in] filename	-	Device name "/dev/nfc"
* @return  	fd 			-	The file descriptor for the device <br>
*   <em> >= 0 </em>     ----success <br>
*   <em> other </em>     ----failed, You can obtain the error code according to errno
@endif 
*/
int mif_open(const char *filename);

//#define nfc_open mif_open ������������߶�����ʹ��

//int mif_get_sp_fd(void); //����ɾ��

/**
@if Chinese
* @brief �رշǽӶ������豸
* @param[in]	fd		-	�ǽӶ������豸�ļ�������
* @return ����ֵ <br>
*   <em> 0 </em>    ----�ɹ� <br>
*   <em> ���� </em>     ----ʧ��, �ɸ���errno��ȡ������
@else
* @brief close MIF device
* @param[in]	fd		-	The file descriptor for the device
* @return int <br>
*   <em> 0 </em>    ----success <br>
*   <em> other </em>     ----failed, You can obtain the error code according to errno
@endif 
*/
int mif_close(int fd);

/**
@if Chinese
* @brief �򿪷ǽӶ������豸���������豸�ļ�������
* @param[in]	filename	-	�豸�ļ��� "/dev/nfc"
* @return   �豸���ļ������� <br>
*   <em> >= 0 </em>     ----�ɹ� <br>
*   <em> ���� </em>     ----ʧ��, �ɸ���errno��ȡ������
* @note ���� @ref mif_open �ı���������ʹ��Ч���� @ref mif_open ��ȫһ��
@else
* @brief Open NFC device,return the file descriptor
* @param[in]	filename	-	Device name "/dev/nfc"
* @return   fd <br>
*   <em> >= 0 </em>     ----success <br>
*   <em> other </em>     ----failed, You can obtain the error code according to errno
* @note The effect is the same as @ref mif_open 
@endif 
*/
int nfc_open(const char *filename);

/**
@if Chinese
* @brief �رշǽӶ������豸
* @param[in]	fd	-	�ǽӶ������豸�ļ�������
* @return ����ֵ <br>
*   <em> 0 </em>    ----�ɹ� <br>
*   <em> ���� </em>     ----ʧ��, �ɸ���errno��ȡ������
* @note ���� @ref mif_close �ı���������ʹ��Ч���� @ref mif_close ��ȫһ��
@else
* @brief Close NFC device
* @param[in]	fd	-	NFC card reader device file descriptor
* @return return value <br>
*   <em> 0 </em>    ----success <br>
*   <em> other </em>     ----failed, You can obtain the error code according to errno
* @note The effect is the same as @ref mif_close 
@endif
*/
int nfc_close(int fd);

/**
@if Chinese
* @brief ����MIF��ʱ�Ľṹ���Ա����
@else
* @brief Structure member resolution on MIF timeouts
@endif
**/
struct mif_timeout {
    uint32_t WaitTime_PollTypeA;    /**<@if Chinese ��TypeA��ѯ������PCD��PICC��֡�ӳ�ʱ��(��λ:us��Ĭ��:100us)  	@else The Frame Delay Time PCD to PICC during TypeA poll procedure (Unit:us, default: 100us) 		@endif*/
    uint32_t WaitTime_PollTypeB;    /**<@if Chinese ��TypeB��ѯ������PCD��PICC��֡�ӳ�ʱ��(��λ:etu��Ĭ��:500etu)  	@else The Frame Delay Time PCD to PICC during TypeB poll procedure (Unit:etu, default: 500etu) 		@endif*/
    uint32_t WaitTime_Mifare;       /**<@if Chinese mifare����ͳ��Ῠ�����ڼ��֡�ȴ�ʱ��(��λ:etu��Ĭ��:10240etu)	@else The Frame Wait Time during mifare classic and ultralight card opertaion (Unit:etu, default: 10240etu) @endif*/
    uint32_t WaitTime_RATS;         /**<@if Chinese T=CL������ʱ֡�ȴ�ʱ��(��λ:etu��Ĭ��:500etu)  					@else The Frame Wait Time during T=CL card activate (Unit:etu, default: 500etu) 					@endif*/
    uint32_t WaitTime_CardResponse; /**<@if Chinese PICC�ȴ���Ӧ�����֡�ȴ�ʱ��(��λ:etu��Ĭ��:573440etu)  		@else The maxium Frame Wait Time during waiting response from PICC (Unit:etu, default: 573440etu) 	@endif*/
    uint32_t WaitTime_CompleteCmd;  /**<@if Chinese PCD��PICC���һ�����ݽ��������ȴ�ʱ��(��λ:ms��Ĭ��:6000ms)  	@else The maxium Wait Time for completing one data exchange between PCD and PICC (Unit:ms, default: 6000ms) @endif*/
    uint32_t WaitTime_DelayBefore;  /**<@if Chinese PICC��PCD��֡�ӳ�ʱ��(��λ:us��Ĭ��:500us)  					@else The Frame Delay Time PICC to PCD (Unit:us, default: 500us) 									@endif*/
    uint32_t WaitTime_IdleRF;       /**<@if Chinese �ز��ر�ʱ���ӳ�ʱ��(��λ:ms��Ĭ��:6ms)  						@else The delay time while carrier off (Unit:ms, default: 6ms) 										@endif*/
};
int mif_set_timeout(const struct mif_timeout *ptime);
int mif_get_timeout(struct mif_timeout *ptime);

int iso14443_delay_etu(int fd, uint32_t numofetu);

/**
@if Chinese
* @brief ��λ�ǽӿ�Ƭ
* @param[in]	fd	-	�ǽӶ������豸�ļ�������
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> ���� </em>     ----ʧ��, �ɸ���errno��ȡ������
@else
* @brief Reset the iso14443 card
* @param[in] 	fd	-	Iso14443 card device file descriptor
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> other </em>     ----failed, You can obtain the error code according to errno
@endif
**/
int iso14443_reset_picc(int fd);

/**
@if Chinese
* @brief ���÷ǽӶ�����Ӳ���ӿ�����
* @param[in] 	fd 		-	�ǽӶ������豸�ļ�������
* @param[in] 	type 	-	�ǽӶ�����Ӳ���ӿ�����,����Ϊ��������:<br>
*                 0x00  ----- ISO14443 TypeA    <br>
*                 0x01  ----- ISO14443 TypeB    <br>
*                 0x02  ----- Sony FeliCa, 212kbits/s   <br>
*                 0x03  ----- Sony FeliCa, 424kbits/s   
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ� <br>
*   <em> ���� </em>     ----ʧ��, �ɸ���errno��ȡ������
@else
* @brief Set the MIF card device interface type
* @param[in]	fd		-	Mif card device file descriptor
* @param[in]	type 	-	MIF card reader Hardware interface type:<br>
*                 0x00  ----- ISO14443 TypeA    <br>
*                 0x01  ----- ISO14443 TypeB    <br>
*                 0x02  ----- Sony FeliCa, 212kbits/s   <br>
*                 0x03  ----- Sony FeliCa, 424kbits/s   
* @return <br>
*   <em> 0 </em>    ----success <br>
*   <em> other </em>     ----failed, You can obtain the error code according to errno
@endif 
*/
int mif_select_carrier_type(int fd, int32_t type);

/**
@if Chinese
* @brief ����Ƭ����REQAָ��
* @param[in]	fd 		-	�ǽӶ������豸�ļ�������
* @param[out]	atqa 	-	��Ƭ�Ը�ָ���Ӧ��[2 Byte]
* @return ����ֵ    <br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.����Ϊ������ӳ����Ϣ:<br>
*               EINVAL  ---- ��Ч�Ĳ���         <br>
*               EIO     ---- Ӳ������           <br>
*               ECOMM   ---- ��żУ������CRC����           <br>
*               EPROTO  ---- ��Ƭ����Ӧ��ISO14443������  <br>
*               EBADE   ---- ��Ƭ���ش�����Ӧ��Ϣ           <br>
*               ETIME   ---- ��ʱ           <br>
*               EMULTIHOP   ---- ��Ƶ�����ж��ſ�            <br>
@else
* @brief Send REQA to card
* @param[in] 	fd 		-	iso14443 card device file descriptor
* @param[out] 	atqa 	-	The card's response to this command[2 Byte]
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument           <br>
*               EIO     ---- hardware error           <br>
*               ECOMM   ---- Parity Error or CRC error           <br>
*               EPROTO  ---- the response from card not compatile with ISO14443  <br>
*               EBADE   ---- card return error response information           <br>
*               ETIME   ---- timeout           <br>
*               EMULTIHOP   ---- more than one card in RF field            <br>
@endif 
*/
int iso14443_ReqA(int fd, void *atqa);

/**
@if Chinese
* @brief ����Ƭ����WUPAָ��
* @param[in]	fd		-	�ǽӶ������豸�ļ�������
* @param[out]	atqa	-	��Ƭ�Ը�ָ���Ӧ��[2 Byte]
* @return ����ֵ    <br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.����Ϊ������ӳ����Ϣ:<br>
*               EINVAL  ---- ��Ч�Ĳ���           <br>
*               EIO     ---- Ӳ������           <br>
*               ECOMM   ---- ��żУ������CRC����           <br>
*               EPROTO  ---- ��Ƭ����Ӧ��ISO14443������  <br>
*               EBADE   ---- ��Ƭ���ش�����Ӧ��Ϣ           <br>
*               ETIME   ---- ��ʱ           <br>
*               EMULTIHOP   ---- ��Ƶ�����ж��ſ�           <br>
@else 
* @brief Send WUPA instructions to iso14443 card
* @param[in]	fd		-	iso14443 card device file descriptor
* @param[out]	atqa	-	The card's response to this command[2 Byte]
* @return   <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument           <br>
*               EIO     ---- hardware error           <br>
*               ECOMM   ---- Parity Error or CRC error           <br>
*               EPROTO  ---- the response from card not compatile with ISO14443  <br>
*               EBADE   ---- card return error response information           <br>
*               ETIME   ---- timeout           <br>
*               EMULTIHOP   ---- more than one card in RF field            <br>
@endif
*/
int iso14443_WupA(int fd, void *atqa);

/**
@if Chinese
* @brief ����Ƭ���ͷ���ͻָ��
* @param[in]	fd	-	�ǽӶ������豸�ļ�������
* @param[in]	sel	-	����ͻ���� <br>
*                0x93    ---- ��һ�� <br>
*                0x95    ---- �ڶ��� <br>
*                0x97    ---- ������ <br>
* @param[out]	uid	-	uid information of current level. [5 Bytes,4�ֽ�UID+BCC]
* @return ����ֵ<br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, �ɸ���errno��ȡ������.����Ϊ������ӳ����Ϣ:<br>
*               EINVAL  ---- invalid argument           <br>
*               EIO     ---- hardware error           <br>
*               ECOMM   ---- Parity Error or CRC error           <br>
*               EPROTO  ---- the response from card not compatile with ISO14443  <br>
*               EBADE   ---- card return error response information           <br>
*               ETIME   ---- timeout           <br>
*               EMULTIHOP   ---- more than one card in RF field            <br>
@else 
* @brief Send anti-collision instructions to the card
* @param[in]	fd	-	contactless card reader device file descriptor
* @param[in]	sel	-	anti-conflict layer <br>
*                0x93    ---- first  level <br>
*                0x95    ---- second  level <br>
*                0x97    ---- third  level <br>
* @param[out]	uid	-	uid information of current level. [5 Bytes,4 bytes UID+BCC]
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument           <br>
*               EIO     ---- hardware error           <br>
*               ECOMM   ---- Parity Error or CRC error           <br>
*               EPROTO  ---- the response from card not compatile with ISO14443  <br>
*               EBADE   ---- card return error response information           <br>
*               ETIME   ---- timeout           <br>
*               EMULTIHOP   ---- more than one card in RF field            <br>
@endif 
*/
int iso14443_Anticollision(int fd, uint8_t sel, void *uid);

/**
@if Chinese
* @brief ����Ƭ����selectָ�� [Type A]
* @param[in]	fd	-	�ǽӶ������豸�ļ�������
* @param[in]	sel	-	����ͻ���� <br>
*       0x93    ---- ��һ�� <br>
*       0x95    ---- �ڶ��� <br>
*       0x97    ---- ������
* @param[in]	uid	-	Ψһ��ʶ��
* @param[out]	sak	-	��Ƭ���ص�ȷ����Ϣ��1�ֽ�
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.����Ϊ������ӳ����Ϣ:<br>
*               EINVAL  ---- ��Ч�Ĳ���           <br>
*               EIO     ---- Ӳ������           <br>
*               ECOMM   ---- ��żУ������CRC����           <br>
*               EPROTO  ---- ��Ƭ����Ӧ��ISO14443������  <br>
*               EBADE   ---- ��Ƭ���ش�����Ӧ��Ϣ           <br>
*               ETIME   ---- ��ʱ           <br>
@else 
* @brief Send the select command to the card [Type A]
* @param[in]	fd	-	contactless card reader device file descriptor
* @param[in]	sel	-	choose layer <br>
*       0x93    ---- first level <br>
*       0x95    ---- second level <br>
*       0x97    ---- third level
* @param[in]	uid	-	Unique Identifier
* @param[out]	sak	-	card returned confirmation, 1 byte
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument           <br>
*               EIO     ---- hardware error           <br>
*               ECOMM   ---- Parity Error or CRC error           <br>
*               EPROTO  ---- the response from card not compatile with ISO14443  <br>
*               EBADE   ---- card return error response information           <br>
*               ETIME   ---- timeout           <br>
@endif 
*/
int iso14443_Select(int fd, uint8_t sel, const void *uid, uint8_t *sak);

/**
@if Chinese
* @brief ��ȡ��ǰA�࿨Ƭ��uid
* @param[in]	fd		-	�ǽӶ������豸�ļ�������
* @param[out]	uidlen	-	uid����[unit:Byte]
* @param[out]	uid		-	��Ƭ��uid����
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.
@else
* @brief Gets the UID of the current class A card
* @param[in]	fd		-	contactless card reader device file descriptor
* @param[out]	uidlen	-	uid length[unit:Byte]
* @param[out]	uid		-	Uid data of the card
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno..
@endif 
*/
int iso14443_get_typeA_uid(int fd, uint8_t *uidlen, void *uid);

/**
@if Chinese
* @brief 	��ȡ��Ƭ������
* @return 	���ؿ�Ƭ������ֵ.<br>
*   MIF_TYPE_A          --- TypeA <br>
*   MIF_TYPE_B,         --- TypeB <br>
*   MIF_TYPE_C1,        --- FeliCa, 212kbits/s <br>
*   MIF_TYPE_C2,        --- FeliCa, 424kbits/s <br>
*   MIF_TYPE_UNKNOWN    --- δ֪������
@else 
* @brief 	Gets the type of the card
* @return 	Returns the type value of the card.<br>
*   MIF_TYPE_A          --- TypeA <br>
*   MIF_TYPE_B,         --- TypeB <br>
*   MIF_TYPE_C1,        --- FeliCa, 212kbits/s <br>
*   MIF_TYPE_C2,        --- FeliCa, 424kbits/s <br>
*   MIF_TYPE_UNKNOWN    --- Unknown Card Type
@endif 
*/
uint8_t iso14443_get_cardtype(void);

/**
@if Chinese
* @brief 	����Ƭ����HALTָ�� [Type A]
* @param[in]	fd	-	�ǽӶ������豸�ļ�������
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.
@else 
* @brief 	Send the HALT instruction to the card [Type A]
* @param[in]	fd	-	contactless card reader device file descriptor
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif
*/
int iso14443_HaltA(int fd);

/**
@if Chinese
* @brief	����RATSָ�����Ƭ [Type A]
* @param[in]	fd		-	�ǽӶ������豸�ļ�������
* @param[in]	cid		-	��Ƭ���߼�����, default is 0
* @param[in]	fsdi	-	�ն˿ɽ��յ����֡����ϵ�� <br>
*               0  ---- 16 bytes    <br>
*               1  ---- 24 bytes    <br>
*               2  ---- 32 bytes    <br>
*               3  ---- 40 bytes    <br>
*               4  ---- 48 bytes    <br>
*               5  ---- 64 bytes    <br>
*               6  ---- 96 bytes    <br>
*               7  ---- 128 bytes   <br>
*               >=8 ---- 256 bytes  
* @param[out]	atslen	-	Ӧ���ĳ���
* @param[out]	ats		-	Ӧ������Чֵ
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.����Ϊ������ӳ����Ϣ:<br>
*               EINVAL  ---- ��Ч�Ĳ���   <br>
*               EIO     ---- Ӳ������   <br>
*               ECOMM   ---- ��żУ������CRC����   <br>
*               EPROTO  ---- ��Ƭ����Ӧ��ISO14443������   <br>
*               EBADE   ---- ��Ƭ���ش�����Ӧ��Ϣ   <br>
*               EACCES   --- ��Ƶ���еĿ�����T=CL��   <br>
*               ETIME   ---- ��ʱ   <br>
@else

* @brief	Send the RATS instruction to the card [Type A]
* @param[in]	fd		-	contactless card reader device file descriptor
* @param[in]	cid		-	card number of card, default is 0
* @param[in]	fsdi	-	The maximum frame length coefficient that terminal can receive, values are as follows <br>
*               0  ---- 16 bytes    <br>
*               1  ---- 24 bytes    <br>
*               2  ---- 32 bytes    <br>
*               3  ---- 40 bytes    <br>
*               4  ---- 48 bytes    <br>
*               5  ---- 64 bytes    <br>
*               6  ---- 96 bytes    <br>
*               7  ---- 128 bytes   <br>
*               >=8 ---- 256 bytes  
* @param[out]	atslen	-	length of ATS information that info_len returned
* @param[out]	ats		-	ATS information that info_len returned
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument   <br>
*               EIO     ---- hardware error   <br>
*               ECOMM   ---- Parity Error or CRC error   <br>
*               EPROTO  ---- the response from card not compatile with ISO14443   <br>
*               EBADE   ---- card return error response information   <br>
*               EACCES   ---  The card in RF field is not a T=CL card   <br>
*               ETIME   ---- timeout   <br>
@endif 
*/
int iso14443_RATS(int fd, uint8_t cid, uint8_t fsdi, uint8_t *atslen, void *ats);

/**
@if Chinese
* @brief ����PPSEָ�����Ƭ [Type A]
* @param[in]	fd	-	�ǽӶ������豸�ļ�������
* @param[in]	cid	-	��Ƭ��ʶ����ͬiso14443_rats(��)
* @param[in]	br	-	��������������PCD��PICC��bit8~bit5��ı����ʣ�,
*  				�Լ���PICC��PCD��bit4~λ�������. <br>
*                  0  --- 106kbits/s    <br>
*                  1  --- 212kbits/s    <br>
*                  2  --- 424kbits/s    <br>
*                  3  --- 848kbits/s    <br>
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.����Ϊ������ӳ����Ϣ:<br>
*               EINVAL  ---- ��Ч�Ĳ���   <br>
*               EIO     ---- Ӳ������   <br>
*               ECOMM   ---- ��żУ������CRC����   <br>
*               EPROTO  ---- ��Ƭ����Ӧ��ISO14443������   <br>
*               EBADE   ---- ��Ƭ���ش�����Ӧ��Ϣ   <br>
*               EACCES  ---  ��Ƶ���еĿ�����T=CL��   <br>
*               ETIME   ---- ��ʱ   <br>
@else
* @brief Send the PPSE instruction to the card [Type A]
* @param[in]	fd	-	contactless card reader device file descriptor
* @param[in]	cid	-	Card Identifier, the same as used in iso14443_rats(...)
* @param[in]	br	-	the bit rate capability, bit8~bit5 code bit rate from PCD to PICC,
*   and bit4~bit code bit rate from PICC to PCD. <br>
*                  0  --- 106kbits/s    <br>
*                  1  --- 212kbits/s    <br>
*                  2  --- 424kbits/s    <br>
*                  3  --- 848kbits/s    
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument   <br>
*               EIO     ---- hardware error   <br>
*               ECOMM   ---- Parity Error or CRC error   <br>
*               EPROTO  ---- the response from card not compatile with ISO14443   <br>
*               EBADE   ---- card return error response information   <br>
*               EACCES   ---  The card in RF field is not a T=CL card   <br>
*               ETIME   ---- timeout   
@endif 
*/
int iso14443_PPS(int fd, uint8_t cid, uint8_t br);

/**
@if Chinese
* @brief	����Ƭ����REQBָ�� [Type B]
* @param[in]	fd			-	�ǽӶ������豸�ļ�������
* @param[in]	afi			-	����Ӧ�ó����Ӧ�ó������ʶ������B. 0
* @param[in]	slotnum		-	����,   <br>
*                   0    ---- only one slot   <br>
*                   1    ---- 2 slots   <br>
*                   2    ---- 4 slots   <br>
*                   3    ---- 8 slots   <br>
*                   4    ---- 16 slots   <br>
* @param[out]	lenofatqb	-	�ش�����ĳ���
* @param[out]	atqb		-	�ش���������
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.����Ϊ������ӳ����Ϣ:<br>
*               EINVAL  ---- ��Ч�Ĳ���   <br>
*               EIO     ---- Ӳ������   <br>
*               ECOMM   ---- ��żУ������CRC����   <br>
*               EPROTO  ---- ��Ƭ����Ӧ��ISO14443������   <br>
*               EBADE   ---- ��Ƭ���ش�����Ӧ��Ϣ   <br>
*               EACCES  ---  ��Ƶ���еĿ�����T=CL��   <br>
*               ETIME   ---- ��ʱ   <br>
@else 
* @brief Send the REQB command to the card [Type B]
* @param[in]	fd			-	contactless card reader device file descriptor
* @param[in]	afi			-	Application Family Identifier, Type B. 0 for all applications
* @param[in]	slotnum		-	Number of slots,   <br>
*                   0    ---- only one slot   <br>
*                   1    ---- 2 slots   <br>
*                   2    ---- 4 slots   <br>
*                   3    ---- 8 slots   <br>
*                   4    ---- 16 slots   <br>
* @param[out]	lenofatqb	-	information length of ATQB
* @param[out]	atqb		-	ATQB information
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.:<br>
*               EINVAL  ---- invalid argument   <br>
*               EIO     ---- hardware error   <br>
*               ECOMM   ---- Parity Error or CRC error   <br>
*               EPROTO  ---- the response from card not compatile with ISO14443   <br>
*               EBADE   ---- card return error response information   <br>
*               EACCES   ---  The card in RF field is not a T=CL card   <br>
*               ETIME   ---- timeout   <br>
@endif 
*/
int iso14443_ReqB(int fd, uint8_t afi, uint8_t slotnum, uint8_t *lenofatqb, void *atqb);

/**
@if Chinese
* @brief ����Ƭ����WUPBָ�� [Type B]
* @param[in]	fd		-	�ǽӶ������豸�ļ�������
* @param[in]	afi		-	����Ӧ�ó����Ӧ�ó������ʶ������B. 0
* @param[in]	slotnum	-	����,   <br>
*                   0    ---- only one slot   <br>
*                   1    ---- 2 slots   <br>
*                   2    ---- 4 slots   <br>
*                   3    ---- 8 slots   <br>
*                   4    ---- 16 slots   <br>
* @param[out] lenofatqb	-	�ش�����ĳ���
* @param[out] atqb		-	�ش��������ֵ
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.
@else 
* @brief Send the WUPB command to the card [Type B]
* @param[in]	fd			-	contactless card reader device file descriptor
* @param[in]	afi			-	Application Family Identifier, Type B. 0 for all applications
* @param[in]	slotnum		-	Number of slots,   <br>
*                   0    ---- only one slot   <br>
*                   1    ---- 2 slots   <br>
*                   2    ---- 4 slots   <br>
*                   3    ---- 8 slots   <br>
*                   4    ---- 16 slots   <br>
* @param[out]	lenofatqb	-	the length of Answer To Request
* @param[out]	atqb		-	Answer to Request
* @return <br>
*   <em> 0 </em>    ----success	<br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno..
@endif 
*/
int iso14443_WupB(int fd, uint8_t afi, uint8_t slotnum, uint8_t *lenofatqb, void *atqb);

/**
@if Chinese
* @brief λ�ñ������ [Type B]
* @param[in]	fd			-	�ǽӶ������豸�ļ�������
* @param[in]	slot		-	ʱ���λ������ReqB��WupB��slotnum������ȡֵӦС��16
* @param[out]	lenofatqb	-	�ش�����ĳ���
* @param[out]	atqb		-	�ش��������ֵ
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.
@else 
* @brief Slot Marker command [Type B]
* @param[in]	fd			-	contactless card reader device file descriptor
* @param[in]	slot		-	time slot parameter, 0~15
* @param[out]	lenofatqb	-	information length of ATQB
* @param[out]	atqb		-	ATQB information
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif 
*/
int iso14443_SlotMarker(int fd, uint8_t slot, uint8_t *lenofatqb, void *atqb);

/**
@if Chinese
* @brief ����Ƭ����ATTRIBָ��
* @param[in]	fd		-	�ǽӶ������豸�ļ�������
* @param[in]	cid		-	����ʶ��
* @param[in]	fsdi	-	PCD������֡��С  <br>
*               0  ---- 16 bytes  <br>
*               1  ---- 24 bytes  <br>
*               2  ---- 32 bytes  <br>
*               3  ---- 40 bytes  <br>
*               4  ---- 48 bytes  <br>
*               5  ---- 64 bytes  <br>
*               6  ---- 96 bytes  <br>
*               7  ---- 128 bytes  <br>
*               >=8 ---- 256 bytes  <br>
* @param[in]	uid		-	Ψһ��ʶ��
* @param[in]	br		-	��������������PCD��PICC��bit8~bit5��λ�ʣ��ʹ�PICC��PCD��bit4~��λ��<br>
*                  0  --- 106kbits/s  <br>
*                  1  --- 212kbits/s  <br>
*                  2  --- 424kbits/s  <br>
*                  3  --- 848kbits/s  <br>
* @param[out]	len		-	�ش�Attrib����ĳ���
* @param[out]	info	-	��ATTRIB����Ļش�
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.
@else 
* @brief Send an ATTRIB instruction to the card
* @param[in]	fd		-	contactless card reader device file descriptor
* @param[in]	cid		-	Card Identifier
* @param[in]	fsdi	-	Frame Size for PCD integer  <br>
*               0  ---- 16 bytes  <br>
*               1  ---- 24 bytes  <br>
*               2  ---- 32 bytes  <br>
*               3  ---- 40 bytes  <br>
*               4  ---- 48 bytes  <br>
*               5  ---- 64 bytes  <br>
*               6  ---- 96 bytes  <br>
*               7  ---- 128 bytes  <br>
*               >=8 ---- 256 bytes  <br>
* @param[in]	uid		-	Unique Identifier
* @param[in]	br		-	The bit rate capability, bit8~bit5 code bit rate from PCD to PICC, and bit4~bit code bit rate from PICC to PCD<br>
*                  0  --- 106kbits/s  <br>
*                  1  --- 212kbits/s  <br>
*                  2  --- 424kbits/s  <br>
*                  3  --- 848kbits/s  <br>
* @param[out]	len		-	The length of Answer to an Attrib command
* @param[out]	info	-	Answer of to an ATTRIB Command
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif 
*/
int iso14443_AttriB(int fd, uint8_t cid, uint8_t fsdi, const void *uid, uint8_t br, uint8_t *len, void *info);

/**
@if Chinese
* @brief PICCѡ���������T=CL [Type B]
* @param[in]	fd		-	�豸id������mif_open(��)
* @param[in]	cid		-	����ʶ��
* @param[in]	fsdi	-	PCD������֡��С  <br>
*               0  ---- 16 bytes  <br>
*               1  ---- 24 bytes  <br>
*               2  ---- 32 bytes  <br>
*               3  ---- 40 bytes  <br>
*               4  ---- 48 bytes  <br>
*               5  ---- 64 bytes  <br>
*               6  ---- 96 bytes  <br>
*               7  ---- 128 bytes  <br>
*               >=8 ---- 256 bytes  
* @param[in]	uid	-	Ψһ��ʶ��
* @param[in]	br	-	��������������PCD��PICC��bit8~bit5��ı����ʣ�
*       				�Լ���PICC��PCD��bit4~λ������� <br>
*                  0  --- 106kbits/s <br>
*                  1  --- 212kbits/s <br>
*                  2  --- 424kbits/s <br>
*                  3  --- 848kbits/s 
* @param[out]	len		-	�ش�Attrib����ĳ���
* @param[out]	info	-	��ATTRIB����Ļش�
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.
@else 
* @brief PICC selection command, set T=CL [Type B]
* @param[in]	fd		-	Device id, return from mif_open(...)
* @param[in]	cid		-	Card Identifier
* @param[in]	fsdi	-	Frame Size for PCD integer  <br>
*               0  ---- 16 bytes  <br>
*               1  ---- 24 bytes  <br>
*               2  ---- 32 bytes  <br>
*               3  ---- 40 bytes  <br>
*               4  ---- 48 bytes  <br>
*               5  ---- 64 bytes  <br>
*               6  ---- 96 bytes  <br>
*               7  ---- 128 bytes  <br>
*               >=8 ---- 256 bytes  
* @param[in]	uid		-	Unique Identifier
* @param[in]	br		-	The bit rate capability, bit8~bit5 code bit rate from PCD to PICC,
*       and bit4~bit code bit rate from PICC to PCD <br>
*                  0  --- 106kbits/s <br>
*                  1  --- 212kbits/s <br>
*                  2  --- 424kbits/s <br>
*                  3  --- 848kbits/s 
* @param[out]	len		-	The length of Answer to an Attrib command
* @param[out]	info	-	Answer of to an ATTRIB Command
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif 
*/
int iso14443_tcl_AttriB(int fd, uint8_t cid, uint8_t fsdi, const void *uid, uint8_t br, uint8_t *len, void *info);

/**
@if Chinese
* @brief ����Ƭ����HALTBָ�� [Type B]
* @param[in]	fd	-	�ǽӶ������豸�ļ�������
* @param[in]	uid	-	Ψһ��ʶ��
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.
@else 
* @brief Send the HALTB command to the card [Type B]
* @param[in]	fd	-	contactless card reader device file descriptor
* @param[in]	uid	-	Unique Identifier
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif 
*/
int iso14443_HaltB(int fd, const void *uid);

// contactless card type definition

#define MIF_M1_S50          0x00	/**<@if Chinese 	�ǽӴ�ʽ������S50	@else mifare classic S50 @endif*/
#define MIF_M1_S70          0x01	/**<@if Chinese 	�ǽӴ�ʽ������S70	@else mifare classic S70 @endif*/
#define MIF_ULTRALIGHT      0x02	/**<@if Chinese 	��Լ�ͷǽӴ�ʽ������	@else mifare Ultralight @endif*/
#define MIF_DESFIRE         0x03	/**<@if Chinese 	�ǽӴ�ʽ������D40��EV1	@else mifare DESFire D40 or EV1 @endif*/
#define MIF_PRO             0x04	/**<@if Chinese 	�ǽӴ�ʽ������ProX	@else mifare ProX @endif*/
#define MIF_PRO_S50         0x05	/**<@if Chinese 	mifare ProX��Ƕ��mifare����S50������T=CLЭ��	@else mifare ProX and embed mifare classic S50,compatible with T=CL protocol @endif*/
#define MIF_PRO_S70         0x06	/**<@if Chinese 	mifare ProX��Ƕ��mifare����S70������T=CLЭ��	@else mifare ProX and embed mifare classic S70,compatible with T=CL protocol @endif*/
#define MIF_TYPEB           0x07	/**<@if Chinese 	ISO14443����b����T=CLЭ�鲻����	@else ISO14443 TypeB, and not compatible with T=CL protocol @endif*/
#define MIF_TYPEB_TCL       0x08	/**<@if Chinese 	ISO14443����b����T=CLЭ�����	@else ISO14443 TypeB, and compatible with T=CL protocol @endif*/
#define MIF_FELICA          0x09	/**<@if Chinese 	���������	@else Sony FeliCa @endif*/
#define MIF_UNKNOWEN_TYPEA  0x0A	/**<@if Chinese 	ISO14443����a����T=CLЭ�鲻����	@else ISO14443 TypeA, and not compatible with T=CL protocol @endif*/

/**
@if Chinese
* @brief ��RF�ֶ�����ѯT=CL���������ؿ���Ϣ
* @param[in]	fd			-	�ǽӶ������豸�ļ�������
* @param[in]	mode		-	��ѯ��ʽ��ȡֵΪ:<br>
*                  0  --- ֻ��ѯ���ڴ���IDLE״̬��T=CL��  <br>
*                  1  --- ��ѯ���ڴ���IDLE״̬��HALT״̬��T=CL��   
* @param[out]	cardinfo_len	-	T=CL����Ϣ�ĳ���
* @param[out]	cardinfo	-	T=CL����Ϣ. T=CL����Ϣ����: <br>
*                           cardinfo[0] --- return the T=CL card type, refer to contactless card type definition. <br>
*                           for TypeA, the following information is ATQA[2bytes] + UidLen(1byte) + Uid(UidLen bytes) + SAK(1byte) <br>
*                           for TypeB, the follwoing information is ATQB[12bytes] 
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.
@else 
* @brief Poll the RF field for T=CL card, and return the card information
* @param[in]	fd			-	contactless card reader device file descriptor
* @param[in]	mode		-	Poll mode, value can be:<br>
*                  0  --- only poll the T=CL cards which in IDLE state now  <br>
*                  1  --- poll the T=CL cards which in IDLE state and HALT state now  
* @param[out]	cardinfo_len	-	The length of T=CL card information
* @param[out]	cardinfo	-	the T=CL card information. the cardinfo organized as following: <br>
*                           cardinfo[0] --- return the T=CL card type, refer to contactless card type definition. <br>
*                           for TypeA, the following information is ATQA[2bytes] + UidLen(1byte) + Uid(UidLen bytes) + SAK(1byte) <br>
*                           for TypeB, the follwoing information is ATQB[12bytes] 
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif 
*/
int iso14443_tcl_poll(int fd, int mode, uint8_t *cardinfo_len, void *cardinfo);

/**
@if Chinese
* @brief �����Ӧ���ڵ�T=CL��
* @param[in]	fd		-	�ǽӶ������豸�ļ�������
* @param[in]	cid		-	��Ƭ���߼�����
* @param[in]	br		-	�ն��뿨Ƭ֮���ͨ�Ų����ʲ���������ȡֵ����: <br>
					��4λΪ�ն˵���Ƭ��ͨ�����ʣ� <br>
*       			��4λΪ��Ƭ���ն˵�ͨ�����ʣ� <br>
*                  0  --- 106kbits/s <br>
*                  1  --- 212kbits/s <br>
*                  2  --- 424kbits/s <br>
*                  3  --- 848kbits/s <br>
* @param[in]	fsdi	-	�ն˿ɽ��յ����֡����ϵ��   <br>
*               0 ---- 16bytes   <br>
*               1 ---- 24bytes   <br>
*               2 ---- 32bytes   <br>
*               3 ---- 40bytes   <br>
*               4 ---- 48bytes   <br>
*               5 ---- 64bytes   <br>
*               6 ---- 96bytes   <br>
*               7 ---- 128bytes   <br>
*               8 ---- 256bytes   <br>
*               ����ֵ ---- 256bytes   <br>
* @param[out]	info_len	-	TypeA ����<br>
							info_len����ATS��Ϣ�ĳ��� <br>
						  TypeB ����<br>
							��Ϊ����ʱ��info_lenָArttriB������Higher-layer INF��Ϣ�ĳ��ȣ�<br>
							��Ϊ���ʱ��info_len���ؿ�Ƭ����Ӧ���ݳ���
* @param[out]	info	-	TypeA ����<br>
							info_len����ATS��Ϣ <br>
						  TypeB ����<br>
							��Ϊ ����ʱ��info ָAttriB������Higher-Layer INF��Ϣ��<br>
							��Ϊ���ʱ��info���ؿ�Ƭ����Ӧ����
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.
@else 
* @brief Active T=CL card in inductive zone
* @param[in]	fd	-	contactless card reader device file descriptor
* @param[in]	cid	-	The logical card no, usually is set as 0
* @param[in]	br	-	The bit rate capability, bit8~bit5 code bit rate from PCD to PICC,
*       and bit4~bit code bit rate from PICC to PCD <br>
*                  0  --- 106kbits/s <br>
*                  1  --- 212kbits/s <br>
*                  2  --- 424kbits/s <br>
*                  3  --- 848kbits/s <br>
* @param[in]	fsdi	-	The maximum frame length coefficient that terminal can receive, values are as follows   <br>
*               0 ---- 16bytes   <br>
*               1 ---- 24bytes   <br>
*               2 ---- 32bytes   <br>
*               3 ---- 40bytes   <br>
*               4 ---- 48bytes   <br>
*               5 ---- 64bytes   <br>
*               6 ---- 96bytes   <br>
*               7 ---- 128bytes   <br>
*               8 ---- 256bytes   <br>
*               other ---- 256bytes   <br>
* @param[out]	info_len	-	The length of card information
* @param[out]	info		-	Card Information. <br>
*                   For Type A, the info field is organized  as following: <br>
*                       Card Type(1byte) || ATQA(2bytes) || uid len(1byte) || uid (uidlen bytes) <br>
*                   For TypeB, the info field is organized as following: <br>
*                       Card Type(1byte) || ATQB(12/13bytes) 
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif 
*/
int iso14443_tcl_active(int fd, uint8_t cid, uint8_t br, uint8_t fsdi, uint8_t *info_len, void *info);

/**
@if Chinese
* @brief ��PCD��PICC֮�佻��T=CL���ݰ�
* @param[in]	fd			-	�ǽӶ������豸�ļ�������
* @param[in]	sendlen		-	���͵�PICC�����ݰ�����
* @param[in]	senddata	-	���͵�PICC�����ݰ�
* @param[out]	recvlen		-	��PICC���ص����ݰ�����
* @param[out]	recvdata	-	��PICC���ص����ݰ�
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.
@else 
* @brief Exchange T=CL data packet between PCD and PICC
* @param[in]	fd			-	Non-access card reader device file descriptor
* @param[in]	sendlen		-	The data packet length send to PICC
* @param[in]	senddata	-	The data send to PICC
* @param[out]	recvlen		-	The data packet length return from PICC
* @param[out]	recvdata	-	The data return from PICC
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif 
*/
int iso14443_tcl_exchange(int fd, uint32_t sendlen, const void *senddata, uint32_t *recvlen, void *recvdata);

/**
@if Chinese
* @brief	��λ��Ƶ�����п���ʹ�����IDLE״̬
* @param[in]	fd	-	�ǽӶ������豸�ļ�������
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.
@else 
* @brief	Reset all card in RF field, and put them into IDLE state
* @param[in]	fd	-	contactless card reader device file descriptor
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif 
*/
int iso14443_tcl_deactive(int fd);

/**
@if Chinese
* @brief PCD��PICC֮������ݽ���������֯��ISO14443 T=CL���ݰ���
* @param[in]	fd			-	�ǽӶ������豸�ļ�������
* @param[in]	sendlen		-	���͵�PICC�����ݰ�����
* @param[in]	senddata	-	���͵�PICC�����ݰ�
* @param[in]	timeout		-	�ȴ�ʱ��(��λ:etu)
* @param[out]	recvlen		-	��PICC���ص����ݰ�����
* @param[out]	recvdata	-	��PICC���ص����ݰ�
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.
@else 
* @brief Exchange data between PCD and PICC, not organized in ISO14443 T=CL data packet
* @param[in]	fd			-	contactless card reader device file descriptor
* @param[in]	sendlen		-	The data packet length send to PICC
* @param[in]	senddata	-	The data send to PICC
* @param[in]	timeout		-	Wait time (unit:etu)
* @param[out]	recvlen		-	The data packet length return from PICC
* @param[out]	recvdata	-	The data return from PICC
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif 
*/
int iso14443_no_tcl_exchange(int fd, uint32_t sendlen, const void *senddata, uint32_t *recvlen, void *recvdata, uint32_t timeout);

/**
@if Chinese
* @brief	�����Ƶ���Ƿ��ж����
* @param[in]	fd	-	�ǽӶ������豸�ļ�������
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.����Ϊ������ӳ����Ϣ:<br>
*               EINVAL  ---- ��Ч�Ĳ���   <br>
*               EIO     ---- Ӳ������   <br>
*               ECOMM   ---- ��żУ������CRC����   <br>
*               EPROTO  ---- ��Ƭ����Ӧ��ISO14443������   <br>
*               EBADE   ---- ��Ƭ���ش�����Ӧ��Ϣ   <br>
*               EACCES  ---  ��Ƶ���еĿ�����T=CL��  <br>
*               ETIME   ---- ��ʱ   <br>
@else 
* @brief Check if more than one card in RF field
* @param[in]	fd	-	contactless card reader device file descriptor
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument   <br>
*               EIO     ---- hardware error   <br>
*               ECOMM   ---- Parity Error or CRC error   <br>
*               EPROTO  ---- the response from card not compatile with ISO14443   <br>
*               EBADE   ---- card return error response information   <br>
*               EACCES   ---  The card in RF field is not a T=CL card   <br>
*               ETIME   ---- timeout during poll card   <br>
@endif 
*/
int iso14443_check_multi_card(int fd);

/**
@if Chinese
* @brief ��PCD������FeliCa֮�佻������
* @param[in]	fd			-	�ǽӶ������豸�ļ�������
* @param[in]	sendlen		-	���͵�PICC�����ݰ�����
* @param[in]	senddata	-	���͵�PICC�����ݰ�
* @param[in]	timeout		-	�ȴ�ʱ��(��λ:etu)
* @param[out]	recvlen		-	��PICC���ص����ݰ�����
* @param[out]	recvdata	-	��PICC���ص����ݰ�
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.����Ϊ������ӳ����Ϣ:<br>
*               EINVAL  ---- ��Ч�Ĳ���    <br>
*               EIO     ---- Ӳ������    <br>
*               ECOMM   ---- ��żУ������CRC����    <br>
*               EPROTO  ---- ��Ƭ����Ӧ��ISO14443������    <br>
*               EBADE   ---- ��Ƭ���ش�����Ӧ��Ϣ    <br>
*               EACCES  ---  ��Ƶ���еĿ�����T=CL��    <br>
*               ETIME   ---- ��ʱ    <br>
@else 
* @brief Exchange data between PCD and Sony FeliCa
* @param[in]	fd			-	contactless card reader device file descriptor
* @param[in]	sendlen		-	The data packet length send to PICC
* @param[in]	senddata	-	The data send to PICC
* @param[in]	timeout		-	Wait time (unit:etu)
* @param[out]	recvlen		-	The data packet length return from PICC
* @param[out]	recvdata	-	The data return from PICC
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument    <br>
*               EIO     ---- hardware error    <br>
*               ECOMM   ---- Parity Error or CRC error    <br>
*               EPROTO  ---- the response from card not compatile with ISO14443    <br>
*               EBADE   ---- card return error response information    <br>
*               EACCES   ---  The card in RF field is not a T=CL card    <br>
*               ETIME   ---- timeout during poll card    <br>
@endif 
*/
int felica_exchange(int fd, uint32_t sendlen, const void *senddata, uint32_t *recvlen, void *recvdata, uint32_t timeout);

/*! 
@if Chinese
	@brief	EMVģʽ�µĿ�Ƭ״̬���� 
@else
	@brief	Card state definition in EMV mode
@endif 
*/
enum {
    NFC_OP_NULL         = 0x00, /**<@if Chinese 0 : δ��ʼ��״̬ 	@else	0: uninitialized		@endif*/
    NFC_OP_POLL,            	/**<@if Chinese 1 : ��ѯ��Ƭ 		@else	1: polling cards		@endif*/
    NFC_OP_ANTICOLL,        	/**<@if Chinese 2 : ����ͻ���� 		@else	2: anti-conflict processing	@endif*/
    NFC_OP_REMOVE,          	/**<@if Chinese 3 : �Ƴ���Ƭ, Ӧ�ó����ȡ������״̬, emv_contactless_deactive_picc���ؼ���ʾ�ƿ���� @else	3: The card is removed. The application program cannot obtain the status. If emv_ContactLess_deactive_PICc returns, the card is removed	@endif*/
    NFC_OP_EXCHANGE_APDU,   	/**<@if Chinese 4:  ���ݽ��� 		@else	4: Data exchange		@endif*/
};

/**
@if Chinese
* @brief	�򿪵�ų�������Ӧ����IC��
* @param[in]	fd	-	�ǽӶ������豸�ļ�������
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.����Ϊ������ӳ����Ϣ:<br>
*               EINVAL  ---- ��Ч�Ĳ���    <br>
*               EIO     ---- Ӳ������    <br>
*               ECOMM   ---- ��żУ������CRC����    <br>
*               EPROTO  ---- ��Ƭ����Ӧ��ISO14443������    <br>
*               EBADE   ---- ��Ƭ���ش�����Ӧ��Ϣ    <br>
*               EACCES  ---  ��Ƶ���еĿ�����T=CL��   <br>
*               ETIME   ---- ��ʱ    <br>
* @note �����Ƶ������2�ſ������ǾͲ��ܼ��������ſ�
*       �����������BLOCK���������������˳�.
@else 
* @brief	Open the electromagnetic filed and check card
* @param[in]	fd	-	contactless card reader device file descriptor
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument    <br>
*               EIO     ---- hardware error    <br>
*               ECOMM   ---- Parity Error or CRC error    <br>
*               EPROTO  ---- the response from card not compatile with ISO14443    <br>
*               EBADE   ---- card return error response information    <br>
*               EACCES   ---  The card in RF field is not a T=CL card    <br>
*               ETIME   ---- timeout during poll card    <br>
* @note If more than 2 cards in RF field, we can't active neither of it
*       this function is not a BLOCK function, it will quit immediately.
@endif 
*/
int emv_contactless_active_picc(int fd);

/**
@if Chinese
* @brief �ƿ���Ƭ����⵽��Ƭ�ƿ���رյ糡
* @param[in]	fd	-	�ǽӶ������豸�ļ�������
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.����Ϊ������ӳ����Ϣ:<br>
*               EINVAL  ---- ��Ч����    <br>
*               EIO     ---- Ӳ������    <br>
*               ECOMM   ---- У�����    <br>
*               EPROTO  ---- ��Ƭ����Ӧ��ISO14443������   <br>
*               EBADE   ---- ��Ƭ���ش�����Ӧ��Ϣ    <br>
*               EACCES  ---  ��Ƶ���еĿ�����T=CL��    <br>
*               ETIME   ---- ��ʱ    <br>
@else 
* @brief Wait until the card remove out of the RF field, then close the electromagnetic field.
* @param[in]	fd	-	contactless card reader device file descriptor
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument    <br>
*               EIO     ---- hardware error    <br>
*               ECOMM   ---- Parity Error or CRC error    <br>
*               EPROTO  ---- the response from card not compatile with ISO14443    <br>
*               EBADE   ---- card return error response information    <br>
*               EACCES   ---  The card in RF field is not a T=CL card    <br>
*               ETIME   ---- timeout during poll card    <br>
@endif 
*/
int emv_contactless_deactive_picc(int fd);

/**
@if Chinese
* @brief �ƿ���Ƭ����⵽��Ƭ�ƿ���رյ糡
* @param[in]	fd	-	�ǽӶ������豸�ļ�������
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.����Ϊ������ӳ����Ϣ:<br>
*               EINVAL  ---- ��Ч����    <br>
*               EIO     ---- Ӳ������    <br>
*               ECOMM   ---- У�����    <br>
*               EPROTO  ---- ��Ƭ����Ӧ��ISO14443������   <br>
*               EBADE   ---- ��Ƭ���ش�����Ӧ��Ϣ    <br>
*               EACCES  ---  ��Ƶ���еĿ�����T=CL��    <br>
*               ETIME   ---- ��ʱ    <br>
* @note ��emv_contactless_deactive_picc()���������ڸýӿڷ�����
@else 
* @brief Wait until the card remove out of the RF field, then close the electromagnetic field.
* @param[in]	fd	-	contactless card reader device file descriptor
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed,You can obtain the error code according to errno:<br>
*				EINVAL	---- invalid argument    <br>
*				EIO		---- hardware error    <br>
*				ECOMM	---- Parity Error or CRC error    <br>
*				EPROTO	---- the response from card not compatile with ISO14443    <br>
*				EBADE	---- card return error response information    <br>
*				EACCES   ---  The card in RF field is not a T=CL card    <br>
*				ETIME	---- timeout during poll card    <br>
* @note The difference from emv_contactLess_deactive_picc () is that this interface is non-blocking
@endif 
*/
int emv_contactless_deactive_picc_nonblock(int fd);

/**
@if Chinese
* @brief ��ȡ��ǰ����״̬.
* @param[in]	fd		-	�ǽӶ������豸�ļ�������
* @param[out]	status	-	��ǰ����״̬�ȡ�NFC_OP_POLL NFC_OP_ANTICOLL
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.����Ϊ������ӳ����Ϣ:<br>
*               EINVAL  ---- ��Ч����    <br>
*               EIO     ---- Ӳ������    <br>
*               ECOMM   ---- У�����    <br>
*               EPROTO  ---- ��Ƭ����Ӧ��ISO14443������   <br>
*               EBADE   ---- ��Ƭ���ش�����Ӧ��Ϣ    <br>
*               EACCES  ---  ��Ƶ���еĿ�����T=CL��    <br>
*               ETIME   ---- ��ʱ    <br>
@else 
* @brief Get current operation status.
* @param[in]	fd		-	contactless card reader device file descriptor
* @param[out]	status	-	Current operation status, et. NFC_OP_POLL NFC_OP_ANTICOLL
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument    <br>
*               EIO     ---- hardware error    <br>
*               ECOMM   ---- Parity Error or CRC error    <br>
*               EPROTO  ---- the response from card not compatile with ISO14443    <br>
*               EBADE   ---- card return error response information    <br>
*               EACCES   ---  The card in RF field is not a T=CL card    <br>
*               ETIME   ---- timeout during poll card    <br>
@endif 
*/
int emv_contactless_obtain_status(int fd, int *status);

/**
@if Chinese
* @brief ��ȡ��ѯ�ڼ����������룬����ͻ�����������ȡ�����
* @param[in]	fd		-	�ǽӶ������豸�ļ�������
* @param[out]	error	-	���һ���������
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.����Ϊ������ӳ����Ϣ:<br>
*               EINVAL  ---- ��Ч����    <br>
*               EIO     ---- Ӳ������    <br>
*               ECOMM   ---- У�����    <br>
*               EPROTO  ---- ��Ƭ����Ӧ��ISO14443������   <br>
*               EBADE   ---- ��Ƭ���ش�����Ӧ��Ϣ    <br>
*               EACCES  ---  ��Ƶ���еĿ�����T=CL��    <br>
*               ETIME   ---- ��ʱ    <br>
@else 
* @brief Get last error code during the poll, prevent(collision, active, exchange, deactive).
* @param[in]	fd		-	contactless card reader device file descriptor
* @param[out]	error	-	Last error code
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument    <br>
*               EIO     ---- hardware error    <br>
*               ECOMM   ---- Parity Error or CRC error    <br>
*               EPROTO  ---- the response from card not compatile with ISO14443    <br>
*               EBADE   ---- card return error response information    <br>
*               EACCES   ---  The card in RF field is not a T=CL card    <br>
*               ETIME   ---- timeout during poll card    <br>
@endif 
*/
int emv_contactless_get_lasterror(int fd, int *error);

/**
@if Chinese
* @brief PCD��PICC����APDU����
* @param[in]	fd			-	�ǽӶ������豸�ļ�������
* @param[in]	sendlen		-	Ҫ���͵����ݳ���(���ֽ�Ϊ��λ)
* @param[in]	senddata	-	Ҫ���͵�����ֵ
* @param[out]	recvlen		-	�������ݵĳ���(���ֽ�Ϊ��λ)
* @param[out]	recvdata	-	���յ�����ֵ
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.����Ϊ������ӳ����Ϣ:<br>
*               EINVAL  ---- ��Ч����    <br>
*               EIO     ---- Ӳ������    <br>
*               ECOMM   ---- У�����    <br>
*               EPROTO  ---- ��Ƭ����Ӧ��ISO14443������   <br>
*               EBADE   ---- ��Ƭ���ش�����Ӧ��Ϣ    <br>
*               EACCES  ---  ��Ƶ���еĿ�����T=CL��    <br>
*               ETIME   ---- ��ʱ    <br>
@else 
* @brief Exchange APDU data between PCD and PICC
* @param[in]	fd			-	contactless card reader device file descriptor
* @param[in]	sendlen		-	The length of data (in bytes) to send
* @param[in]	senddata	-	The data to be send to PICC
* @param[out]	recvlen		-	The length of data (in bytes) that received
* @param[out]	recvdata	-	The data that received from PICC
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno:<br>
*               EINVAL  ---- invalid argument    <br>
*               EIO     ---- hardware error    <br>
*               ECOMM   ---- Parity Error or CRC error    <br>
*               EPROTO  ---- the response from card not compatile with ISO14443    <br>
*               EBADE   ---- card return error response information    <br>
*               EACCES   ---  The card in RF field is not a T=CL card    <br>
*               ETIME   ---- timeout during poll card    <br>
@endif 
*/
int emv_contactless_exchange_apdu(int fd, uint32_t sendlen, const void *senddata,
                                  uint32_t *recvlen, void *recvdata);

/**
@if Chinese
* @brief ��PCD�������ݵ�PICC�����������ͺ���������
* @param[in]	fd			-	�ǽӶ������豸�ļ�������
* @param[in]	sendlen		-	Ҫ���͵����ݳ���(���ֽ�Ϊ��λ)
* @param[in]	senddata	-	Ҫ���͵�����
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.
@else 
* @brief Send data from PCD to PICC nonblock, after sending return immediately
* @param[in]	fd			-	contactless card reader device file descriptor
* @param[in]	sendlen		-	The length of data (in bytes) to send
* @param[in]	senddata	-	The data to be send to PICC
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed,You can obtain the error code according to errno.
@endif 
*/
int emv_contactless_exchange_apdu_nonblock_send(int fd, uint32_t sendlen, const void *senddata);

/**
@if Chinese
* @brief ��PICC��ȡ����
* @param[in]	fd			-	�ǽӶ������豸�ļ�������
* @param[out]	error		-	���ؽ��������еĴ�����ETIME, EPROTO�ȡ�<br>
*                   			������󲻵���0������ζ�Ŵ������ˣ����ҽ�����ֹͣ�������ٴη���APDU��ȥ���
* @param[out]	status		-	��ʾ��ǰ����״̬:NFC_OP_POLL��NFC_OP_ANTICOLL��NFC_OP_ANTICOLL��NFC_OP_REMOVE��
* @param[out]	finish		-	1:������ɣ�Ȼ��Ӳ���recvlen��recvdata��ȡ��Ӧ���ݡ�<br>
*                     			0:δ��ɣ��ȴ���ɡ������������(��һ������error != 0)���������һ���ȴ���
* @param[out]	recvlen		-	��finish == 1ʱ�����յ������ݳ���(���ֽ�Ϊ��λ)��
* @param[out]	recvdata	-	��finish == 1ʱ����PICC���յ�������
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.
@else 
* @brief Get response data from PICC
* @param[in]	fd			-	contactless card reader device file descriptor
* @param[out]	error		-	Return the error during exchange, such as ETIME, EPROTO etc.<br>
*                     			if error not equal 0, that means error occur, and exchange stopped, try send APDU again or deactive.
* @param[out]	status		-	Show current operation state:NFC_OP_POLL, NFC_OP_ANTICOLL, NFC_OP_ANTICOLL, NFC_OP_REMOVE.
* @param[out]	finish		-	1:exchange finish, then get response data from parameter recvlen and recvdata.<br>
*                     			0:not finish, wait until finish. If error occur(the first parameter error != 0), no need to wait further.
* @param[out]	recvlen		-	When finish == 1, the length of data (in bytes) that received.
* @param[out]	recvdata	-	When finish == 1, the data that received from PICC
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno..
@endif 
*/
int emv_contactless_exchange_apdu_nonblock_response(int fd, int *error, int *status, int *finish, uint32_t *recvlen, void *recvdata);

/**
@if Chinese
* @brief	ֻ����ʹ��API��emv_contactless_exchange_apdu_nonblock_send����������ʱ����ֹ��ǰ����
* @param[in]	fd	-	�ǽӶ������豸�ļ�������
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.
@else 
* @brief	Abort current exchange, only if using API "emv_contactless_exchange_apdu_nonblock_send" to send data
* @param[in]	fd	-	Emv card device file descriptor
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif
*/
int emv_contactless_exchange_apdu_nonblock_abort(int fd);

int nfc_get_reg_param(int fd, void *buf, int *nr_reg);
int nfc_set_reg_param(int fd, const void *buf, int nr_reg);
#if 0
int nfc_start_status_notify(int fd, int *status);
int nfc_wait_status_changed(int fd, int *status, int timeout);
int nfc_stop_status_notify(void);
#endif
/**
@if Chinese
* @brief	���ǽӶ�������λΪISO14443ģʽ
* @param[in]	fd	-	�ǽӶ������豸�ļ�������
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.
@else 
* @brief	Reset the non-access card reader to ISO14443 mode
* @param[in]	fd	-	nfc card device file descriptor
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif
*/
int nfc_reset_iso144443(int fd);

/**
@if Chinese
* @brief ��/�رճ�ǿ
* @param[in]	fd		-	�ǽӶ������豸�ļ�������
* @param[in]	onoff	-	�򿪻�رգ�����ΪCARRIER_OFF �� CARRIER_ON
* @return ����ֵ<br>
*   <em> 0 </em>    ----�ɹ�    <br>
*   <em> -1 </em>   ----ʧ��, �ɸ���errno��ȡ������.
@else 
* @brief open/close field
* @param[in]	fd		-	nfc card device file descriptor
* @param[in]	onoff	-	Turn it on or off with the parameter CARRIER_OFF or CARRIER_ON
* @return <br>
*   <em> 0 </em>    ----success    <br>
*   <em> -1 </em>   ----failed, You can obtain the error code according to errno.
@endif  
*/
int nfc_carrier_control(int fd, uint8_t onoff);

#define CARRIER_OFF              0x00       /**<@if Chinese �رճ�ǿ @else	Close the field strength	@endif*/
#define CARRIER_ON               0x01       /**<@if Chinese ������ǿ @else	Open field	@endif*/

#ifdef CFG_EMV_L1_TEST

/**
@if Chinese
	* @brief �����ڶԷǽ�EMV-L1��֤
@else 	
	* @brief It is used only for emV-L1 authentication
@endif 	
 */
int emv_L1_transac_a_test(void);
int emv_L1_transac_b_test(void);
int emv_set_exit_flag(int flag);
int emv_L1_digital_test(void);
int emv_set_cmd_flag(int flag);

int nfc_set_time_param(int fd, nfc_time_param_t *time_param);
int nfc_get_time_param(int fd, nfc_time_param_t *time_param);
int nfc_time_optimize_ctl(int fd, int on_off);
int nfc_time_optimize_status(int fd, int *on_off);
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CONTACTLESS_H_ */

/** @} */
