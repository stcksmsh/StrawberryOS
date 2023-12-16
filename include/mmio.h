/**
 * @file mmio.h
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef MMIO_H
#define MMIO_H

#include <types.h>

/// @brief writes to the MMIO register
/// @param aReg the address of the register
/// @param val the value to write
inline void write32(uint64_t reg, uint32_t val){
    *(volatile uint32_t*)reg = val;
}

/// @brief reads from the MMIO register
/// @param aReg the address of the register
/// @return its current value
inline uint32_t read32(uint64_t reg){
    return *(volatile uint32_t*)reg;
}
/// @brief sets the value mask to the maskShift-th group of maskLen bits, example to set the 6,7,8 bits of X to 0b100 call setMask(X, 0b100, 3, 3)
/// @param value the value to set mask onto
/// @param mask the mask itself
/// @param maskLen the length of the mask
/// @param maskShift how many bits precede the mask, in groups of size mask
/// @return 'masked' value
inline uint32_t setMask(uint32_t value, uint32_t mask, int maskLen, int maskShift){
    value &= ~((((uint32_t)1 << maskLen) - 1) << maskShift);
    value |= mask << maskShift * maskLen;
    return value;
}

/// @brief Sets the valueIndex-th value of valueLen length in register reg
/// @param u64Reg address of the register
/// @param u32Value value to set
/// @param iValueLen length of value
/// @param iValueIndex index of value
/// @return 
inline void regSet(uint64_t reg, uint32_t value, int valueLen, int valueIndex){
    uint32_t regVal = read32(reg);
    regVal = setMask(regVal, value, valueLen, valueIndex);
    write32(reg, regVal);
}
#endif  // MMIO_H




