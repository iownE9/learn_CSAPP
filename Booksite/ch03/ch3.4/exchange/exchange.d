
exchange.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <exchange>:
   0:	f3 0f 1e fa          	endbr64 
   4:	48 8b 07             	mov    (%rdi),%rax
   7:	48 89 37             	mov    %rsi,(%rdi)
   a:	c3                   	ret    
