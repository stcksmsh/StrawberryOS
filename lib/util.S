.section .text

.global memset
.type memset, function
memset:
        tst	x0, #7
        b.ne	2f
        cmp	x2, #16
        b.lo	6f

        orr	w8, w1, w1, lsl #8
        orr	w9, w8, w8, lsl #16
        mov	x10, x0

1:	    stp	w9, w9, [x10]
        add	x8, x10, #16
        sub	x2, x2, #16
        cmp	x2, #15
        stp	w9, w9, [x10, #8]
        mov	x10, x8
        b.hi	1b
        b	3f

2:	    mov	x8, x0
3:	    cbz	x2, 5f

4:	    subs	x2, x2, #1
	    strb	w1, [x8], #1
	    b.ne	4b

5:	    ret

6:	    mov	x8, x0
        cbnz	x2, 4b
        b	5b
