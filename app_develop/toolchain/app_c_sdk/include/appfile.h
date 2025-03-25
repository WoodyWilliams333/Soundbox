/*!
 @if Chinese 
	 * @brief       此模块用于描述 <strong>app file模块</strong> 相关的接口
	 * @par 文件    appfile.h
	 * @author		yangjing
	 * @date        2020-04-09
	 * @version     V1.0
	 * @remarks     Change History:
	 * 日期          | 版本       	| 作者          | 描述
	 * ------------- | -------------| --------------| ----
	 * 2020-04-09    | 1.0.0        | yanjing       | 创建文件
	 * 2022-04-15    | 1.0.1        | lydia         | 增加英文注释  
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
	@defgroup appfile 文件
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
	@brief          设置应用工作目录，默认为/home/user0/app
	@param[in]      ppath	-	应用工作目录路径，为NUL则使用默认
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          获取工作目录路径
	@param[out]     ppath	-	应用工作目录路径
	@param[in]      size	-	ppath最大长度
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          打开/创建文件
	@param[in]      pszFileName	-	文件名
	@param[in]      iFlag		-	打开模式, O_RDONLY O_RDWR O_CREAT 组合
	@return         >=0		-	文件描述符
	@return         其它	-	失败
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
	@brief          关闭文件
	@param[in]      ifd		-	文件描述符
 @else
	@brief          close file
	@param[in]      ifd		-	file descriptor
 @endif
*/  
extern void app_file_close(int ifd);

/*!
 @if Chinese
	@brief          检测文件是否存在
	@param[in]      pszFileName		-	文件名
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          删除文件
	@param[in]      pszFileName		-	文件名
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          文件游标移动
	@param[in]      ifd		-	文件描述符
	@param[in]      move	-	游标偏移量
	@param[in]      whence	-	起始位置
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          读文件内容
	@param[in]      ifd		-	文件描述符
	@param[out]     pvBuff	-	读取数据保存地址
	@param[in]      size	-	期望读取长度
	@return         >=0		-	实际读取长度
	@return         其它	-	失败
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
	@brief          写入文件
	@param[in]      ifd		-	文件描述符
	@param[in]      pvData	-	写入数据
	@param[in]      size	-	期望写入数据长度
	@return         >=0		-	实际读取长度
	@return         其它	-	失败
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
	@brief          获取文件大小
	@param[in]      pszFileName	-	文件名
	@return         >=0		-	文件大小(字节)
	@return         其它	-	失败
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
	@brief          修改文件大小
	@param[in]      fd		-	文件描述符
	@param[in]      length	-	修改文件长度值
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          重命名文件
	@param[in]      oldname		-	原文件名
	@param[in]      newname		-	新文件名
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          检测目录是否存在
	@param[in]      dir		-	目录路径
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          创建目录
	@param[in]      dir	-	目录路径
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          清空目录
	@param[in]      path	-	目录路径
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          删除目录(若目录内不为空，不能删除，需先清空目录)
	@param[in]      dir	-	目录路径
	@return         0		-	成功
	@return         其它	-	失败
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
	@brief          打开目录
	@param[in]      path	-	目录路径
	@return         目录结构
 @else
	@brief          open directory
	@param[in]      path	-	directory path
	@return         directory structure
 @endif
*/    
extern DIR *app_file_opendir(const char *path);

/*!
 @if Chinese
	@brief          读取目录信息
	@param[in]      dir	-	目录路径
	@return         目录结构
 @else
	@brief          read directory
	@param[in]      dir	-	directory path
	@return         directory structure
 @endif
*/     
extern struct dirent *app_file_readdir(DIR *dir);


/*!
 @if Chinese
	@brief          关闭目录
	@param[in]      dir	-	目录路径
 @else
	@brief          close directory
	@param[in]      dir	-	directory path
 @endif
*/ 
extern void app_file_closedir(DIR *dir);


#endif

