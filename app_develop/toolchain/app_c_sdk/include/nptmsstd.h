/*
 * @Description: 
 *      TMS�������˵��:
 *          1.tms�����������Ͷಽ���ģʽ��ʵ�ָ�tms���׹���:
 *            ÿ��tms������һ����������������������������������ִ�С�
 *            ÿ�������ֳַ�һ�������ɸ�������ִ�У�ÿ�������ʱ���̡�
 *            ͨ��������ģʽ�ﵽtms���׹���(�첽��ʽʱ)�пɼ�ʱ��Ӧ�ⲿ�����Ч��
 *            ��ע: ���ڵײ�connect�ӿڵ��������⣬��tcp�����쳣��ʱʱ�޷��ﵽ��ʱ��Ӧ��Ч���������������.
 *          2.tms���Ϊͬ�����첽���ַ�ʽ��
 *              1)ͬ����ʽʱ�����ýӿ�����ִ�����
 *              2)�첽��ʽʱ��tms������һ���߳�����ɣ��˷�ʽ�ɼ�ʱ��Ӧ����tms�ӿ�
 *              3)ͬ�����첽��ʽ��tms��ʼ�����ã��Ҳ��ɸ���
 *          3.�첽��ʽʱ��tms�������������ȼ��������ȼ��ߵĽӿڵ��ú󣬻�������ִ�еĵ����ȼ����ס�
 *            ���ȼ���������: quit = delete > register = checkupdte = download
 * @Author: YangJing
 * @Date: 2021-03-17 11:51:54
 * @LastEditors: YangJing
 * @LastEditTime: 2021-04-19 15:54:36
 */

#ifndef __NP_TMS_STD_H__
#define __NP_TMS_STD_H__

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stdlib.h>

enum TMS_COMM_SELECT {    
    SOLTNO_GPRS = 0,
    SOLTNO_WIFI = 1,
    SOLTNO_CDMA = 2, //reserved !!!
};  // TMSͨѶ��ʽ

enum TMS_IP_DNS {
    TMS_IN_IP  = 0,
    TMS_IN_DNS = 1,
}; // ʹ��ip����dns����������ʽ

enum TMS_WORK_MODE {
    TMS_IN_SYNC  = 0,
    TMS_IN_ASYNC = 1,
}; // ͬ��/�첽ģʽ

enum TMS_ASYNC_MODE {
    TMS_IN_SHOW  = 0,
    TMS_IN_SILENCE = 1,
    TMS_IN_SILENCE_FORBID = 2,  // ��ֹ��Ĭ��ǿ����ʾ
}; // �첽ģʽʱ���Ƿ���ʾTMS����

enum TMS_FLAG {
    TMS_FLAG_FALSE = 0,
    TMS_FLAG_TRUE = 1,
    TMS_FLAG_NOW = 2,
}; // nptsm��ٺ궨��

typedef enum {
    TMS_REGISTER = 2050,            // ����
    TMS_CHECK_UPDATE = 2020,        // Ѳ��
    TMS_REMOTE_DOWNLOAD = 2000,     // ����
    TMS_DOWNLOADED_NOTICE = 2010,   // ����֪ͨ

    TMS_QUIT = 3001,                // �˳�/�жϵ�ǰ����
    TMS_DELETE,                     // ɾ������
    TMS_UPDATE,                     // ����Ӧ��
}tms_trans_code_e; // ��������

typedef enum {
    TASK_REGISTER = 1,
    TASK_CHECKUPDATE,
    TASK_DOWNLOAD,
    TASK_DOWNLOADED_NOTICE,
    TASK_QUIT,
    TASK_DELETE,
    TASK_UPDATE,

    // ���ع����е�������
    TASK_DL_SHARKHANDS = 0x100,
    TASK_DL_VERIFY_REQ,
    TASK_DL_VERIFY_RESP,
    TAKS_DL_GET_LIST,
    TAKS_DL_ANASLYSE_LIST,
    TASK_DL_LOADING,
    TASK_DL_FINISH,
}task_id_e; //��������

#define TMS_MAX_IP_LEN              32
#define TMS_MAX_DNS_LEN             256
#define TMS_MAX_IN_LEN              100

#define TMS_MAX_REMARKS_LEN         256
// #define LEN_RSP_CODE            2

typedef struct _np_tms_respone_t {
    int errcode;                                // ִ�н��
    int rspcode;                                // ��̨��Ӧ���
    uint8_t newverflag;                         // �°汾��ʶ��ֵΪTMS_FLAG_TRUE��ʾ���°汾Ӧ�ô�����
    uint8_t updateflag;                         // �ɸ��±�ʶ��ֵΪTMS_FLAG_TRUE��ʾ�������,��ִ�и���
    uint8_t updateabsolutely;                   // ǿ�Ƹ��±�ʶ, ֵΪTMS_FLAG_TRUE��ʾǿ�Ƹ���
    char newverremark[TMS_MAX_REMARKS_LEN];     // �°汾��ע��Ϣ
} np_tms_respone_t;                             // tms����Ӧ��ص�����


typedef int (*pnptmsrespcb)(np_tms_respone_t *, void *arg); 

typedef struct _np_tms_param_t {
    // �����ò�������ʼ����nptms_config�ӿھ������ò���
    char            ip[TMS_MAX_IP_LEN];         // tmsͨѶ����, ipdnsΪTMS_IN_DNSʱ��Ч
    char            dns[TMS_MAX_DNS_LEN];       // tmsͨѶip, ipdnsΪTMS_IN_IPʱ��Ч
    unsigned short        port;                 // tmsͨѶ�˿� 
    unsigned short        timeout;              // ͨѶ�����ճ�ʱʱ��(ms)����С100ms
    unsigned short        spacelimit;           // �������ش洢�ռ�(kb),��С100kb
    unsigned char         comm_type; 			// see enum TMS_COMM_SELECT
    unsigned char         ipdns; 				// see enum TMS_IP_DNS
    unsigned char         asyncmode;            // see enum TMS_WORK_MODE
    unsigned char         silence;              // see enum TMS_ASYNC_MODE
    
    // ��ʼ��ʱ�����ò���
    const char*     appdir;                     // Ӧ�ù���Ŀ¼
    int             (*autoruncb)(void *);       // ��Ĭ�Զ����к���(��ʱʱ�������Ѳ���)
    unsigned int    silenceperoid;              // ��Ĭ����ִ������,��λ��s),��С6Сʱ
    // pnptmsrespcb    silenrespcb;             // ��Ĭʱ�Զ�Ѳ���Ĵ���

    // ���²���Ϊ�����, Ӧ�ò����������²���
    // int             async_dl_run;            // �첽�����Ƿ���������
} np_tms_param_t;

/**
 * @brief: tms������ʼ��
 * @return 
 *      0   -   �ɹ�
 *      ���� -  ʧ��
 * @param 
 *  {np_tms_param_t} *para  �����ṹ����ϸ��np_tms_param_t����
 */
extern int nptms_init(np_tms_param_t *para);

/**
 * @brief:  ����tms��Ĭ����ֻ����ʹ���첽ģʽʱ��Ч 
 * @return
 *      0   -   �ɹ�
 *      ���� -  ʧ��
 * @param {none}
 */
extern int nptms_start_server(void);

/**
 * @brief:  TMS���ǣ����ǽ�����ݸ�cb�ص��� 
 * @return
 *      0   -   �ɹ�
 *      ���� -  ʧ��
 * @param 
 *      {pnptmsrespcb} cb   ִ�н��֪ͨ�ص�����
 * @param 
 *      {void} *arg     �ص���������
 */
extern int nptms_register(pnptmsrespcb cb, void *arg);

/**
 * @brief:  TMS���ǣ����ǽ�����ݸ�cb�ص��� 
 * @return
 *      0   -   �ɹ�
 *      ���� -  ʧ��
 * @param 
 *      {pnptmsrespcb} cb   ִ�н��֪ͨ�ص�����
 * @param 
 *      {void} *arg     �ص���������
 */
extern int nptms_checkupdate(pnptmsrespcb cb, void *arg);

/**
 * @brief:  TMS���أ����ؽ�����ݸ�cb�ص��� 
 * @return
 *      0   -   �ɹ�
 *      ���� -  ʧ��
 * @param 
 *      {pnptmsrespcb} cb   ִ�н��֪ͨ�ص�����
 * @param 
 *      {void} *arg     �ص���������
 */
extern int nptms_download(pnptmsrespcb cb, void *arg);

/**
 * @brief:  TMS���£����½�����ݸ�cb�ص��� 
 * @return
 *      0   -   �ɹ�
 *      ���� -  ʧ��
 * @param 
 *      {pnptmsrespcb} cb   ִ�н��֪ͨ�ص�����
 * @param 
 *      {void} *arg     �ص���������
 */
extern int nptms_update(pnptmsrespcb cb, void *arg);

/**
 * @brief:  TMSɾ�����أ�������ݸ�cb�ص��� 
 * @return
 *      0   -   �ɹ�
 *      ���� -  ʧ��
 * @param 
 *      {pnptmsrespcb} cb   ִ�н��֪ͨ�ص�����
 * @param 
 *      {void} *arg     �ص���������
 */
extern int nptms_delete_dl(pnptmsrespcb cb, void *arg);

/**
 * @brief:  �˳���ǰTMS���� 
 * @return
 *      0   -   �ɹ�
 *      ���� -  ʧ��
 * @param 
 *      {pnptmsrespcb} cb   ִ�н��֪ͨ�ص�����
 * @param 
 *      {void} *arg     �ص���������
 */
extern int nptms_quit(pnptmsrespcb cb, void *arg);

/**
 * @brief:  tms��������, np_tms_param_t�ڿ����õĲ�������Ч
 *          ��һ�����ö����������arraynum�������ò�����Ŀ
 * @return
 *      0   -   �ɹ�
 *      ���� -  ʧ��
 * @param 
 *      {const char**} namearary ���ò������ƴ����飬���ò��������Ƽ�np_tms_param_t�ڵĳ�Ա�������ַ���
 * @param 
 *      {const void **} valuearray һ��ָ�����ò���ֵ��ָ������, ��ָ������� �ϸ��� ���ò��������� ��ƥ��! 
 * @param 
 *      {int} arraynum ���ò����ĸ�������namearary��valuearray����Ĵ�С
 */
extern int nptms_config(const char **namearary, const void **valuearray, int arraynum);

/**
 * @brief:  ��ȡ������string��
 * @return 
 *      {char *}  ���ص�string��ָ�룬stringΪconst char[], ����Ҫ�ͷţ�Ҳ�����޸�!
 * @param 
 *      {int} code ������
 */
extern const char* nptms_get_errcode_string(int code);

/**
 * @brief:  ��ȡ��̨Ӧ����string��
 * @return
 *      {char *}  ���ص�string��ָ�룬stringΪconst char[], ����Ҫ�ͷţ�Ҳ�����޸�!
 * @param 
 *      {int} code  Ӧ����
 */
extern const char* nptms_get_respcode_string(int code);

/**
 * @brief:  ��ȡ��汾��Ϣ
 * @return
 *      0   -   �ɹ�
 *      ���� -  ʧ��
 * @param 
 *      {char} *version     �汾��Ϣ�����ַ
 * @param 
 *      {int} size          version��С
 */
extern int nptms_get_version(char* version, int size);

#ifdef __cplusplus
}
#endif /* endof __cplusplus */

#endif
