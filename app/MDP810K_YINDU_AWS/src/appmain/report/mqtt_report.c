#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSON.h"
#include "mqtt_report.h"
#include "codestool.h"
#include "record_store.h"
#include "downloadfile.h"
#include "np_led.h"
#include "wnet.h"
#include "system.h"
#include "tersharedata.h"
#include "logger.h"
#include "appsys.h"
#include "fixaudio.h"
#include "appdef.h"
#include "aiot_mqtt.h"
#include "task_thread.h"
#include "pahomqtt.h"
#include "appgprs.h"

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif 
#define internal_getnet_time  (10*60*1000)


static net_lbsInfo mqtt_Info;
static long get_newinfo_time;
static int get_lbsInfo(net_lbsInfo *lbsInfo)
{

	static tBaseStationExt cell_info;
	
	static WnetSigStr_t strength;

	if(lbsInfo == NULL){
		return -1;
	}
	
	if(get_newinfo_time == 0 || (sys_get_timer_count() - get_newinfo_time > internal_getnet_time)){			
		wnet_get_base_station_info_ex(&cell_info);	
		wnet_get_lte_signal(&strength);
		get_newinfo_time = sys_get_timer_count();

	}		
	snprintf(lbsInfo->signal,sizeof(lbsInfo->signal)-1,"%d",strength.wss.sLte.rssi);
	//4G
	if(cell_info.iFlag == 4)
	{
		//cell_info->lte_info[0].flag
		snprintf(lbsInfo->cellid,sizeof(lbsInfo->cellid)-1,"%d",cell_info.Wnet.oLte.cell_id);	
		snprintf(lbsInfo->lac,sizeof(lbsInfo->lac)-1,"%d",cell_info.Wnet.oLte.tac);		
		snprintf(lbsInfo->mnc,sizeof(lbsInfo->mnc)-1,"%d",cell_info.Wnet.oLte.mnc);
		snprintf(lbsInfo->mcc,sizeof(lbsInfo->mcc)-1,"%d",cell_info.Wnet.oLte.mcc); 

	}else if(cell_info.iFlag == 1)
	 {
	 	snprintf(lbsInfo->cellid,sizeof(lbsInfo->cellid)-1,"%d",cell_info.Wnet.oGprs.cell_id);	
		snprintf(lbsInfo->lac,sizeof(lbsInfo->lac)-1,"%d",cell_info.Wnet.oGprs.lac); 	
		snprintf(lbsInfo->mnc,sizeof(lbsInfo->mnc)-1,"%d",cell_info.Wnet.oGprs.mnc);
		snprintf(lbsInfo->mcc,sizeof(lbsInfo->mcc)-1,"%d",cell_info.Wnet.oGprs.mcc); 
						 
	 }

	return 0;
}



int DealRetInfo(task_cmd_struct * evt_node)
{
	int iret = 0;

	int file_free_size;

	char devinfo[100] = {0};
	uint32_t n_total,n_avail,n_max_block_size;
	sys_battery_info_t battery_info;
	
	logger_debug("evt_node->biz_type = %s\n",evt_node->biz_type);
	switch(evt_node->biz_type[0]){
		case EVT_GET_INFO:
			logger_debug("get_lbsInfo \n");
			get_lbsInfo(&mqtt_Info);	

			sys_get_battery_info(&battery_info);

			sys_read_ver(devinfo,sizeof(devinfo));

			snprintf(mqtt_Info.core_version,sizeof(mqtt_Info.core_version)-1,"%s",devinfo);
			strcpy(mqtt_Info.verify_version,APP_SUB_VER);
			strcpy(mqtt_Info.sdk_version,devinfo);
			strcpy(mqtt_Info.app_version,APP_MAIN_VER);
	
			sys_get_free_mem(&n_total,&n_avail,&n_max_block_size);
		
			snprintf(mqtt_Info.ram_free_size,sizeof(mqtt_Info.ram_free_size)-1,"%d byte",(int)n_avail);

			file_free_size = app_get_free_space();	
			snprintf(mqtt_Info.in_flash_free_size,sizeof(mqtt_Info.in_flash_free_size)-1,"%d byte",file_free_size);		

			
			snprintf(mqtt_Info.battery_inf,sizeof(mqtt_Info.battery_inf)-1,"%d%s",(int)battery_info.percent,"%");

			break;
			
		default:
			iret = -1;
			break;
		
	}
	logger_debug("get_lbsInfo end\n");

	return iret;
}


net_lbsInfo *get_mqtt_report_struct(void)
{

	return &mqtt_Info;
}


char * PubTerm_ReportInfo(char *requestId,char *rst,char *res)
{
	//int ret = -1;
	cJSON *root = NULL;
	cJSON *ReportList = NULL;
	char * pout = NULL;
	char tmp_buf[100] = {0};
	char times_send[50] = {0};
	root = cJSON_CreateObject();
	if (root==NULL) return NULL;
	
	cJSON_AddItemToObject(root, "biz_type", cJSON_CreateString("1"));		
	cJSON_AddItemToObject(root, "product_key", cJSON_CreateString(stSysTemp.product_key));
	cJSON_AddItemToObject(root, "device_sn", cJSON_CreateString(stSysTemp.device_name));
	
	ReportList = cJSON_CreateArray();
	if(ReportList){
		memset(tmp_buf,0,sizeof(tmp_buf));
		strcat(tmp_buf,requestId);
		strcat(tmp_buf,"|");
		strcat(tmp_buf,rst);
		strcat(tmp_buf,"|");
		strcat(tmp_buf,res);
		strcat(tmp_buf,"|");
		cJSON_AddItemToArray(ReportList, cJSON_CreateString(tmp_buf));
		get_timestamp(TIME_STAMP_TYPE_SEC,times_send,sizeof(times_send));
		cJSON_AddItemToObject(root, "report_time", cJSON_CreateString(times_send));
		cJSON_AddItemToObject(root, "result_list", ReportList);		
		pout = cJSON_PrintUnformatted(root);
		
	}

	cJSON_Delete(root);

	return pout;
}

