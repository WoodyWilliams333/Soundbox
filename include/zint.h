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
 * @brief ������ά���ģʽ
 */
typedef enum{
	ZINT_BUFFER_MODE = 0,			//�ڴ�ģʽ������ά��ͼ��Դ����
	ZINT_FILE_MODE = 1,				//�ļ�ģʽ
	ZINT_BUFFER_FULL_MODE = 2		//�ڴ�ģʽ����ά��bmp�ļ�����
}E_ZINT_MODE;


/** 
 * @brief ������ά��Ľṹ����Ϣ
 */
typedef struct 
{
    void *      pQRCode;        /**< ����ʹ�ô˳�Ա����     */
    uint8_t *   pBitMap;        /**< ���ɵ�bitmap��������   */
    uint32_t    bitMapLen;      /**< ���ɵ�bitmap���ݳ���   */
    uint32_t    width;          /**< ���ɵ�bitmap���       */
} QRCBMP_T;

/**
 * @name ��ά����ʾ�Ŀ������ 
 * @{ 
 */
#ifndef MIN_QRCODE_WIDTH
#define MIN_QRCODE_WIDTH    80  /**< ��С���Ϊ80�����أ�̫С�Ļ���ʶ��Ȳ��� */
#endif
#ifndef MAX_QRCODE_WIDTH
#define MAX_QRCODE_WIDTH    210 /**< lcd�ĸ߶���240����ȥ30��״̬�������ֻ�ܵ�210���������ϵĶ�ά�����ֻ����ʾ210*210 */
#endif
/** @} */

/** 
 * @brief  ����Ӧ������qrcodeͼƬ��������ȣ��������ô˽ӿ�ȥ���ã�Ĭ�����ɵ�ͼƬ���ش�СΪ195*195
 * @param[in] exp_width: Ӧ�ò���������qrcodeͼƬ�����ؿ��, 
 * @retval 0: ���óɹ� <0: ����ʧ��
 * @note   
 *            1. ע��˽ӿڲ����̰߳�ȫ�ģ������ڶ��߳̿ռ���ͬʱ���ô˽ӿ�
 *            2. ���óɹ���zint���ɵ�ͼƬ���ؿ�ȣ�ֻ�ǻᾡ���������ֵ(һ������С�����õ�ֵ�����ᳬ���������)
 */
int zint_set_expect_qrcode_width(int exp_width);

/** 
 * @brief  ����bufferģʽ���ɶ�ά��ʱ��bmp���ݵ�λ��ȣ�Ĭ��λ���Ϊ16λ
 * @param[in] bits_per_pixel: 1��������ռ��λ��, 
 * @retval 0: ���óɹ� <0: ����ʧ��
 * @note   
 *            1. ע��˽ӿڲ����̰߳�ȫ�ģ������ڶ��߳̿ռ���ͬʱ���ô˽ӿ�
 *            2. �˽ӿڽ�ʹ������bufferģʽ����bmp��ʽ�Ķ�ά�룬ʹ���ļ�ģʽ��������
 */
int zint_set_qrcode_bits_per_pixel(int bits_per_pixel);

/** 
 * @brief  ʹ��zint������ά��
 * @param[in/out]  ppbitmap: ָ�����ɵĶ�ά�����ݣ���bitmap���ݣ�Ӧ����һ������ָ��
 * @param[in/out]  len: ���ɵĴ�bitmap���ݵĳ��ȣ���bufferģʽ��Ч
 * @param[in/out]  width: ���ɵĴ�bitmapͼƬ�Ŀ�ȣ���bufferģʽ��Ч
 * @param[in/out]  height: ���ɵĴ�bitmapͼƬ�ĸ߶ȣ���bufferģʽ��Ч
 * @param[in]      str: ָ�����ɵĶ�ά�����ݣ���bitmap����
 * @param[in]      file_name: ָ�����ɶ�ά��ͼƬ��·������(�ļ�ϵͳ�е�ȫ·��)����fileģʽ��Ч
 * @param[in]      file_mode: 
 *						0: bufferģʽ�����ɵ�bitmap����Ϊ��bitmap���ݣ�������bmp�ļ���ͷ����Ϣ
 *						1: fileģʽ��������һ��������bmpͼƬ�ļ�����ģʽ�´����ppbitmap���ᱻ����
 *						2: bufferģʽ��	���ɵ�bitmap����Ϊ���bmp�ļ���file_name����ΪNULL����Ҫ��.bmp��β
 * @retval 0: �ɹ� <0: ʧ��
 * @note   
 *                 1. ���ʹ���ڴ�ģʽ��ʹ�ú���������Ӧ��Դ�ͷź���zint_release_qrcode
 *                 2. Ĭ�����ɵ�qrcodeͼƬ��СΪ195*195
 *                 3. ��������qrcodeͼƬ��������ȣ����ɵ�ͼƬ�����῿�� @ref zint_set_expect_qrcode_width ���õĿ��
 */
int zint_create_qrcode(uint8_t **ppbitmap, int *len, int *width, int *height,
                       const char *str, const char *file_name, int file_mode);
					   
/** 
 * @brief  �ͷ�zint-qrcode����bitmap�ڴ� 
 * @param[in]  ppbitmap: zint_create_qrcode�ӿ����ɵ�bitmapָ��(Ӧ����һ������ָ��)
 * @retval 0:�ɹ� -1: ʧ��
 */
int zint_release_qrcode(uint8_t **ppbitmap);

/** 
 * @brief  ������ά��
 * @note   ʹ�ú���������Ӧ��Դ�ͷź��� ReleaseQRCode
 * @param  *data: ��Ҫ���������
 * @param  len: �������ݵĳ���
 * @param  unWidthAdjusted: ָ����ά��Ŀ�ȣ�����׼ȷֵ�����������΢��
 * @param  border: �߿��ȣ���λ����
 * @param  pQRCBmp: ָ�����ɵĶ�ά������
 * @param  mode: 0:�Զ�������ά����Ϊ��ӽ�ָ����ȵ�ֵ��1:�Զ�������ά����ΪС�ڵ���ָ����ȵ�ֵ��2:�Զ�������ά����Ϊ���ڵ���ָ����ȵ�ֵ
 * @retval 0:�ɹ� -1:ʧ��
 */
int CreateQRCodeBitMap(char *data, uint32_t len, uint32_t unWidthAdjusted, uint32_t border, QRCBMP_T *pQRCBmp, int mode);

/** 
 * @brief  �ͷŶ�ά��bitmap�ڴ�
 * @param[in]  pQRCBmp: CreateQRCodeBitMap�ӿ����ɵ�bitmapָ��
 */
void ReleaseQRCode(QRCBMP_T *pQRCBmp);

/** 
 * @brief  ʹ��zint����һά����
 * @param[in/out]  ppbitmap: ָ�����ɵ�һά�����ݣ���bitmap���ݣ�Ӧ����һ������ָ��
 * @param[in/out]  len: ���ɵĴ�bitmap���ݵĳ��ȣ���bufferģʽ��Ч
 * @param[in/out]  width: ���ɵĴ�bitmapͼƬ�Ŀ�ȣ���bufferģʽ��Ч
 * @param[in/out]  height: ���ɵĴ�bitmapͼƬ�ĸ߶ȣ���bufferģʽ��Ч
 * @param[in]      str: ָ�����ɵ�һά�����ݣ���bitmap����
 * @param[in]      file_name: ָ������һά��ͼƬ��·������(�ļ�ϵͳ�е�ȫ·��)����fileģʽ��Ч
 * @param[in]      file_mode: �ο�E_ZINT_MODEö�� 
 *						0: bufferģʽ�����ɵ�bitmap����Ϊ��bitmap���ݣ�������bmp�ļ���ͷ����Ϣ
 *						1: fileģʽ��������һ��������bmpͼƬ�ļ�����ģʽ�´����ppbitmap���ᱻ����
 *						2: bufferģʽ�����ɵ�bitmapͼƬ����
 * @retval 0: �ɹ� <0: ʧ��
 * @note   
 *                 1. ���ʹ���ڴ�ģʽ��ʹ�ú���������Ӧ��Դ�ͷź���zint_release_qrcode
 */
int zint_create_code128(uint8_t **ppbitmap, int *len, int *width, int *height,
                       const char *str, const char *file_name, int file_mode);
					   
/** 
 * @brief  �ͷ�zint-code128����bitmap�ڴ� 
 * @param[in]  ppbitmap: zint_create_code128�ӿ����ɵ�bitmapָ��(Ӧ����һ������ָ��)
 * @retval 0:�ɹ� -1: ʧ��
 */
int zint_release_code128(uint8_t **ppbitmap);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*  __ZINT_H__ */
