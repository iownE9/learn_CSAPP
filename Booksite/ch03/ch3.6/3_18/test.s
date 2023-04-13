	.file	"test.c"
	.text
	.globl	test
	.type	test, @function
test:
.LFB0:
	.cfi_startproc
	endbr64
	leaq	(%rdi,%rsi), %rax
	addq	%rdx, %rax
	cmpq	$-3, %rdi
	jge	.L2
	cmpq	%rdx, %rsi
	jge	.L3
	movq	%rdi, %rax
	imulq	%rsi, %rax
	ret
.L3:
	movq	%rsi, %rax
	imulq	%rdx, %rax
	ret
.L2:
	cmpq	$2, %rdi
	jle	.L1
	movq	%rdi, %rax
	imulq	%rdx, %rax
.L1:
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
