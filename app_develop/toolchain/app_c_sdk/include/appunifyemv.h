#ifndef __APP_UNIFYEMV_H__
#define __APP_UNIFYEMV_H__

#ifdef __cplusplus	
extern "C" {
#endif /* __cplusplus */

#include <EmvTypes.h>
#include <EmvError.h>

#define UNIFYEMV_ONLINE_RESULT EMV_ONLINE_RESULT
#define UNIFYEMV_ERROR EMV_ERROR
#define UNIFYEMV_KERNEL_ID EMV_KERNEL_ID
#define UNIFYEMV_OUTCOME_CVM EMV_OUTCOME_CVM

typedef enum{
	UNIFYEMV_PARA_OK,
	UNIFYEMV_PARA_FAIL,
}E_UNIFYEMV_PARA_RET;

typedef enum{
	UNIFYEMV_PIN_OK,
	UNIFYEMV_PIN_BYPASS,
	UNIFYEMV_PIN_CANCEL,
	UNIFYEMV_PIN_TIMEOUT,
	UNIFYEMV_PIN_ERROTHER
}E_UNIFYEMV_PIN_RET;

typedef enum{
	UNIFYEMV_APP_MATCH_BY_AID,
	UNIFYEMV_APP_PARTIAL_MATCH,
	UNIFYEMV_APP_FULL_MATCH,
}E_UNIFYEMV_SELECT_INDICATOR;

typedef enum{
	UNIFYEMV_KERNEL_TYPE_AUTOMATCH,		//MATCH PROCESS BY RID & APP KERNEL LIST
	UNIFYEMV_KERNEL_TYPE_DOMESTIC,		//ONLY FOR PBOC & QPBOC
	UNIFYEMV_KERNEL_TYPE_INTERNATIONAL,	//FOR EMV,PAYPASS,PAYWAVE,DISCOVER,JCB,AMEX...
}E_UNIFYEMV_KERNEL_TYPE;

typedef enum{
	KERNEL_KEY_TYPE_RSA,
	KERNEL_KEY_TYPE_SM2,			
}E_UNIFYEMV_KEY_TYPE;

typedef void(*UNIFYEMV_CB_DISP_PROCESS)(void);
typedef int(*UNIFYEMV_CB_APP_SELECTION)(uint32_t app_count,const char **aids,const char **lables,uint32_t *selected);
typedef UNIFYEMV_ERROR (*UNIFYEMV_CB_CARDHOLDER_CONFIRM)(const char *aid, const char *lable);
typedef UNIFYEMV_ERROR (*UNIFYEMV_CB_CERT_CHECK)(uint8_t cert_type, const char *cert);
typedef E_UNIFYEMV_PIN_RET(*UNIFYEMV_CB_ONLINEPIN_GET)(void);
typedef void (*UNIFYEMV_CB_OFFPIN_PRROMPT)(void);
typedef UNIFYEMV_ERROR (*UNIFYEMV_CB_OFFPIN_STATUS)(int success, int try_count);

typedef struct KERNEL_CALLBACK_FUNC_S{
	UNIFYEMV_CB_DISP_PROCESS  		m_disp_process;
	UNIFYEMV_CB_APP_SELECTION 		m_app_selection;
	UNIFYEMV_CB_CARDHOLDER_CONFIRM	m_cardholder_confirm;
	UNIFYEMV_CB_CERT_CHECK			m_cert_check;
	UNIFYEMV_CB_ONLINEPIN_GET 		m_online_pin_get;
	UNIFYEMV_CB_OFFPIN_PRROMPT		m_offpin_prompt;
	UNIFYEMV_CB_OFFPIN_STATUS  		m_offpin_status_show;
}KERNEL_CALLBACK_FUNC_T,*KERNEL_CALLBACK_FUNC_P;

typedef struct AID_KERNEL_MATCH_ID_S{
	uint8_t 			m_aid[16]; 
	uint32_t 			m_aid_len; 
	UNIFYEMV_KERNEL_ID	m_kernel_id;
}AID_KERNEL_MATCH_ID_T,*AID_KERNEL_MATCH_ID_P;

//终端初始化相关参数结构体
typedef struct CORE_TRANS_PARAM_S{
	uint8_t m_mer_id[15];
	uint8_t m_term_id[8];
	uint8_t m_mer_name[40+1];
	uint8_t m_acq_id[6];
	uint8_t m_txn_currency_code[2];
	uint8_t m_term_currency_code[2];
	uint8_t m_mer_cateory_code[2];
	uint8_t m_term_type;
	uint8_t m_term_cap[3];
	uint8_t m_term_additional_cap[5];
}CORE_TRANS_PARAM_T, *CORE_TRANS_PARAM_P;

//交易相关参数结构体
typedef struct TRANS_PREPRO_PARAM_S{
    uint32_t					m_amt_auth;		//授权金额
    uint32_t					m_amt_other;	//其他金额
    uint32_t					m_tran_seq;		//交易序列计数器
    uint8_t						m_tran_type;	//交易类型
    uint8_t						m_ctl_ttq[4];	//非接交易属性（仅QPBOC有效）
    uint8_t						m_spt_smalg;	//是否支持国密（仅PBOC&QPBOC有效）
	uint8_t 					m_ign_txn_limit;//是否忽略非接限额(仅对非接有效)
	uint8_t 					m_ign_cvm_limit;//是否忽略CVM限额(仅对非接有效)
	E_UNIFYEMV_SELECT_INDICATOR m_app_indicaor;	//应用匹配方式
	E_UNIFYEMV_KERNEL_TYPE 		m_kernel_type;	//流程类型
	UNIFYEMV_KERNEL_ID			m_kernel_id;	//内核类型
}TRANS_PREPRO_PARAM_T,*TRANS_PREPRO_PARAM_P;


typedef struct TERM_AID_PARAM_S{
	uint8_t 			m_aid[16]; 
	uint32_t 			m_aid_len; 
	uint8_t 			m_tac_default[5]; 
	uint8_t 			m_tac_denial[5]; 
	uint8_t 			m_tac_online[5];
	uint8_t				m_ct_floor_limot[6];
	uint8_t				m_ctl_trans_limit[6];	
	uint8_t				m_ctl_floor_limit[6];	
	uint8_t				m_cvm_require_limit[6];
}TERM_AID_PARAM_T,*TERM_AID_PARAM_P;

typedef struct TERM_CAPK_PARAM_S{
	uint8_t 			m_rid[5];
	uint8_t 			m_index;
	E_UNIFYEMV_KEY_TYPE m_key_type;
}TERM_CAPK_PARAM_T,*TERM_CAPK_PARAM_P;

/**
* @brief 内核初始化函数
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_kernel_init(KERNEL_CALLBACK_FUNC_P kernel_callback_func);

/**
* @brief 加载EMV L2内核
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_load_emvl2_kernel(void);

/**
* @brief 加载QPBOC内核
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_load_qpboc_kernel(void);

/**
* @brief 加载PAYWAVE内核
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_load_paywave_kernel(void);

/**
* @brief 加载PAYWAVE内核
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_load_paypass_kernel(void);

/**
* @brief 加载AMEX内核
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_load_amex_kernel(void);

/**
* @brief 加载DISCOVER内核
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_load_discover_kernel(void);

/**
* @brief 加载JCB内核
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/

extern E_UNIFYEMV_PARA_RET unifyemv_load_jcb_kernel(void);

/**
* @brief AID与内核对应流程列表初始化
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_kernel_matchlist_init(AID_KERNEL_MATCH_ID_P match_list,uint32_t size);

/**
* @brief 内核初注销函数
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_kernel_deinit(void);


/**
* @brief 检查AID文件是否可用
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_check_aid_file(void);

/**
* @brief 增加一个AID到内核AID列表中
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_add_one_aid(uint8_t *aid_tlv,uint32_t aid_tlv_len);

/**
* @brief 获取内核aid数量
* @return 内核aid数量
*/
extern uint32_t unifyemv_get_aid_count(void);

/**
* @brief 获取内核aid信息
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_get_one_aid(uint32_t count,TERM_AID_PARAM_P aid_param);

/**
* @brief 删除内核AID列表中一个特定AID
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_delete_one_aid(uint8_t *aid,uint32_t aid_len);

/**
* @brief 清空内核AID列表
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_clear_all_aid(void);


/**
* @brief 检查CAPK文件是否可用
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_check_capk_file(void);

/**
* @brief 增加一个CAPK到内核CAPK列表中
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_add_one_capk(uint8_t *capk_tlv,uint32_t capk_tlv_len);

/**
* @brief 获取内核capk数量
* @return 内核capk数量
*/
extern uint32_t unifyemv_get_capk_count(void);

/**
* @brief 获取内核aid信息
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_get_one_capk(uint32_t count,TERM_CAPK_PARAM_P capk_param);

/**
* @brief 删除内核CAPK列表中一个特定CAPK
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_delete_one_capk(uint8_t *rid,uint32_t rid_len, uint32_t index);

/**
* @brief 清空内核CAPK列表
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_clear_all_capk(void);

/**
* @brief 增加一个卡BIN黑名单到内核卡BIN列表中
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_add_one_blackbin(void);

/**
* @brief 删除内核卡BIN列表中一个卡BIN
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_delete_one_blackbin(void);

/**
* @brief 清空内核卡BIN列表
* @return 内核返回值
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_clear_all_blackbin(void);

extern E_UNIFYEMV_PARA_RET unifyemv_set_kernel_data(const char *tag, uint32_t tag_len, uint8_t *value, uint32_t value_len);

extern E_UNIFYEMV_PARA_RET unifyemv_get_kernel_data(const char *tag, uint32_t tag_len, uint8_t *value, uint32_t *value_len);

extern E_UNIFYEMV_PARA_RET unifyemv_get_card_data(const char *tag, uint32_t tag_len, uint8_t *value ,uint32_t *value_len);

/*get current trans kernel id -- call after select app func*/
extern UNIFYEMV_KERNEL_ID unifyemv_trans_get_kernel_id(void);

/*get pin enter status*/
extern E_UNIFYEMV_PIN_RET unifyemv_trans_get_pin_status(void);

/*trans init & trans pre process(both contacked & contackless)*/
extern UNIFYEMV_ERROR unifyemv_trans_init(int slot_type);

extern UNIFYEMV_ERROR unifyemv_trans_preproc(CORE_TRANS_PARAM_P core_trans_param, TRANS_PREPRO_PARAM_P trans_preproc_para);

/*contacked functions*/
extern UNIFYEMV_ERROR unifyemv_cttrans_buildlist(void);

extern UNIFYEMV_ERROR unifyemv_cttrans_selectapp(void);

extern UNIFYEMV_ERROR unifyemv_cttrans_initapp(void);

extern UNIFYEMV_ERROR unifyemv_cttrans_readdata(void);

extern UNIFYEMV_ERROR unifyemv_cttrans_authdata(void);

extern UNIFYEMV_ERROR unifyemv_cttrans_procrestrict(void);

extern UNIFYEMV_ERROR unifyemv_cttrans_cardholderverify(void);

extern UNIFYEMV_ERROR unifyemv_cttrans_riskmanage(void);

extern UNIFYEMV_ERROR unifyemv_cttrans_action_analysis(void);

extern UNIFYEMV_ERROR unifyemv_cttrans_completion(UNIFYEMV_ONLINE_RESULT online_result,
			uint8_t *auth_resp_code, uint32_t auth_resp_code_len,
			uint8_t *resp_ic_field, uint32_t resp_ic_field_len);


/*contackless functions*/
extern UNIFYEMV_ERROR unifyemv_ctltrans_buildlist(void);

extern UNIFYEMV_ERROR unifyemv_ctltrans_process(void);

extern UNIFYEMV_ERROR unifyemv_ctltrans_completion(UNIFYEMV_ONLINE_RESULT online_result,
			uint8_t *auth_resp_code, uint32_t auth_resp_code_len,
			uint8_t *resp_ic_field, uint32_t resp_ic_field_len);

extern UNIFYEMV_OUTCOME_CVM unifyemv_ctltrans_cvm(void);

/**
* @brief 获取libunifyemv库的版本信息
* @param[out] version，libwnet库的版本信息输出   
* @param[in]  size，version执行的buffer长度，建议至少64字节    
* @return 获取的结果
*	-<em> == 0  </em>  成功
*	-<em> == -1 </em>  失败
*/
extern int unifyemv_get_version(char *version, int size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
