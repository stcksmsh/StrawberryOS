/**
 * @file framebuffer.h
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <mailbox.h>
#include <types.h>

class FrameBuffer {
public:
    FrameBuffer(uint32_t width, uint32_t height, uint32_t depth);
    ~FrameBuffer();

    void clear();

private:
    uint32_t m_iWidth, m_iHeight, m_iDepth;
    uint32_t m_iPitch;
    volatile uint32_t* m_piBuffer;
    Mailbox m_Mailbox;    
};

#endif  // FRAMEBUFFER_H
