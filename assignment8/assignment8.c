#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static volatile sig_atomic_t sigflag; /* set nonzero by sig handler */
static sigset_t newmask, oldmask, zeromask;
FILE* fp;
pid_t pid;

static void sig_usr(int signo) { /* one signal handler for SIGUSR1 and SIGUSR2 */
    sigflag = 1;
}

static void TELL_WAIT(void) {
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
        perror("signal(SIGUSR1) error");

    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
        perror("signal(SIGUSR2) error");

    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);

    /* Block SIGUSR1 and SIGUSR2, and save current signal mask */
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        perror("SIG_BLOCK error");
}

static void TELL_PARENT(void) {
    kill(getppid(), SIGUSR2); /* tell parent we’re done */
}

static void WAIT_PARENT(void) {
    while (sigflag == 0)
        sigsuspend(&zeromask); /* and wait for parent */
    sigflag = 0;
    /* Reset signal mask to original value */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        perror("SIG_SETMASK error");
}

static void TELL_CHILD(pid_t pid) {
    kill(pid, SIGUSR1); /* tell child we’re done */
}

static void WAIT_CHILD(void) {
    while (sigflag == 0)
        sigsuspend(&zeromask); /* and wait for child */
    sigflag = 0;
    /* Reset signal mask to original value */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        perror("SIG_SETMASK error");
}

static int increment_counter(FILE *const file) {
    /* TODO */
    int val;
    fscanf(file, "%d", &val);
    ++val;
    fseek(file, 0L, SEEK_SET);
    fprintf(file, "%d", val);
    fclose(fp);
    return val;
}

int main(void) {
    /* TODO */
    fp = fopen("result.txt", "w");
    fprintf(fp, "%d", 0);
    fclose(fp);

    pid = fork();
    TELL_WAIT();

    while(!pid) {
        fp = fopen("result.txt", "r+");
        int cur = increment_counter(fp);
        if (cur > 100) {
            TELL_PARENT();
            break;
        }
        printf("Child incrementing, value: %d\n", cur);
        TELL_PARENT();
        WAIT_PARENT();
    }

    while(pid) {
        WAIT_CHILD();
        fp = fopen("result.txt", "r+");
        int cur = increment_counter(fp);
        if (cur > 100) {
            TELL_CHILD(pid);
            break;
        }
        printf("Parent incrementing, value: %d\n", cur);
        TELL_CHILD(pid);
    }

    return 0;
}