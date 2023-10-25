#include "common/mmio.h"

void mmioWrite(address reg, uint32_t val){
    *(volatile uint32_t*)reg = val;
}

uint32_t mmioRead(address reg){
    return *(volatile uint32_t*)reg;
}

uint32_t setMask(uint32_t value, uint32_t mask, int maskLen, int maskShift){
    value &= ~((((uint32_t)1 << maskLen) - 1) << maskShift);
    value |= mask << maskShift * maskLen;
    return value;
}

void regSet(address reg, uint32_t value, int valueLen, int valueIndex){
    uint32_t regVal = mmioRead(reg);
    regVal = setMask(regVal, value, valueLen, valueIndex);
    mmioWrite(reg, regVal);
}