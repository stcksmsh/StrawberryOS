#ifndef UTIL_HPP
#define UTIL_HPP

#include <types.hpp>

/// set memory region to a value
extern "C" void *memset(void *pBuffer, int nValue, size_t nLength);

/// copy memory region
extern "C" void *memcpy (void *pDest, const void *pSrc, size_t nLength);

/// move memory region (like memcpy but handles overlapping regions)
extern "C" void *memmove(void *pDest, const void *pSrc, size_t nLength);

/// compare memory regions
extern "C" int memcmp(const void *p1, const void *p2, size_t nLength);

#endif