/*
 * tsh - A tiny shell program with job control
 *
 * Hanlei
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/* Misc manifest constants */
#define MAXLINE 1024   /* max line size */
#define MAXARGS 128    /* max args on a command line */
#define MAXJOBS 16     /* max jobs at any point in time */
#define MAXJID 1 << 16 /* max job ID */

/* Job states */
#define UNDEF 0 /* undefined */
#define FG 1    /* running in foreground */
#define BG 2    /* running in background */
#define ST 3    /* stopped */

/*
 * Jobs states: FG (foreground), BG (background), ST (stopped)
 * Job state transitions and enabling actions:
 *     FG -> ST  : ctrl-z
 *     ST -> FG  : fg command
 *     ST -> BG  : bg command
 *     BG -> FG  : fg command
 * At most 1 job can be in the FG state.
 */

/* Global variables */
extern char **environ;   /* defined in libc */
char prompt[] = "tsh> "; /* command line prompt (DO NOT CHANGE) */
int verbose = 0;         /* if true, print additional output */
int nextjid = 1;         /* next job ID to allocate */
char sbuf[MAXLINE];      /* for composing sprintf messages */

struct job_t
{                          /* The job struct */
    pid_t pid;             /* job PID */
    int jid;               /* job ID [1, 2, ...] */
    int state;             /* UNDEF, BG, FG, or ST */
    char cmdline[MAXLINE]; /* command line */
};
struct job_t jobs[MAXJOBS]; /* The job list */
/* End global variables */

/* Function prototypes */

/* Here are the functions that you will implement */
void eval(char *cmdline);
int builtin_cmd(char **argv);
void do_bgfg(char **argv);
void waitfg(pid_t pid);

void sigchld_handler(int sig);
void sigtstp_handler(int sig);
void sigint_handler(int sig);

/* Here are helper routines that we've provided for you */
int parseline(const char *cmdline, char **argv);
void sigquit_handler(int sig);

void clearjob(struct job_t *job);
void Clearjob(struct job_t *job);
void initjobs(struct job_t *jobs);
int maxjid(struct job_t *jobs);
int addjob(struct job_t *jobs, pid_t pid, int state, char *cmdline);
void Addjob(pid_t pid, int state, char *cmdline); // custom
int deletejob(struct job_t *jobs, pid_t pid);
void Deletejob(pid_t pid); // custom
pid_t fgpid(struct job_t *jobs);
struct job_t *getjobpid(struct job_t *jobs, pid_t pid);
struct job_t *Getjobpid(pid_t pid); // custom
struct job_t *getjobjid(struct job_t *jobs, int jid);
struct job_t *Getjobjid(pid_t jid); // custom
int pid2jid(pid_t pid);
void listjobs(struct job_t *jobs);

void usage(void);
void unix_error(char *msg);
void app_error(char *msg);
typedef void handler_t(int);
handler_t *Signal(int signum, handler_t *handler);

/*********************************************
 * 摘自 csapp.c 的错误处理 包装函数
 ********************************************/
void Sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
void Sigemptyset(sigset_t *set);
void Sigdelset(sigset_t *set, int signum);
void Sigaddset(sigset_t *set, int signum);
void Sigfillset(sigset_t *set);
pid_t Fork(void);
void Execve(const char *filename, char *const argv[], char *const envp[]);
void Sigsuspend(const sigset_t *set);
pid_t Wait(int *status);
// pid_t Waitpid(pid_t pid, int *iptr, int options);
void Kill(pid_t pid, int signum);

static void sio_ltoa(long v, char s[], int b);
static size_t sio_strlen(char s[]);
ssize_t sio_puts(char s[]); /* Put string */
ssize_t sio_putl(long v);   /* Put long */
void sio_error(char s[]);   /* Put error message and exit */
ssize_t Sio_putl(long v);
ssize_t Sio_puts(char s[]);
void Sio_error(char s[]);
static size_t sio_strlen(char s[]);
static void sio_reverse(char s[]);
/*
 * main - The shell's main routine
 */
int main(int argc, char **argv)
{
    char c;
    char cmdline[MAXLINE];
    int emit_prompt = 1; /* emit prompt (default) */

    /* Redirect stderr to stdout (so that driver will get all output
     * on the pipe connected to stdout) */
    dup2(1, 2);

    /* Parse the command line */
    while ((c = getopt(argc, argv, "hvp")) != EOF)
    {
        switch (c)
        {
        case 'h': /* print help message */
            usage();
            break;
        case 'v': /* emit additional diagnostic info */
            verbose = 1;
            break;
        case 'p':            /* don't print a prompt */
            emit_prompt = 0; /* handy for automatic testing */
            break;
        default:
            usage();
        }
    }

    /* Install the signal handlers */

    /* These are the ones you will need to implement */
    Signal(SIGINT, sigint_handler);   /* ctrl-c */
    Signal(SIGTSTP, sigtstp_handler); /* ctrl-z */
    Signal(SIGCHLD, sigchld_handler); /* Terminated or stopped child */

    /* This one provides a clean way to kill the shell */
    Signal(SIGQUIT, sigquit_handler);

    /* Initialize the job list */
    initjobs(jobs);

    /* Execute the shell's read/eval loop */
    while (1)
    {
        /* Read command line */
        if (emit_prompt)
        {
            printf("%s", prompt);
            fflush(stdout);
        }
        if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin))
            app_error("fgets error");
        if (feof(stdin))
        { /* End of file (ctrl-d) */
            fflush(stdout);
            exit(0);
        }

        /* Evaluate the command line */
        eval(cmdline);
        fflush(stdout);
        fflush(stdout);
    }

    exit(0); /* control never reaches here */
}

/*
 * eval - Evaluate the command line that the user has just typed in
 *
 * If the user has requested a built-in command (quit, jobs, bg or fg)
 * then execute it immediately. Otherwise, fork a child process and
 * run the job in the context of the child. If the job is running in
 * the foreground, wait for it to terminate and then return.  Note:
 * each child process must have a unique process group ID so that our
 * background children don't receive SIGINT (SIGTSTP) from the kernel
 * when we type ctrl-c (ctrl-z) at the keyboard. p529 */
void eval(char *cmdline)
{
    char *argv[MAXARGS]; // Argument list execve()
    int bg;              // run in foreground or background

    bg = parseline(cmdline, argv);
    if (argv[0] == NULL)
        return; // 忽略空行

    pid_t pid;
    sigset_t mask_all, mask_one, prev_one;
    Sigfillset(&mask_all);
    Sigemptyset(&mask_one);
    Sigaddset(&mask_one, SIGCHLD);

    if (!builtin_cmd(argv))
    {
        Sigprocmask(SIG_BLOCK, &mask_one, &prev_one); // 屏蔽 SIGCHLD 防止未添加就触发删除
        if ((pid = Fork()) == 0)
        {
            if (setpgid(0, 0) != 0)
            { // 子进程的 pid 设为其进程组id
                unix_error("setpgid error");
            }
            Sigprocmask(SIG_SETMASK, &prev_one, NULL); // execve 解除 SIGCHLD 屏蔽
            Execve(argv[0], argv, environ);
        }

        // 父进程
        Sigprocmask(SIG_SETMASK, &mask_all, NULL); // 屏蔽所有，确保 jobs 不被别人修改 ;p543
        Addjob(pid, (bg ? BG : FG), cmdline);
        Sigprocmask(SIG_SETMASK, &prev_one, NULL); // 恢复正常

        if (verbose)
        {
            printf("Added job [%d] %d %s\n", (nextjid - 1), pid, cmdline);
        }

        if (bg) // background
        {
            printf("[%d] (%d) %s", (nextjid - 1), pid, cmdline);
        }
        else // foreground
        {
            waitfg(pid);
        }
    }
    return;
}

/*
 * parseline - Parse the command line and build the argv array.
 *
 * Characters enclosed in single quotes are treated as a single
 * argument.  Return true if the user has requested a BG job, false if
 * the user has requested a FG job. */
int parseline(const char *cmdline, char **argv)
{
    static char array[MAXLINE]; /* holds local copy of command line */
    char *buf = array;          /* ptr that traverses command line */
    char *delim;                /* points to first space delimiter */
    int argc;                   /* number of args */
    int bg;                     /* background job? */

    strcpy(buf, cmdline);
    buf[strlen(buf) - 1] = ' ';   /* replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* ignore leading spaces */
        buf++;

    /* Build the argv list */
    argc = 0;
    if (*buf == '\'')
    {
        buf++;
        // strchr 返回指向该字符的指针
        delim = strchr(buf, '\'');
    }
    else
    {
        delim = strchr(buf, ' ');
    }

    while (delim)
    {
        argv[argc++] = buf;
        *delim = '\0'; // abc\0def
        buf = delim + 1;
        while (*buf && (*buf == ' ')) /* ignore spaces */
            buf++;

        if (*buf == '\'')
        {
            buf++;
            delim = strchr(buf, '\'');
        }
        else
        {
            delim = strchr(buf, ' ');
        }
    }
    argv[argc] = NULL;

    if (argc == 0) /* ignore blank line */
        return 1;

    /* should the job run in the background? */
    if ((bg = (*argv[argc - 1] == '&')) != 0)
    {
        argv[--argc] = NULL;
    }
    return bg;
}

/*
 * builtin_cmd - If the user has typed a built-in command then execute
 *    it immediately.
 * quit, fg, bg, and jobs */
int builtin_cmd(char **argv)
{

    if (!strcmp(argv[0], "quit"))
    {
        // run 的子进程 无需操作 托管到 init
        exit(0);
    }

    if (!strcmp(argv[0], "fg") || !strcmp(argv[0], "bg"))
    {
        do_bgfg(argv);
        return 1;
    }
    if (!strcmp(argv[0], "jobs"))
    {
        listjobs(jobs);
        return 1;
    }
    if (!strcmp(argv[0], "&"))
    {
        return 1; // 忽略单个 &
    }

    return 0; /* not a builtin command */
}

/*
 * do_bgfg - Execute the builtin bg and fg commands */
void do_bgfg(char **argv)
{
    // 1. 判断 有无 pid or jobid
    if (argv[1] == NULL)
    {
        printf("%s command requires PID or %%jobid argument\n", argv[0]);
        return;
    }

    // 2. % or 数字 开头
    struct job_t *job = NULL; // 目标job
    int isdight = argv[1][0] >= 0x30 && argv[1][0] < 0x40;
    char *ptr = strchr(argv[1], '%');

    if (isdight) // PID
    {
        pid_t pid = atoi(argv[1]);
        job = getjobpid(jobs, pid);
        // %67ggdj 这种情况 ref 没考虑
        if (job == NULL)
        {
            printf("(%s): No such process\n", argv[1]);
            return;
        }
    }
    else if (ptr != NULL) // jobid
    {
        pid_t jid = atoi(ptr + 1);
        // %67ggdj 这种情况
        char jid2[99];
        sprintf(jid2, "%d", jid);
        job = getjobjid(jobs, jid);

        if (strcmp((ptr + 1), jid2) || job == NULL)
        {
            printf("%s: No such job\n", argv[1]);
            return;
        }
    }
    else // error
    {
        printf("%s: argument must be a PID or %%jobid\n", argv[0]);
        return;
    }

    if (strcmp(argv[0], "fg"))
    {
        job->state = BG;
        // SIGCONT 继续进程如果该进程停止
        Kill(-(job->pid), SIGCONT);
        printf("[%d] (%d) %s", job->jid, job->pid, job->cmdline);
    }
    else // foreground
    {
        // 。。。
        job->state = FG;
        Kill(-(job->pid), SIGCONT); // make test13
        waitfg(job->pid);
    }

    return;
}
/*
 * Jobs states: FG (foreground), BG (background), ST (stopped)
 * Job state transitions and enabling actions:
 *     FG -> ST  : ctrl-z
 *     ST -> FG  : fg command
 *     ST -> BG  : bg command
 *     BG -> FG  : fg command
 * At most 1 job can be in the FG state.
 */

/*
 * waitfg - Block until process pid is no longer the foreground process */
void waitfg(pid_t pid)
{
    sigset_t mask, prev;
    Sigemptyset(&mask);
    Sigaddset(&mask, SIGCHLD);
    // p545
    Sigprocmask(SIG_BLOCK, &mask, &prev); // 只屏蔽 SIGCHLD 专门等 foreground job 停止或终止
    while (fgpid(jobs) != 0)              // 有foreground job
    {
        Sigsuspend(&prev); // 原子操作 暂时打开 SIGCHLD
        // 有 SIGCHLD -> 中断 -> 执行 sigchld_handler 处理完当前已停止和已终止的子进程后返回
        // 至到 foreground state 被修改
    }
    Sigprocmask(SIG_SETMASK, &prev, NULL); // 解除 SIGCHLD 屏蔽

    if (verbose)
    {
        printf("waitfg: Process (%d) no longer the fg process\n", pid);
    }
    return;
}

/*****************
 * Signal handlers
 *****************/

/*
 * sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
 *     a child job terminates (becomes a zombie), or stops because it
 *     received a SIGSTOP or SIGTSTP signal. The handler reaps all
 *     available zombie children, but doesn't wait for any other
 *     currently running children to terminate.  */
void sigchld_handler(int sig)
{
    char *head = "sigchld_handler:";
    if (verbose)
    {
        // 逐个替换是个体力活，暂时用不安全的
        // Sio_puts(head);
        // Sio_puts(" entering\n");
        printf("%s entering\n", head);
    }

    int olderrno = errno;
    sigset_t mask_all, prev_all;
    Sigfillset(&mask_all);

    pid_t pid;
    int status;

    // 处理 当前全部已停止和已终止的 子进程
    while ((pid = waitpid(-1, &status, (WNOHANG | WUNTRACED))) > 0)
    {
        int jid = pid2jid(pid);

        Sigprocmask(SIG_BLOCK, &mask_all, &prev_all); // 相当于加锁
        if (WIFSTOPPED(status))                       // 停止 ctrl + Z
        {                                             // 修改状态
            struct job_t *job = Getjobpid(pid);
            job->state = ST;

            printf("Job [%d] (%d) stopped by signal 20\n", jid, pid);
        }
        else // 结束  ctrl + C
        {
            if (verbose)
            {
                printf("%s Job [%d] (%d) deleted\n", head, jid, pid);
            }
            Deletejob(pid);
            if (!WIFEXITED(status)) // crtl + C 非正常终止
            {
                printf("Job [%d] (%d) terminated by signal 2\n", jid, pid);
            }
        }
        Sigprocmask(SIG_BLOCK, &prev_all, NULL); // 相当于释放锁
        if (verbose && WIFEXITED(status))
        {
            printf("%s Job [%d] (%d) terminates OK (status 0)\n", head, jid, pid);
        }
    }

    errno = olderrno;
    if (verbose)
    {
        printf("sigchld_handler: exiting\n");
    }
    return;
}

/*
 * sigint_handler - The kernel sends a SIGINT to the shell whenver the
 *    user types ctrl-c at the keyboard.  Catch it and send it along
 *    to the foreground job. */
void sigint_handler(int sig)
{
    char *head = "sigint_handler:";
    if (verbose)
    {
        printf("%s entering\n", head);
    }
    pid_t pid;
    if ((pid = fgpid(jobs)) <= 0)
    {
        return; // 没有 foreground job
    }
    if (verbose)
    {
        printf("%s Job (%d) killed\n", head, pid);
    }
    // 子进程可能有孙进程 make test11
    Kill(-pid, SIGINT); // pid终止,进而向父进程发送SIGCHLD -> sigchld_handler
    if (verbose)
    {
        printf("%s exiting\n", head);
    }
}

/*
 * sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
 *     the user types ctrl-z at the keyboard. Catch it and suspend the
 *     foreground job by sending it a SIGTSTP. */
void sigtstp_handler(int sig)
{
    char *head = "sigtstp_handler:";
    if (verbose)
    {
        printf("%s entering\n", head);
    }
    pid_t pid;
    if ((pid = fgpid(jobs)) <= 0)
    {
        return; // 没有 foreground job
    }
    if (verbose)
    {
        printf("%s Job (%d) stopped\n", head, pid);
    }
    // 子进程可能有孙进程 make test11
    Kill(-pid, SIGTSTP); // pid停止,进而向父进程发送SIGCHLD -> sigchld_handler
    if (verbose)
    {
        printf("%s exiting\n", head);
    }
    return;
}

/*********************
 * End signal handlers
 *********************/

/***********************************************
 * Helper routines that manipulate the job list
 **********************************************/

/* clearjob - Clear the entries in a job struct */
void clearjob(struct job_t *job)
{
    job->pid = 0;
    job->jid = 0;
    job->state = UNDEF;
    job->cmdline[0] = '\0';
}

/* initjobs - Initialize the job list */
void initjobs(struct job_t *jobs)
{
    int i;

    for (i = 0; i < MAXJOBS; i++)
        clearjob(&jobs[i]);
}

/* maxjid - Returns largest allocated job ID */
int maxjid(struct job_t *jobs)
{
    int i, max = 0;

    for (i = 0; i < MAXJOBS; i++)
        if (jobs[i].jid > max)
            max = jobs[i].jid;
    return max;
}

/* addjob - Add a job to the job list */
int addjob(struct job_t *jobs, pid_t pid, int state, char *cmdline)
{
    int i;

    if (pid < 1)
        return 0;

    for (i = 0; i < MAXJOBS; i++)
    {
        if (jobs[i].pid == 0)
        {
            jobs[i].pid = pid;
            jobs[i].state = state;
            jobs[i].jid = nextjid++;
            if (nextjid > MAXJOBS)
                nextjid = 1;
            strcpy(jobs[i].cmdline, cmdline);
            return 1;
        }
    }
    printf("Tried to create too many jobs\n");
    return 0;
}
void Addjob(pid_t pid, int state, char *cmdline)
{
    if (!addjob(jobs, pid, state, cmdline))
    {
        unix_error("addjob");
    }
}

/* deletejob - Delete a job whose PID=pid from the job list */
int deletejob(struct job_t *jobs, pid_t pid)
{
    int i;

    if (pid < 1)
        return 0;

    for (i = 0; i < MAXJOBS; i++)
    {
        if (jobs[i].pid == pid)
        {
            clearjob(&jobs[i]);
            nextjid = maxjid(jobs) + 1;
            return 1;
        }
    }
    return 0;
}
// void Deletejob(pid_t pid, char *head)
void Deletejob(pid_t pid)
{
    if (!deletejob(jobs, pid))
    {
        char str[99];
        sprintf(str, "deletejob: %d error \n", pid);
        unix_error(str);
    }
}

/* fgpid - Return PID of current foreground job, 0 if no such job */
pid_t fgpid(struct job_t *jobs)
{
    int i;

    for (i = 0; i < MAXJOBS; i++)
        if (jobs[i].state == FG)
            return jobs[i].pid;
    return 0;
}

/* getjobpid  - Find a job (by PID) on the job list */
struct job_t *getjobpid(struct job_t *jobs, pid_t pid)
{
    int i;

    if (pid < 1)
        return NULL;
    for (i = 0; i < MAXJOBS; i++)
        if (jobs[i].pid == pid)
            return &jobs[i];
    return NULL;
}
struct job_t *Getjobpid(pid_t pid)
{
    struct job_t *job = getjobpid(jobs, pid);
    if (job == NULL)
    {
        char str[99];
        sprintf(str, "getjobpid: %d error \n", pid);
        unix_error(str);
    }
    return job;
}

/* getjobjid  - Find a job (by JID) on the job list */
struct job_t *getjobjid(struct job_t *jobs, int jid)
{
    int i;

    if (jid < 1)
        return NULL;
    for (i = 0; i < MAXJOBS; i++)
        if (jobs[i].jid == jid)
            return &jobs[i];
    return NULL;
}
struct job_t *Getjobjid(pid_t jid)
{
    struct job_t *job = getjobjid(jobs, jid);
    if (job == NULL)
    {
        char str[99];
        sprintf(str, "getjobjid: %d error \n", jid);
        unix_error(str);
    }
    return job;
}

/* pid2jid - Map process ID to job ID */
int pid2jid(pid_t pid)
{
    int i;

    if (pid < 1)
        return 0;
    for (i = 0; i < MAXJOBS; i++)
        if (jobs[i].pid == pid)
        {
            return jobs[i].jid;
        }
    return 0;
}

/* listjobs - Print the job list */
void listjobs(struct job_t *jobs)
{
    int i;

    for (i = 0; i < MAXJOBS; i++)
    {
        if (jobs[i].pid != 0)
        {
            printf("[%d] (%d) ", jobs[i].jid, jobs[i].pid);
            switch (jobs[i].state)
            {
            case BG:
                printf("Running ");
                break;
            case FG:
                printf("Foreground ");
                break;
            case ST:
                printf("Stopped ");
                break;
            default:
                printf("listjobs: Internal error: job[%d].state=%d ",
                       i, jobs[i].state);
            }
            printf("%s", jobs[i].cmdline);
        }
    }
}
/******************************
 * end job list helper routines
 ******************************/

/***********************
 * Other helper routines
 ***********************/

/*
 * usage - print a help message
 */
void usage(void)
{
    printf("Usage: shell [-hvp]\n");
    printf("   -h   print this message\n");
    printf("   -v   print additional diagnostic information\n");
    printf("   -p   do not emit a command prompt\n");
    exit(1);
}

/*
 * unix_error - unix-style error routine
 */
void unix_error(char *msg)
{
    fprintf(stdout, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

/*
 * app_error - application-style error routine
 */
void app_error(char *msg)
{
    fprintf(stdout, "%s\n", msg);
    exit(1);
}

/*
 * Signal - wrapper for the sigaction function
 */
handler_t *Signal(int signum, handler_t *handler)
{
    struct sigaction action, old_action;

    action.sa_handler = handler;
    sigemptyset(&action.sa_mask); /* block sigs of type being handled */
    action.sa_flags = SA_RESTART; /* restart syscalls if possible */

    if (sigaction(signum, &action, &old_action) < 0)
        unix_error("Signal error");
    return (old_action.sa_handler);
}

/*
 * sigquit_handler - The driver program can gracefully terminate the
 *    child shell by sending it a SIGQUIT signal.
 */
void sigquit_handler(int sig)
{
    printf("Terminating after receipt of SIGQUIT signal\n");
    exit(1);
}

/*
    摘自csapp.c */
void Sigprocmask(int how, const sigset_t *set, sigset_t *oldset)
{
    if (sigprocmask(how, set, oldset) < 0)
        unix_error("Sigprocmask error");
    return;
}

void Sigemptyset(sigset_t *set)
{
    if (sigemptyset(set) < 0)
        unix_error("Sigemptyset error");
    return;
}

void Sigdelset(sigset_t *set, int signum)
{
    if (sigdelset(set, signum) < 0)
        unix_error("Sigdelset error");
    return;
}
void Sigfillset(sigset_t *set)
{
    if (sigfillset(set) < 0)
        unix_error("Sigfillset error");
    return;
}
void Sigaddset(sigset_t *set, int signum)
{
    if (sigaddset(set, signum) < 0)
        unix_error("Sigaddset error");
    return;
}

/* $begin forkwrapper */
pid_t Fork(void)
{
    pid_t pid;

    if ((pid = fork()) < 0)
        unix_error("Fork error");
    return pid;
}
/* $end forkwrapper */

void Execve(const char *filename, char *const argv[], char *const envp[])
{
    if (execve(filename, argv, envp) < 0)
    {
        printf("%s: Command not found\n", argv[0]);
        exit(0); // 子进程结束
    }
}

void Sigsuspend(const sigset_t *set)
{
    sigsuspend(set); /* always returns -1 */
    if (errno != EINTR)
        unix_error("Sigsuspend error");
}

/* $begin wait */
pid_t Wait(int *status)
{
    pid_t pid;

    if ((pid = wait(status)) < 0)
        unix_error("Wait error");
    return pid;
}
/* $end wait */

/* $begin kill */
void Kill(pid_t pid, int signum)
{
    int rc;

    if ((rc = kill(pid, signum)) < 0)
        unix_error("Kill error");
}
/* $end kill */

/*******************************
 * Wrappers for the SIO routines
 ******************************/
ssize_t Sio_putl(long v)
{
    ssize_t n;

    if ((n = sio_putl(v)) < 0)
        sio_error("Sio_putl error");
    return n;
}

ssize_t Sio_puts(char s[])
{
    ssize_t n;

    if ((n = sio_puts(s)) < 0)
        sio_error("Sio_puts error");
    return n;
}

void Sio_error(char s[])
{
    sio_error(s);
}

/* sio_ltoa - Convert long to base b string (from K&R) */
static void sio_ltoa(long v, char s[], int b)
{
    int c, i = 0;

    do
    {
        s[i++] = ((c = (v % b)) < 10) ? c + '0' : c - 10 + 'a';
    } while ((v /= b) > 0);
    s[i] = '\0';
    sio_reverse(s);
}
/* sio_reverse - Reverse a string (from K&R) */
static void sio_reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
/* sio_strlen - Return length of string (from K&R) */
static size_t sio_strlen(char s[])
{
    int i = 0;

    while (s[i] != '\0')
        ++i;
    return i;
}
/* $end sioprivate */

/*************************************************************
 * The Sio (Signal-safe I/O) package - simple reentrant output
 * functions that are safe for signal handlers.
 *************************************************************/

/* Private sio functions */
/* Public Sio functions */
/* $begin siopublic */

ssize_t sio_puts(char s[]) /* Put string */
{
    return write(STDOUT_FILENO, s, sio_strlen(s)); // line:csapp:siostrlen
}

ssize_t sio_putl(long v) /* Put long */
{
    char s[128];

    sio_ltoa(v, s, 10); /* Based on K&R itoa() */ // line:csapp:sioltoa
    return sio_puts(s);
}

void sio_error(char s[]) /* Put error message and exit */
{
    sio_puts(s);
    _exit(1); // line:csapp:sioexit
}
/* $end siopublic */
