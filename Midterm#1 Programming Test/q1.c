#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmpstring(const void *str1, const void *str2) {
	return strcmp((char *)str1, (char *)str2);
}

int main(int argc, char *argv[]) {
	// for (int i = 0; i < argc; ++i)	printf("%s\n", argv[i]);
	
	FILE* fptr;
	if ((fptr = fopen(argv[argc-1], "r")) == NULL) {
		perror("fail to open the file");
		exit(1);
	}
	char table[1024][1024];
	int idx = 0;
	while(fgets(table[idx], sizeof(table[idx]), fptr)) ++idx;
	qsort(table, idx, sizeof(table[0]), cmpstring);
	int cmd_opt = 0;
	int state = 0;
	while(1) {
		cmd_opt = getopt(argc, argv, "ciu");
		if(cmd_opt == -1) break;
		if(cmd_opt == 'i') state |= (1<<2);
		if(cmd_opt == 'u') state |= (1<<1);
		if(cmd_opt == 'c') state |= (1<<0);
	}
	int cnt[1024] = {0};
	int cur = 0;
	for(int i=0;i<idx;i++) {
		if(state & 4) {
			if(strcasecmp(table[cur],table[i]) == 0) {
				cnt[cur]++;
			
			}
			else {
				cur = i;
				cnt[cur]++;
			}
		}
		else {
			if(strcmp(table[cur],table[i]) == 0) {
				cnt[cur]++;
			
			}
			else {
				cur = i;
				cnt[cur]++;
			}
		}	
	}	
	for(int i=0;i<idx;i++) {
		if(cnt[i] == 0) continue;
		if(state & 2) {
			if(cnt[i] == 1) {
				if(state & 1) printf("%d ", cnt[i]);
				printf("%s", table[i]);
			}
			else continue;
		}
		else {
			if(state & 1)  printf("%d ", cnt[i]);
		       	printf("%s", table[i]);	
		}
	}
	fclose(fptr);
	return 0;
}
