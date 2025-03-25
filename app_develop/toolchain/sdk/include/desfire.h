/*!
 @if Chinese
 	@file        desfire.h
	@author      neal
	@date        2010-10-14
	@version     1.0.0
	@note        ��ģ���������� <strong>mifare desfire</strong> ��صĽӿ�
	@remarks     �޸ļ�¼:
	����          | ����            | ����
	------------- | --------------- | ----
	2010-10-14    | neal            | Create file
 @else
	@file        desfire.h
	@author      neal
	@date        2010-10-14
	@version     1.0.0
	@note        This module is used to describe <strong>mifare desfire</strong> interfaces module
	@remarks     Change History:
	Date          | Author          | Desc
	------------- | --------------- | ----
	2010-10-14    | neal            | Create file
 @endif
*/

/*
 * desfire.h
 *
 *  Created on: Oct 14, 2010
 *      Author: neal
 */

#ifndef DESFIRE_H_
#define DESFIRE_H_

#ifdef __cplusplus
  extern "C" {
#endif /* __cplusplus */

/*!
 @if Chinese
 	@brief       ��ģ����������desfireģ����صĽӿ�,�����ӿ�<b>libnfc.so</b>����
	
	Դ�ļ���<a href="desfire_8h_source.html">desfire.h</a>
 @else
	@brief       This module is used to describe the relevant interface of the desfire module, Need to link library <b>libnfc.so</b> to compile

	Source file: <a href="desfire_8h_source.html">desfire.h</a>
 @endif
 @defgroup desfire desfire
 @ingroup G_NFC
 @{
*/

/*!
 @anchor DESFireErr
 @if Chinese 
 @name Mifare DESFire�����ش�����˵��
 @{
	����ֵ        | ԭ��
	------------- | --------------- 
	1036	      | û�жԱ����ļ����κθ��ģ�����Ҫ�ύTransaction/AbortTransaction
	1038	      | NV-Memory�ڴ治�㣬�޷��������
	1052          | ��֧��������
	1054          | CRC��MAC��ƥ�䣬����ֽ���Ч
	1088          | ָ���ļ�����Ч
	1150          | �����ַ���������Ч
	1181          | ��ǰ����/״̬���������������
	1182          | ������ֵ��Ч
	1184          | �����AID��PICC�ϲ�����
	1185          | Ӧ�ó������޷��ָ��Ĵ���Ӧ�ó��򽫱�����
	1198          | ��ǰ�����֤״̬���������������
	1199          | �������͸��������֡
	1214          | ���Դ�/�� �ļ�/��¼ ������ ��ȡ/д�� ���ݣ�<br>���Գ����ļ�ֵ������
	1217          | PICC�з������ɻָ��Ĵ���PICC��������
	1226          | ��һ��������δ��ȫ��ɡ��������е�֡������PICC������ṩ��
	1229          | PICC�򲻿ɻָ��Ĵ����������
	1230          | Ӧ�ó�����������Ϊ28���޷������CreateApplication
	1246          | �ļ�/Ӧ�ó��򴴽�ʧ�ܣ���Ϊ������ͬ��ŵ��ļ�/Ӧ�ó����Ѿ�����
	1262          | ���ڶϵ���޷����NV-Memoryд��������ڲ�����/���˻����Ѽ���
	1264          | ָ�����ļ��Ų�����
	1265          | �ļ��ڷ������ɻָ��Ĵ����ļ��������á�
 @else
 @name Error code for mifare DESFire operation
 @{	 
	Return value  | Reason          
	------------- | --------------- 
	1036          |  No changes done to backup files,Commit Transaction/AbortTransaction not necessary
	1038          |  Insufficient NV-Memory to complete command
	1052          |  Command code not supported
	1054          |  CRC or MAC does not match data ,Padding bytes not valid
	1088          |  Invalid key number specified
	1150          |  Length of command string invalid
	1181          |  Current configuration/status does not allow the requested command
	1182          |  Value of the parameter(s) invalid
	1184          |  Requested AID not present on PICC
	1185          |  Unrecoverable error within application, application will be disabled
	1198          |  Current authentication status does not allow the requested command
	1199          |  Additional data frame is expected to be sent
	1214          |  Attempt to read/write data from/to beyond the file's/record's limits <br>or Atempt to exceed the limits of a value file
	1217          |  Unrecoverable error within PICC,PICC will be disabled
	1226          |  Previous Command was not fully completed. Not all Frames were requested or provided by the PICC
	1229          |  PICC was disabled by an unrecoverable error
	1230          |  Number of Applications limited to 28,no additional CreateApplication possible
	1246          |  Creation of file/application failed because file/application with same number already exists
	1262          |  Could not complete NV-write operation due to loss of power,interal backup/rollback mechanism activated
	1264          |  Specified file number does not exist
	1265          |  Unrecoverable error within file, file will be disabled.
 @endif
*/
#define DESFireErr	"Just to show the table above."
/** @} */

/**
 @if Chinese
	@brief			����Ӧ�����Ƿ����mifare DESFire�������У��򼤻�
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		mode		��ѯģʽ��ȡֵ���£�					\n
								0������ѯ���д���IDLE״̬�Ŀ�Ƭ			\n
								1����ѯ���д���IDLE����HALT״̬�Ŀ�Ƭ
	@param[out]		uid			��Ƭ���ص�7�ֽ�UID��Ϣ
	@param[out]		atslen		��Ƭ���ص�ATS��Ϣ����
	@param[out]		ats			��Ƭ���ص�ATS��Ϣ
	@retval   	    0			Ѱ�������ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺				\n
								ENODATA		����Ӧ������ mifare DESFire ��			\n	
								EMULTIHOP	����Ӧ�����ж࿨						\n
								EPROTO		����Ƭ�������ݲ����� ISO14443 Э��		\n
								EBADE		����Ƭ���ص����ݳ��Ȳ���ȷ				\n
								EINVAL		����������								\n
								ECOMM		����Ƭ���ص�������ż����� CRC У���	\n
								EIO			������оƬ����							\n
								ETIME		����ʱ����								\n
								����ֵ		������������
 @else
	@brief			Poll if there is mifare DESFire card in inductive zone, if there is, active it.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		mode		polling mode , values are as follow:				\n
								0: just polling card of IDLE state					\n
								1: polling card of IDLE state and HALT state
	@param[out]		uid			7 bytes UID information that card returns
	@param[out]		atslen		length of ATS information that card returns
	@param[out]		ats			ATS information that card returns
	@retval   	    0			find card success
	@retval   	    -1			operate failure, please get the actual error code by errno:			\n
								ENODATA		: is not a mifare mifare DESFire in inductive zone		\n	
								EMULTIHOP	: there is multiple cards in inductive zone				\n
								EPROTO		: Card doesn��t comply with ISO14443 protocol			\n
								EBADE		: error of length of card returned data					\n
								EINVAL		: parameter error										\n
								ECOMM		: Parity error or CRC check error of card returned data	\n
								EIO			: read card chip error									\n
								ETIME		: timeout return										\n
								Other value	: other error code
 @endif
*/
int desfire_poll(int fd,uint8_t mode,void *uid, uint8_t *atslen, void *ats);

/**
 @if Chinese
	@brief			��λmifare DESFire��
	@param[in]		fd			mif_open�������������豸���ļ���
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ�����
 @else
	@brief			Reset mifare DESFire card.
	@param[in]		fd			opened device file number that mif_open function returns
	@retval   	    0			Operate OK
	@retval   	    -1			operate failure, please get the actual error code by errno
 @endif
*/
int desfire_deactive(int fd);

/**
 @if Chinese
	@brief			��mifare DESFire������DES/3DES��Կ��֤
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		keyno		Ҫ��֤����Կ��
	@param[in]		key			��Կ��Ϣ���̶�Ϊ16�ֽ�
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�� �����������											\n
								EIO		�� ����оƬ����											\n
								ECOMM	�� ��Ƭ����������ż����� CRC У���					\n
								EPROTO	�� ��Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	�� ��Ƭ�������ݳ��ȴ���									\n
								ETIME	�� ��ʱ�޷���											\n
								EACCES	�� ��Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	�� ����������
	@note
		- key��Ϣ����Ϊ16�ֽڵģ����ʵ����Կֻ��8�ֽڣ������з�ʽ��չ��16�ֽڣ�<br>
			`key = old_key[0��7] || old_key[0��7]`
 @else
	@brief			Poll if there is mifare DESFire card in inductive zone, if there is, active it.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		keyno		key number that will be certificated
	@param[in]		key			key information, is fixed 16 bytes
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM 		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
	@note
		- key information must be 16 types, if actual key is 8 bytes, then expanding it to 16 bytes as follow:<br>
			`key = old_key[0��7] || old_key[0��7]`
 @endif
*/
int desfire_authenticate(int fd,uint8_t keyno, const void *key);

/**
 @if Chinese
	@brief			��mifare DESFire������DES/3DES��Կ��֤
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		keyno		Ҫ��֤����Կ��
	@param[in]		key			��Կ��Ϣ���̶�Ϊ24�ֽ�
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
	@note
		- key ��Ϣ����Ϊ 24 �ֽڵģ� ���ʵ����Կֻ�� 8 �ֽڣ� �����з�ʽ��չ�� 24 �ֽڣ�<br>
			`key = old_key[0��7] || old_key[0��7] || old_key[0��7]`
		- ���ʵ����Կֻ��16�ֽڣ� �����з�ʽ��չ��24�ֽڣ�<br>
			`key = old_key[0��7] || old_key[8��15] || old_key[0��7]`
 @else
	@brief			Do 3KDES key authentification on mifare DESFire card.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		keyno		key number that will be authenticated
	@param[in]		key			key information, is fixed 24 bytes
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n								\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t fix ISO14443 standard											\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
	@note
		- key information must be 24 types, if actual key is 8 bytes, then expanding it to 24 bytes as follow:<br>
			`key = old_key[0��7] || old_key[0��7] || old_key[0��7]`
		- if actual key is 16 bytes, then expanding it to 24 bytes as follow:<br>
			`key = old_key[0��7] || old_key[8��15] || old_key[0��7]`
 @endif
*/
int desfire_authenticate_iso(int fd,uint8_t keyno, const void *key);

/**
 @if Chinese
	@brief			��mifare DESFire������AES��Կ��֤
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		keyno		Ҫ��֤����Կ��
	@param[in]		key			��Կ��Ϣ���̶�Ϊ16�ֽ�
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
	@note
		- AES��Կ�̶�����Ϊ16�ֽ�
 @else
	@brief			Do AES key authentication on mifare DESFire card.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		keyno		key number that will be certificated
	@param[in]		key			key information, is fixed 16 bytes
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n								\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
	@note
		- AES key��s length is fixed 16 bytes
 @endif
*/
int desfire_authenticate_aes(int fd,uint8_t keyno, const void *key);

/**
 @if Chinese
	@brief			�޸�PICC Master Key���û���Application Master Key����
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		key_setting	�µ� Master Key ���ò���
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Modify PICC Master Key set or Application Master Key set.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		key_setting	new Master Key setting parameter
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code	
 @endif
*/
int desfire_change_key_settings(int fd,uint8_t key_setting);

/**
 @if Chinese
	@brief			�޸�PICC Master Key���û���Application Master Key����
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[out]		key_setting	��Ƭ���ص�Master Key���ò���
	@param[out]		max_key_num	��ǰӦ��֧�ֵ������Կ��
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Get PICC Master Key setting or Application Master Key setting.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[out]		key_setting	Master Key setting parameter that card returned
	@param[out]		max_key_num	maximum key number that current application supports
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_get_key_settings(int fd,uint8_t *key_setting, uint8_t *max_key_num);

/**
 @if Chinese
	@brief			�޸�PICC Master Key
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		type		PICC Master Key��Կ���ͣ�ȡֵ���£�	\n
								0x00��DES/3DES��Կ��16 �ֽڣ�		\n
								0x01��3KDES��Կ��24 �ֽڣ�			\n
								0x02��AES��Կ��16 �ֽڣ�
	@param[in]		key			��Կ��Ϣ��16/24�ֽ�
	@param[in]		version		��Կ�汾��Ϣ
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺						\n
								EINVAL	�������������										\n
								EIO		������оƬ����										\n
								ECOMM	����Ƭ����������ż�����CRCУ���					\n
								EPROTO	����Ƭ�������ݲ�����ISO14443�淶					\n
								EBADE	����Ƭ�������ݳ��ȴ���								\n
								ETIME	����ʱ�޷���										\n
								EACCES	����Ӧ���ڵĿ�Ƭ����mifare DESFire�����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Change PICC Master Key.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		type		PICC Master Key key type, values as follow:	\n
								0x00: DES/3DES key (16 bytes)				\n
								0x01: 3KDES key (24 �ֽ�)					\n
								0x02: AES key (16 �ֽ�)
	@param[in]		key			key information, 16/24 bytes
	@param[in]		version		key version information
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_change_picc_masterkey(int fd,uint8_t type, const void *key,uint8_t version);

/**
 @if Chinese
	@brief			�޸�Ӧ����Կ
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		keysetting	Ӧ�õ�master key�������Բ���
	@param[in]		type		PICC Master Key��Կ���ͣ�ȡֵ���£�	\n
								0x00��DES/3DES��Կ��16 �ֽڣ�		\n
								0x01��3KDES��Կ��24 �ֽڣ�			\n
								0x02��AES��Կ��16 �ֽڣ�
	@param[in]		keyno		Ҫ�޸ĵ���Կ��
	@param[in]		oldkey		�ɵ���Կ��Ϣ��16/24�ֽ�
	@param[in]		newkey		�µ���Կ��Ϣ��16/24�ֽ�
	@param[in]		version		��Կ�汾��Ϣ
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Change application key.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		keysetting	application��s master key configuration attribute parameter
	@param[in]		type		PICC Master Key key type, values as follow:	\n
								0x00: DES/3DES key (16 bytes)				\n
								0x01: 3KDES key (24 �ֽ�)					\n
								0x02: AES key (16 �ֽ�)
	@param[in]		keyno		key number that will be modified
	@param[in]		oldkey		old key information, 16/24 bytes
	@param[in]		newkey		new key information, 16/24 bytes
	@param[in]		version		key version information
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_change_app_key(int fd,
								 uint8_t keysetting,
								 uint8_t type, 
								 uint8_t keyno, 
								 const void *oldkey,
								 const void *newkey, 
								 uint8_t version);
/**
 @if Chinese
	@brief			�޸�PICC Master Key���û���Application Master Key����
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		keyno		��Կ��
	@param[out]		version		��Ƭ���ص���Կ�汾��Ϣ
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Get PICC Master Key setting or Application Master Key setting.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		keyno		key number
	@param[out]		version		key version information that card returned
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_get_key_version(int fd,uint8_t keyno,uint8_t *version);

/**
 @if Chinese
	@brief DesfireӦ�ó�����Ϣ
 @else
	@brief Desfire application information
 @endif
*/
typedef struct
{
	uint8_t AID[3];				/*!< @if Chinese �й�Ӧ�ñ�ʶ @else Application Identifies @endif */
	uint8_t MasterKeySetting; 	/*!< @if Chinese Ӧ�ó�����key���� @else Application master key setting @endif */
	uint8_t NumberOfKey; 		/*!< @if Chinese ������Ӧ�ó����ڴ洢����Կ�� @else Number of keys that can be stored within the application @endif */
	uint8_t CryptoMode;			/*!< @if Chinese Ӧ�ó���ļ���key���ͣ�<br>0 - DES/3DES key<br>1 - 3KDES key<br>2 - AES key @else the key type of application:<br>0 - DES/3DES key<br>1 - 3KDES key<br>2 - AES key @endif */
	uint8_t IsSupFID; 			/*!< @if Chinese �Ƿ�ʹ���ļ���ʶ @else whether use File Identifies @endif */
	uint8_t IsSupISOFID; 		/*!< @if Chinese �Ƿ�ʹ��2�ֽ�ISO/IEC 7816-4�ļ���ʶӦ�ó����е��ļ� @else whether use of 2 byte ISO/IEC 7816-4 File Identifies for files within the Application @endif */
	uint8_t ISOFID[2];			/*!< @if Chinese 2�ֽ�ISO/IEC 7816-4�ļ���ʶ�ļ� @else 2 byte ISO/IEC 7816-4 File Identifies for files @endif */
	uint8_t LenOfDFName; 		/*!< @if Chinese 7816-4ģʽ��ʹ�õ�"DF-name"�ĳ��ȣ�0-��Я��"DF-name" @else the length of "DF-name" used in 7816-4 mode, 0 - does not carries "DF-name" @endif */
	uint8_t DFName[16]; 		/*!< @if Chinese ��7816-4ģʽ����ISO SELECT������ʹ�õ�"DF-name" @else "DF-name" used in 7816-4 mode in combination with the ISO SELECT command @endif */
	uint8_t RFU;
}desfire_appinfo;

/**
 @if Chinese
	@brief			����һ����Ӧ��
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		info		Ӧ����Ϣ
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Create a sub-application.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		info		application information
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_create_application(int fd,const desfire_appinfo *info);

/**
 @if Chinese
	@brief			ɾ��һ����Ӧ��
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		aid			Ӧ�õ�AID��Ϣ��3�ֽ�
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺						\n
								EINVAL	�������������										\n
								EIO		������оƬ����										\n
								ECOMM	����Ƭ����������ż����� CRC У���					\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶					\n
								EBADE	����Ƭ�������ݳ��ȴ���								\n
								ETIME	����ʱ�޷���										\n
								EACCES	����Ӧ���ڵĿ�Ƭ����mifare DESFire�����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Delete a sub-application.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		aid			application AID information, 3 bytes
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_delete_application(int fd,const void *aid);

/**
 @if Chinese
	@brief			��ȡDESFire��������Ӧ�õ�AID��Ϣ
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[out]		num			��Ƭ������Ӧ�ø���
	@param[out]		aid			Ӧ�õ�AID��Ϣ��3�ֽ�/ÿ��Ӧ��
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Get all application��s AID information of DESFire card.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[out]		num			application number that card contained
	@param[out]		aid			application AID information, 3 bytes every application
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_get_application_ids(int fd,uint8_t *num, void *aid);

/**
 @if Chinese
	@brief Desfire��Ӧ��������Ϣ
 @else
	@brief Desfire card application name information
 @endif
*/
typedef struct
{
	uint8_t AID[3];			/*!< @if Chinese Ӧ�ñ�ʶ�� @else Application Identifies @endif */
	uint8_t FID[2];			/*!< @if Chinese 2�ֽ�ISO/IEC 7816-4�ļ���ʶ�ļ� @else 2 byte ISO/IEC 7816-4 File Identifies for files @endif */
	uint8_t LenOfDFName;	/*!< @if Chinese 7816-4ģʽ��ʹ�õ�"DF-name"�ĳ��ȣ�0-��Я��"DF-name" @else the length of "DF-name" used in 7816-4 mode, 0 - does not carries "DF-name" @endif */
	uint8_t DFName[16];		/*!< @if Chinese ��7816-4ģʽ����ISO SELECT������ʹ�õ�"DF-name" @else "DF-name" used in 7816-4 mode in combination with the ISO SELECT command @endif */
	uint8_t RFU[2];			/*!< @if Chinese RFU @else RFU @endif */
}dfname_info;

/**
 @if Chinese
	@brief			��ȡDESFire��������Ӧ�õ���Ϣ
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[out]		appnum		��Ƭ������Ӧ�ø���
	@param[out]		info		Ӧ����Ϣ��ÿ��Ӧ��һ��dfname_info�ṹ
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Get all application��s information of DESFire.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[out]		appnum		application number that card contained
	@param[out]		info		application information, every application has a dfname_info struct
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_get_dfnames(int fd,uint8_t *appnum,dfname_info *info);

/**
 @if Chinese
	@brief			ѡ��һ����Ӧ��
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		aid			Ӧ�õ�AID��Ϣ��3�ֽ�
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Select a sub-application.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		aid			application AID information, 3 bytes
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_select_application(int fd,const void *aid);

/**
 @if Chinese
	@brief			��ʽ������DESFire����ɾ�����е�Ӧ���Լ�Ӧ���µ���Կ���ļ���Ϣ
	@param[in]		fd			mif_open�������������豸���ļ���
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Format DESFire card, delete all application and all application��s key and file information.
	@param[in]		fd			opened device file number that mif_open function returns
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA 	: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value : other error code
 @endif
*/
int desfire_format_picc(int fd);

/**
 @if Chinese
	@brief Desfire���İ汾��Ϣ
 @else
	@brief Desfire card version information
 @endif
*/
typedef struct  
{
	uint8_t HW_VendorID; 	/*!< @if Chinese ��Ӧ��ID��PHILIPSΪ0x04�� @else codes the vendor ID ( 0x04 for PHILIPS ) @endif */
	uint8_t HW_Type;		/*!< @if Chinese �������ͣ�����Ϊ0x01�� @else codes the type ( here 0x01 ) @endif */
	uint8_t HW_SubType;		/*!< @if Chinese ���������ͣ�����Ϊ0x01�� @else codes the subtype ( here 0x01 ) @endif */
	uint8_t HW_MajorVer;	/*!< @if Chinese ���汾�� @else codes the major version number @endif */
	uint8_t HW_MinorVer;	/*!< @if Chinese �ΰ汾�� @else codes the minor version number @endif */
	uint8_t HW_Size;		/*!< @if Chinese �Դ洢��С���б���(����0x1A = 8192�ֽ�) @else codes the storage size ( here 0x1A = 8192 bytes ) @endif */
	uint8_t HW_Protocol;	/*!< @if Chinese ͨ��Э������(����0x05��ʾISO 14443-2��-3) @else codes the communication protocol type (here 0x05 meaning ISO 14443-2 and -3 ) @endif */

	uint8_t SW_VendorID;	/*!< @if Chinese ��Ӧ��ID��PHILIPSΪ0x04�� @else codes the vendor ID ( here 0x04 for PHILIPS ) @endif */
	uint8_t SW_Type;		/*!< @if Chinese �������ͣ�����Ϊ0x01�� @else codes the type ( here 0x01 ) @endif */	
	uint8_t SW_SubType;		/*!< @if Chinese ���������ͣ�����Ϊ0x01�� @else codes the subtype ( here 0x01 ) @endif */
	uint8_t SW_MajorVer;	/*!< @if Chinese ���汾�� @else codes the major version number @endif */	
	uint8_t SW_MinorVer;	/*!< @if Chinese �ΰ汾�� @else codes the minor version number @endif */
	uint8_t SW_Size;		/*!< @if Chinese �Դ洢��С���б���(����0x1A = 8192�ֽ�) @else codes the storage size ( here 0x1A = 8192 bytes ) @endif */
	uint8_t SW_Protocol;	/*!< @if Chinese ͨ��Э������(����0x05��ʾISO 14443-2��-3) @else codes the communication protocol type (here 0x05 meaning ISO 14443-2 and -3 ) @endif */

	uint8_t UID[7];			/*!< @if Chinese Ψһ���к� @else code the unique serial number @endif */
	uint8_t BatchNo[5];		/*!< @if Chinese �������� @else code the production batch number @endif */
	uint8_t CW_Prod;		/*!< @if Chinese ���������� @else codes the calendar week of production @endif */
	uint8_t Year_Prod;		/*!< @if Chinese ����������� @else codes the year of production @endif */
}desfire_version;

/**
 @if Chinese
	@brief			��ȡmifare DESFire���İ汾��Ϣ
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[out]		version		mifare DESFire ���İ汾��Ϣ
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Get version information of mifare DESFire card.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[out]		version		version information of mifare DESFire card
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n	
								Other value	: other error code
 @endif
*/
int desfire_get_version(int fd, desfire_version *version);

/**
 @if Chinese
	@brief			����mifare DESFire��
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		option		������Ϣѡ��
	@param[in]		len			������Ϣ����
	@param[in]		info		������Ϣ����
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Configure mifare DESFire card.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		option		configuration information option
	@param[in]		len			configuration information length
	@param[in]		info		content of configuration information
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_set_configuration(int fd,uint8_t option, uint8_t len,const void *info);

/**
 @if Chinese
	@brief			��ȡmifare DESFire����ʣ����ÿռ��С
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[out]		freesize	mifare DESFire����ʣ����ÿռ��С
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Get the size of the available memory space of mifare DESFire card.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[out]		freesize	size of the remaining available space of mifare DESFire card
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_free_memory(int fd,uint32_t *freesize);

/**
 @if Chinese
	@brief			��ȡmifare DESFire����UID��Ϣ
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[out]		uid			mifare DESFire�����ص�UID��Ϣ��7�ֽ�
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Get UID information of mifare DESFire card.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[out]		uid			UID information that mifare DESFire card returns, 7 bytes
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_get_card_uid(int fd,void *uid);

/**
 @if Chinese
	@brief			��ȡmifare DESFire����ǰ��Ӧ���ڵ��ļ�fid��Ϣ
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[out]		num			Ӧ���ڵ��ļ�����
	@param[out]		fid			�ļ���fid��Ϣ��1�ֽ�/ÿ���ļ�
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Get current sub-application��s file fid information of mifare DESFire card.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[out]		num			file number of application
	@param[out]		fid			fid information of file,1 byte every file
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_get_fids(int fd,uint8_t *num, void *fid);

/**
 @if Chinese
	@brief			��ȡmifare DESFire����ǰ��Ӧ���ڵ��ļ�iso fid��Ϣ
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[out]		num			Ӧ���ڵ��ļ�����
	@param[out]		fid			�ļ���iso fid��Ϣ��2�ֽ�/ÿ���ļ�
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Get current sub-application��s file iso fid information of mifare DESFire card.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[out]		num			file number of application
	@param[out]		fid			file iso fid information, 2 bytes every file
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_get_iso_fids(int fd,uint8_t *num, void *fid);

/**
 @if Chinese
	@brief Desfire�ļ���Ϣ
 @else
	@brief Desfire file information
 @endif
*/
typedef struct
{
	/** 
	 @if Chinese
		�������ͣ�����Ϊ0x01����		\n
		0x00  --- ��׼�����ļ�			\n
		0x01  --- ���������ļ�			\n
		0x02  --- �����ݵ�ֵ�ļ�		\n
		0x03  --- �����ݵ����Լ�¼�ļ�	\n
		0x04  --- �����ݵ�ѭ����¼�ļ�
	 @else
		DESfire file type:							\n
		0x00  --- Standard Data Files				\n
		0x01  --- Backup Data Files					\n
		0x02  --- Value Files wih Backup			\n
		0x03  --- Linear record Files with Backup	\n
		0x04  --- Cyclic Record Files with Backup
	 @endif
	*/
	uint8_t file_type;  
	/** 
	 @if Chinese
		ͨ�����ã�									\n
		0x00 or 0x02	--- �򵥵�ͨ��				\n
		0x01			--- ͨ��MACing��֤�򵥵�ͨ��	\n
		0x03			--- ��ȫ���ܵ�ͨ��
	 @else
		Communication settings:										\n
		0x00 or 0x02	--- Plain communication						\n
		0x01			--- Plain communication secured by MACing	\n
		0x03			--- Fully enciphered communication
	 @endif
	*/
	uint8_t com_sett;

	// Access right capability, 0x0E means free access, and 0x0F means deny access.
	uint8_t read_access_right_keyno;			/*!< @if Chinese �ڽ��ж����ʺͶ�д����֮ǰ��Ҫ��֤����Կ�� @else the reference number of the key which needs to be authenticated prior to Read Access and Read&Write Access @endif */
	uint8_t write_access_right_keyno;			/*!< @if Chinese ��д���ʺͶ�д����֮ǰ��Ҫ���������֤����Կ�� @else the reference number of the key which needs to be authentication prior to Write Access and Read&Write Access @endif */
	uint8_t read_and_write_access_right_keyno;	/*!< @if Chinese ��д����֮ǰ��Ҫ���������֤����Կ�� @else the reference number of the key which needs to be authentication prior to  Read&Write Access @endif */
	uint8_t change_access_right_keyno;			/*!< @if Chinese �ο���Կ�ţ�������������֤���ܸ����ļ��ķ���Ȩ�ޣ�����ÿ������Ȩ�����ӵ���Կ�� @else the reference number of the key,which is necessary to be authenticated with in order to change the access rights for the file and to link each access right to key numbers @endif */
	
	uint32_t file_size;							/*!< @if Chinese �û��ļ���С�����ֽ�Ϊ��λ��������file_type = 0x00��file_type = 0x01ʱ���� @else the user file size in bytes, only available when file_type = 0x00 or file_type = 0x01 @endif */

	// the following four parameters only available when file_type = 0x02
	uint32_t lower_limit;				/*!< @if Chinese ֵ�ļ������� @else lower limit of the value file @endif */
	uint32_t upper_limit;				/*!< @if Chinese ֵ�ļ������� @else upper limit of the value file @endif */
	uint32_t limited_credit_value; 		/*!< @if Chinese ��ǰ��������ö��ֵ @else the current maximum "limited credit" value @endif */
	uint8_t  limited_credit_enabled; 	/*!< @if Chinese ������ļ�����ʹ��LimitedCredit���0x00��ʾ���ã�0x01��ʾ���ã� @else if the LimitedCredit command is allowed for this file (0x00 for disabled, 0x01 for enabled) @endif */

	// the following three parameters  only available when file_type = 0x03 or file_type = 0x04
	uint32_t record_size;  				/*!< @if Chinese һ����¼�Ĵ�С�����ļ�����ʱ���壩 @else the size of one single record (as deefined at file creation) @endif */
	uint32_t max_number_of_records;  	/*!< @if Chinese ��¼�ļ��е�����¼�������ļ�����ʱ���壩 @else the maximum number of records within the record file (as defined at file creation) @endif */
	uint32_t current_number_of_records;	/*!< @if Chinese ��¼�ļ��е�ǰ�ļ�¼�� @else the current number of records within the record file @endif */
}desfire_file;

/**
 @if Chinese
	@brief			��ȡָ���ļ�����Ϣ
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		fileno		�ļ���
	@param[out]		filesetting	���ص��ļ���Ϣ
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�� �����������											\n
								EIO		�� ����оƬ����											\n
								ECOMM	�� ��Ƭ����������ż����� CRC У���					\n
								EPROTO	�� ��Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	�� ��Ƭ�������ݳ��ȴ���									\n
								ETIME	�� ��ʱ�޷���											\n
								EACCES	�� ��Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	�� ����������
 @else
	@brief			Get the designated file��s information.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		fileno		file number
	@param[out]		filesetting	returned file information
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_get_filesetting(int fd,uint8_t fileno, desfire_file *filesetting);

/**
 @if Chinese
	@brief			��ȡָ���ļ�����Ϣ
	@param[in]		fd							mif_open�������������豸���ļ���
	@param[in]		fileno						�ļ���
	@param[in]		comm_set					���ļ��Ĵ��䷽ʽ��ȡֵ���£�	\n
												0x00�����Ĵ���					\n
												0x03�����ܴ���					\n
												0x01����MAC����
	@param[in]		old_change_access_keyno		�ɵĸ�����Կ����֤����Կ��
	@param[in]		new_read_access_keyno		�µĶ��ļ�����֤����Կ��
	@param[in]		new_write_access_keyno		�µ�д�ļ�����֤����Կ��
	@param[in]		new_read_write_access_keyno	�µĶ�д�ļ�����֤����Կ��
	@param[in]		new_change_access_keyno		�µĸ�����Կ����֤����Կ��
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺						\n
								EINVAL	�������������										\n
								EIO		������оƬ����										\n
								ECOMM	����Ƭ����������ż�����CRCУ���					\n
								EPROTO	����Ƭ�������ݲ�����ISO14443�淶					\n
								EBADE	����Ƭ�������ݳ��ȴ���								\n
								ETIME	����ʱ�޷���										\n
								EACCES	����Ӧ���ڵĿ�Ƭ����mifare DESFire�����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Modify file attribute information.
	@param[in]		fd							opened device file number that mif_open function returns
	@param[in]		fileno						file number
	@param[in]		comm_set					transmission mode of the file, values are as follow:	\n
												0x00: plaintext transmission							\n
												0x03: ciphertext transmission							\n
												0x01: transmission with MAC
	@param[in]		old_change_access_keyno		old key number that is needed to be certificated when modifying key
	@param[in]		new_read_access_keyno		new key number that is need to be certificated when reading file
	@param[in]		new_write_access_keyno		new key number that is need to be certificated when writing file
	@param[in]		new_read_write_access_keyno	new key number that is need to be certification when reading and writing file
	@param[in]		new_change_access_keyno		new key number that is need to be certificated when modifying key
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:								\n
								EINVAL :input parameter error															\n
								EIO :read card chip error																\n
								ECOMM :Parity error or CRC check error of card returned data							\n
								EPROTO :Card doesn��t comply with ISO14443 standard										\n
								EBADE :error of length of card returned data											\n
								ETIME :timeout return																	\n
								ENODATA :card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value : other error code
 @endif
*/
int desfire_change_filesettings(int fd,
								uint8_t fileno, 
								uint8_t comm_set,
								uint8_t old_change_access_keyno,
								uint8_t new_read_access_keyno,
								uint8_t new_write_access_keyno,
								uint8_t new_read_write_access_keyno,
								uint8_t new_change_access_keyno);

/**
 @if Chinese
	@brief Desfireһ�������ļ���Ϣ
 @else
	@brief Desfire general data file information
 @endif
*/
typedef struct  
{	
	uint8_t FlgISOFileID; /*!< @if Chinese �Ƿ�����ISO/IEC 7816-4�ļ�ID��ʶ����0x00-���ã�0x01-���ã� @else whether ISO/IEC 7816-4 File IDentifiers enabled (0x00 - disabled, 0x01-enabled) @endif */
	uint8_t ISOFileID[2]; /*!< @if Chinese 2���ֽڵ�ISO/IEC 7816-4�ļ���ʶ�� @else 2bytes ISO/IEC 7816-4 File IDentifiers @endif */
	/** 
	 @if Chinese
		ͨ�����ã�									\n
		0x00 or 0x02	--- �򵥵�ͨ��				\n
		0x01			--- ͨ��MACing��֤�򵥵�ͨ��	\n
		0x03			--- ��ȫ���ܵ�ͨ��
	 @else
		Communication settings:										\n
		0x00 or 0x02	--- Plain communication						\n
		0x01			--- Plain communication secured by MACing	\n
		0x03			--- Fully enciphered communication
	 @endif
	*/
	uint8_t com_sett;
	uint8_t read_access_right_keyno;	/*!< @if Chinese �ڽ��ж����ʺͶ�д����֮ǰ��Ҫ��֤����Կ�� @else the reference number of the key which needs to be authenticated prior to Read Access and Read&Write Access @endif */
	uint8_t write_access_right_keyno;	/*!< @if Chinese ��д���ʺͶ�д����֮ǰ��Ҫ���������֤����Կ�� @else the reference number of the key which needs to be authentication prior to Write Access and Read&Write Access @endif */
	uint8_t read_and_write_access_right_keyno;	/*!< @if Chinese ��д����֮ǰ��Ҫ���������֤����Կ�� @else the reference number of the key which needs to be authentication prior to  Read&Write Access @endif */
	uint8_t change_access_right_keyno;	/*!< @if Chinese �ο���Կ�ţ�������������֤���ܸ����ļ��ķ���Ȩ�ޣ�����ÿ������Ȩ�����ӵ���Կ�� @else the reference number of the key,which is necessary to be authenticated with in order to change the access rights for the file and to link each access right to key numbers @endif */
	uint32_t file_size;	/*!< @if Chinese �û��ļ���С�����ֽ�Ϊ��λ��������file_type = 0x00��file_type = 0x01ʱ���� @else the user file size in bytes, only available when file_type = 0x00 or file_type = 0x01 @endif */
}desfire_std_backup_file_info;

/**
 @if Chinese
	@brief			����һ�������ļ�
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		fileno		�ļ���
	@param[in]		fileinfo	һ�������ļ���Ϣ
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Create general data file.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		fileno		file number
	@param[in]		fileinfo	general data file information
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_create_std_datafile(int fd,
									uint8_t fileno, 
									const desfire_std_backup_file_info *fileinfo);

/**
 @if Chinese
	@brief			�������������ļ�
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		fileno		�ļ���
	@param[in]		fileinfo	���������ļ���Ϣ
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺						\n
								EINVAL	�������������										\n
								EIO		������оƬ����										\n
								ECOMM	����Ƭ����������ż����� CRC У���					\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶					\n
								EBADE	����Ƭ�������ݳ��ȴ���								\n
								ETIME	����ʱ�޷���										\n
								EACCES	����Ӧ���ڵĿ�Ƭ����mifare DESFire�����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Create a backup data file.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		fileno		file number
	@param[in]		fileinfo	backup data file information
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_create_backup_datafile(int fd,
										uint8_t fileno, 
										const desfire_std_backup_file_info *fileinfo);

/**
 @if Chinese
	@brief Desfireֵ�ļ���Ϣ
 @else
	@brief Desfire value file information
 @endif
*/
typedef struct  
{
	/** 
	 @if Chinese
		ͨ�����ã�									\n
		0x00 or 0x02	--- �򵥵�ͨ��				\n
		0x01			--- ͨ��MACing��֤�򵥵�ͨ��	\n
		0x03			--- ��ȫ���ܵ�ͨ��
	 @else
		Communication settings:										\n
		0x00 or 0x02	--- Plain communication						\n
		0x01			--- Plain communication secured by MACing	\n
		0x03			--- Fully enciphered communication
	 @endif
	*/
	uint8_t com_sett;
	uint8_t read_access_right_keyno;	/*!< @if Chinese �ڽ��ж����ʺͶ�д����֮ǰ��Ҫ��֤����Կ�� @else the reference number of the key which needs to be authenticated prior to Read Access and Read&Write Access @endif */
	uint8_t write_access_right_keyno;	/*!< @if Chinese ��д���ʺͶ�д����֮ǰ��Ҫ���������֤����Կ�� @else the reference number of the key which needs to be authentication prior to Write Access and Read&Write Access @endif */
	uint8_t read_and_write_access_right_keyno;	/*!< @if Chinese ��д����֮ǰ��Ҫ���������֤����Կ�� @else the reference number of the key which needs to be authentication prior to  Read&Write Access @endif */
	uint8_t change_access_right_keyno;	/*!< @if Chinese �ο���Կ�ţ�������������֤���ܸ����ļ��ķ���Ȩ�ޣ�����ÿ������Ȩ�����ӵ���Կ�� @else the reference number of the key,which is necessary to be authenticated with in order to change the access rights for the file and to link each access right to key numbers @endif */
	
	uint32_t lower_limit;	/*!< @if Chinese ֵ�ļ������� @else lower limit of the value file @endif */
	uint32_t upper_limit;	/*!< @if Chinese ֵ�ļ������� @else upper limit of the value file @endif */
	uint32_t init_value;	/*!< @if Chinese ֵ�ļ��ĳ�ʼֵ @else the initial value of this value file @endif */
	uint8_t  limited_credit_enabled;	/*!< @if Chinese ������ļ�����ʹ��LimitedCredit���0x00��ʾ���ã�0x01��ʾ���ã� @else if the LimitedCredit command is allowed for this file (0x00 for disabled, 0x01 for enabled) @endif */
}desfire_value_file_info;

/**
 @if Chinese
	@brief			����ֵ�ļ�
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		fileno		�ļ���
	@param[in]		fileinfo	ֵ�ļ���Ϣ
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Create value file.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		fileno		file number
	@param[in]		fileinfo	value file information
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_create_valuefile(int fd, 
								uint8_t fileno, 
								const desfire_value_file_info *fileinfo);

/**
 @if Chinese
	@brief Desfire���Լ�¼�ļ���Ϣ
 @else
	@brief Desfire record file information
 @endif
*/
typedef struct  
{	
	uint8_t FlgISOFileID; /*!< @if Chinese �Ƿ�����ISO/IEC 7816-4�ļ�ID��ʶ����0x00-���ã�0x01-���ã� @else whether ISO/IEC 7816-4 File IDentifiers enabled (0x00 - disabled, 0x01-enabled) @endif */
	uint8_t ISOFileID[2]; /*!< @if Chinese 2���ֽڵ�ISO/IEC 7816-4�ļ���ʶ�� @else 2bytes ISO/IEC 7816-4 File IDentifiers @endif */
	/** 
	 @if Chinese
		ͨ�����ã�									\n
		0x00 or 0x02	--- �򵥵�ͨ��				\n
		0x01			--- ͨ��MACing��֤�򵥵�ͨ��	\n
		0x03			--- ��ȫ���ܵ�ͨ��
	 @else
		Communication settings:										\n
		0x00 or 0x02	--- Plain communication						\n
		0x01			--- Plain communication secured by MACing	\n
		0x03			--- Fully enciphered communication
	 @endif
	*/
	uint8_t com_sett;
	uint8_t read_access_right_keyno;			/*!< @if Chinese �ڽ��ж����ʺͶ�д����֮ǰ��Ҫ��֤����Կ�� @else the reference number of the key which needs to be authenticated prior to Read Access and Read&Write Access @endif */
	uint8_t write_access_right_keyno;			/*!< @if Chinese ��д���ʺͶ�д����֮ǰ��Ҫ���������֤����Կ�� @else the reference number of the key which needs to be authentication prior to Write Access and Read&Write Access @endif */
	uint8_t read_and_write_access_right_keyno;	/*!< @if Chinese ��д����֮ǰ��Ҫ���������֤����Կ�� @else the reference number of the key which needs to be authentication prior to  Read&Write Access @endif */
	uint8_t change_access_right_keyno;			/*!< @if Chinese �ο���Կ�ţ�������������֤���ܸ����ļ��ķ���Ȩ�ޣ�����ÿ������Ȩ�����ӵ���Կ�� @else the reference number of the key,which is necessary to be authenticated with in order to change the access rights for the file and to link each access right to key numbers @endif */

	uint32_t record_size;						/*!< @if Chinese һ����¼�Ĵ�С�����ļ�����ʱ���壩 @else the size of one single record (as deefined at file creation) @endif */
	uint32_t max_number_of_records;				/*!< @if Chinese ��¼�ļ��е�����¼�������ļ�����ʱ���壩 @else the maximum number of records within the record file (as defined at file creation) @endif */
	uint32_t FlgRndAcc;							/*!< @if Chinese �Ƿ�ָ�����д����ѡ���0x00-���ǣ�0x01-�ǣ� @else whether specifies Random write access option, (0x00 - not, 0x01 - yes) @endif */
	uint32_t rnd_acc;							/*!< @if Chinese �Ƿ��������д���ʣ���0x00-���ã�0x01-���ã� @else whether allowed Random write access, (0x00 - disabled, 0x01 - enabled) @endif */				
}desfire_record_file_info;

/**
 @if Chinese
	@brief			�������Լ�¼�ļ�
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		fileno		�ļ���
	@param[in]		fileinfo	���Լ�¼�ļ���Ϣ
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Create linear log file.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		fileno		file number
	@param[in]		fileinfo	linear log file information
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_create_linear_recordfile(int fd,
										uint8_t fileno,
										const desfire_record_file_info *fileinfo);

/**
 @if Chinese
	@brief			����ѭ����¼�ļ�
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		fileno		�ļ���
	@param[in]		fileinfo	ѭ����¼�ļ���Ϣ
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Create cycle log files.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		fileno		file number
	@param[in]		fileinfo	circular log file information
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_create_cyclic_recordfile(int fd,
										uint8_t fileno,
										const desfire_record_file_info *fileinfo);

/**
 @if Chinese
	@brief			ɾ��һ���ļ�
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		fileno		�ļ���
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Delete a file.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		fileno		file number
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_delete_file(int fd,uint8_t fileno);

/**
 @if Chinese
	@brief			��һ�������ļ����߱��������ļ��ж�ȡ����
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		fileno		�ļ���
	@param[in]		comm_set	ͨ�ŷ�ʽ��ȡֵ���£�	\n
								0x00�����Ĵ���			\n
								0x03�����ܴ���			\n
								0x01����MACУ�鴫��
	@param[in]		offset		��ȡ����ʼ��ַ
	@param[in]		len			ϣ����ȡ�ĳ���
	@param[out]		outlen		ʵ�ʶ�ȡ�������ݳ���
	@param[out]		dataout		ʵ�ʶ�ȡ��������
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺						\n
								EINVAL	�������������										\n
								EIO		������оƬ����										\n
								ECOMM	����Ƭ����������ż����� CRC У���					\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶					\n
								EBADE	����Ƭ�������ݳ��ȴ���								\n
								ETIME	����ʱ�޷���										\n
								EACCES	����Ӧ���ڵĿ�Ƭ����mifare DESFire�����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Read data from general data file or backup data file.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		fileno		file number
	@param[in]		comm_set	transmission mode, values are as follow:	\n
								0x00: plaintext transmission				\n
								0x03: ciphertext transmission				\n
								0x01: transmission with MAC verification
	@param[in]		offset		read start address
	@param[in]		len			expect length that will be read
	@param[out]		outlen		actual data length that have been read
	@param[out]		dataout		actual data that have been read
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_read_data(int fd,
						uint8_t fileno, 
						uint8_t comm_set, 	
						uint32_t offset, 
						uint32_t len, 
						uint32_t *outlen, 
						void *dataout);

/**
 @if Chinese
	@brief			��һ�������ļ����߱��������ļ��ж�ȡ����
	@param[in]		fd				mif_open�������������豸���ļ���
	@param[in]		fileno			�ļ���
	@param[in]		comm_set		ͨ�ŷ�ʽ��ȡֵ���£�	\n
									0x00�����Ĵ���			\n
									0x03�����ܴ���			\n
									0x01����MACУ�鴫��
	@param[in]		offset			��ȡ����ʼ��ַ
	@param[in]		len				ϣ����ȡ�ĳ���
	@param[out]		outlen			ʵ�ʶ�ȡ�������ݳ���
	@param[out]		dataout			ʵ�ʶ�ȡ��������
	@param[in]		dataout_size	dataout �Ļ����С
	@retval   	    0				�����ɹ�
	@retval   	    -1				����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺						\n
									EINVAL	�������������										\n
									EIO		������оƬ����										\n
									ECOMM	����Ƭ����������ż����� CRC У���					\n
									EPROTO	����Ƭ�������ݲ����� ISO14443 �淶					\n
									EBADE	����Ƭ�������ݳ��ȴ���								\n
									ETIME	����ʱ�޷���										\n
									EACCES	����Ӧ���ڵĿ�Ƭ����mifare DESFire�����߿�Ƭδ����	\n
									ENOSPC	��dataout�ռ�С�ڽ������ݴ�С						\n
									����ֵ	������������
 @else
	@brief			Read data from general data file or backup data file.
	@param[in]		fd				opened device file number that mif_open function returns
	@param[in]		fileno			file number
	@param[in]		comm_set		transmission mode, values are as follow:	\n
									0x00: plaintext transmission				\n
									0x03: ciphertext transmission				\n
									0x01: transmission with MAC verification
	@param[in]		offset			read start address
	@param[in]		len				expect length that will be read
	@param[out]		outlen			actual data length that have been read
	@param[out]		dataout			actual data that have been read
	@param[in]		dataout_size	the size of dataout buffer
	@retval   	    0				operate success
	@retval   	    -1				operate failure, please get the actual error code by errno:									\n
									EINVAL		: input parameter error															\n
									EIO			: read card chip error															\n
									ECOMM		: Parity error or CRC check error of card returned data							\n
									EPROTO		: Card doesn��t comply with ISO14443 standard									\n
									EBADE		: error of length of card returned data											\n
									ETIME		: timeout return																\n
									ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
									Other value	: other error code
 @endif
*/
int desfire_read_data_safe(int fd,
						uint8_t fileno, 
						uint8_t comm_set, 							
						uint32_t offset, 
						uint32_t len, 
						uint32_t *outlen, 
						void *dataout, 
						uint32_t dataout_size);

/**
 @if Chinese
	@brief			��һ�������ļ����߱��������ļ��ж�ȡ����
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		fileno		�ļ���
	@param[in]		comm_set	ͨ�ŷ�ʽ��ȡֵ���£�	\n
								0x00�����Ĵ���			\n
								0x03�����ܴ���			\n
								0x01����MACУ�鴫��
	@param[in]		offset		д�����ʼ��ַ
	@param[in]		len			Ҫд������ݳ���
	@param[out]		datain		Ҫд�������
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺						\n
								EINVAL	�������������										\n
								EIO		������оƬ����										\n
								ECOMM	����Ƭ����������ż����� CRC У���					\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶					\n
								EBADE	����Ƭ�������ݳ��ȴ���								\n
								ETIME	����ʱ�޷���										\n
								EACCES	����Ӧ���ڵĿ�Ƭ����mifare DESFire�����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Write data into general data file or into backup data file.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		fileno		file number
	@param[in]		comm_set	transmission mode, values are as follow:	\n
								0x00: plaintext transmission				\n
								0x03: ciphertext transmission				\n
								0x01: transmission with MAC verification
	@param[in]		offset		start address that will be written
	@param[in]		len			data length that will be written
	@param[out]		datain		data that will be written
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_write_data(int fd, 
						uint8_t fileno, 
						uint8_t comm_set, 
						uint32_t offset, 
						uint32_t len, 
						const void *datain);

/**
 @if Chinese
	@brief			��ȡָ��ֵ�ļ���ֵ��С
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		fileno		�ļ���
	@param[in]		comm_set	ͨ�ŷ�ʽ��ȡֵ���£�	\n
								0x00�����Ĵ���			\n
								0x03�����ܴ���			\n
								0x01����MACУ�鴫��
	@param[out]		value		��ֵ�ļ���ֵ��С
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Get the value of the specified file.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		fileno		file number
	@param[in]		comm_set	transmission mode, values are as follow:	\n
								0x00: plaintext transmission				\n
								0x03: ciphertext transmission				\n
								0x01: transmission with MAC verification
	@param[out]		value		value size of the value file
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_get_value(int fd,uint8_t fileno,uint8_t comm_set,uint32_t *value);

/**
 @if Chinese
	@brief			��ȡָ��ֵ�ļ���ֵ��С
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		fileno		�ļ���
	@param[in]		comm_set	ͨ�ŷ�ʽ��ȡֵ���£�	\n
								0x00�����Ĵ���			\n
								0x03�����ܴ���			\n
								0x01����MACУ�鴫��
	@param[in]		value		��ֵ��С
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Recharge operation.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		fileno		file number
	@param[in]		comm_set	transmission mode, values are as follow:	\n
								0x00: plaintext transmission				\n
								0x03: ciphertext transmission				\n
								0x01: transmission with MAC verification
	@param[in]		value		size of recharge
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_credit(int fd,uint8_t fileno,uint8_t comm_set,uint32_t value);

/**
 @if Chinese
	@brief			��ֵ����
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		fileno		�ļ���
	@param[in]		comm_set	ͨ�ŷ�ʽ��ȡֵ���£�	\n
								0x00�����Ĵ���			\n
								0x03�����ܴ���			\n
								0x01����MACУ�鴫��
	@param[in]		value		��ֵ��С
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Deduct value operation.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		fileno		file number
	@param[in]		comm_set	transmission mode, values are as follow:	\n
								0x00: plaintext transmission				\n
								0x03: ciphertext transmission				\n
								0x01: transmission with MAC verification
	@param[in]		value		value to deduct
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_debit(int fd,uint8_t fileno,uint8_t comm_set,uint32_t value);

/**
 @if Chinese
	@brief			���޳�ֵ����
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		fileno		�ļ���
	@param[in]		comm_set	ͨ�ŷ�ʽ��ȡֵ���£�	\n
								0x00�����Ĵ���			\n
								0x03�����ܴ���			\n
								0x01����MACУ�鴫��
	@param[in]		value		��ֵ��С
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Limited recharge operation.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		fileno		file number
	@param[in]		comm_set	transmission mode, values are as follow:	\n
								0x00: plaintext transmission				\n
								0x03: ciphertext transmission				\n
								0x01: transmission with MAC verification
	@param[in]		value		size fo recharge
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_limited_credit(int fd,uint8_t fileno,uint8_t comm_set,uint32_t value);

/**
 @if Chinese
	@brief			���޳�ֵ����
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		fileno		�ļ���
	@param[in]		comm_set	ͨ�ŷ�ʽ��ȡֵ���£�	\n
								0x00�����Ĵ���			\n
								0x03�����ܴ���			\n
								0x01����MACУ�鴫��
	@param[in]		offset		��ǰ��¼�ڵ���ʼ��ַ
	@param[in]		len			Ҫд������ݳ���
	@param[in]		info		Ҫд��ļ�¼��Ϣ
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Write log operation.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		fileno		file number
	@param[in]		comm_set	transmission mode, values are as follow:	\n
								0x00: plaintext transmission				\n
								0x03: ciphertext transmission				\n
								0x01: transmission with MAC verification
	@param[in]		offset		start address of current log
	@param[in]		len			length of data that will be written
	@param[in]		info		log information that will be written
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_write_record(int fd,
							uint8_t fileno, 
							uint8_t comm_set, 
							int offset, 
							int len, 
							const void *info);

/**
 @if Chinese
	@brief			����¼����
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		fileno		�ļ���
	@param[in]		comm_set	ͨ�ŷ�ʽ��ȡֵ���£�	\n
								0x00�����Ĵ���			\n
								0x03�����ܴ���			\n
								0x01����MACУ�鴫��
	@param[in]		recordsize	��¼����
	@param[in]		first		Ҫ��ȡ�ĵ�һ����¼��
	@param[in]		num			Ҫ��ȡ�ļ�¼��
	@param[out]		outlen		�������������ܳ���
	@param[out]		info		�������ļ�¼��Ϣ
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Read log operation.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		fileno		file number
	@param[in]		comm_set	transmission mode, values are as follow:	\n
								0x00: plaintext transmission				\n
								0x03: ciphertext transmission				\n
								0x01: transmission with MAC verification
	@param[in]		recordsize	length of log
	@param[in]		first		first log number that will be read
	@param[in]		num			count of logs that will be read
	@param[out]		outlen		total length of data that have been read
	@param[out]		info		log information that have been read
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_read_records(int fd,
							uint8_t fileno, 
							uint8_t comm_set,
							uint32_t recordsize,
							int first, 
							int num, 
							uint32_t *outlen, 
							void *info);

/**
 @if Chinese
	@brief			����¼����
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		fileno		�ļ���
	@param[in]		comm_set	ͨ�ŷ�ʽ��ȡֵ���£�	\n
								0x00�����Ĵ���			\n
								0x03�����ܴ���			\n
								0x01����MACУ�鴫��
	@param[in]		recordsize	��¼����
	@param[in]		first		Ҫ��ȡ�ĵ�һ����¼��
	@param[in]		num			Ҫ��ȡ�ļ�¼��
	@param[out]		outlen		�������������ܳ���
	@param[out]		info		�������ļ�¼��Ϣ
	@param[in]		info_size	info �Ļ����С
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Read log operation.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		fileno		file number
	@param[in]		comm_set	transmission mode, values are as follow:	\n
								0x00: plaintext transmission				\n
								0x03: ciphertext transmission				\n
								0x01: transmission with MAC verification
	@param[in]		recordsize	length of log
	@param[in]		first		first log number that will be read
	@param[in]		num			count of logs that will be read
	@param[out]		outlen		total length of data that have been read
	@param[out]		info		log information that have been read
	@param[in]		info_size	the size of info buffer
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_read_records_safe(int fd,
							uint8_t fileno, 
							uint8_t comm_set,
							uint32_t recordsize,
							int first, 
							int num, 
							uint32_t *outlen, 
							void *info, 
							uint32_t info_size);

/**
 @if Chinese
	@brief			�����¼�ļ��ڵ�����
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		fileno		�ļ���
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Clear all record files.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		fileno		file number
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_clear_recordfile(int fd,uint8_t fileno);

/**
 @if Chinese
	@brief			ȷ��֮ǰ�Ե�ǰӦ���ڸ����ļ�����ز���������
	@param[in]		fd			mif_open�������������豸���ļ���
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Confirm and save all related operations on current application��s files.
	@param[in]		fd			opened device file number that mif_open function returns
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_commit_transaction(int fd);

/**
 @if Chinese
	@brief			����֮ǰ�ӵ�ǰӦ���ڸ����ļ�����ز���
	@param[in]		fd			mif_open�������������豸���ļ���
	@retval   	    0			�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺							\n
								EINVAL	�������������											\n
								EIO		������оƬ����											\n
								ECOMM	����Ƭ����������ż����� CRC У���						\n
								EPROTO	����Ƭ�������ݲ����� ISO14443 �淶						\n
								EBADE	����Ƭ�������ݳ��ȴ���									\n
								ETIME	����ʱ�޷���											\n
								EACCES	����Ӧ���ڵĿ�Ƭ���� mifare DESFire �����߿�Ƭδ����	\n
								����ֵ	������������
 @else
	@brief			Undo related operations on current application��s files.
	@param[in]		fd			opened device file number that mif_open function returns
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn��t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_abort_transaction(int fd);
#ifdef __cplusplus
  }
#endif /* __cplusplus */

#endif /* DESFIRE_H_ */

/** @} */
