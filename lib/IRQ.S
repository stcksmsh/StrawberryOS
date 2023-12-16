/**
 * @file IRQ_S
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
.text

.globl enable_irq
enable_irq:
	msr daifclr, #0x2
	ret

.globl disable_irq
disable_irq:
	msr daifset, #0x2
	ret
