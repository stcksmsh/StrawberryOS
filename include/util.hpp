#ifndef UTIL_HPP
#define UTIL_HPP

#include <types.hpp>

extern "C" void *memset(void *pBuffer, int nValue, size_t nLength);

extern "C" void *memcpy (void *pDest, const void *pSrc, size_t nLength);

extern "C" void *memmove(void *pDest, const void *pSrc, size_t nLength);

extern "C" int memcmp(const void *p1, const void *p2, size_t nLength);

#endif