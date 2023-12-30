#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    system("ps -a");
    int pid;
    if ((pid = fork()) < 0)
        perror("fork error");
    else if (pid == 0)
        return 0;
    system("ps -a");
    return 0;
}
