ExceptionHandler - Handles exceptions, that includes synchronous exceptions, system errors as well as non implemented exceptions
ExceptionHandler - Handles exceptions, used in vector.S
FrameBuffer - Currently not implemented
HeapAllocator - Handles a heap, allocating, reallocating and freeing memory from it, the method `init` must be called to set it up
InterruptHandler - Handles interrupts (IRQs)
Kernel - The '*main*' class of the OS, handles everything aside from bootstrapping and system initialisation
MachineInfo - Used to fetch and store data on the host machine from the VideoCore (see mailbox)
Mailbox - Used to interface with the mailboxes present on the machine, see [maillbox.md](mailbox.md)
MemoryManager - Used to manage all memory of the system, has one(for \<=1GB systems) or more HeapAllocators, handles heap alloc,realloc,free, page alloc, etc. uses MMU (if flag is set and method `enableMMU` invoked)
MiniUart - Used to interface with the devices MiniUART device (since I developed everything on the RPi4B, i used its pins etc, am not sure if this will work on another device)
PageAllocator - Handles page allocation, freeing etc.
TranslationTable - Used to manage the translation tables. Currently VMEM is not supported so the class does not see any use
