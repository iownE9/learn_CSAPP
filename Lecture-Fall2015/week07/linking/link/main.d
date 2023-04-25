
main.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <set_global>:
   0:	f3 0f 1e fa          	endbr64 
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	89 7d fc             	mov    %edi,-0x4(%rbp)
   b:	8b 45 fc             	mov    -0x4(%rbp),%eax
   e:	89 05 00 00 00 00    	mov    %eax,0x0(%rip)        # 14 <set_global+0x14>
  14:	90                   	nop
  15:	5d                   	pop    %rbp
  16:	c3                   	ret    

0000000000000017 <main>:
  17:	f3 0f 1e fa          	endbr64 
  1b:	55                   	push   %rbp
  1c:	48 89 e5             	mov    %rsp,%rbp
  1f:	8b 05 00 00 00 00    	mov    0x0(%rip),%eax        # 25 <main+0xe>
  25:	89 c6                	mov    %eax,%esi
  27:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 2e <main+0x17>
  2e:	48 89 c7             	mov    %rax,%rdi
  31:	b8 00 00 00 00       	mov    $0x0,%eax
  36:	e8 00 00 00 00       	call   3b <main+0x24>
  3b:	bf 6d 3b 00 00       	mov    $0x3b6d,%edi
  40:	e8 bb ff ff ff       	call   0 <set_global>
  45:	8b 05 00 00 00 00    	mov    0x0(%rip),%eax        # 4b <main+0x34>
  4b:	89 c6                	mov    %eax,%esi
  4d:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 54 <main+0x3d>
  54:	48 89 c7             	mov    %rax,%rdi
  57:	b8 00 00 00 00       	mov    $0x0,%eax
  5c:	e8 00 00 00 00       	call   61 <main+0x4a>
  61:	b8 00 00 00 00       	mov    $0x0,%eax
  66:	5d                   	pop    %rbp
  67:	c3                   	ret    
