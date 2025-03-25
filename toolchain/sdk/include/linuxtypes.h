#ifndef _LINUX_TYPES_H_
#define _LINUX_TYPES_H_

#include <stdint.h>

#include <stddef.h>

#ifndef OK
#define OK  ( 0 )
#endif
//#define NULL   ( 0 )

#ifndef off_t
typedef signed long     off_t;
#endif

#ifndef loff_t
typedef signed long     loff_t;
#endif

#ifndef ulong
typedef unsigned long   ulong;
#endif

/* bsd */
typedef unsigned char       u_char;
typedef unsigned short      u_short;
typedef unsigned int        u_int;
typedef unsigned long       u_long;

/* sysv */
typedef unsigned char       unchar;
typedef unsigned char       uchar;
typedef unsigned short      ushort;
typedef unsigned int        uint;
typedef unsigned long       ulong;

typedef signed int          ssize_t;
typedef unsigned short      wchar;

/* fatfs integer type */

/* This type MUST be 8 bit */
typedef unsigned char   BYTE;

/* These types MUST be 16 bit */
typedef short           SHORT;
typedef unsigned short  WORD;
typedef unsigned short  WCHAR;

/* These types MUST be 16 bit or 32 bit */
typedef int             INT;
typedef unsigned int    UINT;

/* These types MUST be 32 bit */
typedef long            LONG;
typedef unsigned long   DWORD;

typedef int             INT32;
typedef short       INT16;
typedef signed char     INT8;
typedef unsigned char   UINT8;
typedef unsigned short  UINT16;
typedef unsigned int    UINT32;
typedef unsigned long   ULONG;

#endif

