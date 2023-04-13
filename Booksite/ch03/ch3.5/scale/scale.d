
scale.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <scale>:
   0:	f3 0f 1e fa          	endbr64 
   4:	48 8d 04 b7          	lea    (%rdi,%rsi,4),%rax
   8:	48 8d 14 52          	lea    (%rdx,%rdx,2),%rdx
   c:	48 8d 04 90          	lea    (%rax,%rdx,4),%rax
  10:	c3                   	ret    
