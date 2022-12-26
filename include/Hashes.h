/*
 *  sources: https://github.com/aappleby/smhasher
 */ 
#pragma once
#include <stdint.h>

//----------------------------------------------------------------------------
// fake / bad hashes

uint32_t BadHash ( const void * key, int len, uint32_t seed);

uint32_t sumhash ( const void * key, int len, uint32_t seed );

uint32_t sumhash32 ( const void * key, int len, uint32_t seed );

uint32_t MurmurOAAT ( const void * key, int len, uint32_t seed );

uint32_t FNV ( const void * key, int len, uint32_t seed);

uint32_t x17 ( const void * key, int len, uint32_t h );

uint32_t Bernstein ( const void * key, int len, uint32_t seed); 

uint32_t Crap8( const uint8_t *key, uint32_t len, uint32_t seed );

