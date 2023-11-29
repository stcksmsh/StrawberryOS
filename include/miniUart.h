#ifndef MiniUART_H
#define MiniUART_H

#include <gpio.h>
#include <bcm2711.h>

class MiniUART{
public:
    MiniUART(){};

    /// initialize the miniUART
    void init();

    /// put a character to the miniUART
    void putChar(char);
    
    /// print CString to miniUART
    void print(char*);

    /// print an integer to miniUART
    void print(int);

    /// print a 64bit unsigned int in binary to miniUART
    void printBinary(uint64_t);

    /// print a 64bit unsigned int in hex to miniUART
    void printHex(uint64_t);

    /// print CString to miniUART and add a newline
    void println(char*);

    /// read a character from the miniUART
    char readChar();

    /// read a line from the miniUART
    char* readLine(char = '\n');

    /// get character, and print back to miniUART
    void update();

    /// the following make the miniUART look like a stream

    MiniUART& operator<<(char*);
    
    MiniUART& operator<<(char);

    MiniUART& operator<<(int);

    MiniUART& operator<<(uint64_t);

private:

    /// load the output queue
    void loadOutputQueue();

    /// is the read byte ready?
    uint32_t isReadByteReady();
    
    /// is the write byte ready?
    uint32_t isWriteByteReady();
    
    /// is the output queue empty?
    uint32_t isOutputQueueEmpty();
};
#endif