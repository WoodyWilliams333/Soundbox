/*
 * @Description: ����ǩ����ع��ܽӿ�
 * @Author: LiuSiCheng
 * @Date: 2021-03-30 14:59:32
 * @LastEditors: LiuSiCheng
 * @LastEditTime: 2021-03-30 15:15:06
 */

#ifndef __LIBPOSTS_H__
#define __LIBPOSTS_H__

#ifdef __cplusplus
extern "C" {
#endif

/** png֧������ */
//#define PNG_SUPPORT                 1           // �����Ƿ�֧��pngͼƬ��Ŀǰnew7220��֧��

#ifndef MIN_VERSION_LEN
#define MIN_VERSION_LEN             64                              // ��ȡ�汾��Ϣ��buffer���ٳ���
#endif

/** ʹ�ö��ڵ���ǩ���Ŀͻ� */
//typedef enum
//{
//    ESM_CUSTOM_DEFAULT              = 0x00,     // Ĭ��
//    ESM_CUSTOM_SXF                  = 0x01,     // ���и�
//} ElecSignCustom_e;

/** ����ǩ����ģʽ��Ӧ�ÿ����ʹ�� */
typedef enum
{
    ESM_NO_FORCE_ELEC_SIGN          = 0x00,     // ��ǿ�Ƶ�ǩ��ͨ��ģʽ
    ESM_ENTER_WITH_SIGN             = 0x01,     // ��ǿ�Ƶ�ǩ������ǩ��֮����ܰ�ȷ�ϼ������ǿ��԰�ȡ�����˳�
    ESM_ON_SIGN_ENTER_NO_PRT        = 0x02,     // ��ǿ�Ƶ�ǩ�����δǩ����ȷ�ϼ�����Ҫ��ͼ��ӡ
    ESM_NO_SIGN_ENTER_INVALID       = 0x04,     // ��ǿ�Ƶ�ǩ��δǩ����ȷ�ϼ����ش����룬���ǿ��԰�ȡ�����˳�(���и�����)
    ESM_FORCE_ELEC_SIGN             = 0x08,     // ǿ�Ƶ�ǩ����ȡ����ť,ֻ��������ȷ�ϼ�����������ǩ��Ҳ���԰�ȷ�����˳�
    ESM_FORCE_ENTER_WITH_SIGN       = 0x10,     // ǿ�Ƶ���ǩ��������ǩ��֮����ܰ�ȷ�ϼ�
    ESM_SHOW_PIC_IN_PHONE           = 0x40,     // ��ȡ��ͼƬ���ֻ�����ȷ��ʾ��ǿ��l0Ϊ0x80
    ESM_GET_PIXEL_SIZE              = 0x80,     // Ϊ��Ҫ��ȡǩ�����ش�С
    ESM_NO_VIRTUAL_KEY              = 0x1000,   // �����ⰴ��
} ElecSignMode_e;

/** ����ǩ������ʾ���� */
typedef enum
{
    ESL_EN                          = 0x00,     // ��ǩӢ����ʾ
    ESL_CHN                         = 0x01,     // ��ǩ������ʾ
} ElecSignLan_e;

/** 
����ǩ����ͼƬ��ʽ�����¸�ʽ����������룬�Զ���ļ�������ָ�ʽ��
��ESIT_BMP��ESIT_BMP_MIN����ͬʱ 
ESIT_JBG��ESIT_JBG_DATA����ͬʱ
*/
typedef enum
{
    ESIT_JBG                        = 0x01,     // ��ǩͼƬjbg��ʽ��ͼƬѹ����ʽ��һ��ͼƬ��СС��1K
    ESIT_BMP                        = 0x02,     // ��ǩͼƬbmp��ʽ
    ESIT_BMP_MIN                    = 0x04,     // ��ǩͼƬbmp��ʽ��ֻ��ȡ��ǩ�����ݵ���С����ͼƬ��С��С

#if defined(PNG_SUPPORT)
    ESIT_PNG                        = 0x08,     // ��ǩͼƬpng��ʽ
#endif

    ESIT_JBG_DATA                   = 0x10,     // ��ǩͼƬjgb��ʽ�������

} ElecSignImageType_e;

/** ����ǩ���ӿڷ���ֵö�� */
typedef enum
{
    ESRC_OK                         = 0,        // ��ǩ�ɹ�
    ESRC_CANCEL                     = -1,       // ��ǩȡ��
    ESRC_TIMEOUT                    = -2,       // ��ǩ��ʱ
    ESRC_TP_ERROR                   = -3,       // TP����ʧ��
    ESRC_ERR_MEM                    = -4,       // �����ڴ�ʧ�ܣ������ڴ治��
    ESRC_ERR_CREATE_FILE            = -5,       // ���ɵ�ǩͼƬʧ��
    ESRC_ERR_SIGN_INVALID           = -6,       // δǩ����ȷ�ϼ�(ǩ����Ч��������ǩ��)
    ESRC_ERR_PARA                   = -7,       // ������Ч
} ElecSignRetCode_e;

/** ����ǩ��������ϸ */
typedef enum {
    ESLS_LINE_1                     = 1,        // ��ֵԽ������Խ��
    ESLS_LINE_2                     = 2,
    ESLS_LINE_3                     = 3,
    ESLS_LINE_4                     = 4,
    ESLS_LINE_5                     = 5,
    ESLS_LINE_6                     = 6,
    ESLS_LINE_7                     = 7,    
} ElecSignLineSize;

#define RGB_16BITS_565(r,g,b)       ((((r) & 0x1F) << 11) | (((g) & 0x3F) << 5) | ((b) & 0x1F))
#define RGB_24BITS_888(r,g,b)       ((((r) & 0xFF) << 16) | (((g) & 0xFF) << 8) | ((b) & 0xFF))
#define RGB_COLOR(r,g,b)            RGB_24BITS_888(r,g,b)               

/** ����ǩ����ɫ���ײ㶼�ǰ�24λɫ���� */
typedef enum {
    ESTC_BLACK                      = RGB_COLOR(0, 0, 0),
    ESTC_WHITE                      = RGB_COLOR(255, 255, 255),
    ESTC_RED                        = RGB_COLOR(255, 0, 0),
    ESTC_GREEN                      = RGB_COLOR(0, 255, 0),
    ESTC_BLUE                       = RGB_COLOR(0, 0, 255),
    ESTC_YELLOW                     = RGB_COLOR(255, 255, 0),
} ElecSignTextColor_e;

/** ���ش���Ļص��������� */
typedef int (*bitmap_handle_cb)(const unsigned char *bitmap, int width, int height, int channel, const char *out_file);

/** �������� */
typedef struct _fixed_rect_t
{
    int x;                                  //����x�������
    int y;                                  //����y�������
    int width;                              //���ο��
    int height;                             //���θ߶�
} fixed_rect_t;

/** ����ǩ����������ṹ */
typedef struct _tp_elec_signature_t
{
    uint16_t mode;                  // ����ǩ����ģʽ��ElecSignMode_e�ĸ������
    uint8_t language;               // ��ʾ������
    uint8_t font_size;              // �����С��16�������24������

    /**
    ���ɵ���ǩ��ͼƬ�ĸ�ʽ,��ö��ElecSignImageType_e
    ע��: ���Դ�����ͼƬ��ʽ��Ҳ���ɶ��ͼƬ�ļ�������Ӧ�ò�ȥ��ͼƬ��ʽת��
    ����: ESIT_JBG|ESIT_BMP��ͬʱ����jbgͼƬ��bmpͼƬ������jbgͼƬ���ڵ���ǩ�����ͣ�bmpͼƬ����ǩ������ӡ
    */
    uint8_t image_type;             // ͼƬ�ĸ�ʽ
    
    uint8_t line_size;              // ���ߵĴ�ϸ 1-7
    uint32_t timeouts;              // ��ʱʱ�䣬��λ: �� 
    uint32_t pixel_size;            // ����ǩ�����ش�С
    uint32_t bmp_width;             // ����ǩ��ͼƬ��bmp��ʽ�����ؿ�ȣ�ֻ��bmp��ʽ�������Ч
    uint32_t bmp_height;            // ����ǩ��ͼƬ��bmp��ʽ�����ظ߶ȣ�ֻ��bmp��ʽ�������Ч
    //char prompt[100];               // ����ǩ������ʾ��Ϣ
    char txn_info_code[40];         // ����ǩ������������

    /**
    image_file: ��������ļ��ľ���·����ע�������ļ���Ҫ����8.3ԭ�򣬷�����ܻᵼ������ͼƬʧ��
    ����: �����ǩ���ӿڿ���֧��ͬʱ���ɶ��ָ�ʽ��ͼƬ���������ɵ�ͼƬ���ƶ���һ���ģ�����׺��������
    ����: 
    image_file������� /home/user0/test/test-es.bmp
    image_type������� ESIT_JBG|ESIT_BMP
    ��ô���ɵ�ͼƬΪ: /home/user0/test/test-es.bmp��/home/user0/test/test-es.jbg
    ��һ��Ӧ�ò���ʹ�õ���ǩ���ӿ����ɵ�ͼƬʱ����Ҫ�ر�ע�� !!!
    */
    char image_file[100];           // ǩ���󱣴�ͼƬ������

    ElecSignTextColor_e color;      //��ǩ������ɫ
    bitmap_handle_cb handle;        // ���ش���ص�����
    //int custom;                     //�ͻ���ʶ

    uint8_t show_outline;           //�Ƿ���ʾ��߿�, !=0 ��ʾ
    /**
    �����ͺڰ�������������Ҫע��:
    ����ǩ������Ĳ���˵��:�������ǩ������Ϊ320*210, �ڰ������ǩ������Ϊ128*64
    sign_rect.x, sign_rect.y �ֱ��ʾǩ���������ʼλ������
    ����: sign_rect.widthȡֵ��Χ: 320--237; sign_rect.heightȡֵ��Χ��210--79
    �ڰ���: sign_rect.widthȡֵ��Χ: 128--119; sign_rect.heightȡֵ��Χ��64--40
    1.�������и���������: 
        sign_rect.x = 0; // ǩ������x��ʼλ��
        sign_rect.y = 30 + 30; // ǩ������y��ʼλ��:״̬���߶�+����߶�
        sign_rect.width = 320; // ǩ��������
        sign_rect.height = 150; // ǩ������߶�
    2.����ͨ�ð汾����������
        �����ⰴ��ǩ������:(ע��: ���ⰴ����λ���ǹ̶���, ����: ���ⰴ����ʼy����=35, ��Ӧ�߶�=30
                                                         �ڰ���: ���ⰴ����ʼy����=0, ��Ӧ�߶�=16)
        �����ߵĴ�ϸline_size>2ʱ���Բ�����������
        sign_rect.x = 0; // ǩ������x��ʼλ��
        sign_rect.y = 30 + 35 + 5 + 30; // ǩ������y��ʼλ��:״̬���߶�+���ⰴ���߶�+ƫ����+��ʾ��Ϣ
        sign_rect.width = 320; // ǩ��������
        sign_rect.height = 130; // ǩ������߶�
        �����ߵĴ�ϸline_size<=2ʱ���Բ�����������
        sign_rect.x = 4; // ǩ������x��ʼλ��, ��ʼλ��Ϊ0��ʱ�������������ʾ�߿򣬱߿���ʾ�᲻����,����ƫ����4�����ص�
        sign_rect.y = 30 + 35 + 5 + 30; // ǩ������y��ʼλ��:״̬���߶�+���ⰴ���߶�+ƫ����+��ʾ��Ϣ
        sign_rect.width = 312; // ǩ��������, Ϊ�����ұ߿���ʾ������һ��, ���Ҹ�ƫ��4�����ص�
        sign_rect.height = 130; // ǩ������߶�
    3.����ͨ�úڰ���������
        sign_rect.x = 0; // ǩ������x��ʼλ��
        sign_rect.y = 16; // ǩ������y��ʼλ��:���ⰴ���߶�(������ʾ��Ϣ�߶�)
        sign_rect.width = 128; // ǩ��������
        sign_rect.height = 48; // ǩ������߶�
    4.����ڰ���ǩ������Ϊȫ��ʱ����Ӧ����ʾ��ǩ��, reset����Ϊ0��ȫ��
        sign_rect.x = 0; // ǩ������x��ʼλ��
        sign_rect.y = 0; // ǩ������y��ʼλ��
        sign_rect.width = 128; // ǩ��������
        sign_rect.height = 64; // ǩ������߶�
    */
    fixed_rect_t sign_rect;         // ����ǩ������
    uint8_t reset;                  // �Ƿ�Ϊ����reset==1�������; ==0��ȫ��

    int jbg_data_len;               //jbg���ݳ���, ����jbg����buf��󳤶�, ���jbg����ʵ�ʳ���ֵ
    unsigned char *jbg_data;        //jbg����

} tp_elec_signature_t;

/**
* @brief ��ȡ����ǩ��
* @param[out] version��libposts��İ汾��Ϣ���   
* @param[in]  size��versionִ�е�buffer���ȣ���������64�ֽ�    
* @return ��ȡ�Ľ��
*   -<em> == 0  </em>  �ɹ�
*   -<em> <  0  </em>  ʧ�ܣ����庬���ö�� @ref ElecSignRetCode_e
*/
extern int posts_get_elec_signature(const tp_elec_signature_t *es_info);

/**
* @brief ����libposts�����־���أ�Ĭ���������־�رյ�
* @param[in] on     �����õ���־����״̬����0��ʾ�򿪣�Ϊ0��ʾ�رգ��� LOGGER_MODULE_ON ö�ٶ���
* @return ���ú����־����״̬
*	-<em> != 0 </em>  logger on
*	-<em> == 0 </em>  logger off
*/
extern int posts_logger_on(int on);

/**
* @brief ��ȡlibposts��İ汾��Ϣ
* @param[out] version��libposts��İ汾��Ϣ���   
* @param[in]  size��versionִ�е�buffer���ȣ���������64�ֽ�    
* @return ��ȡ�Ľ��
*	-<em> == 0  </em>  �ɹ�
*	-<em> == -1 </em>  ʧ��
*/
extern int posts_get_version(char *version, int size);

/**
* @brief ��jbg�ļ�ת��Ϊbmp�ļ�
* @param[out] iBmpWidth ����BMP�ļ��Ŀ��
* @param[out] iBmpHeight ����BMP�ļ��ĸ߶�
* @param[in]  appPath Ӧ����ʹ�õ�·��
* @param[in]  jbgfile ԭʼjbg�ļ���
* @param[in]  bmpfile ����bmp�ļ���
* @return ��ȡ�Ľ��
*	-<em> == 0  </em>  �ɹ�
*	-<em> != 0 </em>  ʧ��
*/
extern int posts_convert_jbg2bmp(const char *appPath, const char *jbgfile, const char *bmpfile, int *iBmpWidth, int *iBmpHeight);

/**
* @brief ����������jbg����ת��Ϊbmp�ļ�
* @param[out] iBmpWidth ����BMP�ļ��Ŀ��
* @param[out] iBmpHeight ����BMP�ļ��ĸ߶�
* @param[in]  appPath Ӧ����ʹ�õ�·��
* @param[in]  jbgdat ԭʼjbg����
* @param[in]  jbglen ԭʼjbg���ݳ���
* @param[in]  bmpfile ����bmp�ļ���
* @return ��ȡ�Ľ��
*   -<em> == 0  </em>  �ɹ�
*   -<em> != 0 </em>  ʧ��
*/
extern int posts_convert_jbgdat2bmp(const char *appPath, const unsigned char *jbgdat, int jbglen, const char *bmpfile, int *iBmpWidth, int *iBmpHeight);

/**
* @brief ����������jbg����ת��Ϊbmp����(bmpͼƬΪ��С��Ч��������)
* @param[out] iBmpWidth ����BMP�ļ��Ŀ��
* @param[out] iBmpHeight ����BMP�ļ��ĸ߶�
* @param[out]  bmpdat ����BMP����
* @param[out]  bmpLen ����BMP���ݳ���
* @param[in]  jbgdat ԭʼjbg����
* @param[in]  jbglen ԭʼjbg���ݳ���
* @return ��ȡ�Ľ��
*   -<em> == 0  </em>  �ɹ�
*   -<em> != 0 </em>  ʧ��
*/
extern int posts_convert_jbgdat2bmpdat(const unsigned char *jbgdat, int jbglen, int *iBmpWidth, int *iBmpHeight, unsigned char *bmpdat, int *bmpLen);


#ifdef __cplusplus
}
#endif

#endif


