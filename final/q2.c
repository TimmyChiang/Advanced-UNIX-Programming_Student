#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>

void sleep_us(long val) {
    struct timeval tval;
    tval.tv_sec = val / 1000000;
    tval.tv_usec = val % 1000000;
    int ret = select(0, NULL, NULL, NULL, &tval);
    // if (ret == -1) {
    //     fprintf(stderr, "select error");
    // } else if (ret == 0) {
    //     fprintf(stderr, "select timeout\n");
    // } else {
    //     fprintf(stdout, "select success\n");
    // }
}

int main(int argc, char *argv[]) {
    long val = 0;
    for (int i = 0; argv[1][i]; ++i)
        val = val * 10 + (argv[1][i] - '0');

    struct timeval start, end;
    gettimeofday(&start, NULL);
    sleep_us(val);
    gettimeofday(&end, NULL);

    printf("Sleep time: %ld us\n", (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);
    return 0;
}