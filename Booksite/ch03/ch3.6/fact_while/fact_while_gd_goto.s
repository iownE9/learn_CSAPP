	.file	"fact_while_gd_goto.c"
	.text
	.globl	fact_while_gd_goto_gd_goto
	.type	fact_while_gd_goto_gd_goto, @function
fact_while_gd_goto_gd_goto:
.LFB0:
	.cfi_startproc
	endbr64
	cmpq	$1, %rdi
	jle	.L4
	movl	$1, %eax
.L3:
	imulq	%rdi, %rax
	subq	$1, %rdi
	cmpq	$1, %rdi
	jne	.L3
	ret
.L4:
	movl	$1, %eax
.L2:
	ret
	.cfi_endproc
.LFE0:
	.size	fact_while_gd_goto_gd_goto, .-fact_while_gd_goto_gd_goto
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
