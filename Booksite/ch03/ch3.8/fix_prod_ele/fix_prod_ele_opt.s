	.file	"fix_prod_ele_opt.c"
	.text
	.globl	fix_prod_ele_opt
	.type	fix_prod_ele_opt, @function
fix_prod_ele_opt:
.LFB0:
	.cfi_startproc
	endbr64
	salq	$6, %rdx
	addq	%rdx, %rdi
	salq	$2, %rcx
	leaq	(%rsi,%rcx), %rax
	leaq	1024(%rsi,%rcx), %rsi
	movl	$0, %ecx
.L2:
	movl	(%rax), %edx
	imull	(%rdi), %edx
	addl	%edx, %ecx
	addq	$4, %rdi
	addq	$64, %rax
	cmpq	%rax, %rsi
	jne	.L2
	movl	%ecx, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	fix_prod_ele_opt, .-fix_prod_ele_opt
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
