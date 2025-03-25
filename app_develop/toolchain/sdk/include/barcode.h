/**
 @if Chinese
	 * @brief       ��ģ���������� <strong>ɨ��ģ��</strong> ��صĽӿ�
	 * @author      Jezz
	 * @date        2018-11-02
	 * @version     V1.0
	 *
	 * @remarks Change History:
	 * Date          | Version       | Author          | Desc
	 * ------------- | ------------- | --------------- | ----
	 * 2018/11/02    | 1.0.0         | Jezz            | �����ļ�
	 * 2022/04/20    | 1.0.1         | Wenming         | ����Ӣ��ע��
 @else	 
	* @brief       This module is used to describe <strong> Barcode </strong> interfaces module
	 * @author      Jezz
	 * @date        2018-11-02
	 * @version     V1.0
	 *
	 * @remarks Change History:
	 * Date          | Version       | Author          | Desc
	 * ------------- | ------------- | --------------- | ----
	 * 2018/11/02    | 1.0.0         | Jezz            | Create file
	 * 2022/04/20    | 1.0.1         | Wenming         | Add English description
 @endif	 
*/


/**
 @if Chinese
	* @defgroup barcode ɨ��
 @else	
	* @defgroup barcode Barcode
 @endif	 	
 * @{
*/


#ifndef __BARCODE_H__
#define __BARCODE_H__

#include <stdint.h>
//#include <syscall.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

 /**
@if Chinese
	* @brief ɨ��ɹ��Ļص����� 
 @else
	* @brief Callback function for successful code scanning 
@endif
 */
typedef int (*bar_callback_t)(uint8_t *data, uint32_t type, uint32_t len);

/**
 @if Chinese
	@brief  ��ö���г���ɨ��������������.
 @else	 	
	@brief  This enumeration lists the code type of the result of the scan.
 @endif			
 */
typedef enum {
    FORMAT_UNKNOWN      = -1,           /**<  Unkown format. */
    FORMAT_CODABAR      = (1 << 0),     /**<  CODABAR 1D format. */
    FORMAT_CODE_39      = (1 << 1),     /**<  Code 39 1D format. */
    FORMAT_CODE_128     = (1 << 2),     /**<  Code 128 1D format. */
    FORMAT_ITF          = (1 << 3),     /**<  ITF (Interleaved Two of Five) 1D format. */
    FORMAT_EAN_8        = (1 << 4),     /**<  EAN-8 1D format. */
    FORMAT_EAN_13       = (1 << 5),     /**<  EAN-13 1D format. */
    FORMAT_UPC_A        = (1 << 6),     /**<  UPC-A 1D format. */
    FORMAT_UPC_E        = (1 << 7),     /**<  UPC-E 1D format. */
    FORMAT_QR_CODE      = (1 << 8),     /**<  QR Code 2D barcode format. */
} BarcodeFormat;

/**
 @if Chinese
	* @brief  ��ö���г���ɨ��ӿ�֧�ֵ�ģʽ.
 @else	 	
	* @brief  This enumeration lists the modes supported by the scan interface.
 @endif		
 */
typedef enum {
    BAR_MODE_CONTINUE           = 0,    /**<@if Chinese	֧��һά�롢��ά�롢����ɨ����	@else Support one-dimensional code, two-dimensional code, continuous scanning code @endif*/
    BAR_MODE_ONCE               = 1,    /**<@if Chinese	֧��һά�롢��ά�룬ֻɨ��һ�κ��	@else Support one-dimensional code, two-dimensional code, only scan once after open @endif*/
    BAR_MODE_MOTIONDETECT       = 2,    /**<@if Chinese	����֧�ֵġ�֧��һά��Ͷ�ά�롣����⵽ͼ�����ȱ仯ʱ����ɨ���룬������BAR_MODE_CONTINUE��ͬ	@else Not supported. One-dimensional code and two-dimensional code are supported. Scan codes are emitted when image brightness changes are detected, otherwise the same as BAR_MODE_CONTINUE @endif*/
    BAR_MODE_ONED_ONLY          = 3,    /**<@if Chinese	��֧��BAR_MODE_CONTINUE��ֻɨ��һ��ά�ȴ��룬������BAR_MODE_CONTINUE��ͬ	@else BAR_MODE_CONTINUE is not supported. Only one dimension code is scanned, otherwise the same as BAR_MODE_CONTINUE @endif*/
    BAR_MODE_MOTIONDETECT_MINI  = 4,    /**<@if Chinese	��֧�ִ˲�������BAR_MODE_MOTIONDETECT��ͬ�����Ƽ�ʹ��	@else This parameter is not supported. It is the same as BAR_MODE_MOTIONDETECT and is not recommended @endif*/
} BarcodeMode;

#define BAR_MAGIC                       'B'				/**< 'B' */
#define BAR_IOCTL_SET_SOUND             (BAR_MAGIC + 0)	/**< 'B'+0 */
#define BAR_IOCTL_SET_READ_CALLBACK     (BAR_MAGIC + 1)	/**< 'B'+1 */
#define BAR_IOCTL_SET_TIMEOUT           (BAR_MAGIC + 2)	/**< 'B'+2 */
#define BAR_IOCTL_SET_PREVIEW           (BAR_MAGIC + 3)	/**< 'B'+3 */
#define BAR_IOCTL_SET_PREVIEW_POS       (BAR_MAGIC + 4) /**< 'B'+ 4*/

#define RED_LED         0x00            /**< red light */
#define WHITE_LED       0x01            /**< white light */

/**
 @if Chinese
	@brief ɨ�����ݽṹ��
 @else
	@brief Scan data structure
 @endif
*/
struct symbol_res_t {
    int   type;			/**<scan type*/
    int   len;			/**<scan length*/
    char *data;			/**<scan data*/
};

/**
 @if Chinese
	@brief download������õ��˽ṹ�壬��ͨӦ�ó����ò��� 
 @else
	@brief Download programs use this structure, not normal applications
 @endif
*/
struct bar_data_t {
    const char *data; 	/**<scan data*/
    char type;			/**<scan type*/
    char len; 			/**<scan length*/
};

/**
 @if Chinese
	* @brief  ��ɨ���豸
	* @param[in]  name	-	��������
	* @param[in]  mode	-	������
	* @return	0		-	�ɹ� 
	* @return	-1		-	ʧ��
	* @code
	#define CAMERA_PREVIEW   (1 << 16)
	int fd;
	fd = bar_open("/dev/barcode", BAR_MODE_ONCE | CAMERA_PREVIEW); //open��ֻɨ��һ�� + Ԥ��
	bar_close(fd);
	* @endcode
 @else
	* @brief  Turn on the code scanning device
	* @param[in]  name	-	Device name
	* @param[in]  mode	-	Open type
	* @return 		0	-	success 
	* @return 		-1	-	fail
	* @code
	#define CAMERA_PREVIEW   (1 << 16)
	int fd;
	fd = bar_open("/dev/barcode", BAR_MODE_ONCE | CAMERA_PREVIEW); //scan only once + preview
	bar_close(fd);
	* @endcode
 @endif		
 */
int bar_open(const char *name, int mode);

/**
 @if Chinese
	 * @brief  �����������
	 * @param[in]  fd	-	������
	 * @param[in]  cmd	-	BAR_IOCTL_SET_SOUND         ����ɨ������ arg:1 ���� arg:0 ����<br>
	 *          			BAR_IOCTL_SET_READ_CALLBACK ����ɨ��ɹ���Ļص���������ʽΪ @ref bar_callback_t
	 * @param[in]  arg	-	�� cmd ��Ӧ
	 * @return	0	-	�ɹ� 
	 * @return	-1	-	ʧ��
	 * @code
		int fd;
		int res;
		fd = bar_open("/dev/barcode", BAR_MODE_ONCE); //open��ֻɨ��һ��

		res = bar_ioctl(fd, BAR_IOCTL_SET_PREVIEW, TRUE); //TRUE:��Ԥ�� FALSE:�ر�Ԥ��
		if (!res) {
			//---- display code ----
			lcd_flip();
		}

		bar_close(fd);
	 * @endcode
 @else	 
	* @brief  Setting Bar Code Parameters
	* @param[in]  fd	-	the descriptor
	* @param[in]  cmd	-	BAR_IOCTL_SET_SOUND	-	Set scan sound(arg:1 sound, arg:0 silent);<br>
							BAR_IOCTL_SET_READ_CALLBACK	-	Sets the callback function after a successful scan��In the form of @ref bar_callback_t
	* @param[in]  arg	-	With CMD corresponding
	* @return 		0	-	success 
	* @return 		-1	-	fail
	 * @code
		int fd;
		int res;
		fd = bar_open("/dev/barcode", BAR_MODE_ONCE); //Scan only once after open

		res = bar_ioctl(fd, BAR_IOCTL_SET_PREVIEW, TRUE); //TRUE:Open the preview   FALSE:Close the preview
		if (!res) {
			//---- display code ----
			lcd_flip();
		}

		bar_close(fd);
	 * @endcode
 @endif	 
 */
int bar_ioctl(int fd, unsigned int cmd, unsigned long arg);

/**
 @if Chinese
	* @brief  ֹͣ����ɨ��
	* @param[in]  fd	-	������
	* @return	0	-	�ɹ� 
	* @return	-1	-	ʧ��
 @else
	* @brief  Stop Bar Code Scanning
	* @param[in]  fd	-	The descriptor
	* @return 		0	-	success 
	* @return 		-1	-	fail
@endif
 */
int bar_close(int fd);

/**
 @if Chinese
	* @brief       ͬ����ȡɨ����
	* @note        ������ݲ�֧�ַ�������Ľ������	
	* @param[in]   fd			-	������
	* @param[out]  data			-	�洢��������������buffer
	* @param[out]  len			-	��������ȡ���������ݳ��ȣ�����ʵ�ʶ�ȡ�����볤��
	* @param[in]   type			-	�洢��������������ͣ������������������ͣ��ɴ����
	* @param[in]   wait_time	-	�ȴ�ʱ�䣬��λms
	* @return	0	-	�ɹ� 
	* @return	-1	-	ʧ��
 @else	 
	 * @brief       Read scan results synchronously
	 * @note        The decoder library does not support the decoding operation of reverse display bar code
	 * @param[in]   fd		-	The descriptor
	 * @param[out]	data	-	Store the read bar code data buffer
	 * @param[out]  len		-	Enter the data length of the bar code to be read and return the actual length of the bar code to be read
	 * @param[in]   type	-	Type of the bar code to be read;If you do not care about the bar code type, you can pass NULL
	 * @param[in]   wait_time	-	Waiting time,  in milliseconds
	* @return 		0	-	success 
	* @return 		-1	-	fail
 @endif	 
 */
int bar_read(int fd, void *data, int *len, int *type, int wait_time);

/**
 @if Chinese
	 * @brief  �ƹ����
	 * @param[in]	id		-	0 ��� 1 �׵�
	 * @param[in]	mode	-	0 �� 1 ��
 @else	 
	* @brief  Light control
	 * @param[in]  id		-	0:red light, 1:white light
	 * @param[in]  mode		-	0:turn off, 1:turn on
 @endif	 
 */
void bar_led_ctrl(int id, int mode);

/**
 @if Chinese
	* @brief  ��ȡ�Ƶ�����״̬
	* @param[in]  id	-	0:��� 1:�׵�
	* @return	0	-	��
	* @return	1	-	��
@else
	* @brief  Gets the indicator status
	* @param[in]  id	-	0-red light 1-white light
	* @return	0	-	turn off
	* @return	1	-	turn on
@endif	
 */
int bar_get_led_status(int id);

/**
 @if Chinese
	 * @brief  ��ȡ��ǰ֧�ֽ�������
	 * @return	֧�ֽ�������,�ο�BarcodeFormat
 @else	 
	 * @brief  Gets the current supported decoding type
	 * @return	Supported decoding types,refer to BarcodeFormat
 @endif	 
 */
unsigned int get_barcode_formats(void);

/**
 @if Chinese
	* @brief  ���ý�������
	* @note   ÿһλbit����һ������
	* @param[in]	formats	-	֧�ֽ�������
	* @return		0		-	�ɹ�
	* @return		����	-	ʧ��
	* @code
	unsigned int format;
	format = FORMAT_CODE_39 | FORMAT_CODE_128 | FORMAT_QR_CODE | FORMAT_EAN_13;
	set_barcode_formats(format);
	* @endcode
 @else
	* @brief  Set the decoding type
	* @note   Each bit represents a type
	* @param[in]  formats	-	Supported decoding types
	* @return		0		-	success
	* @return		other	-	fail
	* @code
	unsigned int format;
	format = FORMAT_CODE_39 | FORMAT_CODE_128 | FORMAT_QR_CODE | FORMAT_EAN_13;
	set_barcode_formats(format);
	* @endcode
 @endif	
 */
int set_barcode_formats(unsigned int formats);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BARCODE_H__ */

/** @} */

