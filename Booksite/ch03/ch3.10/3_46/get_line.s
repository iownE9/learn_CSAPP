	.file	"get_line.c"
	.text
	.globl	get_line
	.type	get_line, @function
get_line:
.LFB51:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	leaq	4(%rsp), %rbp
	movq	%rbp, %rdi
	call	gets@PLT
	movq	%rbp, %rdi
	call	strlen@PLT
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, %rbx
	movq	%rbp, %rsi
	movq	%rax, %rdi
	call	strcpy@PLT
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L4
	movq	%rbx, %rax
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L4:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE51:
	.size	get_line, .-get_line
	.globl	get_line2
	.type	get_line2, @function
get_line2:
.LFB52:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	leaq	4(%rsp), %rbx
	movq	%rbx, %rdi
	call	gets@PLT
	movq	%rbx, %rdi
	call	strlen@PLT
	leaq	1(%rax), %rdi
	call	malloc@PLT
	movq	%rax, %rbx
	testq	%rax, %rax
	je	.L5
	leaq	4(%rsp), %rsi
	movl	$4, %edx
	movq	%rax, %rdi
	call	strncpy@PLT
.L5:
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L9
	movq	%rbx, %rax
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L9:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE52:
	.size	get_line2, .-get_line2
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
