
get_line.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <get_line>:
   0:	f3 0f 1e fa          	endbr64 
   4:	55                   	push   %rbp
   5:	53                   	push   %rbx
   6:	48 83 ec 18          	sub    $0x18,%rsp
   a:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  11:	00 00 
  13:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  18:	31 c0                	xor    %eax,%eax
  1a:	48 8d 6c 24 04       	lea    0x4(%rsp),%rbp
  1f:	48 89 ef             	mov    %rbp,%rdi
  22:	e8 00 00 00 00       	call   27 <get_line+0x27>
  27:	48 89 ef             	mov    %rbp,%rdi
  2a:	e8 00 00 00 00       	call   2f <get_line+0x2f>
  2f:	48 89 c7             	mov    %rax,%rdi
  32:	e8 00 00 00 00       	call   37 <get_line+0x37>
  37:	48 89 c3             	mov    %rax,%rbx
  3a:	48 89 ee             	mov    %rbp,%rsi
  3d:	48 89 c7             	mov    %rax,%rdi
  40:	e8 00 00 00 00       	call   45 <get_line+0x45>
  45:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  4a:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
  51:	00 00 
  53:	75 0a                	jne    5f <get_line+0x5f>
  55:	48 89 d8             	mov    %rbx,%rax
  58:	48 83 c4 18          	add    $0x18,%rsp
  5c:	5b                   	pop    %rbx
  5d:	5d                   	pop    %rbp
  5e:	c3                   	ret    
  5f:	e8 00 00 00 00       	call   64 <get_line2>

0000000000000064 <get_line2>:
  64:	f3 0f 1e fa          	endbr64 
  68:	53                   	push   %rbx
  69:	48 83 ec 10          	sub    $0x10,%rsp
  6d:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  74:	00 00 
  76:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  7b:	31 c0                	xor    %eax,%eax
  7d:	48 8d 5c 24 04       	lea    0x4(%rsp),%rbx
  82:	48 89 df             	mov    %rbx,%rdi
  85:	e8 00 00 00 00       	call   8a <get_line2+0x26>
  8a:	48 89 df             	mov    %rbx,%rdi
  8d:	e8 00 00 00 00       	call   92 <get_line2+0x2e>
  92:	48 8d 78 01          	lea    0x1(%rax),%rdi
  96:	e8 00 00 00 00       	call   9b <get_line2+0x37>
  9b:	48 89 c3             	mov    %rax,%rbx
  9e:	48 85 c0             	test   %rax,%rax
  a1:	74 12                	je     b5 <get_line2+0x51>
  a3:	48 8d 74 24 04       	lea    0x4(%rsp),%rsi
  a8:	ba 04 00 00 00       	mov    $0x4,%edx
  ad:	48 89 c7             	mov    %rax,%rdi
  b0:	e8 00 00 00 00       	call   b5 <get_line2+0x51>
  b5:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  ba:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
  c1:	00 00 
  c3:	75 09                	jne    ce <get_line2+0x6a>
  c5:	48 89 d8             	mov    %rbx,%rax
  c8:	48 83 c4 10          	add    $0x10,%rsp
  cc:	5b                   	pop    %rbx
  cd:	c3                   	ret    
  ce:	e8 00 00 00 00       	call   d3 <get_line2+0x6f>
