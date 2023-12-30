#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <signal.h>
const int N = 3;

static void sig_usr(int signo) {
	if(signo == SIGINT) printf("T1 handling SIGINT\n");
	else if(signo == SIGTERM) printf("T2 handling SIGTERM\n");
	else if(signo == SIGUSR1) printf("T3 handling SIGUSR1\n");
}

void *F1() {
	if(signal(SIGINT, sig_usr) == SIG_ERR) 
		perror("can't catch SIGINT");
}

void *F2() {
	if(signal(SIGTERM, sig_usr) == SIG_ERR) 
		perror("can't catch SIGTERM");
}

void *F3() {
	if(signal(SIGUSR1, sig_usr) == SIG_ERR) 
		perror("can't catch SIGUSR1");
}

int main(void) {
	pthread_t threads[N];
	if(pthread_create(&threads[0], NULL, F1, NULL) != 0) {
		printf("T1 create error\n");
	}	
	if(pthread_create(&threads[1], NULL, F2, NULL) != 0) {
		printf("T2 create error\n");
	}
	if(pthread_create(&threads[2], NULL, F3, NULL) != 0) {
		printf("T3 create error\n");
	}
	while(1);
}
