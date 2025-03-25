/*  zint.h - definitions for libzint

    libzint - the open source barcode library
    Copyright (C) 2009-2016 Robin Stuart <rstuart114@gmail.com>

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    1. Redistributions of source code must retain the above copyright 
       notice, this list of conditions and the following disclaimer.  
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.  
    3. Neither the name of the project nor the names of its contributors
       may be used to endorse or promote products derived from this software
       without specific prior written permission. 

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
    OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
    OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
    SUCH DAMAGE.
 */

#ifndef __ZINT_H__
#define __ZINT_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** 
 * @brief 创建二维码的模式
 */
typedef enum{
	ZINT_BUFFER_MODE = 0,			//内存模式，仅二维码图像源数据
	ZINT_FILE_MODE = 1,				//文件模式
	ZINT_BUFFER_FULL_MODE = 2		//内存模式，二维码bmp文件数据
}E_ZINT_MODE;


/** 
 * @brief 创建二维码的结构体信息
 */
typedef struct 
{
    void *      pQRCode;        /**< 暂无使用此成员变量     */
    uint8_t *   pBitMap;        /**< 生成的bitmap数据内容   */
    uint32_t    bitMapLen;      /**< 生成的bitmap数据长度   */
    uint32_t    width;          /**< 生成的bitmap宽度       */
} QRCBMP_T;

/**
 * @name 二维码显示的宽度限制 
 * @{ 
 */
#ifndef MIN_QRCODE_WIDTH
#define MIN_QRCODE_WIDTH    80  /**< 最小宽度为80个像素，太小的话，识别度不高 */
#endif
#ifndef MAX_QRCODE_WIDTH
#define MAX_QRCODE_WIDTH    210 /**< lcd的高度是240，减去30的状态栏，最大只能到210；即理论上的二维码最大只能显示210*210 */
#endif
/** @} */

/** 
 * @brief  设置应用生成qrcode图片的期望宽度；若不调用此接口去设置，默认生成的图片像素大小为195*195
 * @param[in] exp_width: 应用层期望生成qrcode图片的像素宽度, 
 * @retval 0: 设置成功 <0: 设置失败
 * @note   
 *            1. 注意此接口不是线程安全的，请勿在多线程空间内同时调用此接口
 *            2. 设置成功后，zint生成的图片像素宽度，只是会尽量靠近这个值(一般是略小于设置的值，不会超过期望宽度)
 */
int zint_set_expect_qrcode_width(int exp_width);

/** 
 * @brief  设置buffer模式生成二维码时，bmp数据的位深度，默认位深度为16位
 * @param[in] bits_per_pixel: 1个像素所占的位数, 
 * @retval 0: 设置成功 <0: 设置失败
 * @note   
 *            1. 注意此接口不是线程安全的，请勿在多线程空间内同时调用此接口
 *            2. 此接口仅使用于以buffer模式生成bmp格式的二维码，使用文件模式不起作用
 */
int zint_set_qrcode_bits_per_pixel(int bits_per_pixel);

/** 
 * @brief  使用zint创建二维码
 * @param[in/out]  ppbitmap: 指向生成的二维码数据，纯bitmap数据，应传入一个二级指针
 * @param[in/out]  len: 生成的纯bitmap数据的长度，仅buffer模式有效
 * @param[in/out]  width: 生成的纯bitmap图片的宽度，仅buffer模式有效
 * @param[in/out]  height: 生成的纯bitmap图片的高度，仅buffer模式有效
 * @param[in]      str: 指向生成的二维码数据，纯bitmap数据
 * @param[in]      file_name: 指定生成二维码图片的路径名称(文件系统中的全路径)，仅file模式有效
 * @param[in]      file_mode: 
 *						0: buffer模式，生成的bitmap内容为纯bitmap数据，不包含bmp文件的头部信息
 *						1: file模式，将生成一个完整的bmp图片文件，此模式下传入的ppbitmap将会被忽略
 *						2: buffer模式，	生成的bitmap内容为完成bmp文件，file_name不能为NULL且需要以.bmp结尾
 * @retval 0: 成功 <0: 失败
 * @note   
 *                 1. 如果使用内存模式，使用后必须调用相应资源释放函数zint_release_qrcode
 *                 2. 默认生成的qrcode图片大小为195*195
 *                 3. 若设置了qrcode图片的期望宽度，生成的图片尽量会靠近 @ref zint_set_expect_qrcode_width 设置的宽度
 */
int zint_create_qrcode(uint8_t **ppbitmap, int *len, int *width, int *height,
                       const char *str, const char *file_name, int file_mode);
					   
/** 
 * @brief  释放zint-qrcode生成bitmap内存 
 * @param[in]  ppbitmap: zint_create_qrcode接口生成的bitmap指针(应该是一个二级指针)
 * @retval 0:成功 -1: 失败
 */
int zint_release_qrcode(uint8_t **ppbitmap);

/** 
 * @brief  创建二维码
 * @note   使用后必须调用相应资源释放函数 ReleaseQRCode
 * @param  *data: 需要编码的数据
 * @param  len: 编码数据的长度
 * @param  unWidthAdjusted: 指定二维码的宽度，不是准确值，会根据内容微调
 * @param  border: 边框宽度，单位像素
 * @param  pQRCBmp: 指向生成的二维码数据
 * @param  mode: 0:自动调整二维码宽度为最接近指定宽度的值，1:自动调整二维码宽度为小于等于指定宽度的值，2:自动调整二维码宽度为大于等于指定宽度的值
 * @retval 0:成功 -1:失败
 */
int CreateQRCodeBitMap(char *data, uint32_t len, uint32_t unWidthAdjusted, uint32_t border, QRCBMP_T *pQRCBmp, int mode);

/** 
 * @brief  释放二维码bitmap内存
 * @param[in]  pQRCBmp: CreateQRCodeBitMap接口生成的bitmap指针
 */
void ReleaseQRCode(QRCBMP_T *pQRCBmp);

/** 
 * @brief  使用zint创建一维条码
 * @param[in/out]  ppbitmap: 指向生成的一维码数据，纯bitmap数据，应传入一个二级指针
 * @param[in/out]  len: 生成的纯bitmap数据的长度，仅buffer模式有效
 * @param[in/out]  width: 生成的纯bitmap图片的宽度，仅buffer模式有效
 * @param[in/out]  height: 生成的纯bitmap图片的高度，仅buffer模式有效
 * @param[in]      str: 指向生成的一维码数据，纯bitmap数据
 * @param[in]      file_name: 指定生成一维码图片的路径名称(文件系统中的全路径)，仅file模式有效
 * @param[in]      file_mode: 参考E_ZINT_MODE枚举 
 *						0: buffer模式，生成的bitmap内容为纯bitmap数据，不包含bmp文件的头部信息
 *						1: file模式，将生成一个完整的bmp图片文件，此模式下传入的ppbitmap将会被忽略
 *						2: buffer模式，生成的bitmap图片数据
 * @retval 0: 成功 <0: 失败
 * @note   
 *                 1. 如果使用内存模式，使用后必须调用相应资源释放函数zint_release_qrcode
 */
int zint_create_code128(uint8_t **ppbitmap, int *len, int *width, int *height,
                       const char *str, const char *file_name, int file_mode);
					   
/** 
 * @brief  释放zint-code128生成bitmap内存 
 * @param[in]  ppbitmap: zint_create_code128接口生成的bitmap指针(应该是一个二级指针)
 * @retval 0:成功 -1: 失败
 */
int zint_release_code128(uint8_t **ppbitmap);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*  __ZINT_H__ */
