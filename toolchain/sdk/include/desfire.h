/*!
 @if Chinese
 	@file        desfire.h
	@author      neal
	@date        2010-10-14
	@version     1.0.0
	@note        此模块用于描述 <strong>mifare desfire</strong> 相关的接口
	@remarks     修改记录:
	日期          | 作者            | 描述
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
 	@brief       此模块用于描述desfire模块相关的接口,需链接库<b>libnfc.so</b>编译
	
	源文件：<a href="desfire_8h_source.html">desfire.h</a>
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
 @name Mifare DESFire卡返回错误码说明
 @{
	返回值        | 原因
	------------- | --------------- 
	1036	      | 没有对备份文件做任何更改，不需要提交Transaction/AbortTransaction
	1038	      | NV-Memory内存不足，无法完成命令
	1052          | 不支持命令码
	1054          | CRC或MAC不匹配，填充字节无效
	1088          | 指定的键号无效
	1150          | 命令字符串长度无效
	1181          | 当前配置/状态不允许请求的命令
	1182          | 参数的值无效
	1184          | 请求的AID在PICC上不存在
	1185          | 应用程序中无法恢复的错误，应用程序将被禁用
	1198          | 当前身份验证状态不允许请求的命令
	1199          | 期望发送更多的数据帧
	1214          | 尝试从/往 文件/记录 限制中 读取/写入 数据，<br>或尝试超出文件值的限制
	1217          | PICC中发生不可恢复的错误，PICC将被禁用
	1226          | 上一个命令尚未完全完成。并非所有的帧都是由PICC请求或提供的
	1229          | PICC因不可恢复的错误而被禁用
	1230          | 应用程序数量限制为28，无法再添加CreateApplication
	1246          | 文件/应用程序创建失败，因为具有相同编号的文件/应用程序已经存在
	1262          | 由于断电而无法完成NV-Memory写入操作，内部备份/回退机制已激活
	1264          | 指定的文件号不存在
	1265          | 文件内发生不可恢复的错误，文件将被禁用。
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
	@brief			检测感应区内是否存在mifare DESFire卡，若有，则激活
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		mode		轮询模式，取值如下：					\n
								0：仅轮询所有处于IDLE状态的卡片			\n
								1：轮询所有处于IDLE或者HALT状态的卡片
	@param[out]		uid			卡片返回的7字节UID信息
	@param[out]		atslen		卡片返回的ATS信息长度
	@param[out]		ats			卡片返回的ATS信息
	@retval   	    0			寻卡操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：				\n
								ENODATA		：感应区内无 mifare DESFire 卡			\n	
								EMULTIHOP	：感应区内有多卡						\n
								EPROTO		：卡片返回数据不符合 ISO14443 协议		\n
								EBADE		：卡片返回的数据长度不正确				\n
								EINVAL		：参数错误								\n
								ECOMM		：卡片返回的数据奇偶错或者 CRC 校验错	\n
								EIO			：读卡芯片错误							\n
								ETIME		：超时返回								\n
								其他值		：其它错误码
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
								EPROTO		: Card doesn’t comply with ISO14443 protocol			\n
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
	@brief			复位mifare DESFire卡
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码
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
	@brief			对mifare DESFire卡进行DES/3DES密钥认证
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		keyno		要认证的密钥号
	@param[in]		key			密钥信息，固定为16字节
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	： 输入参数错误											\n
								EIO		： 读卡芯片错误											\n
								ECOMM	： 卡片返回数据奇偶错或者 CRC 校验错					\n
								EPROTO	： 卡片返回数据不符合 ISO14443 规范						\n
								EBADE	： 卡片返回数据长度错误									\n
								ETIME	： 超时无返回											\n
								EACCES	： 感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其他值	： 其它错误码
	@note
		- key信息必须为16字节的，如果实际密钥只有8字节，则按下列方式扩展成16字节：<br>
			`key = old_key[0…7] || old_key[0…7]`
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
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
	@note
		- key information must be 16 types, if actual key is 8 bytes, then expanding it to 16 bytes as follow:<br>
			`key = old_key[0…7] || old_key[0…7]`
 @endif
*/
int desfire_authenticate(int fd,uint8_t keyno, const void *key);

/**
 @if Chinese
	@brief			对mifare DESFire卡进行DES/3DES密钥认证
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		keyno		要认证的密钥号
	@param[in]		key			密钥信息，固定为24字节
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其他值	：其它错误码
	@note
		- key 信息必须为 24 字节的， 如果实际密钥只有 8 字节， 则按下列方式扩展成 24 字节：<br>
			`key = old_key[0…7] || old_key[0…7] || old_key[0…7]`
		- 如果实际密钥只有16字节， 则按下列方式扩展成24字节：<br>
			`key = old_key[0…7] || old_key[8…15] || old_key[0…7]`
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
								EPROTO		: Card doesn’t fix ISO14443 standard											\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
	@note
		- key information must be 24 types, if actual key is 8 bytes, then expanding it to 24 bytes as follow:<br>
			`key = old_key[0…7] || old_key[0…7] || old_key[0…7]`
		- if actual key is 16 bytes, then expanding it to 24 bytes as follow:<br>
			`key = old_key[0…7] || old_key[8…15] || old_key[0…7]`
 @endif
*/
int desfire_authenticate_iso(int fd,uint8_t keyno, const void *key);

/**
 @if Chinese
	@brief			对mifare DESFire卡进行AES密钥认证
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		keyno		要认证的密钥号
	@param[in]		key			密钥信息，固定为16字节
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其他值	：其它错误码
	@note
		- AES密钥固定长度为16字节
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
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
	@note
		- AES key’s length is fixed 16 bytes
 @endif
*/
int desfire_authenticate_aes(int fd,uint8_t keyno, const void *key);

/**
 @if Chinese
	@brief			修改PICC Master Key设置或者Application Master Key设置
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		key_setting	新的 Master Key 设置参数
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其他值	：其它错误码
 @else
	@brief			Modify PICC Master Key set or Application Master Key set.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		key_setting	new Master Key setting parameter
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code	
 @endif
*/
int desfire_change_key_settings(int fd,uint8_t key_setting);

/**
 @if Chinese
	@brief			修改PICC Master Key设置或者Application Master Key设置
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[out]		key_setting	卡片返回的Master Key设置参数
	@param[out]		max_key_num	当前应用支持的最大密钥数
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其他值	：其它错误码
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
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_get_key_settings(int fd,uint8_t *key_setting, uint8_t *max_key_num);

/**
 @if Chinese
	@brief			修改PICC Master Key
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		type		PICC Master Key密钥类型，取值如下：	\n
								0x00：DES/3DES密钥（16 字节）		\n
								0x01：3KDES密钥（24 字节）			\n
								0x02：AES密钥（16 字节）
	@param[in]		key			密钥信息，16/24字节
	@param[in]		version		密钥版本信息
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：						\n
								EINVAL	：输入参数错误										\n
								EIO		：读卡芯片错误										\n
								ECOMM	：卡片返回数据奇偶错或者CRC校验错					\n
								EPROTO	：卡片返回数据不符合ISO14443规范					\n
								EBADE	：卡片返回数据长度错误								\n
								ETIME	：超时无返回										\n
								EACCES	：感应区内的卡片不是mifare DESFire卡或者卡片未激活	\n
								其他值	：其它错误码
 @else
	@brief			Change PICC Master Key.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		type		PICC Master Key key type, values as follow:	\n
								0x00: DES/3DES key (16 bytes)				\n
								0x01: 3KDES key (24 字节)					\n
								0x02: AES key (16 字节)
	@param[in]		key			key information, 16/24 bytes
	@param[in]		version		key version information
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_change_picc_masterkey(int fd,uint8_t type, const void *key,uint8_t version);

/**
 @if Chinese
	@brief			修改应用密钥
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		keysetting	应用的master key配置属性参数
	@param[in]		type		PICC Master Key密钥类型，取值如下：	\n
								0x00：DES/3DES密钥（16 字节）		\n
								0x01：3KDES密钥（24 字节）			\n
								0x02：AES密钥（16 字节）
	@param[in]		keyno		要修改的密钥号
	@param[in]		oldkey		旧的密钥信息，16/24字节
	@param[in]		newkey		新的密钥信息，16/24字节
	@param[in]		version		密钥版本信息
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其他值	：其它错误码
 @else
	@brief			Change application key.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		keysetting	application’s master key configuration attribute parameter
	@param[in]		type		PICC Master Key key type, values as follow:	\n
								0x00: DES/3DES key (16 bytes)				\n
								0x01: 3KDES key (24 字节)					\n
								0x02: AES key (16 字节)
	@param[in]		keyno		key number that will be modified
	@param[in]		oldkey		old key information, 16/24 bytes
	@param[in]		newkey		new key information, 16/24 bytes
	@param[in]		version		key version information
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
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
	@brief			修改PICC Master Key设置或者Application Master Key设置
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		keyno		密钥号
	@param[out]		version		卡片返回的密钥版本信息
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其他值	：其它错误码
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
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_get_key_version(int fd,uint8_t keyno,uint8_t *version);

/**
 @if Chinese
	@brief Desfire应用程序信息
 @else
	@brief Desfire application information
 @endif
*/
typedef struct
{
	uint8_t AID[3];				/*!< @if Chinese 中国应用标识 @else Application Identifies @endif */
	uint8_t MasterKeySetting; 	/*!< @if Chinese 应用程序主key设置 @else Application master key setting @endif */
	uint8_t NumberOfKey; 		/*!< @if Chinese 可以在应用程序内存储的密钥数 @else Number of keys that can be stored within the application @endif */
	uint8_t CryptoMode;			/*!< @if Chinese 应用程序的加密key类型：<br>0 - DES/3DES key<br>1 - 3KDES key<br>2 - AES key @else the key type of application:<br>0 - DES/3DES key<br>1 - 3KDES key<br>2 - AES key @endif */
	uint8_t IsSupFID; 			/*!< @if Chinese 是否使用文件标识 @else whether use File Identifies @endif */
	uint8_t IsSupISOFID; 		/*!< @if Chinese 是否使用2字节ISO/IEC 7816-4文件标识应用程序中的文件 @else whether use of 2 byte ISO/IEC 7816-4 File Identifies for files within the Application @endif */
	uint8_t ISOFID[2];			/*!< @if Chinese 2字节ISO/IEC 7816-4文件标识文件 @else 2 byte ISO/IEC 7816-4 File Identifies for files @endif */
	uint8_t LenOfDFName; 		/*!< @if Chinese 7816-4模式下使用的"DF-name"的长度，0-不携带"DF-name" @else the length of "DF-name" used in 7816-4 mode, 0 - does not carries "DF-name" @endif */
	uint8_t DFName[16]; 		/*!< @if Chinese 在7816-4模式下与ISO SELECT命令结合使用的"DF-name" @else "DF-name" used in 7816-4 mode in combination with the ISO SELECT command @endif */
	uint8_t RFU;
}desfire_appinfo;

/**
 @if Chinese
	@brief			创建一个子应用
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		info		应用信息
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其他值	：其它错误码
 @else
	@brief			Create a sub-application.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		info		application information
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_create_application(int fd,const desfire_appinfo *info);

/**
 @if Chinese
	@brief			删除一个子应用
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		aid			应用的AID信息，3字节
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：						\n
								EINVAL	：输入参数错误										\n
								EIO		：读卡芯片错误										\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错					\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范					\n
								EBADE	：卡片返回数据长度错误								\n
								ETIME	：超时无返回										\n
								EACCES	：感应区内的卡片不是mifare DESFire卡或者卡片未激活	\n
								其他值	：其它错误码
 @else
	@brief			Delete a sub-application.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		aid			application AID information, 3 bytes
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_delete_application(int fd,const void *aid);

/**
 @if Chinese
	@brief			获取DESFire卡内所有应用的AID信息
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[out]		num			卡片包含的应用个数
	@param[out]		aid			应用的AID信息，3字节/每个应用
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其他值	：其它错误码
 @else
	@brief			Get all application’s AID information of DESFire card.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[out]		num			application number that card contained
	@param[out]		aid			application AID information, 3 bytes every application
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_get_application_ids(int fd,uint8_t *num, void *aid);

/**
 @if Chinese
	@brief Desfire卡应用名字信息
 @else
	@brief Desfire card application name information
 @endif
*/
typedef struct
{
	uint8_t AID[3];			/*!< @if Chinese 应用标识符 @else Application Identifies @endif */
	uint8_t FID[2];			/*!< @if Chinese 2字节ISO/IEC 7816-4文件标识文件 @else 2 byte ISO/IEC 7816-4 File Identifies for files @endif */
	uint8_t LenOfDFName;	/*!< @if Chinese 7816-4模式下使用的"DF-name"的长度，0-不携带"DF-name" @else the length of "DF-name" used in 7816-4 mode, 0 - does not carries "DF-name" @endif */
	uint8_t DFName[16];		/*!< @if Chinese 在7816-4模式下与ISO SELECT命令结合使用的"DF-name" @else "DF-name" used in 7816-4 mode in combination with the ISO SELECT command @endif */
	uint8_t RFU[2];			/*!< @if Chinese RFU @else RFU @endif */
}dfname_info;

/**
 @if Chinese
	@brief			获取DESFire卡内所有应用的信息
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[out]		appnum		卡片包含的应用个数
	@param[out]		info		应用信息，每个应用一个dfname_info结构
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其他值	：其它错误码
 @else
	@brief			Get all application’s information of DESFire.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[out]		appnum		application number that card contained
	@param[out]		info		application information, every application has a dfname_info struct
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_get_dfnames(int fd,uint8_t *appnum,dfname_info *info);

/**
 @if Chinese
	@brief			选择一个子应用
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		aid			应用的AID信息，3字节
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其他值	：其它错误码
 @else
	@brief			Select a sub-application.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		aid			application AID information, 3 bytes
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_select_application(int fd,const void *aid);

/**
 @if Chinese
	@brief			格式化整个DESFire卡，删除所有的应用以及应用下的密钥和文件信息
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其他值	：其它错误码
 @else
	@brief			Format DESFire card, delete all application and all application’s key and file information.
	@param[in]		fd			opened device file number that mif_open function returns
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA 	: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value : other error code
 @endif
*/
int desfire_format_picc(int fd);

/**
 @if Chinese
	@brief Desfire卡的版本信息
 @else
	@brief Desfire card version information
 @endif
*/
typedef struct  
{
	uint8_t HW_VendorID; 	/*!< @if Chinese 供应商ID（PHILIPS为0x04） @else codes the vendor ID ( 0x04 for PHILIPS ) @endif */
	uint8_t HW_Type;		/*!< @if Chinese 编码类型（这里为0x01） @else codes the type ( here 0x01 ) @endif */
	uint8_t HW_SubType;		/*!< @if Chinese 编码子类型（这里为0x01） @else codes the subtype ( here 0x01 ) @endif */
	uint8_t HW_MajorVer;	/*!< @if Chinese 主版本号 @else codes the major version number @endif */
	uint8_t HW_MinorVer;	/*!< @if Chinese 次版本号 @else codes the minor version number @endif */
	uint8_t HW_Size;		/*!< @if Chinese 对存储大小进行编码(这里0x1A = 8192字节) @else codes the storage size ( here 0x1A = 8192 bytes ) @endif */
	uint8_t HW_Protocol;	/*!< @if Chinese 通信协议类型(这里0x05表示ISO 14443-2和-3) @else codes the communication protocol type (here 0x05 meaning ISO 14443-2 and -3 ) @endif */

	uint8_t SW_VendorID;	/*!< @if Chinese 供应商ID（PHILIPS为0x04） @else codes the vendor ID ( here 0x04 for PHILIPS ) @endif */
	uint8_t SW_Type;		/*!< @if Chinese 编码类型（这里为0x01） @else codes the type ( here 0x01 ) @endif */	
	uint8_t SW_SubType;		/*!< @if Chinese 编码子类型（这里为0x01） @else codes the subtype ( here 0x01 ) @endif */
	uint8_t SW_MajorVer;	/*!< @if Chinese 主版本号 @else codes the major version number @endif */	
	uint8_t SW_MinorVer;	/*!< @if Chinese 次版本号 @else codes the minor version number @endif */
	uint8_t SW_Size;		/*!< @if Chinese 对存储大小进行编码(这里0x1A = 8192字节) @else codes the storage size ( here 0x1A = 8192 bytes ) @endif */
	uint8_t SW_Protocol;	/*!< @if Chinese 通信协议类型(这里0x05表示ISO 14443-2和-3) @else codes the communication protocol type (here 0x05 meaning ISO 14443-2 and -3 ) @endif */

	uint8_t UID[7];			/*!< @if Chinese 唯一序列号 @else code the unique serial number @endif */
	uint8_t BatchNo[5];		/*!< @if Chinese 生产批号 @else code the production batch number @endif */
	uint8_t CW_Prod;		/*!< @if Chinese 生产日历周 @else codes the calendar week of production @endif */
	uint8_t Year_Prod;		/*!< @if Chinese 编码生产年份 @else codes the year of production @endif */
}desfire_version;

/**
 @if Chinese
	@brief			获取mifare DESFire卡的版本信息
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[out]		version		mifare DESFire 卡的版本信息
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其他值	：其它错误码
 @else
	@brief			Get version information of mifare DESFire card.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[out]		version		version information of mifare DESFire card
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n	
								Other value	: other error code
 @endif
*/
int desfire_get_version(int fd, desfire_version *version);

/**
 @if Chinese
	@brief			配置mifare DESFire卡
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		option		配置信息选项
	@param[in]		len			配置信息长度
	@param[in]		info		配置信息内容
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其他值	：其它错误码
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
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_set_configuration(int fd,uint8_t option, uint8_t len,const void *info);

/**
 @if Chinese
	@brief			获取mifare DESFire卡的剩余可用空间大小
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[out]		freesize	mifare DESFire卡的剩余可用空间大小
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其他值	：其它错误码
 @else
	@brief			Get the size of the available memory space of mifare DESFire card.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[out]		freesize	size of the remaining available space of mifare DESFire card
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_free_memory(int fd,uint32_t *freesize);

/**
 @if Chinese
	@brief			获取mifare DESFire卡的UID信息
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[out]		uid			mifare DESFire卡返回的UID信息，7字节
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其他值	：其它错误码
 @else
	@brief			Get UID information of mifare DESFire card.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[out]		uid			UID information that mifare DESFire card returns, 7 bytes
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_get_card_uid(int fd,void *uid);

/**
 @if Chinese
	@brief			获取mifare DESFire卡当前子应用内的文件fid信息
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[out]		num			应用内的文件个数
	@param[out]		fid			文件的fid信息，1字节/每个文件
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其他值	：其它错误码
 @else
	@brief			Get current sub-application’s file fid information of mifare DESFire card.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[out]		num			file number of application
	@param[out]		fid			fid information of file,1 byte every file
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_get_fids(int fd,uint8_t *num, void *fid);

/**
 @if Chinese
	@brief			获取mifare DESFire卡当前子应用内的文件iso fid信息
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[out]		num			应用内的文件个数
	@param[out]		fid			文件的iso fid信息，2字节/每个文件
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其他值	：其它错误码
 @else
	@brief			Get current sub-application’s file iso fid information of mifare DESFire card.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[out]		num			file number of application
	@param[out]		fid			file iso fid information, 2 bytes every file
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_get_iso_fids(int fd,uint8_t *num, void *fid);

/**
 @if Chinese
	@brief Desfire文件信息
 @else
	@brief Desfire file information
 @endif
*/
typedef struct
{
	/** 
	 @if Chinese
		编码类型（这里为0x01）：		\n
		0x00  --- 标准数据文件			\n
		0x01  --- 备份数据文件			\n
		0x02  --- 带备份的值文件		\n
		0x03  --- 带备份的线性记录文件	\n
		0x04  --- 带备份的循环记录文件
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
		通信设置：									\n
		0x00 or 0x02	--- 简单的通信				\n
		0x01			--- 通过MACing保证简单的通信	\n
		0x03			--- 完全加密的通信
	 @else
		Communication settings:										\n
		0x00 or 0x02	--- Plain communication						\n
		0x01			--- Plain communication secured by MACing	\n
		0x03			--- Fully enciphered communication
	 @endif
	*/
	uint8_t com_sett;

	// Access right capability, 0x0E means free access, and 0x0F means deny access.
	uint8_t read_access_right_keyno;			/*!< @if Chinese 在进行读访问和读写访问之前需要验证的密钥号 @else the reference number of the key which needs to be authenticated prior to Read Access and Read&Write Access @endif */
	uint8_t write_access_right_keyno;			/*!< @if Chinese 在写访问和读写访问之前需要进行身份验证的密钥号 @else the reference number of the key which needs to be authentication prior to Write Access and Read&Write Access @endif */
	uint8_t read_and_write_access_right_keyno;	/*!< @if Chinese 读写访问之前需要进行身份验证的密钥号 @else the reference number of the key which needs to be authentication prior to  Read&Write Access @endif */
	uint8_t change_access_right_keyno;			/*!< @if Chinese 参考密钥号，必须进行身份验证才能更改文件的访问权限，并将每个访问权限链接到密钥号 @else the reference number of the key,which is necessary to be authenticated with in order to change the access rights for the file and to link each access right to key numbers @endif */
	
	uint32_t file_size;							/*!< @if Chinese 用户文件大小（以字节为单位），仅在file_type = 0x00或file_type = 0x01时可用 @else the user file size in bytes, only available when file_type = 0x00 or file_type = 0x01 @endif */

	// the following four parameters only available when file_type = 0x02
	uint32_t lower_limit;				/*!< @if Chinese 值文件的下限 @else lower limit of the value file @endif */
	uint32_t upper_limit;				/*!< @if Chinese 值文件的上限 @else upper limit of the value file @endif */
	uint32_t limited_credit_value; 		/*!< @if Chinese 当前的最大信用额度值 @else the current maximum "limited credit" value @endif */
	uint8_t  limited_credit_enabled; 	/*!< @if Chinese 如果此文件允许使用LimitedCredit命令（0x00表示禁用，0x01表示启用） @else if the LimitedCredit command is allowed for this file (0x00 for disabled, 0x01 for enabled) @endif */

	// the following three parameters  only available when file_type = 0x03 or file_type = 0x04
	uint32_t record_size;  				/*!< @if Chinese 一条记录的大小（在文件创建时定义） @else the size of one single record (as deefined at file creation) @endif */
	uint32_t max_number_of_records;  	/*!< @if Chinese 记录文件中的最大记录数（在文件创建时定义） @else the maximum number of records within the record file (as defined at file creation) @endif */
	uint32_t current_number_of_records;	/*!< @if Chinese 记录文件中当前的记录数 @else the current number of records within the record file @endif */
}desfire_file;

/**
 @if Chinese
	@brief			获取指定文件的信息
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		fileno		文件号
	@param[out]		filesetting	返回的文件信息
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	： 输入参数错误											\n
								EIO		： 读卡芯片错误											\n
								ECOMM	： 卡片返回数据奇偶错或者 CRC 校验错					\n
								EPROTO	： 卡片返回数据不符合 ISO14443 规范						\n
								EBADE	： 卡片返回数据长度错误									\n
								ETIME	： 超时无返回											\n
								EACCES	： 感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其他值	： 其它错误码
 @else
	@brief			Get the designated file’s information.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		fileno		file number
	@param[out]		filesetting	returned file information
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_get_filesetting(int fd,uint8_t fileno, desfire_file *filesetting);

/**
 @if Chinese
	@brief			获取指定文件的信息
	@param[in]		fd							mif_open函数返回所打开设备的文件号
	@param[in]		fileno						文件号
	@param[in]		comm_set					该文件的传输方式，取值如下：	\n
												0x00：明文传输					\n
												0x03：加密传输					\n
												0x01：带MAC传输
	@param[in]		old_change_access_keyno		旧的更改密钥需验证的密钥号
	@param[in]		new_read_access_keyno		新的读文件需验证的密钥号
	@param[in]		new_write_access_keyno		新的写文件需验证的密钥号
	@param[in]		new_read_write_access_keyno	新的读写文件需验证的密钥号
	@param[in]		new_change_access_keyno		新的更改密钥需验证的密钥号
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：						\n
								EINVAL	：输入参数错误										\n
								EIO		：读卡芯片错误										\n
								ECOMM	：卡片返回数据奇偶错或者CRC校验错					\n
								EPROTO	：卡片返回数据不符合ISO14443规范					\n
								EBADE	：卡片返回数据长度错误								\n
								ETIME	：超时无返回										\n
								EACCES	：感应区内的卡片不是mifare DESFire卡或者卡片未激活	\n
								其他值	：其它错误码
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
								EPROTO :Card doesn’t comply with ISO14443 standard										\n
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
	@brief Desfire一般数据文件信息
 @else
	@brief Desfire general data file information
 @endif
*/
typedef struct  
{	
	uint8_t FlgISOFileID; /*!< @if Chinese 是否启用ISO/IEC 7816-4文件ID标识符（0x00-禁用，0x01-启用） @else whether ISO/IEC 7816-4 File IDentifiers enabled (0x00 - disabled, 0x01-enabled) @endif */
	uint8_t ISOFileID[2]; /*!< @if Chinese 2个字节的ISO/IEC 7816-4文件标识符 @else 2bytes ISO/IEC 7816-4 File IDentifiers @endif */
	/** 
	 @if Chinese
		通信设置：									\n
		0x00 or 0x02	--- 简单的通信				\n
		0x01			--- 通过MACing保证简单的通信	\n
		0x03			--- 完全加密的通信
	 @else
		Communication settings:										\n
		0x00 or 0x02	--- Plain communication						\n
		0x01			--- Plain communication secured by MACing	\n
		0x03			--- Fully enciphered communication
	 @endif
	*/
	uint8_t com_sett;
	uint8_t read_access_right_keyno;	/*!< @if Chinese 在进行读访问和读写访问之前需要验证的密钥号 @else the reference number of the key which needs to be authenticated prior to Read Access and Read&Write Access @endif */
	uint8_t write_access_right_keyno;	/*!< @if Chinese 在写访问和读写访问之前需要进行身份验证的密钥号 @else the reference number of the key which needs to be authentication prior to Write Access and Read&Write Access @endif */
	uint8_t read_and_write_access_right_keyno;	/*!< @if Chinese 读写访问之前需要进行身份验证的密钥号 @else the reference number of the key which needs to be authentication prior to  Read&Write Access @endif */
	uint8_t change_access_right_keyno;	/*!< @if Chinese 参考密钥号，必须进行身份验证才能更改文件的访问权限，并将每个访问权限链接到密钥号 @else the reference number of the key,which is necessary to be authenticated with in order to change the access rights for the file and to link each access right to key numbers @endif */
	uint32_t file_size;	/*!< @if Chinese 用户文件大小（以字节为单位），仅在file_type = 0x00或file_type = 0x01时可用 @else the user file size in bytes, only available when file_type = 0x00 or file_type = 0x01 @endif */
}desfire_std_backup_file_info;

/**
 @if Chinese
	@brief			创建一般数据文件
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		fileno		文件号
	@param[in]		fileinfo	一般数据文件信息
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其它值	：其它错误码
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
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
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
	@brief			创建备份数据文件
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		fileno		文件号
	@param[in]		fileinfo	备份数据文件信息
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：						\n
								EINVAL	：输入参数错误										\n
								EIO		：读卡芯片错误										\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错					\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范					\n
								EBADE	：卡片返回数据长度错误								\n
								ETIME	：超时无返回										\n
								EACCES	：感应区内的卡片不是mifare DESFire卡或者卡片未激活	\n
								其它值	：其它错误码
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
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
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
	@brief Desfire值文件信息
 @else
	@brief Desfire value file information
 @endif
*/
typedef struct  
{
	/** 
	 @if Chinese
		通信设置：									\n
		0x00 or 0x02	--- 简单的通信				\n
		0x01			--- 通过MACing保证简单的通信	\n
		0x03			--- 完全加密的通信
	 @else
		Communication settings:										\n
		0x00 or 0x02	--- Plain communication						\n
		0x01			--- Plain communication secured by MACing	\n
		0x03			--- Fully enciphered communication
	 @endif
	*/
	uint8_t com_sett;
	uint8_t read_access_right_keyno;	/*!< @if Chinese 在进行读访问和读写访问之前需要验证的密钥号 @else the reference number of the key which needs to be authenticated prior to Read Access and Read&Write Access @endif */
	uint8_t write_access_right_keyno;	/*!< @if Chinese 在写访问和读写访问之前需要进行身份验证的密钥号 @else the reference number of the key which needs to be authentication prior to Write Access and Read&Write Access @endif */
	uint8_t read_and_write_access_right_keyno;	/*!< @if Chinese 读写访问之前需要进行身份验证的密钥号 @else the reference number of the key which needs to be authentication prior to  Read&Write Access @endif */
	uint8_t change_access_right_keyno;	/*!< @if Chinese 参考密钥号，必须进行身份验证才能更改文件的访问权限，并将每个访问权限链接到密钥号 @else the reference number of the key,which is necessary to be authenticated with in order to change the access rights for the file and to link each access right to key numbers @endif */
	
	uint32_t lower_limit;	/*!< @if Chinese 值文件的下限 @else lower limit of the value file @endif */
	uint32_t upper_limit;	/*!< @if Chinese 值文件的上限 @else upper limit of the value file @endif */
	uint32_t init_value;	/*!< @if Chinese 值文件的初始值 @else the initial value of this value file @endif */
	uint8_t  limited_credit_enabled;	/*!< @if Chinese 如果此文件允许使用LimitedCredit命令（0x00表示禁用，0x01表示启用） @else if the LimitedCredit command is allowed for this file (0x00 for disabled, 0x01 for enabled) @endif */
}desfire_value_file_info;

/**
 @if Chinese
	@brief			创建值文件
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		fileno		文件号
	@param[in]		fileinfo	值文件信息
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其它值	：其它错误码
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
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
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
	@brief Desfire线性记录文件信息
 @else
	@brief Desfire record file information
 @endif
*/
typedef struct  
{	
	uint8_t FlgISOFileID; /*!< @if Chinese 是否启用ISO/IEC 7816-4文件ID标识符（0x00-禁用，0x01-启用） @else whether ISO/IEC 7816-4 File IDentifiers enabled (0x00 - disabled, 0x01-enabled) @endif */
	uint8_t ISOFileID[2]; /*!< @if Chinese 2个字节的ISO/IEC 7816-4文件标识符 @else 2bytes ISO/IEC 7816-4 File IDentifiers @endif */
	/** 
	 @if Chinese
		通信设置：									\n
		0x00 or 0x02	--- 简单的通信				\n
		0x01			--- 通过MACing保证简单的通信	\n
		0x03			--- 完全加密的通信
	 @else
		Communication settings:										\n
		0x00 or 0x02	--- Plain communication						\n
		0x01			--- Plain communication secured by MACing	\n
		0x03			--- Fully enciphered communication
	 @endif
	*/
	uint8_t com_sett;
	uint8_t read_access_right_keyno;			/*!< @if Chinese 在进行读访问和读写访问之前需要验证的密钥号 @else the reference number of the key which needs to be authenticated prior to Read Access and Read&Write Access @endif */
	uint8_t write_access_right_keyno;			/*!< @if Chinese 在写访问和读写访问之前需要进行身份验证的密钥号 @else the reference number of the key which needs to be authentication prior to Write Access and Read&Write Access @endif */
	uint8_t read_and_write_access_right_keyno;	/*!< @if Chinese 读写访问之前需要进行身份验证的密钥号 @else the reference number of the key which needs to be authentication prior to  Read&Write Access @endif */
	uint8_t change_access_right_keyno;			/*!< @if Chinese 参考密钥号，必须进行身份验证才能更改文件的访问权限，并将每个访问权限链接到密钥号 @else the reference number of the key,which is necessary to be authenticated with in order to change the access rights for the file and to link each access right to key numbers @endif */

	uint32_t record_size;						/*!< @if Chinese 一条记录的大小（在文件创建时定义） @else the size of one single record (as deefined at file creation) @endif */
	uint32_t max_number_of_records;				/*!< @if Chinese 记录文件中的最大记录数（在文件创建时定义） @else the maximum number of records within the record file (as defined at file creation) @endif */
	uint32_t FlgRndAcc;							/*!< @if Chinese 是否指定随机写访问选项，（0x00-不是，0x01-是） @else whether specifies Random write access option, (0x00 - not, 0x01 - yes) @endif */
	uint32_t rnd_acc;							/*!< @if Chinese 是否允许随机写访问，（0x00-禁用，0x01-启用） @else whether allowed Random write access, (0x00 - disabled, 0x01 - enabled) @endif */				
}desfire_record_file_info;

/**
 @if Chinese
	@brief			创建线性记录文件
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		fileno		文件号
	@param[in]		fileinfo	线性记录文件信息
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其它值	：其它错误码
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
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
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
	@brief			创建循环记录文件
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		fileno		文件号
	@param[in]		fileinfo	循环记录文件信息
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其它值	：其它错误码
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
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
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
	@brief			删除一个文件
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		fileno		文件号
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其它值	：其它错误码
 @else
	@brief			Delete a file.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		fileno		file number
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_delete_file(int fd,uint8_t fileno);

/**
 @if Chinese
	@brief			从一般数据文件或者备份数据文件中读取数据
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		fileno		文件号
	@param[in]		comm_set	通信方式，取值如下：	\n
								0x00：明文传输			\n
								0x03：加密传输			\n
								0x01：带MAC校验传输
	@param[in]		offset		读取的起始地址
	@param[in]		len			希望读取的长度
	@param[out]		outlen		实际读取到的数据长度
	@param[out]		dataout		实际读取到的数据
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：						\n
								EINVAL	：输入参数错误										\n
								EIO		：读卡芯片错误										\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错					\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范					\n
								EBADE	：卡片返回数据长度错误								\n
								ETIME	：超时无返回										\n
								EACCES	：感应区内的卡片不是mifare DESFire卡或者卡片未激活	\n
								其他值	：其它错误码
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
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
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
	@brief			从一般数据文件或者备份数据文件中读取数据
	@param[in]		fd				mif_open函数返回所打开设备的文件号
	@param[in]		fileno			文件号
	@param[in]		comm_set		通信方式，取值如下：	\n
									0x00：明文传输			\n
									0x03：加密传输			\n
									0x01：带MAC校验传输
	@param[in]		offset			读取的起始地址
	@param[in]		len				希望读取的长度
	@param[out]		outlen			实际读取到的数据长度
	@param[out]		dataout			实际读取到的数据
	@param[in]		dataout_size	dataout 的缓存大小
	@retval   	    0				操作成功
	@retval   	    -1				操作失败，请通过errno获取具体的错误码：						\n
									EINVAL	：输入参数错误										\n
									EIO		：读卡芯片错误										\n
									ECOMM	：卡片返回数据奇偶错或者 CRC 校验错					\n
									EPROTO	：卡片返回数据不符合 ISO14443 规范					\n
									EBADE	：卡片返回数据长度错误								\n
									ETIME	：超时无返回										\n
									EACCES	：感应区内的卡片不是mifare DESFire卡或者卡片未激活	\n
									ENOSPC	：dataout空间小于接收数据大小						\n
									其他值	：其它错误码
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
									EPROTO		: Card doesn’t comply with ISO14443 standard									\n
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
	@brief			往一般数据文件或者备份数据文件中读取数据
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		fileno		文件号
	@param[in]		comm_set	通信方式，取值如下：	\n
								0x00：明文传输			\n
								0x03：加密传输			\n
								0x01：带MAC校验传输
	@param[in]		offset		写入的起始地址
	@param[in]		len			要写入的数据长度
	@param[out]		datain		要写入的数据
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：						\n
								EINVAL	：输入参数错误										\n
								EIO		：读卡芯片错误										\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错					\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范					\n
								EBADE	：卡片返回数据长度错误								\n
								ETIME	：超时无返回										\n
								EACCES	：感应区内的卡片不是mifare DESFire卡或者卡片未激活	\n
								其他值	：其它错误码
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
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
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
	@brief			获取指定值文件的值大小
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		fileno		文件号
	@param[in]		comm_set	通信方式，取值如下：	\n
								0x00：明文传输			\n
								0x03：加密传输			\n
								0x01：带MAC校验传输
	@param[out]		value		该值文件的值大小
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其它值	：其它错误码
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
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_get_value(int fd,uint8_t fileno,uint8_t comm_set,uint32_t *value);

/**
 @if Chinese
	@brief			获取指定值文件的值大小
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		fileno		文件号
	@param[in]		comm_set	通信方式，取值如下：	\n
								0x00：明文传输			\n
								0x03：加密传输			\n
								0x01：带MAC校验传输
	@param[in]		value		充值大小
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其它值	：其它错误码
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
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_credit(int fd,uint8_t fileno,uint8_t comm_set,uint32_t value);

/**
 @if Chinese
	@brief			扣值操作
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		fileno		文件号
	@param[in]		comm_set	通信方式，取值如下：	\n
								0x00：明文传输			\n
								0x03：加密传输			\n
								0x01：带MAC校验传输
	@param[in]		value		扣值大小
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其它值	：其它错误码
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
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_debit(int fd,uint8_t fileno,uint8_t comm_set,uint32_t value);

/**
 @if Chinese
	@brief			有限充值操作
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		fileno		文件号
	@param[in]		comm_set	通信方式，取值如下：	\n
								0x00：明文传输			\n
								0x03：加密传输			\n
								0x01：带MAC校验传输
	@param[in]		value		充值大小
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其它值	：其它错误码
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
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_limited_credit(int fd,uint8_t fileno,uint8_t comm_set,uint32_t value);

/**
 @if Chinese
	@brief			有限充值操作
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		fileno		文件号
	@param[in]		comm_set	通信方式，取值如下：	\n
								0x00：明文传输			\n
								0x03：加密传输			\n
								0x01：带MAC校验传输
	@param[in]		offset		当前记录内的起始地址
	@param[in]		len			要写入的数据长度
	@param[in]		info		要写入的记录信息
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其它值	：其它错误码
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
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
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
	@brief			读记录操作
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		fileno		文件号
	@param[in]		comm_set	通信方式，取值如下：	\n
								0x00：明文传输			\n
								0x03：加密传输			\n
								0x01：带MAC校验传输
	@param[in]		recordsize	记录长度
	@param[in]		first		要读取的第一条记录号
	@param[in]		num			要读取的记录数
	@param[out]		outlen		读出来的数据总长度
	@param[out]		info		读出来的记录信息
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其它值	：其它错误码
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
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
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
	@brief			读记录操作
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		fileno		文件号
	@param[in]		comm_set	通信方式，取值如下：	\n
								0x00：明文传输			\n
								0x03：加密传输			\n
								0x01：带MAC校验传输
	@param[in]		recordsize	记录长度
	@param[in]		first		要读取的第一条记录号
	@param[in]		num			要读取的记录数
	@param[out]		outlen		读出来的数据总长度
	@param[out]		info		读出来的记录信息
	@param[in]		info_size	info 的缓存大小
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其它值	：其它错误码
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
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
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
	@brief			清除记录文件内的所有
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@param[in]		fileno		文件号
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其它值	：其它错误码
 @else
	@brief			Clear all record files.
	@param[in]		fd			opened device file number that mif_open function returns
	@param[in]		fileno		file number
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_clear_recordfile(int fd,uint8_t fileno);

/**
 @if Chinese
	@brief			确认之前对当前应用内各个文件的相关操作并保存
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其它值	：其它错误码
 @else
	@brief			Confirm and save all related operations on current application’s files.
	@param[in]		fd			opened device file number that mif_open function returns
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
								EBADE		: error of length of card returned data											\n
								ETIME		: timeout return																\n
								ENODATA		: card in inductive is not a mifare DESFire card or card had not been activated	\n
								Other value	: other error code
 @endif
*/
int desfire_commit_transaction(int fd);

/**
 @if Chinese
	@brief			撤销之前队当前应用内各个文件的相关操作
	@param[in]		fd			mif_open函数返回所打开设备的文件号
	@retval   	    0			操作成功
	@retval   	    -1			操作失败，请通过errno获取具体的错误码：							\n
								EINVAL	：输入参数错误											\n
								EIO		：读卡芯片错误											\n
								ECOMM	：卡片返回数据奇偶错或者 CRC 校验错						\n
								EPROTO	：卡片返回数据不符合 ISO14443 规范						\n
								EBADE	：卡片返回数据长度错误									\n
								ETIME	：超时无返回											\n
								EACCES	：感应区内的卡片不是 mifare DESFire 卡或者卡片未激活	\n
								其它值	：其它错误码
 @else
	@brief			Undo related operations on current application’s files.
	@param[in]		fd			opened device file number that mif_open function returns
	@retval   	    0			operate success
	@retval   	    -1			operate failure, please get the actual error code by errno:									\n
								EINVAL		: input parameter error															\n
								EIO			: read card chip error															\n
								ECOMM		: Parity error or CRC check error of card returned data							\n
								EPROTO		: Card doesn’t comply with ISO14443 standard									\n
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
