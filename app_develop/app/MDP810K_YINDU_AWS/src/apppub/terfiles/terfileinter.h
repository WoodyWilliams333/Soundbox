
#ifndef _TRANS_FILE_INTER_H_
#define _TRANS_FILE_INTER_H_

int SaveFileComm(const char *filename, void *data_flow, int bytes);
int ReadFileComm(const char *filename, void *data_flow, int need_bytes);


#endif

