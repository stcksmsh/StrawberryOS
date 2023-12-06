.text

.globl enable_irq
enable_irq:
	msr daifclr, #0x2
	ret

.globl disable_irq
disable_irq:
	msr daifset, #0x2
	ret
