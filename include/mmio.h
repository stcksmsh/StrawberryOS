/*
 * mmio.h
 *
 * stcksmsh[github.com] - vukicevickosta@gmail.com
 * 
 * contains functions for reading and writing to MMIO registers
 */

#ifndef MMIO_H
#define MMIO_H

#include <types.h>

/// @brief writes to the MMIO register
/// @param aReg the address of the register
/// @param val the value to write
void mmioWrite(uintptr_t aReg, uint32_t u32Val);

/// @brief reads from the MMIO register
/// @param aReg the address of the register
/// @return its current value
uint32_t mmioRead(uintptr_t aReg);

/// @brief sets the value mask to the maskShift-th group of maskLen bits, example to set the 6,7,8 bits of X to 0b100 call setMask(X, 0b100, 3, 3)
/// @param value the value to set mask onto
/// @param mask the mask itself
/// @param maskLen the length of the mask
/// @param maskShift how many bits precede the mask, in groups of size mask
/// @return 'masked' value
uint32_t setMask(uint32_t u32Value, uint32_t u32Mask, int iMaskLen, int iMaskShift);

/// @brief Sets the valueIndex-th value of valueLen length in register reg
/// @param u64Reg address of the register
/// @param u32Value value to set
/// @param iValueLen length of value
/// @param iValueIndex index of value
/// @return 
void regSet(uintptr_t aReg, uint32_t u32Value, int iValueLen, int iValueIndex);

#endif  // MMIO_H