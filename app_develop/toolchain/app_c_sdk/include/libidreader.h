/*
 * @Description: ��ȡ�������֤��ع��ܽӿ�
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
    IMAGE_SAVE_FILE = 0,                // bmpͼƬ���ݱ���Ϊ�ļ����
    IMAGE_SAVE_BUFF,                    // bmpͼƬ���ݱ���Ϊ�������
}idreader_save_mode;

typedef enum {
    R_TEXT = 0,                         // ֻ��ȡ�ı���Ϣ
    R_TEXT_BMP_IMAGE,                   // ��ȡ�ı���ͼƬ(bmp��ʽ)��Ϣ
    R_TEXT_JPEG_IMAGE,                  // ��ȡ�ı���ͼƬ(jpeg��ʽ)��Ϣ
    R_TEXT_BMP_JPEG_IMAGE,              // ��ȡ�ı���ͼƬ(bmp��jpeg��ʽ)��Ϣ
} idreader_read_mode;

typedef enum {
    SHOW_TITLE = 0,                     // ��ʾ����
    SHOW_CHECK_IDCARD,                  // ��ʾ�������֤��
    SHOW_CHECK_IDCARD_AGAIN,            // ��ȡʧ��, ������ʾ�������֤��
    SHOW_READING_IDCARD,                // ������
    SHOW_QUERYING_RESULT,               // �������, �����ѯ�� 
    SHOW_SUCCESS,                       // �������, ���ݴ�����
    SHOW_END,
} idreader_show_step;

typedef enum {
    ID_R_RET_OK                                 =  0, // �����ɹ�
    ID_R_CANCEL                                 = -1, // ȡ����ѯ
    ID_R_DEV_INFO_ERR                           = -2, // �豸��Ϣ����
    ID_R_USER_CALLBACK_ERR                      = -3, // �û��ص�����
    ID_R_SYS_MEM_ERR                            = -4, // ϵͳ�ڴ����
    ID_R_NFC_INIT_ERR                           = -5, // ˢ��ģ���ʼ��ʧ��
    ID_R_NET_INIT_ERR                           = -6, // �����ʼ��ʧ��
    ID_R_PROC_CARD_ERR                          = -7, // Ѱ��/ѡ��ʧ��
    ID_R_REGISTRATION_FAIL                      = -8, // �豸ע��ʧ��
    ID_R_AUTH_FAIL                              = -9, // ����֤ʧ��
    ID_R_GET_PHOTO_FAIL                         = -10, // ��ȡ��Ƭʧ��
    ID_R_NO_MEM                                 = -11, // �ڴ治��
    ID_R_PROC_PHOTO_FAIL                        = -12, // ��Ƭ����ʧ��
    ID_R_PARA_ERR                               = -13, // �����������
    ID_R_TIMEOUT                                = -14, // ������ʱ
    ID_R_E_FILE_OPEN                            = -15, // �ļ���ʧ��
    ID_R_E_FILE_RD                              = -16, // �ļ���ȡʧ��
    ID_R_E_FILE_WR                              = -17, // �ļ�д��ʧ��
    ID_R_E_FILE_CREAT                           = -18, // �����ļ�ʧ��

    ID_R_IPADDRESS                              = -19, // ����IP��ַ ��ʽ����
    ID_R_REQUESTB                               = -20, // Ѱ������
    ID_R_SELECTB                                = -21, // ѡ������
    ID_R_GET_NO                                 = -22, // ��ȡ���Ŵ��� ִ�п�ID COSָ��ʧ��
    ID_R_GET_NO_RESULT                          = -23, // ��ȡ���Ŵ����� û�з���9000
    ID_R_GET_NO_OTHER                           = -24, // ��ȡ������������
    ID_R_GET_RANDOM                             = -25, // ȡ���������
    ID_R_GET_RANDOM_RESULT                      = -26, // ȡ����������� û�з���9000
    ID_R_SELECT_FIRST_FILE                      = -27, // ѡ��һ���ļ�����
    ID_R_SELECT_FIRST_FILE_RESULT               = -28, // ѡ��һ���ļ������� û�з���9000
    ID_R_READ_FIRST_FILE                        = -29, // ����һ���ļ�����
    ID_R_READ_FIRST_FILE_RESULT                 = -30, // ѡ��һ���ļ������� û�з���9000
    ID_R_RECEIVE_INTERNAL_AUTHENTICATE          = -31, // �����ڲ���֤ TCP ����
    ID_R_EXEC_INTERNAL_AUTHENTICATE             = -32, // ִ���ڲ���֤
    ID_R_SEND_INTERNAL_AUTHENTICATE             = -33, // �����ڲ���֤��� TCP
    ID_R_EXEC_GET_RANDOM                        = -34, // ��ȡ�����
    ID_R_SEND_RANDOM                            = -35, // ��������� TCP
    ID_R_RECEIVE_EXTERNAL_AUTHENTICATE          = -36, // �����ⲿ��֤ TCP ����
    ID_R_EXEC_EXTERNAL_AUTHENTICATE             = -37, // ִ���ⲿ��֤
    ID_R_READ_SEND_SECOND_FILE                  = -38, // ��ȡ�����͵ڶ����ļ�
    ID_R_READ_SEND_THIRD_FILE                   = -39, //��ȡ�����͵������ļ�
    ID_R_READ_SEND_FOURTH_FILE                  = -40, // ��ȡ�����͵��ĸ��ļ�
    ID_R_RECEIVE_LAST_DATA                      = -41, // ������������
    ID_R_CONNECT_SERVER                         = -42, // ���ӷ�����ʧ��
    ID_R_SAMV_BUSY                              = -43, // ��������SAMV ��æ
    ID_R_READ_SEND_FIFTH_FILE                   = -44, // ��ȡ�����͵�����ļ�
    ID_R_DATA_EMPTY                             = -45, // ����Ϊ��
    ID_R_MCU_RESET_ERROR                        = -46, // MCU��λ����
    ID_R_SAMV_RESET_ERROR                       = -47, // SAMV��λ����
    ID_R_SAMV_MANAGER_MESSAGE                   = -48, // SAMV������Ϣ
    ID_R_GET_SAMV_IP_PORT                       = -49, // ��ȡSAMV��ַ�˿ڴ���
    ID_R_GET_SAMV_LAST_ERROR                    = -50, // ��ȡSAMV������
    ID_R_CONNECT_WL_DECODER_SERVER              = -51, // ����wl���������ʧ��
    ID_R_CONNECT_DISPATCH_SERVER                = -52, // ���ӵ��ȷ�����ʧ��
    ID_R_SEND_COS_FALSE                         = -53, // ����COSָ��ʧ��
    ID_R_ZERO_DATA                              = -54, // ����ȫ��Ϊ0
    ID_R_COS_RESULT_ERROR                       = -55, // COS�������
    ID_R_SEND_NETWORK_ERROR                     = -56, // ���緢�ʹ���
    ID_R_RESET_PSAM                             = -57, // ��λPSAM
    ID_R_QUERY_PSAM_STATUS                      = -58, // ��ѯPSAM״̬ʧ��
    ID_R_GET_PSAM_MFKEY                         = -59, // ��ȡMFKEYʧ��
    ID_R_PROCESS_PSAM_VERIFY_LOCK_DATA          = -60, // ����У���������ʧ��
    ID_R_SEND_SAMV_DECODE_INFO                  = -61, // ���Ͱ�ȫģ�������Ϣʧ��
    ID_R_SET_APP_CONFIG                         = -62, // ����APP����
    ID_R_GET_APP_CONFIG                         = -63, // ��ȡAPP����
    ID_R_CLEAR_APP_CONFIG                       = -64, // ������� �ָ�Ĭ��ֵ
    ID_R_CHANGE_APP_CONFIG_PASSWORD             = -65, // �޸���������
    ID_R_POWER_ON_OFF                           = -66, // �򿪹رյ�Դ
    ID_R_GET_ANDROID_PHONE_STATE                = -67, // ��ȡandroid�ֻ�״̬��Ϣ����
    ID_R_GET_ANDROID_PHONE_IMEI                 = -68, // ��ȡandroid�ֻ�״̬IMEI��ϢΪ��
    ID_R_GET_ANDROID_CONTEXT_NULL               = -69, // ��ȡandroid�ֻ�״̬��Ϣ�����Ķ���Ϊ��
    ID_R_LED_ON_OFF                             = -70, // LED ���ش���
    ID_R_DOMAIN_NAME_ERROR                      = -71, // ��������
    ID_R_SELECT_DN_AID                          = -72, // ����֤DN�� ͨǰ���ļ�1
    ID_R_SELECT_DN_AID_RESULT                   = -73, // ����֤DN��������  ͨǰ���ļ�1
    ID_R_READ_DN_BINARY                         = -74, // ����֤DN��  ͨǰ���ļ�1
    ID_R_READ_DN_BINARY_RESULT                  = -75, // ����֤DN��������  ͨǰ���ļ�1
    ID_R_SAMV_TIME_OUT                          = -76, // ��ȫģ�鳬ʱ û�д��ڷ���
    ID_R_SAMV_USB_RECEIVE_TIME_OUT              = -77, // ��ȫģ�鳬ʱ USB ���ճ�ʱ
    ID_R_SAMV_HEAD_ERROR                        = -78, // ��ȫģ������ͷ����
    ID_R_SAMV_PACKAGE_DATA_SIZE                 = -79, // ���ݰ���С����
    ID_R_SAMV_CRC                               = -80, // ���ݰ�У�����
    ID_R_PARAM_NULL                             = -81, // ����Ϊ��
    ID_R_SAMV_COMMAND                           = -82, // ִ�а�ȫģ��ָ�����
    ID_R_GET_SAMV_UART_DATA_SIZE                = -83, // ��ȡ��ȫģ�鴮�����ݴ�С����
    ID_R_GET_SAMV_UART_DATA_SIZE_TIME_OUT       = -84, // ��ȡ��ȫģ�鴮�����ݴ�С��ʱ
    ID_R_SAMV_ERROR                             = -85, // ��ȫģ�����  ������� ȡ�������ݷ���
    ID_R_PASSWORD_NULL                          = -86, // ����Ϊ��
    ID_R_CALLBACK_NULL                          = -87, // �ص�����Ϊ��
    ID_R_LWIP_NOT_READY                         = -88, // LWIPδ׼����
    
    ID_R_SM4ENCRYPT_ERROR 						= -89, // SM4���ܳ���
    ID_R_SM2SIGN_ERROR 							= -90, // ǩ������
    ID_R_PARAM_NOT_INIT 						= -91, // ����δ��ʼ��
	ID_R_SM4DECRYPT_ERROR 						= -92, // SM4���ܳ���
	ID_R_SM2ENCRYPT_ERR 						= -93, // SM2���ܳ���
	ID_R_SM2DECRYPT_ERR 						= -94, // SM2���ܳ���
	ID_R_NET_SEND_ERR 							= -95, // ����ʧ��
	ID_R_NET_RECV_ERR 							= -96, // ����ʧ��
	ID_R_PACK_ERR 								= -97, // ���ʧ��
	ID_R_UNPACK_ERR 							= -98, // ���ʧ��
    ID_R_DNNUM_ERR                              = -99, // ��ȡDN��ʧ��

    ID_R_DESDECRYPT_ERR 						= -100,// DES���ܳ���
    ID_R_DESENCRYPT_ERR 						= -101,// DES���ܳ���

	ID_R_LRC_ERR 								= -102,// lrcУ��λ����(08)
	ID_R_MAC_ERR 								= -103,// MACУ���(A0)
	ID_R_READ_TIMES_ERR 						= -104,// ֤����ȡ��������(A1)
	ID_R_BUSINESS_ERR 							= -105,// ҵ�����(AA)
	ID_R_SERVER_ERR 							= -106,// �������ڲ�����(99)

    ID_R_UNKNOW                                 = -128, // δ֪����
} idreader_reply_code;

/**
 * @brief �����֤�ɹ���������
 */
typedef struct _id_card_info_struct
{
    char file_name[32];                 // �ļ�����, ��Ҫ��ȡ���֤ͼƬʱ, ���봫�뱣��ͼƬ�ļ����� (����Ҫ��׺����)
    char name[45 + 1];                  // ����
    char sex[6 + 1];                    // �Ա� (��: ��)
    char nation[16 + 1];                // ���� (��: ��)
    char birth_date[16 + 1];            // ���������� (��: 20210305)
    char id_num[36 + 1];                // ���֤��
    char address[110 + 1];              // סַ
    char signing_organization[60 + 1];  // ǩ������
    char begin_time[24 + 1];            // ��Ч����ʼ���� (��: 20210305)
    char end_time[24 + 1];              // ��Ч�ڽ�ֹ���� (��: 20210305)
    char dn_numb[65 + 1];               // DN��
    int image_width;                    // ͼƬ��� (��Ҫ����.bmp�ļ�ʱ����)
    int image_height;                   // ͼƬ�߶� (��Ҫ����.bmp�ļ�ʱ����)
} id_card_info_t;

/**
 * @brief �㴴
 */
typedef struct _idreader_param_t {
    char tusn[64];                      // �豸Ψһ��ʶ
    char dns[64];                       // idreaderͨѶ����
    char ip[64];                        // idreaderͨѶIP
    unsigned short port;                // idreaderͨѶ�˿�
} idreader_param_t;

/**
 * @brief ŵ��˹
 */
typedef struct _idreader_lotus_param_t {
    char dns[64];                       // ͨѶ����
    int userAccount;                    // �û��˺�
    char passWord[64];                  // ����
    int postcode;                       // ��������
    int lineType;                       // ��·���� 0=δ֪ 1=���� 2=��ͨ 3=�ƶ� 4=����
    unsigned int timeOutMs;             // ���ճ�ʱʱ�� (����) ��������Ϊ2*1000����
} idreader_lotus_param_t;

/**
 * @brief ������ͨ
 */
typedef struct _idreader_jlht_param_t {
	char SerPubKey[128+1];				//��������Կ
	char TermPubKey[128+1];				//�ն˹�Կ
	char TermPriKey[64+1];				//�ն�˽Կ
    char appid[32];                     //appid
    char tusn[32];                      //�豸Ψһ��ʶ
    char dns[64];                       //ͨѶ����
    char ip[32];                        //ͨѶIP
    unsigned short port;                //ͨѶ�˿�
    int declevel;						//�Ƿ��ȡ��Ƭ 0:����ȡ 1:��ȡ
    int read_len;						//���ζ�ȡ����(Ĭ��0xf0)
} idreader_jlht_param_t;

typedef struct _idreader_jlht_id_info_t {
	int len;						 // id����
    char id[64];                     // id
} idreader_jlht_id_info_t;

/**
 * @brief ��ˢ
 */
typedef struct _idreader_ls_param_t {
	char SerPubKey[128+1];				//��������Կ
	char TermPubKey[128+1];				//�ն˹�Կ
	char TermPriKey[64+1];				//�ն�˽Կ
	char terminalNo[16]; 				//�ն˱��
	char incomingKey[32];				//������Կ����
    char dns[64];                       //ͨѶ����
    char ip[32];                        //ͨѶIP
    unsigned short port;                //ͨѶ�˿�
    int encrytoMethod;					//���ܷ�ʽ 0:���� 1:����(Ŀǰֻ֧�ֹ���)
    int read_len;						//���ζ�ȡ����(Ĭ��0xf0)
} idreader_ls_param_t;

typedef struct _idreader_ls_id_info_t {
	int len;						// id����
    char id[64];                    // id
    char errstr[128];				// ���ڽ���0099ָ��صĴ�����Ϣ
} idreader_ls_id_info_t;

/**
 * @brief ���걦
 */
typedef struct _idreader_kdb_param_t {
	char version[24+1];				//�ն˰汾��
	char tusn[64];					//�豸Ψһ��ʶ
	char rootKey[16];				//����Կ
	char sm4key[16];				//sm4����1
    char dns[64];					//ͨѶ����
    char ip[32];					//ͨѶIP
    unsigned short port;			//ͨѶ�˿�
    int declevel;					//�Ƿ��ȡ��:0x00-����ȡ 0x01-��ȡ(Ŀǰֻ֧��0x01)
    int cardtype;					//֤����:0x01-���֤ 0x02-���֤REQID(Ŀǰֻ֧��0x02)
} idreader_kdb_param_t;

typedef struct _idreader_kdb_id_info_t {
    char name[45 + 1];                  // ����
    char id_num[36 + 1];                // ���֤��
    char signing_organization[60 + 1];  // ǩ������
    char begin_time[24 + 1];            // ��Ч����ʼ���� (��: 20210305)
    char end_time[24 + 1];              // ��Ч�ڽ�ֹ���� (��: 20210305)
    char address[110 + 1];              // סַ
    char task_id[32];					// ����id
} idreader_kdb_id_info_t;

typedef int (*pIdreaderCalSm4MacCb)(uint8_t *inbuf, int inlen, uint8_t *outbuf);

typedef struct {
    idreader_show_step step;
} idreader_notifypara_st;

typedef void (*display_callback)(idreader_notifypara_st *); // ��ʾ�ص�

typedef struct {
    display_callback disp;
} idreader_displayerobv_st;    // ��ʾ�۲��߽ṹ

/**
 * @brief: idreader������ʼ��
 * @param: idreader_param_t *para �����ṹ, ��ϸ��idreader_param_t����
 * @return 
 *   -<em> == 0   </em>  �ɹ�
 *   -<em> == ���� </em>  ʧ��
 */
extern int idreader_init(idreader_param_t *para);

/**
 * @brief: ע����ʾ�۲��ߣ�Ŀǰ��֧��һ���۲���
 * @param: displayerobv_st *obv Ҫע��۲��߽ṹָ��
 * @return
 *   -<em> == 0   </em>  �ɹ�
 *   -<em> == ���� </em>  ʧ��
 */
extern int idreader_registedisplayer(idreader_displayerobv_st *obv);

/**
 * @brief ��ȡ�����Ϣ�ӿں��� (ֻ���ı���Ϣ)
 * @param id_card_info_t *id_card_info �����ṹ, ��ϸ��id_card_info_t����
 * @param: terfunckeys �����ض��˳�ֵ, ������KEY_INVALID��Ϊ����, KEY_INVALID������, 
 *                  (���ô�ֵ�˳�ʱ������Ӧ����ֵ)
 * @param: time_s������ʱʱ�� (S)
 * @return ��ȡ�Ľ��
 *   -<em> == 0   </em>  �ɹ�
 *   -<em> == ���� </em>  ʧ��
 */
extern int idreader_read_info(id_card_info_t *id_card_info, uint8_t *terfunckeys, int time_s);

/**
 * @brief ��ȡ�����Ϣ�ӿں��� (�ɶ����֤ͼƬ)
 * @param[in]: 
 *      ppbmpbuf     bmp��������, (mode!=R_TEXT) �� (file_mode==IMAGE_SAVE_BUFF) ʱʹ��
 *      bmplen       bmp���ݳ���, (mode!=R_TEXT) �� (file_mode==IMAGE_SAVE_BUFF) ʱʹ��
 *      file_mode    ���ݴ洢ģʽ (֧��bufferģʽ��fileģʽ,bufferģʽ��Ҫ������ʹ�ú��ͷ�bitmap�ڴ�)
 *      mode ��ȡ���֤ģʽ, ��ϸ��idreader_read_mode����
 *      terfunckeys �����ض��˳�ֵ, ������KEY_INVALID��Ϊ����, KEY_INVALID������(���ô�ֵ�˳�ʱ������Ӧ����ֵ)
 *      time_s������ʱʱ�� (S)
 * @param[out]: id_card_info_t *id_card_info �����ṹ, ��ϸ��id_card_info_t����
 * @return ��ȡ�Ľ��
 *   -<em> == 0   </em>  �ɹ�
 *   -<em> == ���� </em>  ʧ��
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
 * @brief: jpeg��ʽ�ļ�ת��bmp��ʽ�ļ�
 * @param[in]: 
 *      ppbmpbuf     bmp��������
 *      bmplen       bmp���ݳ���
 *      file_mode    ���ݴ洢ģʽ (֧��bufferģʽ��fileģʽ,bufferģʽ��Ҫ������ʹ�ú��ͷ�bitmap�ڴ�)
 *      file_name:   jpegͼƬ�ļ�����, ����Ҫ�Ӻ�׺; ������ͬ���Ƶ�bmpͼƬ, ��׺����ͬ
 *      ppath:       Ӧ�ù���Ŀ¼·��
 * @param[out]: 
 *      bmp_width:   ͼƬ���
 *      bmp_height: ͼƬ�߶�
 * @return:
 *   -<em> == 0   </em>  �ɹ�
 *   -<em> == ���� </em>  ʧ��
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
 * @brief: �ͷ�idreader_read_info_ex����idreader_jpeg2bmp����ppbmpbuf�ڴ�
 * @param[in]: 
 *      ppbmpbuf     bmp��������
 * @return:
 *      0-�ɹ�
 *      ����-ʧ��
 */
extern int idreader_release_bmpbuf(uint8_t **ppbmpbuf);

/**
 * @brief: idreader������ʼ��
 * @param: idreader_param_t *para �����ṹ, ��ϸ��idreader_param_t����
 * @return 
 *   -<em> == 0   </em>  �ɹ�
 *   -<em> == ���� </em>  ʧ��
 */
extern int idreader_lotus_init(idreader_lotus_param_t *para);

/**
 * @brief ��ȡ�����Ϣ�ӿں��� (����ŵ��˹�ӿ�)
 * @param id_card_info_t *id_card_info �����ṹ, ��ϸ��id_card_info_t����
 * @param: terfunckeys �����ض��˳�ֵ, ������KEY_INVALID��Ϊ����, KEY_INVALID������, 
 *                  (���ô�ֵ�˳�ʱ������Ӧ����ֵ)
 * @param: time_s������ʱʱ�� (S)
 * @return ��ȡ�Ľ��
 *   -<em> == 0   </em>  �ɹ�
 *   -<em> == ���� </em>  ʧ��
 */
extern int idreader_read_info_lotus(id_card_info_t *id_card_info, uint8_t *terfunckeys, int time_s);

/**
 * @brief: ������ͨ������ʼ��
 * @param: idreader_jlht_param_t *para �����ṹ, ��ϸ��idreader_jlht_param_t����
 * @return 
 *   -<em> == 0   </em>  �ɹ�
 *   -<em> == ���� </em>  ʧ��
 */
extern int idreader_jlht_init(idreader_jlht_param_t *para);

/**
 * @brief ��ȡ�����Ϣ�ӿں��� (������ͨ�ӿ�)
 * @param idreader_jlht_id_info_t��ϸ��idreader_jlht_id_info_t����
 * @param: terfunckeys �����ض��˳�ֵ, ������KEY_INVALID��Ϊ����, KEY_INVALID������, 
 *                  (���ô�ֵ�˳�ʱ������Ӧ����ֵ)
 * @param: time_s������ʱʱ�� (S)
 * @return ��ȡ�Ľ��
 *   -<em> == 0   </em>  �ɹ�
 *   -<em> == ���� </em>  ʧ��
 */
extern int idreader_read_info_jlht(idreader_jlht_id_info_t *idinfo, unsigned char *terfunckeys, int time_s);

/**
 * @brief: ��ˢ������ʼ��
 * @param: idreader_ls_param_t *para �����ṹ, ��ϸ��idreader_ls_param_t����
 * @return 
 *   -<em> == 0   </em>  �ɹ�
 *   -<em> == ���� </em>  ʧ��
 */
extern int idreader_ls_init(idreader_ls_param_t *para);

/**
 * @brief ��ȡ�����Ϣ�ӿں��� (��ˢ�ӿ�)
 * @param idreader_ls_id_info_t��ϸ��idreader_ls_id_info_t����
 * @param: terfunckeys �����ض��˳�ֵ, ������KEY_INVALID��Ϊ����, KEY_INVALID������, 
 *                  (���ô�ֵ�˳�ʱ������Ӧ����ֵ)
 * @param: time_s������ʱʱ�� (S)
 * @return ��ȡ�Ľ��
 *   -<em> == 0   </em>  �ɹ�
 *   -<em> == ���� </em>  ʧ��
 */
extern int idreader_read_info_ls(idreader_ls_id_info_t *idinfo, unsigned char *terfunckeys, int time_s);

/**
 * @brief ��ȡ�����Ϣ�ӿں��� (���걦�ӿ�)
 * @param idreader_kdb_param_t��ϸ��idreader_kdb_param_t����
 * @param pCbΪ����SM4 MACֵ�Ļص����������崫�����pIdreaderCalSm4MacCb����
 * @param idreader_kdb_id_info_t��ϸ��idreader_kdb_id_info_t����
 * @param errstr���ڽ��պ�̨���صĴ���������Ϣ�������̨û�з��ش�����Ϣ������ռ��СΪ128�ֽڼ���
 * @param: terfunckeys �����ض��˳�ֵ, ������KEY_INVALID��Ϊ����, KEY_INVALID������, 
 *                  (���ô�ֵ�˳�ʱ������Ӧ����ֵ)
 * @param: time_s������ʱʱ�� (S)
 * @return ��ȡ�Ľ��
 *   -<em> == 0   </em>  �ɹ�
 *   -<em> == ���� </em>  ʧ��
 */
extern int idreader_read_info_kdb(idreader_kdb_param_t *para, pIdreaderCalSm4MacCb pCb, idreader_kdb_id_info_t *idinfo, char *errstr, unsigned char *terfunckeys, int time_s);

/**
 * @brief ��ȡ���DN��
 * @param[out]: dnData      DN����Ϣ
 * @param[in]: dnLen        dnData����󳤶�
 * @param[out]: dnLen       ��ȡ��dnData�ĳ���
 * @param[in]: terfunckeys      �����ض��˳�ֵ, ������KEY_INVALID��Ϊ����, KEY_INVALID������, 
 *                              (���ô�ֵ�˳�ʱ������Ӧ����ֵ)
 * @param[in]: time_s       ������ʱʱ�� (S)
 * @return ��ȡ�Ľ��
 *   -<em> == 0   </em>  �ɹ�
 *   -<em> == ���� </em>  ʧ��
 */
extern int idreader_read_dn_num(char *dnData, int *dnLen, uint8_t *terfunckeys, int time_s);

/**
 * @brief ��ȡ�ͻ�libidreader��SDK�İ汾��Ϣ
 * @param[out] 
 *		version: libidreader��SDK�İ汾��Ϣ���
 * @param[in] 
 *		size:	 versionִ�е�buffer����, ��������64�ֽ�
 * @return ��ȡ�Ľ��
 *	 -<em> == 0   </em>  �ɹ�
 *	 -<em> == -1 </em>	ʧ��
 */
extern int idreader_get_sdk_version(char *version, int size);

/**
 * @brief ��ȡlibidreader��İ汾��Ϣ
 * @param[out] 
 *		version: libidreader��İ汾��Ϣ���
 * @param[in] 
 *		size:	 versionִ�е�buffer����, ��������64�ֽ�
 * @return ��ȡ�Ľ��
 *	 -<em> == 0   </em>  �ɹ�
 *	 -<em> == -1 </em>	ʧ��
 */
extern int idreader_get_version(char *version, int size);

/**
 * @brief �����ض����� (���ý�����ͨ��ŵ��˹)
 * @param[in] 
 *		num: ���ô���
 * @return ����ʵ���ض�����
 */
extern int idreader_set_retry_num(int num);

#ifdef __cplusplus
}
#endif

#endif
