/*!
 @if Chinese
 	@file        mifone.h
	@author      neal
	@date        2010-10-14
	@version     1.0.0
	@note        此模块用于描述 <strong>mifare one</strong> 相关的接口
	@remarks        修改记录:
	日期          | 作者            | 描述
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
 	@brief       此模块用于描述 mifone 模块相关的接口
	
	源文件：<a href="mifone_8h_source.html">mifone.h</a>
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
	@brief			检测感应区内是否存在mifare one卡，若有则激活
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		mode		轮询模式，取值如下：
								0：仅轮询所有处于IDLE状态的卡片
								1：轮询所有处于IDLE或者HALT状态的卡片
	@param[out]		uid			卡片返回的5字节UID信息，4字节UID+BCC
	@param[out]		cardtype	返回的mifare one卡片类型，可能取值如下：		\n
								MIF_M1_S50	：mifare one S50 卡					\n
								MIF_M1_S70	：mifare one S70 卡					\n
								MIF_PRO_S50	：兼容T=CL协议和S50协议的TypeA卡	\n
								MIF_PRO_S70	：兼容T=CL协议和S70协议的TypeA卡
	@retval   	    0			寻卡操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：			\n
								ENODATA ：感应区内无 mifare one 卡				\n
								EMULTIHOP ：感应区内有多卡						\n
								EPROTO ：卡片返回数据不符合 ISO14443 协议		\n
								EBADE ：卡片返回的数据长度不正确				\n
								EINVAL ：参数错误								\n
								ECOMM ：卡片返回的数据奇偶错或者 CRC 校验错		\n
								EIO ：读卡芯片错误								\n
								ETIME ：超时返回								\n
								其他值 ：其它错误码
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
								EPROTO		: Card doesn’t comply with ISO14443 standard			\n
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
	@brief			复位感应区内的mifare one卡
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@retval   	    0			复位操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：		\n
								EIO		：读卡芯片错误						\n
								其它值	：其它错误码
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
	@brief			读取mifare ultralight卡的某页内容，一次读取4个页内容
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		blockno		要认证的数据块号，对于S50卡，取值范围为0~63；对于S70卡，取值范围为0~255
	@param[in]		keytype		要认证的密钥类型，取值如下：				\n
								'A'：认证 A 密钥							\n
								'B'：认证 B 密钥
	@param[in]		key			6字节长度的密钥信息
	@param[in]		uid			4字节的UID信息
	@retval   	    0			密码验证操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：		\n
								EACCES	：感应区内不是mifare one卡			\n
								EPERM	：验证失败							\n
								EPROTO	：卡片返回数据不符合mifare one协议	\n
								EINVAL	：参数错误							\n
								ECOMM	：卡片返回的数据奇偶错或者CRC校验错	\n
								EIO		：读卡芯片错误						\n
								ETIME	：超时返回							\n
								其他值	：其它错误码
 @else
	@brief			Password authentication about mifare one card’s a data block.
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
								EPROTO		: Card doesn’t comply with mifare one protocol			\n
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
	@brief			读取mifare one卡的某个数据块内容
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		blockno		要读取的数据块号，对于S50卡，取值范围为 0~63；对于S70卡，取值范围为0~255
	@param[out]		blockdata	读出来的数据块内容，16字节
	@retval   	    0			读数据块操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：			\n
								EACCES	：感应区内不是 mifare one 卡			\n
								EPERM	：验证失败								\n
								EPROTO	：卡片返回数据不符合 mifare one 协议	\n
								EINVAL	：参数错误								\n
								ECOMM	：卡片返回的数据奇偶错或者 CRC 校验错	\n
								EIO		：读卡芯片错误							\n
								ETIME	：超时返回								\n
								EBADE	：卡片返回的数据长度错误				\n
								其他值	：其它错误码
 @else
	@brief			Read a data block content of mifare one card.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		blockno		number of data block that will be read, for S50 card ,value scope is 0~63, for S70 card ,value scope is 0~255
	@param[out]		blockdata	read content of data block,16 bytes
	@retval   	    0			read data block success
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								EACCES		: is not a mifare one card in inductive zone			\n
								EPERM		: authentication failure								\n
								EPROTO		: Card doesn’t comply with mifare one protocol			\n
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
	@brief			更改mifare one卡的某个数据块内容
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		blockno		要读取的数据块号。对于S50卡，取值范围为0~63；对于S70卡，取值范围为0~255
	@param[in]		blockdata	要写入的数据块内容，16字节
	@retval   	    0			写数据块操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：		\n
								EACCES	：感应区内不是mifare one卡			\n
								EPERM	：验证失败							\n
								EPROTO	：卡片返回数据不符合mifare one协议	\n
								EINVAL	：参数错误							\n
								ECOMM	：卡片返回的数据奇偶错或者CRC校验错	\n
								EIO		：读卡芯片错误						\n
								ETIME	：超时返回							\n
								EBADE	：卡片返回的数据长度错误			\n
								其他值	：其它错误码
 @else
	@brief			Modify content of a data block of mifare one card.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		blockno		number of data block that will be read, for S50 card ,value scope is 0~63, for S70 card ,value scope is 0~255
	@param[in]		blockdata	content of data block that will be written, 16 bytes
	@retval   	    0			write data block success
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								EACCES		: is not a mifare one card in inductive zone			\n
								EPERM		: authentication failure								\n
								EPROTO		: Card doesn’t comply with mifare one protocol			\n
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
	@brief			将mifare one卡的某个数据块设置成数值块，并赋初值
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		blockno		要读取的数据块号。对于S50卡，取值范围为0~63；对于S70卡，取值范围为0~255
	@param[in]		value		要填入的初始值
	@retval   	    0			初始化数值块操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：		\n
								EACCES	：感应区内不是mifare one卡			\n
								EPERM	：验证失败							\n
								EPROTO	：卡片返回数据不符合mifare one协议	\n
								EINVAL	：参数错误							\n
								ECOMM	：卡片返回的数据奇偶错或者CRC校验错	\n
								EIO		：读卡芯片错误						\n
								ETIME	：超时返回							\n
								EBADE	：卡片返回的数据长度错误			\n
								其他值	：其它错误码
 @else
	@brief			Set a data block of mifare one card to value block,and fu initial.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		blockno		number of data block that will be read, for S50 card ,value scope is 0~63, for S70 card ,value scope is 0~255
	@param[in]		value		initial value that will be filled in
	@retval   	    0			initialize value block success
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								EACCES		: is not a mifare one card in inductive zone			\n
								EPERM		: authentication failure								\n
								EPROTO		: Card doesn’t comply with mifare one protocol			\n
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
	@brief			数值块增值操作
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		blockno		要读取的数据块号。对于S50卡，取值范围为0~63；对于S70卡，取值范围为0~255
	@param[in]		value		要增加的值
	@retval   	    0			增值操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：			\n
								EACCES	：感应区内不是 mifare one 卡			\n
								EPERM	：验证失败								\n
								EPROTO	：卡片返回数据不符合 mifare one 协议	\n
								EINVAL	：参数错误								\n
								ECOMM	：卡片返回的数据奇偶错或者 CRC 校验错	\n
								EIO		：读卡芯片错误							\n
								ETIME	：超时返回								\n
								EBADE	：卡片返回的数据长度错误				\n
								ENOSYS	：该块不是数值块						\n
								其他值	：其它错误码
 @else
	@brief			Value block value-added operation.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		blockno		number of data block that will be read, for S50 card ,value scope is 0~63, for S70 card ,value scope is 0~255
	@param[in]		value		value that will be added
	@retval   	    0			value increment operation success
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								EACCES		: is not a mifare one card in inductive zone			\n
								EPERM		: authentication failure								\n
								EPROTO 		: Card doesn’t comply with mifare one protocol			\n
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
	@brief			数值块减值操作
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		blockno		要读取的数据块号。对于S50卡，取值范围为0~63；对于S70卡，取值范围为0~255
	@param[in]		value		要减掉的值
	@retval   	    0			减值操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：			\n
								EACCES	：感应区内不是 mifare one 卡			\n
								EPERM	：验证失败								\n
								EPROTO	：卡片返回数据不符合 mifare one 协议	\n
								EINVAL	：参数错误								\n
								ECOMM	：卡片返回的数据奇偶错或者 CRC 校验错	\n
								EIO		：读卡芯片错误							\n
								ETIME	：超时返回								\n
								EBADE	：卡片返回的数据长度错误				\n
								ENOSYS	：该块不是数值块						\n
								其他值	：其它错误码
 @else
	@brief			Value block decrement operation.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		blockno		number of data block that will be read, for S50 card ,value scope is 0~63, for S70 card ,value scope is 0~255
	@param[in]		value		value that will be impaired
	@retval   	    0			decrement operation success
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								EACCES		: is not a mifare one card in inductive zone			\n
								EPERM		: authentication failure								\n
								EPROTO		: Card doesn’t comply with mifare one protocol			\n
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
	@brief			数值块转存操作
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		blockno		要读取的数据块号。对于S50卡，取值范围为0~63；对于S70卡，取值范围为0~255
	@retval   	    0			转存操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：		\n
								EACCES	：感应区内不是mifare one卡			\n
								EPERM	：验证失败							\n
								EPROTO	：卡片返回数据不符合mifare one协议	\n
								EINVAL	：参数错误							\n
								ECOMM	：卡片返回的数据奇偶错或者CRC校验错	\n
								EIO		：读卡芯片错误						\n
								ETIME	：超时返回							\n
								EBADE	：卡片返回的数据长度错误			\n
								ENOSYS	：该块不是数值块					\n
								其他值	：其它错误码
 @else
	@brief			Restore value in the designated block.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		blockno		number of data block that will be read, for S50 card ,value scope is 0~63, for S70 card ,value scope is 0~255
	@retval   	    0			restore operation success
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								EACCES		: is not a mifare one card in inductive zone			\n
								EPERM		: authentication failure								\n
								EPROTO		: Card doesn’t comply with mifare one protocol			\n
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
	@brief			保存数值块操作结果
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		blockno		要读取的数据块号。对于S50卡，取值范围为0~63；对于S70卡，取值范围为0~255
	@retval   	    0			保存数值块操作结果成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：		\n
								EACCES	：感应区内不是mifare one卡			\n
								EPERM	：验证失败							\n
								EPROTO	：卡片返回数据不符合mifare one协议	\n
								EINVAL	：参数错误							\n
								ECOMM	：卡片返回的数据奇偶错或者CRC校验错	\n
								EIO		：读卡芯片错误						\n
								ETIME	：超时返回							\n
								EBADE	：卡片返回的数据长度错误			\n
								ENOSYS	：该块不是数值块					\n
								其他值	：其它错误码
 @else
	@brief			Save the result of value block operation.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		blockno		number of data block that will be read, for S50 card ,value scope is 0~63, for S70 card ,value scope is 0~255
	@retval   	    0			save the result of value block operation success
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								EACCES		: is not a mifare one card in inductive zone			\n
								EPERM		: authentication failure								\n
								EPROTO		: Card doesn’t comply with mifare one protocol			\n
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
	@brief			获取数值块的值大小
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		blockno		要读取的数据块号。对于S50卡，取值范围为0~63；对于S70卡，取值范围为0~255
	@param[out]		value		卡片返回的值内容
	@retval   	    0			保存数值块操作结果成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：			\n
								EACCES	：感应区内不是 mifare one 卡			\n
								EPERM	：验证失败								\n
								EPROTO	：卡片返回数据不符合 mifare one 协议	\n
								EINVAL	：参数错误								\n
								ECOMM	：卡片返回的数据奇偶错或者 CRC 校验错	\n
								EIO		：读卡芯片错误							\n
								ETIME	：超时返回								\n
								EBADE	：卡片返回的数据长度错误				\n
								ENOSYS	：该块不是数值块						\n
								其他值	：其它错误码
 @else
	@brief			Get the value of the designated block.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		blockno		number of data block that will be read, for S50 card ,value scope is 0~63, for S70 card ,value scope is 0~255
	@param[out]		value		value content that card returns
	@retval   	    0			get the value of value block operation success
	@retval   	    -1			Operate failure, please get the actual error code by errno:			\n
								EACCES		: is not a mifare one card in inductive zone			\n
								EPERM		: authentication failure								\n
								EPROTO		: Card doesn’t comply with mifare one protocol			\n
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