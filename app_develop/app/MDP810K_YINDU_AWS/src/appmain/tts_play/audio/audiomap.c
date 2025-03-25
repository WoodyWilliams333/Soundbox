#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "logger.h"
#include "fixaudio.h"
#include "audiomap.h"

const audio_playMap audio_mp3Map[] = {
	{Audio_percent,                           AudioBaifenzhi".mp3"}, 
	{Audio_changangnjqhz4Gwlms,               "s_phbs4g.mp3"},  
	{Audio_switch2Wifi,                       "s_phbswf.mp3"},     
	{Audio_chongdianyiwancheng,               AudioChongdywc".mp3"},           
	{Audio_chongdianyiyichu,                  AudioChongdyyc".mp3"},
	{Audio_chongdianzhong,                    AudioChongdz".mp3"},
	{Audio_dangqiandianliang_baifenzhi,       AudioDangqiandl".mp3"},
	{Audio_daozhang,                          Audio_daozhang".mp3"},
	{Audio_dianliangdi,                       AudioDianliangdizzgj".mp3"},
	{Audio_dibabi,                            "dibabi.mp3"},
	{Audio_dierbi,                            "dierbi.mp3"}, 
	{Audio_dijiubi,                           "dijiubi.mp3"},
	{Audio_diliubi,                           "diliubi.mp3"}, 
	{Audio_diqibi,                            "diqibi.mp3"},   
	{Audio_disanbi,                           "disanbi.mp3"}, 
	{Audio_dishibi,                           "dishibi.mp3"},   
	{Audio_disibi,                            "disibi.mp3"},  
	{Audio_diwubi,                            "diwubi.mp3"}, 
	{Audio_diyibi,                            Audiodiyibi".mp3"},  
	{Audiodiyibi,                             Audiodiyibi".mp3"}, 
	{Audio_fuwulianjiechenggong,              AudioFuwljcg".mp3"},
	{Audio_fuwulianjieshibai,                 AudioFuwljsb".mp3"}, 
	{Audio_fuwuyituichu,                      "s_shb.mp3"},
	{Audio_huo,                               "huo.mp3"}, 
	{Audio_qingchongdian,                     AudioDianldqcd".mp3"}, 
	{Audio_qingjianchawangluo,                Audio_Qingjianchawangluo".mp3"},
	{Audio_qingshaohou,                       AudioQinsh".mp3"},
	{Audio_qingxierushebeicanshu,             AudioQingxrsbcs".mp3"},
	{Audio_shebeiguzhang,                     "s_devflt.mp3"},
	{Audio_shengjichenggong,                  AudioShenjcg".mp3"}, 
	{Audio_shengjishibai,                     AudioShengjsb".mp3"},
	{Audio_shuangjignjqhzWiFi_APpwms,         AudioChangagnjqhzwifiwlms".mp3"},
	{Audio_wangluolianjiechenggong,           AudioWanglljcg".mp3"},
	{Audio_wangluolianjieshibai_qjcwl,        AudioWanlljsbqjcwl".mp3"}, 
	{Audio_wangluoyichang,                    "s_netab.mp3"},
	{Audio_wangluozhengchang,                 "s_netnor.mp3"}, 
	{Audio_weijiancedaoSIMka,                 AudioWeijcdsimk".mp3"},        
	{Audio_xianzaishi4Gwangluomoshi,          AudioXianzsgprswlms".mp3"},
	{Audio_xianzaishiWiFiAPpeiwangms,         AudioXianzswifiredianpwms".mp3"},
	{Audio_xianzaishiWiFiwangluomoshi,        AudioXianzswifiwlms".mp3"},
	//{Audio_Yinliang,                          AudioYinliangmoshi".mp3"},
	{Audio_yinlianger,                        "s_vol2.mp3"},
	{Audio_Yinliangmoshi,                     "s_volmd.mp3"},
	{Audio_yinliangsan,                       "s_vol3.mp3"},
	{Audio_yinliangsi,                        "s_vol4.mp3"},
	{Audio_yinliangwu,                        "s_vol5.mp3"},
	{Audio_yinliangyi,                        "s_vol1.mp3"},
	{Audio_yinliangzuida,                     AudioYinlzd".mp3"}, 
	{Audio_yinliangzuixiao,                   AudioYinlzx".mp3"},
	{Audio_yituichupeiwang,                   AudioYitcpw".mp3"}, 
	{Audio_zhengzaiguanji,                    AudioZhengzaigguanji".mp3"},
	{Audio_zhengzailianjiewangluo,            AudioZhenzljwl".mp3"},
	{Audio_zhengzaishengjiruanjian,           AudioZhenzsjrj".mp3"},

	{ AudioFuwuytc,                           AudioFuwuytc".mp3" },
	{ AudioChongdz,                           AudioChongdz".mp3"},
	{ AudioShuangjgnjqhzappwms,               AudioShuangjgnjqhzappwms".mp3"},
	{ AudioShuangjgnjqhzklpwms,               AudioShuangjgnjqhzklpwms".mp3"},
	{ AudioXianzswifiappwms,                  AudioXianzswifiappwms".mp3"},
	{ AudioXianzswifiklpwms,                  AudioXianzswifiklpwms".mp3" },
	{ AudioChangagnjqhzgprswlms,              AudioChangagnjqhzgprswlms".mp3"},
	{ AudioZhulsyxl,                          AudioZhulsyxl".mp3" },                         
    { AudioWanglyc,                           AudioWanglyc".mp3"  },
	//{ AudioYinliang,                          AudioYinliang".mp3" },
	{ AudioBajajPay,                          AudioBajajPay".mp3" },
	{ AudioNumHindiversion,                   AudioNumHindiversion".mp3" },
	

	//印度客户增加	
	{ Audiobajajpay,                          Audiobajajpay".mp3"},
	{ Audioshoukuanyin,                       Audioshoukuanyin".mp3"},
	{ AudioWelcome_vbox,                      AudioWelcome_vbox".mp3"},
	{ AudioWUAGBNS,                           AudioWUAGBNS".mp3"},
	{ AudioHindimogo,                         AudioHindimogo".mp3"},
	{ Audio_anjianyin,                         "anjianyin.mp3"},
	

	//印度客户预置银行名称
	{ AudioHindiAxis,                        AudioHindiAxis".mp3" },
	{ AudioHindiBandhan,                     AudioHindiBandhan".mp3"},
	{ AudioHindiBOB,                         AudioHindiBOB".mp3" },
	{ AudioHindiBOI,                         AudioHindiBOI".mp3" },
	{ AudioHindiCSB,                         AudioHindiCSB".mp3" },
	{ AudioHindiFederal,                     AudioHindiFederal".mp3" },
	{ AudioHindiIndian,                      AudioHindiIndian".mp3" },
	{ AudioHindiIndusInd,                    AudioHindiIndusInd".mp3" },
	{ AudioHindiJK,                          AudioHindiJK".mp3" },
	{ AudioHindiJKG,                         AudioHindiJKG".mp3" },
	{ AudioHindiKotak,                       AudioHindiKotak".mp3"},
	{ AudioHindiPNB,                         AudioHindiPNB".mp3" },
	{ AudioHindiSIB,                         AudioHindiSIB".mp3" },
	{ AudioHindiUBI,                         AudioHindiUBI".mp3" },
	{ AudioHindiYES,                         AudioHindiYES".mp3" },



	
};

int getaudioplayfilename(char *playData,char *fileName)
{
    int i = 0,ret = -1;
	if(playData == NULL || fileName == NULL){
		return ret;
	}
	for(i = 0;i < sizeof(audio_mp3Map)/sizeof(audio_mp3Map[0]); i++){
		if(strcmp(playData,audio_mp3Map[i].playData) == 0){
			strcpy(fileName,audio_mp3Map[i].fileName);
			ret = 0;
			logger_debug("i=%d\n",i);
			break;
		}
	}
	if(ret != 0 && strlen(playData) > 0 ){
		strcpy(fileName,playData);
	}
	return ret;
}