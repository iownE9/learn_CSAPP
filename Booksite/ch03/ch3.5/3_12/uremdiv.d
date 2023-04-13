
uremdiv.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <uremdiv>:
   0:	f3 0f 1e fa          	endbr64 
   4:	48 89 f8             	mov    %rdi,%rax
   7:	49 89 d0             	mov    %rdx,%r8
   a:	ba 00 00 00 00       	mov    $0x0,%edx
   f:	48 f7 f6             	div    %rsi
  12:	49 89 00             	mov    %rax,(%r8)
  15:	48 89 11             	mov    %rdx,(%rcx)
  18:	c3                   	ret    
