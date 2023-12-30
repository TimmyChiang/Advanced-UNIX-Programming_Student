#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    char cmd[1000];
    // https://askubuntu.com/questions/522051/how-to-list-all-symbolic-links-in-a-directory#:~:text=in%20that%20case%3A-,find%20.%20%2Dtype%20l%20%2Dls,-To%20only%20process
    sprintf(cmd, "find %s -type l -ls", argv[1]);
    system(cmd);
    return 0;
}
