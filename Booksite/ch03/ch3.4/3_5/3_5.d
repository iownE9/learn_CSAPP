
3_5.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <decode1>:
   0:	f3 0f 1e fa          	endbr64 
   4:	4c 8b 07             	mov    (%rdi),%r8
   7:	48 8b 0e             	mov    (%rsi),%rcx
   a:	48 8b 02             	mov    (%rdx),%rax
   d:	4c 89 06             	mov    %r8,(%rsi)
  10:	48 89 0a             	mov    %rcx,(%rdx)
  13:	48 89 07             	mov    %rax,(%rdi)
  16:	c3                   	ret    
