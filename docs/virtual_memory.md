# Virtual memory management in ARMv8
There exist 4 different Page Tables
Two for EL0/EL1, one for user and one for kernel space
One for EL2 and EL3 each
I will mostly be focusing on the EL0/1 virtual address space for now
This OS is using a 4KB granule size
### Kernel and user space
Kernel and user space are divided based on a variable length "prefix" (highest bits) of the virtual address, the default value is 16bits?
If they are all unset, we are referencing user space, if they are all set we are in kernel space, otherwise a **FAULT** is generated
Relevant Page Table Pointer Registers are:
> - `TTBR0_EL1` - responsible for virtual to physical mapping in user space
> - `TTBR1_EL1` - responsible for virtual to physical mapping in kernel space
### AArch64 descriptor format
The format is used in all levels of the table, from 0 to 3
Level 0 descriptors can only output the address of a level 1 table
Level 3 descriptors can not point to another pinter and must output block addresses

| VA[47:39] | VA[38:30] | VA[29:21] | VA[20:12] | VA[11:0] |
| --------- | --------- | --------- | --------- | -------- |
| Level 0 Table Index <br /> <br /> Pointer to L1 table<br />(no block entry) | Level 1 Table Index <br /> <br /> Pointer to L2 Table<br />Base address of 1GB block | Level 2 Table Index <br /> <br /> Pointer to L3 table<br />Base address of 2MB block | Level 3 Table Index <br /> <br /> Base address of 4KB block | Block offset and PA[11:0] |

Each level has 9 bits, and each level of table has 512 entries
