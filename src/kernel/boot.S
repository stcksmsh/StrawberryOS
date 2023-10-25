.section ".text.boot"  // Make sure the linker puts this at the start of the kernel image

.global _start  // Execution starts here

_start:
    mrs     x1, mpidr_el1
    and     x1, x1, #3 // Check processor ID
    cbz     x1, master // If 0 then it is the master core, so branch to `master`
    // We're not on the main core, so hang in an infinite wait loop
hault_core: wfe
    b       hault_core // infinite loop
master:  // We're on the main core!
    // Set stack to start below our code
    ldr     x1, =_start
    mov     sp, x0

    // Clean the BSS section
    ldr     x1, =__bss_start    // Start address
    ldr     x2, =__bss_size     // Size of the section
memzero:  cbz     x2, jumpToMain      // Quit loop if zero
    str     xzr, [x1], #8
    sub     x2, x2, #1
    b memzero

    // Jump to our main() routine in C (make sure it doesn't return)
jumpToMain:  bl      main
    // In case it does return, halt the master core too
    b jumpToMain
