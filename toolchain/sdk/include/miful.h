/*!
 @if Chinese
 	@file        miful.h
	@author      neal
	@date        2010-10-14
	@version     1.0.0
	@note        此模块用于描述 <strong>mifare ultralight</strong> 相关的接口	
	@remarks        修改记录:
	日期          | 作者            | 描述
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
 	@brief       此模块用于描述miful模块相关的接口
	
	源文件：<a href="miful_8h_source.html">miful.h</a>
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
	@brief			检测感应区内是否存在mifare ultralight卡，若有则激活
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		mode		轮询模式，取值如下：
								0：仅轮询所有处于IDLE状态的卡片
								1：轮询所有处于IDLE或者HALT状态的卡片
	@param[out]		uid			卡片返回的7字节UID信息
	@retval   	    0			寻卡操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：			\n
								ENODATA		：感应区内无mifare ultralight卡		\n
								EMULTIHOP	：感应区内有多卡					\n
								EPROTO		：卡片返回数据不符合ISO14443协议	\n
								EBADE		：卡片返回的数据长度不正确			\n
								EINVAL		：参数错误							\n
								ECOMM		：卡片返回的数据奇偶错或者CRC校验错	\n
								EIO			：读卡芯片错误						\n
								ETIME		：超时返回							\n
								其它值		：其它错误码
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
								EPROTO		: card doesn’t comply with ISO14443 standard			\n
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
	@brief			复位感应区内的mifare ultralight卡
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@retval   	    0			复位操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：	\n
								EIO		：读卡芯片错误					\n
								其它值	：其它错误码
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
	@brief			读取mifare ultralight卡的某页内容，一次读取4个页内容
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		page		要读取的起始页号，0~15
	@param[out]		data		读出来的页内容，16字节
	@retval   	    0			读数据块操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：		\n
								EACCES	：感应区内不是mifare ultralight卡	\n
								EINVAL	：参数错误							\n
								ECOMM	：卡片返回的数据奇偶错或者CRC校验错	\n
								EIO		：读卡芯片错误						\n
								ETIME	：超时返回							\n
								EBADE	：卡片返回的数据长度错误			\n
								其它值	：其它错误码
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
	@brief			更改mifare ultralight卡的某页内容
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		page		要写入的页号，0~15
	@param[in]		data		要写入的页内容，4字节
	@retval   	    0			写数据块操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：		\n
								EACCES	：感应区内不是 mifare ultralight 卡	\n
								EPROTO	：卡片返回数据不符合mifare协议		\n
								EINVAL	：参数错误							\n
								ECOMM	：卡片返回的数据奇偶错或者CRC校验错	\n
								EIO		：读卡芯片错误						\n
								ETIME	：超时返回							\n
								EBADE	：卡片返回的数据长度错误			\n
								其它值	：其它错误码
 @else
	@brief			Write content of a page of mifare ultralight card.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		page		page number that will be written, 0~15
	@param[in]		data		page data that will be written, 4 bytes
	@retval   	    0			write data block operation successfully
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								ENODATA		: is not a mifare ultralight card in inductive zone		\n
								EPROTO		: Card doesn’t comply with mifare protocol				\n
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
	@brief			更改mifare ultralight卡的4页内容，16字节
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		page		要写入的页号，0~15
	@param[in]		data		要写入的数据，16字节
	@retval   	    0			写数据块操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：		\n
								EACCES	：感应区内不是mifare ultralight卡	\n
								EPROTO	：卡片返回数据不符合mifare协议		\n
								EINVAL	：参数错误							\n
								ECOMM	：卡片返回的数据奇偶错或者CRC校验错	\n
								EIO		：读卡芯片错误						\n
								ETIME	：超时返回							\n
								EBADE	：卡片返回的数据长度错误			\n
								其它值	：其它错误码
 @else
	@brief			Write 4pages, 16 bytes.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		page		page number, 0~15
	@param[out]		data		Data to write, 16 bytes.
	@retval   	    0			write data block operation successfully
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								ENODATA		: is not a mifare ultralight card in inductive zone		\n
								EPROTO		: Card doesn’t comply with mifare protocol				\n
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