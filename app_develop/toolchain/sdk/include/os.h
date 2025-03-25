
/**
 @if Chinese
 * @brief       ��ģ���������� <strong>����ϵͳģ��</strong> ��ؽӿ�
 * @note
 * @par �ļ�    os.h
 * @author		Wenming
 * @date          2019/01/28
 * @version       1.0.1
 * @remarks        Change History:
 * ����          | ����            | ����
 * ------------- | --------------- | ----
 * 2019/01/28    | liluchang       | �����ļ�
 * 2022/04/21    | Wenming         | ����Ӣ��ע��
@else 
 * @brief       This module is used to describe <strong>Operating System</strong> interfaces module
 * @note
 * @par File    os.h
 * @author		Wenming
 * @date          2019/01/28
 * @version       1.0.1
 * @remarks        Change History:
 * Date          | Author          | Desc
 * ------------- | --------------- | ----
 * 2019/01/28    | liluchang       | Create file
 * 2022/04/21    | Wenming         | Add English description
@endif 
*/


/**
@if Chinese
 * @defgroup os_service ����ϵͳ
@else 
 * @defgroup os_service Operating System
@endif
 * @{
*/

#ifndef __OS_H__
#define __OS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
@if Chinese
	*@brief  ���̺߳ͻ���������ؽӿ� 
@else	
	*@brief  Multithreading and mutex related interfaces 
@endif
*/
#include "os_pthread.h"

/**
@if Chinese
	*@brief  ��ʱ����ؽӿ� 
@else	
	*@brief  Timer related interfaces 
@endif	
*/
#include "timer.h"

/**
@if Chinese
	*@brief �ź�����ؽӿ� 
@else	
	*@brief Semaphore correlation interface
@endif	
*/
#include "semaphore.h"

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __OS_H__ */

/** @} */
