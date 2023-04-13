
arith2.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <arith2>:
   0:	f3 0f 1e fa          	endbr64 
   4:	48 09 f7             	or     %rsi,%rdi
   7:	48 c1 ff 03          	sar    $0x3,%rdi
   b:	48 f7 d7             	not    %rdi
   e:	48 89 d0             	mov    %rdx,%rax
  11:	48 29 f8             	sub    %rdi,%rax
  14:	c3                   	ret    
