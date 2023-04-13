	.file	"intlen.c"
	.text
	.globl	len
	.type	len, @function
len:
.LFB51:
	.cfi_startproc
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	call	strlen@PLT
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE51:
	.size	len, .-len
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%ld"
	.text
	.globl	iptoa
	.type	iptoa, @function
iptoa:
.LFB52:
	.cfi_startproc
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movq	(%rsi), %r8
	leaq	.LC0(%rip), %rcx
	movq	$-1, %rdx
	movl	$1, %esi
	movl	$0, %eax
	call	__sprintf_chk@PLT
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE52:
	.size	iptoa, .-iptoa
	.globl	intlen
	.type	intlen, @function
intlen:
.LFB53:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$32, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	movq	%rdi, (%rsp)
	movq	%rsp, %rsi
	leaq	12(%rsp), %rbx
	movq	%rbx, %rdi
	call	iptoa
	movq	%rbx, %rdi
	call	len
	movq	24(%rsp), %rdx
	subq	%fs:40, %rdx
	jne	.L8
	addq	$32, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L8:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE53:
	.size	intlen, .-intlen
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
