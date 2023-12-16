/**
 * @file machineinfo.cpp
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <machineinfo.h>
#include <mailbox.h>

bool MachineInfo::m_bOvervoltageAllowed = false;
bool MachineInfo::m_bOTPProgAllowed = false;
bool MachineInfo::m_bOTPReadAllowed = false;
bool MachineInfo::m_bWarrantyValid = false;
bool MachineInfo::m_bRevisionStyle = false;
uint64_t MachineInfo::m_aMemSize = 0;
int MachineInfo::m_iManufacturer = 0;
int MachineInfo::m_iProcessor = 0;
int MachineInfo::m_iModel = 0;
int MachineInfo::m_iRevision = 0;
uint64_t MachineInfo::m_u64MAC = 0;
uint64_t MachineInfo::m_aARM_MEM_START = 0;
uint64_t MachineInfo::m_aARM_MEM_END = 0;
uint64_t MachineInfo::m_aVC_MEM_START = 0;
uint64_t MachineInfo::m_aVC_MEM_END = 0;

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
    if(!mb.call(MBOX_CH_ARM_TO_VC))return -1;
    
    /// get data from revision
    {
        uint32_t revisionVal = mb.readBuff(5);
        /// bit 23
        m_bRevisionStyle = (revisionVal >> 23) & 0x1;  
        /// new style
        if(m_bRevisionStyle == 1){
            /// bit 31
            m_bOvervoltageAllowed = (revisionVal >> 31) & 0x1;
            /// bit 30
            m_bOTPProgAllowed = (revisionVal >> 30) & 0x1;
            /// bit 29
            m_bOTPReadAllowed = (revisionVal >> 29) & 0x1;
            /// bit 25
            m_bWarrantyValid = (revisionVal >> 25) & 0x1;
            /// bits 20..22
            m_aMemSize = (1<<28) << ((revisionVal >> 20 ) & 0x7);
            // m_lmemSize = revision;
            /// bits 16..19
            m_iManufacturer = (revisionVal >> 16) & 0xF;
            /// bits 12..15
            m_iProcessor = (revisionVal >> 12) & 0xF;
            // bits 4..11
            m_iModel = (revisionVal >> 4) & 0xFF;
            /// bits 0..3
            m_iRevision = revisionVal & 0xF;
        }/// old style
        else{
            /// dont think this area is important
            /// probably wont be using these boards anyway
        }
    }
    
    /// get MAC 
    m_u64MAC = ((uint64_t)mb.readBuff(9) << 32) + mb.readBuff(10);
    

    /// get ARM memory data
    m_aARM_MEM_START = mb.readBuff(14);
    m_aARM_MEM_END = m_aARM_MEM_START + mb.readBuff(15) - 1;


    /// get VC memory data
    m_aVC_MEM_START = mb.readBuff(19);
    m_aVC_MEM_END = m_aVC_MEM_START + mb.readBuff(20) - 1;
    return 0;
}
