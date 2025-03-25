
#ifndef __NP_TMS_H__
#define __NP_TMS_H__

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stdlib.h>
#include "tms_silence.h"


#define MAX_IP_LEN              16
#define MAX_DNS_LEN             32
#define MAX_IN_LEN              16
#define MAX_REMARK_INFO_LEN     256

enum TMS_LANGUAGE {
    DISP_IN_CHINESE = 0,
    DISP_IN_ENGLISE = 1,
};

enum TMS_COMM_SELECT {    
    SOLTNO_GPRS = 0,
    SOLTNO_WIFI = 1,
    SOLTNO_CDMA = 2, //reserved !!!
};

enum TMS_IP_DNS {
    TMS_IN_IP  = 0,
    TMS_IN_DNS = 1,
};

enum TMS_PARAM_IN {
    TMS_PARAM_INVALID_IN = 0,
    TMS_PARAM_VALID_IN   = 1,    
};

enum TMS_PARAM_OUT {
    TMS_PARAM_NO_RETURN  = 0,
    TMS_PARAM_RETURN     = 1,    
};

//TMS error list
enum TMS_ERROR_CODE {
    TMS_E_OK                = 0,    //���׳ɹ�
    TMS_E_PACKET            = -1,   //���ʧ��
    TMS_E_CONNECT           = -2,   //����ʧ��
    TMS_E_SEND              = -3,   //����ʧ��
    TMS_E_RECV              = -4,   //����ʧ��
    TMS_E_RECV_TIMEOUT      = -5,   //���ճ�ʱ
    TMS_E_UNPACKET          = -6,   //���ʧ��
    TMS_E_RSPCODE           = -7,   //��������� //��ʱ����ʹ��
    TMS_E_DNS               = -8,   //��������ʧ��
    TMS_E_DELETE            = -9,   //ɾ��ʧ��
    TMS_E_GPRS_DEV          = -10,  //ͨѶ�豸������
    TMS_E_PPP_LOGIN         = -11,  //PPP��¼ʧ��
    TMS_E_PPP_TIMEOUT       = -12,  //PPP��ʱ
    TMS_E_NO_SIM            = -13,  //SIM��δ����
    TMS_E_DOWNLOAD          = -14,  //TMS����ʧ�ܣ�ͨ��Ϊ���ڲ���������ʧ��
    TMS_E_DOWNLOAD_CANCEL   = -15,  //TMS����ȡ��
    TMS_E_WIFI_DISC         = -16,  //WIFIδ���ӻ�����ʧ��
    TMS_E_NO_REGISTER       = -17,  //�ն�δ��ʼ����δִ�в��ǽ���
    TMS_E_DESKTOP_FILE      = -18,  //Desktop file�����ڻ򲻺Ϸ�
    TMS_E_WIFI_CLOSE        = -19,  //WIFI�豸δ��
    TMS_E_COMM_DEV          = -20,  //ͨѶ�豸�쳣
    TMS_E_RSPCODE_BASE      = -50,  //TMS��̨������������� -51��ʾ������Ϊ"01"��-66��ʾ������Ϊ"16"
    TMS_E_RSPCODE_END       = -100, //ͬ��
    TMS_E_NO_DISP           = -127, //����ʾ��Ϣ������ʹ��
    TMS_E_UNKNOW            = -128, //δ֪����
};

typedef struct _np_tms_param_t {
    char        ip[MAX_IP_LEN];
    char        dns[MAX_DNS_LEN];
    uint16_t    port; 
    uint16_t    timeout;
    uint8_t     language; //see enum TMS_LANGUAGE
    uint8_t     comm_type; //see enum TMS_COMM_SELECT
    uint8_t     ipdns; //see enum TMS_IP_DNS
    char        apn[MAX_IN_LEN];
    char        user[MAX_IN_LEN];
    char        passwd[MAX_IN_LEN];
} np_tms_param_t;

/*
���ñ���tms�����Ļص�����������������ʵ�֣��������ܴ����ļ�ϵͳ�У�Ҳ���ܴ��������ط�
*/
typedef int (*save_tms_param)(void *arg);

extern int tms_main(np_tms_param_t *param, int paramvalidin, int paramreturn, save_tms_param cb);

/////////////////////////////////////////////////////////////////////////////////////////////

//extern API for APP-TMS call

/*
����Ӧ�ó�����TMS�⴫��ͨѶ��������ʹ�ÿ��Ĭ�ϲ������ɴ���NULL
��tms app deinit�ӿ�����ʹ��
����0��ʾ�ɹ���������ʾʧ��
*/
int tms_app_init(void *param, int paramvalidin);

/*
����TMS����Ӧ�ó��򵼳�ͨѶ����������տ�������棬�������ã��ɴ���NULL
��tms app init�ӿ�����ʹ��
����0��ʾ�ɹ���������ʾʧ��
*/
int tms_app_deinit(void *param, int paramreturn);

/*
������������ֵΪ0�����ǳɹ�
�����������Ϊ����ʧ��
*/
int tms_app_terminal_register(void);

/*
������������ֵΪ0����ʾ��ѯ�ɹ�����ѯ�ɹ�������2�ֿ���:
1.��ѯ�ɹ�����Ӧ����Ҫ���ظ���: ��ʱupdateflg������ֵΪ1���أ���remarkinfo�����ش�����Ӧ�õı�ע��Ϣ(������Ϣ)
2.��ѯ�ɹ�����ǰ�汾�����°汾: ��ʱupdateflg������ֵΪ0���أ�remarkinfo�����ݿɺ���
�����������Ϊ��ѯʧ��
ע��: remarkinfo����Ч�ռ�����256�ֽ�
*/
int tms_app_check_update(int *updateflg, char *remarkinfo);

int tms_app_check_update_ex(int *updateflg, char *remarkinfo);//ȥ����ʾ


typedef struct _tms_update_result_t {
    int done;           //�첽�����Ƿ���ɣ�Ӧ�ò�����ڷ����첽����ǰ��մ˱�־����������󣬽���ص�����λ�˱�־
    int ret;            //���ڱ���tms���׵ķ���ֵ����ö�� TMS_ERROR_CODE
    int updateflg;      //���ڱ��浱ǰӦ���Ƿ���Ҫ���ظ���, 1��ʾ��Ҫ���ظ��£�����ֵ��ʾ����Ҫ
    char remarkinfo[MAX_REMARK_INFO_LEN]; //���ڱ���������·���Ӧ�õİ汾������Ϣ������256�ֽ�
} tms_update_result_t;



typedef int (*tms_result_cb)(tms_update_result_t *result);

/*
������������ֵΪ0����ʾ�����첽����ɹ�
void *argĿǰ�������ɴ���NULL
tms_result_cb cb���ڱ���tms������Ϣ����Ļص�
ע������:
Ӧ�÷����첽�����ڴ��ۿ���ʱ�䣬�ɲ�ѯ����Ƿ��з��أ���������Ӧ����Ҫ���ظ��£���
�ٴε���Զ�����ؽӿڽ�������
*/
int tms_app_check_update_async(void *arg, tms_result_cb cb);

/*
������������ֵΪ0ʱ����ʾ���سɹ����˺�����װ�����ء����µ�������̣�
��˳���Ļ����ӽ������أ���һֱ����ʾ�������£���Ϊǿ�Ƹ��¡�
�����������Ϊ����ʧ��
*/
int tms_app_download(void);

int tms_app_update_single(void);


/*
������������ֵΪ0ʱ����ʾ������ȫ���� ���˺���ִ�����ֻ������أ�

���ؽ�����tms_update_tasks_ex���Ѹ������������̡�

��������ֵ����Ϊ����ʧ��
*/
int tms_app_download_ex(void);

//int tms_update_tasks_ex(void);//TMS�������� ʹ��ǰ���ж��Ƿ������ˮδ����


void checkstop(void);

int checkShow(void);

/*
����0��ʾ�ɹ���������ʾʧ��
*/
int tms_app_delete_tmp_files(void);

/*
��Ӧ�Ĳ�������NULL, ��ʾ����ȡ����汾��Ϣ��ÿһ�����Чbuf��������16�ֽ�
����0��ʾ�ɹ���������ʾʧ��
*/
int tms_app_get_versions(char *appname, char *appver, char *libtmsver);

/*
�Ƿ�ʹ��tms���ع����У����а�ȡ�����˳�����
����0��ʾ������ȡ��������ֵ��ʾ����ȡ����Ĭ��Ϊ������ȡ��
*/
void tms_app_download_cancel_enable(int enable);

/*
��ȡtms��İ汾�ţ�version�Ŀռ�����32�ֽ�
*/
int tms_app_get_tms_version(char *version, int nbytes);

/*
��ȡ����ֵret����ĺ��壬�ֱ���������ʾ��Ӣ����ʾ������buf����32�ֽ�
����ֵ˵��:
����0ʱ���ɴ�msgcn��msgen��ȡ����ʾ��msg;
������1���ɴ�msgcn��msgen��ȡ����ʾ��msg����ʱ�ն˲��ǽ���Ҳ�ǳɹ��ģ�Ӧ����Ҫ���ɹ���ʾ
������-1����ʾ�˷������ʾ������ʾ;
*/
int tms_app_get_result_disp(int ret, char *msgcn, char *msgen);

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif /* endof __cplusplus */

#endif
