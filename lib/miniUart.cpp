#include <miniUart.h>

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
    if(ch == '\n')putChar('\r');
}

void MiniUART::print(char* buff){
    while(*buff != 0)putChar(*buff++);
}

void MiniUART::print(int n){
    int zeroCnt = 0;
    int rev = 0;
    if(n < 0){
        putChar('-');
        n = - n;
    }
    while(n % 10 == 0 && n > 0){
        zeroCnt ++;
        n /= 10;
    }
    while(n > 0){
        rev = rev * 10 + n % 10;
        n /= 10;
    }
    do{
        putChar('0' + rev%10);
        rev /= 10;
    }while(rev > 0);
    while(zeroCnt > 0){
        putChar('0');
        zeroCnt --;
    }
}

void MiniUART::printBinary(uint64_t n){
    for(int i = 64; i >= 0; i--){
        if(n & (1 << i))putChar('1');
        else putChar('0');
    }
}

void MiniUART::printHex(uint64_t n){
    for(int i = 15; i >= 0; i--){
        int val = (n >> (i * 4)) & 0xF;
        switch(val){
            case 0: putChar('0'); break;
            case 1: putChar('1'); break;
            case 2: putChar('2'); break;
            case 3: putChar('3'); break;
            case 4: putChar('4'); break;
            case 5: putChar('5'); break;
            case 6: putChar('6'); break;
            case 7: putChar('7'); break;
            case 8: putChar('8'); break;
            case 9: putChar('9'); break;
            case 10: putChar('A'); break;
            case 11: putChar('B'); break;
            case 12: putChar('C'); break;
            case 13: putChar('D'); break;
            case 14: putChar('E'); break;
            case 15: putChar('F'); break;
        }
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

void MiniUART::update(){
    if (isReadByteReady()) {
       char ch = readChar();
       if (ch == '\r') putChar('\n');
       else putChar(ch);
    }
}


void MiniUART::loadOutputQueue(){
    
        while (!isOutputQueueEmpty() && isWriteByteReady()) {
        putChar(MiniUART_output_queue[MiniUART_output_queue_read]);
        MiniUART_output_queue_read = (MiniUART_output_queue_read + 1) & (MiniUART_MAX_QUEUE - 1); // Don't overrun
    }
}

uint32_t MiniUART::isReadByteReady()  {
    return mmioRead(ARM_AUX_MU_LSR_REG) & 0x01;
}

uint32_t MiniUART::isWriteByteReady(){
    /// we read the 5th bit of ARM_AUX_MU_LSR_REG
    return mmioRead(ARM_AUX_MU_LSR_REG) & 0x20;
}

uint32_t MiniUART::isOutputQueueEmpty() {
    return MiniUART_output_queue_read == MiniUART_output_queue_write;
}

MiniUART& MiniUART::operator<<(char* buff){
    print(buff);
    return *this;
}

MiniUART& MiniUART::operator<<(char ch){
    putChar(ch);
    return *this;
}

MiniUART& MiniUART::operator<<(int n){
    print(n);
    return *this;
}

MiniUART& MiniUART::operator<<(uint64_t n){
    print(n);
    return *this;
}