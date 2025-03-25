
/**
@if Chinese
 * @brief       ��ģ���������� <strong>����ϵͳ�ź���ģ��</strong> ��ؽӿ�
 * @note
 * @par �ļ�    semaphore.h
 * @author
 * @date        2019/01/28
 * @version     1.0.0
 * @remarks     Change History:
 * ����          | ����          | ����
 * ------------- | --------------- | ----
 * 2019/01/28    | liluchang       | �����ļ�
 * 2022/04/21    | Wenming         | ����Ӣ��ע��
@else 
 * @brief       This module is used to describe <strong>Operating system semaphores</strong> interfaces module
 * @note
 * @par File    semaphore.h
 * @author
 * @date        2019/01/28
 * @version     1.0.0
 * @remarks     Change History:
 * Date          | Author          | Desc
 * ------------- | --------------- | ----
 * 2019/01/28    | liluchang       | Create file
 * 2022/04/21    | Wenming         | Add English description
@endif
*/


/**
@if Chinese
 * @defgroup os_semaphore �ź���
@else 
 * @defgroup os_semaphore Semaphore
@endif 
 * @ingroup os_service
 * @{
*/

#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef void *sem_handle_t;                     /**<@if Chinese �ź���������� @else Semaphore operation handle @endif*/

/**
@if Chinese
 * @name �źŵȴ�״̬
@else 
 * @name semaphore Wait option
@endif	 
 * @{
 */
#define SEM_OPT_NO_WAIT         0x0             /**<@if Chinese û�еȴ��ź��� @else no wait for semaphore 		@endif*/
#define SEM_OPT_WAIT_FOREVER    0xFFFFFFFF      /**<@if Chinese һֱ�ȴ��ź��� @else wait for semaphore forever @endif*/
/** @} */

/**
@if Chinese
 * @brief �����ź���
 * @param[in] name_ptr          -	�ź���������
 * @param[in] initial_count     -	�ź�����ʼ������
 * @retval �ǿ� -�����ɹ�	
 * @retval  �� 	-����ʧ��.
@else  
 * @brief os api, create semaphore
 * @param[in] name_ptr          -	the name of semaphore
 * @param[in] initial_count     -	initial counter of semaphore
 * @retval non-NULL	-	semaphore create ok
 * @retval	NULL	-	Faild.
@endif 
 */
sem_handle_t os_create_sem(const char *name_ptr, uint32_t initial_count);

/**
@if Chinese
 * @brief ɾ���ź���
 * @param[in] sem    -	�ź������
 * @retval 	0	-	�ź�ɾ���ɹ� 	 
 * @retval  <0	-	�ź�ɾ��ʧ��.
@else  
 * @brief os api, delete semaphore
 * @param[in] sem    the handle of semaphore
 * @retval 	0	-	semaphore delete ok
 * @retval  <0	-	Faild.
@endif 
 */
int os_delete_sem(sem_handle_t sem);

/**
@if Chinese
 * @brief ��ȡ�ź���
 * @param[in] sem			-	�ź������
 * @param[in] wait_option	-	�ȴ�ѡ���μ� SEM_OPT_NO_WAIT��SEM_OPT_WAIT_FOREVER�궨�塣
 * @retval	0	-	��ȡ�ɹ�
 * @retval	<0	-	��ȡʧ��.
@else 
 * @brief os api, get a semaphore
 * @param[in] sem           -	the handle of semaphore
 * @param[in] wait_option	-	Wait options, see SEM_OPT_NO_WAIT or SEM_OPT_WAIT_FOREVER macro definitions
 * @retval	0	-	semaphore get ok
 * @retval  <0	-	Faild.
@endif	 
 */
int os_get_sem(sem_handle_t sem, uint32_t wait_option);

/**
@if Chinese
 * @brief �׳�һ���ź���
 * @param[in] sem    -	�ź������
 * @retval	0	-	��ȡ�ɹ�
 * @retval  <0	-	��ȡʧ��.
@else  
 * @brief os api, put a semaphore
 * @param[in] sem    -	the handle of semaphore
 * @retval	0	-	semaphore put ok
 * @retval  <0	-	Faild.
@endif	 
 */
int os_put_sem(sem_handle_t sem);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SEMAPHORE_H__ */

/** @} */

