#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
    time_t cur;
    struct tm *tm;
    int cnt = 0;
    while(1) {
        ++cnt;
        sleep(10);
        if (cnt % 6 == 0) {
            cnt = 0;
            cur = time(0);
            if ((tm = localtime (&cur)) == NULL) {
                printf ("Get time error\n");
                return 1;
            }
            printf ("%02d\n", tm->tm_sec);
        }
    }
}