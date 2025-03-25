#ifndef _APP_BMP_H_
#define _APP_BMP_H_

typedef enum {
    IMAGE_STATE_FILE = 0,                // bmpͼƬ����Ϊ�ļ�ģʽ
    IMAGE_STATE_BUFF,                    // bmpͼƬ����Ϊ����ģʽ
}app_bmp_image_data_mode;

typedef enum {
    APP_BMP_R_OK                =  0, // ͼƬת���ɹ�
    APP_BMP_R_PARAM_NULL        = -1, // ����Ϊ��
    APP_BMP_R_E_FILE_OPEN       = -2, // �ļ���ʧ��
    APP_BMP_R_E_FILE_RD         = -3, // �ļ���ȡʧ��
    APP_BMP_R_E_FILE_WR         = -4, // �ļ�д��ʧ��
    APP_BMP_R_E_FILE_CREAT      = -5, // �����ļ�ʧ��
    APP_BMP_R_NO_MEM            = -6, // �ڴ治��
}app_bmp_reply_code;

/**
 * @brief: bmpͼƬ�������Ŵ������С (Դ������fileģʽ��ʽ����, ���ʱ����ͨ��fileModeѡ��bufferģʽ����fileģʽ)
 * @param[in]: 
 *      psrcBmpPath     Դͼ�ļ����·��
 *      poutBmpPath     ����ͼƬ���·��
 *      ppoutBmpBuf     bmp��������
 *      outBmpLen       bmp���ݳ���
 *      fileMode        ������ݴ洢ģʽ (֧��bufferģʽ��fileģʽ, bufferģʽ��Ҫ������ʹ�ú��ͷ�ppoutBmpBuf�ڴ�)
 *      scale:          Դͼ���ű��� (���紫��ֵΪ0.5ʱ��ʾͼƬ��СΪԴͼ��0.5��, ����ֵΪ1.5ʱ��ʾͼƬ�Ŵ�ΪԴͼ��1.5��)
 * @param[out]: 
 *      ppoutBmpBuf     bmp��������
 *      outBmpLen       bmp���ݳ���
 *      bmpWidth        ����ͼƬ���
 *      bmpHeight       ����ͼƬ�߶�
 * @return:
 *   -<em> == 0   </em>  �ɹ�
 *   -<em> == ���� </em>  ʧ��
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
 * @brief: bmpͼƬ�������Ŵ������С (Դ������bufferģʽ��ʽ����, ���ʱ����ͨ��fileModeѡ��bufferģʽ����fileģʽ)
 * @param[in]: 
 *      psrcBmpBuf      Դͼ����
 *      poutBmpPath     ����ͼƬ���·�� (fileģʽʱ��Ҫ�����ֵ)
 *      ppoutBmpBuf     bmp��������
 *      outBmpLen       bmp���ݳ���
 *      fileMode        ������ݴ洢ģʽ (֧��bufferģʽ��fileģʽ, bufferģʽ��Ҫ������ʹ�ú��ͷ�ppoutBmpBuf�ڴ�)
 *      scale:          Դͼ���ű��� (���紫��ֵΪ0.5ʱ��ʾͼƬ��СΪԴͼ��0.5��, ����ֵΪ1.5ʱ��ʾͼƬ�Ŵ�ΪԴͼ��1.5��)
 * @param[out]: 
 *      ppoutBmpBuf     bmp��������
 *      outBmpLen       bmp���ݳ���
 *      bmpWidth        ����ͼƬ���
 *      bmpHeight       ����ͼƬ�߶�
 * @return:
 *   -<em> == 0   </em>  �ɹ�
 *   -<em> == ���� </em>  ʧ��
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
 * @brief: �ͷ�app_bmp_image_file_scale/app_bmp_image_dat_scale����ppbmpBuf�ڴ�
 * @param[in]: 
 *      ppbmpBuf     bmp��������
 * @return:
 *      0-�ɹ�
 *      ����-ʧ��
 */
extern int app_bmp_release_bmpbuf(uint8_t **ppbmpBuf);

#endif

