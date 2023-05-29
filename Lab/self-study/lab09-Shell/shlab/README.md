################
CS:APP Shell Lab
################

*对于数据竞争的测试感觉不完善*

*对于信号屏蔽,欢迎更 elegant 的方案,我的也可能存在bug,欢迎指正 :)*

*review*  
```
子进程终止或停止,发送SIGCHLD给父进程  
ctrl+C 发送SIGINT给前台进程组   
ctrl+Z 发送SIGSTP给前台进程组  
进程A 发送SIGKILL给进程B,使B终止  
int kill(pid_t pid, int sig) 发送信号sig给pid进程  
SIGCONT 继续进程如果该进程停止
```

没有标准API的输出样例,需要自己 ./tshref 运行一个个试 倒推  每种情况输出样例的位置次序

整体不难,就是麻烦

my method: 除添加job外，其余对 jobs 的操作都封装在信号处理程序内 - "加锁"

不完善之处:  
信号处理程序没用异步信号安全的 Sio_puts()  Sio_putl()   
-v 模式下的输出可能与ref有出入   


*lab 是个好 lab 就是资料太老且要求不明确,CMU还不公开全部,怀念CS61a*


退出时无需回收：
```
steve@Steve ~/l/L/s/l/shlab (main)> ./tshref -v
tsh> ./myspin 80 &
Added job [1] 10642 ./myspin 80 &

[1] (10642) ./myspin 80 &
tsh> /bin/ps w
Added job [2] 10643 /bin/ps w

    PID TTY      STAT   TIME COMMAND
  10439 pts/0    Ss     0:00 -sh
  10492 pts/0    S      0:00 fish
  10641 pts/0    S+     0:00 ./tshref -v
  10642 pts/0    S      0:00 ./myspin 80
  10643 pts/0    R      0:00 /bin/ps w
sigchld_handler: entering
sigchld_handler: Job [2] (10643) deleted
sigchld_handler: Job [2] (10643) terminates OK (status 0)
sigchld_handler: exiting
waitfg: Process (10643) no longer the fg process
tsh> quit # 直接退出，没有信号处理程序的调用
steve@Steve ~/l/L/s/l/shlab (main)> ps w
    PID TTY      STAT   TIME COMMAND
  10439 pts/0    Ss     0:00 -sh
  10492 pts/0    Sl     0:00 fish
  10642 pts/0    S      0:00 ./myspin 80 # 后台依旧运行
  10656 pts/0    R+     0:00 ps w
steve@Steve ~/l/L/s/l/shlab (main)>

```

Files:

Makefile	# Compiles your shell program and runs the tests
README		# This file
tsh.c		# The shell program that you will write and hand in
tshref		# The reference shell binary.

# The remaining files are used to test your shell
sdriver.pl	# The trace-driven shell driver
trace*.txt	# The 15 trace files that control the shell driver
tshref.out 	# Example output of the reference shell on all 15 traces

# Little C programs that are called by the trace files
myspin.c	# Takes argument <n> and spins for <n> seconds
mysplit.c	# Forks a child that spins for <n> seconds
mystop.c        # Spins for <n> seconds and sends SIGTSTP to itself
myint.c         # Spins for <n> seconds and sends SIGINT to itself

