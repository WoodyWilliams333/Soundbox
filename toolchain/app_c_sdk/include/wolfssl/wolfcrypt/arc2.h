/* arc2.h
 *
 * Copyright (C) 2006-2017 wolfSSL Inc.
 *
 * This file is part of wolfSSL.
 *
 * wolfSSL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * wolfSSL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335, USA
 */



#ifndef WOLF_CRYPT_ARC2_H
#define WOLF_CRYPT_ARC2_H

#ifdef ADD_SOME_PBE_ALGO

#include <wolfssl/wolfcrypt/types.h>

#ifdef __cplusplus
    extern "C" {
#endif

#ifdef WOLFSSL_ASYNC_CRYPT
    #include <wolfssl/wolfcrypt/async.h>
#endif

//////////////////////////////////////////////////////////////////////////////

#ifndef RC2_INT
#define RC2_INT unsigned int
#endif

#undef RC2_ENCRYPT_OPR
#define RC2_ENCRYPT_OPR     1

#undef RC2_DECRYPT_OPR
#define RC2_DECRYPT_OPR     0

typedef struct rc2_key_st {
    RC2_INT data[64];
} RC2_KEY;

void RC2_set_key(RC2_KEY *key, int len, const unsigned char *data, int bits);
void RC2_encrypt(unsigned long *d, RC2_KEY *key);
void RC2_decrypt(unsigned long *d, RC2_KEY *key);
void RC2_cbc_encrypt(const unsigned char *in, unsigned char *out, long length,
                     RC2_KEY *ks, unsigned char *iv, int encrypt);

#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif

#endif /* WOLF_CRYPT_ARC2_H */


