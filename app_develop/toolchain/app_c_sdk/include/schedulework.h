/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app scheduleworkģ��</strong> ��صĽӿ�
	 * @par �ļ�    schedulework.h
	 * @author		yangjing
	 * @date        2020-09-29
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-09-29    | 1.0.0        | yangjing      | �����ļ�
	 * 2022-05-05    | 1.0.1        | lydia         | ����Ӣ��ע�� 
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app schedulework </strong>  module
	 * @par file    schedulework.h
	 * @author		yangjing
	 * @date        2020-09-29
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-09-29    | 1.0.0        | yangjing      | create file
	 * 2022-05-05    | 1.0.1        | lydia         | Add English description
 @endif 
*/

/*!
 @if Chinese
	@defgroup schedulework schedulework
 @else
	@defgroup schedulework schedulework
 @endif
 * @{
*/
#ifndef _SCHEDULE_WORK_H_
#define _SCHEDULE_WORK_H_

#include "workqueue.h"

/**
 @if Chinese
	* @brief 	��ʼ����������
	* @param[out]	work		-	��ʼ������ʵ��
	* @param[in]	workfunc	-	����ִ�е�������ָ��
	* @param[in]	workarg		-	����������ָ��
	* @return		0			-	�ɹ�
	* @return		����		-	ʧ��
 @else
	* @brief 	initialize work tasks
	* @param[out]	work		-	initialize task instance
	* @param[in]	workfunc	-	pointer to the task function where the work is executed
	* @param[in]	workarg		-	task function parameter pointer
	* @return		0			-	success
	* @return		other		-	fail
 @endif
*/ 
extern int init_work(ST_WORK_NODE *work, pWorkFunc workfunc, void *workarg);

/**
 @if Chinese
	* @brief 	�������������������߳���ִ��(��������������ȳ���˳��ִ��)
	* @param[in]	work		-	��ʼ��������ʵ��
	* @return		0			-	�ɹ�
	* @return		����		-	ʧ��
 @else
	* @brief 	assign tasks, which will be executed within the task thread (the assigned tasks will be executed in the order of first in first out)
	* @param[in]	work		-	initialize task instance
	* @return		0			-	success
	* @return		other		-	fail
 @endif
*/ 
extern int schedule_work(ST_WORK_NODE *work);

#endif

