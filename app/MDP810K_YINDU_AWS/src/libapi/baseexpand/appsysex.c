#include <stdio.h>
#include <string.h>
#include <system.h>
#include <appsys.h>

#include "appsysex.h"

appbool app_support_power_off(void)
{
#ifdef CFG_4G_FLAG
	return app_true;
#else
	char supver[] = "1.3.8"; 
	
	if (app_compare_fwversion(supver) < 0) {
		return app_false;
	}

	return app_true;
#endif	
}

