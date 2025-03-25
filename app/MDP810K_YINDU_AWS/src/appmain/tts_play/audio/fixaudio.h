#ifndef __MDP810_AUDIO_H__
#define __MDP810_AUDIO_H__
#include "fixaudio_ex.h"
#include "fixaudioen.h"

typedef struct {
	const char *playData;
    const char *fileName;
    const char *memData;
}audio_playMap;

//使用|，如果mp3流媒体播报失败，会使用tts播报，tts会播报“竖线”，使用空格，逗号不会播报标点符号
#define Audio_REGEX             "|"
//系统相关
#define Audio_YLMS         "Volume mode"
#define Audio_JYCXMS       "query mode" //ignore it is chinese Modal particles
#define Audio_Bi           "笔"  //ignore it is chinese Modal particles
#define Audio_Di           "第" //ignore it is chinese Modal particles

//网络相关
#define Audio_XianZai      "now is"
#define Audio_ReDian       "WiFi configuration mode"
#define Audio_WeiXin       "WiFi wechat configuration mode"
#define Audio_4gwlms       "4G network mode"
#define Audio_wifiwlms     "WiFi network mode"
#define Audio_SJGNJQH      "Double click function key switch to"
#define Audio_ZZLJ         "connecting"
#define Audio_YDWL         "mobile network"
#define Audio_WXWL         "wireless network"
#define Audio_LJCG         "connect successfully"
#define Audio_LJSB         "connect failed"
#define Audio_FWQ          "server"
#define Audio_QJCWL        "please check network"
#define Audio_ZhengC       "normal"
#define Audio_YiChang      "abnormal"

//系统相关
//现在是音量模式
#define Audio_XianZaiShiYLMS      		Audio_XianZai Audio_REGEX Audio_YLMS
//现在是交易查询模式
#define Audio_XianZaiShiJSCXMS    		Audio_XianZai Audio_REGEX Audio_JYCXMS
//欢迎使用云音箱
#define Audio_HuanYinShiYongYYX         "welcome"
//祝您生意兴隆
#define Audio_ZhuShengYiXL              "welcome"
//正在关机，感谢使用智能语音助手
#define Audio_ZhengZaiGuanJiGXSYYYZS    "power down"
//请写入设备参数
#define Audio_QingXieRuSBCS             "please write parameters"
//电量低
#define Audio_DianLiangDi               "low power"
//请充电
#define Audio_QingChongDian             "please charge"
//当前电量百分之
#define Audio_DangQianDianLianBFZ       "power percent is"
//按键
#define Audio_anjianyin                 "press button"
//升级成功请关机
#define Audio_XiaZaiChengGong           "download success"
//音量最小
#define Audio_YinLiangZuiXiao           "Min Volume"
//音量最大
#define Audio_YinLiangZuiDa             "MAX Volume"
//音量加
#define Audio_YinLiangAdd               "Volume up"
//音量减
#define Audio_YinLiangSub               "Volume down"
//充电中
#define Audio_ChongDianZhong            "in charging"
//充电已移出
#define Audio_ChongDianYiYiChu          "charging removed"
//充电已完成
#define Audio_ChongDianYiWanCheng       "finished charging"
//交易记录删除成功
#define Audio_JYJL_QC_CG                "delete record success"

//网络相关
//正在连接移动网络
#define Audio_ZhengZaiLianjieYDWL       Audio_ZZLJ Audio_REGEX Audio_YDWL
//移动网络连接成功
#define Audio_YiDongWangLuoLJCG         Audio_YDWL Audio_REGEX Audio_LJCG
//移动网络连接失败，请检查网络
#define Audio_YDWLLJSB_QJCWL            Audio_YDWL Audio_REGEX Audio_LJSB Audio_REGEX Audio_QJCWL
//正在连接无线网络
#define Audio_ZhengZaiLianjieWXWL       Audio_ZZLJ Audio_REGEX Audio_WXWL
//无线网络连接成功
#define Audio_WuXianWangLuoLJCG         Audio_WXWL Audio_REGEX Audio_LJCG
//无线网络连接失败，请检查网络
#define Audio_WXWLLJSB_QJCWL            Audio_WXWL Audio_REGEX Audio_LJSB Audio_REGEX Audio_QJCWL
//现在是4G网络模式
#define Audio_Xianzs4gwlms      		Audio_XianZai Audio_REGEX Audio_4gwlms
//现在是WIFI网络模式
#define Audio_Xianzswifiwlms     		Audio_XianZai Audio_REGEX Audio_wifiwlms
//现在是WiFi微信配网模式
#define Audio_Xianzswifiwxpwms      	Audio_XianZai Audio_REGEX Audio_WeiXin
//现在是WiFi热点配网模式
#define Audio_Xianzswifiappwms      	Audio_XianZai Audio_REGEX Audio_ReDian 
//双击功能键切换至WiFi-AP配网模式
#define Audio_Shuangjgnjqhzappwms       Audio_SJGNJQH Audio_REGEX Audio_ReDian 
//双击功能键切换至WiFi-快联配网模式
#define Audio_Shuangjgnjqhzklpwms       Audio_SJGNJQH Audio_REGEX Audio_WeiXin 
//无线网络异常
#define Audio_WXWangLuoYiChang          Audio_WXWL Audio_REGEX Audio_YiChang
//移动网络异常
#define Audio_YDWangLuoYiChang          Audio_YDWL Audio_REGEX Audio_YiChang
//无线网络正常
#define Audio_WXWangLuoZhengC           Audio_WXWL Audio_REGEX Audio_ZhengC
//移动网络正常
#define Audio_YDWangLuoZhengC           Audio_YDWL Audio_REGEX Audio_ZhengC
//服务器连接成功
#define Audio_FuWuQiLianjieChengGong    Audio_FWQ Audio_REGEX Audio_LJCG
//服务器连接失败
#define Audio_FuWuQiLianjieShiBai       Audio_FWQ Audio_REGEX Audio_LJSB
//未检测到SIM卡
#define Audio_WeiJianCeDaoSIMKa         "no sim card"
//已退出配网
#define Audio_YiTuiChuPeiWang           "network configuration exit"
//请重启设备
#define Audio_ChongQiSheBei             "please reboot"
//请插入SIM卡
#define Audio_QingChaRuSIMKa             "please insert sim"
//信号等级
#define Audio_XinHaoDengji              "signal level"
//信号强
#define Audio_XinHaoQiang               "strong signal"
//信号正常
#define Audio_XinHaoZhengchang          "normal signal"
//信号等级
#define Audio_XinHaoRuo                 "week signal"
//设备自动重启
#define Audio_SheBeiZiDongChongQi       "reboot automacticly"
//完成更新
#define Audio_WanChenGengXin            "update successfully"
//请重启设备,完成更新
#define Audio_CQSBWCGX                   Audio_WanChenGengXin Audio_REGEX Audio_ChongQiSheBei
//设备自动重启,完成更新
#define Audio_SBZDCQWCGX                Audio_SheBeiZiDongChongQi Audio_REGEX Audio_WanChenGengXin

//支付方式
//成功收款
#define Audio_chenggong_shoukuan        "success"
//支付宝收款
#define Audio_zhifubao_shoukuan         "alipay"
//微信收款
#define Audio_weixin_shoukuan           "wechat"
//云闪付收款
#define Audio_yunshanfu_shoukuan        "cloud pay"
//数字人民币收款
#define Audio_shuzirenminbi_shoukuan    "Digital Cash"
//用户取消支付
#define Audio_quxiaozhifu               "canceled"

//MDP820 
#define Audio_percent                           "percent"  
#define Audio_changangnjqhz4Gwlms               "press and hold the function button to switch 4G network"
#define Audio_switch2Wifi                       "press and hold the function button to switch WIFI network"  
#define Audio_chongdianyiwancheng               "charging has been completed"
#define Audio_chongdianyiyichu                  "power cable is removed"
#define Audio_chongdianzhong                    "device is charging"
#define Audio_dangqiandianliang_baifenzhi       "current power"
#define Audio_daozhang                          "received"
#define Audio_dianliangdi                       "low battery,device pwer off"
#define Audio_dibabi                            "the eighth transaction"
#define Audio_dierbi                            "the second transaction"
#define Audio_dijiubi                           "the nineth transaction"
#define Audio_diliubi                           "the sixth transaction"
#define Audio_diqibi                            "the seventh transaction"
#define Audio_disanbi                           "the third transaction"
#define Audio_dishibi                           "the tenth transaction"
#define Audio_disibi                            "the forth transaction"
#define Audio_diwubi                            "the fifth transaction"
#define Audio_diyibi                            "the first transaction"
#define Audio_fuwulianjiechenggong              "service connect sucess"
#define Audio_fuwulianjieshibai                 "service connect fail"
#define Audio_fuwuyituichu                      "service has been"
#define Audio_huo                               "or"
#define Audio_qingchongdian                     "low battery, pls charge power"
#define Audio_qingjianchawangluo                "please check network"
#define Audio_qingshaohou                       "please wait a moment"
#define Audio_qingxierushebeicanshu             "please download parameter"
#define Audio_shaungjignjqhzWiFi_klpwms         "press function button twice to switch wifi by scan"
#define Audio_shebeiguzhang                     "device  is faulty"
#define Audio_shengjichenggong                  "upgrade success"
#define Audio_shengjishibai                     "upgarde fail"
#define Audio_shuangjignjqhzWiFi_APpwms         "press function button twice to switch to hotpot set mode for wifi network"
#define Audio_wangluolianjiechenggong           "network connect success"
#define Audio_wangluolianjieshibai_qjcwl        "network connect fail, pls check network"
#define Audio_wangluoyichang                    "network is abnormal"
#define Audio_wangluozhengchang                 "netwrok is normal"
#define Audio_weijiancedaoSIMka                 "SIM card not detected"       
#define Audio_xianzaishi4Gwangluomoshi          "4G network"
#define Audio_xianzaishiWiFiAPpeiwangms         "hotpot set mode for wifi network"
#define Audio_xianzaishiWiFiwangluomoshi        "wifi network"
#define Audio_Yinliang                          ""//volume"
#define Audio_yinlianger                        "volume level2"
#define Audio_Yinliangmoshi                     "volume mode"
#define Audio_yinliangsan                       "volume level3"
#define Audio_yinliangsi                        "volume level4"
#define Audio_yinliangwu                        "volume level5"
#define Audio_yinliangyi                        "volume level1"
#define Audio_yinliangzuida                     "maximum volume"
#define Audio_yinliangzuixiao                   "minimum volume"
#define Audio_yituichupeiwang                   "stop wifi settings"
#define Audio_zhengzaiguanji                    "shuting down"
#define Audio_zhengzailianjiewangluo            "network connecting"
#define Audio_zhengzaishengjiruanjian           "software upgrading"









#endif
