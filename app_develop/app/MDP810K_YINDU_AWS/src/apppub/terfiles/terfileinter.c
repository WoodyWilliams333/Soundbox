#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "basicext.h"
#include "libapiext.h"
#include "appbasicext.h"

#include "terfiledef.h"


#define STR_SIZE_BYTES_LEN		4


int SaveFileComm(const char *filename, void *data_flow, int bytes)
{
	int iret = RET_OK, fd = -1;
	uint8_t bcdbuf[STR_SIZE_BYTES_LEN] = {0};
	int bcdlen = 0;

	bcdlen = STR_SIZE_BYTES_LEN;
	
	do{
		fd = app_file_open(filename,  O_RDWR|O_CREAT);
		if(fd < 0){
			iret = E_FILE_OPEN;
			break;
		}

		app_file_seek(fd, 0, SEEK_SET);

		pub_long2bcd(bytes, bcdlen, bcdbuf);
		iret = app_file_write(fd, bcdbuf, bcdlen);
		//logger_debug("write bytes len ret = %d\n", iret);
		if(iret != bcdlen){
			iret = E_FILE_WR;
			break;
		}

		iret = app_file_write(fd, (uint8_t *)data_flow, bytes);
		//logger_debug("write bytes ret = %d\n", iret);
		if(iret != bytes){
			iret = E_FILE_WR;
			break;
		}
		else{
			iret = RET_OK;
		}
		
	}while(0);

	if(fd >= 0){
		app_file_close(fd);
	}

	//logger_debug("save <%s> file ret = %d\n", filename, iret);
	return iret;
}

int ReadFileComm(const char *filename, void *data_flow, int need_bytes)
{
	int iret = RET_OK, fd = -1;
	uint8_t bcdbuf[STR_SIZE_BYTES_LEN] = {0};
	int bcdlen = 0, bytes = 0, readlen = 0;

	bcdlen = STR_SIZE_BYTES_LEN;
	
	do{
		fd = app_file_open(filename, O_RDONLY);
		if(fd < 0){
			iret = E_FILE_OPEN;
			break;
		}

		app_file_seek(fd, 0, SEEK_SET);
		// 先读取结构体的长度
		iret = app_file_read(fd, bcdbuf, bcdlen);
		//logger_debug("read bytes len ret = %d\n", iret);
		if(iret != bcdlen){
			iret = E_FILE_RD;
			break;
		}

		bytes = pub_bcd2long(bcdbuf, bcdlen, NULL);
		readlen = MIN(need_bytes, bytes);
		iret = app_file_read(fd, (uint8_t*)data_flow, readlen);		
		//logger_debug("read bytes ret = %d\n", iret);
		if(iret != readlen){
			iret = E_FILE_RD;
			break;
		}
		else{
			iret = RET_OK;
		}
	}while(0);

	if(fd >= 0){
		app_file_close(fd);
	}

	
	//logger_debug("read <%s> file ret = %d\n", filename, iret);
	return iret;
}


