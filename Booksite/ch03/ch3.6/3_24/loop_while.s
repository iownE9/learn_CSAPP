	.file	"loop_while.c"
	.text
	.globl	loop_while
	.type	loop_while, @function
loop_while:
.LFB0:
	.cfi_startproc
	endbr64
	movl	$1, %eax
	jmp	.L2
.L3:
	leaq	(%rdi,%rsi), %rdx
	imulq	%rdx, %rax
	addq	$1, %rdi
.L2:
	cmpq	%rsi, %rdi
	jl	.L3
	ret
	.cfi_endproc
.LFE0:
	.size	loop_while, .-loop_while
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
