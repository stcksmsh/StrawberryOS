/**
 * @file mailbox.cpp
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief implementation of Mailbox class
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <mailbox.h>

bool Mailbox::call(uint8_t channel){
    unsigned int r = ((unsigned int)((unsigned long)&m_pBuffer) & ~0xF) | (channel & 0xF);

    while(read32(MAILBOX0_STATUS) & MBOX_STATUS_FULL);

    write32(MAILBOX1_WRITE, r);
    
    while(1){
        while(read32(MAILBOX0_STATUS) & MBOX_STATUS_EMPTY);

        if(r == read32(MAILBOX0_READ))
            return m_pBuffer[1] == MBOX_RESPONSE_SUCCESS;
    }
    return 0;
}

void Mailbox::clearBuff(){
    for(int i = 0; i < 36; i++){
        m_pBuffer[i] = 0;
    }
}

void Mailbox::writeBuff(int pos, uint32_t data){
    m_pBuffer[pos] = data;
}

uint32_t Mailbox::readBuff(int pos){
    return m_pBuffer[pos];
}