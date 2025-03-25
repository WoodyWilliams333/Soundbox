/*
 * @Description: 
 * @Author: YangJing
 * @Date: 2021-04-22 08:39:44
 * @LastEditors: YangJing
 * @LastEditTime: 2021-05-13 08:32:57
 */

#ifndef _NP_TMS_DISPLYAER_H_
#define _NP_TMS_DISPLYAER_H_

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

typedef struct {
    int missiontotallen;                // ��ǰ�����ܳ���
    int missiondownloadlen;             // ��ǰ���������س���
    int totallen;                       // �����ܳ���
    int downloadlen;                    // �������ܳ���
}notifydl_st;

typedef struct {
    int errcode;                       // ���½��
}notifyupdate_st;

typedef struct {
    int transid;                        // TMS����id
    int taskid;                         // ����id
    int step;                           // ����id
    int state;                          // ����״̬
    int leftms;                         // ����ִ��ʣ��ʱ��
    const char *modname;                // ģ������
    int missionid;                      // ģ��id

    union {
        notifydl_st dlinfo;             // ������Ϣ             
        notifyupdate_st updateinfo;     // ������Ϣ
    } curinfo;
}notifypara_st;

typedef void (*recv_state_change)(notifypara_st *); // �۲��߽���֪ͨ�ص�

typedef struct {
    recv_state_change recver;    
}displayerobv_st;   // ��ʾ�۲��߽ṹ

/**
 * @brief: ��ȡTMS��������
 * @return {none}
 * @param 
 *      {int} transid   tms����id
 * @param 
 *      {char} *name    �������ƻ����ַ
 * @param 
 *      {int} size      �����С
 */
extern void nptms_get_trans_name(int transid, char *name, int size);

/**
 * @brief: ��ȡTMS��������
 * @return {none}
 * @param 
 *      {int} taskid    tms����id
 * @param 
 *      {char} *name    �������ƻ����ַ
 * @param 
 *      {int} size      �����С
 */
extern void nptms_get_task_name(int taskid, char *name, int size);

/**
 * @brief: ��ȡTMS����������
 * @return {none}
 * @param 
 *      {int} step   tms������id
 * @param 
 *      {char} *name    ���������ƻ����ַ
 * @param 
 *      {int} size      �����С
 */
extern void nptms_get_step_name(int step, char *name, int size);

/**
 * @brief: ע����ʾ�۲��ߣ�Ŀǰ��֧��һ���۲���
 * @return
 *      0   -   �ɹ�
 *      ���� -  ʧ��
 * @param 
 * {displayerobv_st} *obv Ҫע��۲��߽ṹָ��
 */
extern int nptms_registedisplayer(displayerobv_st *obv);    

#ifdef __cplusplus
}
#endif /* endof __cplusplus */

#endif
