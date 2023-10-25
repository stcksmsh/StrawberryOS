#ifndef UART_HEADERFILE
#define UART_HEADERFILE

#include "gpio.h"

#define UART_MAX_QUEUE 16384 /// 16 * 1024

static const uint32_t AUX_UART_CLOCK  = 500000000;

typedef enum{
    AUX_BASE = 0xFE215000,
    AUX_IRQ = AUX_BASE + 0x00,
    AUX_ENABLES = AUX_BASE + 0x04,
    AUX_MU_IO_REG = AUX_BASE + 0x40,
    AUX_MU_IER_REG = AUX_BASE + 0x44,
    AUX_MU_IIR_REG = AUX_BASE + 0x48,
    AUX_MU_LCR_REG = AUX_BASE + 0x4c,
    AUX_MU_MCR_REG = AUX_BASE + 0x50,
    AUX_MU_LSR_REG = AUX_BASE + 0x54,
    AUX_MU_MSR_REG = AUX_BASE + 0x58,
    AUX_MU_SCRATCH = AUX_BASE + 0x5c,
    AUX_MU_CNTL_REG = AUX_BASE + 0x60,
    AUX_MU_STAT_REG = AUX_BASE + 0x64,
    AUX_MU_BAUD_REG = AUX_BASE + 0x68,
    AUX_SPI1_CNTL0_REGSP = AUX_BASE + 0x80,
    AUX_SPI1_CNTL1_REGSP = AUX_BASE + 0x84,
    AUX_SPI1_STAT_REGSP = AUX_BASE + 0x88,
    AUX_SPI1_PEEK_REGSP = AUX_BASE + 0x8c,
    AUX_SPI1_IO_REa = AUX_BASE + 0xa0,
    AUX_SPI1_IO_REb = AUX_BASE + 0xa4,
    AUX_SPI1_IO_REc = AUX_BASE + 0xa8,
    AUX_SPI1_IO_REd = AUX_BASE + 0xac,
    AUX_SPI1_TXHOLD_REa = AUX_BASE + 0xb0,
    AUX_SPI1_TXHOLD_REb = AUX_BASE + 0xb4,
    AUX_SPI1_TXHOLD_REc = AUX_BASE + 0xb8,
    AUX_SPI1_TXHOLD_REd = AUX_BASE + 0xbc,
    AUX_SPI2_CNTL0_REGSP = AUX_BASE + 0xc0,
    AUX_SPI2_CNTL1_REGSP = AUX_BASE + 0xc4,
    AUX_SPI2_STAT_REGSP = AUX_BASE + 0xc8,
    AUX_SPI2_PEEK_REGSP = AUX_BASE + 0xcc,
    AUX_SPI2_IO_REa = AUX_BASE + 0xe0,
    AUX_SPI2_IO_REb = AUX_BASE + 0xe4,
    AUX_SPI2_IO_REc = AUX_BASE + 0xe8,
    AUX_SPI2_IO_REd = AUX_BASE + 0xec,
    AUX_SPI2_TXHOLD_REa = AUX_BASE + 0xf0,
    AUX_SPI2_TXHOLD_REb = AUX_BASE + 0xf4,
    AUX_SPI2_TXHOLD_REc = AUX_BASE + 0xf8,
    AUX_SPI2_TXHOLD_REd = AUX_BASE + 0xfc
} AUX_REG;

/// @brief initialises the UART interface
void uart_init();

/// @brief writes a char array to uart
/// @param buff the array to write
void uart_write(char* buff);

void uart_loadOutputFifo();

uint8_t uart_readByte();

uint32_t uart_isReadByteReady();

/// @brief checks the UART line status whether we can send
/// @return 0 if we cant, > 0 if we can
uint32_t uart_isWriteByteReady();

/// @brief waits intil uart_isWriteByteReady, then sends
/// @param ch the character to send
void uart_writeByteBlocking(char ch);

void uart_update();

#define AUX_MU_BAUD(baud) ((AUX_UART_CLOCK/(baud*8))-1)

#endif