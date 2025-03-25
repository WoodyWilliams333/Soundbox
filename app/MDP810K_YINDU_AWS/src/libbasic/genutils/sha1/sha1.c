
#ifdef TMS_HAVE_CONFIG_H
#include "c2_tms_cfg.h"
#endif

#include <string.h>
#include "sha1.h" 


#define GET_DWORD(n,b,i) \
{\
(n) = ((unsigned long)(b)[(i) ] << 24 ) |\
 ((unsigned long) (b)[(i) + 1] << 16 ) | \
 ((unsigned long) (b)[(i) + 2] << 8 ) |\
 ((unsigned long) (b)[(i) + 3] ); \
}

#define PUT_DWORD(n,b,i) \
{ \
(b)[(i) ] = (unsigned char) ( (n) >> 24 ); \
(b)[(i) + 1] = (unsigned char) ( (n) >> 16 ); \
(b)[(i) + 2] = (unsigned char) ( (n) >> 8 ); \
(b)[(i) + 3] = (unsigned char) ( (n) ); \
} 





static void sha1_process( LP_SHA1_CONTEXT ctx, unsigned char data[64] ) 
{ 
    unsigned long temp, W[16], A, B, C, D, E; 
    
    GET_DWORD( W[0], data, 0 ); 
    GET_DWORD( W[1], data, 4 ); 
    GET_DWORD( W[2], data, 8 ); 
    GET_DWORD( W[3], data, 12 ); 
    GET_DWORD( W[4], data, 16 ); 
    GET_DWORD( W[5], data, 20 ); 
    GET_DWORD( W[6], data, 24 ); 
    GET_DWORD( W[7], data, 28 ); 
    GET_DWORD( W[8], data, 32 ); 
    GET_DWORD( W[9], data, 36 ); 
    GET_DWORD( W[10], data, 40 ); 
    GET_DWORD( W[11], data, 44 ); 
    GET_DWORD( W[12], data, 48 ); 
    GET_DWORD( W[13], data, 52 ); 
    GET_DWORD( W[14], data, 56 ); 
    GET_DWORD( W[15], data, 60 ); 

#define S(x,n) ((x << n) | ((x & 0xFFFFFFFF) >> (32 - n))) 
    
#define R(t) \
    (\
        temp = W[(t - 3) & 0x0F] ^ W[(t - 8) & 0x0F] ^ \
        W[(t - 14) & 0x0F] ^ W[ t & 0x0F], \
        ( W[t & 0x0F] = S(temp,1) ) \
    ) 
        
#define P(a,b,c,d,e,x) { \
    e += S(a,5) + F(b,c,d) + K + x; b = S(b,30); \
    } 
    
    A = ctx->State[0]; 
    B = ctx->State[1]; 
    C = ctx->State[2]; 
    D = ctx->State[3]; 
    E = ctx->State[4]; 
    
#define F(x,y,z) (z ^ (x & (y ^ z))) 
#define K 0x5A827999 
    
    P( A, B, C, D, E, W[0] ); 
    P( E, A, B, C, D, W[1] ); 
    P( D, E, A, B, C, W[2] ); 
    P( C, D, E, A, B, W[3] ); 
    P( B, C, D, E, A, W[4] ); 
    P( A, B, C, D, E, W[5] ); 
    P( E, A, B, C, D, W[6] ); 
    P( D, E, A, B, C, W[7] ); 
    P( C, D, E, A, B, W[8] ); 
    P( B, C, D, E, A, W[9] ); 
    P( A, B, C, D, E, W[10] ); 
    P( E, A, B, C, D, W[11] ); 
    P( D, E, A, B, C, W[12] ); 
    P( C, D, E, A, B, W[13] ); 
    P( B, C, D, E, A, W[14] ); 
    P( A, B, C, D, E, W[15] ); 
    P( E, A, B, C, D, R(16) ); 
    P( D, E, A, B, C, R(17) ); 
    P( C, D, E, A, B, R(18) ); 
    P( B, C, D, E, A, R(19) ); 
    
#undef K 
#undef F 
    
#define F(x,y,z) (x ^ y ^ z) 
#define K 0x6ED9EBA1 
    
    P( A, B, C, D, E, R(20) ); 
    P( E, A, B, C, D, R(21) ); 
    P( D, E, A, B, C, R(22) ); 
    P( C, D, E, A, B, R(23) ); 
    P( B, C, D, E, A, R(24) ); 
    P( A, B, C, D, E, R(25) ); 
    P( E, A, B, C, D, R(26) ); 
    P( D, E, A, B, C, R(27) ); 
    P( C, D, E, A, B, R(28) ); 
    P( B, C, D, E, A, R(29) ); 
    P( A, B, C, D, E, R(30) ); 
    P( E, A, B, C, D, R(31) ); 
    P( D, E, A, B, C, R(32) ); 
    P( C, D, E, A, B, R(33) ); 
    P( B, C, D, E, A, R(34) ); 
    P( A, B, C, D, E, R(35) ); 
    P( E, A, B, C, D, R(36) ); 
    P( D, E, A, B, C, R(37) ); 
    P( C, D, E, A, B, R(38) ); 
    P( B, C, D, E, A, R(39) ); 
    
#undef K 
#undef F 
    
#define F(x,y,z) ((x & y) | (z & (x | y))) 
#define K 0x8F1BBCDC 
    
    P( A, B, C, D, E, R(40) ); 
    P( E, A, B, C, D, R(41) ); 
    P( D, E, A, B, C, R(42) ); 
    P( C, D, E, A, B, R(43) ); 
    P( B, C, D, E, A, R(44) ); 
    P( A, B, C, D, E, R(45) ); 
    P( E, A, B, C, D, R(46) ); 
    P( D, E, A, B, C, R(47) ); 
    P( C, D, E, A, B, R(48) ); 
    P( B, C, D, E, A, R(49) ); 
    P( A, B, C, D, E, R(50) ); 
    P( E, A, B, C, D, R(51) ); 
    P( D, E, A, B, C, R(52) ); 
    P( C, D, E, A, B, R(53) ); 
    P( B, C, D, E, A, R(54) ); 
    P( A, B, C, D, E, R(55) ); 
    P( E, A, B, C, D, R(56) ); 
    P( D, E, A, B, C, R(57) ); 
    P( C, D, E, A, B, R(58) ); 
    P( B, C, D, E, A, R(59) ); 
    
#undef K 
#undef F 
    
#define F(x,y,z) (x ^ y ^ z) 
#define K 0xCA62C1D6 
    
    P( A, B, C, D, E, R(60) ); 
    P( E, A, B, C, D, R(61) ); 
    P( D, E, A, B, C, R(62) ); 
    P( C, D, E, A, B, R(63) ); 
    P( B, C, D, E, A, R(64) ); 
    P( A, B, C, D, E, R(65) ); 
    P( E, A, B, C, D, R(66) ); 
    P( D, E, A, B, C, R(67) ); 
    P( C, D, E, A, B, R(68) ); 
    P( B, C, D, E, A, R(69) ); 
    P( A, B, C, D, E, R(70) ); 
    P( E, A, B, C, D, R(71) ); 
    P( D, E, A, B, C, R(72) ); 
    P( C, D, E, A, B, R(73) ); 
    P( B, C, D, E, A, R(74) ); 
    P( A, B, C, D, E, R(75) ); 
    P( E, A, B, C, D, R(76) ); 
    P( D, E, A, B, C, R(77) ); 
    P( C, D, E, A, B, R(78) ); 
    P( B, C, D, E, A, R(79) ); 
    
#undef K 
#undef F 
    
    ctx->State[0] += A; 
    ctx->State[1] += B; 
    ctx->State[2] += C; 
    ctx->State[3] += D; 
    ctx->State[4] += E; 
} 


static unsigned char sha1_padding[64] = 
{ 
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
}; 


void SysSha1Init(LP_SHA1_CONTEXT ctx)
{
    memset(ctx, 0, sizeof(SHA1_CONTEXT));
    ctx->Total[0] = 0; 
    ctx->Total[1] = 0; 
    
    ctx->State[0] = 0x67452301; 
    ctx->State[1] = 0xEFCDAB89; 
    ctx->State[2] = 0x98BADCFE; 
    ctx->State[3] = 0x10325476; 
    ctx->State[4] = 0xC3D2E1F0; 
}
int SysSha1Update(LP_SHA1_CONTEXT ctx , const unsigned char * pData, unsigned long dwLength )
{
    int iRetval = 1;
    if ((dwLength > 0) && (0 == pData))
        iRetval = 0;
    if ((1 == iRetval) && (dwLength > 0))
    {
        unsigned long left, fill; 
        
    
        
        left = ctx->Total[0] & 0x3F; 
        fill = 64 - left; 
        
        ctx->Total[0] += dwLength; 
        ctx->Total[0] &= 0xFFFFFFFF; 
        
        if( ctx->Total[0] < dwLength ) 
            ctx->Total[1]++; 
        
        if( left && dwLength >= fill ) 
        { 
            memcpy( (void *) (ctx->Buffer + left), 
                (void *) pData, fill ); 
            sha1_process( ctx, ctx->Buffer); 
            dwLength -= fill; 
            pData += fill; 
            left = 0; 
        } 
        
        while( dwLength >= 64 ) 
        { 
            sha1_process( ctx, (unsigned char *)pData ); 
            dwLength -= 64; 
            pData += 64; 
        } 
        
        if( dwLength ) 
        { 
            memcpy( (void *) (ctx->Buffer + left), 
                (void *) pData, dwLength ); 
        } 
    }
    return iRetval;
}

int SysSha1Fina(LP_SHA1_CONTEXT ctx  , unsigned char digest[20] )
{
    int iRetval = 1;
    if (0 != ctx)
    {
        unsigned long last, padn; 
        unsigned long high, low; 
        unsigned char msglen[8]; 
        
        high = ( ctx->Total[0] >> 29 ) 
            | ( ctx->Total[1] << 3 ); 
        low = ( ctx->Total[0] << 3 ); 
        
        PUT_DWORD( high, msglen, 0 ); 
        PUT_DWORD( low, msglen, 4 ); 
        
        last = ctx->Total[0] & 0x3F; 
        padn = ( last < 56 ) ? ( 56 - last ) : ( 120 - last ); 
        
        SysSha1Update(ctx, sha1_padding, padn ); 
        SysSha1Update(ctx, msglen, 8 ); 
        
        PUT_DWORD( ctx->State[0], digest, 0 ); 
        PUT_DWORD( ctx->State[1], digest, 4 ); 
        PUT_DWORD( ctx->State[2], digest, 8 ); 
        PUT_DWORD( ctx->State[3], digest, 12 ); 
        PUT_DWORD( ctx->State[4], digest, 16 ); 
    }
    else
    {
        iRetval = 0;
    }
    return iRetval;
}

int SysSha1Calc(const void * pvData, unsigned long ulLength, void * pvHash20)
{
    SHA1_CONTEXT ctx;
    SysSha1Init(&ctx);
    SysSha1Update(&ctx, (const unsigned char *)pvData, ulLength);
    SysSha1Fina(&ctx, (unsigned char *)pvHash20);
    return 0;
}

