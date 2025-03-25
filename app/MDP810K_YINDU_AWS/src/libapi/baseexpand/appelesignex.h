/*
 * @Description: ����ǩ����ع��ܽӿ�
 * @Author: YangJing
 * @Date: 2020-04-03 14:08:40
 * @LastEditors: YangJing
 * @LastEditTime: 2020-04-10 09:59:04
 */

#ifndef _APP_ELE_SIGN_EX_
#define _APP_ELE_SIGN_EX_

#include <libposts.h>

/**
 * @description: ��ȡ����ǩ��
 * @param[in]: 
 *      es_info ����ǩ����Ϣ����ϸ��ο�����ǩ���ⶨ��
 * @param[out]: none
 * @return: 
 *      0-�ɹ�
 *      ����-ʧ��
 */
extern int app_posts_get_elec_sign(const tp_elec_signature_t *es_info);

/**
 * @description: jbg�ļ�תbmp�ļ�
 * @param[in]: 
 *      appPath-Ӧ�ù���Ŀ¼
 *      jbgfile-jbg�ļ���
 *      bmpfile-bmp�ļ���
 * @param[out]: 
 *      iBmpWidth-bmpͼƬ���
 *      iBmpHeight-bmpͼƬ�߶�
 * @return:
 *      0-�ɹ�
 *      ����-ʧ��
 */
extern int app_posts_jbg2bmp(const char *appPath ,const char *jbgfile, const char *bmpfile,int *iBmpWidth,int *iBmpHeight);

/**
 * @description: jbg����תbmp�ļ�
 * @param[in]: 
 *      appPath-Ӧ�ù���Ŀ¼
 *      jbgdat-jbg����
 *      jbglen-jbg���ݳ���
 *      bmpfile-bmp�ļ���
 * @param[out]:
 *      iBmpWidth-bmpͼƬ���
 *      iBmpHeight-bmpͼƬ�߶�
 * @return:
 *      0-�ɹ�
 *      ����-ʧ��
 */
extern int app_posts_jbgdat2bmp(const char *appPath ,const unsigned char *jbgdat, int jbglen, const char *bmpfile,int *iBmpWidth,int *iBmpHeight);

#endif
