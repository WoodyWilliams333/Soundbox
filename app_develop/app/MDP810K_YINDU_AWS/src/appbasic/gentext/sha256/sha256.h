#ifndef _new_sha256_h
#define _new_sha256_h
 
#include<string.h>
#include<stdio.h>
#include<stdint.h>

void sha256(const unsigned char *data, size_t len, unsigned char *out);
 
#endif /* sha256_h */