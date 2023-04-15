
activity-nsp.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <win>:
   0:	f3 0f 1e fa          	endbr64 
   4:	48 83 ec 08          	sub    $0x8,%rsp
   8:	81 ff 13 52 01 00    	cmp    $0x15213,%edi
   e:	74 2e                	je     3e <win+0x3e>
  10:	81 ff 13 82 01 00    	cmp    $0x18213,%edi
  16:	74 34                	je     4c <win+0x4c>
  18:	81 ff 13 86 01 00    	cmp    $0x18613,%edi
  1e:	74 3a                	je     5a <win+0x5a>
  20:	8b 05 00 00 00 00    	mov    0x0(%rip),%eax        # 26 <win+0x26>
  26:	3d 13 55 01 00       	cmp    $0x15513,%eax
  2b:	74 3b                	je     68 <win+0x68>
  2d:	48 8d 3d 00 00 00 00 	lea    0x0(%rip),%rdi        # 34 <win+0x34>
  34:	e8 00 00 00 00       	call   39 <win+0x39>
  39:	48 83 c4 08          	add    $0x8,%rsp
  3d:	c3                   	ret    
  3e:	48 8d 3d 00 00 00 00 	lea    0x0(%rip),%rdi        # 45 <win+0x45>
  45:	e8 00 00 00 00       	call   4a <win+0x4a>
  4a:	eb ed                	jmp    39 <win+0x39>
  4c:	48 8d 3d 00 00 00 00 	lea    0x0(%rip),%rdi        # 53 <win+0x53>
  53:	e8 00 00 00 00       	call   58 <win+0x58>
  58:	eb df                	jmp    39 <win+0x39>
  5a:	48 8d 3d 00 00 00 00 	lea    0x0(%rip),%rdi        # 61 <win+0x61>
  61:	e8 00 00 00 00       	call   66 <win+0x66>
  66:	eb d1                	jmp    39 <win+0x39>
  68:	48 8d 3d 00 00 00 00 	lea    0x0(%rip),%rdi        # 6f <win+0x6f>
  6f:	e8 00 00 00 00       	call   74 <win+0x74>
  74:	eb c3                	jmp    39 <win+0x39>

0000000000000076 <solve>:
  76:	f3 0f 1e fa          	endbr64 
  7a:	48 83 ec 38          	sub    $0x38,%rsp
  7e:	48 c7 44 24 28 b4 00 	movq   $0xb4,0x28(%rsp)
  85:	00 00 
  87:	48 c7 44 24 08 af 00 	movq   $0xaf,0x8(%rsp)
  8e:	00 00 
  90:	48 8d 7c 24 10       	lea    0x10(%rsp),%rdi
  95:	e8 00 00 00 00       	call   9a <solve+0x24>
  9a:	48 8b 54 24 28       	mov    0x28(%rsp),%rdx
  9f:	48 b8 31 35 32 31 33 	movabs $0x3331323531,%rax
  a6:	00 00 00 
  a9:	48 39 c2             	cmp    %rax,%rdx
  ac:	74 19                	je     c7 <solve+0x51>
  ae:	48 8b 54 24 08       	mov    0x8(%rsp),%rdx
  b3:	48 b8 31 38 32 31 33 	movabs $0x3331323831,%rax
  ba:	00 00 00 
  bd:	48 39 c2             	cmp    %rax,%rdx
  c0:	74 11                	je     d3 <solve+0x5d>
  c2:	48 83 c4 38          	add    $0x38,%rsp
  c6:	c3                   	ret    
  c7:	bf 13 52 01 00       	mov    $0x15213,%edi
  cc:	e8 00 00 00 00       	call   d1 <solve+0x5b>
  d1:	eb db                	jmp    ae <solve+0x38>
  d3:	bf 13 82 01 00       	mov    $0x18213,%edi
  d8:	e8 00 00 00 00       	call   dd <solve+0x67>
  dd:	eb e3                	jmp    c2 <solve+0x4c>

00000000000000df <main>:
  df:	f3 0f 1e fa          	endbr64 
  e3:	48 83 ec 08          	sub    $0x8,%rsp
  e7:	48 8b 35 00 00 00 00 	mov    0x0(%rip),%rsi        # ee <main+0xf>
  ee:	48 8d 3d 00 00 00 00 	lea    0x0(%rip),%rdi        # f5 <main+0x16>
  f5:	e8 00 00 00 00       	call   fa <main+0x1b>
  fa:	48 8d 3d 00 00 00 00 	lea    0x0(%rip),%rdi        # 101 <main+0x22>
 101:	e8 00 00 00 00       	call   106 <main+0x27>
 106:	b8 00 00 00 00       	mov    $0x0,%eax
 10b:	48 83 c4 08          	add    $0x8,%rsp
 10f:	c3                   	ret    
