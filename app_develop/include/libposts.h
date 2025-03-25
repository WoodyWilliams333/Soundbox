
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

/** 电子签名的模式，应用可组合使用 */
typedef enum {
    ESM_NO_FORCE_ELEC_SIGN          = 0x00,     // 不强制电签，通用模式
    ESM_ENTER_WITH_SIGN             = 0x01,     // 不强制电签，必须签名之后才能按确认键，但是可以按取消键退出
    ESM_FORCE_ELEC_SIGN             = 0x02,     // 强制电签，无取消按钮,只有清屏和确认键按，但是无签名也可以按确定键退出    
    ESM_ON_SIGN_ENTER_NO_PRT        = 0x04,     // 不强制电签，如果未签名按确认键不需要截图打印
    ESM_FORCE_ENTER_WITH_SIGN       = 0x08,		// 强制电子签名，必须签名之后才能按确认键
    ESM_SHOW_PIC_IN_PHONE           = 0x40,     // 获取的图片在手机上正确显示，强制l0为0x80
    ESM_GET_PIXEL_SIZE              = 0x80,     // 为需要获取签名像素大小
    ESM_NO_VIRTUAL_KEY				= 0x1000,	// 无虚拟按键
} ElecSignMode_e;

/** 电子签名的显示语言 */
typedef enum {
    ESL_EN                          = 0x00,     // 电签英文显示
    ESL_CHN                         = 0x01,     // 电签中文显示
} ElecSignLan_e;

/** 电子签名的图片格式，以下格式可以组合输入，以多个文件输出多种格式，但ESIT_BMP和ESIT_BMP_MIN不能同时 */
typedef enum {
    ESIT_JBG                        = 0x01,     // 电签图片jbg格式，图片压缩格式，一般图片大小小于1K
    ESIT_BMP                        = 0x02,     // 电签图片bmp格式
    ESIT_BMP_MIN                    = 0x04,     // 电签图片bmp格式，只截取有签名数据的最小区域，图片大小较小    

#if defined(PNG_SUPPORT)
    ESIT_PNG                        = 0x08,     // 电签图片png格式    
#endif
} ElecSignImageType_e;

/** 电子签名接口返回值枚举 */
typedef enum {
    ESRC_OK                         = 0,        // 电签成功
    ESRC_CANCEL                     = -1,       // 电签取消
    ESRC_TIMEOUT                    = -2,       // 电签超时
    ESRC_TP_ERROR                   = -3,       // TP操作失败
    ESRC_ERR_MEM                    = -4,       // 分配内存失败，可能内存不足
    ESRC_ERR_CREATE_FILE            = -5,       // 生成电签图片失败
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

/** 电子签名传入参数结构 */
typedef struct _tp_elec_signature_t
{
    uint16_t             mode;                   // 电子签名的模式，ElecSignMode_e的各种组合
    uint8_t             language;               // 显示的语言
    uint8_t             font_size;              // 字体大小，16号字体或24号字体

    /**
    生成电子签名图片的格式,见枚举ElecSignImageType_e
    注意: 可以传入多个图片格式，也生成多个图片文件，减少应用层去做图片格式转换
    例如: ESIT_JBG|ESIT_BMP，同时生成jbg图片和bmp图片，其中jbg图片用于电子签名上送，bmp图片用于签购单打印
    */
    uint8_t             image_type;             // 图片的格式
    
    uint8_t             line_size;              // 画线的粗细 1-7
    uint32_t            timeouts;               // 超时时间，单位: 秒 
    uint32_t            pixel_size;             // 电子签名像素大小
    uint32_t            bmp_width;              // 电子签名图片，bmp格式，像素宽度，只有bmp格式输出才有效
    uint32_t            bmp_height;             // 电子签名图片，bmp格式，像素高度，只有bmp格式输出才有效
    char                prompt[100];            // 电子签名板提示信息
    char                txn_info_code[40];      // 电子签名交易特征码

    /**
    image_file: 传入的是文件的绝对路径，注意命名文件需要满足8.3原则，否则可能会导致生成图片失败
    另外: 因电子签名接口可以支持同时生成多种格式的图片，所以生成的图片名称都是一样的，但后缀有所区别
    例如: 
    image_file传入的是 /home/user0/test/test-es.bmp
    image_type传入的是 ESIT_JBG|ESIT_BMP
    那么生成的图片为: /home/user0/test/test-es.bmp和/home/user0/test/test-es.jbg
    这一点应用层在使用电子签名接口生成的图片时，需要特别注意 !!!
    */
    char                image_file[100];        // 签名后保存图片的名称

    ElecSignTextColor_e color;                  //电签画笔颜色
    bitmap_handle_cb    handle;                 // 像素处理回调函数
} tp_elec_signature_t;

/**
* @brief 获取电子签名
* @param[out] version，libposts库的版本信息输出   
* @param[in]  size，version执行的buffer长度，建议至少64字节    
* @return 获取的结果
*	-<em> == 0  </em>  成功
*	-<em> <  0  </em>  失败，具体含义见枚举 @ref ElecSignRetCode_e
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
* @param[out] iBmpWidth ，iBmpHeight 生成BMP文件的宽度与高度
* @param[in]  appPath 应用所使用的路径
* @param[in]  jbgfile 原始jbg文件名
* @param[in]  bmpfile 生成bmp文件名
* @return 获取的结果
*	-<em> == 0  </em>  成功
*	-<em> != 0 </em>  失败
*/
extern int posts_convert_jbg2bmp(const char *appPath ,const char *jbgfile, const char *bmpfile,int *iBmpWidth,int *iBmpHeight);


#ifdef __cplusplus
}
#endif

#endif


