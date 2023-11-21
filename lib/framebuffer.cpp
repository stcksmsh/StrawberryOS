#include <framebuffer.hpp>

FrameBuffer::FrameBuffer(uint32_t width, uint32_t height, uint32_t depth)
    : m_width(width), m_height(height), m_depth(depth){
        m_mailbox.clearBuff();
        
        m_mailbox.writeBuff(0, 35 * 4); /// set message size (35 uint_32s, meaning 35 * 4 bytes)
        m_mailbox.writeBuff(1, MBOX_REQUEST); /// set to request

        /// now come the tags
        m_mailbox.writeBuff(2, MBOX_TAG_SET_PHY_WH); /// set physical width/height
        m_mailbox.writeBuff(3, 8); /// value size in bytes
        m_mailbox.writeBuff(4, MBOX_REQUEST); /// request
        m_mailbox.writeBuff(5, 1920); /// width
        m_mailbox.writeBuff(6, 1080); /// height

        m_mailbox.writeBuff(7, MBOX_TAG_SET_VIRT_WH); /// set virtual width/height
        m_mailbox.writeBuff(8, 8);
        m_mailbox.writeBuff(9, MBOX_REQUEST);
        m_mailbox.writeBuff(10, 1920); /// width
        m_mailbox.writeBuff(11, 1080); /// height

        m_mailbox.writeBuff(12, MBOX_TAG_SET_VIRT_OFFSET); /// set virtual offset
        m_mailbox.writeBuff(13, 8);
        m_mailbox.writeBuff(14, MBOX_REQUEST);
        m_mailbox.writeBuff(15, 0); /// x
        m_mailbox.writeBuff(16, 0); /// y

        m_mailbox.writeBuff(17, MBOX_TAG_SET_DEPTH); /// set depth
        m_mailbox.writeBuff(18, 4);
        m_mailbox.writeBuff(19, MBOX_REQUEST);
        m_mailbox.writeBuff(20, 32); /// depth in pixels

        m_mailbox.writeBuff(21, MBOX_TAG_SET_PIX_ORD); /// set pixel order
        m_mailbox.writeBuff(22, 4);
        m_mailbox.writeBuff(23, MBOX_REQUEST);
        m_mailbox.writeBuff(24, 1); /// RGB

        m_mailbox.writeBuff(25, MBOX_TAG_ALLOCATE_BUFF); /// allocate buffer
        m_mailbox.writeBuff(26, 8);
        m_mailbox.writeBuff(27, MBOX_REQUEST);
        m_mailbox.writeBuff(28, 4096); /// alignment in bytes
        m_mailbox.writeBuff(29, 0); /// size in bytes

        m_mailbox.writeBuff(30, MBOX_TAG_GET_PITCH); /// get pitch
        m_mailbox.writeBuff(31, 4);
        m_mailbox.writeBuff(32, MBOX_REQUEST);
        m_mailbox.writeBuff(33, 0); /// pitch

        m_mailbox.writeBuff(34, MBOX_TAG_END); /// end of tags

    if(m_mailbox.call(MBOX_CHANNEL_ARM_TO_VC) && m_mailbox.readBuff(20) == 32 && m_mailbox.readBuff(28) != 0){
        m_pitch = m_mailbox.readBuff(33);
        m_buffer = (uint32_t*)((uint64_t)m_mailbox.readBuff(28) & 0x3FFFFFFF);
    }

}

FrameBuffer::~FrameBuffer()
{
}

void FrameBuffer::clear()
{
    uint32_t pixels = m_width * m_height;
    for (uint32_t i = 0; i < pixels; i++)
    {
        m_buffer[i] = 0;
    }
}