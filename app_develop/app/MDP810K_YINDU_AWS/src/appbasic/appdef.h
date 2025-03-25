
#ifndef _APP_DEF_H_
#define _APP_DEF_H_

#include "apidef.h"

#ifndef CFG_4G_FLAG
#define CFG_4G_FLAG 
#endif

#ifndef DYNAMICPARAM
#define DYNAMICPARAM
#endif


#define APP_MAIN_VER		"V1.0.04_AWS01.09.59_APP"  //兼容MDP810移远模块的版本格式 MDP810和MDP810K只维护一个升级包
#define APP_SUB_VER			"20250104"
#define APP_PARAM_VERSION	"0001"

typedef enum{
	TRANS_CHANNEL = 0x01,
	TMS_CHANNEL
}COMM_CHANNEL;

typedef enum{
	NO_LOGIN = -1,
	SYS_MANAGER = 0,	//管理员密码
	SUP_MANAGER,		//主管密码
	TELLER
}E_TELLER_TYPE;

#define RESULT_DISP_TIME_MS 	200
#define RESULT_DISP_TIME 		3
#define MAX_DISP_TIME 			0x0FFFFFFF
#define CONFIRM_TIME 			1
#define MAX_TRANS_LOG_NUM		100

#define SYS_TELLER_NO	"099"   ////系统管理员
#define SUP_TELLER_NO	"000"
#define TELLER_NOBODY	"\x01\x01\x01"	
#define TELLER_LOCK		"\x02\x01\x01"	

#define MAX_APP_NUM		  32		 //EMV库最大AID个数
#define MAX_KEY_NUM       64         //EMV库认证最大公钥个数
#define PART_MATCH        0x01       //应用选择匹配标志(部分匹配)
#define FULL_MATCH        0x00       //应用选择匹配标志(完全匹配)

#define  HAVE_INPUT_PIN	  '1'
#define  NOT_INPUT_PIN	  '2'

#define MAX_KEY_INDEX 90 //91用作最大TDK，92-99应用保留使用，不提供给用户

#define  PIN_KEY_ID		(stTransPara.ucKeyIndex)  //+1	//工作密钥索引关联主密钥
#define  MAC_KEY_ID		(stTransPara.ucKeyIndex)  //+1
#define  TDK_KEY_ID     (stTransPara.ucKeyIndex+1)  //+2  //磁道加密密钥
#define  TEST_KEY_ID	(90)	


//#define  EMV_PIN_KEY_ID  31    // 脱机明文PIN KEY ID

#define  DOUBLE_PIN_KEY_ID  PIN_KEY_ID
#define  DOUBLE_MAC_KEY_ID  MAC_KEY_ID
#define  DOUBLE_TDK_KEY_ID  TDK_KEY_ID   // 磁道加密密钥

#define CARDBIN_A	0x01
#define CARDBIN_B	0x02
#define CARDBIN_C	0x03

#define MAX_BLACKLIST_NUM    500

#define FORCE_NONEEDPIN		3
#define FREE_NONEED_PIN 	2
#define NEED_PIN		1

#define   TS_ELECSIGN_HAVE   0x20    // 有电子签名
#define   TS_ELECSIGN_UP     0x02    // 电子签名需要上送
#define   INV_TXN_INDEX			   0xFF000000	  // 无效的最后后面一个字节8bit标识交易类型

//说明，请勿暂用低4位，低4位用来表明上送失败的次数
#define TS_NEEDTC			    0x4000		// EMV交易需要TC上送
#define TS_NEEDUPLOAD			0x2000		// 没有批次上送
#define TS_TXN_OFFLINE			0x1000		// 磁条卡的离线交易需要上送 
#define TS_ICC_OFFLINE          0x0800      // ICC卡的离线交易需要上送
#define TS_ELECSIGN_TXN         0x0400      // 电子签名交易需要上送
#define TS_ELECSIGN_FAIL_TXN    0x0200      // 电子签名交易上送失败

//批结算状态
#define  NOLOG				0
#define	 RMBLOG				1
#define  FRNLOG				2
#define  ALLLOG				3
#define  EMVLOG				4

//POS工作状态
#define  WORK_STATUS         '0'
#define  BATCH_STATUS		 '1'
#define  SETTLE_STATUS		 '2'	

//密钥算法类型
#define KEY_MODE_DES      '1'
#define KEY_MODE_3DES     '0'

#define CHECK_UPDATE_APP_TIME_QUICK		1
#define CHECK_UPDATE_APP_TIME_DEFAULT	10*60
#define CHECK_UPDATE_APP_DISABLE		-1

#define App_Lcd_Lan 1 //1 for English,0 for Chinese

#define APP_FILE_PATH           "/home/user0/"APP_NAME
#define HOME_DIR                "/home/user0"
#define MP3_DIR             "mp3"
#define OTA_DIR             "ota"
#define MP3_TMP_DIR         "tmpmp3"  //用于语音下载暂时存储目录
#define OTA_FILE_PATA       "MDP810K" //用于提取ota升级包判断
 


#define OTA_TEMP_FILE             "ota_tmp.pkg"
#define AUDIO_TEMP_FILE             "aud_tmp.pkg"


//#define UPLOAD_AUDIOPLAY_RESULT //是否上送播报结果
#define UPLOAD_DEV_INFO         //是否上送设备信息



#define MQTT_CA_CERT   "rootCA.crt"
#define MQTT_CLIENT_CERT   "client.crt"
#define MQTT_CLIENT_KEY   "key.pem"



#endif

