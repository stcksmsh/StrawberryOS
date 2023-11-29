#ifndef MMIO_HPP
#define MMIO_HPP

#include <types.h>

/// @brief writes to the MMIO register
/// @param reg the address of the register
/// @param val the value to write
void mmioWrite(uint64_t reg, uint32_t val);

/// @brief reads from the MMIO register
/// @param reg the address of the register
/// @return its current value
uint32_t mmioRead(uint64_t reg);

/// @brief sets the value mask to the maskShift-th group of maskLen bits, example to set the 6,7,8 bits of X to 0b100 call setMask(X, 0b100, 3, 3)
/// @param value the value to set mask onto
/// @param mask the mask itself
/// @param maskLen the length of the mask
/// @param maskShift how many bits precede the mask, in groups of size mask
/// @return 'masked' value
uint32_t setMask(uint32_t value, uint32_t mask, int maskLen, int maskShift);

/// @brief Sets the valueIndex-th value of valueLen length in register reg
/// @param reg address of the register
/// @param value value to set
/// @param valueLen length of value
/// @param valueIndex index of value
/// @return 
void regSet(uint64_t reg, uint32_t value, int valueLen, int valueIndex);

#endif