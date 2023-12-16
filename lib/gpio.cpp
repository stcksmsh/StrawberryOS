/**
 * @file gpio.cpp
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <gpio.h>

void pinSet(uint8_t pin){
    uint64_t reg = 0;
    if(pin <= 31) reg = ARM_GPIO_GPSET0;
    else reg = ARM_GPIO_GPSET1;
    regSet(reg, 0b1, 1, pin%32);
}

void pinClear(uint8_t pin){
    uint64_t reg = 0;
    if(pin <= 31) reg = ARM_GPIO_GPCLR0;
    else reg = ARM_GPIO_GPCLR1;
    regSet(reg, 0b1, 1, pin%32);
}

int pinRead(uint8_t pin){
    uint64_t reg = 0;
    if(pin <= 31) reg = ARM_GPIO_GPLEV0;
    else reg = ARM_GPIO_GPLEV1;
    uint32_t val = read32(reg);
    val = setMask(val, 0b1, 1, pin%32);
    return val;
}

void pinMode(uint8_t pin, GPIO_MODE mode){
    uint64_t reg = ARM_GPIO_GPFSEL0 + 0x04 * (pin / 10);
    regSet(reg, mode, 3, pin%10);
}

void pinPull(uint8_t pin, GPIO_PULL pull){
   uint64_t reg = ARM_GPIO_GPIO_PUPDNN0 + 0x4 * (pin / 16);
   regSet(reg, pull, 2, pin%16);
}