/*!
 @if Chinese 
	 * @brief       ��ģ���������� <strong>app fileģ��</strong> ��صĽӿ�
	 * @par �ļ�    appfile.h
	 * @author		yangjing
	 * @date        2020-04-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * ����          | �汾       	| ����          | ����
	 * ------------- | -------------| --------------| ----
	 * 2020-04-09    | 1.0.0        | yanjing       | �����ļ�
	 * 2022-04-15    | 1.0.1        | lydia         | ����Ӣ��ע��  
 @else	 
	 * @brief       This module is used to describe the relevant interface of the <strong>app file </strong>  module
	 * @par file    appfile.h
	 * @author		yangjing
	 * @date        2020-04-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * Date          | Version      | Author        | Desc
	 * ------------- | -------------| --------------| ----
	 * 2020-04-09    | 1.0.0        | yanjing       | create file
	 * 2022-04-15    | 1.0.1        | lydia         | Add English description
 @endif 
*/
/*!
 @if Chinese
	@defgroup appfile �ļ�
 @else
	@defgroup appfile file
 @endif
 * @{
*/ 
#ifndef _APP_FILE_H_
#define _APP_FILE_H_

#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#include <appdatatypedef.h>

/*!
 @if Chinese
	@brief          ����Ӧ�ù���Ŀ¼��Ĭ��Ϊ/home/user0/app
	@param[in]      ppath	-	Ӧ�ù���Ŀ¼·����ΪNUL��ʹ��Ĭ��
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          set the working directory,default is /home/user0/app
	@param[in]      ppath	-	the working directory,NULL is default path
	@return         0		-	success
	@return         other	-	fail
 @endif
*/    
extern int app_file_set_workdir(const char *ppath);

/*!
 @if Chinese
	@brief          ��ȡ����Ŀ¼·��
	@param[out]     ppath	-	Ӧ�ù���Ŀ¼·��
	@param[in]      size	-	ppath��󳤶�
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          get the work directory
	@param[out]     ppath	-	the working directory
	@param[in]      size	-	the max length of ppath
	@return         0		-	success
	@return         other	-	fail
 @endif
*/ 
extern int app_file_get_workdir(char *ppath, int size);

/*!
 @if Chinese
	@brief          ��/�����ļ�
	@param[in]      pszFileName	-	�ļ���
	@param[in]      iFlag		-	��ģʽ, O_RDONLY O_RDWR O_CREAT ���
	@return         >=0		-	�ļ�������
	@return         ����	-	ʧ��
 @else
	@brief          open/create file
	@param[in]      pszFileName	-	file name
	@param[in]      iFlag		-	open mode, O_RDONLY O_RDWR O_CREAT
	@return         >=0		-	success,file descriptor
	@return         other	-	fail
 @endif
*/  
extern int app_file_open(const char *pszFileName, int iFlag);

/*!
 @if Chinese
	@brief          �ر��ļ�
	@param[in]      ifd		-	�ļ�������
 @else
	@brief          close file
	@param[in]      ifd		-	file descriptor
 @endif
*/  
extern void app_file_close(int ifd);

/*!
 @if Chinese
	@brief          ����ļ��Ƿ����
	@param[in]      pszFileName		-	�ļ���
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          Checking Whether the specified file exists
	@param[in]      pszFileName		-	file name
	@return         0		-	success
	@return         other	-	fail
 @endif
*/  
extern int app_file_exists(const char * pszFileName);

/*!
 @if Chinese
	@brief          ɾ���ļ�
	@param[in]      pszFileName		-	�ļ���
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          delete file
	@param[in]      pszFileName		-	file name
	@return         0		-	success
	@return         other	-	fail
 @endif
*/   
extern int app_file_remove(const char * pszFileName);

/*!
 @if Chinese
	@brief          �ļ��α��ƶ�
	@param[in]      ifd		-	�ļ�������
	@param[in]      move	-	�α�ƫ����
	@param[in]      whence	-	��ʼλ��
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          file cursor movement
	@param[in]      ifd		-	file descriptor
	@param[in]      move	-	cursor offset
	@param[in]      whence	-	Start position
	@return         0		-	success
	@return         other	-	fail
 @endif
*/  
extern int app_file_seek(int ifd, off_t move, int whence);

/*!
 @if Chinese
	@brief          ���ļ�����
	@param[in]      ifd		-	�ļ�������
	@param[out]     pvBuff	-	��ȡ���ݱ����ַ
	@param[in]      size	-	������ȡ����
	@return         >=0		-	ʵ�ʶ�ȡ����
	@return         ����	-	ʧ��
 @else
	@brief          Read file data from current position of specified file
	@param[in]      ifd		-	file descriptor
	@param[out]     pvBuff	-	Data buffer
	@param[in]      size	-	Length of data to read
	@return         >=0		-	success,length of data read
	@return         other	-	fail
 @endif
*/ 
extern int app_file_read(int ifd, void * pvBuff, int size);

/*!
 @if Chinese
	@brief          д���ļ�
	@param[in]      ifd		-	�ļ�������
	@param[in]      pvData	-	д������
	@param[in]      size	-	����д�����ݳ���
	@return         >=0		-	ʵ�ʶ�ȡ����
	@return         ����	-	ʧ��
 @else
	@brief          Write data to current position of specified file
	@param[in]      ifd		-	file descriptor
	@param[in]      pvData	-	Data buffer for writing
	@param[in]      size	-	Length of data to write
	@return         >=0		-	success,length of data writen
	@return         other	-	fail
 @endif
*/  
extern int app_file_write(int ifd, void * pvData, int size);

/*!
 @if Chinese
	@brief          ��ȡ�ļ���С
	@param[in]      pszFileName	-	�ļ���
	@return         >=0		-	�ļ���С(�ֽ�)
	@return         ����	-	ʧ��
 @else
	@brief          get file size
	@param[in]      pszFileName	-	file name
	@return         >=0		-	success,file size
	@return         other	-	fail
 @endif
*/   
extern int app_file_size(const char *pszFileName);

/*!
 @if Chinese
	@brief          �޸��ļ���С
	@param[in]      fd		-	�ļ�������
	@param[in]      length	-	�޸��ļ�����ֵ
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          modify file size
	@param[in]      fd		-	file descriptor
	@param[in]      length	-	modify file length
	@return         0		-	success
	@return         other	-	fail
 @endif
*/   
extern int app_file_ftruncate(int fd,off_t length);

/*!
 @if Chinese
	@brief          �������ļ�
	@param[in]      oldname		-	ԭ�ļ���
	@param[in]      newname		-	���ļ���
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          rename the data file
	@param[in]      oldname		-	old file name
	@param[in]      newname		-	new file name
	@return         0		-	success
	@return         other	-	fail
 @endif
*/    
extern int app_file_rename(const char *oldname,const char *newname);

/*!
 @if Chinese
	@brief          ���Ŀ¼�Ƿ����
	@param[in]      dir		-	Ŀ¼·��
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          check whether the directory exists
	@param[in]      dir		-	directory path
	@return         0		-	success
	@return         other	-	fail
 @endif
*/  
extern appbool app_file_checkappdir(const char *dir);

/*!
 @if Chinese
	@brief          ����Ŀ¼
	@param[in]      dir	-	Ŀ¼·��
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          creat directory
	@param[in]      dir	-	directory path
	@return         0		-	success
	@return         other	-	fail
 @endif
*/  
extern int app_file_creatappdir(const char *dir);

/*!
 @if Chinese
	@brief          ���Ŀ¼
	@param[in]      path	-	Ŀ¼·��
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          empty directory
	@param[in]      path	-	directory path
	@return         0		-	success
	@return         other	-	fail
 @endif
*/  
extern int app_file_cleardir(const char *path);

/*!
 @if Chinese
	@brief          ɾ��Ŀ¼(��Ŀ¼�ڲ�Ϊ�գ�����ɾ�����������Ŀ¼)
	@param[in]      dir	-	Ŀ¼·��
	@return         0		-	�ɹ�
	@return         ����	-	ʧ��
 @else
	@brief          delete directory
	@param[in]      dir	-	directory path
	@return         0		-	success
	@return         other	-	fail
 @endif
*/   
extern int app_file_rmappdir(const char *dir);

/*!
 @if Chinese
	@brief          ��Ŀ¼
	@param[in]      path	-	Ŀ¼·��
	@return         Ŀ¼�ṹ
 @else
	@brief          open directory
	@param[in]      path	-	directory path
	@return         directory structure
 @endif
*/    
extern DIR *app_file_opendir(const char *path);

/*!
 @if Chinese
	@brief          ��ȡĿ¼��Ϣ
	@param[in]      dir	-	Ŀ¼·��
	@return         Ŀ¼�ṹ
 @else
	@brief          read directory
	@param[in]      dir	-	directory path
	@return         directory structure
 @endif
*/     
extern struct dirent *app_file_readdir(DIR *dir);


/*!
 @if Chinese
	@brief          �ر�Ŀ¼
	@param[in]      dir	-	Ŀ¼·��
 @else
	@brief          close directory
	@param[in]      dir	-	directory path
 @endif
*/ 
extern void app_file_closedir(DIR *dir);


#endif

