
#include <stdio.h>
#include <string.h>
#include <errno.h>


#include "basicext.h"
#include "libapiext.h"
#include "schedulework.h"
#include "appbasicext.h"



#ifdef ASYNC_CONNECT_TCP
#define ASYNC_SERVER_SOCKET_TIMEOUT 20 //后台socket超时时间
#endif

static ST_COMM_CONFIG gl_CommConfig[MAX_COMM_HANDLER_NUM];
static SysCommOps_t gl_CommOpsObj[MAX_COMM_HANDLER_NUM];
static ST_LINK_INFO gl_CommLink[MAX_COMM_HANDLER_NUM];
#ifdef ASYNC_CONNECT
static appbool bDoPreDial = app_false;
#ifdef ASYNC_CONNECT_TCP
static uint32_t guiPreConnectStartTime;
#endif
#endif

static int CheckCommHandlerValid(int handler, appbool checkcomm)
{
	int ret = (handler < MAX_COMM_HANDLER_NUM ?  RET_OK : E_COMM_INVALID_HANDLE);	

	if(checkcomm == app_true && ret == RET_OK){
		ret = (gl_CommOpsObj[handler].comm != NULL ? RET_OK : E_COMM_NO_INIT);
	}
	
	return ret;
}

int CommInit(int comHandler, CommType_e comtype, SockType_e protocoltype)
{
	int ret = RET_OK;
	SysCommOps_t *lpComOps = NULL;

	logger_debug("CommInit\n");
	if( comtype < CT_WIFI || comtype > CT_GPRS){
		ret = E_COMM_INVALID_TYPE;
		logger_error("E_COMM_INVALID_TYPE! type=%d\n",comtype);
		return ret;
	}
	
	if( protocoltype < SOCK_TCP || protocoltype > SOCK_SSL){
		ret = E_COMM_INVALID_PROL;
		logger_error("E_COMM_INVALID_PROL!\n");
		return ret;
	}

	if((ret = CheckCommHandlerValid(comHandler, app_false)) != RET_OK){
		logger_error("CheckCommHandlerinValid!\n");
		return ret;
	}

	gl_CommConfig[comHandler].comm_type = comtype;
	gl_CommConfig[comHandler].protocol_type = protocoltype;

	
	logger_debug("wnet_comm_ops_init-->ucCommType = %X, protocol_type = %X\n", 
			gl_CommConfig[comHandler].comm_type, gl_CommConfig[comHandler].protocol_type);
	lpComOps = wnet_comm_ops_init(gl_CommConfig[comHandler].comm_type, 
				gl_CommConfig[comHandler].protocol_type, &gl_CommOpsObj[comHandler]);
	if(lpComOps == NULL){
		logger_error("wnet_comm_ops_init get null lpComOps!\n");
		ret = E_COMM_INIT_FAILED;
	}
	logger_error("lpComOps is ok!!!\n");
	gl_CommLink[comHandler].iSocket = -1;

#ifdef ASYNC_CONNECT
	bDoPreDial = app_false;
#endif

	return ret;
}


int CommParamSet(int comHandler, appbool DNSIP, 
			ST_WIRELESS_PARAM *lpWirelessParam, ST_SSL_PARAM *lpSslParam)
{

	int ret = RET_OK;

	if((ret = CheckCommHandlerValid(comHandler, app_false)) != RET_OK){
		return ret;
	}

	if( lpWirelessParam != NULL){
		memcpy(&gl_CommConfig[comHandler].wireless, lpWirelessParam, sizeof(ST_WIRELESS_PARAM));
	}

	if(lpSslParam != NULL){
		memcpy(&gl_CommConfig[comHandler].ssl, lpSslParam, sizeof(ST_SSL_PARAM));
	}

	gl_CommConfig[comHandler].dns_ip = DNSIP;
	
	return ret;	
}

int CommPreDial(int comHandler, ST_HOST_PARAM *lpHostParam)
{
	int ret =RET_OK;	
#ifdef ASYNC_CONNECT
	ST_ASYNC_CONNECT_PARAM param;
#endif

	logger_debug("[%s] run...\n", __FUNCTION__);

	if((ret = CheckCommHandlerValid(comHandler, app_true)) != RET_OK){
		logger_error("[%s] CheckCommHandlerValid ret:%d...\n", __FUNCTION__, ret);
		return ret;
	}

	#if 0
	if(0==wnet_gprs_is_attatched(0)){
		logger_debug("[%s] wnet_gprs_attach...\n", __FUNCTION__);
		wnet_gprs_attach();
		app_pos_msleep(200);
	}
	#endif
	
#ifdef ASYNC_CONNECT
	if (comHandler == TRANS_COMM_HANDLE) {
#ifdef ASYNC_CONNECT_PPP
		//把GPRS的APN、用户名和用户密码传给wnet库
		memcpy(&param.wireless,  &gl_CommConfig[comHandler].wireless, sizeof(ST_WIRELESS_PARAM));
		ret = gl_CommOpsObj[comHandler].comm->async_predial(&gl_CommOpsObj[comHandler], &param);
		bDoPreDial = app_true;

		logger_debug("[%s] 进入预拨号run...\n", __FUNCTION__);
		
#else
		if (lpHostParam == NULL) {
			//把GPRS的APN、用户名和用户密码传给wnet库
			memcpy(&param.wireless,  &gl_CommConfig[comHandler].wireless, sizeof(ST_WIRELESS_PARAM));
			ret = gl_CommOpsObj[comHandler].comm->async_predial(&gl_CommOpsObj[comHandler], &param);
		}
		else {
			// 异步的预拨号就是做connect就可以了
			param.timeout_ms = 30*1000;
			param.protocol_type = gl_CommConfig[comHandler].protocol_type;
			param.dns_ip = gl_CommConfig[comHandler].dns_ip;
			memcpy(&param.host, lpHostParam, sizeof(ST_HOST_PARAM));
			memcpy(&gl_CommConfig[comHandler].host[0], lpHostParam, sizeof(ST_HOST_PARAM));
			memcpy(&param.ssl,	&gl_CommConfig[comHandler].ssl, sizeof(ST_SSL_PARAM));
			memcpy(&param.wireless,  &gl_CommConfig[comHandler].wireless, sizeof(ST_WIRELESS_PARAM));
			ret = gl_CommOpsObj[comHandler].comm->async_connect(&gl_CommOpsObj[comHandler], &param);
			bDoPreDial = app_true;
			guiPreConnectStartTime = app_get_tick_count();
		}
#endif		
	}
	else {
		//设置同步PPP的时候可以中断操作
		ret = gl_CommOpsObj[comHandler].comm->predial(&gl_CommConfig[comHandler].wireless);
	}
#else
	//设置同步PPP的时候可以中断操作
	ret = gl_CommOpsObj[comHandler].comm->predial(&gl_CommConfig[comHandler].wireless);
#endif
	if (ret < 0) {
		logger_error("predial [FAIL], retval=%d, errno=%d\n", ret, errno);
		ret = E_COMM_CONNECT_FAILED;
	}
	logger_error("CommPreDial---->ret=%d\n", ret);
	return ret;
	
}

int CommChkPredial(int comHandler)
{
	int ret = RET_OK;
	#ifdef ASYNC_CONNECT
	AsyncConnectStateAPP_e state = ASYNC_APP_ST_CONNECT_FAIL;
	#endif
	
#ifdef ASYNC_CONNECT
	if (bDoPreDial == app_false) {

		logger_debug("bDoPreDial  为false\n");
		
		return E_COMM_CONNECT_FAILED;
	}

	app_kb_flush();
	do {
		//app_pos_msleep(20);//给状态机处理的时间
		if((ret = CheckCommHandlerValid(comHandler, app_true)) != RET_OK){
			return ret;
		}
		
		state = gl_CommOpsObj[comHandler].comm->async_ppp_state_chk();
		if( state == ASYNC_APP_ST_CONNECT_OK || state == ASYNC_APP_ST_CONNECT_FAIL ){
			logger_debug("state = %d\n", state);
			break;
		}
		
		//检查按键
		#if 0
		if(app_kb_get_key_ms(50) == KEY_CANCEL){
			async_thread_stop();
			logger_debug("cancel!!!\n");
			return E_TRANS_CANCEL;
		}	
		#endif 
	} while (1);

	if( state == ASYNC_APP_ST_CONNECT_FAIL){

		logger_debug("ASYNC_APP_ST_CONNECT_FAIL!\n");
		
		return E_COMM_CONNECT_FAILED;
	}
#endif

	return ret;
}

#ifdef ASYNC_CONNECT_TCP
appbool CommChkIfPreDial(void)
{
	return bDoPreDial;
}

int CommChkPreConnect(int comHandler, ST_HOST_PARAM *lpHostParam, uint32_t timeout, 
													pAfterDNSCallback pSaveIpFunc)
{
	int ret = RET_OK, iKey = 0;
    char ser_ip[MAX_IP_CNT][MAX_IP_LEN];
    int ser_ip_cnt = 0;
	int fd = -1;	

	AsyncConnectStateAPP_e state = ASYNC_APP_ST_CONNECT_FAIL;

	//logger_debug("[%s] run...\n", __FUNCTION__);
	
	if((ret = CheckCommHandlerValid(comHandler, app_true)) != RET_OK){
		logger_error("CommHandler invalid ret = %d\n", ret);
		return ret;
	}

	app_kb_flush();
	while(1){
		
		state = gl_CommOpsObj[comHandler].comm->async_state_chk((const SysCommOps_t*)&gl_CommConfig[comHandler], 
			&fd, ser_ip, &ser_ip_cnt, app_false); //gl_CommLink[comHandler].iSocket
		//logger_debug("async connect state=%d, fd=%d\n", state, fd);
		if( state == ASYNC_APP_ST_CONNECT_OK || state == ASYNC_APP_ST_CONNECT_FAIL ){
			break;
		}

		//如果检查的超时时间为0则认为直接返回结果无需等待
		if (timeout == 0) {
			ret = E_COMM_CONNECT_FAILED;
			break;
		}
		
		//检查按键
		#if 0
		iKey = app_kb_get_key_ms(20);
		if(iKey == KEY_CANCEL){
			ret = E_TRANS_CANCEL;//E_COMM_CONNECT_CANCEL
			break;
		}
		#endif
		app_pos_msleep(20); //给状态机处理的时间
	
	}

	if( state == ASYNC_APP_ST_CONNECT_FAIL && ret != E_TRANS_CANCEL){
		ret = E_COMM_CONNECT_FAILED;
	}
	
	gl_CommLink[comHandler].iSocket = fd;

	logger_debug("gl_CommLink[comHandler].iSocket = %d\n", gl_CommLink[comHandler].iSocket);

	// 使用DNS 且 连接成功 且 回调不为NULL 才执行回调
	if(gl_CommConfig[comHandler].dns_ip == app_true && 
			ret == RET_OK && pSaveIpFunc != NULL){
		pSaveIpFunc(ser_ip, ser_ip_cnt);
	}
			
	logger_debug("%s->ret = %d\n", __FUNCTION__, ret);
	
	return ret;
}

int CommChkSocketState(int comHandler)
{
	int ret = RET_OK;

	//超过后台挂断时间
	if (app_get_tick_count() > guiPreConnectStartTime+ASYNC_SERVER_SOCKET_TIMEOUT*1000) {
		ret = E_COMM_RECV_FAILED;
		logger_debug("CommChkSocketState time out!!!\n");
		return ret;
	}


	logger_debug("CommChkSocketState ret=%d\n", ret);
	return ret;
}
												
#endif


int CommConnect(int comHandler, ST_HOST_PARAM *lpHostParam, uint32_t timeout, 
													pAfterDNSCallback pSaveIpFunc)
{
	int ret = RET_OK, iKey = 0;
    char ser_ip[MAX_IP_CNT][MAX_IP_LEN];
    int ser_ip_cnt = 0;
	int fd = -1;
	
#ifdef ASYNC_CONNECT
	ST_ASYNC_CONNECT_PARAM param;
	AsyncConnectStateAPP_e state = ASYNC_APP_ST_CONNECT_FAIL;
#endif

	logger_debug("[%s] run...\n", __FUNCTION__);
	
	if((ret = CheckCommHandlerValid(comHandler, app_true)) != RET_OK){
		logger_error("CommHandler invalid ret = %d\n", ret);
		return ret;
	}

	param.timeout_ms = timeout;
	param.protocol_type = gl_CommConfig[comHandler].protocol_type;
	param.dns_ip = gl_CommConfig[comHandler].dns_ip;
	memcpy(&param.host, lpHostParam, sizeof(ST_HOST_PARAM));
	memcpy(&gl_CommConfig[comHandler].host[0], lpHostParam, sizeof(ST_HOST_PARAM));
	memcpy(&param.ssl,  &gl_CommConfig[comHandler].ssl, sizeof(ST_SSL_PARAM));
	memcpy(&param.wireless,  &gl_CommConfig[comHandler].wireless, sizeof(ST_WIRELESS_PARAM));

	logger_debug("protocol_type = %d, ssl ver = %d\n", param.protocol_type, param.ssl.version);

	logger_debug("host ip = %s, name = %s, port = %s, dns_ip =%d\n", 
			param.host.ip_port.ip, param.host.name, param.host.ip_port.port, param.dns_ip);
	
#ifndef ASYNC_CONNECT //异步操作时，DNS在异步连接时解析
	if(gl_CommConfig[comHandler].dns_ip == app_true){ // 需要做域名解析
		fd = gl_CommOpsObj[comHandler].comm->dns(&gl_CommOpsObj[comHandler], 
			(const char *)param.host.name, ser_ip, &ser_ip_cnt);
		if(fd < 0){
			logger_error("dns failed ret = %d, errno = %d\n", fd, errno);
			ret = E_COMM_DNS_FAILED;
			return ret;
		}
		else{
			logger_debug("dns ip =%s\n", ser_ip[0]);
			snprintf(param.host.ip_port.ip, 	sizeof(param.host.ip_port.ip), "%s", ser_ip[0]);
			logger_debug("dns ip =%s\n", param.host.ip_port.ip);
		}

	}
#endif	
	
#ifdef ASYNC_CONNECT
//如果wnet库使用CONTINUOUS_MUL_CONNECT_SUPPORT，
//即每次连接前关闭原有链路，则不检查状态，直接发起连接

	ret = gl_CommOpsObj[comHandler].comm->async_connect(&gl_CommOpsObj[comHandler], &param);
	if(ret < 0){
		logger_error("async_connect failed, ret = %d, errno = %d\n", ret, errno);
		ret = E_COMM_CONNECT_FAILED;
	}
	else {
		app_kb_flush();
		while(1){
			
			state = gl_CommOpsObj[comHandler].comm->async_state_chk((const SysCommOps_t*)&gl_CommConfig[comHandler], 
				&fd, ser_ip, &ser_ip_cnt, app_false); //gl_CommLink[comHandler].iSocket
			//logger_debug("async connect state=%d, fd=%d\n", state, fd);
			if( state == ASYNC_APP_ST_CONNECT_OK || state == ASYNC_APP_ST_CONNECT_FAIL ){
				break;
			}
			//检查按键
			#if 0
			iKey = app_kb_get_key_ms(20);
			if(iKey == KEY_CANCEL){
				ret = E_TRANS_CANCEL;//E_COMM_CONNECT_CANCEL
				break;
			}
			#endif 
			app_pos_msleep(20); //给状态机处理的时间
		}
	}

	if( state == ASYNC_APP_ST_CONNECT_FAIL && ret != E_TRANS_CANCEL){
		ret = E_COMM_CONNECT_FAILED;
	}
	
	gl_CommLink[comHandler].iSocket = fd;

#else
	logger_debug("gl_CommConfig[comHandler].ssl.ca_cert[0] = %s\n", 
								gl_CommConfig[comHandler].ssl.ca_cert[0]);
	fd = gl_CommOpsObj[comHandler].comm->connect(
					&gl_CommOpsObj[comHandler], &param.host.ip_port, &param.ssl, param.timeout_ms);
	if (fd < 0) {
		ret = E_COMM_CONNECT_FAILED;
	}
	gl_CommLink[comHandler].iSocket = fd;
#endif	

	logger_debug("gl_CommLink[comHandler].iSocket = %d\n", gl_CommLink[comHandler].iSocket);

	// 使用DNS 且 连接成功 且 回调不为NULL 才执行回调
	if(gl_CommConfig[comHandler].dns_ip == app_true && 
			ret == RET_OK && pSaveIpFunc != NULL){
		pSaveIpFunc(ser_ip, ser_ip_cnt);
	}
			
	logger_debug("%s->ret = %d\n", __FUNCTION__, ret);
	
	return ret;
}



int CommHangUp(int comHandler)
{
	int ret = RET_OK;

	//logger_debug("[%s] run...\n", __FUNCTION__);

	if((ret = CheckCommHandlerValid(comHandler, app_true)) != RET_OK){
		return ret;
	}

#ifdef ASYNC_CONNECT
	ret = gl_CommOpsObj[comHandler].comm->async_disconnect(&gl_CommOpsObj[comHandler]);
    if (ret < 0) {
        logger_error("async disconnect [FAIL], retval=%d, errno=%d\n", ret, errno);
        ret = E_COMM_CLOSE_FAILED;
    }
#else
	ret = gl_CommOpsObj[comHandler].comm->close(&gl_CommOpsObj[comHandler], gl_CommLink[comHandler].iSocket);
#endif

	logger_debug("comm close done, ret = %d\n", ret);
	bDoPreDial = app_false;
	gl_CommLink[comHandler].iSocket = -1;

	return ret;
}

int CommSend(int comHandler, void *psendbuf, int bytes, uint32_t timeout)
{
	int ret = RET_OK;
	int writebyte = 0;
	uint32_t startick = 0, pcurtick = 0;
	
	//logger_debug("[%s] run...\n", __FUNCTION__);

	if((ret = CheckCommHandlerValid(comHandler, app_true)) != RET_OK){
		return ret;
	}

	//logger_debug("gl_CommLink[comHandler].iSocket = %d\n", gl_CommLink[comHandler].iSocket);

	startick = app_get_tick_count();
	while(1){
		pcurtick = app_get_tick_count();
		if(pcurtick-startick > timeout*1000){
			ret = E_COMM_SEND_FAILED;
			break;
		}
		
		ret = gl_CommOpsObj[comHandler].comm->write(&gl_CommOpsObj[comHandler], 
			&gl_CommConfig[comHandler].host[0], gl_CommLink[comHandler].iSocket, 
			(uint8_t *)(psendbuf)+writebyte, bytes-writebyte, timeout);
		if(ret > 0){
			writebyte += ret;
			logger_debug("write ret = %d, writebyte = %d\n", ret, writebyte);
			if( writebyte >= bytes){
				ret = RET_OK;
				break;
			}
		}
		else if(ret == 0){
			logger_warn("write retval=%d, errno=%d\n", ret, errno);
			if( writebyte >= bytes){
				ret = RET_OK;
				break;
			}
			else{
				ret = E_COMM_SEND_FAILED;
				break;
			}
		}
		else{
			if( errno == EAGAIN || errno == EINTR){
				app_pos_msleep(10);
				continue;
			}
			logger_error("write [FAIL], retval=%d, errno=%d\n", ret, errno);
			ret = E_COMM_SEND_FAILED;
			break;
		}
		app_pos_msleep(10);		
	}
	
	return ret;
}

/**
 * @describe: 寻找第一个字母为Char的地方
 */
char * pub_firstnotchar(char *psStr, char Char)
{
	char *psChar;
	if ( psStr == NULL ) {
		return NULL;
	}

	psChar = psStr;
	while (*psChar == Char && psChar != NULL) {
		psChar++;
	}

	return psChar;
}



int ProcHttpHeader(const void *szHeader, unsigned long *iContenLen, unsigned long *isChunked)
{
	char * ps1 = NULL, *ps2 = NULL, *ps3 = NULL;
	char szTempData[1024] = {0}, szHttpStatus[5] = {0};
    
	*iContenLen = 0;
	*isChunked = 0;
	memset(szTempData, 0, sizeof(szTempData));
	memcpy(szTempData, szHeader, strlen(szHeader) < (sizeof(szTempData) - 1) ? strlen(szHeader) : (sizeof(szTempData) - 1));
	
	pub_strupper(szTempData);
	
	ps1 = strstr(szTempData, "HTTP/"); // fine the position of first "HTTP/"
	if ( ps1 == NULL ) {
		return 1;
	}
	
	ps1 += strlen("HTTP/") + 3; // move the pointer to back of Http/1.1 or Htpp/1.0
	ps2 = pub_firstnotchar(ps1, ' '); // find the position of the first byte that is not space
	
	memset(szHttpStatus, 0, sizeof(szHttpStatus));
	memcpy(szHttpStatus, ps2, 3);
	
	if (memcmp(szHttpStatus, "200", 3) != 0 && memcmp(szHttpStatus, "206", 3) != 0) {// 200 means success
		return 1;
	}
	
	ps1 = strstr(szTempData, "CONTENT-LENGTH"); // find the position of "CONTENT-LENGTH"
	if ( ps1 != NULL ) {
	    char tmpbuff[10] = {0};
	    
	    ps1 += strlen("CONTENT-LENGTH: ");
	    ps2 = strstr(ps1, "\r\n");
	    
	    memcpy(tmpbuff, ps1, (int)(ps2 - ps1));
	    *iContenLen = atoi(tmpbuff);
	} else {
	    char tmpbuff[10] = {0};
	    
        ps1 = strstr(szTempData, "-LENGTH");
	    if ( ps1 != NULL ) {
	        ps1 += strlen("-LENGTH: ");
	        ps2 = strstr(ps1, "\r\n");
	    
	        memcpy(tmpbuff, ps1, (int)(ps2 - ps1));
	        *iContenLen = atoi(tmpbuff);
	    }
    }
    
	//判断是否断点续传
	ps1 = strstr(szTempData, "CONTENT-RANGE: BYTES ");
	if ( ps1 != NULL ) {
		ps1 += strlen("CONTENT-RANGE: BYTES ");
		ps3 = strchr(ps1, '/');
		if ( ps3 != NULL ) {
	        char tmpbuff[10] = {0};
	        
			ps3++;			//跳过'/'字符
			ps2 = strstr(ps3, "\r\n");
			
	        memcpy(tmpbuff, ps3, (int)(ps2 - ps3));
	        *iContenLen = atoi(tmpbuff);
		}
	}
	
	ps1 = strstr(szTempData, "TRANSFER-ENCODING"); // find the position of "TRANSFER-ENCODING"
	if ( ps1 != NULL ) {
		ps1 += strlen("TRANSFER-ENCODING:");	
		ps2 = strstr(ps1, "CHUNKED");
		if (ps2 < strstr(ps1, "\r\n")) {// if the value of TRANSFER-ENCODING if CHUNKED
			*isChunked = 1;
		}
	}
	return 0;
}



int CommRecvhttp(int comHandler, void *precvbuf, int bytes, uint32_t timeout, pRecvDispFc DispCb)
{
	int ret = RET_OK,  time = 0;
	int readnum = 0, iDispInv = 200;
	uint32_t startick = 0, pretick = 0, pcurtick = 0;
	char *pHttps = NULL;
	unsigned long  isChunked = 0, totallen = 0, iDataLen = 0;
	appbool bContinue = app_false;

	if((ret = CheckCommHandlerValid(comHandler, app_true)) != RET_OK){
		return ret;
	}


	if( DispCb != NULL){
		time = timeout;
		DispCb((void *)&time);
	}

	do{
		startick = app_get_tick_count();
		while(1){
			pcurtick = app_get_tick_count();
			if(pcurtick-startick > timeout*1000){
				ret = E_COMM_RECV_TIMEOUT;
				break;
			}
			
			if( pcurtick-pretick > iDispInv){
				time = timeout- (pcurtick - startick)/1000;
				if( DispCb != NULL){
					DispCb(&time);
				}
				pretick = pcurtick;
			}
			logger_debug("&gl_CommOpsObj[%d]:%d;\n",comHandler,gl_CommLink[comHandler].iSocket);
			ret = gl_CommOpsObj[comHandler].comm->read(&gl_CommOpsObj[comHandler], 
				gl_CommLink[comHandler].iSocket, (uint8_t*)(precvbuf)+readnum, bytes-readnum, 200);
			if( ret > 0){
				readnum += ret;
				if(readnum >= bytes){
					logger_error("recv packet too long \n");
					logger_error("readnum = %d bytes = %d\n",readnum,bytes);
					ret = E_COMM_RECV_FAILED;
					break;
				}
				pHttps = strstr((char *)precvbuf, "\r\n\r\n");
				if (pHttps != NULL){
					bContinue = app_true;
					break;
				}
			}
			else if(ret == 0){
			    logger_error(" recv [FAIL],  readnum = %d, retval=%d, errno=%d\n",readnum,  ret, errno);
				ret = E_COMM_RECV_FAILED;
				break;
			}
			else{
				if(errno == EAGAIN || errno == EINTR){
					app_pos_msleep(10);
					continue; // EAGAIN(errno 11) 表明接收超时错误
				}
			    logger_error(" recv [FAIL], retval=%d, errno=%d\n", ret, errno);
			    ret = E_COMM_RECV_FAILED;
				break;
			}

			app_pos_msleep(10);
		}

		if(bContinue == app_false){
			break;
		}

		if ( ProcHttpHeader(precvbuf, &totallen, &isChunked) != 0 ) {
			ret = E_COMM_RECV_FAILED;
			break;
		}
		

		if(!isChunked){//定长
			while(1){
				pcurtick = app_get_tick_count();
				if(pcurtick-startick > timeout*1000){
					ret = E_COMM_RECV_TIMEOUT;
					break;
				}

				if( pcurtick-pretick > iDispInv){
					time = timeout- (pcurtick - startick)/1000;
					if( DispCb != NULL){
						DispCb(&time);
					}
					pretick = pcurtick;
				}

				iDataLen = readnum - ((uint32_t)pHttps + 4 - (uint32_t)precvbuf);   //跳过\r\n\r\n
				if ( (iDataLen >= totallen)) {
					ret = RET_OK;
					break;
				}
				
				ret = gl_CommOpsObj[comHandler].comm->read(&gl_CommOpsObj[comHandler], 
				gl_CommLink[comHandler].iSocket, (uint8_t*)(precvbuf)+readnum, bytes-readnum, 200);
				if( ret > 0){
					readnum += ret;
					if ( readnum < (uint32_t)pHttps + 4 - (uint32_t)precvbuf+totallen ) {
						continue;
					}
				}
				else if(ret == 0){
				    logger_error(" recv [FAIL],  readnum = %d, retval=%d, errno=%d\n", ret, readnum, errno);
					ret = E_COMM_RECV_FAILED;
					break;
				}
				else{
					if(errno == EAGAIN || errno == EINTR){
						app_pos_msleep(10);
						continue; // EAGAIN(errno 11) 表明接收超时错误
					}
				    logger_error(" recv [FAIL], retval=%d, errno=%d\n", ret, errno);
				    ret = E_COMM_RECV_FAILED;
					break;
				}

				app_pos_msleep(10);
			}
		}
		else{//不定长
		  	//蔡文超  如果是CHUNK方式，则检查数据是否接收完全
			if (readnum >= 5) {
					if (memcmp((uint8_t*)(precvbuf)+readnum-5, "0\r\n\r\n", 5) == 0) {
					ret = RET_OK;
					break;
				}
			}
		//	startick = app_get_tick_count();
			while(1){
				pcurtick = app_get_tick_count();
				if(pcurtick-startick > timeout*1000){
					ret = RET_OK;
					break;
				}

				if( pcurtick-pretick > iDispInv){
					time = timeout- (pcurtick - startick)/1000;
					if( DispCb != NULL){
						DispCb(&time);
					}
					pretick = pcurtick;
				}

				ret = gl_CommOpsObj[comHandler].comm->read(&gl_CommOpsObj[comHandler], 
				gl_CommLink[comHandler].iSocket, (uint8_t*)(precvbuf)+readnum, bytes-readnum, 200);
				logger_debug(" recv [%d]=%s\n", ret, (uint8_t*)(precvbuf)+readnum);
				if( ret > 0){
					readnum += ret;
				}
				else if(ret == 0){
				    logger_error(" recv [FAIL],  readnum = %d, retval=%d, errno=%d\n", readnum, ret, errno);
					ret = E_COMM_RECV_FAILED;
					break;
				}
				else{
					if(errno == EAGAIN || errno == EINTR){
						app_pos_msleep(10);
						continue; // EAGAIN(errno 11) 表明接收超时错误
					}
				    logger_error(" recv [FAIL], retval=%d, errno=%d\n", ret, errno);
				    ret = E_COMM_RECV_FAILED;
					break;
				}

				if(memcmp((uint8_t*)precvbuf+readnum-4,"\r\n\r\n",4) == 0){
					ret = RET_OK;
					break;
				}
			}
		}
	}while(0);
	
	if(ret!=RET_OK)
		logger_hexdump("precvbuf fail:\n",precvbuf, readnum);
	return ret;
}



int CommRecv(int comHandler, void *precvbuf, int bytes, uint32_t timeout, pRecvDispFc DispCb)
{
	int ret = RET_OK,  time = 0;
	int readnum = 0, iDispInv = 200;
	uint32_t startick = 0, pretick = 0, pcurtick = 0;

	
	//logger_debug("[%s] run...\n", __FUNCTION__);
	if((ret = CheckCommHandlerValid(comHandler, app_true)) != RET_OK){
		return ret;
	}

	if( DispCb != NULL){
		time = timeout;
		DispCb((void *)&time);
	}
	startick = app_get_tick_count();
	while(1){
		pcurtick = app_get_tick_count();
		if(pcurtick-startick > timeout*1000){
			ret = E_COMM_RECV_TIMEOUT;
			break;
		}
		
		if( pcurtick-pretick > iDispInv){
			time = timeout- (pcurtick - startick)/1000;
			if( DispCb != NULL){
				DispCb(&time);
			}
			pretick = pcurtick;
		}
		
		//logger_debug("gl_CommLink[comHandler].iSocket = %d\n", gl_CommLink[comHandler].iSocket);
		ret = gl_CommOpsObj[comHandler].comm->read(&gl_CommOpsObj[comHandler], 
			gl_CommLink[comHandler].iSocket, (uint8_t*)(precvbuf)+readnum, bytes-readnum, 200);
		if( ret > 0){
			logger_debug("read  ret = %d\n", ret);
			readnum += ret;
			if(readnum >= bytes){
				ret = RET_OK;
				break;
			}
		}
		else if(ret == 0){
		    logger_error(" recv [FAIL],  readnum = %d, retval=%d, errno=%d\n", ret, readnum, errno);
			ret = E_COMM_RECV_FAILED;
			break;
		}
		else{
			if(errno == EAGAIN || errno == EINTR){
				app_pos_msleep(10);
				continue; // EAGAIN(errno 11) 表明接收超时错误
			}
		    logger_error(" recv [FAIL], retval=%d, errno=%d\n", ret, errno);
		    ret = E_COMM_RECV_FAILED;
			break;
		}
	}
	return ret;
}


static void comm_var_init(void)
{
	int iLoop = 0;
	for(iLoop = 0; iLoop < MAX_COMM_HANDLER_NUM; iLoop++){
		gl_CommOpsObj[iLoop].comm = NULL;
		gl_CommOpsObj[iLoop].protocol = NULL;
		gl_CommLink[iLoop].iSocket = -1;
	}

}

void CommModuleInit(void)
{
	logger_debug("CommModuleInit\n");
	comm_var_init();
}

//exit 会关闭模块所有连接
void CommModuleExit(void)
{
	int iLoop = 0;
	
	logger_debug("CommModuleExit\n");
	
	for(iLoop = 0; iLoop < MAX_COMM_HANDLER_NUM; iLoop++){
		if(gl_CommOpsObj[iLoop].comm != NULL && gl_CommOpsObj[iLoop].comm->exit != NULL){
			gl_CommOpsObj[iLoop].comm->exit(NULL);
			break;
		}
	}
	
	comm_var_init();
}

#ifdef CFG_4G_FLAG
appbool CheckBaseStationValid(tBaseStationExt oBaseStation)
{
	if(oBaseStation.Wnet.oLte.mcc <= 0
		|| oBaseStation.Wnet.oLte.mnc < 0
		|| oBaseStation.Wnet.oLte.mcc >= 0xFFFF
		|| oBaseStation.Wnet.oLte.mnc >= 0xFFFF){ //获取基站信息失败
		return app_false;
	}
	return app_true;
}
#endif

static appbool bHaveBasetation = app_false;
void GetBaseStation(void *oBaseStationExt)
{
	int ret;
	CommBaseStation_t *gBaseStation = (CommBaseStation_t*)oBaseStationExt;

#ifdef CFG_4G_FLAG
	tBaseStationExt oBaseStation;
	uint32_t starttick = 0;

	memset(&oBaseStation, 0, sizeof(oBaseStation));
	starttick = app_get_tick_count();
	while(1){
		if ( app_get_tick_count() - starttick > gBaseStation->timeoutms){
			break;
		}

		//有SIM卡就附网，没附网的话获取到的基站信息可能是错的 
		//if(gBaseStation->commtype == CT_GPRS){ //210323
			if(app_wireless_check_simcard()==0){//附网前一定要检测卡，要不然附网容易失败
				ret = app_wireless_wnet_attach(); //获取基站前先附网
			}
		//}
	
		ret = app_wireless_get_basestation_info(&oBaseStation);
		logger_debug("app_wireless_get_basestation_info=%d\n",ret);
		logger_debug("mcc=%d\n",oBaseStation.Wnet.oLte.mcc);
		logger_debug("mnc=%d\n",oBaseStation.Wnet.oLte.mnc);
		logger_debug("tac=%d\n",oBaseStation.Wnet.oLte.tac);
		logger_debug("cell_id=%d\n",oBaseStation.Wnet.oLte.cell_id);
		if(ret!=0 || CheckBaseStationValid(oBaseStation)==app_false){ //获取基站失败
			app_pos_msleep(200);
			continue;
		}
		gBaseStation->stBaseStation = oBaseStation; //获取成功才赋值
		break;
	}
#else
	GPRS_NETWORK_STATUS_T stGprsStatus;
	memset(&stGprsStatus,0,sizeof(GPRS_NETWORK_STATUS_T));
	ret = app_wireless_wnet_get_network_info(&stGprsStatus);
	if (ret == 0) {
		gBaseStation->stBaseStation.Wnet.oGprs.mcc = stGprsStatus.mcc;
		gBaseStation->stBaseStation.Wnet.oGprs.mnc = stGprsStatus.mnc;
		gBaseStation->stBaseStation.Wnet.oGprs.lac = stGprsStatus.lac;
		gBaseStation->stBaseStation.Wnet.oGprs.cell_id = stGprsStatus.cell_id;
	}
	logger_debug("mcc=%d\n",gBaseStation->stBaseStation.Wnet.oGprs.mcc);
	logger_debug("mnc=%d\n",gBaseStation->stBaseStation.Wnet.oGprs.mnc);
	logger_debug("lac=%d\n",gBaseStation->stBaseStation.Wnet.oGprs.lac);
	logger_debug("cell_id=%d\n",gBaseStation->stBaseStation.Wnet.oGprs.cell_id);
#endif	
	bHaveBasetation = app_true; //已获取基站信息
}

void CommGetBaseStation(CommBaseStation_t *oBaseStationExt)
{
	ST_WORK_NODE stmwork;
	int ret = 0;
 
	ret = init_work(&stmwork, GetBaseStation, oBaseStationExt);
	if(ret == 0){
		ret = schedule_work(&stmwork);
	}
	if(ret != 0){
		GetBaseStation(oBaseStationExt);
	}
}

appbool CheckGetBaseStation(void){
	return bHaveBasetation;
}

