#include "common/uart.h"

uint8_t uart_output_queue[UART_MAX_QUEUE];
uint32_t uart_output_queue_write = 0;
uint32_t uart_output_queue_read = 0;


void uart_init(){
    /// enables the UART
    mmioWrite(AUX_ENABLES, 1);
    /// disable interrupts
    mmioWrite(AUX_MU_IER_REG, 0);
    /// disable everything until set up
    mmioWrite(AUX_MU_CNTL_REG, 0);
    /// set UART to 8bit mode
    mmioWrite(AUX_MU_LCR_REG, 3);
    /// set UART_1RTS to high
    mmioWrite(AUX_MU_MCR_REG, 0);
    /// disable interrupts again???
    mmioWrite(AUX_MU_IER_REG, 0);
    /// 6 is to clear receive and transmit FIFO, C enables FIFOs
    mmioWrite(AUX_MU_IIR_REG, 0xC6);
    /// set baud rate
    mmioWrite(AUX_MU_BAUD_REG, AUX_MU_BAUD(115200));
    /// set pins 14 and 15 to ALT5, RX and TX
    pinPull(14, DOWN);
    pinMode(14, ALT5);
    pinPull(15, DOWN);
    pinMode(15, ALT5);
    // enable receiver and transmiter
    mmioWrite(AUX_MU_CNTL_REG, 3);    
}

uint32_t uart_isReadByteReady()  {
    return mmioRead(AUX_MU_LSR_REG) & 0x01;
}

uint32_t uart_isWriteByteReady(){
    /// we read the 5th bit of AUX_MU_LSR_REG
    return mmioRead(AUX_MU_LSR_REG) & 0x20;
}

void uart_writeByteBlocking(char ch){
    // while(!uart_isWriteByteReady());
    mmioWrite(AUX_MU_IO_REG, (uint32_t)ch);
}

void uart_write(char* buff){
    while(*buff){
        if(*buff == '\n')uart_writeByteBlocking('\r');
        uart_writeByteBlocking(*buff++);
    }
}

void uart_update(){
    uart_loadOutputFifo();
    if (uart_isReadByteReady()) {
       uint8_t ch = uart_readByte();
       if (ch == '\r') uart_write("\n");
       else uart_writeByteBlocking(ch);
    }
}

uint32_t uart_isOutputQueueEmpty() {
    return uart_output_queue_read == uart_output_queue_write;
}

void uart_loadOutputFifo(){
        while (!uart_isOutputQueueEmpty() && uart_isWriteByteReady()) {
        uart_writeByteBlocking(uart_output_queue[uart_output_queue_read]);
        uart_output_queue_read = (uart_output_queue_read + 1) & (UART_MAX_QUEUE - 1); // Don't overrun
    }
}

uint8_t uart_readByte() {
    while (!uart_isReadByteReady());
    return (uint8_t)mmioRead(AUX_MU_IO_REG);
}

