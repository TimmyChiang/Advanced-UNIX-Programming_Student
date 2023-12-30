#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct memstruct {
	char *buf;
	size_t bufsize;
	size_t curpos;
} memstruct;

FILE* myfmemopen(void*, size_t);
int myread(void*, char*, int);
int mywrite(void*, const char*, int);
fpos_t myseek(void*, fpos_t, int);
int myclose(void*);

FILE* myfmemopen(void* buf, size_t size) {
	
	memstruct *mem;
	mem = malloc(sizeof(memstruct));
	
	mem -> buf = buf;
	mem -> bufsize = size;
	mem -> curpos = 0;

	FILE* fp = funopen(mem, myread, mywrite, myseek, myclose);
	return fp;
}

int myread(void* cookie, char* buf, int nbytes) {
	memstruct* mem = cookie;
	int maxlen;
	if (nbytes > mem -> bufsize - mem -> curpos)
		maxlen = mem -> bufsize - mem -> curpos;
	else
		maxlen = nbytes;
	memcpy(buf, mem -> buf + mem -> curpos, maxlen);
	mem -> curpos += maxlen;
	return maxlen;
}

int mywrite(void* cookie, const char* buf, int nbytes) {
	memstruct* mem = cookie;
	memcpy(mem -> buf + mem -> curpos, buf, nbytes);
	return nbytes;
}

fpos_t myseek(void* cookie, fpos_t pos, int whence) {
	memstruct* mem = cookie;
	fpos_t res;

	switch(whence) {
		case SEEK_SET:
		      res = pos;
		      break;
		case SEEK_END:
		      res = mem -> bufsize + pos;
		      break;
		case SEEK_CUR:
		      res = mem -> curpos;
		      break;
		default:
		      break;
	}
	mem -> curpos = res;
	return res;
}

int myclose(void* cookie) {
	memstruct* mem = cookie;
	free(mem -> buf);
	free(mem);
	return 0;
}

int main() {
	const char s[] = "hello, world";
	char buf[1024] = {0};
	FILE* fp = myfmemopen(buf, 1024);
	char buffer[1024];
	if (fwrite(s, sizeof(char), 12, fp) +1 != sizeof(s))
		fprintf(stderr, "fwrite error\n");
	if (fseek(fp, 7L, SEEK_SET))
		fprintf(stderr, "fseek error\n");
	fread(buffer, sizeof(char), sizeof(buffer), fp);
	puts(buffer);
	if(fseek(fp, 0L, SEEK_SET))
		fprintf(stderr, "fseek error\n");
	fread(buffer, sizeof(char), sizeof(buffer), fp);
	puts(buffer);
	fclose(fp);
	return 0;
}
