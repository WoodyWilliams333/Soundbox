#include <stdio.h>
#include <stdlib.h>
#include <apperrdef.h>
#include <apperrdefex.h>
#include <appprinter.h>
#include <appfile.h>
#include <zint.h>


#include "appprinterex.h"
#include "libapiext.h"


#include "logger.h"

#define QR_PRT_FILE    "qrprt.bmp"

int app_prt_printf_qrcode(int x, int y, int width1, int height1, int qrbmpwidth, const char *qrstr)
{
	 int iret = 0;
	 int iBmpWidth = 150, iBmpHeiht = 150;
	 char work_path[256] = {0};
	 char file_path[256] = {0};
	 int iBmpLen = 0, iZoom = 0;
	 uint8_t *pBmpData = NULL;
	 

	 iBmpWidth=width1;
	 iBmpHeiht=height1;
	 zint_set_qrcode_level(2); //打印彩屏和黑白屏容错等级都是2 210519
	 zint_set_qrcode_scale(0.5); //先不缩放 210519
	 zint_set_expect_qrcode_width(21); //设置预期的宽度是最小的宽度 210519
	 app_file_get_workdir(work_path,sizeof(work_path));
	 snprintf(file_path, sizeof(file_path), "%s/%s", work_path, QR_PRT_FILE);
	 logger_debug("qr file = %s,qrstr=%s\n", file_path,qrstr);
	 iret = zint_create_qrcode(&pBmpData, &iBmpLen, &iBmpWidth, &iBmpHeiht, 
					qrstr, file_path, ZINT_BUFFER_FULL_MODE); //改成BUFFER模式 210519
	 logger_debug("qr file = %s,qrstr=%s,iret=%d\n", file_path,qrstr,iret);
	 logger_debug("qr qrbmpwidth = %d,iBmpWidth=%d\n", qrbmpwidth,iBmpWidth);
	 
	 if( iret == 0){
	 	iZoom = qrbmpwidth/iBmpWidth; //期望宽度除以实际宽度，得到缩放倍数 210519
		if((qrbmpwidth%iBmpWidth) > (iBmpWidth/2)){ //余数大于实际宽度的一半，则倍数加1 210519
			iZoom++;
		}
		logger_debug("iZoom = %d\n", iZoom);
		if(iZoom > 0){ //缩放倍数大于0 210525
			zint_release_qrcode(&pBmpData);//释放内存 210519
			zint_set_qrcode_scale(iZoom*0.5); //设置缩放倍数，zint库会乘以2 210519
			zint_set_expect_qrcode_width(qrbmpwidth); //设置完缩放之后还要设置下预期宽度
			iret = zint_create_qrcode(&pBmpData, &iBmpLen, &iBmpWidth, &iBmpHeiht, 
				qrstr, file_path, ZINT_BUFFER_FULL_MODE);
			logger_debug("zint_create_qrcode iret=%d qrbmpwidth = %d,iBmpWidth=%d\n", iret,qrbmpwidth,iBmpWidth);
			if(iret != 0){
				return iret;
			}
		}
		app_prt_printf_bmp_buffer(x, y, pBmpData, iBmpLen, iBmpWidth, iBmpHeiht, PRT_MID);
		zint_release_qrcode(&pBmpData);
	 }
	 return iret;
}

