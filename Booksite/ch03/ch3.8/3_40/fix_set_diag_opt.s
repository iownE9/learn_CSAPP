	.file	"fix_set_diag_opt.c"
	.text
	.globl	fix_set_diag_opt
	.type	fix_set_diag_opt, @function
fix_set_diag_opt:
.LFB0:
	.cfi_startproc
	endbr64
	movl	$0, %eax
.L2:
	movl	%esi, (%rdi,%rax,4)
	addq	$17, %rax
	cmpq	$272, %rax
	jne	.L2
	ret
	.cfi_endproc
.LFE0:
	.size	fix_set_diag_opt, .-fix_set_diag_opt
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
