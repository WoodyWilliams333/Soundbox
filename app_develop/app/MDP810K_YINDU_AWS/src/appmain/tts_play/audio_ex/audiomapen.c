#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "fixaudio.h"
#include "fixaudioen.h"
#include "tts_play.h"
#include "codestool.h"
#include "audiomap.h"
#include "fixaudio.h"
#include "logger.h"

//************************************************************************************************************//

const audio_playMap audio_tmail_Map[] = {
	//bai
	{ "1",AudioNumEnBai,Audiohindilangh1},
	{ "2",AudioNumEnBai,Audiohindilangh2},
	{ "3",AudioNumEnBai,Audiohindilangh3},
	{ "4",AudioNumEnBai,Audiohindilangh4},
	{ "5",AudioNumEnBai,Audiohindilangh5},
	{ "6",AudioNumEnBai,Audiohindilangh6},
	{ "7",AudioNumEnBai,Audiohindilangh7},
	{ "8",AudioNumEnBai,Audiohindilangh8},
	{ "9",AudioNumEnBai,Audiohindilangh9},

	//wan
	{ "1",Audiohindilangwan,Audiohindilangtt1},
	{ "2",Audiohindilangwan,Audiohindilangtt2},
	{ "3",Audiohindilangwan,Audiohindilangtt3},
	{ "4",Audiohindilangwan,Audiohindilangtt4},
	{ "5",Audiohindilangwan,Audiohindilangtt5},
	{ "6",Audiohindilangwan,Audiohindilangtt6},
	{ "7",Audiohindilangwan,Audiohindilangtt7},
	{ "8",Audiohindilangwan,Audiohindilangtt8},
	{ "9",Audiohindilangwan,Audiohindilangtt9},

	
};


char* get_Tmail_amount_playfile(char *srcSmtNum,char* type)
{
	
	int i = 0;
	if(srcSmtNum == NULL || type == NULL){
		return NULL;
	}
	for(i = 0;i < sizeof(audio_tmail_Map)/sizeof(audio_tmail_Map[0]); i++){
		if(strcmp(srcSmtNum,audio_tmail_Map[i].playData) == 0
			&& strcmp(type,audio_tmail_Map[i].fileName) == 0
			){			
			logger_debug("fileName_ex=%s\n",audio_tmail_Map[i].memData);
			return  (char*)audio_tmail_Map[i].memData;
		}
	}
	return NULL;
}


