	.file	"var_prod_ele.c"
	.text
	.globl	var_prod_ele
	.type	var_prod_ele, @function
var_prod_ele:
.LFB0:
	.cfi_startproc
	endbr64
	testq	%rdi, %rdi
	jle	.L4
	imulq	%rdi, %rcx
	leaq	(%rsi,%rcx,4), %r10
	leaq	0(,%rdi,4), %r9
	leaq	(%rdx,%r8,4), %rcx
	movl	$0, %esi
	movl	$0, %eax
.L3:
	movl	(%r10,%rax,4), %edx
	imull	(%rcx), %edx
	addl	%edx, %esi
	addq	$1, %rax
	addq	%r9, %rcx
	cmpq	%rax, %rdi
	jne	.L3
.L1:
	movl	%esi, %eax
	ret
.L4:
	movl	$0, %esi
	jmp	.L1
	.cfi_endproc
.LFE0:
	.size	var_prod_ele, .-var_prod_ele
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
