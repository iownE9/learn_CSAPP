	.file	"union_get.c"
	.text
	.globl	get1
	.type	get1, @function
get1:
.LFB0:
	.cfi_startproc
	endbr64
	movq	(%rdi), %rax
	movq	%rax, (%rsi)
	ret
	.cfi_endproc
.LFE0:
	.size	get1, .-get1
	.globl	get2
	.type	get2, @function
get2:
.LFB1:
	.cfi_startproc
	endbr64
	movzwl	8(%rdi), %eax
	movw	%ax, (%rsi)
	ret
	.cfi_endproc
.LFE1:
	.size	get2, .-get2
	.globl	get3
	.type	get3, @function
get3:
.LFB2:
	.cfi_startproc
	endbr64
	addq	$10, %rdi
	movq	%rdi, (%rsi)
	ret
	.cfi_endproc
.LFE2:
	.size	get3, .-get3
	.globl	get4
	.type	get4, @function
get4:
.LFB3:
	.cfi_startproc
	endbr64
	movq	%rdi, (%rsi)
	ret
	.cfi_endproc
.LFE3:
	.size	get4, .-get4
	.globl	get5
	.type	get5, @function
get5:
.LFB4:
	.cfi_startproc
	endbr64
	movq	(%rdi), %rax
	movl	(%rdi,%rax,4), %eax
	movl	%eax, (%rsi)
	ret
	.cfi_endproc
.LFE4:
	.size	get5, .-get5
	.globl	get6
	.type	get6, @function
get6:
.LFB5:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movzbl	(%rax), %eax
	movb	%al, (%rsi)
	ret
	.cfi_endproc
.LFE5:
	.size	get6, .-get6
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
