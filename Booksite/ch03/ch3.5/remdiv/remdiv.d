
remdiv.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <remdiv>:
   0:	f3 0f 1e fa          	endbr64 
   4:	48 89 f8             	mov    %rdi,%rax
   7:	49 89 d0             	mov    %rdx,%r8
   a:	48 99                	cqto   
   c:	48 f7 fe             	idiv   %rsi
   f:	49 89 00             	mov    %rax,(%r8)
  12:	48 89 11             	mov    %rdx,(%rcx)
  15:	c3                   	ret    
