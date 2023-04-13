
3_9.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <shift_left4_rightn>:
   0:	f3 0f 1e fa          	endbr64 
   4:	48 89 f8             	mov    %rdi,%rax
   7:	48 c1 e0 04          	shl    $0x4,%rax
   b:	89 f1                	mov    %esi,%ecx
   d:	48 d3 f8             	sar    %cl,%rax
  10:	c3                   	ret    
