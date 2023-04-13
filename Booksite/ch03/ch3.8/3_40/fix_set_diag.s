	.file	"fix_set_diag.c"
	.text
	.globl	fix_set_diag
	.type	fix_set_diag, @function
fix_set_diag:
.LFB0:
	.cfi_startproc
	endbr64
	movl	$0, %eax
	jmp	.L2
.L3:
	movq	%rax, %rdx
	salq	$6, %rdx
	addq	%rdi, %rdx
	movl	%esi, (%rdx,%rax,4)
	addq	$1, %rax
.L2:
	cmpq	$15, %rax
	jle	.L3
	ret
	.cfi_endproc
.LFE0:
	.size	fix_set_diag, .-fix_set_diag
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
