# Virtual memory management in ARMv8
There exist 4 different Page Tables Base Registers
Two for EL0/EL1, one for user and one for kernel space
One for EL2 and EL3 each
I will mostly be focusing on the EL0/1 virtual address space for now
This OS is using a 4KB granule size, and as such all information below pertains to that granule size
## Kernel and user space
Kernel and user space are divided based on a variable length "prefix" (highest bits) of the virtual address, the default value is 16bits?
If they are all unset, we are referencing user space, if they are all set we are in kernel space, otherwise a **FAULT** is generated
Relevant Page Table Pointer Registers are:
> - `TTBR0_EL1` - responsible for virtual to physical mapping in user space
> - `TTBR1_EL1` - responsible for virtual to physical mapping in kernel space
## AArch64 descriptor format
The format is used in all levels of the table, from 0 to 3
Level 0 descriptors can only output the address of a level 1 table
Level 3 descriptors can not point to another pinter and must output block addresses

| VA[47:39] | VA[38:30] | VA[29:21] | VA[20:12] | VA[11:0] |
| --------- | --------- | --------- | --------- | -------- |
| Level 0 Table Index <br /> <br /> Pointer to L1 table<br />(no block entry) | Level 1 Table Index <br /> <br /> Pointer to L2 Table<br />Base address of 1GB block | Level 2 Table Index <br /> <br /> Pointer to L3 table<br />Base address of 2MB block | Level 3 Table Index <br /> <br /> Base address of 4KB block | Block offset and PA[11:0] |

Each level has 9 bits for the entry index in the VA, and each level of table has 512 entries

### Format of Page Table Descriptors with granule size 4KB

All descriptors are 64bits wide
Bit 0 in all descriptors is the Valid bit, if unset the descriptor is not valid
Bit 1 in all descriptors is the Type bit, if set the descriptor is a Table descriptor, and if unset it is a Block descriptor
For a L0 descriptor to be valid the Type bit must be set
For a L3 descriptor to be valid, the Type bit must not be set

#### Table descriptors

The table descriptors have the following structure:

| 63 | 62:61 | 60 | 59 | 58:51 | 50:48 | 47:12 | 11:2 | 1 | 0 |
| -- | ----- | -- | -- | ----- | ----- | ----- | ---- | - | - |
| NS | AP | (U)XN | PXN | Ignored | Reserved | Address | Ignored | Type | Valid |

Fields have the following meanings:
> - NS - Non-Secure
>> - In L1 in Secure State, this bit determines the IPA or PA address space used for translation tables in subsequent lookup levels, for more information see page D8-5867 of the *Arm Architecture Reference Manual for A-profile Architecture*
>> - In all other translation stages and states, this bit is **RESERVED**
> - AP - Access Permission bits, they control permissions limits for subsequent translation levels in unprivileged (EL0) and privileged (EL1/2/3) modes. The following table shows the AP bit settings:
>> | AP | EL0 | EL1/2/3 |
>> | -- | --- | ------- |
>> | 00 | No access | Read/Write |
>> | 01 | Read/Write | Read/Write |
>> | 10 | No access | Read only |
>> | 11 | Read only | Read only |
>>
>> Only applicable in L1, in L2 or L3 these bits are **RESERVED**
> - (U)XN - (User) eXecute Never, if set then code can not be executed from the page in Unprivileged/User (EL0) mode
> - PXN - Privileged eXecute Never, if set then code can not be executed from the page in Privileged (EL1/2/3) mode
> - Address - Address of the following page table

In L2, bits 63:59, that is fields: NX, AP, (U)XN and PXN are **RESERVED**

#### Block descriptors

The block descriptors have the following structure:

##### L1

| 63 | 62:59 | 58:55 | 54 | 53 | 52 | 51 | 50 | 49:48 | 47:30 | 29:12 | 11 | 10 | 9:8 | 7:6 | 5 | 4:2 | 1 | 0 |
| -- | ----- | ----- | -- | -- | -- | -- | -- | ----- | ----- | ----- | -- | -- | --- | --- | - | --- | - | - |
| Reserved | PBHA | Ignored | (U)XN | PXN | Contiguous | DBM | GP | Reserved | Address | Reserved | nG | AF | SH | AP | NS | AttrIndx | Type | Valid |

L1 block descriptors are used for 1GB blocks

##### L2 

| 63 | 62:59 | 58:55 | 54 | 53 | 52 | 51 | 50 | 49:48 | 47:21 | 20:12 | 11 | 10 | 9:8 | 7:6 | 5 | 4:2 | 1 | 0 |
| -- | ----- | ----- | -- | -- | -- | -- | -- | ----- | ----- | ----- | -- | -- | --- | --- | - | --- | - | - |
| Reserved | PBHA | Ignored | (U)XN | PXN | Contiguous | DBM | GP | Reserved | Address | Reserved | nG | AF | SH | AP | NS | MemAttr | Type | Valid |

L2 block descriptors are used for 2MB blocks

#### Page descriptors

Page descriptors are the only valid L3 descriptors:

| 63:59 | 58:55 | 54 | 53 | 52 | 51:48 | 47:12 | 11 | 10 | 9:8 | 7:6 | 5 | 4:2 | 1 | 0 |
| ----- | ----- | -- | -- | -- | ----- | ----- | -- | -- | --- | --- | - | --- | - | - |
| Ignored | Reserved | (U)XN | PXN | Contiguous | Reserved | Address | nG | AD | SH | AP | NS | MemAttr | Type | Valid |

