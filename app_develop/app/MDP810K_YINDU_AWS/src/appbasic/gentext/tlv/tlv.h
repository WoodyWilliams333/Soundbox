
#ifndef _TLV_H_
#define _TLV_H_


#define TAGMASK_CLASS			0xC0	
#define TAGMASK_CONSTRUCTED		0x20	
#define TAGMASK_FIRSTBYTE		0x1F	
#define TAGMASK_NEXTBYTE		0x80	

#define LENMASK_NEXTBYTE		0x80	
#define LENMASK_LENBYTES		0x7F	

#define NULL_TAG_1				0x00	
#define NULL_TAG_2				0xFF	

typedef void (*SaveTLVData)(uint16_t uiTag, uint8_t *psData, int iDataLen);
typedef void (*SaveTLVDataStandard)(uint32_t uiTag, uint8_t *psData, int iDataLen);


int GetTlvValue(uint8_t **ppsTLVString, int iMaxLen, SaveTLVData pfSaveData, uint8_t bExpandAll);
int UnpackTlvData(uint8_t * pTlvData, int TlvLen, SaveTLVData pfSaveData);
void MakeTlvString(uint16_t uiTagNum, uint8_t *psData, int iLength, uint8_t **ppsOutData);
void MakeTlvString_Field59(uint16_t uiTagNum, uint8_t *psData, int iLength, uint8_t **ppsOutData);


#endif

