#ifndef _WIFI_CONFIG_H
#define _WIFI_CONFIG_H

#define FILE_AP_LIST		"aplist.log"
#define MAX_WIFI_INFO_LIST	32	

#ifndef APP_STRNCPY
#define APP_STRNCPY(dest, src) \
do {\
	strncpy((char *)dest, (char *)src, sizeof(dest));\
	dest[sizeof(dest)-1] = '\0';\
} while (0)
#endif

typedef struct st_wificonfig_ap_info
{
	int iSecurityType;             	//  Sets the Wireless LAN security type. £≠£≠ º”√‹ƒ£ Ω
	char szSSID[32+1];              //  SSID
	char szKey[32+1];              	//  Personal Shared Key Pass-Phrase,
}WIFICONFIG_AP_INFO;


int wifi_ap_airkiss_mode(appbool ap, void(* fp)(void));
#endif

