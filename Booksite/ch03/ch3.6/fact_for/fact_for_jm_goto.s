	.file	"fact_for_jm_goto.c"
	.text
	.globl	fact_for_jm_goto_jm_goto
	.type	fact_for_jm_goto_jm_goto, @function
fact_for_jm_goto_jm_goto:
.LFB0:
	.cfi_startproc
	endbr64
	movl	$1, %edx
	movl	$2, %eax
	jmp	.L2
.L4:
	imulq	%rax, %rdx
	addq	$1, %rax
.L2:
	cmpq	%rdi, %rax
	jle	.L4
	movq	%rdx, %rax
	ret
	.cfi_endproc
.LFE0:
	.size	fact_for_jm_goto_jm_goto, .-fact_for_jm_goto_jm_goto
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
