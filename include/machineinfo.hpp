#ifndef MACHINEINFO_HPP
#define MACHINEINFO_HPP

#include <mailbox.hpp>

class MachineInfo{
private:
    static bool overvoltageAllowed;
    static bool OTPProgAllowed;
    static bool OTPReadAllowed;
    static bool warrantyValid;
    /*
     * 0 - old style
     * 1 - new style
    */
    static bool revisionStyle;
    /*
     * RAM capacity in bytes (possible values: 256MB, 512MB, ... 4GB, 8GB)
     */
    static uint64_t memSize;
    /*
     * 0 - Sony UK
     * 1 - Egoman
     * 2 - Embest
     * 3 - Sony Japan
     * 4 - Embest
     * 5 - Stadium
     */
    static int manufacturer;
    /*
     * 0 - BCM2835
     * 1 - BCM2836
     * 2 - BCM2837
     * 3 - BCM2711
     * 4 - BCM2712
     */
    static int processor;
    /*
     * 0 - A
     * 1 - B
     * 2 - A+
     * 3 - B+
     * 4 - 2B
     * 5 - Alpha (early prototype)
     * 6 - CM1
     * 8 - 3B
     * 9 - Zero
     * 10 - CM3
     * 12 - Zero W
     * 13 - 3B+
     * 14 - 3A+
     * 15 - internal use
     * 16 - CM3+
     * 17 - 4B
     * 18 - Zero 2W
     * 19 - 400
     * 19 - CM4
     * 20 - CM4S
     * 21 - 4B
     * 22 - 
     */
    static int model;
    /*
     * revision number - 0,1,...
     */
    static int revision;

    static uint64_t MAC;

    static uint64_t ARM_MEM_START;
    
    static uint64_t ARM_MEM_END;

    static uint64_t VC_MEM_START;
    
    static uint64_t VC_MEM_END;

public:

    /// @brief gets machine info
    /// @return returns 0 if successful , error code otherwise
    static int getInfo();

    /// @brief gets the overvoltage allowed status
    /// @return true if overvoltage is allowed, false otherwise
    static bool isOvervoltageAllowed() {
        return overvoltageAllowed;
    }

    /// @brief gets the OTP programming allowed status
    /// @return true if OTP programming is allowed, false otherwise
    static bool isOTPProgAllowed() {
        return OTPProgAllowed;
    }

    /// @brief gets the OTP read allowed status
    /// @return true if OTP read is allowed, false otherwise
    static bool isOTPReadAllowed() {
        return OTPReadAllowed;
    }

    /// @brief gets the warranty validity status
    /// @return true if warranty is valid, false otherwise
    static bool isWarrantyValid() {
        return warrantyValid;
    }

    /// @brief gets the revision style
    /// @return true if new style, false if old style
    static bool isRevisionStyle() {
        return revisionStyle;
    }

    /// @brief gets the RAM capacity in bytes
    /// @return the RAM capacity in bytes
    static uint64_t getMemSize() {
        return memSize;
    }

    /// @brief gets the manufacturer
    /// @return the manufacturer code
    static int getManufacturer() {
        return manufacturer;
    }

    /// @brief gets the processor
    /// @return the processor code
    static int getProcessor() {
        return processor;
    }

    /// @brief gets the model
    /// @return the model code
    static int getModel() {
        return model;
    }

    /// @brief gets the revision number
    /// @return the revision number
    static int getRevision() {
        return revision;
    }

    static uint64_t getMAC() {
        return MAC;
    }

    static uint64_t getARM_MEM_START() {
        return ARM_MEM_START;
    }

    static uint64_t getARM_MEM_END() {
        return ARM_MEM_END;
    }

    static uint64_t getVC_MEM_START() {
        return VC_MEM_START;
    }

    static uint64_t getVC_MEM_END() {
        return VC_MEM_END;
    }

};
    


#endif