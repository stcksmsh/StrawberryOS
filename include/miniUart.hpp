#ifndef MiniUART_H
#define MiniUART_H

#include <gpio.hpp>
#include <bcm2711.hpp>

class MiniUART{
public:
    MiniUART(){};

    void init();

    void putChar(char);
    
    void print(char*);

    void print(int);

    void printBinary(uint64_t);

    void printHex(uint64_t);
    // void print(double, int = 6);

    void println(char*);

    char readChar();

    char* readLine(char = '\n');

    void update();


    MiniUART& operator<<(char*);

    MiniUART& operator<<(int);

private:

    uint8_t RX, TX;

    void loadOutputQueue();

    uint32_t isReadByteReady();
    
    uint32_t isWriteByteReady();
    
    uint32_t isOutputQueueEmpty();
};
#endif