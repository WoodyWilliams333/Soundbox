/*
 * @Description: 电子签名相关功能接口
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

/** png支持配置 */
//#define PNG_SUPPORT                 1           // 定义是否支持png图片，目前new7220不支持

#ifndef MIN_VERSION_LEN
#define MIN_VERSION_LEN             64                              // 获取版本信息的buffer最少长度
#endif

/** 使用对于电子签名的客户 */
//typedef enum
//{
//    ESM_CUSTOM_DEFAULT              = 0x00,     // 默认
//    ESM_CUSTOM_SXF                  = 0x01,     // 随行付
//} ElecSignCustom_e;

/** 电子签名的模式，应用可组合使用 */
typedef enum
{
    ESM_NO_FORCE_ELEC_SIGN          = 0x00,     // 不强制电签，通用模式
    ESM_ENTER_WITH_SIGN             = 0x01,     // 不强制电签，必须签名之后才能按确认键，但是可以按取消键退出
    ESM_ON_SIGN_ENTER_NO_PRT        = 0x02,     // 不强制电签，如果未签名按确认键不需要截图打印
    ESM_NO_SIGN_ENTER_INVALID       = 0x04,     // 不强制电签，未签名按确认键返回错误码，但是可以按取消键退出(随行付适用)
    ESM_FORCE_ELEC_SIGN             = 0x08,     // 强制电签，无取消按钮,只有清屏和确认键按，但是无签名也可以按确定键退出
    ESM_FORCE_ENTER_WITH_SIGN       = 0x10,     // 强制电子签名，必须签名之后才能按确认键
    ESM_SHOW_PIC_IN_PHONE           = 0x40,     // 获取的图片在手机上正确显示，强制l0为0x80
    ESM_GET_PIXEL_SIZE              = 0x80,     // 为需要获取签名像素大小
    ESM_NO_VIRTUAL_KEY              = 0x1000,   // 无虚拟按键
} ElecSignMode_e;

/** 电子签名的显示语言 */
typedef enum
{
    ESL_EN                          = 0x00,     // 电签英文显示
    ESL_CHN                         = 0x01,     // 电签中文显示
} ElecSignLan_e;

/** 
电子签名的图片格式，以下格式可以组合输入，以多个文件输出多种格式，
但ESIT_BMP和ESIT_BMP_MIN不能同时 
ESIT_JBG和ESIT_JBG_DATA不能同时
*/
typedef enum
{
    ESIT_JBG                        = 0x01,     // 电签图片jbg格式，图片压缩格式，一般图片大小小于1K
    ESIT_BMP                        = 0x02,     // 电签图片bmp格式
    ESIT_BMP_MIN                    = 0x04,     // 电签图片bmp格式，只截取有签名数据的最小区域，图片大小较小

#if defined(PNG_SUPPORT)
    ESIT_PNG                        = 0x08,     // 电签图片png格式
#endif

    ESIT_JBG_DATA                   = 0x10,     // 电签图片jgb格式数据输出

} ElecSignImageType_e;

/** 电子签名接口返回值枚举 */
typedef enum
{
    ESRC_OK                         = 0,        // 电签成功
    ESRC_CANCEL                     = -1,       // 电签取消
    ESRC_TIMEOUT                    = -2,       // 电签超时
    ESRC_TP_ERROR                   = -3,       // TP操作失败
    ESRC_ERR_MEM                    = -4,       // 分配内存失败，可能内存不足
    ESRC_ERR_CREATE_FILE            = -5,       // 生成电签图片失败
    ESRC_ERR_SIGN_INVALID           = -6,       // 未签名按确认键(签名无效，请重新签名)
    ESRC_ERR_PARA                   = -7,       // 参数无效
} ElecSignRetCode_e;

/** 电子签名线条粗细 */
typedef enum {
    ESLS_LINE_1                     = 1,        // 数值越大，线条越粗
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

/** 电子签名颜色，底层都是按24位色处理 */
typedef enum {
    ESTC_BLACK                      = RGB_COLOR(0, 0, 0),
    ESTC_WHITE                      = RGB_COLOR(255, 255, 255),
    ESTC_RED                        = RGB_COLOR(255, 0, 0),
    ESTC_GREEN                      = RGB_COLOR(0, 255, 0),
    ESTC_BLUE                       = RGB_COLOR(0, 0, 255),
    ESTC_YELLOW                     = RGB_COLOR(255, 255, 0),
} ElecSignTextColor_e;

/** 像素处理的回调函数定义 */
typedef int (*bitmap_handle_cb)(const unsigned char *bitmap, int width, int height, int channel, const char *out_file);

/** 矩形区域 */
typedef struct _fixed_rect_t
{
    int x;                                  //矩形x坐标起点
    int y;                                  //矩形y坐标起点
    int width;                              //矩形宽度
    int height;                             //矩形高度
} fixed_rect_t;

/** 电子签名传入参数结构 */
typedef struct _tp_elec_signature_t
{
    uint16_t mode;                  // 电子签名的模式，ElecSignMode_e的各种组合
    uint8_t language;               // 显示的语言
    uint8_t font_size;              // 字体大小，16号字体或24号字体

    /**
    生成电子签名图片的格式,见枚举ElecSignImageType_e
    注意: 可以传入多个图片格式，也生成多个图片文件，减少应用层去做图片格式转换
    例如: ESIT_JBG|ESIT_BMP，同时生成jbg图片和bmp图片，其中jbg图片用于电子签名上送，bmp图片用于签购单打印
    */
    uint8_t image_type;             // 图片的格式
    
    uint8_t line_size;              // 画线的粗细 1-7
    uint32_t timeouts;              // 超时时间，单位: 秒 
    uint32_t pixel_size;            // 电子签名像素大小
    uint32_t bmp_width;             // 电子签名图片，bmp格式，像素宽度，只有bmp格式输出才有效
    uint32_t bmp_height;            // 电子签名图片，bmp格式，像素高度，只有bmp格式输出才有效
    //char prompt[100];               // 电子签名板提示信息
    char txn_info_code[40];         // 电子签名交易特征码

    /**
    image_file: 传入的是文件的绝对路径，注意命名文件需要满足8.3原则，否则可能会导致生成图片失败
    另外: 因电子签名接口可以支持同时生成多种格式的图片，所以生成的图片名称都是一样的，但后缀有所区别
    例如: 
    image_file传入的是 /home/user0/test/test-es.bmp
    image_type传入的是 ESIT_JBG|ESIT_BMP
    那么生成的图片为: /home/user0/test/test-es.bmp和/home/user0/test/test-es.jbg
    这一点应用层在使用电子签名接口生成的图片时，需要特别注意 !!!
    */
    char image_file[100];           // 签名后保存图片的名称

    ElecSignTextColor_e color;      //电签画笔颜色
    bitmap_handle_cb handle;        // 像素处理回调函数
    //int custom;                     //客户标识

    uint8_t show_outline;           //是否显示外边框, !=0 显示
    /**
    彩屏和黑白屏参数传入需要注意:
    电子签名区域的参数说明:彩屏最大签名区域为320*210, 黑白屏最大签名区域为128*64
    sign_rect.x, sign_rect.y 分别表示签名区域的起始位置坐标
    彩屏: sign_rect.width取值范围: 320--237; sign_rect.height取值范围：210--79
    黑白屏: sign_rect.width取值范围: 128--119; sign_rect.height取值范围：64--40
    1.例如随行付彩屏参数: 
        sign_rect.x = 0; // 签名区域x起始位置
        sign_rect.y = 30 + 30; // 签名区域y起始位置:状态栏高度+标题高度
        sign_rect.width = 320; // 签名区域宽度
        sign_rect.height = 150; // 签名区域高度
    2.例如通用版本彩屏参数：
        带虚拟按键签名区域:(注意: 虚拟按键的位置是固定的, 彩屏: 虚拟按键起始y坐标=35, 对应高度=30
                                                         黑白屏: 虚拟按键起始y坐标=0, 对应高度=16)
        当画线的粗细line_size>2时可以参照下面设置
        sign_rect.x = 0; // 签名区域x起始位置
        sign_rect.y = 30 + 35 + 5 + 30; // 签名区域y起始位置:状态栏高度+虚拟按键高度+偏移量+提示信息
        sign_rect.width = 320; // 签名区域宽度
        sign_rect.height = 130; // 签名区域高度
        当画线的粗细line_size<=2时可以参照下面设置
        sign_rect.x = 4; // 签名区域x起始位置, 起始位置为0的时候如果设置了显示边框，边框显示会不明显,所以偏移了4个像素点
        sign_rect.y = 30 + 35 + 5 + 30; // 签名区域y起始位置:状态栏高度+虚拟按键高度+偏移量+提示信息
        sign_rect.width = 312; // 签名区域宽度, 为了左右边框显示的明显一点, 左右各偏移4个像素点
        sign_rect.height = 130; // 签名区域高度
    3.例如通用黑白屏参数：
        sign_rect.x = 0; // 签名区域x起始位置
        sign_rect.y = 16; // 签名区域y起始位置:虚拟按键高度(或者提示信息高度)
        sign_rect.width = 128; // 签名区域宽度
        sign_rect.height = 48; // 签名区域高度
    4.例如黑白屏签名区域为全屏时：在应用提示请签名, reset设置为0清全屏
        sign_rect.x = 0; // 签名区域x起始位置
        sign_rect.y = 0; // 签名区域y起始位置
        sign_rect.width = 128; // 签名区域宽度
        sign_rect.height = 64; // 签名区域高度
    */
    fixed_rect_t sign_rect;         // 电子签名区域
    uint8_t reset;                  // 是否为清屏reset==1部分清除; ==0清全屏

    int jbg_data_len;               //jbg数据长度, 输入jbg数据buf最大长度, 输出jbg数据实际长度值
    unsigned char *jbg_data;        //jbg数据

} tp_elec_signature_t;

/**
* @brief 获取电子签名
* @param[out] version，libposts库的版本信息输出   
* @param[in]  size，version执行的buffer长度，建议至少64字节    
* @return 获取的结果
*   -<em> == 0  </em>  成功
*   -<em> <  0  </em>  失败，具体含义见枚举 @ref ElecSignRetCode_e
*/
extern int posts_get_elec_signature(const tp_elec_signature_t *es_info);

/**
* @brief 设置libposts库的日志开关，默认情况是日志关闭的
* @param[in] on     欲设置的日志开关状态，非0表示打开，为0表示关闭，见 LOGGER_MODULE_ON 枚举定义
* @return 设置后的日志开关状态
*	-<em> != 0 </em>  logger on
*	-<em> == 0 </em>  logger off
*/
extern int posts_logger_on(int on);

/**
* @brief 获取libposts库的版本信息
* @param[out] version，libposts库的版本信息输出   
* @param[in]  size，version执行的buffer长度，建议至少64字节    
* @return 获取的结果
*	-<em> == 0  </em>  成功
*	-<em> == -1 </em>  失败
*/
extern int posts_get_version(char *version, int size);

/**
* @brief 将jbg文件转换为bmp文件
* @param[out] iBmpWidth 生成BMP文件的宽度
* @param[out] iBmpHeight 生成BMP文件的高度
* @param[in]  appPath 应用所使用的路径
* @param[in]  jbgfile 原始jbg文件名
* @param[in]  bmpfile 生成bmp文件名
* @return 获取的结果
*	-<em> == 0  </em>  成功
*	-<em> != 0 </em>  失败
*/
extern int posts_convert_jbg2bmp(const char *appPath, const char *jbgfile, const char *bmpfile, int *iBmpWidth, int *iBmpHeight);

/**
* @brief 将读出来的jbg数据转换为bmp文件
* @param[out] iBmpWidth 生成BMP文件的宽度
* @param[out] iBmpHeight 生成BMP文件的高度
* @param[in]  appPath 应用所使用的路径
* @param[in]  jbgdat 原始jbg数据
* @param[in]  jbglen 原始jbg数据长度
* @param[in]  bmpfile 生成bmp文件名
* @return 获取的结果
*   -<em> == 0  </em>  成功
*   -<em> != 0 </em>  失败
*/
extern int posts_convert_jbgdat2bmp(const char *appPath, const unsigned char *jbgdat, int jbglen, const char *bmpfile, int *iBmpWidth, int *iBmpHeight);

/**
* @brief 将读出来的jbg数据转换为bmp数据(bmp图片为最小有效区域数据)
* @param[out] iBmpWidth 生成BMP文件的宽度
* @param[out] iBmpHeight 生成BMP文件的高度
* @param[out]  bmpdat 生成BMP数据
* @param[out]  bmpLen 生成BMP数据长度
* @param[in]  jbgdat 原始jbg数据
* @param[in]  jbglen 原始jbg数据长度
* @return 获取的结果
*   -<em> == 0  </em>  成功
*   -<em> != 0 </em>  失败
*/
extern int posts_convert_jbgdat2bmpdat(const unsigned char *jbgdat, int jbglen, int *iBmpWidth, int *iBmpHeight, unsigned char *bmpdat, int *bmpLen);


#ifdef __cplusplus
}
#endif

#endif


