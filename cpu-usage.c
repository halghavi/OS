#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
int main() {
	int proc;


	int i=0, cpu_found=0, tmp = 0, total=0, prev_total=0, diff_idle=0, diff_total=0, idle=0, prev_idle=0, x=0, diff_usage=0;

	if( (proc = open("/proc/stat", O_RDONLY)) == -1) {
		printf("Failed to open file\n");
		return 1;
	}


	char str[10000];
	if (read(proc, str, 10000) < 0)
		return 1;
	int l = strlen(str);
	for (int j = 0; j < l; j++) {
		char c = str[j];
		if( (c == 'c' && i == 0) || (c == 'p' && i == 1) || (c == 'u' && i == 2)){
			cpu_found++;
		}

		else if( c >= '0' && c <= '9' && cpu_found == 3){
			tmp *= 10;
			tmp += c-'0';
		}

		else if( c == ' ' && cpu_found == 3 ){
			total += tmp;
			x++;
			if( x == 6 )
				idle = tmp;
			tmp = 0;
		}

		else if( c == '\n' && cpu_found == 3 ){
			i = 0;
			cpu_found = 0;
			total += tmp;
			tmp = 0;
			break;
		}
		i++;
	}

	diff_idle = idle-prev_idle;
	diff_total = total-prev_total;

	prev_total=total;
	prev_idle=idle;

	diff_usage=100*(diff_total - diff_idle);

	printf("CPU: %6.2f%%\n", (float)diff_usage/(float)diff_total );
	fflush(stdout);
	close(proc);

	return 0;

}
