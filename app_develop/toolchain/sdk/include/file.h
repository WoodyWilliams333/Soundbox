
/**
 @if Chinese
	 * @brief    ��ģ���������� <strong>�ļ�ϵͳģ��</strong> ��صĽӿ�
	 * @author   liluchang
	 * @date     2019-01-24
	 * @version  V1.0
	 * @remarks Change History:
	 * Date          | Version       | Author          | Desc
	 * ------------- | ------------- | --------------- | -----------
	 * 2019/01/24    | 1.0.0         | liluchang       | �����ļ�
	 * 2022/04/20    | 1.0.1         | Wenming         | ����Ӣ��ע��
 @else
	 * @brief    This module is used to describe <strong>File System</strong> interfaces module
	 * @author   liluchang
	 * @date     2019-01-24
	 * @version  V1.0
	 * @remarks Change History:
	 * Date          | Version       | Author          | Desc
	 * ------------- | ------------- | --------------- | -----------
	 * 2019/01/24    | 1.0.0         | liluchang       | Create file
	 * 2022/04/20    | 1.0.1         | Wenming         | Add English description
 @endif
*/

/**
 @if Chinese
	* @defgroup FS �ļ�ϵͳ
 @else	
	* @defgroup FS FileSystem
 @endif	
 * @{
 */

#ifndef __FILE_H__
#define __FILE_H__

#include "sys/types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 @if Chinese
	 * @brief   <strong> �ļ�ϵͳ����<span style="color:red">ʾ��</span>����<span style="color:red">(������ô˽ӿ�)</span></strong>
	 * @retval  ��
	 * @note    <span style="color:red"> <strong> ������Ӧ�õ��ýӿڣ�����ʾ������ο���������� </strong> </span>
	 * @par     ʾ��:
	 * @code

	#include <stdio.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <errno.h>
	#include <string.h>

	//���ļ�
	//oflag֧����������: O_CREAT/O_RDONLY/O_WRONLY/O_RDWR/O_TRUNC/O_APPEND
	int file_open(const char *pathname, int oflag)
	{
		int fd = -1;

		printf("pathname = %s flag = %X O_CREAT = %X\n", pathname, oflag, O_CREAT);

		if( (oflag & O_CREAT) != 0) {
			printf("creat or open file\n");
			fd = open(pathname, oflag, 0664); //0664�ɺ��ԣ��ײ��ļ�ϵͳ������ʵ�ʴ���������
		}
		else {
			printf("open file\n");
			fd = open(pathname, oflag);
		}

		return fd;
	}

	//�ر��ļ�
	int file_close(int fd)
	{
		return close(fd);
	}

	//�ļ���дλ��ƫ�ƣ��µĶ�дλ��Ϊ: ��WhenceΪ����ģ�ƫ����ΪOffset��λ��
	int file_seek(int fd, uint32_t Offset, int Whence)
	{
		return lseek(fd, Offset, Whence);
	}

	//���ļ��ж�ȡ����
	int file_read(int fd, void *databuf, int len)
	{
		return read(fd, databuf, len);
	}

	//���ļ���д����
	int file_write(int fd, const void *databuf, int len)
	{
		return write(fd, databuf, len);
	}

	//�ļ��ضϣ��ضϺ�ĳ���Ϊlen�ֽ�
	int file_truncate(int fd, int len)
	{
		return ftruncate(fd, len);
	}

	//�ļ�ˢ�£��ײ��ݲ�֧�ִ˲���
	int file_flush(int fd)
	{
		return 0;
	}

	//�ļ����ڷ���1���ļ������ڷ���0
	int file_exist(const char *pathname)
	{
		return !access(pathname, F_OK) ? 1 : 0;
	}

	//��ȡ�ļ��Ĵ�С�����ظ�����ʾʧ�ܣ�
	int file_get_size(const char *pathname)
	{
		int fd = -1, ret = -1;

		do{
			fd = open(pathname, O_RDONLY);
			if(fd < 0){
				printf("open fail, ret=%d, errno=%d\n", ret, errno);
				break;
			}

			ret = lseek(fd, 0, SEEK_END);
			if (ret < 0) {
				printf("lseek ret=%d, errno=%d\n", ret, errno);
			}

			close(fd);
		}while(0);

		return ret;
	}

	//ɾ���ļ�
	int file_remove(const char *pathname)
	{
		return remove(pathname);
	}

	//�����ļ�����
	int file_rename(const char *oldname, const char *newname)
	{
		return rename(oldname, newname);
	}

	//�ļ�ϵͳ�Ĳ������
	int fs_module_test(void)
	{
		int retval = 0;
		int fd;
		const char tmp_data[] = "++++++++++++++++";
		int tmp_data_len = strlen(tmp_data);
		const char file_data[] = "0123456789abcdef0123456789abcdef0123456789abcdef";
		int file_data_len = strlen(file_data);
		char file_read_buf[128];
		const char *tmp1_file = "/home/user0/tmp1.log";
		const char *tmp2_file = "/home/user0/tmp2.log";

		retval = file_get_size("/home/sbin/download.bin");
		printf("download.bin file size = %d\n", retval);

		if (file_exist(tmp1_file)) {
			printf("open exist file ...\n");
			fd = file_open(tmp1_file, O_RDWR);
		} else {
			printf("create new file ...\n");
			fd = file_open(tmp1_file, O_CREAT|O_RDWR);
		}

		if (fd < 0) {
			printf("open file fail, retval=%d, errno=%d\n", retval, errno);
			retval = -1;
			goto exit_entry;
		}

		//���ļ���д���������
		retval = file_write(fd, file_data, file_data_len);
		printf("write file, retval=%d\n", retval);

		//��Դ�ļ��Ķ�дָ���Ƶ���ʼλ��
		retval = file_seek(fd, 0, SEEK_SET);
		printf("seek file, retval=%d\n", retval);

		//��ȡд����ļ�����
		memset(file_read_buf, 0, sizeof(file_read_buf));
		retval = file_read(fd, file_read_buf, sizeof(file_read_buf));
		printf("read file, retval=%d\n", retval);

		//�ȶԶ��������ݺ�д�������
		printf("read-data-1: %s\n", file_read_buf);
		if (file_data_len != retval ||
			memcmp(file_read_buf, file_data, file_data_len)) {
			printf("read data mismatched !!!\n");
		} else {
			printf("read data OK !!!\n");
		}

		//��Դ�ļ��Ķ�дָ���Ƶ����ļ�β��λ����ǰƫ��16���ֽ�
		retval = file_seek(fd, -16, SEEK_END);
		printf("seek file, retval=%d\n", retval);

		//����д��һ�β�������

		//���ļ���д���������
		retval = file_write(fd, tmp_data, tmp_data_len);
		printf("write file 2, retval=%d\n", retval);

		//��Դ�ļ��Ķ�дָ���Ƶ���ʼλ��
		retval = file_seek(fd, 0, SEEK_SET);
		printf("seek file 2, retval=%d\n", retval);

		//��ȡд����ļ�����
		memset(file_read_buf, 0, sizeof(file_read_buf));
		retval = file_read(fd, file_read_buf, sizeof(file_read_buf));
		printf("read file 2, retval=%d\n", retval);

		//�ȶԶ��������ݺ�д�������
		printf("read-data-2: %s\n", file_read_buf);
		if (file_data_len != retval ||
			memcmp(file_read_buf, file_data, file_data_len - tmp_data_len) ||
			memcmp(file_read_buf + file_data_len - tmp_data_len, tmp_data, tmp_data_len)) {
			printf("read data mismatched !!!\n");
		} else {
			printf("read data OK !!!\n");
		}

		//ˢ��һ���ļ�����
		retval = file_flush(fd);
		printf("flush file, retval=%d, errno=%d\n", retval, errno);

		//�ر��ļ�
		retval = file_close(fd);
		printf("close file, retval=%d, errno=%d\n", retval, errno);

		//�ļ�����������
		if (file_exist(tmp2_file)) {
			//��tmp2_file����ʱ��rename�ᱨ��errno=17��������Ҫ��ɾ��tmp2_file
			retval = file_remove(tmp2_file);
			printf("remove file2, retval=%d, errno=%d\n", retval, errno);

			retval = file_rename(tmp1_file, tmp2_file);
			printf("rename file, retval=%d, errno=%d\n", retval, errno);
		} else {
			retval = file_rename(tmp1_file, tmp2_file);
			printf("rename file, retval=%d, errno=%d\n", retval, errno);
		}

		//��ȡ�µ��ļ�����
		retval = file_get_size(tmp2_file);
		printf("%s file size = %d, errno=%d\n", tmp2_file, retval, errno);

		//ɾ���ļ�
		retval = file_remove(tmp2_file);
		printf("remove file, retval=%d, errno=%d\n", retval, errno);

	exit_entry:
		return retval;
	}

	#if 0 //��־���ʾ��
	download.bin file size = 466600
	create new file ...
	pathname = /home/user0/tmp1.log flag = 202 O_CREAT = 200
	creat or open file
	write file, retval=48
	seek file, retval=0
	read file, retval=48
	read-data-1: 0123456789abcdef0123456789abcdef0123456789abcdef
	read data OK !!!
	seek file, retval=32
	write file 2, retval=16
	seek file 2, retval=0
	read file 2, retval=48
	read-data-2: 0123456789abcdef0123456789abcdef++++++++++++++++
	read data OK !!!
	flush file, retval=0, errno=2
	close file, retval=0, errno=2
	rename file, retval=0, errno=2
	/home/user0/tmp2.log file size = 48, errno=2
	remove file, retval=0, errno=2
	#endif

	 @endcode
@else
	 
	 * @brief   <strong> File system Operations <span style="color:red">the sample </span>Source<span style="color:red">(do not call this interface)</span></strong>
	 * @retval  none
	 * @note    <span style="color:red"> <strong> Abnormal application call interface, only for example code reference, do not call </strong> </span>
	 * @par     The sample:
	 * @code

	#include <stdio.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <errno.h>
	#include <string.h>

	//Open file system
	//oflag: O_CREAT/O_RDONLY/O_WRONLY/O_RDWR/O_TRUNC/O_APPEND
	int file_open(const char *pathname, int oflag)
	{
		int fd = -1;

		printf("pathname = %s flag = %X O_CREAT = %X\n", pathname, oflag, O_CREAT);

		if( (oflag & O_CREAT) != 0) {
			printf("creat or open file\n");
			fd = open(pathname, oflag, 0664); //0664Negligible, the underlying file system does not actually create its properties
		}
		else {
			printf("open file\n");
			fd = open(pathname, oflag);
		}

		return fd;
	}

	//Close file
	int file_close(int fd)
	{
		return close(fd);
	}

	//The file read/write position is Offset. The new read/write position is based on Whence and the Offset is Offset
	int file_seek(int fd, uint32_t Offset, int Whence)
	{
		return lseek(fd, Offset, Whence);
	}

	//Read info from the file system
	int file_read(int fd, void *databuf, int len)
	{
		return read(fd, databuf, len);
	}

	//Write content into a document
	int file_write(int fd, const void *databuf, int len)
	{
		return write(fd, databuf, len);
	}

	//The file is truncated, and the truncated length is len bytes
	int file_truncate(int fd, int len)
	{
		return ftruncate(fd, len);
	}

	//File refresh. This operation is not supported by the underlying layer
	int file_flush(int fd)
	{
		return 0;
	}

	//Returns 1 if the file exists and 0 if the file does not exist
	int file_exist(const char *pathname)
	{
		return !access(pathname, F_OK) ? 1 : 0;
	}

	//Get the size of the file, return a negative number to indicate failure,
	int file_get_size(const char *pathname)
	{
		int fd = -1, ret = -1;

		do{
			fd = open(pathname, O_RDONLY);
			if(fd < 0){
				printf("open fail, ret=%d, errno=%d\n", ret, errno);
				break;
			}

			ret = lseek(fd, 0, SEEK_END);
			if (ret < 0) {
				printf("lseek ret=%d, errno=%d\n", ret, errno);
			}

			close(fd);
		}while(0);

		return ret;
	}

	//Delete file
	int file_remove(const char *pathname)
	{
		return remove(pathname);
	}

	//Update file name
	int file_rename(const char *oldname, const char *newname)
	{
		return rename(oldname, newname);
	}

	//File system test entry
	int fs_module_test(void)
	{
		int retval = 0;
		int fd;
		const char tmp_data[] = "++++++++++++++++";
		int tmp_data_len = strlen(tmp_data);
		const char file_data[] = "0123456789abcdef0123456789abcdef0123456789abcdef";
		int file_data_len = strlen(file_data);
		char file_read_buf[128];
		const char *tmp1_file = "/home/user0/tmp1.log";
		const char *tmp2_file = "/home/user0/tmp2.log";

		retval = file_get_size("/home/sbin/download.bin");
		printf("download.bin file size = %d\n", retval);

		if (file_exist(tmp1_file)) {
			printf("open exist file ...\n");
			fd = file_open(tmp1_file, O_RDWR);
		} else {
			printf("create new file ...\n");
			fd = file_open(tmp1_file, O_CREAT|O_RDWR);
		}

		if (fd < 0) {
			printf("open file fail, retval=%d, errno=%d\n", retval, errno);
			retval = -1;
			goto exit_entry;
		}

		//Write test data to a file
		retval = file_write(fd, file_data, file_data_len);
		printf("write file, retval=%d\n", retval);

		//Moves the read/write pointer to the source file to the starting position
		retval = file_seek(fd, 0, SEEK_SET);
		printf("seek file, retval=%d\n", retval);

		//Read written file data
		memset(file_read_buf, 0, sizeof(file_read_buf));
		retval = file_read(fd, file_read_buf, sizeof(file_read_buf));
		printf("read file, retval=%d\n", retval);

		//Compares read data with written data
		printf("read-data-1: %s\n", file_read_buf);
		if (file_data_len != retval ||
			memcmp(file_read_buf, file_data, file_data_len)) {
			printf("read data mismatched !!!\n");
		} else {
			printf("read data OK !!!\n");
		}

		//Moves the read/write pointer to the source file 16 bytes forward from the end of the file
		retval = file_seek(fd, -16, SEEK_END);
		printf("seek file, retval=%d\n", retval);

		//Write a new piece of test data

		//Write test data to a file
		retval = file_write(fd, tmp_data, tmp_data_len);
		printf("write file 2, retval=%d\n", retval);

		//Moves the read/write pointer to the source file to the starting position
		retval = file_seek(fd, 0, SEEK_SET);
		printf("seek file 2, retval=%d\n", retval);

		//Read written file data
		memset(file_read_buf, 0, sizeof(file_read_buf));
		retval = file_read(fd, file_read_buf, sizeof(file_read_buf));
		printf("read file 2, retval=%d\n", retval);

		//Compares read data with written data
		printf("read-data-2: %s\n", file_read_buf);
		if (file_data_len != retval ||
			memcmp(file_read_buf, file_data, file_data_len - tmp_data_len) ||
			memcmp(file_read_buf + file_data_len - tmp_data_len, tmp_data, tmp_data_len)) {
			printf("read data mismatched !!!\n");
		} else {
			printf("read data OK !!!\n");
		}

		//Refresh the file operation
		retval = file_flush(fd);
		printf("flush file, retval=%d, errno=%d\n", retval, errno);

		//Close file
		retval = file_close(fd);
		printf("close file, retval=%d, errno=%d\n", retval, errno);

		//File rename operation
		if (file_exist(tmp2_file)) {
			//If tmp2_file exists, rename will report an error with errno=17, so delete tmp2_file first
			retval = file_remove(tmp2_file);
			printf("remove file2, retval=%d, errno=%d\n", retval, errno);

			retval = file_rename(tmp1_file, tmp2_file);
			printf("rename file, retval=%d, errno=%d\n", retval, errno);
		} else {
			retval = file_rename(tmp1_file, tmp2_file);
			printf("rename file, retval=%d, errno=%d\n", retval, errno);
		}

		//Gets the new file length
		retval = file_get_size(tmp2_file);
		printf("%s file size = %d, errno=%d\n", tmp2_file, retval, errno);

		//Delete file
		retval = file_remove(tmp2_file);
		printf("remove file, retval=%d, errno=%d\n", retval, errno);

	exit_entry:
		return retval;
	}

	#if 0 //Log Output Example
	download.bin file size = 466600
	create new file ...
	pathname = /home/user0/tmp1.log flag = 202 O_CREAT = 200
	creat or open file
	write file, retval=48
	seek file, retval=0
	read file, retval=48
	read-data-1: 0123456789abcdef0123456789abcdef0123456789abcdef
	read data OK !!!
	seek file, retval=32
	write file 2, retval=16
	seek file 2, retval=0
	read file 2, retval=48
	read-data-2: 0123456789abcdef0123456789abcdef++++++++++++++++
	read data OK !!!
	flush file, retval=0, errno=2
	close file, retval=0, errno=2
	rename file, retval=0, errno=2
	/home/user0/tmp2.log file size = 48, errno=2
	remove file, retval=0, errno=2
	#endif

	 @endcode
@endif	 
	 
 */
void file_system_module_demo_code_never_call_this_api_please(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __FILE_H__ */

/** @} */

