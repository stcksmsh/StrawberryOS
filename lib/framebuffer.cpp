#include <framebuffer.hpp>

FrameBuffer::FrameBuffer(uint32_t width, uint32_t height, uint32_t depth)
    : m_iWidth(width), m_iHeight(height), m_iDepth(depth){
        m_Mailbox.clearBuff();
        
        m_Mailbox.writeBuff(0, 35 * 4); /// set message size (35 uint_32s, meaning 35 * 4 bytes)
        m_Mailbox.writeBuff(1, MBOX_REQUEST); /// set to request

        /// now come the tags
        m_Mailbox.writeBuff(2, MBOX_TAG_SET_PHY_WH); /// set physical width/height
        m_Mailbox.writeBuff(3, 8); /// value size in bytes
        m_Mailbox.writeBuff(4, MBOX_REQUEST); /// request
        m_Mailbox.writeBuff(5, 1920); /// width
        m_Mailbox.writeBuff(6, 1080); /// height

        m_Mailbox.writeBuff(7, MBOX_TAG_SET_VIRT_WH); /// set virtual width/height
        m_Mailbox.writeBuff(8, 8);
        m_Mailbox.writeBuff(9, MBOX_REQUEST);
        m_Mailbox.writeBuff(10, 1920); /// width
        m_Mailbox.writeBuff(11, 1080); /// height

        m_Mailbox.writeBuff(12, MBOX_TAG_SET_VIRT_OFFSET); /// set virtual offset
        m_Mailbox.writeBuff(13, 8);
        m_Mailbox.writeBuff(14, MBOX_REQUEST);
        m_Mailbox.writeBuff(15, 0); /// x
        m_Mailbox.writeBuff(16, 0); /// y

        m_Mailbox.writeBuff(17, MBOX_TAG_SET_DEPTH); /// set depth
        m_Mailbox.writeBuff(18, 4);
        m_Mailbox.writeBuff(19, MBOX_REQUEST);
        m_Mailbox.writeBuff(20, 32); /// depth in pixels

        m_Mailbox.writeBuff(21, MBOX_TAG_SET_PIX_ORD); /// set pixel order
        m_Mailbox.writeBuff(22, 4);
        m_Mailbox.writeBuff(23, MBOX_REQUEST);
        m_Mailbox.writeBuff(24, 1); /// RGB

        m_Mailbox.writeBuff(25, MBOX_TAG_ALLOCATE_BUFF); /// allocate buffer
        m_Mailbox.writeBuff(26, 8);
        m_Mailbox.writeBuff(27, MBOX_REQUEST);
        m_Mailbox.writeBuff(28, 4096); /// alignment in bytes
        m_Mailbox.writeBuff(29, 0); /// size in bytes

        m_Mailbox.writeBuff(30, MBOX_TAG_GET_PITCH); /// get pitch
        m_Mailbox.writeBuff(31, 4);
        m_Mailbox.writeBuff(32, MBOX_REQUEST);
        m_Mailbox.writeBuff(33, 0); /// pitch

        m_Mailbox.writeBuff(34, MBOX_TAG_END); /// end of tags

    if(m_Mailbox.call(MBOX_CH_ARM_TO_VC) && m_Mailbox.readBuff(20) == 32 && m_Mailbox.readBuff(28) != 0){
        m_iWidth = m_Mailbox.readBuff(10);
        m_iHeight = m_Mailbox.readBuff(11);
        m_iPitch = m_Mailbox.readBuff(33);
        m_pBuffer = (uint32_t*)((uint64_t)m_Mailbox.readBuff(28) & 0x3FFFFFFF);
    }

}

FrameBuffer::~FrameBuffer(){}

void FrameBuffer::clear()
{
    for(uint32_t x = 0; x < m_iWidth; x++){
        for(uint32_t y = 0; y < m_iHeight; y++){
            m_pBuffer[x * 4 + y * m_iPitch] = 0x0000AA00;
        }
    }
}