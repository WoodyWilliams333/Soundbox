#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "schedulework.h"

#include "basicext.h"
#include "libapiext.h"
#include "appbasicext.h"

#include "terfileinter.h"
#include "terfiledef.h"

#include "esfile.h"

#define ES_STORAGE_SIZE 1000 //电签存储区域固定大小

static uint8_t wr_jbgdat_flag = WR_JPGDAT_DONE;

static int read_jbg_info(int fd,  ST_JBG_INFO *lpJbginfo, int jbgseek, appbool brjbgdata)
{
	int ret = RET_OK;

	logger_debug("%s -> begin, offset = %d\n", __func__, jbgseek);
	do{
		app_file_seek(fd, jbgseek, SEEK_SET);
		ret = app_file_read(fd, lpJbginfo, ST_JBG_INFO_SIZE);
		if(ret != ST_JBG_INFO_SIZE){
			logger_error("fd = %d read fail, ret = %d, errno = %d\n", fd, ret, errno);
			ret = E_FILE_RD;
			break;			
		}

		lpJbginfo->pjbgdata = NULL;//如果不置空，并且不执行下面的malloc，后面释放内存的时候会导致蓝屏 210908
		if(brjbgdata == app_true){
			lpJbginfo->pjbgdata = malloc(lpJbginfo->size);
			if(lpJbginfo->pjbgdata == NULL){
				logger_error("malloc jbg data <%d> failed\n", lpJbginfo->size);
				ret = E_NO_MEM;
				break;
			}
			
			ret = app_file_read(fd, lpJbginfo->pjbgdata, lpJbginfo->size);	
			if(ret != lpJbginfo->size){
				logger_error("fd = %d read fail, ret = %d, errno = %d\n", fd, ret, errno);
				ret = E_FILE_RD;	
				break;		
			}
		}

		ret = RET_OK;
	}while(0);

	return ret; 
}

static int read_jbg_info_first(int fd, ST_JBG_HEAD *lpJbghead, ST_JBG_INFO *lpJbginfo)
{
	int ret = RET_OK;
	ST_JBG_INFO tmpInfo;

	logger_debug("%s -> begin, offset = %d\n", __func__, lpJbghead->offset);
	do{
		if(app_file_seek(fd, 0, SEEK_END) <= (lpJbghead->offset + ST_JBG_INFO_SIZE)){ 
			logger_error("no jbg info!\n");
			ret = E_FILE_RD;
			break;
		}
		else{
			ret = read_jbg_info(fd, &tmpInfo, lpJbghead->offset, app_false);
			if(ret != RET_OK){
				logger_error("fd = %d read fail, ret = %d, errno = %d\n", fd, ret, errno);
				ret = E_FILE_RD;
				break;			
			}	

			if(lpJbginfo != NULL){
				memcpy(lpJbginfo,&tmpInfo,ST_JBG_INFO_SIZE);
			}
		}
	
		ret = RET_OK;
	}while(0);

	return ret;
}

static int write_jbg_info(int fd, ST_JBG_INFO *lpJbginfo, appbool bwjbgdata)
{
	int ret = RET_OK;
	char szTmp[ES_STORAGE_SIZE];

	do{
		app_file_seek(fd, lpJbginfo->offset, SEEK_SET);
		ret = app_file_write(fd, lpJbginfo, ST_JBG_INFO_SIZE);
		if(ret != ST_JBG_INFO_SIZE){
			logger_error("fd = %d read fail, ret = %d, errno = %d\n", fd, ret, errno);
			ret = E_FILE_RD;
			break;			
		}

		if(bwjbgdata == app_true){
			memset(szTmp,0xFF,ES_STORAGE_SIZE);
			//每个电子签名固定占ES_STORAGE_SIZE个字节
			ret = app_file_write(fd, lpJbginfo->pjbgdata, lpJbginfo->size);
			ret += app_file_write(fd, szTmp,ES_STORAGE_SIZE-lpJbginfo->size);
			if(ret != ES_STORAGE_SIZE){
				logger_error("fd = %d write fail, ret = %d, errno = %d\n", fd, ret, errno);
				ret = E_FILE_RD;	
				break;		
			}	

			logger_debug("lpJbginfo->size = %d\n", lpJbginfo->size);
		}

		ret = RET_OK;
	}while(0);

	return ret;
}

static int append_jbg_info(int fd, ST_JBG_HEAD *lpJbghead, ST_JBG_INFO *lpJbginfo)
{
	int ret = RET_OK;
	ST_JBG_INFO tmpInfo, firstinfo, lastinfo;
	
	do{
		if(app_file_seek(fd, 0, SEEK_END) <= (lpJbghead->offset + ST_JBG_INFO_SIZE)){ //如果不存在第一个jbg信息，则需要创建第一个
			tmpInfo.offset = lpJbghead->offset;
			tmpInfo.preoffset = tmpInfo.offset;
			tmpInfo.nextoffset = tmpInfo.offset;

			tmpInfo.index = lpJbginfo->index;
			tmpInfo.no = lpJbginfo->no;
			tmpInfo.size = lpJbginfo->size;
			tmpInfo.pjbgdata = lpJbginfo->pjbgdata;
				
			ret = write_jbg_info(fd, &tmpInfo, app_true);
			if(ret != RET_OK){
				logger_error("creat first jbg info failed, ret = %d\n", ret);
				break;
			}
		}
		else{
			//读取第一个jbg信息
			ret = read_jbg_info(fd, &firstinfo, lpJbghead->offset, app_false);
			if(ret != RET_OK)	{
				logger_error("read first jbg info failed, ret = %d\n", ret);
				break;
			}

			//读取最后一个jbg信息
			ret = read_jbg_info(fd, &lastinfo, firstinfo.preoffset, app_false);
			if(ret != RET_OK)	{
				logger_error("read last jbg info failed, ret = %d\n", ret);
				break;
			}

			tmpInfo = *lpJbginfo;
			tmpInfo.preoffset = lastinfo.offset;
			tmpInfo.nextoffset = firstinfo.offset;
			tmpInfo.offset = lastinfo.offset + ST_JBG_INFO_SIZE + ES_STORAGE_SIZE;
			logger_debug("tmpInfo.offset = %d\n", tmpInfo.offset);
			ret = write_jbg_info(fd, &tmpInfo, app_true);
			if(ret != RET_OK){
				logger_error("wirte index <%d> jbg info failed, ret = %d\n", tmpInfo.index, ret);
				break;
			}			
			
			firstinfo.preoffset = tmpInfo.offset;
			lastinfo.nextoffset = tmpInfo.offset;
			if(firstinfo.offset == lastinfo.offset){ //当第一笔与最后一笔是相同offset，说明之前只存在第一笔，需要特别处理
				firstinfo.nextoffset = lastinfo.nextoffset; 
				ret = write_jbg_info(fd,  &firstinfo, app_false);
				if(ret != RET_OK){
					logger_error("wirte first jbg info failed, ret = %d\n", ret);
					break;
				}
			}
			else{
				ret = write_jbg_info(fd,  &firstinfo, app_false);
				if(ret != RET_OK){
					logger_error("wirte first jbg info failed, ret = %d\n", ret);
					break;
				}

				ret = write_jbg_info(fd,  &lastinfo, app_false);
				if(ret != RET_OK){
					logger_error("wirte last jbg info failed, ret = %d\n", ret);
					break;
				}
			}
		}
	
	}while(0);

	logger_debug("lastinfo-> offset = %d, preoffset = %d, nextoffset = %d\n", 
			lastinfo.offset, lastinfo.preoffset, lastinfo.nextoffset);
	logger_debug("firstinfo-> offset = %d, preoffset = %d, nextoffset = %d\n", 
			firstinfo.offset, firstinfo.preoffset, firstinfo.nextoffset);
	logger_debug("tmpInfo-> offset = %d, preoffset = %d, nextoffset = %d\n", 
			tmpInfo.offset, tmpInfo.preoffset, tmpInfo.nextoffset);

	return ret;
}


static int replace_jbg_info(int fd, ST_JBG_HEAD *lpJbghead, ST_JBG_INFO *lpJbginfo)
{
	int ret = RET_OK;
	int file_offset = 0;
	ST_JBG_INFO tmpInfo, preinfo, lastinfo;
	int icnt = 0;
	appbool bmatch;
	
	logger_debug("%s enter..., index = %d\n", __func__, lpJbginfo->index);
	do{
		if(app_file_seek(fd, 0, SEEK_END) <= (lpJbghead->offset + ST_JBG_INFO_SIZE)){ //如果不存在第一个jbg信息，返回成功
			ret = E_TRANS_NOMATE;
			break;
		}
		else{
			ret = read_jbg_info(fd, &preinfo, lpJbghead->offset, app_false);//定位到第一个jbg
			if(ret != RET_OK)	{
				logger_error("first jbg info read fail, ret = %d\n", ret);
				break;
			}

			ret = read_jbg_info(fd, &lastinfo, preinfo.preoffset, app_false);//定位到最后一个jbg
			if(ret != RET_OK)	{
				logger_error("last jbg info read fail, ret = %d\n", ret);
				break;
			}

			bmatch = app_false;
			file_offset = preinfo.offset;
			do{
				logger_debug("file_offset = %d\n", file_offset);
				icnt++;
				ret = read_jbg_info(fd, &tmpInfo, file_offset, app_false);
				if(ret != RET_OK){
					logger_error("<%d> jbg info read fail, ret = %d\n", icnt, ret);
					break;
				}

				if(tmpInfo.index == lpJbginfo->index){
					logger_debug("find same index = %d, offset = %d\n", tmpInfo.index, tmpInfo.offset);
					tmpInfo.size = lpJbginfo->size;
					tmpInfo.pjbgdata = lpJbginfo->pjbgdata;
					ret = write_jbg_info(fd, &tmpInfo, app_true);
					if(ret != RET_OK){
						logger_error("<%d> jbg info write fail, ret = %d\n", icnt, ret);
						break;
					}

					bmatch = app_true;
				}
				file_offset = tmpInfo.nextoffset;
			}while(tmpInfo.offset != lastinfo.offset && tmpInfo.offset >= ST_JBG_HEAD_SIZE);		

			if(bmatch == app_false && ret == RET_OK){
				ret = E_TRANS_NOMATE;
			}
			
			break;
		}
	
	}while(0);

	return ret;
}


static int open_jbg_dat(char *name, LP_JBG_HEAD lpjbghead)
{
	int fd = -1, ret = RET_OK;
	char buffer[24] = {0};
	int head_len = sizeof(ST_JBG_HEAD);

	do{
		if(app_file_exists(name) < 0 || app_file_size(name) <= 0){ // 文件不存在或文件无数据，则初始化头部信息
			fd = app_file_open(name,  O_RDWR|O_CREAT);	// 打开 jbg.dat
			if (fd < 0){	
				logger_error("<%s> open fail, ret = %d, errno = %d\n", name, ret, errno);
				ret = E_FILE_OPEN;
				break;
			}

			//初始化文件
			lpjbghead->num = 0;
			lpjbghead->offset = head_len;

			ret = app_file_write(fd, lpjbghead, head_len);
			if(ret != head_len){
				logger_error("<%s> write fail, ret = %d, errno = %d\n", name, ret, errno);
				ret = E_FILE_WR;
				break;				
			}
		}
		else{ //已存在文件头部信息，读取
			fd = app_file_open(name,  O_RDWR);	// 打开 jbg.dat
			if (fd < 0){
				logger_error("<%s> open fail, ret = %d, errno = %d\n", name, ret, errno);
				ret = E_FILE_OPEN;
				break;
			}

			ret = app_file_read(fd, buffer, head_len);	// 读取图片数量和当前偏移位置
			if(ret < 0){
				logger_error("<%s> read fail, ret = %d, errno = %d\n", name, ret, errno);
				ret = E_FILE_RD;
				break;
			}

			memcpy(&lpjbghead->num, buffer, 4);
			memcpy(&lpjbghead->offset, buffer + 4, 4);

			logger_debug("read head, num = %d, offset = %d\n", lpjbghead->num, lpjbghead->offset);
		}

		ret = RET_OK;
	}while(0);

	if(ret == RET_OK){
		ret = fd;
	}
	else{
		if(fd >= 0){
			app_file_close(fd);
		}
		ret = -1;
	}

	return ret;
}

// 上送电子签名在jbg.dat中查找指定图片数据
int find_jbg_dat(int index, char *psImageBuffer,int *len)
{
	ST_JBG_INFO stJbgInfoTmp, stJbgInfoFirst;
	ST_JBG_HEAD stJbgHead;
	int fd = -1;
	char datfile[100] = {0};
	int ret = RET_OK;
	int offset = 0;

	//等待线程处理完毕
	while(wr_jbgdat_flag == WR_JPGDAT_ING){
		app_pos_msleep(10);
	}

	memset(&stJbgInfoTmp, 0, ST_JBG_INFO_SIZE);
	do{
		snprintf(datfile, sizeof(datfile), "%s/%s", ES_IMAGE_DIR, ES_JBG_DAT);
		fd = open_jbg_dat(datfile,  &stJbgHead);	// 打开 jbg.dat
		if (fd < 0){
			logger_error("%s, open %s fail\n",__func__,datfile);
			break;
		}

		ret = read_jbg_info_first(fd, &stJbgHead, &stJbgInfoFirst);
		if (ret != RET_OK){
			logger_error("read first jbg info fail, ret = %d\n", ret);
			break;
		}

		stJbgInfoTmp = stJbgInfoFirst;
		do{
			logger_debug("stJbgInfoTmp.index = %d, index = %d\n", stJbgInfoTmp.index, index);
			if(stJbgInfoTmp.index == index){
				break;
			}

			if(stJbgInfoTmp.nextoffset == stJbgInfoFirst.offset){
				logger_error("not find index(%d) jbg info!\n",  index);
				ret = E_FILE_RD;
				break;
			}

			offset = stJbgInfoTmp.nextoffset;
			ret = read_jbg_info(fd, &stJbgInfoTmp, stJbgInfoTmp.nextoffset, app_false);
			if (ret != RET_OK){
				logger_error("read <%d> jbg info fail, ret = %d\n", stJbgInfoTmp.index, ret);
				break;
			}
		}while(1);

		if(ret != RET_OK){
			break;
		}

		//再次读取，获取jbg数据
		offset = stJbgInfoTmp.offset;
		ret = read_jbg_info(fd, &stJbgInfoTmp, offset, app_true);	
		if (ret != RET_OK){
			logger_error("read <%d> jbg info fail, ret = %d\n", stJbgInfoTmp.index, ret);
			break;		
		}

		*len = stJbgInfoTmp.size;
		memcpy(psImageBuffer, stJbgInfoTmp.pjbgdata, stJbgInfoTmp.size);
		
	}while(0);

	if(stJbgInfoTmp.pjbgdata != NULL){
		free(stJbgInfoTmp.pjbgdata);
	}

	if(fd >= 0){
		app_file_close(fd);
	}

	return ret;
}

void CalPreoffset(void)
{
    int fd = -1, ret = -1, iFileSize = 0, iNodeLen = 0, iFileSeekEnd = -1;
    char datfile[100] = {0};
    ST_JBG_HEAD stJbgHead;
    ST_JBG_INFO preinfo, lastinfo;
    
    snprintf(datfile, sizeof(datfile), "%s/%s", ES_IMAGE_DIR, ES_JBG_DAT);  //jbg.bat路径
    fd = open_jbg_dat(datfile, &stJbgHead);	// 打开 jbg.dat
	if (fd < 0){
		logger_error("%s, open %s fail\n",__func__,datfile);
		goto  exit_entry;
	}
	
	if( stJbgHead.offset <= 0){     //jpg数据的起始偏移地址固定为sizeof(ST_JBG_HEAD)
		stJbgHead.offset = sizeof(ST_JBG_HEAD);
	}

	iFileSeekEnd = app_file_seek(fd, 0, SEEK_END);  //定位到文件尾

    //文件长度为文件头长度+电签长度,文件头长度为stJbgHead.offset,每笔电签固定长度为ST_JBG_INFO_SIZE+ES_STORAGE_SIZE
    if(iFileSeekEnd > (stJbgHead.offset + ST_JBG_INFO_SIZE) &&  //存在一笔签名,如果不存在电签，文件长度为stJbgHead.offset
        iFileSeekEnd <= (stJbgHead.offset + ST_JBG_INFO_SIZE + ES_STORAGE_SIZE)) {
        ret = read_jbg_info(fd, &preinfo, stJbgHead.offset, app_false);//定位到第一个jbg
    	if(ret != RET_OK)	{
    		logger_error("first jbg info read fail, ret = %d\n", ret);
    		goto  exit_entry;
    	}

    	//只存在一笔电签preoffset、offset、nextoffset都为文件头地址stJbgHead.offset
        preinfo.preoffset = stJbgHead.offset;
        preinfo.offset = stJbgHead.offset;
        preinfo.nextoffset = stJbgHead.offset;

        //写入电签数据
    	ret = write_jbg_info(fd, &preinfo, app_false);
		if(ret != RET_OK){
			logger_error("wirte first jbg info failed, ret = %d\n", ret);
			goto  exit_entry;
		}
    } else if(iFileSeekEnd > (stJbgHead.offset + 2* ST_JBG_INFO_SIZE + ES_STORAGE_SIZE)){ //存在两笔签名
    	ret = read_jbg_info(fd, &preinfo, stJbgHead.offset, app_false);//定位到第一个jbg
    	if(ret != RET_OK)	{
    		logger_error("first jbg info read fail, ret = %d\n", ret);
    		goto  exit_entry;
    	}
    	
        iFileSize = app_file_size(datfile);
        iNodeLen = ST_JBG_INFO_SIZE + ES_STORAGE_SIZE;  //每笔电签固定长度
        logger_error("preinfo.preoffset: %d, iFileSize: %d\n", preinfo.preoffset, iFileSize);
        //文件长度去掉文件头8个字节后应是iNodeLen的整数倍，第一笔电签前一笔地址不应超过文件长度-iNodeLen
    	if ((iFileSize - 8)%iNodeLen || (preinfo.preoffset > (iFileSize - iNodeLen) && 
    	    iFileSize - iNodeLen >= 0)) {
    	    preinfo.preoffset = iFileSize - (iFileSize - 8)%iNodeLen - iNodeLen;//计算最后一笔电签的地址
    	    logger_error("cal preinfo.preoffset: %d\n", preinfo.preoffset);

    	    ret = write_jbg_info(fd, &preinfo, app_false);//更新第一笔电签的前一笔地址
    		if(ret != RET_OK){
    			logger_error("wirte first jbg info failed, ret = %d\n", ret);
    			goto  exit_entry;
    		}
        }

        ret = read_jbg_info(fd, &lastinfo, preinfo.preoffset, app_false);//定位到最后一个jbg
		if(ret != RET_OK)	{
			logger_error("first jbg info read fail, ret = %d\n", ret);
			goto  exit_entry;
		}

		lastinfo.nextoffset = preinfo.offset;   //最后一笔电签的下一笔地址指向第一笔电签的地址
		
		ret = write_jbg_info(fd, &lastinfo, app_false); //写入最后一笔电签数据
		if(ret != RET_OK){
			logger_error("wirte first jbg info failed, ret = %d\n", ret);
			goto  exit_entry;
		}
    }

exit_entry:

    if(fd >= 0){
		logger_debug("%s, close fd = %d\n",__func__, fd);
		app_file_close(fd); //关闭文件更新电签记录
	}
}

void Add_JbgToFileImpl(void *arg)
{
	int fd = -1, tmpfd = -1, ret = RET_OK;
	int tmplen = 0, index = 0;
	char *ptmp = NULL;
	char signfile[100] = {0};
	char datfile[100] = {0};
	char oldname[100] = {0};
	char newname[100] = {0};
	ST_JBG_HEAD stJbgHead;
	ST_JBG_INFO stJbgInfoTmp;

	wr_jbgdat_flag = WR_JPGDAT_ING;
	memcpy(&index,(int *)arg, sizeof(int));

	snprintf(signfile, sizeof(signfile), "%s/%03d", ES_IMAGE_DIR, index);
	snprintf(oldname, sizeof(oldname), "%s.jbg", signfile);
	snprintf(newname, sizeof(newname), "%s.tmp", signfile);

	//先重命名jbg文件
	ret = app_file_rename(oldname, newname); // 重命名 *.jbg 为 *.tmp
	if(ret < 0){
		logger_debug("%s, rename %s fail\n",__func__,oldname);
		goto  exit_entry;
	}

	//读取jbg文件数据
	tmpfd = app_file_open(newname, O_RDONLY);	// 打开*.tmp文件
	if (tmpfd < 0){
		logger_debug("%s, open %s fail\n",__func__,newname);
		goto  exit_entry;
	}
	tmplen = app_file_size(newname);
	if(tmplen > ES_STORAGE_SIZE){
		logger_debug("esfile size exceed storage size\n",__func__);
		goto  exit_entry;
	}
	
	ptmp = (char *)malloc(tmplen);
	if(ptmp == NULL){
		logger_debug("%s, ptmp malloc fail\n",__func__);
		goto  exit_entry;
	}
	
	ret = app_file_read(tmpfd, ptmp, tmplen);	// 读出*.tmp文件
	if(ret != tmplen){
		logger_debug("%s, read %s fail\n",__func__,newname);
		goto  exit_entry;
	}
	
	app_file_close(tmpfd);
	tmpfd = -1;

    //校正第一节点前一笔地址(末笔地址)
	CalPreoffset();
		
	//打开/创建jbg.dat文件
	snprintf(datfile, sizeof(datfile), "%s/%s", ES_IMAGE_DIR, ES_JBG_DAT);
	fd = open_jbg_dat(datfile, &stJbgHead);	// 打开 jbg.dat
	if (fd < 0){
		logger_error("%s, open %s fail\n",__func__,datfile);
		goto  exit_entry;
	}

	if( stJbgHead.num < 0){
		 stJbgHead.num = 0;
	}
	
	if( stJbgHead.offset <= 0){
		stJbgHead.offset = 	sizeof(ST_JBG_HEAD);
	}
	
	logger_debug("before jbg info index = %d, num = %d, offset = %d size=%d\n", index, stJbgHead.num, 
		stJbgHead.offset,app_file_seek(fd, (int)0, SEEK_END));

	stJbgInfoTmp.index = index;
	stJbgInfoTmp.no = 0;
	stJbgInfoTmp.size = tmplen;
	stJbgInfoTmp.pjbgdata = ptmp;
	
	//替换已存在的相同index的签名jbg数据
	ret = replace_jbg_info(fd, &stJbgHead, &stJbgInfoTmp);
	logger_debug("replace_jbg_info ret = %d E_TRANS_NOMATE = %d\n", ret , E_TRANS_NOMATE);
	if(ret != E_TRANS_NOMATE){//无匹配的电签和读写失败都要退出
		goto  exit_entry;
	}

	///添加签名jbg数据
	ret = append_jbg_info(fd, &stJbgHead, &stJbgInfoTmp);
	if(ret != RET_OK){
		goto  exit_entry;
	}

	stJbgHead.num++;
	app_file_seek(fd, 0, SEEK_SET);
	app_file_write(fd, &stJbgHead, ST_JBG_HEAD_SIZE);	

	logger_debug("after jbg info index = %d, num = %d, offset = %d\n", index, stJbgHead.num, stJbgHead.offset);

exit_entry:
	if(tmpfd >= 0){
		logger_debug("%s, close tmpfd = %d\n", __func__, tmpfd);
		app_file_close(tmpfd);
	}

	if(fd >= 0){
		logger_debug("%s, close fd = %d\n",__func__, fd);
		app_file_close(fd);
	}
	
	if(!app_file_exists(oldname)){	// 删掉 *.jbg
		logger_debug("%s, remove %s\n",__func__,oldname);
		app_file_remove(oldname);
	}

	if(!app_file_exists(newname)){	// 删掉 *.tmp
		logger_debug("%s, remove %s\n",__func__,newname);
		app_file_remove(newname);
	}

	if(ptmp != NULL){
		free(ptmp);
		ptmp = NULL;
	}
	
	wr_jbgdat_flag = WR_JPGDAT_DONE;		
}

void Add_JbgToFile(void *arg, appbool bThreadProc)
{
	int ret;
	ST_WORK_NODE jbg2file;
	
	if(bThreadProc == app_true){
		logger_error("%s bThreadProc = app_true\n",__func__);
		ret = init_work(&jbg2file, Add_JbgToFileImpl, arg);
		if(ret == 0){
			ret = schedule_work(&jbg2file);
		} else {
			logger_error("jbg2file schedule work create err\n");
			Add_JbgToFileImpl(arg);
		}
	}
	else{
		logger_error("%s bThreadProc = app_false\n",__func__);
		Add_JbgToFileImpl(arg);
	}
}

