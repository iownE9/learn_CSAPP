***********
自定义修改:
***********  
感谢 Kcxain 😘  
博客：<https://deconx.cn/blog>

<https://github.com/kcxain/CSAPP-Lab/tree/master/initial_labs/08_Malloc%20Lab>

下载traces/*文件,完善测试用例


修改 config.h   
	
	#define TRACEDIR "traces/"


#include <math.h>  
命令行最后 -lm   


三个版本都是简单实现,未进行性能优化

欲知后事如何,且见下回

有趣的是: mm-seglist  

改变类数量 测试出来性能不变  

#define SEGNUM 14    
/* 改为14个类 */

#####################################################################
# CS:APP Malloc Lab  
# Handout files for students
#
# Copyright (c) 2002, R. Bryant and D. O'Hallaron, All rights reserved.
# May not be used, modified, or copied without permission.
#
######################################################################

***********
Main Files:
***********

mm.{c,h}	  
	Your solution malloc package. mm.c is the file that you  
	will be handing in, and is the only file you should modify.  

mdriver.c	  
	The malloc driver that tests your mm.c file  

short{1,2}-bal.rep  
	Two tiny tracefiles to help you get started.   

Makefile	  
	Builds the driver  

**********************************
Other support files for the driver
**********************************

config.h	Configures the malloc lab driver  
fsecs.{c,h}	Wrapper function for the different timer packages  
clock.{c,h}	Routines for accessing the Pentium and Alpha cycle counters  
fcyc.{c,h}	Timer functions based on cycle counters  
ftimer.{c,h}	Timer functions based on interval timers and gettimeofday()  
memlib.{c,h}	Models the heap and sbrk function  

*******************************
Building and running the driver
*******************************
To build the driver, type "make" to the shell.

To run the driver on a tiny test trace:

	unix> mdriver -V -f short1-bal.rep

The -V option prints out helpful tracing and summary information.

To get a list of the driver flags:

	unix> mdriver -h

