#include <stdio.h>
#include <time.h>

int main (int argc, char *argv[]) {
    time_t now;
    struct tm *tm;

    char wday[7][10] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    char mon[12][10] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    now = time(0);
    if ((tm = localtime (&now)) == NULL) {
        printf ("Get time error\n");
        return 1;
    }

    printf ("%02d:%02d:%02d, %s %s %02d, %04d\n",
        tm->tm_hour, tm->tm_min, tm->tm_sec, wday[tm->tm_wday],
        mon[tm->tm_mon], tm->tm_mday, tm->tm_year+1900);

    return 0;
}