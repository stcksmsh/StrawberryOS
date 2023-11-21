#ifndef MBOX_H
#define MBOX_H

#include <bcm2711.hpp>
#include <mmio.hpp>

#define MBOX_BUFF_MAX_SIZE 36 // in bytes

class Mailbox{
public:
    bool call(uint8_t channel);
    void clearBuff();
    void writeBuff(int pos, uint32_t data);
    uint32_t readBuff(int pos);
    
private:
    volatile uint32_t __attribute__((aligned(16))) buff[MBOX_BUFF_MAX_SIZE];  
};

/*
 * MBox value definitions
 */

#define MBOX_REQUEST 0x00000000

#define MBOX_STATUS_EMPTY	0x40000000
#define MBOX_STATUS_FULL		0x80000000

#define MBOX_RESPONSE_SUCCESS	0x80000000
#define MBOX_RESPONSE_ERROR		0x80000001

/*
 *  Channels
 */

#define MBOX_CHANNEL_ARM_TO_VC 0x00000008
#define MBOX_CHANNEL_VC_TO_ARM 0x00000009


/*
 *  Tags
 */

#define MBOX_TAG_END 0x00000000

/*
 *  LED tags
 */
#define MBOX_STATUS_LED_PIN 42
#define MBOX_POWER_LED_PIN 130 // the on and off values seem to be flipped???
/// 0x00000000 turns it on and 0xffffffff turns it off?? further investigation required

#define MBOX_TAG_SET_LED  0x00038041


/*
 *  Framebuffer tags
 *  all tags in request will be processed in one operation
 *  when setting parameters without an allocate buffer tag no change occurs if current buffer size is too small
 *  when an allocate buffer response is returned previous buffer is implicitly freed
 */

#define MBOX_TAG_ALLOCATE_BUFF 0x00040001
#define MBOX_TAG_RELEASE_BUFF 0x00048001

#define MBOX_TAG_BLANK_SCREEN 0x00040002

#define MBOX_TAG_GET_PHY_WH 0x00040003
#define MBOX_TAG_TEST_PHY_WH 0x00044003
#define MBOX_TAG_SET_PHY_WH 0x00048003

#define MBOX_TAG_GET_VIRT_WH 0x00040004
#define MBOX_TAG_TEST_VIRT_WH 0x00044004
#define MBOX_TAG_SET_VIRT_WH 0x00048004

#define MBOX_TAG_GET_DEPTH 0x00040005
#define MBOX_TAG_TEST_DEPTH 0x00044005
#define MBOX_TAG_SET_DEPTH 0x00048005

#define MBOX_TAG_GET_PIX_ORD 0x00040006
#define MBOX_TAG_TEST_PIX_ORD 0x00044006
#define MBOX_TAG_SET_PIX_ORD 0x00048006

#define MBOX_TAG_GET_ALPHA_MODE 0x00040007
#define MBOX_TAG_TEST_ALPHA_MODE 0x00044007
#define MBOX_TAG_SET_ALPHA_MODE 0x00048007

#define MBOX_TAG_GET_PITCH 0x00040008

#define MBOX_TAG_GET_VIRT_OFFSET 0x00040009
#define MBOX_TAG_TEST_VIRT_OFFSET 0x00044009
#define MBOX_TAG_SET_VIRT_OFFSET 0x00048009

#define MBOX_TAG_GET_OVERSCAN 0x0004000A
#define MBOX_TAG_TEST_OVERSCAN 0x0004400A
#define MBOX_TAG_SET_OVERSCAN 0x0004800A

#define MBOX_TAG_GET_PALETTE 0x0004000B
#define MBOX_TAG_TEST_PALETTE 0x0004400B
#define MBOX_TAG_SET_PALETTE 0x0004800B


#endif 
