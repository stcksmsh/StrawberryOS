#include <machineinfo.hpp>
#include <mailbox.hpp>

bool MachineInfo::overvoltageAllowed = false;
bool MachineInfo::OTPProgAllowed = false;
bool MachineInfo::OTPReadAllowed = false;
bool MachineInfo::warrantyValid = false;
bool MachineInfo::revisionStyle = false;
uint64_t MachineInfo::memSize = 0;
int MachineInfo::manufacturer = 0;
int MachineInfo::processor = 0;
int MachineInfo::model = 0;
int MachineInfo::revision = 0;
uint64_t MachineInfo::MAC = 0;
uint64_t MachineInfo::ARM_MEM_START = 0;
uint64_t MachineInfo::ARM_MEM_END = 0;
uint64_t MachineInfo::VC_MEM_START = 0;
uint64_t MachineInfo::VC_MEM_END = 0;

int MachineInfo::getInfo(){
    Mailbox mb = Mailbox();
    mb.writeBuff(0, 22 * 4);
    mb.writeBuff(1, MBOX_REQUEST);

    /// get revision data
    mb.writeBuff(2, MBOX_TAG_GET_BOARD_REVISION);
    mb.writeBuff(3, 4);
    mb.writeBuff(4, MBOX_REQUEST);
    mb.writeBuff(5, 1); /// non zero becaue 0x0 is END_TAG


    /// get MAC address
    mb.writeBuff(6, MBOX_TAG_GET_BOARD_MAC);
    mb.writeBuff(7, 8);
    mb.writeBuff(8, MBOX_REQUEST);
    mb.writeBuff(9, 1);
    mb.writeBuff(10, 1);

    /// get ARM memory range
    mb.writeBuff(11, MBOX_TAG_GET_ARM_MEMORY);
    mb.writeBuff(12, 8);
    mb.writeBuff(13, MBOX_REQUEST);
    mb.writeBuff(14, 1);
    mb.writeBuff(15, 1);

    /// get VC memory range
    mb.writeBuff(16, MBOX_TAG_GET_VC_MEMORY);
    mb.writeBuff(17, 8);
    mb.writeBuff(18, MBOX_REQUEST);
    mb.writeBuff(19, 1);
    mb.writeBuff(20, 1);

    /// END tag
    mb.writeBuff(21, MBOX_TAG_END);

    /// if call fails, return 1
    if(!mb.call(MBOX_CH_ARM_TO_VC))return 1;
    
    /// get data from revision
    {
        uint32_t revisionVal = mb.readBuff(5);
        /// bit 23
        revisionStyle = (revisionVal >> 23) & 0x1;  
        /// new style
        if(revisionStyle == 1){
            /// bit 31
            overvoltageAllowed = (revisionVal >> 31) & 0x1;
            /// bit 30
            OTPProgAllowed = (revisionVal >> 30) & 0x1;
            /// bit 29
            OTPReadAllowed = (revisionVal >> 29) & 0x1;
            /// bit 25
            warrantyValid = (revisionVal >> 25) & 0x1;
            /// bits 20..22
            memSize = (1<<28) << ((revisionVal >> 20 ) & 0x7);
            // memSize = revision;
            /// bits 16..19
            manufacturer = (revisionVal >> 16) & 0xF;
            /// bits 12..15
            processor = (revisionVal >> 12) & 0xF;
            // bits 4..11
            model = (revisionVal >> 4) & 0xFF;
            /// bits 0..3
            revision = revisionVal & 0xF;
        }/// old style
        else{
            /// dont think this area is important
            /// probably wont be using these boards anyway
        }
    }
    
    /// get MAC 
    MAC = ((uint64_t)mb.readBuff(9) << 32) + mb.readBuff(10);
    

    /// get ARM memory data
    ARM_MEM_START = mb.readBuff(14);
    ARM_MEM_END = ARM_MEM_START + mb.readBuff(15) - 1;


    /// get VC memory data
    VC_MEM_START = mb.readBuff(19);
    VC_MEM_END = VC_MEM_START + mb.readBuff(20) - 1;
    return 0;
}
