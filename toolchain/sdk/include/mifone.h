/*!
 @if Chinese
 	@file        mifone.h
	@author      neal
	@date        2010-10-14
	@version     1.0.0
	@note        ��ģ���������� <strong>mifare one</strong> ��صĽӿ�
	@remarks        �޸ļ�¼:
	����          | ����            | ����
	------------- | --------------- | ----
	2010-10-14    | neal            | Create file
 @else
	@file        mifone.h
	@author      neal
	@date        2010-10-14
	@version     1.0.0
	@note        This module is used to describe <strong>mifare one</strong> interfaces module
	@remarks        Change History:
	Date          | Author          | Desc
	------------- | --------------- | ----
	2010-10-14    | neal            | Create file
 @endif
*/

/*!
 @if Chinese
 	@brief       ��ģ���������� mifone ģ����صĽӿ�
	
	Դ�ļ���<a href="mifone_8h_source.html">mifone.h</a>
 @else
	@brief       This module is used to describe the relevant interface of the mifone module
    
	Source file: <a href="mifone_8h_source.html">mifone.h</a>
 @endif
 @defgroup mifone mifone
 @ingroup G_NFC
 @{
*/

/*
 * mifone.h
 *
 *  Created on: Oct 14, 2010
 *      Author: neal
 */

#ifndef MIFONE_H_
#define MIFONE_H_

#ifdef __cplusplus
  extern "C" {
#endif /* __cplusplus */

/**
 @if Chinese
	@brief			����Ӧ�����Ƿ����mifare one���������򼤻�
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		mode		��ѯģʽ��ȡֵ���£�
								0������ѯ���д���IDLE״̬�Ŀ�Ƭ
								1����ѯ���д���IDLE����HALT״̬�Ŀ�Ƭ
	@param[out]		uid			��Ƭ���ص�5�ֽ�UID��Ϣ��4�ֽ�UID+BCC
	@param[out]		cardtype	���ص�mifare one��Ƭ���ͣ�����ȡֵ���£�		\n
								MIF_M1_S50	��mifare one S50 ��					\n
								MIF_M1_S70	��mifare one S70 ��					\n
								MIF_PRO_S50	������T=CLЭ���S50Э���TypeA��	\n
								MIF_PRO_S70	������T=CLЭ���S70Э���TypeA��
	@retval   	    0			Ѱ�������ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺			\n
								ENODATA ����Ӧ������ mifare one ��				\n
								EMULTIHOP ����Ӧ�����ж࿨						\n
								EPROTO ����Ƭ�������ݲ����� ISO14443 Э��		\n
								EBADE ����Ƭ���ص����ݳ��Ȳ���ȷ				\n
								EINVAL ����������								\n
								ECOMM ����Ƭ���ص�������ż����� CRC У���		\n
								EIO ������оƬ����								\n
								ETIME ����ʱ����								\n
								����ֵ ������������
 @else
	@brief			Poll if there is mifare one card in inductive zone, if yes, active it.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		mode		polling mode , values are as follow:
								0: just polling card of IDLE state
								1: polling card of IDLE state and HALT state
	@param[out]		uid			5 bytes UID information that card returns, 4 bytes UID+BCC
	@param[out]		cardtype	returned mifare one card type, may have the value below:						\n
								MIF_M1_S50	: mifare one S50 card												\n
								MIF_M1_S70	: mifare one S70 card												\n
								MIF_PRO_S50	: TypeA card that compatible with T=CL protocol and S50 protocol	\n
								MIF_PRO_S70	: TypeA card that compatible with T=CL protocol and S70 protocol
	@retval   	    0			find card success
	@retval   	    -1			operate failure, please get the actual error code by errno:			\n
								ENODATA		: no card in inductive card								\n
								EMULTIHOP	: exist multiple cards in inductive zone				\n
								EPROTO		: Card doesn��t comply with ISO14443 standard			\n
								EBADE		: error of length of card returned data					\n
								EINVAL		: parameter error										\n
								ECOMM		: Parity error or CRC check error of card returned data	\n
								EIO			: read card chip error									\n
								ETIME 		: timeout return other value : other error code
 @endif
*/
int mifare_one_poll(int fd, uint8_t mode, void *uid , uint8_t *cardtype);

/**
 @if Chinese
	@brief			��λ��Ӧ���ڵ�mifare one��
	@param[in]		fd			mif_open�������������豸���ļ���
	@retval   	    0			��λ�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺		\n
								EIO		������оƬ����						\n
								����ֵ	������������
 @else
	@brief			Reset mifare one card in inductive zone.
	@param[in]		fd			opened device file number that mif_open function returns
	@retval   	    0			reset OK
	@retval   	    -1			operate failure, please get the actual error code by errno:	\n
								EIO			: read card chip error							\n
								Other value	: other error code
 @endif
*/
int mifare_one_halt(int fd);

/**
 @if Chinese
	@brief			��ȡmifare ultralight����ĳҳ���ݣ�һ�ζ�ȡ4��ҳ����
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		blockno		Ҫ��֤�����ݿ�ţ�����S50����ȡֵ��ΧΪ0~63������S70����ȡֵ��ΧΪ0~255
	@param[in]		keytype		Ҫ��֤����Կ���ͣ�ȡֵ���£�				\n
								'A'����֤ A ��Կ							\n
								'B'����֤ B ��Կ
	@param[in]		key			6�ֽڳ��ȵ���Կ��Ϣ
	@param[in]		uid			4�ֽڵ�UID��Ϣ
	@retval   	    0			������֤�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺		\n
								EACCES	����Ӧ���ڲ���mifare one��			\n
								EPERM	����֤ʧ��							\n
								EPROTO	����Ƭ�������ݲ�����mifare oneЭ��	\n
								EINVAL	����������							\n
								ECOMM	����Ƭ���ص�������ż�����CRCУ���	\n
								EIO		������оƬ����						\n
								ETIME	����ʱ����							\n
								����ֵ	������������
 @else
	@brief			Password authentication about mifare one card��s a data block.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		blockno		number of data block that will be authenticated, for S50 card ,value scope is 0~63, for S70 card ,value scope is 0~255
	@param[in]		keytype		certificated key type, values are as follow:	\n
								'A': certificate A key							\n
								'B': certificate B key
	@param[in]		key			6 bytes key information
	@param[in]		uid			4 bytes UID information
	@retval   	    0			password authentication success
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								EACCES		: is not a mifare one card in inductive zone			\n
								EPERM		: authentication failure								\n
								EPROTO		: Card doesn��t comply with mifare one protocol			\n
								EINVAL		: parameter error										\n
								ECOMM		: Parity error or CRC check error of card returned data	\n
								EIO			: read card chip error									\n
								ETIME		: timeout return										\n
								Other value	: other error code
 @endif
*/
int mifare_one_authenticate(int fd, uint8_t blockno, uint8_t keytype,const void *key, const void *uid);

/**
 @if Chinese
	@brief			��ȡmifare one����ĳ�����ݿ�����
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		blockno		Ҫ��ȡ�����ݿ�ţ�����S50����ȡֵ��ΧΪ 0~63������S70����ȡֵ��ΧΪ0~255
	@param[out]		blockdata	�����������ݿ����ݣ�16�ֽ�
	@retval   	    0			�����ݿ�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺			\n
								EACCES	����Ӧ���ڲ��� mifare one ��			\n
								EPERM	����֤ʧ��								\n
								EPROTO	����Ƭ�������ݲ����� mifare one Э��	\n
								EINVAL	����������								\n
								ECOMM	����Ƭ���ص�������ż����� CRC У���	\n
								EIO		������оƬ����							\n
								ETIME	����ʱ����								\n
								EBADE	����Ƭ���ص����ݳ��ȴ���				\n
								����ֵ	������������
 @else
	@brief			Read a data block content of mifare one card.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		blockno		number of data block that will be read, for S50 card ,value scope is 0~63, for S70 card ,value scope is 0~255
	@param[out]		blockdata	read content of data block,16 bytes
	@retval   	    0			read data block success
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								EACCES		: is not a mifare one card in inductive zone			\n
								EPERM		: authentication failure								\n
								EPROTO		: Card doesn��t comply with mifare one protocol			\n
								EINVAL		: parameter error                                       \n
								ECOMM		: Parity error or CRC check error of card returned data \n
								EIO			: read card chip error                                  \n
								ETIME		: timeout return                                        \n
								EBADE		: length of data that card return ed is error           \n
								other value	: other error code
 @endif
*/
int mifare_one_read_block(int fd, uint8_t blockno, void *blockdata);

/**
 @if Chinese
	@brief			����mifare one����ĳ�����ݿ�����
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		blockno		Ҫ��ȡ�����ݿ�š�����S50����ȡֵ��ΧΪ0~63������S70����ȡֵ��ΧΪ0~255
	@param[in]		blockdata	Ҫд������ݿ����ݣ�16�ֽ�
	@retval   	    0			д���ݿ�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺		\n
								EACCES	����Ӧ���ڲ���mifare one��			\n
								EPERM	����֤ʧ��							\n
								EPROTO	����Ƭ�������ݲ�����mifare oneЭ��	\n
								EINVAL	����������							\n
								ECOMM	����Ƭ���ص�������ż�����CRCУ���	\n
								EIO		������оƬ����						\n
								ETIME	����ʱ����							\n
								EBADE	����Ƭ���ص����ݳ��ȴ���			\n
								����ֵ	������������
 @else
	@brief			Modify content of a data block of mifare one card.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		blockno		number of data block that will be read, for S50 card ,value scope is 0~63, for S70 card ,value scope is 0~255
	@param[in]		blockdata	content of data block that will be written, 16 bytes
	@retval   	    0			write data block success
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								EACCES		: is not a mifare one card in inductive zone			\n
								EPERM		: authentication failure								\n
								EPROTO		: Card doesn��t comply with mifare one protocol			\n
								EINVAL		: parameter error										\n
								ECOMM		: Parity error or CRC check error of card returned data	\n
								EIO			: read card chip error									\n
								ETIME		: timeout return										\n
								EBADE		: length of data that card return ed is error			\n
								Other value	: other error code
 @endif
*/
int mifare_one_write_block(int fd, uint8_t blockno, const void *blockdata);

/**
 @if Chinese
	@brief			��mifare one����ĳ�����ݿ����ó���ֵ�飬������ֵ
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		blockno		Ҫ��ȡ�����ݿ�š�����S50����ȡֵ��ΧΪ0~63������S70����ȡֵ��ΧΪ0~255
	@param[in]		value		Ҫ����ĳ�ʼֵ
	@retval   	    0			��ʼ����ֵ������ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺		\n
								EACCES	����Ӧ���ڲ���mifare one��			\n
								EPERM	����֤ʧ��							\n
								EPROTO	����Ƭ�������ݲ�����mifare oneЭ��	\n
								EINVAL	����������							\n
								ECOMM	����Ƭ���ص�������ż�����CRCУ���	\n
								EIO		������оƬ����						\n
								ETIME	����ʱ����							\n
								EBADE	����Ƭ���ص����ݳ��ȴ���			\n
								����ֵ	������������
 @else
	@brief			Set a data block of mifare one card to value block,and fu initial.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		blockno		number of data block that will be read, for S50 card ,value scope is 0~63, for S70 card ,value scope is 0~255
	@param[in]		value		initial value that will be filled in
	@retval   	    0			initialize value block success
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								EACCES		: is not a mifare one card in inductive zone			\n
								EPERM		: authentication failure								\n
								EPROTO		: Card doesn��t comply with mifare one protocol			\n
								EINVAL		: parameter error										\n
								ECOMM		: Parity error or CRC check error of card returned data	\n
								EIO			: read card chip error									\n
								ETIME		: timeout return										\n
								EBADE		: length of data that card return ed is error			\n
								Other value	: other error code
 @endif
*/
int mifare_one_set_value(int fd, uint8_t blockno, uint32_t value);

/**
 @if Chinese
	@brief			��ֵ����ֵ����
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		blockno		Ҫ��ȡ�����ݿ�š�����S50����ȡֵ��ΧΪ0~63������S70����ȡֵ��ΧΪ0~255
	@param[in]		value		Ҫ���ӵ�ֵ
	@retval   	    0			��ֵ�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺			\n
								EACCES	����Ӧ���ڲ��� mifare one ��			\n
								EPERM	����֤ʧ��								\n
								EPROTO	����Ƭ�������ݲ����� mifare one Э��	\n
								EINVAL	����������								\n
								ECOMM	����Ƭ���ص�������ż����� CRC У���	\n
								EIO		������оƬ����							\n
								ETIME	����ʱ����								\n
								EBADE	����Ƭ���ص����ݳ��ȴ���				\n
								ENOSYS	���ÿ鲻����ֵ��						\n
								����ֵ	������������
 @else
	@brief			Value block value-added operation.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		blockno		number of data block that will be read, for S50 card ,value scope is 0~63, for S70 card ,value scope is 0~255
	@param[in]		value		value that will be added
	@retval   	    0			value increment operation success
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								EACCES		: is not a mifare one card in inductive zone			\n
								EPERM		: authentication failure								\n
								EPROTO 		: Card doesn��t comply with mifare one protocol			\n
								EINVAL 		: parameter error										\n
								ECOMM		: Parity error or CRC check error of card returned data	\n
								EIO			: read card chip error									\n
								ETIME		: timeout return										\n
								EBADE		: length of data that card return ed is error			\n
								ENOSYS		: the block is not a value block						\n
								Other value : other error code
 @endif
*/
int mifare_one_increment(int fd, uint8_t blockno, uint32_t value);

/**
 @if Chinese
	@brief			��ֵ���ֵ����
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		blockno		Ҫ��ȡ�����ݿ�š�����S50����ȡֵ��ΧΪ0~63������S70����ȡֵ��ΧΪ0~255
	@param[in]		value		Ҫ������ֵ
	@retval   	    0			��ֵ�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺			\n
								EACCES	����Ӧ���ڲ��� mifare one ��			\n
								EPERM	����֤ʧ��								\n
								EPROTO	����Ƭ�������ݲ����� mifare one Э��	\n
								EINVAL	����������								\n
								ECOMM	����Ƭ���ص�������ż����� CRC У���	\n
								EIO		������оƬ����							\n
								ETIME	����ʱ����								\n
								EBADE	����Ƭ���ص����ݳ��ȴ���				\n
								ENOSYS	���ÿ鲻����ֵ��						\n
								����ֵ	������������
 @else
	@brief			Value block decrement operation.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		blockno		number of data block that will be read, for S50 card ,value scope is 0~63, for S70 card ,value scope is 0~255
	@param[in]		value		value that will be impaired
	@retval   	    0			decrement operation success
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								EACCES		: is not a mifare one card in inductive zone			\n
								EPERM		: authentication failure								\n
								EPROTO		: Card doesn��t comply with mifare one protocol			\n
								EINVAL		: parameter error										\n
								ECOMM		: Parity error or CRC check error of card returned data	\n
								EIO			: read card chip error									\n
								ETIME		: timeout return										\n
								EBADE		: length of data that card return ed is error			\n
								ENOSYS		: the block is not a value block						\n
								Other value	: other error code
 @endif
*/
int mifare_one_decrement(int fd, uint8_t blockno, uint32_t value);

/**
 @if Chinese
	@brief			��ֵ��ת�����
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		blockno		Ҫ��ȡ�����ݿ�š�����S50����ȡֵ��ΧΪ0~63������S70����ȡֵ��ΧΪ0~255
	@retval   	    0			ת������ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺		\n
								EACCES	����Ӧ���ڲ���mifare one��			\n
								EPERM	����֤ʧ��							\n
								EPROTO	����Ƭ�������ݲ�����mifare oneЭ��	\n
								EINVAL	����������							\n
								ECOMM	����Ƭ���ص�������ż�����CRCУ���	\n
								EIO		������оƬ����						\n
								ETIME	����ʱ����							\n
								EBADE	����Ƭ���ص����ݳ��ȴ���			\n
								ENOSYS	���ÿ鲻����ֵ��					\n
								����ֵ	������������
 @else
	@brief			Restore value in the designated block.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		blockno		number of data block that will be read, for S50 card ,value scope is 0~63, for S70 card ,value scope is 0~255
	@retval   	    0			restore operation success
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								EACCES		: is not a mifare one card in inductive zone			\n
								EPERM		: authentication failure								\n
								EPROTO		: Card doesn��t comply with mifare one protocol			\n
								EINVAL		: parameter error										\n
								ECOMM		: Parity error or CRC check error of card returned data	\n
								EIO			: read card chip error									\n
								ETIME 		: timeout return										\n
								EBADE		: length of data that card return ed is error			\n
								ENOSYS		: the block is not a value block						\n
								Other value	: other error code
 @endif
*/
int mifare_one_restore(int fd, uint8_t blockno);

/**
 @if Chinese
	@brief			������ֵ��������
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		blockno		Ҫ��ȡ�����ݿ�š�����S50����ȡֵ��ΧΪ0~63������S70����ȡֵ��ΧΪ0~255
	@retval   	    0			������ֵ���������ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺		\n
								EACCES	����Ӧ���ڲ���mifare one��			\n
								EPERM	����֤ʧ��							\n
								EPROTO	����Ƭ�������ݲ�����mifare oneЭ��	\n
								EINVAL	����������							\n
								ECOMM	����Ƭ���ص�������ż�����CRCУ���	\n
								EIO		������оƬ����						\n
								ETIME	����ʱ����							\n
								EBADE	����Ƭ���ص����ݳ��ȴ���			\n
								ENOSYS	���ÿ鲻����ֵ��					\n
								����ֵ	������������
 @else
	@brief			Save the result of value block operation.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		blockno		number of data block that will be read, for S50 card ,value scope is 0~63, for S70 card ,value scope is 0~255
	@retval   	    0			save the result of value block operation success
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								EACCES		: is not a mifare one card in inductive zone			\n
								EPERM		: authentication failure								\n
								EPROTO		: Card doesn��t comply with mifare one protocol			\n
								EINVAL		: parameter error										\n
								ECOMM		: Parity error or CRC check error of card returned data	\n
								EIO			: read card chip error									\n
								ETIME		: timeout return										\n
								EBADE		: length of data that card return ed is error			\n
								ENOSYS		: the block is not a value block						\n
								Other value	: other error code
 @endif
*/
int mifare_one_transfer(int fd, uint8_t blockno);

/**
 @if Chinese
	@brief			��ȡ��ֵ���ֵ��С
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		blockno		Ҫ��ȡ�����ݿ�š�����S50����ȡֵ��ΧΪ0~63������S70����ȡֵ��ΧΪ0~255
	@param[out]		value		��Ƭ���ص�ֵ����
	@retval   	    0			������ֵ���������ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺			\n
								EACCES	����Ӧ���ڲ��� mifare one ��			\n
								EPERM	����֤ʧ��								\n
								EPROTO	����Ƭ�������ݲ����� mifare one Э��	\n
								EINVAL	����������								\n
								ECOMM	����Ƭ���ص�������ż����� CRC У���	\n
								EIO		������оƬ����							\n
								ETIME	����ʱ����								\n
								EBADE	����Ƭ���ص����ݳ��ȴ���				\n
								ENOSYS	���ÿ鲻����ֵ��						\n
								����ֵ	������������
 @else
	@brief			Get the value of the designated block.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		blockno		number of data block that will be read, for S50 card ,value scope is 0~63, for S70 card ,value scope is 0~255
	@param[out]		value		value content that card returns
	@retval   	    0			get the value of value block operation success
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								EACCES		: is not a mifare one card in inductive zone			\n
								EPERM		: authentication failure								\n
								EPROTO		: Card doesn��t comply with mifare one protocol			\n
								EINVAL		: parameter error										\n
								ECOMM		: Parity error or CRC check error of card returned data	\n
								EIO			: read card chip error									\n
								ETIME		: timeout return										\n
								EBADE		: length of data that card return ed is error			\n
								ENOSYS		: the block is not a value block						\n
								Other value : other error code
 @endif
*/
int mifare_one_get_value(int fd, uint8_t blockno, uint32_t *value);
#ifdef __cplusplus
  }
#endif /* __cplusplus */

#endif /* MIFONE_H_ */
/** @} */