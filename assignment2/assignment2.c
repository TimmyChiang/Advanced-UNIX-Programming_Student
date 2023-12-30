#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUF_SIZE 100000
char BUF[BUF_SIZE];

int main(int argc, char* argv[]) {
	remove(argv[2]);
	int src_id = open(argv[1], O_RDWR);
	int des_id = open(argv[2], O_CREAT | O_RDWR);
	int cnt = 0;
	do {
		cnt = read(src_id, BUF, BUF_SIZE);
		write(des_id, BUF, cnt);
	} while(cnt == BUF_SIZE);
	chmod(argv[2], (1<<9)-1);
	return 0;
}

