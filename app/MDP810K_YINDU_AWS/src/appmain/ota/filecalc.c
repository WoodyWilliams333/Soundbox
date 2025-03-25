/*
 * @Description: 
 * @Author: YangJing
 * @Date: 2021-03-30 16:13:03
 * @LastEditors: YangJing
 * @LastEditTime: 2021-06-02 15:22:24
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wolfssl/openssl/md5.h>
#include <wolfssl/openssl/sha.h>
#include <system.h>
#include "mathutils.h"
#include "sha1.h"
#include "filecalc.h"
#include "logger.h"
#include "apperrdef.h"
#include "appfile.h"
#include "appdef.h"
#include "genutils.h"
#include "appmalloc.h"


#define TERMINAL_DEBUG_CID    		32495
#define APP_NAME_OFFSET             0xAC
#define HARDWARE_CID                "CID"                   /**< CID */

int file_check_cid(char *filepath)
{
	int iLen = 0,ret = 0;
	unsigned int cid = 0;
	char *buf = NULL;
	char path[64]={0};
	
	logger_debug("%s\n", __FUNCTION__);
	logger_debug("filepath:%s;\r\n",filepath);
	iLen = 0;
	
	buf = app_malloc(255);
	if(buf == NULL)
		return -1;
	memset(buf, 0, 255);
	ret = sys_get_hardware_config(HARDWARE_CID, buf, &iLen);
	if(ret == 0){
		cid = strtol(buf, NULL, 16);	
	}

	if(cid != TERMINAL_DEBUG_CID){
		//验证cid需要绝对路径
		snprintf((char *)path, sizeof(path), "%s/%s",APP_FILE_PATH, filepath);
		logger_debug("path:%s;\r\n",path);
		ret = sys_verify_file((const char *)path);
		if(ret != 0){
			ret = -1;
			goto EXIT;
		}
	}

EXIT:
	if(buf != NULL)
		app_free(buf);
	return ret;
}

int file_check_terminal(const char *appname)
{
	int ret = 0,fd = -1,iLen = 0;
	char szModelName[4+1];
	logger_debug("%s\n", __FUNCTION__);
	logger_debug("appname:%s;\r\n",appname);
	do{	
		if(app_file_exists(appname) < 0){
			logger_error(" %s not exist;\n",appname);
			ret = -1;
			break;
		}
		else{
			fd = app_file_open(appname, O_RDONLY);
			if(fd  < 0){
				logger_error(" %s open error;\n",appname);
				ret = -1;
				break;
			}

			
			ret = app_file_seek(fd,APP_NAME_OFFSET,SEEK_SET);
			if (ret < 0){
						logger_error(" %s seek error;\n",appname);
		        ret = -1;
		        break;
    		}
			
			memset(szModelName,0,sizeof(szModelName));
			iLen = app_file_read(fd, szModelName, 4);
			if(iLen != 4){
				logger_error("szModelName[%d]:%s;\n",iLen,szModelName);
				ret = -1;
				break;
			}

			// logger_hexdump("app szModelName\n", szModelName, 4);
#ifdef CFG_4G_FLAG
#ifdef CFG_8850_FLAG
			if(memcmp(szModelName,"\x00\x00\x92\x22",4)==0){ //8850的模块，0x2292，转成十进制是8850，4G机器
				logger_debug("find 8850\n");
				ret = 0;
			}else{
				logger_error("error szModelName:%s ;\n",szModelName);
				ret = -1;
			}
#else			
			if(memcmp(szModelName,"\x00\x00\xCE\x22",4)==0){ //8910的模块，0x22CE，转成十进制是8910，4G机器
				logger_debug("find 8910\n");
				ret = 0;
			}else{
				logger_error("error szModelName:%s ;\n",szModelName);
				ret = -1;
			}
#endif	
#else
			if(memcmp(szModelName,"\x00\x00\x83\x19",4)==0 || memcmp(szModelName,"\x00\x00\x00\x00",4)==0){ //2G机器
				ret = 0;
			}
            else{
				ret = -1;
			}
#endif
			
		}
	}while(0);
	
	if(fd >= 0){
		app_file_close(fd);
	}
	
	return ret;
}

int file_rename(const char *oldname,const char *newname)
{
	return rename(oldname,newname);
}

int rename_one_file(const char *pSrcName, const char *pDstName,const char *pTmpName)
{
    int ret = -1;
//    const char tmpfile[64] = {0};//APP_FILE_PATH"/"OTA_DIR"/retmp.dat";
    
logger_debug(" pSrcName = %s\n,pDstName=%s;\n", pSrcName,pDstName);
	
	if(access(pDstName, F_OK) >= 0){
		do{
			if(access(pTmpName, F_OK) >= 0){
				ret = remove(pTmpName);
				if(ret != 0){
					logger_error("remove file error... errno = %d\n", errno);
				}
			}
			ret = file_rename(pDstName, pTmpName);
			if(ret != 0){
				logger_error("rename file error... errno = %d\n", errno);
				break;
			}
      
			if(access(pDstName, F_OK) < 0){
				ret = file_rename(pSrcName, pDstName);
				if(ret != 0){
					logger_error("rename error... errno = %d\n", errno);
					file_rename(pTmpName, pDstName);
					break;
				}
			}
		}while(0);
	}
	else{
		if(access(pDstName, F_OK) < 0){
			ret = file_rename(pSrcName, pDstName);
			if(ret != 0){
				logger_error("rename error...ret=%d errno = %d\n",ret, errno);
			}
		}
	}
	
//	if(access(pTmpName, F_OK) >= 0){//先不删除临时文件。
//		ret = remove(pTmpName);
//		if(ret != 0){
//			logger_error("remove file error... errno = %d\n", errno);
//		}
//	}

    return ret;
}


//int ota_create_dir(const char *pathname)
//{
//    //#ifndef C2_TMS_COMPILE
//
//    char dirname[256] = {0};
//    int len, i;
//    char username[256];
//    struct passwd *user = NULL;
//    mode_t mode;
//
//    (void)mode;
//    (void)username;
//    
//
//    strncpy(dirname, pathname, sizeof(dirname) - 1);
//    len = strlen(dirname);
//
//    if (dirname[len - 1] != '/') {
//        dirname[len] = '/';
//        dirname[len + 1] = 0;
//        len = strlen(dirname);
//    }
//
//	logger_debug("dirname = %s\n", dirname);
//    for (i = 0; i < len; i++) {
//    	if (i == 0 && dirname[i] == '/') {
//			continue;
//		}
//        if (dirname[i] == '/') {
//            dirname[i] = 0;
//
//			logger_debug("dirname = %s\n", dirname);
//            if (access(dirname, F_OK) != 0) {
//                if(mkdir(dirname, 0777) == -1){
//                    logger_debug("mkdir error: %d", errno);
//                    return -1;
//                }
//
//                if(user) {
//                    //chown(dirname, user->pw_uid, user->pw_gid);
//                }
//            }
//            dirname[i] = '/';
//        }
//    }
//
//    return 0;
//}
//

int ota_file_read(const char *name,char *outData,int readLen)
{
	int ret = -1;
	int fp = -1;
	logger_debug("%s\n", __FUNCTION__);
	logger_debug("file_read name:%s readLen=%d;\r\n",name,readLen);
	if(app_file_exists(name) != 0)
		goto exit;
	
	fp = app_file_open(name, O_RDONLY);//r+以读/写方式打开文件，该文件必须存在。
	if(fp <= 0){
		goto exit;
	}
	if (app_file_read(fp, (void *)outData, readLen) !=  readLen) {
		goto exit;
	}

	ret = 0;

exit:
	if(fp > 0){
		app_file_close(fp);

	}
	
	return ret;
}

int ota_file_save(const char *name,char *content,int len,int type)
{
	int fd = 0;
	int ret = -1;
	
	logger_debug("[%s] run...;\n", __FUNCTION__);
	logger_debug("name :%s;\n",name);
	fd = app_file_open(name, O_RDWR | O_CREAT);
	if (fd < 0) {
		logger_error("open fail;\n");
		return (-1);
	}
	
	if(type == 1)
		ret = app_file_seek(fd, (int)0, SEEK_END);
	else 
		ret = app_file_seek(fd, (int)0, SEEK_SET);
	if (ret < 0) {
		app_file_close(fd);
		logger_error("seek fail;\n");
		return (-1);
	}
	
	ret = app_file_write(fd, (uint8_t *) content, len);
	if (ret != len) {
		app_file_close(fd);
		logger_error("write fail;\n");
		return (-1);
	}
	app_file_close(fd);
	logger_debug("app_file_close\n");
	return 0;
}

int ota_file_remove(void)
{
	image_hdr_t *pihdr = NULL;
	int len_hdr = sizeof(image_hdr_t);
	char file_path[64]={0};
	int iRet = -1;
	
	logger_debug("[%s] run...;\n", __FUNCTION__);
	pihdr = (image_hdr_t *)app_malloc(len_hdr);
	if(pihdr == NULL){
		goto EXIT;
	}
	iRet = ota_file_read(SYSTEM_IHDR_FILE,(char *)pihdr,len_hdr);
	if(iRet < 0)
		goto EXIT;
	
	for(int i = 0; i < pihdr->firmware_num; i++){
		iRet = parse_path(pihdr->firms_info[i].path,file_path);
		if(iRet < 0)
			goto EXIT;
		
		if(strlen(file_path) >=0 && app_file_exists(file_path)>=0){
			iRet = app_file_remove(file_path);
			logger_debug("[%s] app_file_remove..iRet=%d;\n", file_path,iRet);
			if(iRet < 0)
				goto EXIT;
		}
	}
	if(app_file_exists(SYSTEM_IHDR_FILE) >= 0){
		iRet = app_file_remove(SYSTEM_IHDR_FILE);
		logger_debug("[%s] app_file_remove..iRet=%d;\n", SYSTEM_IHDR_FILE,iRet);
		if(iRet < 0)
			goto EXIT;
	}
	
	if(app_file_exists(SYSTEM_HASH_FILE) >= 0){
		iRet = app_file_remove(SYSTEM_HASH_FILE);
		logger_debug("[%s] app_file_remove..iRet=%d;\n", SYSTEM_HASH_FILE,iRet);
		if(iRet < 0)
			goto EXIT;
	}
	
	iRet = 0;
EXIT:
	if(pihdr != NULL)
		app_free(pihdr);
	return iRet;
}

int ota_file_check(ota_params *ota_param,char *file_path)
{
	#define DATA_SIZE 1024
	int len = 0;
	int iRet = -1,ret = -1;
	WOLFSSL_SHA256_CTX *hash256 = NULL;
	SHA1_CONTEXT *hash1 = NULL;
	MD5_CTX *md5 = NULL;
	uint8_t  hashbuf[32+1]={0};
	char calbuf[64+1] = {0};
	char verify_value[64+1] = {0};
	unsigned char *data = NULL;
	int fd = -1;
	
	if(ota_param->size>MAX_SIZE_BUFF){
		logger_error("file is out of size!!!\n");
		iRet = -1;
		goto EXIT;
	}

	if(file_path==NULL || strlen(file_path)<1){
		logger_error("file path is wrong!!!\n");
		iRet = -1;
		goto EXIT;
	}
		
	len = ota_param->size;
	if(len==0){
		logger_error("ota_param->size is wrong!!!\n");
		iRet = -1;
		goto EXIT;
	}
		
	data = app_malloc(DATA_SIZE);
	if(data == NULL){
		logger_error("app_malloc data err!!!\n");
		iRet = -1;
		goto EXIT;
	}

	if(ota_param->verify == OTA_VERIFY_MD5){
		md5 = (MD5_CTX *)app_malloc(sizeof(MD5_CTX));
		if(md5 == NULL){
			iRet = -1;
			goto EXIT;
		}
		MD5_Init(md5);
	}else if(ota_param->verify == OTA_VERIFY_SHA1){
		hash1 = (SHA1_CONTEXT *)app_malloc(sizeof(SHA1_CONTEXT));
		if(hash1 == NULL){
			iRet = -1;
			goto EXIT;
		}
		SysSha1Init(hash1);
	}else if(ota_param->verify == OTA_VERIFY_SHA256){
		hash256 = (WOLFSSL_SHA256_CTX *)app_malloc(sizeof(WOLFSSL_SHA256_CTX));
		if(hash256 == NULL){
			iRet = -1;
			goto EXIT;
		}
		SHA256_Init(hash256);
	}else{
		iRet = -1;
		goto EXIT;
	}

	if((fd = app_file_open(file_path, O_RDONLY)) < 0){
		logger_error("[%s]open err fd:%d;\n",file_path,fd);
		iRet = -1;
		goto EXIT;
    }

	while(1){
		memset(data,0,DATA_SIZE);
		if((ret = app_file_read(fd, data, DATA_SIZE)) <=0){
			break;
		}else{
			if(ota_param->verify == OTA_VERIFY_MD5){
				MD5_Update(md5,data,ret);
			}else if(ota_param->verify == OTA_VERIFY_SHA1){
				SysSha1Update(hash1,data,ret);
			}else if(ota_param->verify == OTA_VERIFY_SHA256){
				SHA256_Update(hash256,data,ret);
			}
			//if(0 == ret || ret < DATA_SIZE){
			if(0 == ret){
				iRet = -1;
				logger_error("ret=%d\n",ret);
				break;
			}
		}
	};
	app_file_close(fd);

	if(ota_param->verify == OTA_VERIFY_MD5){
		MD5_Final(hashbuf,md5);
		pub_bcd2asc0(hashbuf, 16, (char*)calbuf);
	}else if(ota_param->verify == OTA_VERIFY_SHA1){
		SysSha1Fina(hash1,hashbuf);
		pub_bcd2asc0(hashbuf, 20, (char*)calbuf);
	}else if(ota_param->verify == OTA_VERIFY_SHA256){
		SHA256_Final(hashbuf,hash256);
		pub_bcd2asc0(hashbuf, 32, (char*)calbuf);
	}else{
		iRet = -1;
		goto EXIT;
	}
	
	strcpy(verify_value,ota_param->verify_value);
	pub_strupper(verify_value);
	logger_debug("verify_value:%s\n",verify_value);
	logger_debug("calbuf:%s\n",calbuf);
	if (strcmp(calbuf, verify_value) == 0){
		iRet = 0;
		logger_debug("sign check success!\n");
	}else{
		iRet = -1;
		logger_debug("sign check failed!\n");
	}
		
EXIT:
	if(hash256 != NULL)
		app_free(hash256);
	if(hash1 != NULL)
		app_free(hash1);
	if(md5 != NULL)
		app_free(md5);
	return iRet;
}


