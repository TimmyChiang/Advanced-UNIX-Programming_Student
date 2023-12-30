#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main() {
	const char student[] = "student.";
	const char nthu_student[] = "NTHU student.";
	char buffer[80] = {};
	int fd = open("sample.txt", O_RDWR);
	if(fd != -1) {
		int offset = - (int) sizeof(student);
		lseek(fd, offset, SEEK_END);
		read(fd, buffer, sizeof(student));
		write(STDOUT_FILENO, buffer, sizeof(buffer) - 1);
		lseek(fd, offset, SEEK_END);
		write(fd, nthu_student, sizeof(nthu_student) - 1);
		lseek(fd, 0, SEEK_SET);
		read(fd, buffer, sizeof(buffer));
		write(STDOUT_FILENO, buffer, sizeof(buffer) - 1);
	} else {
		puts("QQ");
	}
	return 0;
}
