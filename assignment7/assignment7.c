#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    pid_t pid = fork();
    if(pid < 0) {
        perror("fork error");
        return -1;
    } else if(pid == 0) {
	// Child
        setsid();
	/* To verify that child process does not have a control terminal
        if((open("/dev/tty", O_RDWR)) < 0) {
            printf("The child has no controlling terminal.\n");
        } else {
            printf("The child has a controlling terminal\n");
        }
	*/
    } else {
	// Parent
	// printf("child = %d\n", pid);
	system("ps -x -o pid,pgid,tpgid");
    }
    return 0;
}
