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
    uint32_t m_width, m_height, m_depth;
    uint32_t m_pitch;
    volatile uint32_t* m_buffer;
    Mailbox m_mailbox;    
};

#endif
