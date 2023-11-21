#include <miniUart.hpp>

#define MiniUART_MAX_QUEUE 16384 /// 16 * 1024

#define AUX_MiniUART_CLOCK 500000000

#define AUX_MU_BAUD(baud) ((AUX_MiniUART_CLOCK/(baud*8))-1)

uint8_t MiniUART_output_queue[MiniUART_MAX_QUEUE];
uint32_t MiniUART_output_queue_write = 0;
uint32_t MiniUART_output_queue_read = 0;


void MiniUART::init(){
    /// enables the MiniUART
    mmioWrite(ARM_AUX_ENABLES, 1);
    /// disable interrupts
    mmioWrite(ARM_AUX_MU_IER_REG, 0);
    /// disable everything until set up
    mmioWrite(ARM_AUX_MU_CNTL_REG, 0);
    /// set MiniUART to 8bit mode
    mmioWrite(ARM_AUX_MU_LCR_REG, 3);
    /// set MiniUART_1RTS to high
    mmioWrite(ARM_AUX_MU_MCR_REG, 0);
    /// disable interrupts again???
    mmioWrite(ARM_AUX_MU_IER_REG, 0);
    /// 6 is to clear receive and transmit FIFO, C enables FIFOs
    mmioWrite(ARM_AUX_MU_IIR_REG, 0xC6);
    /// set baud rate
    mmioWrite(ARM_AUX_MU_BAUD_REG, AUX_MU_BAUD(115200));
    /// set pins 14 and 15 to ALT5, RX and TX
    pinPull(14, DOWN);
    pinMode(14, ALT5);
    pinPull(15, DOWN);
    pinMode(15, ALT5);
    // enable receiver and transmiter
    mmioWrite(ARM_AUX_MU_CNTL_REG, 3);    
}

void MiniUART::putChar(char ch){
    while(!isWriteByteReady());
    mmioWrite(ARM_AUX_MU_IO_REG, (uint32_t)ch);
}

void MiniUART::print(char* buff){
    while(*buff){
        if(*buff == '\n')putChar('\r');
        putChar(*buff++);
    }
}

void MiniUART::println(char* buff){
    print(buff);
    putChar('\n');
}

char MiniUART::readChar() {
    while (!isReadByteReady());
    return (char)mmioRead(ARM_AUX_MU_IO_REG);
}

// char* MiniUART::readLine(char delim = '\n') {
//     char* buff = (char*)malloc(1);
//     buff[0] = '\0';
//     char ch;
//     while ((ch = readChar()) != delim) {
//         buff = (char*)realloc(buff, strlen(buff) + 2);
//         buff[strlen(buff) + 1] = '\0';
//         buff[strlen(buff)] = ch;
//     }
//     return buff;
// }

uint32_t MiniUART::isReadByteReady()  {
    return mmioRead(ARM_AUX_MU_LSR_REG) & 0x01;
}

uint32_t MiniUART::isWriteByteReady(){
    /// we read the 5th bit of ARM_AUX_MU_LSR_REG
    return mmioRead(ARM_AUX_MU_LSR_REG) & 0x20;
}

MiniUART& MiniUART::operator<<(char* buff){
    print(buff);
    return *this;
}

void MiniUART::update(){
    loadOutputQueue();
    if (isReadByteReady()) {
       char ch = readChar();
       if (ch == '\r') putChar('\n');
       else putChar(ch);
    }
}

uint32_t MiniUART::isOutputQueueEmpty() {
    return MiniUART_output_queue_read == MiniUART_output_queue_write;
}

void MiniUART::loadOutputQueue(){
    
        while (!isOutputQueueEmpty() && isWriteByteReady()) {
        putChar(MiniUART_output_queue[MiniUART_output_queue_read]);
        MiniUART_output_queue_read = (MiniUART_output_queue_read + 1) & (MiniUART_MAX_QUEUE - 1); // Don't overrun
    }
}
