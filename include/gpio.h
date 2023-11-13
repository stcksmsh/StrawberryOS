#ifndef GPIO_HEADERFILE
#define GPIO_HEADERFILE

#include <stdint.h>
#include <mmio.h>

/// @brief Specifies the BASE address for GPIO pin registers, as well as their respective offsets
typedef enum{
    GPIO_BASE = 0xFE200000,
    GPFSEL0 = GPIO_BASE + 0x00,
    GPFSEL1 = GPIO_BASE + 0x04,
    GPFSEL2 = GPIO_BASE + 0x08,
    GPFSEL3 = GPIO_BASE + 0x0c,
    GPFSEL4 = GPIO_BASE + 0x10,
    GPFSEL5 = GPIO_BASE + 0x14,
    GPSET0 = GPIO_BASE + 0x1c,
    GPSET1 = GPIO_BASE + 0x20,
    GPCLR0 = GPIO_BASE + 0x28,
    GPCLR1 = GPIO_BASE + 0x2c,
    GPLEV0 = GPIO_BASE + 0x34,
    GPLEV1 = GPIO_BASE + 0x38,
    GPEDS0 = GPIO_BASE + 0x40,
    GPEDS1 = GPIO_BASE + 0x44,
    GPREN0 = GPIO_BASE + 0x4c,
    GPREN1 = GPIO_BASE + 0x50,
    GPFEN0 = GPIO_BASE + 0x58,
    GPFEN1 = GPIO_BASE + 0x5c,
    GPHEN0 = GPIO_BASE + 0x64,
    GPHEN1 = GPIO_BASE + 0x68,
    GPLEN0 = GPIO_BASE + 0x70,
    GPLEN1 = GPIO_BASE + 0x74,
    GPAREN0 = GPIO_BASE + 0x7c,
    GPAREN1 = GPIO_BASE + 0x80,
    GPAFEN0 = GPIO_BASE + 0x88,
    GPAFEN1 = GPIO_BASE + 0x8c,
    GPIO_PUP_PDN_CNTRL_REG0 = GPIO_BASE + 0xe4,
    GPIO_PUP_PDN_CNTRL_REG1 = GPIO_BASE + 0xe8,
    GPIO_PUP_PDN_CNTRL_REG2 = GPIO_BASE + 0xec,
    GPIO_PUP_PDN_CNTRL_REG3 = GPIO_BASE + 0xf0
}  GPIO_REG;

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
void pinSet(uint8_t pin);

/// @brief Clears the specified pin
/// @param pin the pin to clear [0..57]]
void pinClear(uint8_t pin);

/// @brief Reads the value of the specified pin
/// @param pin the pin to read [0..57]
/// @return 0 if not set, more than 0 if set, less than 0 if error
int pinRead(uint8_t pin);

#endif