
arith.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <arith>:
   0:	f3 0f 1e fa          	endbr64 
   4:	48 31 f7             	xor    %rsi,%rdi
   7:	48 8d 04 52          	lea    (%rdx,%rdx,2),%rax
   b:	48 c1 e0 04          	shl    $0x4,%rax
   f:	81 e7 0f 0f 0f 0f    	and    $0xf0f0f0f,%edi
  15:	48 29 f8             	sub    %rdi,%rax
  18:	c3                   	ret    
