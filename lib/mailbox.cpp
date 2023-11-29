#include <mailbox.h>

bool Mailbox::call(uint8_t channel){
    unsigned int r = ((unsigned int)((unsigned long)&m_pBuffer) & ~0xF) | (channel & 0xF);

    while(mmioRead(MAILBOX0_STATUS) & MBOX_STATUS_FULL);

    mmioWrite(MAILBOX1_WRITE, r);
    
    while(1){
        while(mmioRead(MAILBOX0_STATUS) & MBOX_STATUS_EMPTY);

        if(r == mmioRead(MAILBOX0_READ))
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