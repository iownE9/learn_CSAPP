steve@Steve ~/l/L/s/l/B/lab2_handout (main)> gcc -o phase1 -g -std=c99 phase1.c
steve@Steve ~/l/L/s/l/B/lab2_handout (main)> ls
phase1  phase1.c  phase2.c  phase2.h
steve@Steve ~/l/L/s/l/B/lab2_handout (main)> gdb -q phase1
Reading symbols from phase1...
(gdb) break main
Breakpoint 1 at 0x13be: file phase1.c, line 55.
(gdb) break unscramble
Breakpoint 2 at 0x1318: file phase1.c, line 41.
(gdb) break reverse
Breakpoint 3 at 0x1284: file phase1.c, line 31.
(gdb) break toggleCase
Breakpoint 4 at 0x11f7: file phase1.c, line 20.
(gdb) info break
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x00000000000013be in main at phase1.c:55
2       breakpoint     keep y   0x0000000000001318 in unscramble at phase1.c:41
3       breakpoint     keep y   0x0000000000001284 in reverse at phase1.c:31
4       breakpoint     keep y   0x00000000000011f7 in toggleCase at phase1.c:20
(gdb) run
Starting program: /home/steve/learn_CSAPP/Lab/self-study/lab02-Bomb/Bootcamp 2 Debugging & GDB/lab2_handout/phase1
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Breakpoint 1, main () at phase1.c:55
55          word_t *secret_msg = (word_t *) calloc(1, sizeof(word_t));
(gdb) next
56          secret_msg->str = (char *) calloc(length, sizeof(char));
(gdb) next
57          strncpy(secret_msg->str, "!312 Av XPHy QBBt", length);;
(gdb) print *(word_t*)secret_msg
$1 = {str = 0x5555555592c0 "", len = 0}
(gdb) next
58          secret_msg->len = length;
(gdb) print *(word_t*)secret_msg
$2 = {str = 0x5555555592c0 "!312 Av XPHy QBBt", len = 0}
(gdb) continue
Continuing.

Breakpoint 2, unscramble (msg=0x5555555592a0) at phase1.c:41
41          char chng = 13;
(gdb) step
42          for (int i = 0; i < msg->len; i++) {
(gdb) next
43              ltr = msg->str[i];
(gdb) next
44              if (isAlpha(ltr)) {
(gdb) print ltr
$3 = 33 '!'
(gdb) print isAlpha(ltr)
$4 = false
(gdb) watch ltr
Hardware watchpoint 5: ltr
(gdb) continue
Continuing.

Hardware watchpoint 5: ltr

Old value = 33 '!'
New value = 51 '3'
unscramble (msg=0x5555555592a0) at phase1.c:44
44              if (isAlpha(ltr)) {
(gdb) step
isAlpha (ltr=51 '3') at phase1.c:14
14          bool soln = (('a' <= ltr && ltr <= 'z') || ('A' <= ltr && ltr <= 'Z'));
(gdb) backtrace
#0  isAlpha (ltr=51 '3') at phase1.c:14
#1  0x0000555555555345 in unscramble (msg=0x5555555592a0) at phase1.c:44
#2  0x0000555555555429 in main () at phase1.c:60
(gdb)
