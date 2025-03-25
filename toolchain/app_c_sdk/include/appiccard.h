/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app iccardģ��</strong> ��صĽӿ�
	 * @par �ļ�    appiccard.h
	 * @author		yangjing
	 * @date        2020-08-05
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-08-05    | 1.0.0        | yanjing       | �����ļ�
	 * 2022-04-15    | 1.0.1        | lydia         | ����Ӣ��ע��  
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app iccard </strong>  module
	 * @par file    appiccard.h
	 * @author		yangjing
	 * @date        2020-08-05
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-08-05    | 1.0.0        | yanjing       | create file
	 * 2022-04-15    | 1.0.1        | lydia         | Add English description
 @endif 
*/

/*!
 @if Chinese
	@defgroup appiccard ic��
 @else
	@defgroup appiccard iccard
 @endif
 * @{
*/

#ifndef _APP_IC_CARD_H_
#define _APP_IC_CARD_H_


#ifdef __cplusplus	
extern "C" {
#endif /* __cplusplus */

/**
 @if Chinese
	@brief  ��ö�������г��˿�������.
 @else
	@brief  This enumerated type lists the  card slot types.
 @endif
  */
typedef enum
{
	SLOT_PSAM1, 	/**< @if Chinese �Ӵ�ʽPSAM����1 @else contact PSAM1 card slot @endif */
	SLOT_PSAM2, 	/**< @if Chinese �Ӵ�ʽPSAM����2 @else contact PSAM2 card slot @endif */
	SLOT_PSAM3, 	/**< @if Chinese �Ӵ�ʽPSAM����3 @else contact PSAM3 card slot @endif */
	SLOT_PSAM4, 	/**< @if Chinese �Ӵ�ʽPSAM����4 @else contact PSAM4 card slot @endif */
	SLOT_EXCARD, 	/**< @if Chinese �Ӵ�ʽ�û����� @else contact user card slot @endif */
	SLOT_INRF, 	    /**< @if Chinese ���÷ǽӿ��� @else inner contactless card slot @endif */
	SLOT_EXRF_COM1, /**< @if Chinese ���÷ǽӿ���COM1�� @else external contactless COM1 card slot @endif */
	SLOT_EXRF_COM2, /**< @if Chinese ���÷ǽӿ���COM2�� @else external contactless COM2 card slot @endif */
	SLOT_EXRF_COM3, /**< @if Chinese ���÷ǽӿ���COM3�� @else external contactless COM3 card slot @endif */
	SLOT_EXRF_USB, 	/**< @if Chinese ���÷ǽӿ���USB�� @else external contactless USB slot @endif */
	SLOT_CHECK		/**< @if Chinese ���Ӵ�ʽ���۲忨״̬ @else check the status for contact card slot @endif */
} SlotType;

/**
 @if Chinese
	@brief  ��ö�������г���IC������.
 @else
	@brief  This enumerated type lists the IC card types.
 @endif
  */
typedef enum
{
    ICC_SLE4442,		
    ICC_SLE4428,		
    ICC_SLE4436,		
    ICC_AT24C64,		
    ICC_CPUCARD,
    ICC_MIFARE,    		
    ICC_RFCPU_1356,            //<�ǽ�CPU��13.56M
    ICC_RFCPU_24,              //<�ǽ�CPU��2.4G 
    ICC_AT88SC102,
    ICC_AT88SC153,
    ICC_AT88SC1604
} IccType;

/**
 @if Chinese
	@brief  ��ö�������г���IC����������.
 @else
	@brief  This enumerated type lists the IC card operation types.
 @endif
  */
typedef enum
{
	SLE4442_GET_ATR_BYTES, //�ϵ縴λ��ȡ��λӦ������
	SLE4442_READ_MAIN_MEMORY, //�����洢��
	SLE4442_UPDATE_MAIN_MEMORY, //�޸����洢��
	SLE4442_READ_PROTECTION_MEMORY, //�������洢��
	SLE4442_WRITE_PROTECTION_MEMORY, //д�����洢��
	SLE4442_READ_SECURITY_MEMORY, //�����ܴ洢��
	SLE4442_UPDATE_SECURITY_MEMORY, //�޸ļ��ܴ洢��
	SLE4442_COMPARE_VERIFICATION_DATA, //�Ƚ�У������
	SLE4442_PSC_VERIFICATION, //�ɱ�̼��ܴ�����֤
	SLE4428_GET_ATR_BYTES, //�ϵ縴λ��ȡ��λӦ������
	SLE4428_READ_PROTECTED, //������λ��
	SLE4428_READ_UNPROTECTED, //��������λ��
	SLE4428_WRITE_ERASE_PROTECTED, //�����ʹ�����λд
	SLE4428_WRITE_ERASE_UNPROTECTED, //�����Ͳ�������λд
	SLE4428_PROTECT_COMPARE, //���Ƚϵı���λд
	SLE4428_PSC_VERIFICATION, //�ɱ�̼��ܴ�����֤
	SLE4428_SET_PSC, //���ÿɱ�̼��ܴ���
	SLE4436_READ_BYTES, //��ȡָ��λ�����ֽ�
	SLE4436_WRITE_BYTES, //д��ָ��λ�����ֽ�
	SLE4436_WRITE_ERASE_CARRY, //�ڼ�������λ��ִַ��д/����/��λ
	SLE4436_WRITE_ERASE_CARRY_BACKUP,//�ڼ�������λ��ִַ��д/����/��λ�����ñ���
	SLE4436_AUTHENTICATE_CARD, //ִ����֤
	SLE4436_PRESENT_CODE, //��Ƭ�ṩ�����ֽڵĴ�����
	AT24C64A_READ_CARD_MEMORY, //��ָ��λ�ö����ڴ�
	AT24C64A_READ_CARD_MEM_SEQUL, //�ӵ�ǰ��Ƭλ�ö����ڴ�
	AT24C64A_WRITE_CARD_MEMORY, //��ָ��λ��д����Ϣ
	AT24C64A_MEM_RESET,//�洢����λ
	MIFARE_AUTH_BLOCK, //��֤����ָ�����ݿ������
	MIFARE_READ_BLOCKS, //�����ݿ�
	MIFARE_WRITE_BLOCKS, //д���ݿ�
	MIFARE_INCREASE_DATA, //�������ݿ����ݲ���������浽�Ĵ�����
	MIFARE_DECREASE_DATA, //�������ݿ����ݲ���������浽�Ĵ�����
	CPUCARD_TRANSMIT_APDU //����APDU����
} OperationType;

/**
 @if Chinese
	@brief  ��ö�������г���IC��APDU.
 @else
	@brief  This enumerated type lists the IC card apdu.
 @endif
  */
typedef struct
{
	unsigned char OperType; /* reference enum - OperationType */
	unsigned char CLA; /* Class unsigned char of the command message*/
	unsigned char INS; /* Instrution*/
	unsigned char P1; /* Parameter1*/
	unsigned char P2; /* Parameter2*/
	unsigned char Lc; /* length of being sent data*/
	unsigned char Le; /* length of expected data*/
	unsigned char SW1; /* status word1*/
	unsigned char SW2; /* status word2*/
	unsigned char C_Data[256]; /* command data*/
	unsigned char R_Data[256]; /* response data*/
} ICCAPDU;

/**
 @if Chinese
	@brief  ��ö�������г���IC��״̬.
 @else
	@brief  This enumerated type lists the IC card status.
 @endif
  */
typedef enum
{
	ICC_NORF = -4,        /**< @if Chinese �޷ǽӿ�Ƭ @else no contactless card @endif */ 
	ICC_EMPTY = -3,       /**< @if Chinese �����޿�Ƭ @else no card in card slot @endif */ 
	ICC_COMMAND_FAIL = -2,/**< @if Chinese �뿨ƬͨѶ���� @else communication error with card @endif */ 
	ICC_FAIL = -1,        /**< @if Chinese ����ʧ�� @else operation failed @endif */ 
	ICC_OK = 0            /**< @if Chinese �����ɹ� @else operation success @endif */
}ICCStatus;

/*!
 @if Chinese
	@brief          ���Ӵ�ʽ��Ƭ�Ƿ��ڿ�����
	@param[in]      iSlotType	-	���ۺţ��ο�enum SlotType
	@return         IC��״̬
 @else
	@brief          check whether the contact card is in the card slot
	@param[in]      iSlotType	-	card slot type��reference enum SlotType
	@return         IC card status
 @endif
*/
extern int app_icc_getcardstatus(int iSlotType);

/*!
 @if Chinese
	@brief          �Ӵ�ʽIC���ϵ�
	@param[in]      iCardType	-	IC�����ͣ��ο�enum IccType
	@param[in]      iSlotType	-	���ۺţ��ο�enum SlotType
	@return         IC��״̬
 @else
	@brief          contact IC card power on
	@param[in]      iCardType	-	IC card type��reference enum IccType
	@param[in]      iSlotType	-	card slot type��reference enum SlotType
	@return         IC card status
 @endif
*/
extern int app_icc_powerup(int iCardType, int iSlotType);

/*!
 @if Chinese
	@brief          �Ӵ�ʽ��Ƭ�µ�
	@param[in]      iCardType	-	IC�����ͣ��ο�enum IccType
	@param[in]      iSlotType	-	���ۺţ��ο�enum SlotType
	@return         IC��״̬
 @else
	@brief          contact IC card power off
	@param[in]      iCardType	-	IC card type��reference enum IccType
	@param[in]      iSlotType	-	card slot type��reference enum SlotType
	@return         IC card status
 @endif
*/
extern int app_icc_powerdown(int iCardType,  int iSlotType);

/*!
 @if Chinese
	@brief          �Ӵ�ʽIC��ͨѶ����
	@param[in]      iCardType	-	IC�����ͣ��ο�enum IccType
	@param[in]      iSlotType	-	���ۺţ��ο�enum SlotType
	@param[in]      Apdu		-	�������Ŀ�Ƭ��������ICCAPDU�ṹ�е�OperType�������Ͷ���
	@param[out]     Apdu		-	���ص����ݸ���ICCAPDU�ṹ�е�OperType�������Ͷ���������R_Data��
	@return         IC��״̬
 @else
	@brief          Send APDU to ICCard, and receive APDU from ICCard
	@param[in]      iCardType	-	IC card type��reference enum IccType
	@param[in]      iSlotType	-	card slot type��reference enum SlotType
	@param[in]      Apdu		-	send APDU,reference OperType from struct ICCAPDU 
	@param[out]     Apdu		-	receive APDU,reference OperType from struct ICCAPDU 
	@return         IC card status
 @endif
*/
extern int app_icc_comm (int iCardType,int iSlotType , ICCAPDU *Apdu);

/*!
 @if Chinese
	@brief          �Ӵ�ʽIC��ͨѶ����(͸��)
	@param[in]      iCardType	-	IC�����ͣ��ο�enum IccType
	@param[in]      iSlotType	-	���ۺţ��ο�enum SlotType
	@param[in]      sendlen		-	���͵����ݳ���
	@param[in]      senddata	-	���͵���������
	@param[out]     recvlen		-	�յ������ݳ���
	@param[out]     recvdata	-	�յ�����������
	@return         IC��״̬
 @else
	@brief          contact IC card communication function
	@param[in]      iCardType	-	IC card type��reference enum IccType
	@param[in]      iSlotType	-	card slot type��reference enum SlotType
	@param[in]      sendlen		-	the length of send data
	@param[in]      senddata	-	send data buffer
	@param[out]     recvlen		-	the length of receive data
	@param[out]     recvdata	-	receive data buffer
	@return         IC card status
 @endif
*/
extern int app_icc_comm_raw(int iCardType,int iSlotType,  uint32_t sendlen, const void *senddata, uint32_t *recvlen, void *recvdata);

/*!
 @if Chinese
	@brief          �ǽӶ�����Ѱ��
	@param[in]      iCardType	-	IC�����ͣ��ο�enum IccType
	@param[in]      iSlotType	-	���ۺţ��ο�enum SlotType
	@param[out]     psUID		-	�����к�,��һ���ֽ�Ϊ���кų���
	@return         IC��״̬
 @else
	@brief          contactless card reader search card 
	@param[in]      iCardType	-	IC card type��reference enum IccType
	@param[in]      iSlotType	-	card slot type��reference enum SlotType
	@param[out]     psUID		-	card serial number. The first byte is the length of the serial number
	@return         IC card status
 @endif
*/
extern int app_icc_ctls_powerup_seek (int iCardType, int iSlotType, char *psUID);

/*!
 @if Chinese
	@brief          ��IC���豸
	@param[in]      iSlotType	-	���ۺţ��ο�enum SlotType
	@return         IC��״̬
 @else
	@brief          open IC card device 
	@param[in]      iSlotType	-	card slot type��reference enum SlotType
	@return         IC card status
 @endif
*/
extern int app_icc_open(int iSlotType);

/*!
 @if Chinese
	@brief          �ر�IC���豸
	@param[in]      iSlotType	-	���ۺţ��ο�enum SlotType
	@return         IC��״̬
 @else
	@brief          close IC card device 
	@param[in]      iSlotType	-	card slot type��reference enum SlotType
	@return         IC card status
 @endif
*/
extern int app_icc_close(int iSlotType);

/*!
 @if Chinese
	@brief          ����IC�����ۻ�ȡ��Ӧ��������
	@param[in]      iSlotType	-	���ۺţ��ο�enum SlotType
	@return         >=0			-	�ɹ�,���۶�Ӧ��������   other-fail
 @else
	@brief          get card slot descriptor
	@param[in]      iSlotType	-	card slot type��reference enum SlotType
	@return         >=0			-	success,card slot descriptor
	@return         other	-	fail
 @endif
*/
int app_icc_get_slotfd(int iSlotType);

/*!
 @if Chinese
	@brief          IC��ͨѶ����
	@param[in]      slottype	-	���ۺţ��ο�enum SlotType
	@param[in]      sendlen		-	���͵����ݳ���
	@param[in]      senddata	-	���͵���������
	@param[out]     recvlen		-	�յ������ݳ���
	@param[out]     recvdata	-	�յ�����������
	@return         IC��״̬
 @else
	@brief          IC card communication function 
	@param[in]      slottype	-	card slot type��reference enum SlotType
	@param[in]      sendlen		-	the length of send data
	@param[in]      senddata	-	send data buffer
	@param[out]     recvlen		-	the length of receive data
	@param[out]     recvdata	-	receive data buffer
	@return         IC card status
 @endif
*/
extern int app_icc_exchange_apdu(int slottype, uint32_t sendlen, unsigned char *senddata, uint32_t *recvlen, unsigned char *recvdata);

#ifdef __cplusplus
	}
#endif /* __cplusplus */

#endif


