/*
 * @Description: app������壬�������㣬 �����������Ӵ����壬����Ԥ�����������Զ������
 * @Author: YangJing
 * @Date: 2020-04-07 09:36:37
 * @LastEditors: YangJing
 * @LastEditTime: 2020-04-10 14:23:00
 */

#ifndef _APP_ERR_DEF_H_
#define _APP_ERR_DEF_H_



typedef enum{
	RET_OK = 0,
		
	E_TRANS_BASE 		= 1,						// �����������
	E_TRANS_CANCEL		= -(E_TRANS_BASE),			// ����ȡ��
	E_TRANS_FAILED		= -(E_TRANS_BASE + 1),		// ����ʧ��
	E_TRANS_NOTSUPPORT	= -(E_TRANS_BASE + 2),		// ��ƥ�佻��
	E_TRANS_TIMEOUT		= -(E_TRANS_BASE + 3),		// ���׳�ʱ
	E_TRANS_NOMATE 		= -(E_TRANS_BASE + 4),		// �޽��׼�¼
	E_TRANS_LOG_FULL	= -(E_TRANS_BASE + 5),		// ���׼�¼��
	E_TRANS_NO_LOG 		= -(E_TRANS_BASE + 6),		// �ն��޽�����־
		
	E_FILE_BASE 		= 0x1000,					// �ļ��������
	E_FILE_OPEN			= -(E_FILE_BASE + 1),		// �ļ���ʧ��
	E_FILE_RD 			= -(E_FILE_BASE + 2),		// �ļ���ȡʧ��
	E_FILE_WR 			= -(E_FILE_BASE + 3),		// �ļ�д��ʧ��
	E_FILE_CREAT		= -(E_FILE_BASE + 4),		// �����ļ�ʧ��
	E_FILE_REMOVE		= -(E_FILE_BASE + 5),		// ɾ���ļ�ʧ��
	
	E_CARD_BASE 		= 0x2000,					// ��Ƭ�������
	E_CARD_FAILED			= -(E_CARD_BASE + 1),	// ����ʧ��
	E_CARD_NEED_INSERT		= -(E_CARD_BASE + 2),	// ��Ҫ�忨����
	E_CARD_NEED_KEYIN		= -(E_CARD_BASE + 3),	// ��Ҫ����
	E_CARD_APP_BLOCKED		= -(E_CARD_BASE + 4),	// Ӧ������
	E_CARD_BLOCKER			= -(E_CARD_BASE + 5),	// ��������
	E_CARD_TRAN_DEFUSED 	= -(E_CARD_BASE + 6),	// ���׾ܾ�
	E_CARD_CARD_DEFUSED 	= -(E_CARD_BASE + 7),	// ���׳жң���Ƭ�ܾ�
	E_CARD_SCRIPT_FAIL		= -(E_CARD_BASE + 8),	// �ű�ʧ��
	E_CARD_SET_PARAM_FAIL	= -(E_CARD_BASE + 9),	// ���÷ǽӲ���ʧ��
	E_CARD_PRE_PROCESS_FAIL = -(E_CARD_BASE + 10),	// �ǽ�Ԥ����ʧ��
	E_CARD_NEED_FALLBACK	= -(E_CARD_BASE + 11),	// ��ҪFALLBACK
	
	E_SCAN_BASE 		= 0x3000,					// ɨ���������
	E_SCAN_INIT			= -(E_SCAN_BASE + 1),		// ��ʼ��ɨ��ǹʧ��
	E_SCAN_NO_FILE		= -(E_SCAN_BASE + 2),		// û�в�ѯ�ļ�
	E_SCAN_QUERY_TIMEOUT= -(E_SCAN_BASE + 3),		// ��ѯ��ʱ

	E_MANAGER_BASE		= 0x4000,					// �����������
	E_NO_TELLER			= -(E_MANAGER_BASE+1),		// �޲���Ա

	E_COMM_BASE			= 0x5000,					// ͨѶ�������
	E_COMM_INVALID_TYPE = -(E_COMM_BASE+1),			// ��ЧͨѶ����
	E_COMM_INVALID_PROL = -(E_COMM_BASE+2),			// ��ЧͨѶЭ��
	E_COMM_INVALID_HANDLE = -(E_COMM_BASE+3), 		// ��ЧͨѶ���
	E_COMM_NO_INIT 		= -(E_COMM_BASE+4),			// δ��ʼ��
	E_COMM_INIT_FAILED  = -(E_COMM_BASE+5),			// ��ʼ��ʧ��
	E_COMM_CONNECT_CANCEL = -(E_COMM_BASE+6), 		// �˳�����
	E_COMM_CONNECT_FAILED = -(E_COMM_BASE+7), 		// ����ʧ��
	E_COMM_CLOSE_FAILED	= -(E_COMM_BASE+8), 		// ��·�ر�ʧ��
	E_COMM_SEND_FAILED =  -(E_COMM_BASE+9), 		// ����ʧ��
	E_COMM_RECV_FAILED =  -(E_COMM_BASE+10), 		// ����ʧ��
	E_COMM_RECV_TIMEOUT = -(E_COMM_BASE+11), 		// ����ʧ��
	E_COMM_PACK_WRONG = -(E_COMM_BASE+12),			// ���ʧ��
	E_COMM_UNPACK_WRONG = -(E_COMM_BASE+13),		// ���ʧ��
	E_COMM_DNS_FAILED = -(E_COMM_BASE+14),			// ��������ʧ��
	//E_COMM_MSG_VERIFY	= -(E_COMM_BASE + 15),		// ����У��ʧ��
	E_COMM_MSG_CHKMAC	= -(E_COMM_BASE + 15),		// ����MACУ�����
	E_COMM_NO_SIM = -(E_COMM_BASE + 16),			// ��SIM��
	E_COMM_GET_IP = -(E_COMM_BASE + 17),			// ��ȡIP����
	E_COMM_WIFI_CONFIG = -(E_COMM_BASE + 18),		// WIFI��������ʧ��

	E_PED_BASE 			= 0x6000,					// PED�������
	E_PED_WRITE_KEY		= -(E_PED_BASE+1),			// д��Կ����
	E_PED_CALC_MAC		= -(E_PED_BASE+2),			// MAC�������
	E_PED_LOAD_PINKEY	= -(E_PED_BASE+3),			// װ��PINKEY����
	E_PED_LOAD_MACKEY	= -(E_PED_BASE+4),			// װ��MACKEY����
	E_PED_LOAD_TDK		= -(E_PED_BASE+5),			// װ��TDK����
	E_PED_GET_PINBLOCK	= -(E_PED_BASE+6),			// ��ȡpinblockʧ��
	E_PED_BYPASS		= -(E_PED_BASE+7),			// bypass

	E_PRT_BASE 			= 0x7000,					// ��ӡ�������
	E_PRT_NO_INIT		= -(E_PRT_BASE+1),			// ��ӡ��δ��ʼ��
	E_PRT_INIT			= -(E_PRT_BASE+2),			// ��ӡ����ʼ��ʧ��
	E_PRT_PRN			= -(E_PRT_BASE+3),			// ��ӡʧ��
	E_PRT_NO_PAPER		= -(E_PRT_BASE+4),			// ��ӡ��ȱֽ
	E_PRT_BUSY			= -(E_PRT_BASE+5),			// ��ӡ���豸æ
	E_PRT_H_TEMP		= -(E_PRT_BASE+6),			// ��ӡ���¶ȹ���
	E_PRT_NO_BATTERY	= -(E_PRT_BASE+7),			// ��ӡ���޵��
	E_PRT_REDO			= -(E_PRT_BASE+8),			// ��Ҫ�ش�
	E_PRT_UNKONW		= -(E_PRT_BASE+100),		// ��ӡ��δ֪����

	E_TMS_BASE			= 0x8000,					// TMS��
	E_TMS_NOT_REGISTER	= -(E_TMS_BASE+1),			// δ����
	
	
	E_OTHER_BASE		= 0xF000,					// �������ʹ���
	E_NO_MEM			= -(E_OTHER_BASE+1),		// �ڴ治��
	E_APP_EXIT			= -(E_OTHER_BASE+2),		// Ӧ���˳�
	E_APP_FAILED		= -(E_OTHER_BASE+3),		// Ӧ�ó���
	E_NO_TRANS			= -(E_OTHER_BASE+4),		// û�н��״���
	E_PW_WRONG			= -(E_OTHER_BASE+5),		// �����
	E_WIFI_CLOSED		= -(E_OTHER_BASE+6),		// WIFIδ��
	E_NOT_FIND			= -(E_OTHER_BASE+7),		// ��ƥ����
	E_NO_BINLIST		= -(E_OTHER_BASE+8),		// ��bin��
	E_ELE_SIGN_FAILED	= -(E_OTHER_BASE+9),		// ����ǩ��ʧ��
	E_REVERSE_FAIL      = -(E_OTHER_BASE+10),		// ����ʧ��
	E_SCRIPT_FAIL      	= -(E_OTHER_BASE+11),		// �ű�ʧ��
	E_ES_UPLOAD_FAIL    = -(E_OTHER_BASE+12),		// ����ǩ������ʧ��
	
	
	W_BASE = 0x10000,								// ������

	I_BASE = 0x20000,								// ��ʾ��
	I_NO_DISP = -(I_BASE+1),						// ������ʾ
	I_SET_FAILED = -(I_BASE+2),						// ����ʧ��
	I_SET_CACEL = -(I_BASE+3),						// ����ȡ��
	I_NOT_BACK = -(I_BASE+4),						// ���ò��˻���һ��(�˵�...)

	R_BASE = 0x40000								// Ԥ����Ӧ���Զ�����չ��Ϣ
	
}E_APP_RET;

#endif
