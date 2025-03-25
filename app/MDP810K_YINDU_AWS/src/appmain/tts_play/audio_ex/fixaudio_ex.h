#ifndef __MDP810_AUDIO_EX_H__
#define __MDP810_AUDIO_EX_H__




typedef struct {
	const char *playData;
	const char *en_playdata;
}audio_en_playMap;



typedef struct {
	char *playData;
    char **bufName;
	int *audioLen;
}audio_ram_playMap;

typedef struct _ram_playMap{
	char *fileName;
	char *playData;
	int audioLen;
	struct _ram_playMap *nextItem;
}audio_ram_playMap_ex;



// 0
#define AudioNum0 "0"
#define AudioNum0Len sizeof(AudioNum0)
// 1
#define AudioNum1 "1"
#define AudioNum1Len sizeof(AudioNum1)
// 2
#define AudioNum2 "2"
#define AudioNum2Len sizeof(AudioNum2)
// 3
#define AudioNum3 "3"
#define AudioNum3Len sizeof(AudioNum3)
// 4
#define AudioNum4 "4"
#define AudioNum4Len sizeof(AudioNum4)
// 5
#define AudioNum5 "5"
#define AudioNum5Len sizeof(AudioNum5)
// 6
#define AudioNum6 "6"
#define AudioNum6Len sizeof(AudioNum6)
// 7
#define AudioNum7 "7"
#define AudioNum7Len sizeof(AudioNum7)
// 8
#define AudioNum8 "8"
#define AudioNum8Len sizeof(AudioNum8)
// 9
#define AudioNum9 "9"
#define AudioNum9Len sizeof(AudioNum9)
// .
#define AudioDian "点"
#define AudioDianLen sizeof(AudioDian)

// .
#define Audio_Dian "."
#define Audio_DianLen sizeof(Audio_Dian)


//十
#define AudioShi "十"
#define AudioShiLen sizeof(AudioShi)

//10
#define Audio_10 "10"
#define Audio_10Len sizeof(Audio_10)

//百
#define AudioBai "百"
#define AudioBaiLen sizeof(AudioBai)
//千
#define AudioQian "千"
#define AudioQianLen sizeof(AudioQian)
//万
#define AudioWan "万"
#define AudioWanLen sizeof(AudioWan)
//元
#define AudioYuan "元"
#define AudioYuanLen sizeof(AudioYuan)
// fen
#define AudioFen "分"
#define AudioFenLen sizeof(AudioFen)
// 角
#define AudioJiao "角"
#define AudioJiaoLen sizeof(AudioJiao)

//按键音嘀
#define AudioAnjy "嘀"
#define AudioAnjyLen sizeof(AudioAnjy)

// 头
#define AudioTou "头"
#define AudioTouLen sizeof(AudioTou)


// 尾
#define AudioWei "尾"
#define AudioWeiLen sizeof(AudioWei)

// 笔
#define AudioBi "笔"
#define AudioBiLen sizeof(AudioBi)


// 第
#define AudioDi "第"
#define AudioDiLen sizeof(AudioDi)


//请写入设备参数
#define AudioQingxrsbcs "plz_download_parameter"
#define AudioQingxrsbcsLen strlen(AudioQingxrsbcs)

//升级成功
#define AudioShenjcg "upgrade_success"
#define AudioShenjcgLen strlen(AudioShenjcg)

//正在升级软件
#define AudioZhenzsjrj "software_upgrading"
#define AudioZhenzsjrjLen strlen(AudioZhenzsjrj)

//升级失败
#define AudioShengjsb "upgrade_fail"
#define AudioShengjsbLen strlen(AudioShengjsb)


#define AudioTuiccx "stop_wifi_setting"
#define AudioTuiccxLen  strlen(AudioTuiccx)


#define AudioXianzs4gwlms    "4G_network"
#define AudioXianzs4gwlmsLen strlen(AudioXianzs4gwlms)

//网络连接成功
#define AudioWanglljcg "network_connect_success"
#define AudioWanglljcgLen strlen(AudioWanglljcg)

//网络连接失败，请检查网络
#define AudioWanlljsbqjcwl "network_connfail_plz_chk"
#define AudioWanlljsbqjcwlLen strlen(AudioWanlljsbqjcwl)

//音量最大
#define AudioYinlzd "maximum_volume"
#define AudioYinlzdLen strlen(AudioYinlzd)
//音量最小
#define AudioYinlzx "minimum_volume"
#define AudioYinlzxLen strlen(AudioYinlzx)


//电量低请充电
#define AudioDianldqcd "please_charge_battery"
#define AudioDianldqcdLen strlen(AudioDianldqcd)

//服务连接成功
#define AudioFuwljcg "service_connect_success"
#define AudioFuwljcgLen strlen(AudioFuwljcg)

//服务连接失败
#define AudioFuwljsb "service_connect_fail"
#define AudioFuwljsbLen strlen(AudioFuwljsb)

//服务已退出
#define AudioFuwuytc "service_has_exited"
#define AudioFuwuytcLen strlen(AudioFuwuytc)


//正在关机
#define AudioZhengzaigguanji "shutting_down"
#define AudioZhengzaigguanjiLen strlen(AudioZhengzaigguanji)

//网络故障，请检查网络状态
#define AudioWanglgzqjcwlzt "network_connfail_plz_chk"
#define AudioWanglgzqjcwlztLen strlen(AudioWanglgzqjcwlzt)


//充电已移出
#define AudioChongdyyc "power_cable_is_removed"
#define AudioChongdyycLen strlen(AudioChongdyyc)
//充电中
#define AudioChongdz "device_is_charging"
#define AudioChongdzLen strlen(AudioChongdz)
//充电已完成
#define AudioChongdywc "charging_has_been_completed"
#define AudioChongdywcLen strlen(AudioChongdywc)
//或
#define AudioHuo "或"
#define AudioHuoLen strlen(AudioHuo)
//请稍候
#define AudioQinsh "please_wait_a_moment"
#define AudioQinshLen strlen(AudioQinsh)


//双击功能键切换至WiFi-AP配网模式
#define AudioShuangjgnjqhzappwms "wifi_network"
#define AudioShuangjgnjqhzappwmsLen strlen(AudioShuangjgnjqhzappwms)

//双击功能键切换至WiFi-快联配网模式
#define AudioShuangjgnjqhzklpwms "wifi_network"
#define AudioShuangjgnjqhzklpwmsLen strlen(AudioShuangjgnjqhzklpwms)

//未检测到SIM卡
#define AudioWeijcdsimk "SIM_card_not_detected"
#define AudioWeijcdsimkLen strlen(AudioWeijcdsimk)

//现在是4G网络模式
#define AudioXianzsgprswlms "4G_network"
#define AudioXianzsgprswlmsLen strlen(AudioXianzsgprswlms)

//现在是移动网络模式
#define AudioXianzsydwlms "4G_network"
#define AudioXianzsydwlmsLen strlen(AudioXianzsydwlms)

//现在是WIFI网络模式
#define AudioXianzswifiwlms "wifi_network"
#define AudioXianzswifiwlmsLen strlen(AudioXianzswifiwlms)
//现在是WiFi AP配网模式
#define AudioXianzswifiappwms AudioXianzswifiwlms//"WiFi_ap_config_mode"
#define AudioXianzswifiappwmsLen strlen(AudioXianzswifiappwms)

//现在是WiFi 热点配网模式
#define AudioXianzswifiredianpwms "WiFi_hotspot_config_mode" 
#define AudioAudioXianzswifiredianpwmsLen strlen(AudioXianzswifiredianpwms)

//现在是WiFi快联配网模式
#define AudioXianzswifiklpwms "wifi_network"
#define AudioXianzswifiklpwmsLen strlen(AudioXianzswifiklpwms)
//已退出配网
#define AudioYitcpw "stop_wifi_setting"
#define AudioYitcpwLen strlen(AudioYitcpw)
//长按功能键切换至4G网络模式
#define AudioChangagnjqhzgprswlms "P_and_H_switch_4Gnet"
#define AudioChangagnjqhzgprswlmsLen strlen(AudioChangagnjqhzgprswlms)
//长按功能键切换至WiFi网络模式
#define AudioChangagnjqhzwifiwlms "p_and_H_switch_WiFinet"
#define AudioChangagnjqhzwifiwlmsLen strlen(AudioChangagnjqhzwifiwlms)
//正在连接网络
#define AudioZhenzljwl "Network_Connecting"
#define AudioZhenzljwlLen strlen(AudioZhenzljwl)

// 祝您生意兴隆
#define AudioZhulsyxl "wish_u_a_good_business"
#define AudioZhulsyxlLen strlen(AudioZhulsyxl)

//欢迎使用云音箱
#define AudioHuanysyyyx "welcome"
#define AudioHuanysyyyxLen strlen(AudioHuanysyyyx)

#define AudioWanglyc  "network_connfail_plz_chk"
#define AudioWanglycLen strlen(AudioWanglyc)

#define AudioWanglzc  "network_connect_success"
#define AudioWanglzcLen strlen(AudioWanglzc)

//请检查网络
#define Audio_Qingjianchawangluo  "please_check_network"

//电量低正在关机
#define AudioDianliangdizzgj "low_battery"
#define AudioDianliangdizzgjLen strlen(AudioDianliangdizzgj)

//当前电量
#define AudioDangqiandl "current_power"
#define AudioDangqiandlLen strlen(AudioDangqiandl)

//百分之
#define AudioBaifenzhi "percent"
#define AudioBaifenzhiLen strlen(AudioBaifenzhi)


//现在是音量模式
#define AudioYinliangmoshi "volume"
#define AudioYinliangmoshiLen strlen(AudioYinliangmoshi)

//音量
#define AudioYinliang ""//volume"
#define AudioYinliangLen strlen(AudioYinliang)


//第一笔
#define Audiodiyibi "previous_transaction"
#define AudioAudiodiyibiLen strlen(Audiodiyibi)


//重复笔数 中英文对应翻译使用到
#define Audiodi1bi "the|first|transaction"
#define Audiodi1biLen sizeof(Audiodi1bi)

#define Audiodi2bi "the|second|transaction"
#define Audiodi2biLen sizeof(Audiodi2bi)

#define Audiodi3bi "the|third|transaction"
#define Audiodi3biLen sizeof(Audiodi3bi)

#define Audiodi4bi "the|forth|transaction"
#define Audiodi4biLen sizeof(Audiodi4bi)

#define Audiodi5bi "the|fifth|transaction"
#define Audiodi5biLen sizeof(Audiodi5bi)

#define Audiodi6bi "the|sixth|transaction"
#define Audiodi6biLen sizeof(Audiodi6bi)

#define Audiodi7bi "the|seventh|transaction"
#define Audiodi7biLen sizeof(Audiodi7bi)

#define Audiodi8bi "the|eighth|transaction"
#define Audiodi8biLen sizeof(Audiodi8bi)

#define Audiodi9bi "the|nineth|transaction"
#define Audiodi9biLen sizeof(Audiodi9bi)

#define Audiodi10bi "the|tenth|transaction"
#define Audiodi10biLen sizeof(Audiodi10bi)



#endif
