#ifndef GPIO_H
#define GPIO_H

#include <bcm2711.h>
#include <stdint.h>
#include <mmio.h>

/// @brief Specifies the 7 different modes a GPIO pin can be in
typedef enum{
    INPUT = 0b000,
    OUTPUT = 0b001,
    ALT0 = 0b100,
    ALT1 = 0b101,
    ALT2 = 0b110,
    ALT3 = 0b111,
    ALT4 = 0b011,
    ALT5 = 0b010
} GPIO_MODE;

/// @brief specifies the 3 pull resistors
typedef enum{
    NONE = 0b00,
    UP = 0b01,
    DOWN = 0b10
} GPIO_PULL;

/// @brief sets the pull for the specified pin
/// @param pin the number of the pin to change pull
/// @param pull the pull to set
void pinPull(uint8_t pin, GPIO_PULL pull);

/// @brief Sets the desired  GPIO pin to input, output or some alternative function
/// @param pin the number of the pin to set
/// @param mode the mode to set it to
void pinMode(uint8_t pin, GPIO_MODE mode);

/// @brief Sets the specified pin
/// @param pin the pin to set [0..57]
void pinSet(int pin);

/// @brief Clears the specified pin
/// @param pin the pin to clear [0..57]]
void pinClear(uint8_t pin);

/// @brief Reads the value of the specified pin
/// @param pin the pin to read [0..57]
/// @return 0 if not set, more than 0 if set, less than 0 if error
int pinRead(uint8_t pin);

#endif