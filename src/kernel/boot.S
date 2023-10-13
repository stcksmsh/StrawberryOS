.section ".text.boot"

.global _start

_start:
    /* 
    |   This part will turn of all cores that are not core number 0
    */
    mrc p15, #0, r1, c0, c0, #5 // fetch current core number to r1?? pretty sure
    and r1, r1, #3 // make it only show the last two bits (0..3)
    cmp r1, #0 // is it 0?
    bne halt // if it is not HALT

    mov sp, #0x8000

    ldr r4, =__bss_start
    ldr r9, =__bss_end
    mov r5, #0
    mov r6, #0
    mov r7, #0
    mov r8, #0
    b       2f

1:
    stmia r4!, {r5-r8}

2:
    cmp r4, r9
    blo 1b

    ldr r3, =kernel_main
    blx r3

halt:
    wfe
    b halt