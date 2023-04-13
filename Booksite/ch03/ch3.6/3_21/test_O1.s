	.file	"test.c"
	.text
	.globl	test
	.type	test, @function
test:
.LFB0:
	.cfi_startproc
	endbr64
	testq	%rsi, %rsi
	jle	.L2
	movq	%rsi, %rdx
	subq	%rdi, %rdx
	movq	%rdi, %rax
	andq	%rsi, %rax
	cmpq	%rsi, %rdi
	cmovl	%rdx, %rax
	ret
.L2:
	leaq	0(,%rdi,8), %rax
	addq	%rsi, %rdi
	cmpq	$-1, %rsi
	cmovl	%rdi, %rax
	ret
	.cfi_endproc
.LFE0:
	.size	test, .-test
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
