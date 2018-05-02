/* public api for steve reid's public domain SHA-1 implementation */
/* this file is in the public domain */

// From https://github.com/aappleby/smhasher

#pragma once
#include <stdint.h>

//#if defined(_MSC_VER)

//#define ROTL32(x,y)	_rotl(x,y)

//#else	//	defined(_MSC_VER)

inline uint32_t rotl32(uint32_t x, int8_t r)
{
	return (x << r) | (x >> (32 - r));
}
#define	ROTL32(x,y)	rotl32(x,y)

//#endif

struct SHA1_CTX
{
	uint32_t state[5];
	uint32_t count[2];
	uint8_t  buffer[64];
};

#define SHA1_DIGEST_SIZE 20

void SHA1_Init(SHA1_CTX* context);
void SHA1_Update(SHA1_CTX* context, const uint8_t* data, const size_t len);
void SHA1_Final(SHA1_CTX* context, uint8_t digest[SHA1_DIGEST_SIZE]);

void sha1_32a(const void * key, int len, uint32_t seed, void * out);
void digest_to_hex(const uint8_t digest[SHA1_DIGEST_SIZE], char *output);
