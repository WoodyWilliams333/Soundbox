/*
 * @Description: 电子签名相关功能接口
 * @Author: YangJing
 * @Date: 2020-04-03 14:08:40
 * @LastEditors: YangJing
 * @LastEditTime: 2020-04-10 09:59:04
 */

#ifndef _APP_ELE_SIGN_EX_
#define _APP_ELE_SIGN_EX_

#include <libposts.h>

/**
 * @description: 获取电子签名
 * @param[in]: 
 *      es_info 电子签名信息，详细请参考电子签名库定义
 * @param[out]: none
 * @return: 
 *      0-成功
 *      其它-失败
 */
extern int app_posts_get_elec_sign(const tp_elec_signature_t *es_info);

/**
 * @description: jbg文件转bmp文件
 * @param[in]: 
 *      appPath-应用工作目录
 *      jbgfile-jbg文件名
 *      bmpfile-bmp文件名
 * @param[out]: 
 *      iBmpWidth-bmp图片宽度
 *      iBmpHeight-bmp图片高度
 * @return:
 *      0-成功
 *      其它-失败
 */
extern int app_posts_jbg2bmp(const char *appPath ,const char *jbgfile, const char *bmpfile,int *iBmpWidth,int *iBmpHeight);

/**
 * @description: jbg数据转bmp文件
 * @param[in]: 
 *      appPath-应用工作目录
 *      jbgdat-jbg数据
 *      jbglen-jbg数据长度
 *      bmpfile-bmp文件名
 * @param[out]:
 *      iBmpWidth-bmp图片宽度
 *      iBmpHeight-bmp图片高度
 * @return:
 *      0-成功
 *      其它-失败
 */
extern int app_posts_jbgdat2bmp(const char *appPath ,const unsigned char *jbgdat, int jbglen, const char *bmpfile,int *iBmpWidth,int *iBmpHeight);

#endif
