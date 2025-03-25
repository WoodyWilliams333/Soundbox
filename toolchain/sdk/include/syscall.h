/*
 * @file    syscall.h
 * @author  generated automatically.
 * @date    2019-10-15 17:13:51
 * DO NOT MODIFY IT!
 */


#ifndef _EXPORT_SYSCALL_H_
#define _EXPORT_SYSCALL_H_

#include "syscall_dep.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


int syscall_reg_gprs_signal(uint32 callback);
void *syscall_get_errno(void);
int syscall_exit(int stat);
int syscall_stat(const char *filename, struct file_stat *st);
int syscall_gettimeofday(void *tp, void *tzp);
int syscall_statfs(struct statfs *st);
int syscall_isatty(int fd);
int syscall_close(int fd);
int syscall_getpid(void);
clock_t syscall_times(struct tms *tp);
int syscall_mkdir(const char *pathname, mode_t mode);
int syscall_readdir(int fd, void *buf, int count);
int syscall_closedir(int fd);
int syscall_rename(const char *oldpath, const char *newpath);
int syscall_unlink(const char *pathname);
int syscall_system(const char *command);
int syscall_access(const char *pathname, int mode);
void *syscall_brk(void *addr);
int syscall_select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
int syscall_fs_format(void);
int syscall_msleep(uint32_t keepms);
int syscall_printf(char *buff, int buflen);
int syscall_beep(uint32 freq, uint32 ms);
TCPIP_SOCKET_T syscall_SocketCreate(int type);
int syscall_SocketConnect(TCPIP_SOCKET_T so, SOCKET_ADDR_S *addr_ptr, int addr_len);
int syscall_SocketSend(TCPIP_SOCKET_T so, char *buf, int len);
int syscall_SocketSendTo(TCPIP_SOCKET_T so, char *buf, int len, SOCKET_ADDR_S *to);
int syscall_SocketRecv(TCPIP_SOCKET_T so, char *buf, int len);
int syscall_SocketRecvFrom(TCPIP_SOCKET_T so, char *buf, int len, SOCKET_ADDR_S *from);
int syscall_SocketClose(TCPIP_SOCKET_T so);
int syscall_SocketErrNo(TCPIP_SOCKET_T so);
int syscall_sock_select(sci_fd_set *in, sci_fd_set *out, sci_fd_set *ex, long tv);
void syscall_FD_ZERO(sci_fd_set *set);
void syscall_FD_SET(TCPIP_SOCKET_T so, sci_fd_set *set);
void syscall_FD_CLR(TCPIP_SOCKET_T so, sci_fd_set *set);
int syscall_FD_ISSET(TCPIP_SOCKET_T so, sci_fd_set *set);
int syscall_INetAtoN(char *ip_str, TCPIP_IPADDR_T *ipaddr_ptr);
char *syscall_INetNtoA(TCPIP_IPADDR_T ipaddr);
TCPIP_HOST_HANDLE syscall_NetworkGetHostByName(char *name_ptr, TCPIP_IPADDR_T *address, int flags);
int syscall_GetSockName(TCPIP_SOCKET_T so, SOCKET_ADDR_S *name_ptr);
int syscall_GetPeerName(TCPIP_SOCKET_T so, SOCKET_ADDR_S *name_ptr);
int syscall_SocketGetOpt(TCPIP_SOCKET_T so, SOCKET_OPT_E opt, uint32 *pdata);
int syscall_SocketSetOpt(TCPIP_SOCKET_T so, SOCKET_OPT_E opt, uint32 *pdata);
int syscall_SocketGetState(TCPIP_SOCKET_T so, short *state_ptr);
int syscall_socket(const char *devname, int domain, int type, int protocol);
int syscall_accept(int fd, struct sockaddr *addr, socklen_t *addrlen);
int syscall_bind(int fd, const struct sockaddr *addr, socklen_t addrlen);
int syscall_connect(int fd, const struct sockaddr *addr, socklen_t addrlen);
ssize_t syscall_send(int fd, const void *buf, size_t len, int flags);
ssize_t syscall_sendto(int fd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
ssize_t syscall_recv(int fd, void *buf, size_t len, int flags);
ssize_t syscall_recvfrom(int fd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
int syscall_getsockopt(int fd, int level, int optname, void *optval, socklen_t *optlen);
int syscall_setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen);
struct hostent *syscall_gethostbyname(const char *devname, const char *name);
int syscall_open_camera(uint32 callback, BOOLEAN is_preview, BOOLEAN is_once);
int syscall_close_camera(void);
int syscall_camera_preview(BOOLEAN is_preview);
BOOLEAN MNNV_GetIMEIEx(MN_DUAL_SYS_E dual_sys, MN_IMEI_T imei);
int syscall_write_sy_license(uint8 *buff, uint32 item_length);
int syscall_read_sy_license(uint8 *buff, uint32 item_length);
BOOLEAN syscall_set_upgrade_firmware_pathflag(const char *filepath);
BOOLEAN syscall_set_upgrade_app_flag(void);
void *syscall_create_event(const char *name_ptr);
int syscall_set_event(void *group_ptr, uint32 flags_to_set, uint32 set_option);
int syscall_get_event(void *group_ptr, uint32 requested_flags, uint32 get_option, uint32 *actual_flags_ptr, uint32 wait_option);
int syscall_delete_event(void *group_ptr);
int syscall_send_signal(void *signal_ptr, uint32 dest_id);
int syscall_send_signal_front(void *signal_ptr, uint32 dest_id);
void *syscall_get_signal(uint32 thread_id);
void *syscall_peek_signal(uint32 thread_id);
void syscall_assert(const char *expinfo, const char *file, int line);
uint32 syscall_get_thread_id(void);
SCI_TIMER_PTR syscall_create_timer(const char *timer_name, TIMER_FUN timer_fun, uint32 input, uint32 timer_expire, uint32 auto_activate);
SCI_TIMER_PTR syscall_create_period_timer(const char *timer_name, TIMER_FUN timer_fun, uint32 input, uint32 timer_expire, uint32 auto_activate);
int syscall_change_timer(SCI_TIMER_PTR timer_ptr, TIMER_FUN timer_fun, uint32 timer_expire);
int syscall_active_timer(SCI_TIMER_PTR timer_ptr);
int syscall_deactive_timer(SCI_TIMER_PTR timer_ptr);
BOOLEAN syscall_is_timer_active(SCI_TIMER_PTR timer_ptr);
void syscall_del_timer(SCI_TIMER_PTR timer_ptr);
void syscall_timer_exit(SCI_TIMER_PTR timer_ptr);
int syscall_get_timer_info(SCI_TIMER_PTR timer_ptr, char *name, BOOLEAN *active, uint32 *remaining_time, uint32 *reschedule_time);
uint32 syscall_get_current_time(void);
uint32 syscall_get_tick_count(void);
int syscall_get_tick_time(SCI_TICK_TIME_T *tick_time);
void *syscall_create_mutex(const char *name_ptr, uint32 priority_inherit);
int syscall_delete_mutex(void *mutex_ptr);
int syscall_get_mutex(void *mutex_ptr, uint32 wait_option);
int syscall_put_mutex(void *mutex_ptr);
void *syscall_create_sem(const char *name_ptr, uint32 initial_count);
int syscall_delete_sem(void *sem_ptr);
int syscall_get_sem(void *sem_ptr, uint32 wait_option);
int syscall_put_sem(void *sem_ptr);
int syscall_delete_signal(void *sig);
void *syscall_malloc(uint32 size);
int syscall_free(void *sig);
int syscall_thread_exit(void);
void syscall_set_lcd_brightness(uint32 bright);
int syscall_ttsplay(const unsigned char *ttsResour, unsigned int datalen, int cb, int volume, uint32 callback);
int syscall_ttsplay_ex(int format, const unsigned char *ttsResour, unsigned int datalen, int cb, int volume, uint32 callback);
int syscall_TTS_Abort(void);
int syscall_power_off(void);
int syscall_reboot(void);
int syscall_verify_file(const char *filename);
int syscall_get_free_mem(uint32 *total_heap_mem, uint32 *available_heap_mem, uint32 *max_available_heap_mem_blk);
BOOLEAN syscall_is_privilege(void);
int TelephonyDial(const char *num);
int TelephonyHangup(void);
int syscall_set_bat_type(char *bat_type);
int syscall_get_bat_type(char *bat_type, int len);
int lcd_function(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
int syscall_firmware_update(const char *imgfile);
void syscall_reset_on_panic(int enable);
uint8_t * syscall_read_uid(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _EXPORT_H_ */
