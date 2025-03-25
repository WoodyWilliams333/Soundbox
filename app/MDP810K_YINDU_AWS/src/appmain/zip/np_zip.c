#include <stdint.h>
#include <errno.h>
#include <os_pthread.h>
#include <string.h>
#include "np_zip.h"
#include "logger.h"
#include "unzip.h"
#include "appfile.h" 


#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif 


#define WRITEBUFFERSIZE (8192)

static int dirname(const char *path, char *filepath)
{
    int retval = 0;
    char *ptr, c = '/';

    if (!path || !filepath) {
        retval = -EINVAL;
        goto exit_entry;
    }

    ptr = strrchr(path, c);
    if (ptr) {
        memcpy(filepath, path, ptr - path + 1);
        filepath[ptr - path + 1] = '\0';
    } else {
        retval = 1;
    }

exit_entry:
    return retval;
}

static int mkdir_recursive(const char *pathname)
{
    char DirName[256];
    int i, len;
    int retval = 0;

    if (!pathname) {
        retval = -EINVAL;
        goto exit_entry;
    }

    memset(DirName, 0x00, sizeof(DirName));
    snprintf(DirName, sizeof(DirName), "%s", pathname);
    len = strlen(DirName);

    if (DirName[len - 1] != '/')
        strcat(DirName, "/");

    len = strlen(DirName);

    for (i = 1; i < len; i++) {
        if (DirName[i] == '/') {
            DirName[i] = 0;
            if ((retval = access(DirName, F_OK)) != 0) {
                if ((retval = mkdir(DirName, 0700)) != 0) {
                    goto exit_entry;  /*fail*/
                }
            }
            DirName[i] = '/';
        }
    }

exit_entry:
    return retval;
}


int npk_install(const char *npk, const char *install_home,char* filter,char* filter_filename)
{
    FILE *dstFile;
    unzFile zf = NULL;
    unz_file_info fileInfo;
    unz_global_info info;
    char fileName[128];
    char f_path[256],check_path[50] = {0};
    char path[256];
    void *buf = NULL;
    int retval = -1,file_count = 0;
    int total_bytes_read = 0;
    int bytes_remaining;
    int bytes_read;
    
    if(!npk || !install_home)
        return -EINVAL;

    zf = unzOpen(npk);
    if(!zf) {
        logger_debug("unzOpen : %s fail\n", npk);
        return -EINVAL;
    }
    unzGetGlobalInfo(zf, &info);

    if(unzGoToFirstFile(zf) != UNZ_OK) {
        logger_debug("unzGoToFirstFile fail\n");
        unzClose(zf);
        return -EINVAL;
    }
    
    buf = (void*)malloc(WRITEBUFFERSIZE);
    if (!buf) {
        retval = -ENOMEM;
        goto exit_entry;
    }

	if(filter){
		snprintf(check_path,sizeof(check_path),"%s/",filter);		
	}
    // Copy each file entry
    do {
        retval = unzGetCurrentFileInfo(zf, &fileInfo, fileName, sizeof(fileName), NULL, 0, NULL, 0);
        if(retval != UNZ_OK) {
            logger_debug("unzGetCurrentFileInfo fail\n");
            goto exit_entry;
        }
        snprintf(f_path, sizeof(f_path), "%s/%s", install_home, fileName);
		logger_debug("unzip dir fileName=%s \n",fileName);
        if (fileInfo.uncompressed_size == 0) {
            if (access(f_path,F_OK) != F_OK) {
                    mkdir_recursive(f_path);
					
            }
            continue;
        }
        retval = unzOpenCurrentFile(zf);
        if(retval != UNZ_OK) {
            logger_debug("unzGoToFirstFile fail\n");
            goto exit_entry;
        }

		if(filter && strstr(f_path,check_path) == NULL){
			logger_debug("%s continue\n",f_path);
			continue;
		}
		
		if(filter && filter_filename){
			snprintf(f_path,sizeof(f_path),"%s",filter_filename);		
		}
		
        if (!dirname(f_path, path)) {
            if(access(path, F_OK) != F_OK ) {
                mkdir_recursive(path);
            }
        }        
		
		logger_debug("f_path=%s\n",f_path);
        dstFile = fopen(f_path, "wb+");
        if(!dstFile) {
            unzCloseCurrentFile(zf);                        
            retval = -errno;
			logger_debug("%s openfailed\n",f_path);
            goto exit_entry;
        }
                
        total_bytes_read = 0;
        while( total_bytes_read < fileInfo.uncompressed_size){
                bytes_remaining = fileInfo.uncompressed_size - total_bytes_read;
                bytes_read = unzReadCurrentFile( zf, buf, MIN(WRITEBUFFERSIZE, bytes_remaining ) );
                if( bytes_read <= 0 ) {
                    logger_debug("Error decompressing file\n");
                    fclose(dstFile);
                    unzCloseCurrentFile(zf);
                    retval = -1;
                    goto exit_entry;
                }
                if (bytes_read != fwrite( buf, 1, bytes_read, dstFile)) {
                    logger_debug("Error write file\n");
                    fclose(dstFile);
                    unzCloseCurrentFile(zf);
                    retval = -1;
                    goto exit_entry;
                }
                total_bytes_read += bytes_read;
        }
		file_count++;
        fclose(dstFile);
        unzCloseCurrentFile(zf);
    } while(unzGoToNextFile(zf) == UNZ_OK);
    retval = 0;
exit_entry:
	logger_debug("unzip file_count=%d \n",file_count);
    if (buf) 
        free(buf);
    unzClose(zf);
    return retval;
}



