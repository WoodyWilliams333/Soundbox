
#ifndef _APP_DEF_H_
#define _APP_DEF_H_

#include "apidef.h"

#ifndef CFG_4G_FLAG
#define CFG_4G_FLAG 
#endif

#ifndef DYNAMICPARAM
#define DYNAMICPARAM
#endif


#define APP_MAIN_VER		"V1.0.04_AWS01.09.59_APP"  //����MDP810��Զģ��İ汾��ʽ MDP810��MDP810Kֻά��һ��������
#define APP_SUB_VER			"20250104"
#define APP_PARAM_VERSION	"0001"

typedef enum{
	TRANS_CHANNEL = 0x01,
	TMS_CHANNEL
}COMM_CHANNEL;

typedef enum{
	NO_LOGIN = -1,
	SYS_MANAGER = 0,	//����Ա����
	SUP_MANAGER,		//��������
	TELLER
}E_TELLER_TYPE;

#define RESULT_DISP_TIME_MS 	200
#define RESULT_DISP_TIME 		3
#define MAX_DISP_TIME 			0x0FFFFFFF
#define CONFIRM_TIME 			1
#define MAX_TRANS_LOG_NUM		100

#define SYS_TELLER_NO	"099"   ////ϵͳ����Ա
#define SUP_TELLER_NO	"000"
#define TELLER_NOBODY	"\x01\x01\x01"	
#define TELLER_LOCK		"\x02\x01\x01"	

#define MAX_APP_NUM		  32		 //EMV�����AID����
#define MAX_KEY_NUM       64         //EMV����֤���Կ����
#define PART_MATCH        0x01       //Ӧ��ѡ��ƥ���־(����ƥ��)
#define FULL_MATCH        0x00       //Ӧ��ѡ��ƥ���־(��ȫƥ��)

#define  HAVE_INPUT_PIN	  '1'
#define  NOT_INPUT_PIN	  '2'

#define MAX_KEY_INDEX 90 //91�������TDK��92-99Ӧ�ñ���ʹ�ã����ṩ���û�

#define  PIN_KEY_ID		(stTransPara.ucKeyIndex)  //+1	//������Կ������������Կ
#define  MAC_KEY_ID		(stTransPara.ucKeyIndex)  //+1
#define  TDK_KEY_ID     (stTransPara.ucKeyIndex+1)  //+2  //�ŵ�������Կ
#define  TEST_KEY_ID	(90)	


//#define  EMV_PIN_KEY_ID  31    // �ѻ�����PIN KEY ID

#define  DOUBLE_PIN_KEY_ID  PIN_KEY_ID
#define  DOUBLE_MAC_KEY_ID  MAC_KEY_ID
#define  DOUBLE_TDK_KEY_ID  TDK_KEY_ID   // �ŵ�������Կ

#define CARDBIN_A	0x01
#define CARDBIN_B	0x02
#define CARDBIN_C	0x03

#define MAX_BLACKLIST_NUM    500

#define FORCE_NONEEDPIN		3
#define FREE_NONEED_PIN 	2
#define NEED_PIN		1

#define   TS_ELECSIGN_HAVE   0x20    // �е���ǩ��
#define   TS_ELECSIGN_UP     0x02    // ����ǩ����Ҫ����
#define   INV_TXN_INDEX			   0xFF000000	  // ��Ч��������һ���ֽ�8bit��ʶ��������

//˵�����������õ�4λ����4λ������������ʧ�ܵĴ���
#define TS_NEEDTC			    0x4000		// EMV������ҪTC����
#define TS_NEEDUPLOAD			0x2000		// û����������
#define TS_TXN_OFFLINE			0x1000		// �����������߽�����Ҫ���� 
#define TS_ICC_OFFLINE          0x0800      // ICC�������߽�����Ҫ����
#define TS_ELECSIGN_TXN         0x0400      // ����ǩ��������Ҫ����
#define TS_ELECSIGN_FAIL_TXN    0x0200      // ����ǩ����������ʧ��

//������״̬
#define  NOLOG				0
#define	 RMBLOG				1
#define  FRNLOG				2
#define  ALLLOG				3
#define  EMVLOG				4

//POS����״̬
#define  WORK_STATUS         '0'
#define  BATCH_STATUS		 '1'
#define  SETTLE_STATUS		 '2'	

//��Կ�㷨����
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
#define MP3_TMP_DIR         "tmpmp3"  //��������������ʱ�洢Ŀ¼
#define OTA_FILE_PATA       "MDP810K" //������ȡota�������ж�
 


#define OTA_TEMP_FILE             "ota_tmp.pkg"
#define AUDIO_TEMP_FILE             "aud_tmp.pkg"


//#define UPLOAD_AUDIOPLAY_RESULT //�Ƿ����Ͳ������
#define UPLOAD_DEV_INFO         //�Ƿ������豸��Ϣ



#define MQTT_CA_CERT   "rootCA.crt"
#define MQTT_CLIENT_CERT   "client.crt"
#define MQTT_CLIENT_KEY   "key.pem"



#endif

