#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <mailbox.hpp>
#include <types.hpp>

class FrameBuffer {
public:
    FrameBuffer(uint32_t width, uint32_t height, uint32_t depth);
    ~FrameBuffer();

    void clear();

private:
    uint32_t m_iWidth, m_iHeight, m_iDepth;
    uint32_t m_iPitch;
    volatile uint32_t* m_pBuffer;
    Mailbox m_Mailbox;    
};

#endif
