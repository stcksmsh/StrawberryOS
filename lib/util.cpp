#include <util.h>

int memcmp(const void *p1, const void *p2, size_t nLength)
{

    const uint8_t *pBytes1 = (const uint8_t *)p1;
    const uint8_t *pBytes2 = (const uint8_t *)p2;
    while(nLength){
        if(*pBytes1 == *pBytes2){
            nLength--;
            pBytes1++;
            pBytes2++;
        }else{
            return *pBytes1 - *pBytes2;
        }
    }
    return 0;
}

void *memmove(void *pDest, const void *pSrc, size_t nLength){
    const uint8_t *pBytesSrc = (const uint8_t *)pSrc;
    uint8_t *pBytesDest = (uint8_t *)pDest;
    if(pBytesDest < pBytesSrc || pBytesDest >= pBytesSrc + nLength){
        memcpy(pDest, pSrc, nLength);
    }else{
        pBytesSrc += nLength - 1;
        pBytesDest += nLength - 1;
        while(nLength){
           *pBytesDest = *pBytesSrc;
            pBytesDest--;
            pBytesSrc--;
            nLength--;
        }
    }
    return pDest;
}