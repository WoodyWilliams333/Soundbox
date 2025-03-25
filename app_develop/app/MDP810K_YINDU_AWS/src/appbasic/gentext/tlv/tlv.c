#include <stdio.h>
#include <string.h>

#include "basicext.h"
#include "libapiext.h"

#include "tlv.h"

int IsConstructedTag(uint16_t uiTag)
{
	int		i;

	for(i=0; (uiTag&0xFF00) && i<2; i++)
	{
		uiTag >>= 8;
	}

	return ((uiTag & TAGMASK_CONSTRUCTED)==TAGMASK_CONSTRUCTED);
}



int GetTlvValue(uint8_t **ppsTLVString, int iMaxLen, SaveTLVData pfSaveData, uint8_t bExpandAll)
{
	int iRet,iFlag=0;
	uint8_t *psTag, *psSubTag;
	uint16_t uiTag, uiLenBytes;
	uint32_t lTemp;

	for(psTag=*ppsTLVString; psTag<*ppsTLVString+iMaxLen; psTag++)
	{
		if( (*psTag!=NULL_TAG_1) && (*psTag!=NULL_TAG_2) )
		{
			break;
		}
		if(*psTag==NULL_TAG_2)
			iFlag=1;
	}
	if( psTag>=*ppsTLVString+iMaxLen )
	{
		*ppsTLVString = psTag;
		return 0;
	}

	uiTag = *psTag++;
	if(( (uiTag & TAGMASK_FIRSTBYTE)==TAGMASK_FIRSTBYTE )||(iFlag==1))
	{
		uiTag = (uiTag<<8) + *psTag++;
	}
	if( psTag>=*ppsTLVString+iMaxLen )
	{
		return -1;
	}

	if( (*psTag & LENMASK_NEXTBYTE)==LENMASK_NEXTBYTE )
	{
		uiLenBytes = *psTag & LENMASK_LENBYTES;
		pub_char2long(psTag+1, uiLenBytes, &lTemp);
	}
	else
	{
		uiLenBytes = 0;
		lTemp      = *psTag & LENMASK_LENBYTES;
	}
	psTag += uiLenBytes+1;
	if( psTag+lTemp>*ppsTLVString+iMaxLen ){
		return -2;
	}
	*ppsTLVString = psTag+lTemp;

	(*pfSaveData)(uiTag, psTag, (int)lTemp);
	if( !IsConstructedTag(uiTag) || !bExpandAll )
	{
		return 0;
	}

	for(psSubTag=psTag; psSubTag<psTag+lTemp; )
	{
		iRet = GetTlvValue(&psSubTag, psTag+lTemp-psSubTag, pfSaveData, app_true);
		if( iRet<0 )
		{
			return iRet;
		}
	}

	return 0;
}

// 解析TLV参数
int UnpackTlvData(uint8_t * pTlvData, int TlvLen, SaveTLVData pfSaveData)
{
	int	iRet;
	uint8_t	*psTemp, *psTLVData;
	
	//iTotalLen = ByteToShort(glRecvPack.sField62) - 1;
	//psTLVData = &glRecvPack.sField62[2+1];	// bit 62: len(2) + control(1) + TLV Data(n)

	psTLVData = pTlvData;
	for(psTemp=psTLVData; psTemp<psTLVData+TlvLen; )
	{
		iRet = GetTlvValue(&psTemp, psTLVData+TlvLen-psTemp, pfSaveData, app_false);
		if( iRet<0 ){
			return E_TRANS_FAILED;
		}
	}
	
	return RET_OK;
}

// 只处理基本数据元素Tag,不包括结构/模板类的Tag
void MakeTlvString(uint16_t uiTagNum, uint8_t *psData, int iLength, uint8_t **ppsOutData)
{
	uint8_t	*psTemp;

	if( iLength<=0 )
	{
		return;
	}

	psTemp = *ppsOutData;
	if( uiTagNum & 0xFF00 )
	{
		*psTemp++ = (uint8_t)(uiTagNum >> 8);
	}
	*psTemp++ = (uint8_t)uiTagNum;	
	if( iLength<=127 )	// 目前数据长度均小余127字节,但仍按标准进行处理
	{
		*psTemp++ = (uint8_t)iLength;
	}
	else
	{	
		*psTemp++ = 0x81;
		*psTemp++ = (uint8_t)iLength;
	}	
	memcpy(psTemp, psData, iLength);
	psTemp += iLength;	
	*ppsOutData = psTemp;
}

void MakeTlvString_Field59(uint16_t uiTagNum, uint8_t *psData, int iLength, uint8_t **ppsOutData)
{
	uint8_t	*psTemp;

	if( iLength<0 )
	{
		return;
	}

	psTemp = *ppsOutData;
	sprintf((char*)psTemp, "%02X", uiTagNum);
    psTemp += 2;

    sprintf((char*)psTemp, "%03d", iLength);
    psTemp += 3;
	
	memcpy(psTemp, psData, iLength);
	psTemp += iLength;	
	*ppsOutData = psTemp;
}




