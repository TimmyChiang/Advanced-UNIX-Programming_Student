#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	time_t now;
	struct tm* info;
	time(&now);
	info = localtime(&now);

	char buffer[100];
	strftime(buffer, 100, "%a %b %d %H:%M:%S %Z %Y", info);
	puts(buffer);

	// New York Time Zone, For Report
	/*
	setenv("TZ", "America/New_York", 1);
	time(&now);
	info = localtime(&now);

	strftime(buffer, 100, "%a %b %d %H:%M:%S %Z %Y", info);
	puts(buffer);
	*/
	return 0;
}
