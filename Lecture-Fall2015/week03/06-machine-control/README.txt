Extensions:
	.64s: x86-64 assembly code
	.64bs: x86-64 assembly code with conditional moves disabled
	.O1-64s: x86-64 assembly code compiled with -O1 optimization

FILES

control.c
control.s
control.bs
	Sample conditional operations

loop.c
loop.64s
loop.O1-64s
	Sample loops

switch.c
switch.64s
switch.64d
	Sample switch statement

*_mine 为自主添加文件
观察发现此情况下：其并未将switch 转换 跳转表