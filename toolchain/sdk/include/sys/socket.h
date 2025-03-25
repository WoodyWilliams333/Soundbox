/**
@if Chinese
 * @brief       此模块用于描述 <strong>Socket</strong> 相关的接口
 * @par         文件    socket.h
 * @author      Waylon
 * @date        2020-12-26
 * @version     V1.0
 *
 * @remarks Change History:
 * Date          | Version       | Author          | Desc
 * ------------- | ------------- | --------------- | ----
 * 2020/12/26    | 1.0.0         | Waylon          | 创建文件
 * 2022/04/21    | 1.0.1         | Wenming         | 修改部分中文注释 
@else 
 * @brief       This module is used to describe <strong>Socket</strong> interfaces module
 * @par         File    socket.h
 * @author      Waylon
 * @date        2020-12-26
 * @version     V1.0
 *
 * @remarks Change History:
 * Date          | Version       | Author          | Desc
 * ------------- | ------------- | --------------- | ----
 * 2020/12/26    | 1.0.0         | Waylon          | Create file
 * 2022/04/21    | 1.0.1         | Wenming         | Add doxygen English comment information
@endif 
*/


/**
@if Chinese
 * @defgroup Socket 套接字
@else 
 * @defgroup Socket Socket
@endif 
 * @{
*/

/*
 * Copyright (c) 1982, 1985, 1986, 1988, 1993, 1994
 *  The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *  This product includes software developed by the University of
 *  California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *  @(#)socket.h    8.4 (Berkeley) 2/21/94
 * $FreeBSD: src/sys/sys/socket.h,v 1.60 2002/04/20 02:24:35 mike Exp $
 */

#ifndef _SYS_SOCKET_H_
#define _SYS_SOCKET_H_

#include <sys/_types.h>
#include <stdint.h>
#include <sys/types.h>

/* Needed by linuxthreads. */

# define __SOCKADDR_ARG     struct sockaddr *__restrict
# define __CONST_SOCKADDR_ARG   __const struct sockaddr *

/*
 * Definitions related to sockets: types, address families, options.
 */

/*
 * Data types.
 */
typedef unsigned short  sa_family_t;
typedef unsigned long   socklen_t;  /**<@if Chinese 地址结构长度 @else Address Structure length @endif*/
typedef int             pid_t;
typedef unsigned short             uid_t;
typedef unsigned short             gid_t;
typedef unsigned short  u_short;
typedef char           *caddr_t;
typedef unsigned short  in_port_t;
typedef uint32_t  u32_t;
typedef uint8_t   u8_t;


/*
 * Types
 */
#define SOCK_STREAM 1       	/**<@if Chinese STREAM套接字 	@else stream socket 			@endif*/
#define SOCK_DGRAM  2       	/**<@if Chinese DGRAM套接字 	@else datagram socket 			@endif*/
#define SOCK_RAW    3       	/**<@if Chinese RAW套接字 		@else raw-protocol interface 	@endif*/
#define SOCK_RDM    4       	/**<@if Chinese RDM套接字 		@else reliably-delivered message @endif*/
#define SOCK_SEQPACKET  5       /**<@if Chinese SEQPACKET套接字 @else sequenced packet stream 	@endif*/

/**
@if Chinese
 *@brief 选择套接字标志.
@else 
 *@brief Option flags per-socket.
@endif
 */
#define SO_DEBUG        0x0001      /**<@if Chinese 打开调试信息记录 		@else turn on debugging info recording 	@endif*/
#define SO_ACCEPTCONN   0x0002      /**<@if Chinese Socket已经有了listen() @else socket has had listen() 			@endif*/
#define SO_REUSEADDR    0x0004      /**<@if Chinese 允许本地地址重用 		@else allow local address reuse 		@endif*/
#define SO_KEEPALIVE    0x0008      /**<@if Chinese 保持连接 				@else keep connections alive 			@endif*/
#define SO_DONTROUTE    0x0010      /**<@if Chinese 只用接口地址 			@else just use interface addresses 		@endif*/
#define SO_BROADCAST    0x0020      /**<@if Chinese 允许发送广播式MSGS 		@else permit sending of broadcast msgs 	@endif*/
#define SO_USELOOPBACK  0x0040      /**<@if Chinese 尽可能绕过硬件 			@else bypass hardware when possible 	@endif*/
#define SO_LINGER       0x0080      /**<@if Chinese 如果数据存在，则停留在关闭状态 @else linger on close if data present @endif*/
#define SO_OOBINLINE    0x0100      /**<@if Chinese 将接收到的OOB数据整理好 @else leave received OOB data in line 	@endif*/
#define SO_REUSEPORT    0x0200      /**<@if Chinese 允许本地地址和端口重用 	@else allow local address & port reuse 	@endif*/
#define SO_TIMESTAMP    0x0400      /**<@if Chinese 接收到dgram流量的时间戳 @else timestamp received dgram traffic 	@endif*/
#define SO_ACCEPTFILTER 0x1000      /**<@if Chinese 有一个接受过滤器 		@else there is an accept filter 		@endif*/

/**
@if Chinese
 *@brief Socket 动作类型.
@else 
 *@brief Additional options, not kept in so_options.
@endif 
 */
#define SO_SNDBUF   0x1001      /**<@if Chinese socket 发送字符标志 @else send buffer size 		@endif*/
#define SO_RCVBUF   0x1002      /**<@if Chinese socket 接收字符标志 @else receive buffer size 	@endif*/
#define SO_SNDLOWAT 0x1003      /**<@if Chinese 发送最低点 			@else send low-water mark 	@endif*/
#define SO_RCVLOWAT 0x1004      /**<@if Chinese 接收到最低点 		@else receive low-water mark @endif*/
#define SO_SNDTIMEO 0x1005      /**<@if Chinese 发送超时 			@else send timeout 			@endif*/
#define SO_RCVTIMEO 0x1006      /**<@if Chinese 接收超时 			@else receive timeout 		@endif*/
#define SO_ERROR    0x1007      /**<@if Chinese 获取错误状态并清除 	@else get error status and clear @endif*/
#define SO_TYPE     0x1008      /**<@if Chinese 获取套接字类型 		@else get socket type 		@endif*/
#define SO_CNTTIMEO 0x1009
/*efine SO_PRIVSTATE    0x1009         get/deny privileged state */

/**
@if Chinese
 *@brief  用于操作延迟选项的结构
@else 
 *@brief  Structure used for manipulating linger option.
@endif 
 */
struct linger {
    int l_onoff;        /**<@if Chinese 选择开/关  	@else option on/off @endif*/
    int l_linger;       /**<@if Chinese 停留时间  	@else linger time 	@endif*/
};

struct accept_filter_arg {
    char    af_name[16];
    char    af_arg[256 - 16];
};

struct hostent {
    char *h_name; /* official name of host */
    char **h_aliases; /* alias list */
    int h_addrtype; /* host address type */
    int h_length; /* length of address */
    char **h_addr_list; /* list of addresses from name server */
#define h_addr h_addr_list[0]
};

/*
 * Level number for (get/set)sockopt() to apply to socket itself.
 */
#define SOL_SOCKET  0xffff      /* options for socket level */

/* Protocol families.  */
#define PF_UNSPEC   0   /* Unspecified.  */
#define PF_LOCAL    1   /* Local to host (pipes and file-domain).  */
#define PF_UNIX     PF_LOCAL /* Old BSD name for PF_LOCAL.  */
#define PF_FILE     PF_LOCAL /* Another non-standard name for PF_LOCAL.  */
#define PF_INET     2   /* IP protocol family.  */
#define PF_AX25     3   /* Amateur Radio AX.25.  */
#define PF_IPX      4   /* Novell Internet Protocol.  */
#define PF_APPLETALK    5   /* Appletalk DDP.  */
#define PF_NETROM   6   /* Amateur radio NetROM.  */
#define PF_BRIDGE   7   /* Multiprotocol bridge.  */
#define PF_ATMPVC   8   /* ATM PVCs.  */
#define PF_X25      9   /* Reserved for X.25 project.  */
#define PF_INET6    10  /* IP version 6.  */
#define PF_ROSE     11  /* Amateur Radio X.25 PLP.  */
#define PF_DECnet   12  /* Reserved for DECnet project.  */
#define PF_NETBEUI  13  /* Reserved for 802.2LLC project.  */
#define PF_SECURITY 14  /* Security callback pseudo AF.  */
#define PF_KEY      15  /* PF_KEY key management API.  */
#define PF_NETLINK  16
#define PF_ROUTE    PF_NETLINK /* Alias to emulate 4.4BSD.  */
#define PF_PACKET   17  /* Packet family.  */
#define PF_ASH      18  /* Ash.  */
#define PF_ECONET   19  /* Acorn Econet.  */
#define PF_ATMSVC   20  /* ATM SVCs.  */
#define PF_SNA      22  /* Linux SNA Project */
#define PF_IRDA     23  /* IRDA sockets.  */
#define PF_PPPOX    24  /* PPPoX sockets.  */
#define PF_WANPIPE  25  /* Wanpipe API sockets.  */
#define PF_BLUETOOTH    31  /* Bluetooth sockets.  */
#define PF_MAX      32  /* For now..  */

/* Address families.  */
#define AF_UNSPEC   PF_UNSPEC
#define AF_LOCAL    PF_LOCAL
#define AF_UNIX     PF_UNIX
#define AF_FILE     PF_FILE
#define AF_INET     PF_INET
#define AF_AX25     PF_AX25
#define AF_IPX      PF_IPX
#define AF_APPLETALK    PF_APPLETALK
#define AF_NETROM   PF_NETROM
#define AF_BRIDGE   PF_BRIDGE
#define AF_ATMPVC   PF_ATMPVC
#define AF_X25      PF_X25
#define AF_INET6    PF_INET6
#define AF_ROSE     PF_ROSE
#define AF_DECnet   PF_DECnet
#define AF_NETBEUI  PF_NETBEUI
#define AF_SECURITY PF_SECURITY
#define AF_KEY      PF_KEY
#define AF_NETLINK  PF_NETLINK
#define AF_ROUTE    PF_ROUTE
#define AF_PACKET   PF_PACKET
#define AF_ASH      PF_ASH
#define AF_ECONET   PF_ECONET
#define AF_ATMSVC   PF_ATMSVC
#define AF_SNA      PF_SNA
#define AF_IRDA     PF_IRDA
#define AF_PPPOX    PF_PPPOX
#define AF_WANPIPE  PF_WANPIPE
#define AF_BLUETOOTH    PF_BLUETOOTH
#define AF_MAX      PF_MAX

/**
@if Chinese
 * @brief 网络通信地址结构
@else 
 * @brief Network communication address structure
@endif 
 */
struct sockaddr {
    sa_family_t sa_family;      /**<@if Chinese 地址族               @else Address 					@endif*/
    char        sa_data[14];    /**<@if Chinese 14字节协议地址       @else 14-byte protocol address @endif*/
};
#define SOCK_MAXADDRLEN 255     /* longest possible addresses */

#ifndef _IN_ADDR_T_DECLARED
typedef uint32_t    in_addr_t;
#define _IN_ADDR_T_DECLARED
#endif

#ifndef _IN_PORT_T_DECLARED
typedef uint16_t    in_port_t;
#define _IN_PORT_T_DECLARED
#endif

struct in6_addr {
  union {
    u32_t u32_addr[4];
    u8_t  u8_addr[16];
  } un;
#define s6_addr  un.u8_addr
};


#ifndef _STRUCT_IN_ADDR_DECLARED
struct in_addr {
    in_addr_t s_addr;
};
#define _STRUCT_IN_ADDR_DECLARED
#endif

#ifndef _STRUCT_IN_ADDR_DECLARED
struct in_addr {
    in_addr_t s_addr;
};
#define _STRUCT_IN_ADDR_DECLARED
#endif


#ifndef _STRUCT_SOCKADDR_IN_DECLARED
/**
 @if Chinese
 * @brief 网络通信地址结构
@else 
 * @brief Network communication address structure
@endif 
 */
struct sockaddr_in {
    sa_family_t sin_family;     /**<@if Chinese 地址族               @else Address family 	@endif*/
    in_port_t sin_port;         /**<@if Chinese 端口号               @else port number 		@endif*/
    struct in_addr sin_addr;    /**<@if Chinese IP地址               @else IP addresses 	@endif*/
    char sin_zero[8];           /**<@if Chinese 填充0以保持与sockaddr结构同样大小 @else Padding 0 to keep the same size as the sockADDR structure @endif*/
};

struct sockaddr_in6 {
  sa_family_t     sin6_family;   /* AF_INET6                    */
  in_port_t       sin6_port;     /* Transport layer port #      */
  u32_t           sin6_flowinfo; /* IPv6 flow information       */
  struct in6_addr sin6_addr;     /* IPv6 address                */
  u32_t           sin6_scope_id; /* Set of interfaces for scope */
};


#define _STRUCT_SOCKADDR_IN_DECLARED
#endif

struct addrinfo {
    int               ai_flags;      /* Input flags. */
    int               ai_family;     /* Address family of socket. */
    int               ai_socktype;   /* Socket type. */
    int               ai_protocol;   /* Protocol of socket. */
    socklen_t         ai_addrlen;    /* Length of socket address. */
    struct sockaddr  *ai_addr;       /* Socket address of socket. */
    char             *ai_canonname;  /* Canonical name of service location. */
    struct addrinfo  *ai_next;       /* Pointer to next in list. */
};


/*
 * Structure used by kernel to pass protocol
 * information in raw sockets.
 */
struct sockproto {
    u_short sp_family;      /* address family */
    u_short sp_protocol;        /* protocol */
};

/*
 * RFC 2553: protocol-independent placeholder for socket addresses
 */
#define _SS_MAXSIZE 128U
#define _SS_ALIGNSIZE   (sizeof(int64_t))
#define _SS_PAD1SIZE    (_SS_ALIGNSIZE - sizeof(unsigned char) - sizeof(sa_family_t))
#define _SS_PAD2SIZE    (_SS_MAXSIZE - sizeof(unsigned char) - sizeof(sa_family_t) - \
                _SS_PAD1SIZE - _SS_ALIGNSIZE)

struct sockaddr_storage {
    unsigned char       ss_len;     /* address length */
    sa_family_t ss_family;  /* address family */
    char        __ss_pad1[_SS_PAD1SIZE];
    int64_t     __ss_align; /* force desired structure storage alignment */
    char        __ss_pad2[_SS_PAD2SIZE];
};

/*
 * Definitions for network related sysctl, CTL_NET.
 *
 * Second level is protocol family.
 * Third level is protocol number.
 *
 * Further levels are defined by the individual families below.
 */
#define NET_MAXID   AF_MAX

#define CTL_NET_NAMES { \
    { 0, 0 }, \
    { "unix", CTLTYPE_NODE }, \
    { "inet", CTLTYPE_NODE }, \
    { "implink", CTLTYPE_NODE }, \
    { "pup", CTLTYPE_NODE }, \
    { "chaos", CTLTYPE_NODE }, \
    { "xerox_ns", CTLTYPE_NODE }, \
    { "iso", CTLTYPE_NODE }, \
    { "emca", CTLTYPE_NODE }, \
    { "datakit", CTLTYPE_NODE }, \
    { "ccitt", CTLTYPE_NODE }, \
    { "ibm_sna", CTLTYPE_NODE }, \
    { "decnet", CTLTYPE_NODE }, \
    { "dec_dli", CTLTYPE_NODE }, \
    { "lat", CTLTYPE_NODE }, \
    { "hylink", CTLTYPE_NODE }, \
    { "appletalk", CTLTYPE_NODE }, \
    { "route", CTLTYPE_NODE }, \
    { "link_layer", CTLTYPE_NODE }, \
    { "xtp", CTLTYPE_NODE }, \
    { "coip", CTLTYPE_NODE }, \
    { "cnt", CTLTYPE_NODE }, \
    { "rtip", CTLTYPE_NODE }, \
    { "ipx", CTLTYPE_NODE }, \
    { "sip", CTLTYPE_NODE }, \
    { "pip", CTLTYPE_NODE }, \
    { "isdn", CTLTYPE_NODE }, \
    { "key", CTLTYPE_NODE }, \
    { "inet6", CTLTYPE_NODE }, \
    { "natm", CTLTYPE_NODE }, \
    { "atm", CTLTYPE_NODE }, \
    { "hdrcomplete", CTLTYPE_NODE }, \
    { "netgraph", CTLTYPE_NODE }, \
    { "snp", CTLTYPE_NODE }, \
    { "scp", CTLTYPE_NODE }, \
}

/*
 * PF_ROUTE - Routing table
 *
 * Three additional levels are defined:
 *  Fourth: address family, 0 is wildcard
 *  Fifth: type of info, defined below
 *  Sixth: flag(s) to mask with for NET_RT_FLAGS
 */
#define NET_RT_DUMP 1       /* dump; may limit to a.f. */
#define NET_RT_FLAGS    2       /* by flags, e.g. RESOLVING */
#define NET_RT_IFLIST   3       /* survey interface list */
#define NET_RT_MAXID    4

#define CTL_NET_RT_NAMES { \
    { 0, 0 }, \
    { "dump", CTLTYPE_STRUCT }, \
    { "flags", CTLTYPE_STRUCT }, \
    { "iflist", CTLTYPE_STRUCT }, \
}

/*
 * Maximum queue length specifiable by listen.
 */
#ifndef SOMAXCONN
#define SOMAXCONN   128
#endif

/*
 * Message header for recvmsg and sendmsg calls.
 * Used value-result for recvmsg, value only for sendmsg.
 */
struct msghdr {
    void        *msg_name;      /* optional address */
    socklen_t    msg_namelen;       /* size of address */
    struct iovec    *msg_iov;       /* scatter/gather array */
    int      msg_iovlen;        /* # elements in msg_iov */
    void        *msg_control;       /* ancillary data, see below */
    socklen_t    msg_controllen;    /* ancillary data buffer len */
    int      msg_flags;     /* flags on received message */
};

#define MSG_OOB     0x1     /* process out-of-band data */
#define MSG_PEEK    0x2     /* peek at incoming message */
#define MSG_DONTROUTE   0x4     /* send without using routing tables */
#define MSG_EOR     0x8     /* data completes record */
#define MSG_TRUNC   0x10        /* data discarded before delivery */
#define MSG_CTRUNC  0x20        /* control data lost before delivery */
#define MSG_WAITALL 0x40        /* wait for full request or error */
#define MSG_DONTWAIT    0x80        /* this message should be nonblocking */
#define MSG_EOF     0x100       /* data completes connection */
#define MSG_COMPAT      0x8000      /* used in sendit() */

/*
 * Header for ancillary data objects in msg_control buffer.
 * Used for additional information with/about a datagram
 * not expressible by flags.  The format is a sequence
 * of message elements headed by cmsghdr structures.
 */
struct cmsghdr {
    socklen_t   cmsg_len;       /* data byte count, including hdr */
    int     cmsg_level;     /* originating protocol */
    int     cmsg_type;      /* protocol-specific type */
    /* followed by  unsigned char  cmsg_data[]; */
};

/*
 * While we may have more groups than this, the cmsgcred struct must
 * be able to fit in an mbuf, and NGROUPS_MAX is too large to allow
 * this.
*/
#define CMGROUP_MAX 16

/*
 * Credentials structure, used to verify the identity of a peer
 * process that has sent us a message. This is allocated by the
 * peer process but filled in by the kernel. This prevents the
 * peer from lying about its identity. (Note that cmcred_groups[0]
 * is the effective GID.)
 */
struct cmsgcred {
    pid_t   cmcred_pid;     /* PID of sending process */
    uid_t   cmcred_uid;     /* real UID of sending process */
    uid_t   cmcred_euid;        /* effective UID of sending process */
    gid_t   cmcred_gid;     /* real GID of sending process */
    short   cmcred_ngroups;     /* number or groups */
    gid_t   cmcred_groups[CMGROUP_MAX]; /* groups */
};

/* given pointer to struct cmsghdr, return pointer to data */
#define CMSG_DATA(cmsg)     ((unsigned char *)(cmsg) + \
                 _ALIGN(sizeof(struct cmsghdr)))

/* given pointer to struct cmsghdr, return pointer to next cmsghdr */
#define CMSG_NXTHDR(mhdr, cmsg) \
    (((caddr_t)(cmsg) + _ALIGN((cmsg)->cmsg_len) + \
      _ALIGN(sizeof(struct cmsghdr)) > \
        (caddr_t)(mhdr)->msg_control + (mhdr)->msg_controllen) ? \
        (struct cmsghdr *)NULL : \
        (struct cmsghdr *)((caddr_t)(cmsg) + _ALIGN((cmsg)->cmsg_len)))

#define CMSG_FIRSTHDR(mhdr) ((struct cmsghdr *)(mhdr)->msg_control)

/* RFC 2292 additions */

#define CMSG_SPACE(l)       (_ALIGN(sizeof(struct cmsghdr)) + _ALIGN(l))
#define CMSG_LEN(l)     (_ALIGN(sizeof(struct cmsghdr)) + (l))

#ifdef _KERNEL
#define CMSG_ALIGN(n)   _ALIGN(n)
#endif

/* "Socket"-level control message types: */
#define SCM_RIGHTS  0x01        /* access rights (array of int) */
#define SCM_TIMESTAMP   0x02        /* timestamp (struct timeval) */
#define SCM_CREDS   0x03        /* process creds (struct cmsgcred) */

/*
 * 4.3 compat sockaddr, move to compat file later
 */
struct osockaddr {
    u_short sa_family;      /* address family */
    char    sa_data[14];        /* up to 14 bytes of direct address */
};

/*
 * 4.3-compat message header (move to compat file later).
 */
struct omsghdr {
    caddr_t msg_name;       /* optional address */
    int msg_namelen;        /* size of address */
    struct  iovec *msg_iov;     /* scatter/gather array */
    int msg_iovlen;     /* # elements in msg_iov */
    caddr_t msg_accrights;      /* access rights sent/received */
    int msg_accrightslen;
};

/*
 * howto arguments for shutdown(2), specified by Posix.1g.
 */
#define SHUT_RD     0       /* shut down the reading side */
#define SHUT_WR     1       /* shut down the writing side */
#define SHUT_RDWR   2       /* shut down both sides */

/*
 * sendfile(2) header/trailer struct
 */
struct sf_hdtr {
    struct iovec *headers;  /* pointer to an array of header struct iovec's */
    int hdr_cnt;        /* number of header iovec's */
    struct iovec *trailers; /* pointer to an array of trailer struct iovec's */
    int trl_cnt;        /* number of trailer iovec's */
};

//#include <sys/cdefs.h>

//__BEGIN_DECLS
int accept(int, struct sockaddr *, socklen_t *);
int bind(int, const struct sockaddr *, socklen_t);
int connect(int, const struct sockaddr *, socklen_t);
int getpeername(int, struct sockaddr *, socklen_t *);
int getsockname(int, struct sockaddr *, socklen_t *);
int getsockopt(int, int, int, void *, socklen_t *);
int listen(int, int);
ssize_t recv(int, void *, size_t, int);
ssize_t recvfrom(int, void *, size_t, int, struct sockaddr *, socklen_t *);
ssize_t recvmsg(int, struct msghdr *, int);
ssize_t send(int, const void *, size_t, int);
ssize_t sendto(int, const void *,
               size_t, int, const struct sockaddr *, socklen_t);
ssize_t sendmsg(int, const struct msghdr *, int);
int sendfile(int, int, off_t, size_t, struct sf_hdtr *, off_t *, int);
int setsockopt(int, int, int, const void *, socklen_t);
int shutdown(int, int);
int socket(int, int, int);
int socketpair(int, int, int, int *);
struct hostent *gethostbyname_safe(const char *name, void *host_buf, int len);
//int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

/**
@if Chinese
 * @brief			将指定的文件描述符集合清空
 * @param[in]		set     -	文件描述符集合
 * @retval			none
@else 
 * @brief			Clears the specified set of file descriptors
 * @param[in]		set     -	Collection of file descriptors
 * @retval			none
@endif 
*/
void net_FD_ZERO(void *set);

/**
@if Chinese
 * @brief			在文件描述符集合中增加一个新的文件描述符
 * @param[in]		fd		-	文件描述符
 * @param[in]		set		-	文件描述符集合
 * @retval			none
@else 
 * @brief			Adds a new file descriptor to the file descriptor collection
 * @param[in]		fd		-	file descriptor
 * @param[in]		set		-	Collection of file descriptors
 * @retval			none
@endif 
*/
void net_FD_SET(int fd, void *set);

/**
@if Chinese
 * @brief			测试指定的文件描述符是否在该集合中
 * @param[in]		fd		-	文件描述符
 * @param[in]		set		-	文件描述符集合
 * @retval			1       -	文件描述符在该集合中
 * @retval			0       -	文件描述符不在该集合中
@else 
 * @brief			Tests whether the specified file descriptor is in the collection
 * @param[in]		fd		-	file descriptor
 * @param[in]		set		-	Collection of file descriptors
 * @retval			1       -	The file descriptor is in the collection
 * @retval			0       -	The file descriptor is not in the collection
@endif 
*/
int net_FD_ISSET(int fd, void *set);

/**
@if Chinese
 * @brief			在文件描述符集合中删除一个文件描述符
 * @param[in]		fd		-	文件描述符
 * @param[in]		set		-	文件描述符集合
@else 
 * @brief			Removes a file descriptor from the file descriptor collection
 * @param[in]		fd		file descriptor
 * @param[in]		set		Collection of file descriptors
@endif 
*/
void net_FD_CLR(int fd, void *set);

/**
@if Chinese
 * @brief			用来统一监视多个文件描述符
 * @param[in]		nfds        -	集合中所有文件描述符的范围，即所有文件描述符的最大值加1
 * @param[in]		readfds     -	用来检查可读性的一组文件描述符集合
 * @param[in]		writefds    -	用来检查可写性的一组文件描述符集合
 * @param[in]		exceptfds   -	用来检查是否有异常条件出现的文件描述符集合
 * @param[in]		timeout     -	超时时间
 * @retval			>0          -	被监视的文件描述符有变化
 * @retval          -1          -	发生错误
 * @retval          =0          -	超时
 * @note
 * 		            输入参数readfds、writefds、exceptfds数据结构如下:
 *		            @code
 *			            typedef struct sci_fd_set {
 *				            unsigned        fd_count;
 *				            long            fd_array[12];
 *			            } sci_fd_set;
 *		            @endcode 
@else 
 * @brief			Used to monitor multiple file descriptors uniformly
 * @param[in]		nfds        -	The range of all file descriptors in the collection, i.e., the maximum value of all file descriptors plus 1
 * @param[in]		readfds     -	A collection of file descriptors used to check readability
 * @param[in]		writefds    -	A collection of file descriptors used to check writability
 * @param[in]		exceptfds   -	A collection of file descriptors used to check for exception condition occurrences
 * @param[in]		timeout     -	time-out period
 * @retval			>0         	-	The monitored file descriptor has changed
 * @retval          -1          -	go wrong
 * @retval          =0          -	Timeout
 * @note
 * 		            Input the param readfds、writefds、exceptfds, the data structure is as follows:
 *		            @code
 *			            typedef struct sci_fd_set {
 *				            unsigned        fd_count;
 *				            long            fd_array[12];
 *			            } sci_fd_set;
 *		            @endcode   
@endif 
*/
int net_select(int nfds, void *readfds, void *writefds, void *exceptfds, struct timeval *timeout);

/**
@if Chinese
 * @brief			创建一个套接字，同时指定协议和类型
 * @param[in]		domain	    -	协议族
 * @param[in]		type 	    -	套接字的类型
 * @param[in]		protocol    -	指定传输协议
 * @retval			>=0         -	成功，返回非负套接字描述符
 * @retval          -1          -	失败，请通过errno获取具体的错误码
 * @note
 *					[1] 协议族有AF_INET、AF_INET6、AF_LOCAL、AF_ROUTE等等<br>
 *					[2] 套接字的类型有SOCK_STREAM、SOCK_DGRAM、SOCK_SEQPACKET、SOCK_RAW等等<br>
 *					[3] 传输协议常用的有IPPROTO_TCP、IPPTOTO_UDP，通常设置为0使用默认的值<br>
 *                  目前套接字支持wifi和无线网络，使用前可以先切换网络
@else 
 * @brief			Creates a socket, specifying the protocol and type
 * @param[in]		domain	    -	protocol family
 * @param[in]		type 	    -	The type of the socket
 * @param[in]		protocol    -	The type of the socket
 * @retval			>=0         -	Success, returns a non-negative socket descriptor
 * @retval          -1          -	Failed. Obtain the error code from errno
 * @note
 *					[1] protocol family have AF_INET、AF_INET6、AF_LOCAL、AF_ROUTE and so on<br>
 *					[2] Socket have SOCK_STREAM、SOCK_DGRAM、SOCK_SEQPACKET、SOCK_RAW and so on<br>
 *					[3] The common transport protocols are IPPROTO_TCP and IPPTOTO_UDP. The default value is 0<br>
 *                  Currently the socket supports wifi and wireless network, you can switch network before using
@endif 
*/
int net_socket(int domain, int type, int protocol);

/**
@if Chinese
 * @brief			客户端向服务器端的监听套接字发送连接请求
 * @param[in]		fd		    -	套接字描述符
 * @param[in]		addr 	    -	服务器端地址
 * @param[in]		addrlen     -	地址长度
 * @retval          =0          -	成功
 * @retval          -1          -	失败，请通过errno获取具体的错误码
@else 
 * @brief			The client sends a connection request to the listening socket on the server side
 * @param[in]		fd		    -	Socket descriptor
 * @param[in]		addr 	    -	Server address
 * @param[in]		addrlen     -	address length
 * @retval          =0          -	Success
 * @retval          -1          -	Failed. Obtain the error code from errno
@endif 
*/
int net_connect(int fd, const struct sockaddr *addr, socklen_t addrlen);

/**
@if Chinese
 * @brief			接收数据，一般用在TCP通信中
 * @param[in]		fd		    -	套接字描述符
 * @param[out]		buf 	    -	接收数据缓冲区
 * @param[in]		len 	    -	接收数据长度
 * @param[in]		flags 	    -	一般设置为0
 * @retval			>0          -	成功，返回实际收到的字节数
 * @retval			=0          -	连接关闭
 * @retval          -1          -	失败，请通过errno获取具体的错误码
@else 
 * @brief			To receive data, generally used in TCP communication
 * @param[in]		fd		    -	Socket descriptor
 * @param[out]		buf 	    -	Receive data
 * @param[in]		len 	    -	Receive data length
 * @param[in]		flags 	    -	default 0
 * @retval			>0          -	Success returns the actual number of bytes received
 * @retval			=0          -	Connect close
 * @retval          -1          -	Failed. Obtain the error code from errno
@endif 
*/
ssize_t net_recv(int fd, void *buf, size_t len, int flags);

/**
@if Chinese
 * @brief			发送数据，一般用在TCP通信中
 * @param[in]		fd		    -	套接字描述符
 * @param[in]		buf 	    -	发送缓冲区地址
 * @param[in]		len 	    -	发送数据的长度
 * @param[in]		flags 	    -	一般设置为0
 * @retval			>0          -	成功,返回实际发送的字节数
 * @retval			=0          -	连接关闭
 * @retval          -1          -	失败，请通过errno获取具体的错误码
@else 
 * @brief			To send data, usually used in TCP communication
 * @param[in]		fd		    -	Socket descriptor
 * @param[in]		buf 	    -	Send buf
 * @param[in]		len 	    -	Send buf length
 * @param[in]		flags 	    -	default 0
 * @retval			>0          -	Success returns the actual number of bytes received
 * @retval			=0          -	Connect close
 * @retval          -1          -	Failed. Obtain the error code from errno
@endif 
*/
ssize_t net_send(int fd, const void *buf, size_t len, int flags);

/**
@if Chinese
 * @brief			接收数据，一般用在UDP通信中
 * @param[in]		fd		    -	套接字描述符
 * @param[out]		buf 	    -	接收数据缓冲区
 * @param[in]		len 	    -	接收数据长度
 * @param[in]		flags 	    -	一般设置为0
 * @param[in]		src_addr 	-	发送方的IP地址和端口号信息
 * @param[in]		addrlen 	-	地址长度
 * @retval			>0          -	成功，返回实际收到的字节数
 * @retval			=0          -	连接关闭
 * @retval          -1          -	失败，请通过errno获取具体的错误码
@else 
 * @brief			To receive data, generally used in UDP communication
 * @param[in]		fd		    -	Socket descriptor
 * @param[out]		buf 	    -	Send buf
 * @param[in]		len 	    -	Send buf length
 * @param[in]		flags 	    -	default 0
 * @param[in]		src_addr 	-	IP address and port number of the sender
 * @param[in]		addrlen 	-	address length
 * @retval			>0          -	Success returns the actual number of bytes received
 * @retval			=0          -	Connect close
 * @retval          -1          -	Failed. Obtain the error code from errno
@endif 
*/
ssize_t net_recvfrom(int fd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);

/**
@if Chinese
 * @brief			发送数据，一般用在UDP通信中
 * @param[in]		fd		    -	套接字描述符
 * @param[in]		buf 	    -	发送缓冲区地址
 * @param[in]		len 	    -	发送数据的长度
 * @param[in]		flags       -	一般设置为0
 * @param[in]		dest_addr   -	接收方套接字的IP地址和端口号
 * @param[in]		addrlen 	    -	地址长度
 * @retval			>0          -	成功,返回实际发送的字节数
 * @retval			=0          -	连接关闭
 * @retval          -1          -	失败，请通过errno获取具体的错误码
@else 
 * @brief			Send data, commonly used in UDP communication
 * @param[in]		fd		    -	Socket descriptor
 * @param[in]		buf 	    -	Send buf
 * @param[in]		len 	    -	Send buf length
 * @param[in]		flags       -	default 0
 * @param[in]		dest_addr   -	The IP address and port number of the receiver socket
 * @param[in]		addrlen 	    -	address length
 * @retval			>0          -	Success returns the number of bytes actually sent
 * @retval			=0          -	Connect closed
 * @retval          -1          -	Failed. Obtain the error code from errno
@endif
 */
ssize_t net_sendto(int fd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);

/**
@if Chinese
 * @brief			获取与某个套接字关联的选项
 * @param[in]		sockfd		-	套接字描述符
 * @param[in]		level 		-	选项所属协议层
 * @param[in]		optname		-	套接字选项名
 * @param[out]		optval		-	保存选项值的缓冲区
 * @param[in]		optlen 		-	选项值的长度
 * @retval			=0          -	成功
 * @retval          -1          -	失败，请通过errno获取具体的错误码
@else 
 * @brief			Gets the options associated with a socket
 * @param[in]		sockfd		-	Socket descriptor
 * @param[in]		level 		-	The protocol layer to which the option belongs
 * @param[in]		optname		-	Socket option name
 * @param[out]		optval		-	Buffer to hold option values
 * @param[in]		optlen 		-	The length of the option value
 * @retval			=0          -	Success
 * @retval          -1          -	Failed. Obtain the error code from errno
@endif 
*/
int net_getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen);

/**
@if Chinese
 * @brief			设置与某个套接字关联的选项
 * @param[in]		sockfd		-	套接字描述符
 * @param[in]		level 		-	选项所属协议层
 * @param[in]		optname		-	套接字选项名
 * @param[out]		optval		-	设置选项值的缓冲区
 * @param[in]		optlen 		-	选项值的长度
 * @retval			=0          -	成功
 * @retval          -1          -	失败，请通过errno获取具体的错误码
@else 
 * @brief			Sets the options associated with a socket
 * @param[in]		sockfd		-	Socket descriptor
 * @param[in]		level 		-	The protocol layer to which the option belongs
 * @param[in]		optname		-	Socket option name
 * @param[out]		optval		-	Buffer for setting option values
 * @param[in]		optlen 		-	The length of the option value
 * @retval			=0          -	Success
 * @retval          -1          -	Failed. Obtain the error code from errno
@endif 
*/
int net_setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);

/**
@if Chinese
 * @brief			获取与某个套接字关联的外地协议地址
 * @param[in]		fd		    -	套接字描述符
 * @param[out]		addr 		-	保存地址的缓冲区
 * @param[out]		addrlen		-	地址长度
 * @retval			=0          -	成功
 * @retval          -1          -	失败，请通过errno获取具体的错误码
@else 
 * @brief			Gets the foreign protocol address associated with a socket
 * @param[in]		fd		    -	Socket descriptor
 * @param[out]		addr 		-	Buffer to hold addresses
 * @param[out]		addrlen		-	addresses length
 * @retval			=0          -	Success
 * @retval          -1          -	Failed. Obtain the error code from errno
@endif 
*/
int net_getpeername(int fd, struct sockaddr *addr, socklen_t *addrlen);

/**
@if Chinese
 * @brief			获取与某个套接字关联的本地协议地址
 * @param[in]		fd			-	套接字描述符
 * @param[out]		addr 		-	保存地址的缓冲区
 * @param[out]		addrlen		-	地址长度
 * @retval			=0          -	成功
 * @retval          -1          -	失败，请通过errno获取具体的错误码
@else 
 * @brief			Gets the local protocol address associated with a socket
 * @param[in]		fd			-	Socket descriptor
 * @param[out]		addr 		-	Buffer to hold addresses
 * @param[out]		addrlen		-	Addresses length
 * @retval			=0          -	Success
 * @retval          -1          -	Failed. Obtain the error code from errno
@endif 
*/
int net_getsockname(int fd, struct sockaddr *addr, socklen_t *addrlen);

/**
@if Chinese
 * @brief			将保存在相应地址结构中的地址信息与套接字进行绑定
 * @param[in]		sockfd		-	套接字描述符
 * @param[in]		addr 	    -	绑定的地址
 * @param[in]		addrlen     -	地址长度
 * @retval			=0          -	成功
 * @retval          -1          -	失败，请通过errno获取具体的错误码
 * @note            未实现该接口，总是返回-1
@else 
 * @brief			Binds the address information stored in the corresponding address structure to the socket
 * @param[in]		sockfd		-	Socket descriptor
 * @param[in]		addr 	    -	Bound address
 * @param[in]		addrlen     -	Address length
 * @retval			=0          -	Success
 * @retval          -1         	-	address
 * @note            If this interface is not implemented, -1 is always returned
@endif 
*/
int net_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

/**
@if Chinese
 * @brief			在一个套接字上监听连接
 * @param[in]		sockfd		-	套接字描述符
 * @param[out]		backlog     -   队列中最大接收连接数量
 * @retval			=0          -	成功
 * @retval          -1          -	失败，请通过errno获取具体的错误码
 * @note            未实现该接口，总是返回-1
@else 
 * @brief			listen for connections on a socket
 * @param[in]		sockfd		-	Socket descriptor
 * @param[int]		backlog     -	the maximum length to which the queue of pending connections for sockfd may grow
 * @retval			=0          -	Success
 * @retval          -1         	-	address
 * @note            If this interface is not implemented, -1 is always returned
@endif 
*/
int net_listen(int sockfd, int backlog);

/**
@if Chinese
 * @brief			在套接字上接受一个连接
 * @param[in]		sockfd		-	套接字描述符
 * @param[out]		addr 	    -   sockaddr地址指针
 * @param[out]		addrlen     -	地址长度
 * @retval			=0          -	成功
 * @retval          -1          -	失败，请通过errno获取具体的错误码
 * @note            未实现该接口，总是返回-1
@else 
 * @brief			accept a connection on a socket
 * @param[in]		sockfd		-	Socket descriptor
 * @param[out]		addr 	    -	is a pointer to a sockaddr structure
 * @param[out]		addrlen     -	on return it will contain the actual size of the peer
       address
 * @retval			=0          -	Success
 * @retval          -1         	-	address
 * @note            If this interface is not implemented, -1 is always returned
@endif 
*/
int net_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

/**
@if Chinese
 * @brief			获取主机名IP地址
 * @param[in]		nodename		-	主机名
 * @param[in]		servname 	    -   端口名
 * @param[in]		hints 	        -   获取
 * @param[out]		res             -	返回的结果
 * @retval			=0              -	成功
 * @retval          -1              -	失败，请通过errno获取具体的错误码
 * @note            未实现该接口，总是返回-1
@else 
 * @brief			get host address info
 * @param[in]		nodename		-	host name
 * @param[in]		servname 	    -   port name
 * @param[in]		hints 	        -   hints
 * @param[out]		res             -	result
 * @retval			=0              -	Success
 * @retval          -1         	    -	address
 * @note            If this interface is not implemented, -1 is always returned
@endif 
*/
int net_getaddrinfo(const char *nodename, const char *servname,const struct addrinfo *hints, struct addrinfo **res);

//__END_DECLS

#define NetSocket(family, type, protocol) socket(family, type, protocol)
#define  NetAccept(sockfd, cliaddr, addrlen) accept(sockfd, cliaddr, addrlen)
#define  NetBind(sockfd, myaddr, addrlen) bind(sockfd, myaddr, addrlen)
#define  NetConnect(sockfd, servaddr, addrlen) connect(sockfd, servaddr, addrlen)
#define  NetSend(sockfd, buff,  nbytes, flags) send(sockfd, buff,  nbytes, flags)
#define  NetSendto(sockfd, buff, nbytes, flags, to, addrlen) sendto(sockfd, buff, nbytes, flags, to, addrlen)
#define  NetRecv(sockfd, buff, nbytes, flags) recv (sockfd, buff, nbytes, flags)
#define  NetRecvfrom(sockfd, buff, nbytes, flags, from, addrlen) recvfrom(sockfd, buff, nbytes, flags, from, addrlen)
#define  NetClose(sockfd) close(sockfd)
#define  NetGetsockopt(sockfd, level, optname, optval, optlen) getsockopt(sockfd, level, optname, optval, optlen)
#define  NetSetsockopt(sockfd, level, optname, optval, optlen) setsockopt(sockfd, level, optname, optval, optlen)


#endif /* !_SYS_SOCKET_H_ */

/** @} */
