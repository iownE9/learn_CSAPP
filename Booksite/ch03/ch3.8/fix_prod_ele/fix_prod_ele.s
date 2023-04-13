	.file	"fix_prod_ele.c"
	.text
	.globl	fix_prod_ele
	.type	fix_prod_ele, @function
fix_prod_ele:
.LFB0:
	.cfi_startproc
	endbr64
	movq	%rdi, %r9
	movq	%rsi, %r10
	movl	$0, %r8d
	movl	$0, %eax
	jmp	.L2
.L3:
	movq	%rdx, %rdi
	salq	$6, %rdi
	addq	%r9, %rdi
	movq	%rax, %rsi
	salq	$6, %rsi
	addq	%r10, %rsi
	movl	(%rsi,%rcx,4), %esi
	imull	(%rdi,%rax,4), %esi
	addl	%esi, %r8d
	addq	$1, %rax
.L2:
	cmpq	$15, %rax
	jle	.L3
	movl	%r8d, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	fix_prod_ele, .-fix_prod_ele
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
