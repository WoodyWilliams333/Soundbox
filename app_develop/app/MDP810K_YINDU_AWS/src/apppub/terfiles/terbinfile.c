#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "basicext.h"
#include "libapiext.h"
#include "appbasicext.h"

#include "terfileinter.h"
#include "terfiledef.h"

#if 0
static uint8_t *list_binA = NULL, *list_binB = NULL, *list_binC = NULL;
static int Alist_len = 0, Blist_len = 0, Clist_len = 0;

int SaveAddFileBINB(uint8_t *AddBinBuf)
{
	int fd = -1, ret = RET_OK, file_len = 0;

	do{
		fd = app_file_open(FILE_BINB, O_RDWR|O_CREAT);
	    if ( fd < 0 ) {
	        ret = E_FILE_OPEN;
			break;
	    }

		file_len = app_file_seek(fd, (int)0, SEEK_END);
		if(file_len != 0 && list_binB != NULL)
			free(list_binB); //把之前分配的空间释放掉

	    ret = app_file_seek(fd, (int)0, SEEK_END);
	    if ( ret < 0 ) {
	        ret = E_FILE_RD;
			break;
	    }

		ret = app_file_write(fd, AddBinBuf, strlen((char*)AddBinBuf));//把新增的写入到文件中
		if( ret!=strlen((char*)AddBinBuf) ){
	        ret = E_FILE_WR;
			break;
		}
	    
	    ret = app_file_seek(fd, (int)0, SEEK_SET);
	    if ( ret < 0 ) {
	        ret = E_FILE_WR;
			break;
	    }

	    //重新分配BINB的空间，需要读取以前的内容+新增内容
	    file_len += strlen((char*)AddBinBuf);
	    list_binB = malloc(file_len); 
	    
	    ret = app_file_read(fd, list_binB, file_len);
	    if ( ret != file_len ) {
			ret = E_FILE_RD;
	        free(list_binB);
	        list_binB = NULL;
	        break;
	    }
	    
	    Blist_len = file_len;
	}while(0);

	if( fd > 0)
	    app_file_close(fd);

	return ret;
}

void SaveFileBINC(uint8_t *AddBinBuf)
{
	int fd, ret,file_len;

	if ( app_file_exists(FILE_BINC) >= 0 ) {
        app_file_remove(FILE_BINC); //先删掉再创建新的
        if(list_binC != NULL)
        	free(list_binC);
    }

	do{
		fd = app_file_open(FILE_BINC, O_RDWR|O_CREAT);
	    if ( fd < 0 ) {
			ret = E_FILE_OPEN;
			break;
	    }
	    
	    ret = app_file_seek(fd, (int)0, SEEK_SET);
	    if ( ret < 0 ) {
			ret = E_FILE_RD;
			break;
	    }

		ret = app_file_write(fd, AddBinBuf, strlen((char*)AddBinBuf));
		if( ret!=strlen((char*)AddBinBuf) ){
			ret = E_FILE_WR;
			break;
		}
		else{
			ret = RET_OK;
		}
	}while(0);

	if(fd > 0){
		app_file_close(fd);
	}

	if( ret == RET_OK){
		file_len = strlen((char*)AddBinBuf);
		list_binC = malloc(file_len);
		strcpy((char*)list_binC,(char*)AddBinBuf);
		Clist_len = file_len;
		logger_debug("list_binC = %s len = %d\n", list_binC, Clist_len);
	}

}


void LoadFileBIN(void)
{
    int fd = -1, ret = RET_OK, file_len = 0, i= 0;
	int iCnt = 3;
	uint8_t **pBin = NULL;
	uint8_t **BinPt[3] = {&list_binA, &list_binB, &list_binC};
	int *BinLen[3] = {&Alist_len, &Blist_len, &Clist_len};
	const char *binfile[3] = {FILE_BINA, FILE_BINB, FILE_BINC};
	
	for(i = 0; i < iCnt; i++){
		pBin = BinPt[i];
		file_len = 0;
		do{
		    if ( app_file_exists(binfile[i]) < 0 ) {
		        break;
		    }
		    fd = app_file_open(binfile[i], O_RDWR);
		    if ( fd < 0 ) {
				ret = E_FILE_OPEN;
				break;
		    }
		    
		    file_len = app_file_seek(fd, (int)0, SEEK_END);
		    
		    ret = app_file_seek(fd, (int)0, SEEK_SET);
		    if ( ret < 0 ) {
				ret = E_FILE_RD;
				break;
		    }

			if(*pBin){  //如果申请过list_binA、list_binB、list_binC的空间，这里进行释放
				free(*pBin);
				*pBin = NULL;
		    }
		    *pBin = malloc(file_len);
		    
		    ret = app_file_read(fd, *pBin, file_len);
		    if ( ret != file_len ) {
				ret = E_FILE_RD;
		        free(*pBin);
		        *pBin = NULL;
		        break;
		    }
		}while(0);
		
		*BinLen[i] = file_len;
	    app_file_close(fd);
	}
}




//删除卡BIN文件
void RemoveFileBIN(uint8_t ucCardBinFlg)
{
	switch (ucCardBinFlg) {
		case CARDBIN_A:
            app_file_remove(FILE_BINA);
			if(list_binA !=NULL){
				free(list_binA);
			}
            list_binA = NULL;
            Alist_len = 0;
            break;

        case CARDBIN_B:
            app_file_remove(FILE_BINB);
			if(list_binB !=NULL){
				free(list_binB);
			}
            list_binB= NULL;
            Blist_len = 0;
            break;

        case CARDBIN_C:
            app_file_remove(FILE_BINC);
			if(list_binC !=NULL){
				free(list_binC);
			}
            list_binC= NULL;
            Clist_len = 0;
            break;

        default:
            break;
    }
}


//检查卡BIN是否已存在BINB表
int CheckBinExistBinBList(uint8_t *card_no)
{
    uint8_t *start_ptr, *end_ptr;
	
    start_ptr = end_ptr = list_binB;
    
    while ( end_ptr - list_binB < Blist_len ) {
        if ( *end_ptr++ != '|' ) {
            continue;
        }
		
        if ( memcmp(card_no, start_ptr, 8) == 0 ) {//比较bin
           // DEBUG("card_no in bin_list");
            return 2;//找到
        }
        
        start_ptr = end_ptr;//下一条开始
    }
    return 1; //不在BIN表范围内
}


// uint8_t *bin_list, int list_len,
int CheckInBinList(uint8_t ucCardBinFlg, uint8_t *card_no)
{
    uint8_t *start_ptr, *end_ptr, bin_len, cmp_len;
	uint8_t *bin_list = NULL;
	int list_len = 0;
	uint8_t tmp[20] = {0};
	
	switch (ucCardBinFlg) {
		case CARDBIN_A:
			bin_list = list_binA;
			list_len = Alist_len;
            break;

        case CARDBIN_B:
			bin_list = list_binB;
			list_len = Blist_len;
            break;

        case CARDBIN_C:
			bin_list = list_binC;
			list_len = Clist_len;
            break;

        default:
            break;	
	}
	
    if ( bin_list == NULL || list_len == 0 ) {
        return E_NO_BINLIST;
    }
    
    start_ptr = end_ptr = bin_list;
    
    while ( end_ptr - bin_list < list_len ) {
        if ( *end_ptr++ != '|' ) {
            continue;
        }
        
        if ( 1 ) {//debug
            memcpy(tmp, start_ptr, end_ptr - start_ptr - 1);
        }
        
        bin_len = pub_asc2long((char*)start_ptr, 2, NULL);

		
        cmp_len = end_ptr - start_ptr - 2 - 1;//skip len && '|'
        
        if ( strlen((char*)card_no) == bin_len ) {
            if ( memcmp(card_no, start_ptr+2, cmp_len) == 0 ) {//比较卡号
                return RET_OK;//找到
            }
        }
        
        start_ptr = end_ptr;//下一条开始
    }
	
    return E_NOT_FIND; //不在BIN表范围内
}

#endif


