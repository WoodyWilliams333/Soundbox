#ifndef __MDP810_AUDIO_H__
#define __MDP810_AUDIO_H__
#include "fixaudio_ex.h"
#include "fixaudioen.h"

typedef struct {
	const char *playData;
    const char *fileName;
    const char *memData;
}audio_playMap;

//ʹ��|�����mp3��ý�岥��ʧ�ܣ���ʹ��tts������tts�Ქ�������ߡ���ʹ�ÿո񣬶��Ų��Ქ��������
#define Audio_REGEX             "|"
//ϵͳ���
#define Audio_YLMS         "Volume mode"
#define Audio_JYCXMS       "query mode" //ignore it is chinese Modal particles
#define Audio_Bi           "��"  //ignore it is chinese Modal particles
#define Audio_Di           "��" //ignore it is chinese Modal particles

//�������
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

//ϵͳ���
//����������ģʽ
#define Audio_XianZaiShiYLMS      		Audio_XianZai Audio_REGEX Audio_YLMS
//�����ǽ��ײ�ѯģʽ
#define Audio_XianZaiShiJSCXMS    		Audio_XianZai Audio_REGEX Audio_JYCXMS
//��ӭʹ��������
#define Audio_HuanYinShiYongYYX         "welcome"
//ף��������¡
#define Audio_ZhuShengYiXL              "welcome"
//���ڹػ�����лʹ��������������
#define Audio_ZhengZaiGuanJiGXSYYYZS    "power down"
//��д���豸����
#define Audio_QingXieRuSBCS             "please write parameters"
//������
#define Audio_DianLiangDi               "low power"
//����
#define Audio_QingChongDian             "please charge"
//��ǰ�����ٷ�֮
#define Audio_DangQianDianLianBFZ       "power percent is"
//����
#define Audio_anjianyin                 "press button"
//�����ɹ���ػ�
#define Audio_XiaZaiChengGong           "download success"
//������С
#define Audio_YinLiangZuiXiao           "Min Volume"
//�������
#define Audio_YinLiangZuiDa             "MAX Volume"
//������
#define Audio_YinLiangAdd               "Volume up"
//������
#define Audio_YinLiangSub               "Volume down"
//�����
#define Audio_ChongDianZhong            "in charging"
//������Ƴ�
#define Audio_ChongDianYiYiChu          "charging removed"
//��������
#define Audio_ChongDianYiWanCheng       "finished charging"
//���׼�¼ɾ���ɹ�
#define Audio_JYJL_QC_CG                "delete record success"

//�������
//���������ƶ�����
#define Audio_ZhengZaiLianjieYDWL       Audio_ZZLJ Audio_REGEX Audio_YDWL
//�ƶ��������ӳɹ�
#define Audio_YiDongWangLuoLJCG         Audio_YDWL Audio_REGEX Audio_LJCG
//�ƶ���������ʧ�ܣ���������
#define Audio_YDWLLJSB_QJCWL            Audio_YDWL Audio_REGEX Audio_LJSB Audio_REGEX Audio_QJCWL
//����������������
#define Audio_ZhengZaiLianjieWXWL       Audio_ZZLJ Audio_REGEX Audio_WXWL
//�����������ӳɹ�
#define Audio_WuXianWangLuoLJCG         Audio_WXWL Audio_REGEX Audio_LJCG
//������������ʧ�ܣ���������
#define Audio_WXWLLJSB_QJCWL            Audio_WXWL Audio_REGEX Audio_LJSB Audio_REGEX Audio_QJCWL
//������4G����ģʽ
#define Audio_Xianzs4gwlms      		Audio_XianZai Audio_REGEX Audio_4gwlms
//������WIFI����ģʽ
#define Audio_Xianzswifiwlms     		Audio_XianZai Audio_REGEX Audio_wifiwlms
//������WiFi΢������ģʽ
#define Audio_Xianzswifiwxpwms      	Audio_XianZai Audio_REGEX Audio_WeiXin
//������WiFi�ȵ�����ģʽ
#define Audio_Xianzswifiappwms      	Audio_XianZai Audio_REGEX Audio_ReDian 
//˫�����ܼ��л���WiFi-AP����ģʽ
#define Audio_Shuangjgnjqhzappwms       Audio_SJGNJQH Audio_REGEX Audio_ReDian 
//˫�����ܼ��л���WiFi-��������ģʽ
#define Audio_Shuangjgnjqhzklpwms       Audio_SJGNJQH Audio_REGEX Audio_WeiXin 
//���������쳣
#define Audio_WXWangLuoYiChang          Audio_WXWL Audio_REGEX Audio_YiChang
//�ƶ������쳣
#define Audio_YDWangLuoYiChang          Audio_YDWL Audio_REGEX Audio_YiChang
//������������
#define Audio_WXWangLuoZhengC           Audio_WXWL Audio_REGEX Audio_ZhengC
//�ƶ���������
#define Audio_YDWangLuoZhengC           Audio_YDWL Audio_REGEX Audio_ZhengC
//���������ӳɹ�
#define Audio_FuWuQiLianjieChengGong    Audio_FWQ Audio_REGEX Audio_LJCG
//����������ʧ��
#define Audio_FuWuQiLianjieShiBai       Audio_FWQ Audio_REGEX Audio_LJSB
//δ��⵽SIM��
#define Audio_WeiJianCeDaoSIMKa         "no sim card"
//���˳�����
#define Audio_YiTuiChuPeiWang           "network configuration exit"
//�������豸
#define Audio_ChongQiSheBei             "please reboot"
//�����SIM��
#define Audio_QingChaRuSIMKa             "please insert sim"
//�źŵȼ�
#define Audio_XinHaoDengji              "signal level"
//�ź�ǿ
#define Audio_XinHaoQiang               "strong signal"
//�ź�����
#define Audio_XinHaoZhengchang          "normal signal"
//�źŵȼ�
#define Audio_XinHaoRuo                 "week signal"
//�豸�Զ�����
#define Audio_SheBeiZiDongChongQi       "reboot automacticly"
//��ɸ���
#define Audio_WanChenGengXin            "update successfully"
//�������豸,��ɸ���
#define Audio_CQSBWCGX                   Audio_WanChenGengXin Audio_REGEX Audio_ChongQiSheBei
//�豸�Զ�����,��ɸ���
#define Audio_SBZDCQWCGX                Audio_SheBeiZiDongChongQi Audio_REGEX Audio_WanChenGengXin

//֧����ʽ
//�ɹ��տ�
#define Audio_chenggong_shoukuan        "success"
//֧�����տ�
#define Audio_zhifubao_shoukuan         "alipay"
//΢���տ�
#define Audio_weixin_shoukuan           "wechat"
//�������տ�
#define Audio_yunshanfu_shoukuan        "cloud pay"
//����������տ�
#define Audio_shuzirenminbi_shoukuan    "Digital Cash"
//�û�ȡ��֧��
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
