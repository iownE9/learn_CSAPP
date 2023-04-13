	.file	"fact_for_gd_goto.c"
	.text
	.globl	fact_for_gd_goto
	.type	fact_for_gd_goto, @function
fact_for_gd_goto:
.LFB0:
	.cfi_startproc
	endbr64
	cmpq	$1, %rdi
	jle	.L4
	movl	$1, %edx
	movl	$2, %eax
.L3:
	addq	$1, %rdx
	addq	$1, %rax
	cmpq	%rax, %rdi
	jge	.L3
.L1:
	movq	%rdx, %rax
	ret
.L4:
	movl	$1, %edx
.L2:
	jmp	.L1
	.cfi_endproc
.LFE0:
	.size	fact_for_gd_goto, .-fact_for_gd_goto
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
