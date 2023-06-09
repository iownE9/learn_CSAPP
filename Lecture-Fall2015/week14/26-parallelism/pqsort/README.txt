This directory contains all of the code required to create a parallel
version of quicksort based on pthreads.  It is based on code developed
for the Fall, 2010 offering of 15-213/18-243, but with subsequent
refinements.

Files:
	csapp.{c,h}:	  Standard routines from CS:APP
	realtimer.{c,h}:  Code to compute elapsed time for program.
	taskq.{c,h}:	  Implementation of a multi-threaded task queue
	qsort.{c,h}:	  Serial & parallel quicksort implementation
	sortbench.c:	  Benchmarking program.
	sortbench-run.pl: Run tests and collect data
	Makefile

Make ERROR:  
/usr/bin/ld: csapp.o: relocation R_X86_64_32 against `.rodata.str1.1' can not be used when making a PIE object; recompile with -fPIE   
/usr/bin/ld: failed to set dynamic section sizes: bad value  
collect2: error: ld returned 1 exit status  
make: *** [Makefile:23: sortbench] Error 1  

	
