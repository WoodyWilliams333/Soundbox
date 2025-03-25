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

//�ն˳�ʼ����ز����ṹ��
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

//������ز����ṹ��
typedef struct TRANS_PREPRO_PARAM_S{
    uint32_t					m_amt_auth;		//��Ȩ���
    uint32_t					m_amt_other;	//�������
    uint32_t					m_tran_seq;		//�������м�����
    uint8_t						m_tran_type;	//��������
    uint8_t						m_ctl_ttq[4];	//�ǽӽ������ԣ���QPBOC��Ч��
    uint8_t						m_spt_smalg;	//�Ƿ�֧�ֹ��ܣ���PBOC&QPBOC��Ч��
	uint8_t 					m_ign_txn_limit;//�Ƿ���Էǽ��޶�(���Էǽ���Ч)
	uint8_t 					m_ign_cvm_limit;//�Ƿ����CVM�޶�(���Էǽ���Ч)
	E_UNIFYEMV_SELECT_INDICATOR m_app_indicaor;	//Ӧ��ƥ�䷽ʽ
	E_UNIFYEMV_KERNEL_TYPE 		m_kernel_type;	//��������
	UNIFYEMV_KERNEL_ID			m_kernel_id;	//�ں�����
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
* @brief �ں˳�ʼ������
* @return �ں˷���ֵ
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_kernel_init(KERNEL_CALLBACK_FUNC_P kernel_callback_func);

/**
* @brief ����EMV L2�ں�
* @return �ں˷���ֵ
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_load_emvl2_kernel(void);

/**
* @brief ����QPBOC�ں�
* @return �ں˷���ֵ
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_load_qpboc_kernel(void);

/**
* @brief ����PAYWAVE�ں�
* @return �ں˷���ֵ
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_load_paywave_kernel(void);

/**
* @brief ����PAYWAVE�ں�
* @return �ں˷���ֵ
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_load_paypass_kernel(void);

/**
* @brief ����AMEX�ں�
* @return �ں˷���ֵ
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_load_amex_kernel(void);

/**
* @brief ����DISCOVER�ں�
* @return �ں˷���ֵ
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_load_discover_kernel(void);

/**
* @brief ����JCB�ں�
* @return �ں˷���ֵ
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/

extern E_UNIFYEMV_PARA_RET unifyemv_load_jcb_kernel(void);

/**
* @brief AID���ں˶�Ӧ�����б��ʼ��
* @return �ں˷���ֵ
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_kernel_matchlist_init(AID_KERNEL_MATCH_ID_P match_list,uint32_t size);

/**
* @brief �ں˳�ע������
* @return �ں˷���ֵ
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_kernel_deinit(void);


/**
* @brief ���AID�ļ��Ƿ����
* @return �ں˷���ֵ
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_check_aid_file(void);

/**
* @brief ����һ��AID���ں�AID�б���
* @return �ں˷���ֵ
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_add_one_aid(uint8_t *aid_tlv,uint32_t aid_tlv_len);

/**
* @brief ��ȡ�ں�aid����
* @return �ں�aid����
*/
extern uint32_t unifyemv_get_aid_count(void);

/**
* @brief ��ȡ�ں�aid��Ϣ
* @return �ں˷���ֵ
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_get_one_aid(uint32_t count,TERM_AID_PARAM_P aid_param);

/**
* @brief ɾ���ں�AID�б���һ���ض�AID
* @return �ں˷���ֵ
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_delete_one_aid(uint8_t *aid,uint32_t aid_len);

/**
* @brief ����ں�AID�б�
* @return �ں˷���ֵ
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_clear_all_aid(void);


/**
* @brief ���CAPK�ļ��Ƿ����
* @return �ں˷���ֵ
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_check_capk_file(void);

/**
* @brief ����һ��CAPK���ں�CAPK�б���
* @return �ں˷���ֵ
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_add_one_capk(uint8_t *capk_tlv,uint32_t capk_tlv_len);

/**
* @brief ��ȡ�ں�capk����
* @return �ں�capk����
*/
extern uint32_t unifyemv_get_capk_count(void);

/**
* @brief ��ȡ�ں�aid��Ϣ
* @return �ں˷���ֵ
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_get_one_capk(uint32_t count,TERM_CAPK_PARAM_P capk_param);

/**
* @brief ɾ���ں�CAPK�б���һ���ض�CAPK
* @return �ں˷���ֵ
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_delete_one_capk(uint8_t *rid,uint32_t rid_len, uint32_t index);

/**
* @brief ����ں�CAPK�б�
* @return �ں˷���ֵ
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_clear_all_capk(void);

/**
* @brief ����һ����BIN���������ں˿�BIN�б���
* @return �ں˷���ֵ
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_add_one_blackbin(void);

/**
* @brief ɾ���ں˿�BIN�б���һ����BIN
* @return �ں˷���ֵ
*	-<em> != 0 </em>  fail
*	-<em> == 0 </em>  success
*/
extern E_UNIFYEMV_PARA_RET unifyemv_delete_one_blackbin(void);

/**
* @brief ����ں˿�BIN�б�
* @return �ں˷���ֵ
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
* @brief ��ȡlibunifyemv��İ汾��Ϣ
* @param[out] version��libwnet��İ汾��Ϣ���   
* @param[in]  size��versionִ�е�buffer���ȣ���������64�ֽ�    
* @return ��ȡ�Ľ��
*	-<em> == 0  </em>  �ɹ�
*	-<em> == -1 </em>  ʧ��
*/
extern int unifyemv_get_version(char *version, int size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
