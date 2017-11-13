//In the name of God
//...
#include <sys/time.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

int main(int argc, char *argv[]) {
	struct timeval now;
	if (gettimeofday(&now, NULL) == -1)
		return 1;
	struct tm *timeinfo;

	timeinfo = localtime((const time_t *) &now);

	char time[100];

	strftime(time, 100, "Current Date & time is: %c", timeinfo);
	printf("%s\n", time);
	return 0;
}
