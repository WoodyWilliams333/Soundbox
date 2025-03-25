/*
 * @Description: seos��ͷ�ļ�
 * @Author: YangJing
 * @Date: 2020-04-03 09:04:00
 * @LastEditors: YangJing
 * @LastEditTime: 2020-04-14 09:29:25
 */

#ifndef __SEOS_H__
#define __SEOS_H__

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */


#ifndef MAYBE_UNUSE
#define MAYBE_UNUSE(x)              (void)(x)
#endif

#ifndef UNUSE
#define UNUSE(x)                    (void)(x)
#endif

#ifndef __attribute_used__
#define __attribute_used__          __attribute__((__used__))
#endif

#ifndef __attribute_maybe_unused__
#define __attribute_maybe_unused__  __attribute__((__unused__)) 
#endif


/**
* @brief ����wnet�����־���أ�Ĭ���������־�رյ�
* @param[in] on     �����õ���־����״̬����0��ʾ�򿪣�Ϊ0��ʾ�رգ��� LOGGER_MODULE_ON ö�ٶ���
* @return ���ú����־����״̬
*	-<em> != 0 </em>  logger on
*	-<em> == 0 </em>  logger off
*/
extern int seos_logger_on(int on);


/**
* @brief ��ȡlibseos��İ汾��Ϣ
* @param[out] version��libwnet��İ汾��Ϣ���   
* @param[in]  size��versionִ�е�buffer���ȣ���������64�ֽ�    
* @return ��ȡ�Ľ��
*	-<em> == 0  </em>  �ɹ�
*	-<em> == -1 </em>  ʧ��
*/
extern int seos_get_version(char *version, int size);

#ifdef __cplusplus
}
#endif /* end of __cplusplus */

#endif /* end of __SEOS_H__ */

