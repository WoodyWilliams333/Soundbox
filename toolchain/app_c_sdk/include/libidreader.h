/*
 * @Description: 读取二代身份证相关功能接口
 * @Author: LiuSiCheng
 * @Date: 2022-01-12 15:21:29
 * @LastEditors: LiuSiCheng
 * @LastEditTime: 2022-01-12 15:21:29
 */
#ifndef __LIB_IDREADER_H__
#define __LIB_IDREADER_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    IMAGE_SAVE_FILE = 0,                // bmp图片数据保存为文件输出
    IMAGE_SAVE_BUFF,                    // bmp图片数据保存为缓存输出
}idreader_save_mode;

typedef enum {
    R_TEXT = 0,                         // 只读取文本信息
    R_TEXT_BMP_IMAGE,                   // 读取文本和图片(bmp格式)信息
    R_TEXT_JPEG_IMAGE,                  // 读取文本和图片(jpeg格式)信息
    R_TEXT_BMP_JPEG_IMAGE,              // 读取文本和图片(bmp和jpeg格式)信息
} idreader_read_mode;

typedef enum {
    SHOW_TITLE = 0,                     // 显示标题
    SHOW_CHECK_IDCARD,                  // 提示放入二代证件
    SHOW_CHECK_IDCARD_AGAIN,            // 读取失败, 重新提示放入二代证件
    SHOW_READING_IDCARD,                // 读卡中
    SHOW_QUERYING_RESULT,               // 读卡完成, 结果查询中 
    SHOW_SUCCESS,                       // 读卡完成, 数据处理中
    SHOW_END,
} idreader_show_step;

typedef enum {
    ID_R_RET_OK                                 =  0, // 读卡成功
    ID_R_CANCEL                                 = -1, // 取消查询
    ID_R_DEV_INFO_ERR                           = -2, // 设备信息错误
    ID_R_USER_CALLBACK_ERR                      = -3, // 用户回调错误
    ID_R_SYS_MEM_ERR                            = -4, // 系统内存错误
    ID_R_NFC_INIT_ERR                           = -5, // 刷卡模块初始化失败
    ID_R_NET_INIT_ERR                           = -6, // 网络初始化失败
    ID_R_PROC_CARD_ERR                          = -7, // 寻卡/选卡失败
    ID_R_REGISTRATION_FAIL                      = -8, // 设备注册失败
    ID_R_AUTH_FAIL                              = -9, // 卡验证失败
    ID_R_GET_PHOTO_FAIL                         = -10, // 获取照片失败
    ID_R_NO_MEM                                 = -11, // 内存不足
    ID_R_PROC_PHOTO_FAIL                        = -12, // 照片处理失败
    ID_R_PARA_ERR                               = -13, // 传入参数错误
    ID_R_TIMEOUT                                = -14, // 读卡超时
    ID_R_E_FILE_OPEN                            = -15, // 文件打开失败
    ID_R_E_FILE_RD                              = -16, // 文件读取失败
    ID_R_E_FILE_WR                              = -17, // 文件写入失败
    ID_R_E_FILE_CREAT                           = -18, // 创建文件失败

    ID_R_IPADDRESS                              = -19, // 错误IP地址 格式错误
    ID_R_REQUESTB                               = -20, // 寻卡错误
    ID_R_SELECTB                                = -21, // 选卡错误
    ID_R_GET_NO                                 = -22, // 获取卡号错误 执行卡ID COS指令失败
    ID_R_GET_NO_RESULT                          = -23, // 获取卡号错误结果 没有返回9000
    ID_R_GET_NO_OTHER                           = -24, // 获取卡号其他错误
    ID_R_GET_RANDOM                             = -25, // 取随机数错误
    ID_R_GET_RANDOM_RESULT                      = -26, // 取随机数错误结果 没有返回9000
    ID_R_SELECT_FIRST_FILE                      = -27, // 选第一个文件错误
    ID_R_SELECT_FIRST_FILE_RESULT               = -28, // 选第一个文件错误结果 没有返回9000
    ID_R_READ_FIRST_FILE                        = -29, // 读第一个文件错误
    ID_R_READ_FIRST_FILE_RESULT                 = -30, // 选第一个文件错误结果 没有返回9000
    ID_R_RECEIVE_INTERNAL_AUTHENTICATE          = -31, // 接收内部认证 TCP 动作
    ID_R_EXEC_INTERNAL_AUTHENTICATE             = -32, // 执行内部认证
    ID_R_SEND_INTERNAL_AUTHENTICATE             = -33, // 发送内部认证结果 TCP
    ID_R_EXEC_GET_RANDOM                        = -34, // 获取随机数
    ID_R_SEND_RANDOM                            = -35, // 发送随机数 TCP
    ID_R_RECEIVE_EXTERNAL_AUTHENTICATE          = -36, // 接收外部认证 TCP 动作
    ID_R_EXEC_EXTERNAL_AUTHENTICATE             = -37, // 执行外部认证
    ID_R_READ_SEND_SECOND_FILE                  = -38, // 读取并发送第二个文件
    ID_R_READ_SEND_THIRD_FILE                   = -39, //读取并发送第三个文件
    ID_R_READ_SEND_FOURTH_FILE                  = -40, // 读取并发送第四个文件
    ID_R_RECEIVE_LAST_DATA                      = -41, // 接收最后的数据
    ID_R_CONNECT_SERVER                         = -42, // 连接服务器失败
    ID_R_SAMV_BUSY                              = -43, // 服务器端SAMV 繁忙
    ID_R_READ_SEND_FIFTH_FILE                   = -44, // 读取并发送第五个文件
    ID_R_DATA_EMPTY                             = -45, // 数据为空
    ID_R_MCU_RESET_ERROR                        = -46, // MCU复位错误
    ID_R_SAMV_RESET_ERROR                       = -47, // SAMV复位错误
    ID_R_SAMV_MANAGER_MESSAGE                   = -48, // SAMV管理信息
    ID_R_GET_SAMV_IP_PORT                       = -49, // 获取SAMV地址端口错误
    ID_R_GET_SAMV_LAST_ERROR                    = -50, // 获取SAMV最后错误
    ID_R_CONNECT_WL_DECODER_SERVER              = -51, // 连接wl解码服务器失败
    ID_R_CONNECT_DISPATCH_SERVER                = -52, // 连接调度服务器失败
    ID_R_SEND_COS_FALSE                         = -53, // 发送COS指令失败
    ID_R_ZERO_DATA                              = -54, // 数据全部为0
    ID_R_COS_RESULT_ERROR                       = -55, // COS结果错误
    ID_R_SEND_NETWORK_ERROR                     = -56, // 网络发送错误
    ID_R_RESET_PSAM                             = -57, // 复位PSAM
    ID_R_QUERY_PSAM_STATUS                      = -58, // 查询PSAM状态失败
    ID_R_GET_PSAM_MFKEY                         = -59, // 获取MFKEY失败
    ID_R_PROCESS_PSAM_VERIFY_LOCK_DATA          = -60, // 处理校验加密数据失败
    ID_R_SEND_SAMV_DECODE_INFO                  = -61, // 发送安全模块解码信息失败
    ID_R_SET_APP_CONFIG                         = -62, // 设置APP配置
    ID_R_GET_APP_CONFIG                         = -63, // 获取APP配置
    ID_R_CLEAR_APP_CONFIG                       = -64, // 清除配置 恢复默认值
    ID_R_CHANGE_APP_CONFIG_PASSWORD             = -65, // 修改配置密码
    ID_R_POWER_ON_OFF                           = -66, // 打开关闭电源
    ID_R_GET_ANDROID_PHONE_STATE                = -67, // 获取android手机状态信息出错
    ID_R_GET_ANDROID_PHONE_IMEI                 = -68, // 获取android手机状态IMEI信息为空
    ID_R_GET_ANDROID_CONTEXT_NULL               = -69, // 获取android手机状态信息上下文对象为空
    ID_R_LED_ON_OFF                             = -70, // LED 开关错误
    ID_R_DOMAIN_NAME_ERROR                      = -71, // 域名错误
    ID_R_SELECT_DN_AID                          = -72, // 二代证DN码 通前面文件1
    ID_R_SELECT_DN_AID_RESULT                   = -73, // 二代证DN码结果错误  通前面文件1
    ID_R_READ_DN_BINARY                         = -74, // 二代证DN码  通前面文件1
    ID_R_READ_DN_BINARY_RESULT                  = -75, // 二代证DN码结果错误  通前面文件1
    ID_R_SAMV_TIME_OUT                          = -76, // 安全模块超时 没有串口返回
    ID_R_SAMV_USB_RECEIVE_TIME_OUT              = -77, // 安全模块超时 USB 接收超时
    ID_R_SAMV_HEAD_ERROR                        = -78, // 安全模块数据头错误
    ID_R_SAMV_PACKAGE_DATA_SIZE                 = -79, // 数据包大小错误
    ID_R_SAMV_CRC                               = -80, // 数据包校验错误
    ID_R_PARAM_NULL                             = -81, // 参数为空
    ID_R_SAMV_COMMAND                           = -82, // 执行安全模块指令错误
    ID_R_GET_SAMV_UART_DATA_SIZE                = -83, // 获取安全模块串口数据大小错误
    ID_R_GET_SAMV_UART_DATA_SIZE_TIME_OUT       = -84, // 获取安全模块串口数据大小超时
    ID_R_SAMV_ERROR                             = -85, // 安全模块错误  具体错误 取串口数据分析
    ID_R_PASSWORD_NULL                          = -86, // 密码为空
    ID_R_CALLBACK_NULL                          = -87, // 回调函数为空
    ID_R_LWIP_NOT_READY                         = -88, // LWIP未准备好
    
    ID_R_SM4ENCRYPT_ERROR 						= -89, // SM4加密出错
    ID_R_SM2SIGN_ERROR 							= -90, // 签名错误
    ID_R_PARAM_NOT_INIT 						= -91, // 参数未初始化
	ID_R_SM4DECRYPT_ERROR 						= -92, // SM4解密出错
	ID_R_SM2ENCRYPT_ERR 						= -93, // SM2加密出错
	ID_R_SM2DECRYPT_ERR 						= -94, // SM2解密出错
	ID_R_NET_SEND_ERR 							= -95, // 发送失败
	ID_R_NET_RECV_ERR 							= -96, // 接收失败
	ID_R_PACK_ERR 								= -97, // 组包失败
	ID_R_UNPACK_ERR 							= -98, // 解包失败
    ID_R_DNNUM_ERR                              = -99, // 获取DN码失败

    ID_R_DESDECRYPT_ERR 						= -100,// DES解密出错
    ID_R_DESENCRYPT_ERR 						= -101,// DES加密出错

	ID_R_LRC_ERR 								= -102,// lrc校验位错误(08)
	ID_R_MAC_ERR 								= -103,// MAC校验错(A0)
	ID_R_READ_TIMES_ERR 						= -104,// 证件读取次数超限(A1)
	ID_R_BUSINESS_ERR 							= -105,// 业务错误(AA)
	ID_R_SERVER_ERR 							= -106,// 服务器内部错误(99)

    ID_R_UNKNOW                                 = -128, // 未知错误
} idreader_reply_code;

/**
 * @brief 身份认证成功返回数据
 */
typedef struct _id_card_info_struct
{
    char file_name[32];                 // 文件名称, 需要读取身份证图片时, 必须传入保存图片文件名称 (不需要后缀名称)
    char name[45 + 1];                  // 姓名
    char sex[6 + 1];                    // 性别 (如: 男)
    char nation[16 + 1];                // 民族 (如: 汉)
    char birth_date[16 + 1];            // 出生年月日 (如: 20210305)
    char id_num[36 + 1];                // 身份证号
    char address[110 + 1];              // 住址
    char signing_organization[60 + 1];  // 签发机关
    char begin_time[24 + 1];            // 有效期起始日期 (如: 20210305)
    char end_time[24 + 1];              // 有效期截止日期 (如: 20210305)
    char dn_numb[65 + 1];               // DN码
    int image_width;                    // 图片宽度 (需要生成.bmp文件时返回)
    int image_height;                   // 图片高度 (需要生成.bmp文件时返回)
} id_card_info_t;

/**
 * @brief 汇创
 */
typedef struct _idreader_param_t {
    char tusn[64];                      // 设备唯一标识
    char dns[64];                       // idreader通讯域名
    char ip[64];                        // idreader通讯IP
    unsigned short port;                // idreader通讯端口
} idreader_param_t;

/**
 * @brief 诺塔斯
 */
typedef struct _idreader_lotus_param_t {
    char dns[64];                       // 通讯域名
    int userAccount;                    // 用户账号
    char passWord[64];                  // 密码
    int postcode;                       // 邮政编码
    int lineType;                       // 线路类型 0=未知 1=电信 2=联通 3=移动 4=其他
    unsigned int timeOutMs;             // 接收超时时间 (毫秒) 建议设置为2*1000毫秒
} idreader_lotus_param_t;

/**
 * @brief 金联汇通
 */
typedef struct _idreader_jlht_param_t {
	char SerPubKey[128+1];				//服务器公钥
	char TermPubKey[128+1];				//终端公钥
	char TermPriKey[64+1];				//终端私钥
    char appid[32];                     //appid
    char tusn[32];                      //设备唯一标识
    char dns[64];                       //通讯域名
    char ip[32];                        //通讯IP
    unsigned short port;                //通讯端口
    int declevel;						//是否读取照片 0:不读取 1:读取
    int read_len;						//单次读取长度(默认0xf0)
} idreader_jlht_param_t;

typedef struct _idreader_jlht_id_info_t {
	int len;						 // id长度
    char id[64];                     // id
} idreader_jlht_id_info_t;

/**
 * @brief 乐刷
 */
typedef struct _idreader_ls_param_t {
	char SerPubKey[128+1];				//服务器公钥
	char TermPubKey[128+1];				//终端公钥
	char TermPriKey[64+1];				//终端私钥
	char terminalNo[16]; 				//终端编号
	char incomingKey[32];				//进件密钥明文
    char dns[64];                       //通讯域名
    char ip[32];                        //通讯IP
    unsigned short port;                //通讯端口
    int encrytoMethod;					//加密方式 0:国密 1:国际(目前只支持国密)
    int read_len;						//单次读取长度(默认0xf0)
} idreader_ls_param_t;

typedef struct _idreader_ls_id_info_t {
	int len;						// id长度
    char id[64];                    // id
    char errstr[128];				// 用于接收0099指令返回的错误信息
} idreader_ls_id_info_t;

/**
 * @brief 开店宝
 */
typedef struct _idreader_kdb_param_t {
	char version[24+1];				//终端版本号
	char tusn[64];					//设备唯一标识
	char rootKey[16];				//根密钥
	char sm4key[16];				//sm4分量1
    char dns[64];					//通讯域名
    char ip[32];					//通讯IP
    unsigned short port;			//通讯端口
    int declevel;					//是否读取照:0x00-不读取 0x01-读取(目前只支持0x01)
    int cardtype;					//证件类:0x01-身份证 0x02-身份证REQID(目前只支持0x02)
} idreader_kdb_param_t;

typedef struct _idreader_kdb_id_info_t {
    char name[45 + 1];                  // 姓名
    char id_num[36 + 1];                // 身份证号
    char signing_organization[60 + 1];  // 签发机关
    char begin_time[24 + 1];            // 有效期起始日期 (如: 20210305)
    char end_time[24 + 1];              // 有效期截止日期 (如: 20210305)
    char address[110 + 1];              // 住址
    char task_id[32];					// 任务id
} idreader_kdb_id_info_t;

typedef int (*pIdreaderCalSm4MacCb)(uint8_t *inbuf, int inlen, uint8_t *outbuf);

typedef struct {
    idreader_show_step step;
} idreader_notifypara_st;

typedef void (*display_callback)(idreader_notifypara_st *); // 显示回调

typedef struct {
    display_callback disp;
} idreader_displayerobv_st;    // 显示观察者结构

/**
 * @brief: idreader参数初始化
 * @param: idreader_param_t *para 参数结构, 详细见idreader_param_t定义
 * @return 
 *   -<em> == 0   </em>  成功
 *   -<em> == 其它 </em>  失败
 */
extern int idreader_init(idreader_param_t *para);

/**
 * @brief: 注册显示观察者，目前仅支持一个观察者
 * @param: displayerobv_st *obv 要注册观察者结构指针
 * @return
 *   -<em> == 0   </em>  成功
 *   -<em> == 其它 </em>  失败
 */
extern int idreader_registedisplayer(idreader_displayerobv_st *obv);

/**
 * @brief 读取身份信息接口函数 (只读文本信息)
 * @param id_card_info_t *id_card_info 参数结构, 详细见id_card_info_t定义
 * @param: terfunckeys 传入特定退出值, 数组以KEY_INVALID作为结束, KEY_INVALID不能少, 
 *                  (设置此值退出时返回相应按键值)
 * @param: time_s读卡超时时间 (S)
 * @return 获取的结果
 *   -<em> == 0   </em>  成功
 *   -<em> == 其它 </em>  失败
 */
extern int idreader_read_info(id_card_info_t *id_card_info, uint8_t *terfunckeys, int time_s);

/**
 * @brief 读取身份信息接口函数 (可读身份证图片)
 * @param[in]: 
 *      ppbmpbuf     bmp缓存数据, (mode!=R_TEXT) 且 (file_mode==IMAGE_SAVE_BUFF) 时使用
 *      bmplen       bmp数据长度, (mode!=R_TEXT) 且 (file_mode==IMAGE_SAVE_BUFF) 时使用
 *      file_mode    数据存储模式 (支持buffer模式和file模式,buffer模式需要调用者使用后释放bitmap内存)
 *      mode 读取身份证模式, 详细见idreader_read_mode定义
 *      terfunckeys 传入特定退出值, 数组以KEY_INVALID作为结束, KEY_INVALID不能少(设置此值退出时返回相应按键值)
 *      time_s读卡超时时间 (S)
 * @param[out]: id_card_info_t *id_card_info 参数结构, 详细见id_card_info_t定义
 * @return 获取的结果
 *   -<em> == 0   </em>  成功
 *   -<em> == 其它 </em>  失败
 */
extern int idreader_read_info_ex(
    uint8_t **ppbmpbuf, 
    int *bmplen, 
    int file_mode,
    idreader_read_mode mode, 
    id_card_info_t *id_card_info, 
    uint8_t *terfunckeys, 
    int time_s);

/**
 * @brief: jpeg格式文件转成bmp格式文件
 * @param[in]: 
 *      ppbmpbuf     bmp缓存数据
 *      bmplen       bmp数据长度
 *      file_mode    数据存储模式 (支持buffer模式和file模式,buffer模式需要调用者使用后释放bitmap内存)
 *      file_name:   jpeg图片文件名称, 不需要加后缀; 生成相同名称的bmp图片, 后缀不相同
 *      ppath:       应用工作目录路径
 * @param[out]: 
 *      bmp_width:   图片宽度
 *      bmp_height: 图片高度
 * @return:
 *   -<em> == 0   </em>  成功
 *   -<em> == 其它 </em>  失败
 */
extern int idreader_jpeg2bmp(
    uint8_t **ppbmpbuf, 
    int *bmplen, 
    int file_mode, 
    const char *file_name, 
    const char *ppath, 
    int *bmp_width, 
    int *bmp_height);

/**
 * @brief: 释放idreader_read_info_ex或者idreader_jpeg2bmp生成ppbmpbuf内存
 * @param[in]: 
 *      ppbmpbuf     bmp缓存数据
 * @return:
 *      0-成功
 *      其它-失败
 */
extern int idreader_release_bmpbuf(uint8_t **ppbmpbuf);

/**
 * @brief: idreader参数初始化
 * @param: idreader_param_t *para 参数结构, 详细见idreader_param_t定义
 * @return 
 *   -<em> == 0   </em>  成功
 *   -<em> == 其它 </em>  失败
 */
extern int idreader_lotus_init(idreader_lotus_param_t *para);

/**
 * @brief 读取身份信息接口函数 (重庆诺塔斯接口)
 * @param id_card_info_t *id_card_info 参数结构, 详细见id_card_info_t定义
 * @param: terfunckeys 传入特定退出值, 数组以KEY_INVALID作为结束, KEY_INVALID不能少, 
 *                  (设置此值退出时返回相应按键值)
 * @param: time_s读卡超时时间 (S)
 * @return 获取的结果
 *   -<em> == 0   </em>  成功
 *   -<em> == 其它 </em>  失败
 */
extern int idreader_read_info_lotus(id_card_info_t *id_card_info, uint8_t *terfunckeys, int time_s);

/**
 * @brief: 金联汇通参数初始化
 * @param: idreader_jlht_param_t *para 参数结构, 详细见idreader_jlht_param_t定义
 * @return 
 *   -<em> == 0   </em>  成功
 *   -<em> == 其它 </em>  失败
 */
extern int idreader_jlht_init(idreader_jlht_param_t *para);

/**
 * @brief 读取身份信息接口函数 (金联汇通接口)
 * @param idreader_jlht_id_info_t详细见idreader_jlht_id_info_t定义
 * @param: terfunckeys 传入特定退出值, 数组以KEY_INVALID作为结束, KEY_INVALID不能少, 
 *                  (设置此值退出时返回相应按键值)
 * @param: time_s读卡超时时间 (S)
 * @return 获取的结果
 *   -<em> == 0   </em>  成功
 *   -<em> == 其它 </em>  失败
 */
extern int idreader_read_info_jlht(idreader_jlht_id_info_t *idinfo, unsigned char *terfunckeys, int time_s);

/**
 * @brief: 乐刷参数初始化
 * @param: idreader_ls_param_t *para 参数结构, 详细见idreader_ls_param_t定义
 * @return 
 *   -<em> == 0   </em>  成功
 *   -<em> == 其它 </em>  失败
 */
extern int idreader_ls_init(idreader_ls_param_t *para);

/**
 * @brief 读取身份信息接口函数 (乐刷接口)
 * @param idreader_ls_id_info_t详细见idreader_ls_id_info_t定义
 * @param: terfunckeys 传入特定退出值, 数组以KEY_INVALID作为结束, KEY_INVALID不能少, 
 *                  (设置此值退出时返回相应按键值)
 * @param: time_s读卡超时时间 (S)
 * @return 获取的结果
 *   -<em> == 0   </em>  成功
 *   -<em> == 其它 </em>  失败
 */
extern int idreader_read_info_ls(idreader_ls_id_info_t *idinfo, unsigned char *terfunckeys, int time_s);

/**
 * @brief 读取身份信息接口函数 (开店宝接口)
 * @param idreader_kdb_param_t详细见idreader_kdb_param_t定义
 * @param pCb为计算SM4 MAC值的回调函数，具体传参详见pIdreaderCalSm4MacCb定义
 * @param idreader_kdb_id_info_t详细见idreader_kdb_id_info_t定义
 * @param errstr用于接收后台返回的错误描述信息，如果后台没有返回错误信息，定义空间大小为128字节即可
 * @param: terfunckeys 传入特定退出值, 数组以KEY_INVALID作为结束, KEY_INVALID不能少, 
 *                  (设置此值退出时返回相应按键值)
 * @param: time_s读卡超时时间 (S)
 * @return 获取的结果
 *   -<em> == 0   </em>  成功
 *   -<em> == 其它 </em>  失败
 */
extern int idreader_read_info_kdb(idreader_kdb_param_t *para, pIdreaderCalSm4MacCb pCb, idreader_kdb_id_info_t *idinfo, char *errstr, unsigned char *terfunckeys, int time_s);

/**
 * @brief 读取身份DN码
 * @param[out]: dnData      DN码信息
 * @param[in]: dnLen        dnData的最大长度
 * @param[out]: dnLen       读取到dnData的长度
 * @param[in]: terfunckeys      传入特定退出值, 数组以KEY_INVALID作为结束, KEY_INVALID不能少, 
 *                              (设置此值退出时返回相应按键值)
 * @param[in]: time_s       读卡超时时间 (S)
 * @return 获取的结果
 *   -<em> == 0   </em>  成功
 *   -<em> == 其它 </em>  失败
 */
extern int idreader_read_dn_num(char *dnData, int *dnLen, uint8_t *terfunckeys, int time_s);

/**
 * @brief 获取客户libidreader库SDK的版本信息
 * @param[out] 
 *		version: libidreader库SDK的版本信息输出
 * @param[in] 
 *		size:	 version执行的buffer长度, 建议至少64字节
 * @return 获取的结果
 *	 -<em> == 0   </em>  成功
 *	 -<em> == -1 </em>	失败
 */
extern int idreader_get_sdk_version(char *version, int size);

/**
 * @brief 获取libidreader库的版本信息
 * @param[out] 
 *		version: libidreader库的版本信息输出
 * @param[in] 
 *		size:	 version执行的buffer长度, 建议至少64字节
 * @return 获取的结果
 *	 -<em> == 0   </em>  成功
 *	 -<em> == -1 </em>	失败
 */
extern int idreader_get_version(char *version, int size);

/**
 * @brief 设置重读次数 (适用金联汇通、诺塔斯)
 * @param[in] 
 *		num: 设置次数
 * @return 返回实际重读次数
 */
extern int idreader_set_retry_num(int num);

#ifdef __cplusplus
}
#endif

#endif
