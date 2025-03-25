/*
 * @Description: 
 * @Author: YangJing
 * @Date: 2020-04-03 14:08:40
 * @LastEditors: YangJing
 * @LastEditTime: 2020-04-16 08:49:32
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "logger.h"

#include "appelesignex.h"

int app_posts_get_elec_sign(const tp_elec_signature_t *es_info)
{
	int iret = 0;

	iret = posts_get_elec_signature(es_info);
	logger_debug("posts_get_elec_signature ret = %d, errno = %d\n", iret, errno);

	return iret;
}

int app_posts_jbg2bmp(const char *appPath ,const char *jbgfile, const char *bmpfile,int *iBmpWidth,int *iBmpHeight)
{
	int iret = 0;

	iret = posts_convert_jbg2bmp(appPath, jbgfile, bmpfile, iBmpWidth,iBmpHeight);
	logger_debug("posts_convert_jbg2bmp ret = %d, errno = %d\n", iret, errno);

	return iret;
}

int app_posts_jbgdat2bmp(const char *appPath ,const unsigned char *jbgdat, int jbglen, const char *bmpfile,int *iBmpWidth,int *iBmpHeight)
{
	int iret = 0;

	iret = posts_convert_jbgdat2bmp(appPath, jbgdat, jbglen, bmpfile, iBmpWidth,iBmpHeight);
	logger_debug("posts_convert_jbg2bmp ret = %d, errno = %d\n", iret, errno);

	return iret;
}

