
#ifndef __NP_ZIP_H__
#define __NP_ZIP_H__


#include "zlib.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


//npk-压缩包路径 install_home-解压出来存放的目录 filter-过滤的目录(只抽取该目录内容为NULL则不过滤) filter_filename-指定过滤文件写入名称
int npk_install(const char *npk, const char *install_home,char* filter,char* filter_filename);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* end for __LED_H__ */

/** @} */

