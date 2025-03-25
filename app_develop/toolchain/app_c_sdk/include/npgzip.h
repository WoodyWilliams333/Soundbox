
#ifndef __NP_GZIP_H__
#define __NP_GZIP_H__

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

/*!
 @if Chinese
	@brief          解压文件
	@param[in]    	inPathName	-	输入文件路径名
	@param[in]    	outPathName	-	输出文件路径名
	@return         void
 @else
 @endif
*/
extern void gzip_decompress_file(char* inPathName, char* outPathName);

#ifdef __cplusplus
}
#endif /* endof __cplusplus */

#endif
