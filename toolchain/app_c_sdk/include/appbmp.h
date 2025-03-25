#ifndef _APP_BMP_H_
#define _APP_BMP_H_

typedef enum {
    IMAGE_STATE_FILE = 0,                // bmp图片数据为文件模式
    IMAGE_STATE_BUFF,                    // bmp图片数据为缓存模式
}app_bmp_image_data_mode;

typedef enum {
    APP_BMP_R_OK                =  0, // 图片转换成功
    APP_BMP_R_PARAM_NULL        = -1, // 参数为空
    APP_BMP_R_E_FILE_OPEN       = -2, // 文件打开失败
    APP_BMP_R_E_FILE_RD         = -3, // 文件读取失败
    APP_BMP_R_E_FILE_WR         = -4, // 文件写入失败
    APP_BMP_R_E_FILE_CREAT      = -5, // 创建文件失败
    APP_BMP_R_NO_MEM            = -6, // 内存不足
}app_bmp_reply_code;

/**
 * @brief: bmp图片按比例放大或者缩小 (源数据以file模式方式传入, 输出时可以通过fileMode选择buffer模式或者file模式)
 * @param[in]: 
 *      psrcBmpPath     源图文件存放路径
 *      poutBmpPath     生成图片存放路径
 *      ppoutBmpBuf     bmp缓存数据
 *      outBmpLen       bmp数据长度
 *      fileMode        输出数据存储模式 (支持buffer模式和file模式, buffer模式需要调用者使用后释放ppoutBmpBuf内存)
 *      scale:          源图缩放比例 (例如传入值为0.5时表示图片缩小为源图的0.5倍, 输入值为1.5时表示图片放大为源图的1.5倍)
 * @param[out]: 
 *      ppoutBmpBuf     bmp缓存数据
 *      outBmpLen       bmp数据长度
 *      bmpWidth        生成图片宽度
 *      bmpHeight       生成图片高度
 * @return:
 *   -<em> == 0   </em>  成功
 *   -<em> == 其它 </em>  失败
 */
extern int app_bmp_image_file_scale(
    const char *psrcBmpPath, 
    const char *poutBmpPath, 
    uint8_t **ppoutBmpBuf,
    int *outBmpLen, 
    int fileMode, 
    int *bmpWidth, 
    int *bmpHeight, 
    double scale);

/**
 * @brief: bmp图片按比例放大或者缩小 (源数据以buffer模式方式传入, 输出时可以通过fileMode选择buffer模式或者file模式)
 * @param[in]: 
 *      psrcBmpBuf      源图数据
 *      poutBmpPath     生成图片存放路径 (file模式时需要传入此值)
 *      ppoutBmpBuf     bmp缓存数据
 *      outBmpLen       bmp数据长度
 *      fileMode        输出数据存储模式 (支持buffer模式和file模式, buffer模式需要调用者使用后释放ppoutBmpBuf内存)
 *      scale:          源图缩放比例 (例如传入值为0.5时表示图片缩小为源图的0.5倍, 输入值为1.5时表示图片放大为源图的1.5倍)
 * @param[out]: 
 *      ppoutBmpBuf     bmp缓存数据
 *      outBmpLen       bmp数据长度
 *      bmpWidth        生成图片宽度
 *      bmpHeight       生成图片高度
 * @return:
 *   -<em> == 0   </em>  成功
 *   -<em> == 其它 </em>  失败
 */
extern int app_bmp_image_dat_scale(
    const char *psrcBmpBuf, 
    const char *poutBmpPath, 
    uint8_t **ppoutBmpBuf,
    int *outBmpLen, 
    int fileMode, 
    int *bmpWidth, 
    int *bmpHeight, 
    double scale);

/**
 * @brief: 释放app_bmp_image_file_scale/app_bmp_image_dat_scale生成ppbmpBuf内存
 * @param[in]: 
 *      ppbmpBuf     bmp缓存数据
 * @return:
 *      0-成功
 *      其它-失败
 */
extern int app_bmp_release_bmpbuf(uint8_t **ppbmpBuf);

#endif

