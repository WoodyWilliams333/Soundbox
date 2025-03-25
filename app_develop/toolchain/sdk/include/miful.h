/*!
 @if Chinese
 	@file        miful.h
	@author      neal
	@date        2010-10-14
	@version     1.0.0
	@note        ��ģ���������� <strong>mifare ultralight</strong> ��صĽӿ�	
	@remarks        �޸ļ�¼:
	����          | ����            | ����
	------------- | --------------- | ----
	2010-10-14    | neal            | Create file
 @else
	@file        miful.h
	@author      neal
	@date        2010-10-14
	@version     1.0.0
	@note        This module is used to describe <strong>mifare ultralight</strong> interfaces module
	@remarks        Change History:
	Date          | Author          | Desc
	------------- | --------------- | ----
	2010-10-14    | neal            | Create file
 @endif
*/

/*!
 @if Chinese
 	@brief       ��ģ����������mifulģ����صĽӿ�
	
	Դ�ļ���<a href="miful_8h_source.html">miful.h</a>
 @else
	@brief       This module is used to describe the relevant interface of the miful module

	Source file: <a href="miful_8h_source.html">miful.h</a>
 @endif
 @defgroup miful miful
 @ingroup G_NFC
 @{
*/

/*
 * miful.h
 *
 *  Created on: Oct 14, 2010
 *      Author: neal
 */

#ifndef MIFUL_H_
#define MIFUL_H_

#ifdef __cplusplus
  extern "C" {
#endif /* __cplusplus */

/**
 @if Chinese
	@brief			����Ӧ�����Ƿ����mifare ultralight���������򼤻�
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		mode		��ѯģʽ��ȡֵ���£�
								0������ѯ���д���IDLE״̬�Ŀ�Ƭ
								1����ѯ���д���IDLE����HALT״̬�Ŀ�Ƭ
	@param[out]		uid			��Ƭ���ص�7�ֽ�UID��Ϣ
	@retval   	    0			Ѱ�������ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺			\n
								ENODATA		����Ӧ������mifare ultralight��		\n
								EMULTIHOP	����Ӧ�����ж࿨					\n
								EPROTO		����Ƭ�������ݲ�����ISO14443Э��	\n
								EBADE		����Ƭ���ص����ݳ��Ȳ���ȷ			\n
								EINVAL		����������							\n
								ECOMM		����Ƭ���ص�������ż�����CRCУ���	\n
								EIO			������оƬ����						\n
								ETIME		����ʱ����							\n
								����ֵ		������������
 @else
	@brief			Poll if there is mifare ultralight card in inductive zone, if there is, active it.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		mode		Polling mode, values are as follow:
								0: just polling card of IDLE state
								1: polling card of IDLE state and HALT state
	@param[out]		uid			7 bytes UID information that card returns
	@retval   	    0			find card successfully
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								ENODATA		: is not a mifare ultralight card in inductive zone		\n
								EMULTIHOP	: exist multiple cards in inductive zone				\n
								EPROTO		: card doesn��t comply with ISO14443 standard			\n
								EBADE		: error of length of card returned data					\n
								EINVAL		: parameter error										\n
								ECOMM		: parity error or CRC check error of card returned data	\n
								EIO			: read card chip error									\n
								ETIME		: timeout return										\n
								Other value	: other error code
 @endif
*/
int mifare_ultralight_poll(int fd, uint8_t mode, void *uid);

/**
 @if Chinese
	@brief			��λ��Ӧ���ڵ�mifare ultralight��
	@param[in]		fd			mif_open�������������豸���ļ���
	@retval   	    0			��λ�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺	\n
								EIO		������оƬ����					\n
								����ֵ	������������
 @else
	@brief			Halt mifare ultralight card in inductive zone.
	@param[in]		fd			opened device file number that mif_open function returns
	@retval   	    0			reset success
	@retval   	    -1			operate failure, please get the actual error code by errno:	\n
								EIO			: read card chip error							\n
								Other value	: other error code
 @endif
*/
int mifare_ultralight_halt(int fd);

/**
 @if Chinese
	@brief			��ȡmifare ultralight����ĳҳ���ݣ�һ�ζ�ȡ4��ҳ����
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		page		Ҫ��ȡ����ʼҳ�ţ�0~15
	@param[out]		data		��������ҳ���ݣ�16�ֽ�
	@retval   	    0			�����ݿ�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺		\n
								EACCES	����Ӧ���ڲ���mifare ultralight��	\n
								EINVAL	����������							\n
								ECOMM	����Ƭ���ص�������ż�����CRCУ���	\n
								EIO		������оƬ����						\n
								ETIME	����ʱ����							\n
								EBADE	����Ƭ���ص����ݳ��ȴ���			\n
								����ֵ	������������
 @else
	@brief			Read content of a page of mifare ultralight card, 4 pages at one time.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		page		start page number that will be read, 0~15
	@param[out]		data		page content that be read, 16 bytes
	@retval   	    0			read data block successfully
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								ENODATA		:is not a mifare ultralight card in inductive zone		\n
								EINVAL		:parameter error										\n
								ECOMM		:Parity error or CRC check error of card returned data	\n
								EIO			:read card chip error									\n
								ETIME		:timeout return											\n
								EBADE		:error of length of card returned data					\n
								other value	: other error code
 @endif
*/
int mifare_ultralight_read_page(int fd,uint8_t page,void *data);

/**
 @if Chinese
	@brief			����mifare ultralight����ĳҳ����
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		page		Ҫд���ҳ�ţ�0~15
	@param[in]		data		Ҫд���ҳ���ݣ�4�ֽ�
	@retval   	    0			д���ݿ�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺		\n
								EACCES	����Ӧ���ڲ��� mifare ultralight ��	\n
								EPROTO	����Ƭ�������ݲ�����mifareЭ��		\n
								EINVAL	����������							\n
								ECOMM	����Ƭ���ص�������ż�����CRCУ���	\n
								EIO		������оƬ����						\n
								ETIME	����ʱ����							\n
								EBADE	����Ƭ���ص����ݳ��ȴ���			\n
								����ֵ	������������
 @else
	@brief			Write content of a page of mifare ultralight card.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		page		page number that will be written, 0~15
	@param[in]		data		page data that will be written, 4 bytes
	@retval   	    0			write data block operation successfully
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								ENODATA		: is not a mifare ultralight card in inductive zone		\n
								EPROTO		: Card doesn��t comply with mifare protocol				\n
								EINVAL		: parameter error										\n
								ECOMM		: Parity error or CRC check error of card returned data	\n
								EIO			: read card chip error									\n
								ETIME		: timeout return										\n
								EBADE		: error of length of card returned data					\n
								Other value	: other error code
 @endif
*/
int mifare_ultralight_write_page(int fd,uint8_t page,const void *data);

/**
 @if Chinese
	@brief			����mifare ultralight����4ҳ���ݣ�16�ֽ�
	@param[in]		fd			mif_open�������������豸���ļ���
	@param[in]		page		Ҫд���ҳ�ţ�0~15
	@param[in]		data		Ҫд������ݣ�16�ֽ�
	@retval   	    0			д���ݿ�����ɹ�
	@retval   	    -1			����ʧ�ܣ���ͨ��errno��ȡ����Ĵ����룺		\n
								EACCES	����Ӧ���ڲ���mifare ultralight��	\n
								EPROTO	����Ƭ�������ݲ�����mifareЭ��		\n
								EINVAL	����������							\n
								ECOMM	����Ƭ���ص�������ż�����CRCУ���	\n
								EIO		������оƬ����						\n
								ETIME	����ʱ����							\n
								EBADE	����Ƭ���ص����ݳ��ȴ���			\n
								����ֵ	������������
 @else
	@brief			Write 4pages, 16 bytes.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		page		page number, 0~15
	@param[out]		data		Data to write, 16 bytes.
	@retval   	    0			write data block operation successfully
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								ENODATA		: is not a mifare ultralight card in inductive zone		\n
								EPROTO		: Card doesn��t comply with mifare protocol				\n
								EINVAL		: parameter error										\n
								ECOMM 		: Parity error or CRC check error of card returned data	\n
								EIO			: read card chip error									\n
								ETIME		: timeout return										\n
								EBADE		: error of length of card returned data					\n
								other value : other error code										\n
 @endif
*/
int mifare_ultralight_write_page16(int fd,uint8_t page,const void *data);

#ifdef __cplusplus
  }
#endif /* __cplusplus */

#endif /* MIFUL_H_ */
/** @} */