/*
 * @Description: app层错误定义，若不满足， 请另自行增加错误定义，可在预留域中增加自定义错误
 * @Author: YangJing
 * @Date: 2020-04-07 09:36:37
 * @LastEditors: YangJing
 * @LastEditTime: 2020-04-10 14:23:00
 */

#ifndef _APP_ERR_DEF_H_
#define _APP_ERR_DEF_H_



typedef enum{
	RET_OK = 0,
		
	E_TRANS_BASE 		= 1,						// 交易类错误定义
	E_TRANS_CANCEL		= -(E_TRANS_BASE),			// 交易取消
	E_TRANS_FAILED		= -(E_TRANS_BASE + 1),		// 交易失败
	E_TRANS_NOTSUPPORT	= -(E_TRANS_BASE + 2),		// 无匹配交易
	E_TRANS_TIMEOUT		= -(E_TRANS_BASE + 3),		// 交易超时
	E_TRANS_NOMATE 		= -(E_TRANS_BASE + 4),		// 无交易记录
	E_TRANS_LOG_FULL	= -(E_TRANS_BASE + 5),		// 交易记录满
	E_TRANS_NO_LOG 		= -(E_TRANS_BASE + 6),		// 终端无交易日志
		
	E_FILE_BASE 		= 0x1000,					// 文件类错误定义
	E_FILE_OPEN			= -(E_FILE_BASE + 1),		// 文件打开失败
	E_FILE_RD 			= -(E_FILE_BASE + 2),		// 文件读取失败
	E_FILE_WR 			= -(E_FILE_BASE + 3),		// 文件写入失败
	E_FILE_CREAT		= -(E_FILE_BASE + 4),		// 创建文件失败
	E_FILE_REMOVE		= -(E_FILE_BASE + 5),		// 删除文件失败
	
	E_CARD_BASE 		= 0x2000,					// 卡片类错误定义
	E_CARD_FAILED			= -(E_CARD_BASE + 1),	// 读卡失败
	E_CARD_NEED_INSERT		= -(E_CARD_BASE + 2),	// 需要插卡交易
	E_CARD_NEED_KEYIN		= -(E_CARD_BASE + 3),	// 需要手输
	E_CARD_APP_BLOCKED		= -(E_CARD_BASE + 4),	// 应用锁定
	E_CARD_BLOCKER			= -(E_CARD_BASE + 5),	// 卡被锁定
	E_CARD_TRAN_DEFUSED 	= -(E_CARD_BASE + 6),	// 交易拒绝
	E_CARD_CARD_DEFUSED 	= -(E_CARD_BASE + 7),	// 交易承兑，卡片拒绝
	E_CARD_SCRIPT_FAIL		= -(E_CARD_BASE + 8),	// 脚本失败
	E_CARD_SET_PARAM_FAIL	= -(E_CARD_BASE + 9),	// 设置非接参数失败
	E_CARD_PRE_PROCESS_FAIL = -(E_CARD_BASE + 10),	// 非接预处理失败
	E_CARD_NEED_FALLBACK	= -(E_CARD_BASE + 11),	// 需要FALLBACK
	
	E_SCAN_BASE 		= 0x3000,					// 扫码类错误定义
	E_SCAN_INIT			= -(E_SCAN_BASE + 1),		// 初始化扫描枪失败
	E_SCAN_NO_FILE		= -(E_SCAN_BASE + 2),		// 没有查询文件
	E_SCAN_QUERY_TIMEOUT= -(E_SCAN_BASE + 3),		// 查询超时

	E_MANAGER_BASE		= 0x4000,					// 管理类错误定义
	E_NO_TELLER			= -(E_MANAGER_BASE+1),		// 无操作员

	E_COMM_BASE			= 0x5000,					// 通讯类错误定义
	E_COMM_INVALID_TYPE = -(E_COMM_BASE+1),			// 无效通讯类型
	E_COMM_INVALID_PROL = -(E_COMM_BASE+2),			// 无效通讯协议
	E_COMM_INVALID_HANDLE = -(E_COMM_BASE+3), 		// 无效通讯句柄
	E_COMM_NO_INIT 		= -(E_COMM_BASE+4),			// 未初始化
	E_COMM_INIT_FAILED  = -(E_COMM_BASE+5),			// 初始化失败
	E_COMM_CONNECT_CANCEL = -(E_COMM_BASE+6), 		// 退出连接
	E_COMM_CONNECT_FAILED = -(E_COMM_BASE+7), 		// 连接失败
	E_COMM_CLOSE_FAILED	= -(E_COMM_BASE+8), 		// 链路关闭失败
	E_COMM_SEND_FAILED =  -(E_COMM_BASE+9), 		// 发送失败
	E_COMM_RECV_FAILED =  -(E_COMM_BASE+10), 		// 接收失败
	E_COMM_RECV_TIMEOUT = -(E_COMM_BASE+11), 		// 接收失败
	E_COMM_PACK_WRONG = -(E_COMM_BASE+12),			// 组包失败
	E_COMM_UNPACK_WRONG = -(E_COMM_BASE+13),		// 解包失败
	E_COMM_DNS_FAILED = -(E_COMM_BASE+14),			// 域名解析失败
	//E_COMM_MSG_VERIFY	= -(E_COMM_BASE + 15),		// 报文校验失败
	E_COMM_MSG_CHKMAC	= -(E_COMM_BASE + 15),		// 报文MAC校验错误
	E_COMM_NO_SIM = -(E_COMM_BASE + 16),			// 无SIM卡
	E_COMM_GET_IP = -(E_COMM_BASE + 17),			// 获取IP错误
	E_COMM_WIFI_CONFIG = -(E_COMM_BASE + 18),		// WIFI参数配置失败

	E_PED_BASE 			= 0x6000,					// PED类错误定义
	E_PED_WRITE_KEY		= -(E_PED_BASE+1),			// 写密钥错误
	E_PED_CALC_MAC		= -(E_PED_BASE+2),			// MAC计算错误
	E_PED_LOAD_PINKEY	= -(E_PED_BASE+3),			// 装载PINKEY错误
	E_PED_LOAD_MACKEY	= -(E_PED_BASE+4),			// 装载MACKEY错误
	E_PED_LOAD_TDK		= -(E_PED_BASE+5),			// 装载TDK错误
	E_PED_GET_PINBLOCK	= -(E_PED_BASE+6),			// 获取pinblock失败
	E_PED_BYPASS		= -(E_PED_BASE+7),			// bypass

	E_PRT_BASE 			= 0x7000,					// 打印类错误定义
	E_PRT_NO_INIT		= -(E_PRT_BASE+1),			// 打印机未初始化
	E_PRT_INIT			= -(E_PRT_BASE+2),			// 打印机初始化失败
	E_PRT_PRN			= -(E_PRT_BASE+3),			// 打印失败
	E_PRT_NO_PAPER		= -(E_PRT_BASE+4),			// 打印机缺纸
	E_PRT_BUSY			= -(E_PRT_BASE+5),			// 打印机设备忙
	E_PRT_H_TEMP		= -(E_PRT_BASE+6),			// 打印机温度过高
	E_PRT_NO_BATTERY	= -(E_PRT_BASE+7),			// 打印机无电池
	E_PRT_REDO			= -(E_PRT_BASE+8),			// 需要重打
	E_PRT_UNKONW		= -(E_PRT_BASE+100),		// 打印机未知错误

	E_TMS_BASE			= 0x8000,					// TMS类
	E_TMS_NOT_REGISTER	= -(E_TMS_BASE+1),			// 未补登
	
	
	E_OTHER_BASE		= 0xF000,					// 其它类型错误
	E_NO_MEM			= -(E_OTHER_BASE+1),		// 内存不足
	E_APP_EXIT			= -(E_OTHER_BASE+2),		// 应用退出
	E_APP_FAILED		= -(E_OTHER_BASE+3),		// 应用出错
	E_NO_TRANS			= -(E_OTHER_BASE+4),		// 没有交易存在
	E_PW_WRONG			= -(E_OTHER_BASE+5),		// 密码错
	E_WIFI_CLOSED		= -(E_OTHER_BASE+6),		// WIFI未打开
	E_NOT_FIND			= -(E_OTHER_BASE+7),		// 无匹配项
	E_NO_BINLIST		= -(E_OTHER_BASE+8),		// 无bin表
	E_ELE_SIGN_FAILED	= -(E_OTHER_BASE+9),		// 电子签名失败
	E_REVERSE_FAIL      = -(E_OTHER_BASE+10),		// 冲正失败
	E_SCRIPT_FAIL      	= -(E_OTHER_BASE+11),		// 脚本失败
	E_ES_UPLOAD_FAIL    = -(E_OTHER_BASE+12),		// 电子签名上送失败
	
	
	W_BASE = 0x10000,								// 警告类

	I_BASE = 0x20000,								// 提示类
	I_NO_DISP = -(I_BASE+1),						// 无需提示
	I_SET_FAILED = -(I_BASE+2),						// 设置失败
	I_SET_CACEL = -(I_BASE+3),						// 设置取消
	I_NOT_BACK = -(I_BASE+4),						// 设置不退回上一层(菜单...)

	R_BASE = 0x40000								// 预留给应用自定义扩展信息
	
}E_APP_RET;

#endif
