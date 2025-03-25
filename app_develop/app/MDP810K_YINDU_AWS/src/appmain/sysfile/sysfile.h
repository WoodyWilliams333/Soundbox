#ifndef _SYS_FILE_H_
#define _SYS_FILE_H_
int get_para_for_string(const char *inStr, const char *strTag, char *outValue, int outSize);
int get_para_for_string_ptr(const char *inStr, const char *strTag, char **outValue);
void get_ali_mqtt_para(void);
#endif //_SYS_FILE_H_