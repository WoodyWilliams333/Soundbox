#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <wolfssl/openssl/err.h>
#include <wolfssl/openssl/ssl.h>
#include <wolfssl/openssl/rand.h>
#include <wolfssl/openssl/crypto.h>
#include <wolfssl/openssl/md5.h>
#include <wolfssl/openssl/sha.h>
#include "sha1.h"
#include <os_pthread.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "logger.h"
#include <wolfssl/openssl/rsa.h>
#include "appped.h"
//#include "base64.h"
#include "ped.h"
#include "appdef.h"
#include "ota_http_upgrade.h"
#include "filecalc.h"
#include "task_thread.h"
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "network.h"
#include "socket.h"
#include "errno.h"
#include "libwnet.h"
#include "https.h"
#include "genutils.h"
#include "appmalloc.h"
#include "appfile.h"
#include "appsys.h"
#include "downloadfile.h"
#include <wolfssl/openssl/sha.h>
#include "codestool.h"

#pragma GCC diagnostic ignored "-Wcast-align"

#define HTTP_HEADERS_MAXLEN 	2048 	// Headers 的最大长度
#define HTTP_CONTENT_MAXLEN 	1024*8 	// Headers 的最大长度//216k 16k:35秒 8k:28秒 4k: 34.6秒 2k：203秒
const char image_tail_magic[] = "npup";
const char pkg_tail_magic[] = "npkg";
const char bin_tail_magic[] = "bin";

//static int gSockfd = -1;
static int gHttpTimeout = 10;//秒

/*
 * Headers 按需更改
 */
const char *HttpsPostHeaders = 	"User-Agent: Mozilla/4.0 (compatible; MSIE 5.01; Windows NT 5.0)\r\n"
								"Cache-Control: no-cache\r\n"
								"Accept: */*\r\n"
								"Content-type: application/x-www-form-urlencoded\r\n";  //text/plain//application/x-www-form-urlencoded

void ShowCerts(SSL * ssl)
{
    X509 *cert;
    char *line;
 
    cert = SSL_get_peer_certificate(ssl);
    if (cert != NULL)
    {
        logger_error("数字证书信息:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        logger_error("证书: %s\n", line);
        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        logger_error("颁发者: %s\n", line);
        free(line);
        X509_free(cert);
    }
    else
        logger_error("无证书信息！\n");
}

static void MIS_SSL_debug_err_msg(WOLFSSL *ssl)
{
	int errorNum;
	char *errorstr = NULL;//[128];

	errorNum = 0;
	errorstr = (char *)app_malloc(128);
	if(errorstr == NULL)
		goto EXIT;
	memset(errorstr, 0, 128);
	
	errorNum = wolfSSL_get_error(ssl, errorNum);
	wolfSSL_ERR_error_string(errorNum, errorstr);
	logger_error("SSL-get-error()=%d, err-string=%s\n", errorNum, errorstr);
EXIT:
	if(errorstr != NULL)
		app_free(errorstr);
}

/*
 * @Name 			- 创建TCP连接, 并建立到连接
 * @Parame *server 	- 字符串, 要连接的服务器地址, 可以为域名, 也可以为IP地址
 * @Parame 	port 	- 端口
 *
 * @return 			- 返回对应sock操作句柄, 用于控制后续通信
 */
int client_connect_tcp(char *server,int port)
{
	int sockfd;
	struct hostent *host;
	struct sockaddr_in cliaddr;
	struct timeval stTimeVal;
	int retval;
	char *host_out = NULL;
	int host_size = 256;
	logger_debug("%s\n", __FUNCTION__);
	logger_debug("server:%s,port:%d;\n",server,port);

	sockfd=net_socket(AF_INET,SOCK_STREAM,0);

	if(sockfd < 0){
		logger_error("create socket error\n");
		return -1;
	}
	host_out = app_malloc(host_size);
	if(host_out == NULL){
		close(sockfd);
		return -1;
	}
    if(!(host = gethostbyname_safe(server, host_out, host_size))) { //(线程安全)域名解析开始
           logger_error("parse dns: %s fail, hptr=%p !\n", server, host);
           app_free(host_out);
           close(sockfd);
           return -2;
    }

	bzero(&cliaddr,sizeof(struct sockaddr));
	cliaddr.sin_family=AF_INET;
	cliaddr.sin_port=htons(port);
	cliaddr.sin_addr = *((struct in_addr *)host->h_addr);

	//cliaddr.sin_addr.s_addr = inet_addr(host->h_addr); //设置地址
        
    stTimeVal.tv_sec    = gHttpTimeout;
    stTimeVal.tv_usec   = 0;
//    retval = setsockopt(sockfd, SOL_SOCKET, SO_CNTTIMEO, &stTimeVal, sizeof(stTimeVal));
//    if(retval < 0 && errno != ENOTSUP) {
//        logger_error("net recv timeout set fail, retval=%d, errno=%d, fd=%d, timeout_ms=%d(ms)\n", retval, errno, sockfd, gHttpTimeout);
//	}
    retval = net_setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &stTimeVal, sizeof(stTimeVal));
    if(retval < 0 && errno != ENOTSUP) {
        logger_error("net recv timeout set fail, retval=%d, errno=%d, fd=%d, timeout_ms=%d(ms)\n", retval, errno, sockfd, gHttpTimeout);
	}

  	if(net_connect(sockfd,(struct sockaddr *)&cliaddr,sizeof(struct sockaddr))<0){
		logger_error("[-] error=%d\n",errno);
		app_free(host_out);
		close(sockfd);
		return -3;
	}
	app_free(host_out);
	return(sockfd);
}

int pack_head(ota_params *ota_param,const char *host, int port, const char *page, char *data,int len)
{
	int re_len = strlen(page) + strlen(host) + strlen(HttpsPostHeaders) + HTTP_HEADERS_MAXLEN;

	char *post = NULL;
	post = app_malloc(re_len);
	if(post == NULL){
		return -1;
	}
    logger_debug("[%s] run...len=%d;\n", __FUNCTION__,len);

	sprintf(post, \
			"GET %s HTTP/1.0\r\n"\
			"Host: %s\r\n"\
			"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"\
			"Range: bytes=%d-%d\r\n"\
			"Content-length: 0\r\n"\
			"Connection: Keep-Alive\r\n\r\n"\
			,page, host, (int)(ota_param->star_size), (int)(ota_param->star_size+len-1));
	logger_debug("post =%s;\n", post);

	re_len = strlen(post);
	memset(data, 0, re_len+1);
	memcpy(data, post, re_len);

	app_free(post);
	return re_len;
}


int pack_head_ex(int	star_size,const char *host, int port, const char *page, char *data,int len)
{
	int re_len = strlen(page) + strlen(host) + strlen(HttpsPostHeaders) + HTTP_HEADERS_MAXLEN;
	char uri[150] = {0};
	char *post = NULL;
	post = app_malloc(re_len);
	if(post == NULL){
		return -1;
	}
    logger_debug("[%s] run...len=%d;\n", __FUNCTION__,len);
	deal_url((char *)page,uri,NULL,NULL,0);
	
	sprintf(post, \
			"GET %s HTTP/1.1\r\n"\
			"Host: %s\r\n"\
			"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"\
			"Range: bytes=%d-%d\r\n"\
			"Connection: Keep-Alive\r\n\r\n"\
			,uri, host,star_size, star_size+len-1);
	logger_debug("post =%s;\n", post);

	re_len = strlen(post);
	memset(data, 0, re_len+1);
	memcpy(data, post, re_len);

	app_free(post);
	return re_len;
}

int pack_http_post_head(char *method,int	star_size,const char *host, int port, const char *page,const char *OcpKey,char *bodydata,int bodyLen, 
		char *data,int len)
{
	int re_len = strlen(page) + strlen(host) + strlen(HttpsPostHeaders) + HTTP_HEADERS_MAXLEN;
	char uri[150] = {0};
	char *post = NULL;
	post = app_malloc(re_len);
	if(post == NULL){
		return -1;
	}
    logger_debug("[%s] run...len=%d;\n", __FUNCTION__,len);
	deal_url((char *)page,uri,NULL,NULL,0);

	if(OcpKey){
		if(bodydata && bodyLen >0){
			sprintf(post, \
					"%s %s HTTP/1.1\r\n"\
					"Host: %s\r\n"\
					"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"\
					"Range: bytes=%d-%d\r\n"\
					"Content-length: %d\r\n"\
					"Content-Type: application/json\r\n"
					"Ocp-Apim-Subscription-Key: %s\r\n"
					"Connection: Keep-Alive\r\n\r\n%s"\
					,method,uri, host,star_size, star_size+len-1,bodyLen,OcpKey,bodydata);

		}else{
			sprintf(post, \
					"%s %s HTTP/1.1\r\n"\
					"Host: %s\r\n"\
					"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"\
					"Range: bytes=%d-%d\r\n"\
					"Content-length: 0\r\n"\
					"Content-Type: application/json\r\n"
					"Ocp-Apim-Subscription-Key: %s\r\n"
					"Connection: Keep-Alive\r\n\r\n"\
					,method,uri, host,star_size, star_size+len-1,OcpKey);

		}
		
	}else{
		sprintf(post, \
					"%s %s HTTP/1.1\r\n"\
					"Host: %s\r\n"\
					"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"\
					"Range: bytes=%d-%d\r\n"\
					"Content-length: 0\r\n"\
					"Content-Type: application/json\r\n"
					"Connection: Keep-Alive\r\n\r\n"\
					,method,uri, host,star_size, star_size+len-1);
			
	}
	logger_debug("post =%s;\n", post);

	re_len = strlen(post);
	memset(data, 0, re_len+1);
	memcpy(data, post, re_len);

	app_free(post);
	return re_len;
}



/*
 * @Name 		- 	初始化SSL, 并且绑定sockfd到SSL
 * 					此作用主要目的是通过SSL来操作sock
 * 					
 * @return 		- 	返回已完成初始化并绑定对应sockfd的SSL指针
 */
WOLFSSL *ssl_init(int sockfd)
{
	int re = 0;
	WOLFSSL *ssl;
	WOLFSSL_CTX *ctx;
   
    logger_debug("[%s] run...\n", __FUNCTION__);
    
	wolfSSL_library_init();
    //OpenSSL_add_all_algorithms(); //这个用不成，请使用SSL_APP_DEFAULT_CIPHER_LIST
	wolfSSL_load_error_strings();
	ctx = wolfSSL_CTX_new(wolfTLSv1_2_client_method());
	if (ctx == NULL){     
		return NULL;
	}
    wolfSSL_CTX_set_verify(ctx, WOLFSSL_VERIFY_NONE, NULL); 
    if (!wolfSSL_CTX_set_cipher_list(ctx, SSL_APP_DEFAULT_CIPHER_LIST))
    {
        logger_error("set cipher list= \"%s\" fail.\n", SSL_APP_DEFAULT_CIPHER_LIST);  
    }
    //wolfSSL_CTX_set_timeout(ctx, gHttpTimeout);
	ssl = wolfSSL_new(ctx);
	if (ssl == NULL){
		MIS_SSL_debug_err_msg(ssl);
		wolfSSL_CTX_free(ctx);
		return NULL;
	}
    
	/* 把socket和SSL关联 */
	re = wolfSSL_set_fd(ssl, sockfd);
	if (re == 0){
		wolfSSL_free(ssl);
		wolfSSL_CTX_free(ctx);
		return NULL;
	}
	wolfSSL_CTX_free(ctx);
	
	return ssl;
}

int ssl_connect(WOLFSSL *ssl)
{
	int re = 0;
	
	logger_debug("[%s] run...\n", __FUNCTION__);
	re = wolfSSL_connect(ssl);
	if(re != 1){
        MIS_SSL_debug_err_msg(ssl);
		return -1;
	}
    else
    {
        logger_debug("Connected with %s encryption\n", SSL_get_cipher(ssl));
        ShowCerts(ssl);
    }
    return 0;
}

/*
 * @Name 			- 通过SSL建立连接并发送数据
 * @Parame 	*ssl 	- SSL指针, 已经完成初始化并绑定了对应sock句柄的SSL指针
 * @Parame 	*data 	- 准备发送数据的指针地址
 * @Parame 	 size 	- 准备发送的数据长度
 *
 * @return 			- 返回发送完成的数据长度, 如果发送失败, 返回 -1
 */
int tcp_send(ota_protocol_t net_mode, int sockfd, WOLFSSL *ssl, const char *data, int size)
{
	int re = 0;
	int count = 0;

    logger_debug("[%s] run...size=%d;\n", __FUNCTION__,size);

    if(net_mode == OTA_PROTOCOL_HTTPS){
        if (!ssl || !data) {
            return -1;
        }
    }else{
        if (!sockfd || !data) {
            return -1;
        }
    }

	while(count < size)
	{
        if(net_mode == OTA_PROTOCOL_HTTPS){
            re = wolfSSL_write(ssl, data+count, size-count);
        }else{
            re = net_send(sockfd, data+count, size-count, 0);
        }
		if(re < 0){
            logger_error("SSL_write err !!!\n");
			return -2;
		}
		count += re;
	}

	return count;
}

int checkStr(const char *str)
{
	int i = 0;
	
	for(i = 0;i < strlen(str);i++){
		if(str[i] > 0x80){
			return -1;
		}
	}
	return 0;
}

int parse_path(char *input,char *file_path)
{
	const char tmpPath[] = OTA_DIR"/";
	char *pName = NULL;
	int iRet=-1;
	int j=0;
	
	logger_debug("[%s] run...input=%s;\n", __FUNCTION__,input);
	for(j = strlen(input)-1; j >= 0;j--){
		if(input[j] == '/'){
			pName = &input[j+1];
			break;
		}
	}
	if(j < 0){
		pName = input;
	}
	if(pName != NULL){
		if(strlen(pName) > 30 || checkStr(pName) < 0){
			logger_error("parse_path err !!!\n");
			return -1;
		}
		
		snprintf(file_path, 60, "%s%s",tmpPath,pName);
		iRet = 0;
	}
	return iRet;
}

int getName(ota_params *ota_param,image_hdr_t *pihdr,char *file_path,int *file_size)
{
	int iRet=-1;
	logger_debug("%s\n", __FUNCTION__);
	logger_debug("[%s] pihdr->size:%d ota_param->star_size=%d;\n", __FUNCTION__,pihdr->size,ota_param->star_size);
	logger_debug("[%s] pihdr->firmware_num=%d;\n", __FUNCTION__,pihdr->firmware_num);
	if(ota_param->star_size < sizeof(image_hdr_t)){
		logger_debug("++++++++++++++++\n");
		strcpy(file_path,SYSTEM_IHDR_FILE);
		*file_size = sizeof(image_hdr_t)-ota_param->star_size;
		iRet = 0;
		logger_debug("first get name:file_path=%s,file_size=%d\n",file_path,file_size);
	}else{
		logger_debug("++++++++++++++++\n");
		for(int i = 0; i < pihdr->firmware_num; i++){
			logger_debug("[%s] pihdr->firms_info[%d].offset:%d pihdr->firms_info[i].len=%d;\n", __FUNCTION__,i,pihdr->firms_info[i].offset,pihdr->firms_info[i].len);
			if(ota_param->star_size >= pihdr->firms_info[i].offset + pihdr->firms_info[i].len){
				if(i == pihdr->firmware_num-1){//下载完毕
					logger_debug("++++++++++++++++\n");
					*file_size = 0;
					iRet = 0;
				}
				logger_debug("++++++++++++++++\n");
				continue;
			}

			iRet = parse_path(pihdr->firms_info[i].path,file_path);
			logger_debug("[%s] file_path:%s ;\n", __FUNCTION__,file_path);
			if(app_file_exists(file_path) >= 0 && 
				app_file_size(file_path) > pihdr->firms_info[i].len){
				logger_debug("[%s] pihdr->firms_info[%d].path:%s len=%d;app_file_size():%d;\n", __FUNCTION__,i,pihdr->firms_info[i].path,pihdr->firms_info[i].len,app_file_size(file_path));
				logger_error("getName error!!!\n");
				return iRet;
			}
			logger_debug("[%s] pihdr->firms_info[%d].path:%s len=%d;app_file_size():%d;\n", __FUNCTION__,i,pihdr->firms_info[i].path,pihdr->firms_info[i].len,app_file_size(file_path));

			*file_size = pihdr->firms_info[i].offset + pihdr->firms_info[i].len - ota_param->star_size;
			if(file_path != NULL)
				iRet = 0;
			break;
		}
	}
	logger_debug("[%s] getName file_path:%s *file_size=%d;\n", __FUNCTION__,file_path,*file_size);
	return iRet;
}

int parse_size(image_hdr_t *pihdr,char *file_path,int *file_size)
{
	int iRet=-1;
	int size;
	logger_debug("%s\n", __FUNCTION__);
	for(int i = 0; i < pihdr->firmware_num; i++){
		if(strlen(pihdr->firms_info[i].path)){
			iRet = parse_path(pihdr->firms_info[i].path,file_path);
			if(app_file_exists(file_path) < 0){
				*file_size = pihdr->firms_info[i].len;
				iRet = 0;
				break;
			}
			size = app_file_size(file_path);
			if(size < pihdr->firms_info[i].len){
				*file_size = pihdr->firms_info[i].len - size;
				iRet = 0;
				break;
			}
		}else{
			*file_size = 0;
			iRet = 0;
			break;
		}
	}

	logger_debug("[%s] parse_size file_path:%s *file_size=%d;\n", __FUNCTION__,file_path,*file_size);
	return iRet;
}

int tcp_recv(ota_protocol_t net_mode, int sockfd, WOLFSSL *ssl, char *buff, int size,int get_header)
{
	int i = 0; 				// 读取数据取换行数量, 即判断headers是否结束 
	int re,iRet = -1;
	int len = 0,offset=0,len_tmp=0,total=0;
	struct timeval stTimeVal;
	char *headers = NULL,b;
	char *pctxlen = NULL,*pctxlenend = NULL;
	const char FieldStrEnd[] = "\x0d\x0a";
	const char CtxLenStr[] = "Content-Length:";
	char fieldstr[20+1] = {0};
	logger_debug("%s\n", __FUNCTION__);
	headers = app_malloc(HTTP_HEADERS_MAXLEN);
	if(headers == NULL){
		return -1;
	}

    if(net_mode == OTA_PROTOCOL_HTTPS){
        if(ssl == NULL){
            iRet = -1;
            goto EXIT;
        }
    }else{
        if(!sockfd){
            goto EXIT;
        }
    }

	stTimeVal.tv_sec    = gHttpTimeout;
	stTimeVal.tv_usec   = 0;
	re = net_setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &stTimeVal, sizeof(stTimeVal));
	if(re < 0 && errno != ENOTSUP) {
		logger_error("net recv timeout set fail, retval=%d, errno=%d, fd=%d, timeout_ms=%d(ms)\n", re, errno, sockfd, gHttpTimeout);
	}

    // Headers以换行结束, 此处判断头是否传输完成
    offset = 0;
	while(1)
	{
        if(net_mode == OTA_PROTOCOL_HTTPS){
            if((len = wolfSSL_read(ssl, &b, 1)) != 1){
                break;
            }
        }else{
            if((len = net_recv(sockfd, &b, 1, 0)) != 1){
                break;
            }
        }
		headers[offset++] = b;
		if(i < 4){
			if(b == '\r' || b == '\n'){
				i++;
				if(i>=4){
					break;
				}
			}else{
				i = 0;
			}
		}
		logger_debug("%c", b);		// 打印Headers
	}
	logger_debug("\n");
	pctxlen = strstr(headers,"HTTP/1.1 ");
	if(pctxlen != NULL){
		pctxlen += strlen("HTTP/1.1 "); //偏移到字段结束
		pctxlenend = strstr(pctxlen, " "); // 获取长度串
		if (pctxlenend){
				memcpy(fieldstr, pctxlen, pctxlenend-pctxlen);
				pub_trimspcstr(fieldstr, ' ');
				total = atoi(fieldstr); //返回码
			}
	}
	if(total < 200 || total >= 300){
		logger_error("total = %d!!!\n",total);
		logger_error("recv fail, len=%d, errno=%d, fd=%d, timeout_ms=%d(ms)\n", len, errno, sockfd, gHttpTimeout);
		iRet = -1;
		goto EXIT;
	}

	if(NULL!=strstr(headers,"Connection: close")) //Sever will disconnected the tcp connection
	{
		logger_error("need to re-connect tcp!!!\n");
		iRet = -9; //need to reconnect tcp
		goto EXIT;
	}
	
	pctxlen = strstr(headers,CtxLenStr);
	if(pctxlen != NULL){
		pctxlen += strlen(CtxLenStr); //偏移到字段结束
		pctxlenend = strstr(pctxlen, FieldStrEnd); // 获取长度串
			if (pctxlenend){
				memcpy(fieldstr, pctxlen, pctxlenend-pctxlen);
				pub_trimspcstr(fieldstr, ' ');
				total = atoi(fieldstr); //整个报文内容总长度
				logger_error("total = %d!!!\n",total);
			}
	}

	if(total > size){
		logger_error("total = %d!!!\n",total);
		iRet = -1;
		goto EXIT;
	}

	//是否获取http报文头(有的业务需要报文头数据)
	if(get_header){
		memcpy(buff,headers,offset);
	}else{
		offset = 0;
	}
	while(1){
		if(check_playing() == PLAY_BUSY){
			iRet = -1;
			goto EXIT;
		}
		if(offset >= size || offset >= total)
			break;
		len_tmp = (total - offset) > 1024 ? 1024 : (total - offset);
        if(net_mode == OTA_PROTOCOL_HTTPS){
            len = wolfSSL_read(ssl, buff+offset, len_tmp);
        }else{
            len = net_recv(sockfd, buff+offset, len_tmp, 0);
        }
		if(len < 0 || offset < 0){
			iRet = -1;
			goto EXIT;
		}
		offset += len;
		logger_debug("[%s] len:%d,offset:%d;\n", __FUNCTION__,len,offset);

	}
	iRet = offset;
EXIT:
	logger_debug("[%s] iRet:%d;\n", __FUNCTION__,iRet);
	if(headers != NULL)
		app_free(headers);

	return iRet;
}

int pkg_update(ota_params *ota_param,image_hdr_t *pihdr,char *rdata,int r_len)
{
	char *ptr = NULL ,*ptrstart = NULL,*ptrnext = NULL;
	int iRet = -1;
	int len_hdr = sizeof(image_hdr_t);
	int save_len = 0,tmp_len = 0;
	char name[64]={0};
	int i = 0;
	uint32_t type;
	
	ptrstart = ptr = rdata;
	hash_update(ota_param,rdata,r_len);
	while(1){
		if(ptr - ptrstart >= r_len)
			break;
		ptrnext = ptr;
		if(ota_param->star_size == 0 && r_len >= 79){
				memcpy(pihdr->magic,"npkg",4);
				memcpy(&pihdr->size,&rdata[23],4);
				
				if(memcmp(&rdata[30],"\x00\x00",2) !=0 ){
					iRet = -1;
					logger_error("pkg_version error!!!\n");
					break;
				}
				
				ptr = &rdata[79];
				if(*ptr == 0){//固件
					ptr += 5;
				}else{
					iRet = -1;
					logger_error("pkg_img error!!!\n");
					break;
				}
				//logo
				
					
				ptr += 5;//UID1+清除数据标识
				if(memcmp(ptr,"\x00\x00\x00\x00",4)==0){
					ptr += 4;//库文件
				}else{
					iRet = -1;
					logger_error("pkg_lib error!!!\n");
					break;
				}
				if(memcmp(ptr,"\x00\x00\x00\x00",4)==0){
					ptr += 4;//字库文件
				}else{
					iRet = -1;
					logger_error("pkg_font error!!!\n");
					break;
				}
				if(memcmp(ptr,"\x00\x00\x00\x00",4)==0){
					ptr += 4;//桌面文件
				}else{
					iRet = -1;
					logger_error("pkg_desk error!!!\n");
					break;
				}
				if(memcmp(ptr,"\x00\x00\x00\x00",4)==0){
					ptr += 4;//其它文件
				}else{
					memcpy(&pihdr->firmware_num,ptr,4);
					if(pihdr->firmware_num > MAX_FIRMWARE_NUM){
						iRet = -1;
						logger_error("pkg_num error!!!\n");
						break;
					}
					ptr += 4;
					iRet = ota_file_save(SYSTEM_IHDR_FILE,(char *)pihdr,len_hdr,0);
					if(iRet < 0){
						break;
					}
				}
				save_len = ptr - ptrnext;
		}else{
			iRet = parse_size(pihdr,name,&tmp_len);
			if(iRet < 0){
				break;
			}
			if(tmp_len == 0){
				for(i = 0;i < pihdr->firmware_num;i++){
					if(strlen(pihdr->firms_info[i].path))
						continue;
					sprintf(pihdr->firms_info[i].path,"%s/%s",HOME_DIR,ptr);//文件名称
					ptr += strlen(ptr)+1;
					memcpy(&type,ptr,4);//文件类型 
					ptr += 4;
					if(type == TASK_APP_FILE || type == TASK_DYNAMIC_LIB_FILE)
						ptr += 4;//CID
					memcpy(&pihdr->firms_info[i].len,ptr,4);
					ptr += 4;
					iRet = ota_file_save(SYSTEM_IHDR_FILE,(char *)pihdr,len_hdr,0);
					if(iRet < 0){
						break;
					}
					break;
				}
				save_len = ptr-ptrnext;
			}else {
				save_len = r_len-(ptr-rdata);
				if(tmp_len < save_len){
					save_len = tmp_len;
				}
				iRet = ota_file_save(name,(char *)ptr,save_len,1);
				if(iRet < 0){
					break;
				}
				ptr += save_len;
			}
		}
		ota_param->down_flag = FOTA_HTTP_DOWN_DOWNING;
		ota_param->star_size += save_len;
		ota_param_save(ota_param,SYSTEM_UPGRADE_FILE);
	}
	return iRet;
}

int load_file(ota_params *ota_param,char *host, int port, char *url)
{
	WOLFSSL *ssl = NULL;
	int r_len = 0,offset=0,tmp_len = 0,sockfd = -1;
	char *sdata = NULL;
	char *rdata = NULL;
	char name[64]={0};
	int data_len = 0;
	int ssize = strlen(url) + HTTP_HEADERS_MAXLEN; 	// 欲发送的数据包大小
	int len_hdr = sizeof(image_hdr_t);
	image_hdr_t *pihdr = NULL;
	int iRet = -1;

    logger_debug("%s\n", __FUNCTION__);
    logger_debug("url:%s;\n",url);

	pihdr = (image_hdr_t *)app_malloc(len_hdr);
	if(pihdr == NULL){
		goto EXIT;
	}
	memset(pihdr,0,len_hdr);
	//读取头文件image_hdr_t
	
	sdata = (char *)app_malloc(ssize);
	if(sdata == NULL){
		goto EXIT;
	}

	rdata = app_malloc(HTTP_CONTENT_MAXLEN);
	if(rdata == NULL){
		goto EXIT;
	}
	
	sockfd = client_connect_tcp(host, port);
	if(sockfd < 0){
		iRet = -2;
		goto EXIT;
	}

    if(ota_param->net_mode == OTA_PROTOCOL_HTTPS){
        // 2、SSL初始化, 关联Socket到SSL
        ssl = ssl_init(sockfd);
        if(ssl == NULL){
            iRet = -3;
            goto EXIT;
        }
        iRet = ssl_connect(ssl);
        if(iRet < 0){
            iRet = -4;
            goto EXIT;
        }
    }

	offset = 0;
	
	while(1){
		logger_debug("[%s]  ota_param->star_size:%d;\n", __FUNCTION__,ota_param->star_size);
		if(check_playing() == PLAY_BUSY){
			iRet = -1;
			logger_error("check_playing !!!\n");
			break;
		}
		//img结尾
		if(ota_param->star_size >= ota_param->size ||
			( ota_param->data_type == FOTA_DATA_DOWN_IMG &&
			 (ota_param->star_size + strlen(image_tail_magic)) >= ota_param->size)
			){
			logger_debug("++++++++++++++++\n");
			iRet = 0;
			break;
		}
		logger_debug("++++++++++++++++\n");
		if(app_file_exists(SYSTEM_IHDR_FILE) >= 0){
			if(ota_param->star_size <= app_file_size(SYSTEM_IHDR_FILE)){
				offset = ota_param->star_size;
			}else if(ota_param->star_size > app_file_size(SYSTEM_IHDR_FILE)){
				offset = len_hdr;
			}
			iRet = ota_file_read(SYSTEM_IHDR_FILE,(char *)pihdr,offset);
			if(iRet < 0){
				logger_debug("++++++++++++++++\n");
				break;
			}
		}else{
			offset = 0;
			ota_param->star_size = 0;
			ota_param->down_flag = FOTA_HTTP_DOWN_INIT;
			ota_param_save(ota_param,SYSTEM_UPGRADE_FILE);
		}
		logger_debug("++++++++++++++++\n");
		if(ota_param->star_size == 0){
			app_file_cleardir(OTA_DIR);
		}
		
		iRet = getName(ota_param,pihdr,name,&r_len);
		if(iRet < 0 || r_len <= 0){
			logger_debug("++++++++++++++++\n");
			break;
		}
	
		if(r_len < HTTP_CONTENT_MAXLEN)
			tmp_len = r_len;
		else
			tmp_len = HTTP_CONTENT_MAXLEN;

		// 3、组合GET数据
		data_len = pack_head_ex(ota_param->star_size,host, port, url, sdata,tmp_len);
        logger_debug("%s",sdata);

        // 4、通过SSL发送数据
        r_len = tcp_send(ota_param->net_mode, sockfd, ssl, sdata, data_len);
        if(r_len < 0){
			logger_debug("++++++++++++++++\n");
            iRet = -5;
            break;
        }

        r_len = tcp_recv(ota_param->net_mode, sockfd, ssl, rdata, tmp_len,0);
        if(r_len <= 0){
			logger_debug("++++++++++++++++\n");
            iRet = -6;
            break;
        }
		
		logger_debug("++++++++++++++++\n");
		logger_debug("recv length:%d\n",tmp_len);
		logger_debug("++++++++++++++++\n");

		if(ota_param->star_size == 0 && r_len >= 79){
			#if 0
			if(memcmp(rdata,image_tail_magic,4) == 0){
				ota_param->data_type = FOTA_DATA_DOWN_IMG;
			}else{
				iRet = -1;
				ota_param->down_flag = FOTA_HTTP_DOWN_FAIL;
				logger_error("ota_data error!!!\n");
				break;
			}
			#else
			ota_param->data_type = FOTA_DATA_DOWN_IMG;
			#endif
			ota_param_save(ota_param,SYSTEM_UPGRADE_FILE);
		}
			
		logger_debug("++++++++++++++++\n");
		iRet = ota_file_save(name,(char *)rdata,r_len,1);
		if(iRet < 0){
			logger_debug("++++++++++++++++\n");
			break;
		}
		logger_debug("++++++++++++++++\n");
		ota_param->down_flag = FOTA_HTTP_DOWN_DOWNING;
		if(ota_param->star_size < len_hdr){
			memcpy(pihdr+offset,rdata,r_len);
			offset += r_len;
		}
		ota_param->star_size += r_len;
		ota_param_save(ota_param,SYSTEM_UPGRADE_FILE);
		logger_debug("++++++++++++++++\n");
	}

EXIT:
	// 6、关闭会话, 释放内存
	logger_debug("+++++++gSockfd=%d\n",sockfd);
	if(sdata != NULL)
		app_free(sdata);
	if(rdata != NULL)
		app_free(rdata);
	if(pihdr != NULL)
		app_free(pihdr);
	if(sockfd > 0)
	    close(sockfd);
	if(ssl != NULL){
		wolfSSL_shutdown(ssl);
		wolfSSL_ERR_free_strings();
		wolfSSL_free(ssl);
	}
	
	return iRet;
}


int DownloadFile(ota_params *ota_param,char *host, int port, char *url,char *filename)
{
	WOLFSSL *ssl = NULL;
	int r_len = 0,tmp_len = 0,sockfd = -1;
	char *sdata = NULL;
	char *rdata = NULL;
	int data_len = 0;
	int ssize = strlen(url) + HTTP_HEADERS_MAXLEN; 	// 欲发送的数据包大小
	int iRet = -1;

    logger_debug("%s\n", __FUNCTION__);
    logger_debug("url:%s;\n",url);

RETRY:
	//读取头文件image_hdr_t
	sdata = (char *)app_malloc(ssize);
	if(sdata == NULL){
		goto EXIT;
	}

	rdata = app_malloc(HTTP_CONTENT_MAXLEN);
	if(rdata == NULL){
		goto EXIT;
	}
	
	sockfd = client_connect_tcp(host, port);
	if(sockfd < 0){
		iRet = -2;
		goto EXIT;
	}

    if(ota_param->net_mode == OTA_PROTOCOL_HTTPS){
        // 2、SSL初始化, 关联Socket到SSL
        ssl = ssl_init(sockfd);
        if(ssl == NULL){
			iRet = -3;
            goto EXIT;
        }
        iRet = ssl_connect(ssl);
        if(iRet < 0){
			iRet = -4;
            goto EXIT;
        }
    }

	while(1){
		logger_debug("[%s]  ota_param->star_size:%d;\n", __FUNCTION__,ota_param->star_size);
		if(check_playing() == PLAY_BUSY){
			iRet = ERR_BUSY_FIALED;
			logger_error("check_playing !!!\n");
			break;
		}
		
		if(ota_param->star_size >= ota_param->size ){
			logger_debug("++++++++++++++++\n");
			iRet = 0;
			break;
		}
		
		r_len= ota_param->size - ota_param->star_size;
		if(r_len < HTTP_CONTENT_MAXLEN)
			tmp_len = r_len;
		else
			tmp_len = HTTP_CONTENT_MAXLEN;

		// 3、组合GET数据
		data_len = pack_head_ex(ota_param->star_size,host, port, url, sdata,tmp_len);
        logger_debug("%s",sdata);

        // 4、通过SSL发送数据
        r_len = tcp_send(ota_param->net_mode, sockfd, ssl, sdata, data_len);
        if(r_len < 0){
			logger_debug("++++++++++++++++\n");
            iRet = -5;
            break;
        }

        r_len = tcp_recv(ota_param->net_mode, sockfd, ssl, rdata, tmp_len,0);
        if(r_len <= 0){
			logger_debug("++++++++++++++++\n");
			if(r_len==-9)
           		iRet = -9;
			else
				iRet = -6;
            break;
        }
		
		logger_debug("++++++++++++++++\n");
		logger_debug("recv length:%d\n",r_len);
		logger_debug("++++++++++++++++\n");

		if(ota_param->star_size == 0 && r_len >= 79){
			#if 0
			if(memcmp(rdata,image_tail_magic,4) == 0){
				ota_param->data_type = FOTA_DATA_DOWN_IMG;
			}else{
				iRet = -1;
				ota_param->down_flag = FOTA_HTTP_DOWN_FAIL;
				logger_error("ota_data error!!!\n");
				break;
			}
			#else
			ota_param->data_type = FOTA_DATA_DOWN_IMG;
			#endif
			
			if(NULL!=strstr(filename,OTA_TEMP_FILE))
				ota_param_save(ota_param,SYSTEM_UPGRADE_FILE);
			else{
				iRet = -7;
            	goto EXIT;
			}
				
		}
			
		logger_debug("ota_file_save r_len=%d\n",r_len);
		iRet = ota_file_save(filename,(char *)rdata,r_len,1);
		if(iRet < 0){
			logger_debug("++++++++++++++++\n");
			break;
		}
		logger_debug("++++++++++++++++\n");
		ota_param->down_flag = FOTA_HTTP_DOWN_DOWNING;
		ota_param->star_size += r_len;
		
		if(NULL!=strstr(filename,OTA_TEMP_FILE))
			ota_param_save(ota_param,SYSTEM_UPGRADE_FILE);
		else{
			iRet = -7;
        	goto EXIT;
		}
		logger_debug("++++++++++++++++\n");
	}

EXIT:
	// 6、关闭会话, 释放内存
	logger_debug("++++++++++++++++\n");
	if(sdata != NULL)
		app_free(sdata);
	if(rdata != NULL)
		app_free(rdata);
	if(sockfd > 0)
	    close(sockfd);
	if(ssl != NULL){
		wolfSSL_shutdown(ssl);
		wolfSSL_ERR_free_strings();
		wolfSSL_free(ssl);
	}

	if(iRet==-9)
		goto RETRY;
	return iRet;
}

int https_down(ota_params *ota_param, char *fileName)
{
	int iLen = 0;
	char *szDNS = NULL;//[100]={0};
	char szPort[10]={0};
	//https默认端口号是80或者443
	char *url_page =  NULL;
	char *pBegin = NULL,*pEnd = NULL;
	appbool power_save_bak = app_on;
	int iRet = -1;
	
	logger_debug("fileName:%s;\n",fileName);
	power_save_bak = app_set_auto_powersave_mode(app_off);
	
	url_page = (char *)app_malloc(1024);
	if(url_page == NULL){
		goto EXIT;
    }
	szDNS = (char *)app_malloc(100);
	if(szDNS == NULL){
		goto EXIT;
    }
	sprintf(url_page,"%s",ota_param->url);
	pBegin = strstr(url_page,"://");
	if(pBegin == NULL){
		goto EXIT;
	}
	pBegin += 3;
	
	pEnd = NULL;
	pEnd = strstr(pBegin,"/");
	if(pEnd == NULL){
		goto EXIT;
	}
	if(pEnd > pBegin)
		iLen = pEnd - pBegin;
	if(iLen > 0){
		memcpy((char *)szDNS,pBegin,iLen);
		szDNS[iLen]=0;
        //https://horn.newpostech.com:26057/download/1122.bmp 这里提取带端口号的地址
		pBegin = NULL;
		pBegin = strstr((char *)szDNS,":");
		if(pBegin != NULL){
			strcpy((char *)szPort,pBegin+1);
			*pBegin = 0;
		}else{
            if(ota_param->net_mode == OTA_PROTOCOL_HTTP){
                strcpy((char *)szPort,"80");//HTTP后台不返回端口号的情况下，默认80
            }else{
                strcpy((char *)szPort,"443");//HTTPS后台不返回端口号的情况下，默认443
            }
		}
	}
	
	if(ota_param->net_mode == OTA_PROTOCOL_HTTPS || ota_param->net_mode == OTA_PROTOCOL_HTTP){
        logger_debug(">>>5, net_mode=%d(HTTPS=%d, HTTP=%d)\n", ota_param->net_mode, OTA_PROTOCOL_HTTPS, OTA_PROTOCOL_HTTP);
		iRet = DownloadFile(ota_param,(char *)szDNS, atoi((char *)szPort), url_page,fileName);
    }
    logger_debug(">>>6, load_file iRet=%d\n", iRet);
EXIT:
	if(url_page != NULL){
		app_free(url_page);
	}
	if(szDNS != NULL)
		app_free(szDNS);
	app_set_auto_powersave_mode(power_save_bak);
	return iRet;
}


int http_load_file(char *file_path,int file_size,char *host, int port, char *url,signed_struct *signed_va)
{
	WOLFSSL *ssl = NULL;
	int r_len = 0,tmp_len = 0;
	char *sdata = NULL;
	char *rdata = NULL;
	char hashbuf[65]={0};
	int data_len = 0;
	int ssize = strlen(url) + HTTP_HEADERS_MAXLEN; 	// 欲发送的数据包大小
	int iRet = -1,http_fd = -1,start_size = 0,start_tmp_size = 0,file_fd = -1;
	ota_protocol_t net_mode = OTA_PROTOCOL_HTTP;
	WOLFSSL_SHA256_CTX *hash256 = NULL;
	
	if(signed_va){
		hash256 = (WOLFSSL_SHA256_CTX *)app_malloc(sizeof(WOLFSSL_SHA256_CTX));
		if(hash256 == NULL){
			signed_va = NULL;
		}else{
			SHA256_Init(hash256);
		}
	}

    logger_debug("%s\n", __FUNCTION__);
    logger_debug("url:%s,file_path=%s,file_size=%d\n",url,file_path,file_size);
	if(strncmp(url,"https",5) == 0){
		net_mode = OTA_PROTOCOL_HTTPS;
	}else if(strncmp(url,"http",4) == 0){
		net_mode = OTA_PROTOCOL_HTTP;		
	}	

	sdata = (char *)app_malloc(ssize);
	if(sdata == NULL){
		goto EXIT;
	}

	rdata = app_malloc(HTTP_CONTENT_MAXLEN);
	if(rdata == NULL){
		goto EXIT;
	}
	
	http_fd = client_connect_tcp(host, port);
	if(http_fd < 0){
		iRet = -2;
		goto EXIT;
	}

    if(net_mode == OTA_PROTOCOL_HTTPS){
        // 2、SSL初始化, 关联Socket到SSL
        ssl = ssl_init(http_fd);
        if(ssl == NULL){
            iRet = -3;
            goto EXIT;
        }
        iRet = ssl_connect(ssl);
        if(iRet < 0){
            iRet = -4;
            goto EXIT;
        }
    }
	start_size = app_file_size(file_path);
	if(start_size < 0){
		start_size = 0;
	}
	if(signed_va){
		start_tmp_size = start_size;
		if(start_tmp_size > 0){
			file_fd = app_file_open(file_path, O_RDONLY);
			do{
				
				r_len = app_file_read(file_fd, rdata,MIN(start_tmp_size,HTTP_CONTENT_MAXLEN));
				if(r_len > 0){
					SHA256_Update(hash256,rdata,r_len);
					start_tmp_size -=  r_len;
				}else{
					break;
				}
			}while(start_tmp_size > 0);
			app_file_close(file_fd);
		}
	}
	while(file_size > 0){
		
		file_fd = app_file_open(file_path,O_RDWR | O_CREAT);
		if(file_fd < 0){
			iRet = -5;
	        break;
		}
			
		logger_debug("[%s]  start_size:%d;\n", __FUNCTION__,start_size);
		if(check_playing() == PLAY_BUSY){
			iRet = -8;
			logger_error("check_playing !!!\n");
			break;
		}
		
		if(file_size < HTTP_CONTENT_MAXLEN)
			tmp_len = file_size;
		else
			tmp_len = HTTP_CONTENT_MAXLEN;

		// 3、组合GET数据
		data_len = pack_head_ex(start_size,host, port, url, sdata,tmp_len);
        logger_debug("%s",sdata);

        // 4、通过SSL发送数据
        r_len = tcp_send(net_mode, http_fd, ssl, sdata, data_len);
        if(r_len < 0){
			logger_debug("++++++++++++++++\n");
            iRet = -9;
            break;
        }

        r_len = tcp_recv(net_mode, http_fd, ssl, rdata, tmp_len,0);
        if(r_len <= 0){
			logger_debug("++++++++++++++++\n");
            iRet = -6;
            break;
        }
		
		logger_debug("++++++++++++++++\n");
		logger_debug("recv length:%d\n",tmp_len);
		logger_debug("++++++++++++++++\n");
	
		if(signed_va){
			SHA256_Update(hash256,rdata,r_len);
		}
		app_file_seek(file_fd, (int)0, SEEK_END);
		iRet = app_file_write(file_fd, (uint8_t *) rdata, r_len);
		if (iRet != r_len) {
			logger_error("write fail;\n");
			iRet = -7;
            break;
		}else{
			app_file_close(file_fd);
			file_fd = -1;	
		}
		file_size -= iRet;
		start_size += iRet;
		logger_debug("+++++file_size=%d++++++++\n",file_size);
	}

	if(file_size == 0){
		iRet = 0;
	}
	if(signed_va){
		SHA256_Final((uint8_t*)hashbuf,hash256);
		np_hex_to_string((uint8_t*)hashbuf,32,signed_va->sign);
		signed_va->sign_len = 64;
	}
	
EXIT:
	// 6、关闭会话, 释放内存
	logger_debug("+++++iRet=%d++++++++\n",iRet);
	if(sdata != NULL)
		app_free(sdata);
	if(rdata != NULL)
		app_free(rdata);

	if(http_fd > 0)
	    close(http_fd);

	if(file_fd >= 0){
		app_file_close(file_fd);
	}
	
	if(ssl != NULL){
		wolfSSL_shutdown(ssl);
		wolfSSL_ERR_free_strings();
		wolfSSL_free(ssl);
	}

	if(hash256 != NULL)
		app_free(hash256);
	return iRet;
}


int http_load_file_bypost(char *file_path,int file_size,char *host, int port, char *url,
	char* uuid,char* opk_key,signed_struct *signed_va)
{
	WOLFSSL *ssl = NULL;
	int r_len = 0,tmp_len = 0;
	char *sdata = NULL;
	char *rdata = NULL;
	char hashbuf[65]={0};
	int data_len = 0;
	int ssize = strlen(url) + HTTP_HEADERS_MAXLEN; 	// 欲发送的数据包大小
	int iRet = -1,http_fd = -1,start_size = 0,start_tmp_size = 0,file_fd = -1;
	ota_protocol_t net_mode = OTA_PROTOCOL_HTTP;
	WOLFSSL_SHA256_CTX *hash256 = NULL;
	
	if(signed_va){
		hash256 = (WOLFSSL_SHA256_CTX *)app_malloc(sizeof(WOLFSSL_SHA256_CTX));
		if(hash256 == NULL){
			signed_va = NULL;
		}else{
			SHA256_Init(hash256);
		}
	}

    logger_debug("%s\n", __FUNCTION__);
    logger_debug("url:%s,file_path=%s,file_size=%d\n",url,file_path,file_size);
	if(strncmp(url,"https",5) == 0){
		net_mode = OTA_PROTOCOL_HTTPS;
	}else if(strncmp(url,"http",4) == 0){
		net_mode = OTA_PROTOCOL_HTTP;		
	}	

	sdata = (char *)app_malloc(ssize);
	if(sdata == NULL){
		goto EXIT;
	}

	rdata = app_malloc(HTTP_CONTENT_MAXLEN);
	if(rdata == NULL){
		goto EXIT;
	}
	
	http_fd = client_connect_tcp(host, port);
	if(http_fd < 0){
		iRet = -2;
		goto EXIT;
	}

    if(net_mode == OTA_PROTOCOL_HTTPS){
        // 2、SSL初始化, 关联Socket到SSL
        ssl = ssl_init(http_fd);
        if(ssl == NULL){
            iRet = -3;
            goto EXIT;
        }
        iRet = ssl_connect(ssl);
        if(iRet < 0){
            iRet = -4;
            goto EXIT;
        }
    }
	start_size = app_file_size(file_path);
	if(start_size < 0){
		start_size = 0;
	}
	if(signed_va){
		start_tmp_size = start_size;
		if(start_tmp_size > 0){
			file_fd = app_file_open(file_path, O_RDONLY);
			do{
				
				r_len = app_file_read(file_fd, rdata,MIN(start_tmp_size,HTTP_CONTENT_MAXLEN));
				if(r_len > 0){
					SHA256_Update(hash256,rdata,r_len);
					start_tmp_size -=  r_len;
				}else{
					break;
				}
			}while(start_tmp_size > 0);
			app_file_close(file_fd);
		}
	}
	while(file_size > 0){
		
		file_fd = app_file_open(file_path,O_RDWR | O_CREAT);
		if(file_fd < 0){
			iRet = -5;
	        break;
		}
			
		logger_debug("[%s]  start_size:%d;\n", __FUNCTION__,start_size);
		if(check_playing() == PLAY_BUSY){
			iRet = -8;
			logger_error("check_playing !!!\n");
			break;
		}
		
		if(file_size < HTTP_CONTENT_MAXLEN)
			tmp_len = file_size;
		else
			tmp_len = HTTP_CONTENT_MAXLEN;

		// 3、组合请求报文
		data_len = pack_http_post_head((char*)"POST",start_size,host, port, url,opk_key,NULL,0 ,sdata,tmp_len);
        logger_debug("%s",sdata);

        // 4、通过SSL发送数据
        r_len = tcp_send(net_mode, http_fd, ssl, sdata, data_len);
        if(r_len < 0){
			logger_debug("++++++++++++++++\n");
            iRet = -9;
            break;
        }

        r_len = tcp_recv(net_mode, http_fd, ssl, rdata, tmp_len,0);
        if(r_len <= 0){
			logger_debug("++++++++++++++++\n");
            iRet = -6;
            break;
        }
		
		logger_debug("++++++++++++++++\n");
		logger_debug("recv length:%d\n",tmp_len);
		logger_debug("++++++++++++++++\n");
	
		if(signed_va){
			SHA256_Update(hash256,rdata,r_len);
		}
		app_file_seek(file_fd, (int)0, SEEK_END);
		iRet = app_file_write(file_fd, (uint8_t *) rdata, r_len);
		if (iRet != r_len) {
			logger_error("write fail;\n");
			iRet = -7;
            break;
		}else{
			app_file_close(file_fd);
			file_fd = -1;	
		}
		file_size -= iRet;
		start_size += iRet;
		logger_debug("+++++file_size=%d++++++++\n",file_size);
	}

	if(file_size == 0){
		iRet = 0;
	}
	if(signed_va){
		SHA256_Final((uint8_t*)hashbuf,hash256);
		np_hex_to_string((uint8_t*)hashbuf,32,signed_va->sign);
		signed_va->sign_len = 64;
	}
	
EXIT:
	// 6、关闭会话, 释放内存
	logger_debug("+++++iRet=%d++++++++\n",iRet);
	if(sdata != NULL)
		app_free(sdata);
	if(rdata != NULL)
		app_free(rdata);

	if(file_fd >= 0){
		app_file_close(file_fd);
	}
	
	if(ssl != NULL){
		wolfSSL_shutdown(ssl);
		wolfSSL_ERR_free_strings();
		wolfSSL_free(ssl);
	}

	if(http_fd > 0)
	    close(http_fd);

	if(hash256 != NULL)
		app_free(hash256);
	return iRet;
}



int sent_http_method(char *method,char *http_url,char* opk_key,char* body,int bodyLen,unsigned char *outData,int *outLen,int get_header_flag)
{

	WOLFSSL *ssl = NULL;
	int r_len = 0,tmp_len = 0,retry_count = 3;
	char *sdata = NULL;
	int data_len = 0;
	int iRet = -1,szPort = 0;
	char szDNS[65] = {0};
	int ssize = strlen(http_url) + HTTP_HEADERS_MAXLEN;	// 欲发送的数据包大小
	int http_fd = -1,start_size = 0;
	ota_protocol_t net_mode = OTA_PROTOCOL_HTTP;
	
	logger_debug("%s\n", __FUNCTION__);
	logger_debug("url:%s,bodyLen=%d\n",http_url,bodyLen);
	if(strncmp(http_url,"https",5) == 0){
		net_mode = OTA_PROTOCOL_HTTPS;
	}else if(strncmp(http_url,"http",4) == 0){
		net_mode = OTA_PROTOCOL_HTTP;		
	}	

	deal_url(http_url,NULL,szDNS,&szPort,0);

	if(szPort == 0){
		if(strncmp(http_url,"https",5) == 0){
			szPort = 443;	
		}else if(strncmp(http_url,"http",4) == 0){
			szPort = 80;
		}
	}

	sdata = (char *)app_malloc(ssize);
	if(sdata == NULL){
		goto EXIT;
	}
	
	http_fd = client_connect_tcp(szDNS, szPort);
	if(http_fd < 0){
		iRet = -2;
		goto EXIT;
	}

	if(net_mode == OTA_PROTOCOL_HTTPS){
		// 2、SSL初始化, 关联Socket到SSL
		ssl = ssl_init(http_fd);
		if(ssl == NULL){
			iRet = -3;
			goto EXIT;
		}
		iRet = ssl_connect(ssl);
		if(iRet < 0){
			iRet = -4;
			goto EXIT;
		}
	}

	do{
					
		logger_debug("[%s]	start_size:%d;\n", __FUNCTION__,start_size);

		// 3、组合GET数据
		data_len = pack_http_post_head(method,start_size,szDNS, szPort, http_url,opk_key,body,bodyLen,sdata,tmp_len);
		logger_debug("%s",sdata);

		// 4、通过SSL发送数据
		r_len = tcp_send(net_mode, http_fd, ssl, sdata, data_len);
		if(r_len < 0){
			logger_debug("++++++++++++++++\n");
			iRet = -9;
			break;
		}
		memset(sdata,0,ssize);
		if(outData && outLen){
			r_len = tcp_recv(net_mode, http_fd, ssl, (char *)outData, *outLen,get_header_flag);
		}else{
			r_len = tcp_recv(net_mode, http_fd, ssl, sdata, tmp_len,get_header_flag);
		}
		if(r_len > 0){
			if(outLen){
				*outLen = r_len;
			}
			logger_debug("++++++++++++++++\n");
			iRet = 0;
			break;
		}
		
		logger_debug("++++++++++++++++\n");
		logger_debug("recv length:%d\n",tmp_len);
		logger_debug("++++++++++++++++\n");

	}while(retry_count--);

EXIT:
	// 6、关闭会话, 释放内存
	logger_debug("+++++iRet=%d+++++http_fd=%d+++\n",iRet,http_fd);
	if(sdata != NULL)
		app_free(sdata);

	
	if(ssl != NULL){
		wolfSSL_shutdown(ssl);
		wolfSSL_ERR_free_strings();
		wolfSSL_free(ssl);
	}

	if(http_fd > 0)
	    close(http_fd);

	return iRet;

}



