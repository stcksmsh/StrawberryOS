#include <mmio.h>

void mmioWrite(uint64_t reg, uint32_t val){
    *(volatile uint32_t*)reg = val;
}

uint32_t mmioRead(uint64_t reg){
    return *(volatile uint32_t*)reg;
}

uint32_t setMask(uint32_t value, uint32_t mask, int maskLen, int maskShift){
    value &= ~((((uint32_t)1 << maskLen) - 1) << maskShift);
    value |= mask << maskShift * maskLen;
    return value;
}

void regSet(uint64_t reg, uint32_t value, int valueLen, int valueIndex){
    uint32_t regVal = mmioRead(reg);
    regVal = setMask(regVal, value, valueLen, valueIndex);
    mmioWrite(reg, regVal);
}