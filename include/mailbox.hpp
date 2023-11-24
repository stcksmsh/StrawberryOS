#ifndef MBOX_HPP
#define MBOX_HPP

#include <bcm2711.hpp>
#include <mmio.hpp>

#define MBOX_BUFF_MAX_SIZE 64 // in uint32_t s

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
#define MBOX_CH_POWER 0x00000000
#define MBOX_CH_FRAMEBUFFER 0x00000001 /// deprecated
#define MBOX_CH_VIRT_UART 0x00000002
#define MBOX_CH_VCHIQ 0x00000003
#define MBOX_CH_LEDs 0x00000004
#define MBOX_CH_BUTTONS 0x00000005
#define MBOX_CH_TOUCH_SCREEN 0x00000006
#define MBOX_CH_UNKNOWN 0x00000007
#define MBOX_CH_ARM_TO_VC 0x00000008 /// this one is probably all I will ever use
#define MBOX_CH_VC_TO_ARM 0x00000009


/*
 *  Tags
 *  for channels 8 and 9
 */

#define MBOX_TAG_END 0x00000000

/*
 *  Hardware tags
 */

#define MBOX_TAG_GET_BOARD_MODEL 0x00010001
#define MBOX_TAG_GET_BOARD_REVISION 0x00010002
#define MBOX_TAG_GET_BOARD_MAC 0x00010003
#define MBOX_TAG_GET_BOARD_SERIAL 0x00010004
#define MBOX_TAG_GET_ARM_MEMORY 0x00010005
#define MBOX_TAG_GET_VC_MEMORY 0x00010006
#define MBOX_TAG_GET_CLOCKS 0x00010007

/*
 * Power tags
 */

#define MBOX_TAG_GET_POWER_STATE 0x00020001
#define MBOX_TAG_GET_TIMING 0x00020002
#define MBOX_TAG_SET_POWER_STATE 0x00028001

/*
 * Device IDs
 */

#define MBOX_DEVICE_SD_CARD 0x00000000
#define MBOX_DEVICE_UART0 0x00000001
#define MBOX_DEVICE_UART1 0x00000002
#define MBOX_DEVICE_USB_HCD 0x00000003
#define MBOX_DEVICE_I2C0 0x00000004
#define MBOX_DEVICE_I2C1 0x00000005
#define MBOX_DEVICE_I2C2 0x00000006
#define MBOX_DEVICE_SPI 0x00000007
#define MBOX_DEVICE_CCP2TX 0x00000008

/*
 *  LED tags
 */

#define MBOX_STATUS_LED_PIN 42
#define MBOX_POWER_LED_PIN 130 
// the on and off values for the PWR led seem to be flipped???
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
