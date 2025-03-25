
#ifndef _BIN_DATA_H_
#define _BIN_DATA_H_

#define TMS_MAX_PACKET_LEN 4000+10  //tms_ok


typedef struct{
	int len;
	unsigned char data[TMS_MAX_PACKET_LEN+4];   //uint8_t
	
}ST_BIN_DATA;
#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

extern ST_BIN_DATA sendPacket, recvPacket;

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif

