#include "all_system.h"
#include <sys/time.h>

double get_time(void)
{
    struct timeval tp;
    struct timezone tzp;

    gettimeofday(&tp,&tzp);
    return((double) tp.tv_sec + .000001 * (double) tp.tv_usec);
}

int main ( int argc, char *argv[] )
{
	int	ret,fd;
	if (argc < 3)
	{
		printf("\n") ;
		printf(" Usage: %s <full path> <megabytes to read>\n", argv[0]) ;
		printf("\n") ;
		printf(" Example:") ;
		printf(" %s /tmp/expand/test_1 2\n", argv[0]);
		printf("\n") ;
		return -1 ;
	}	
	
	FILE *file = fopen(argv[1], "r+");
	if (file == NULL) {
		printf("Error opening file\n");
		return 1;
	}
	printf("%d = fopen('%s','%s')\n", fileno(file), argv[1],"r+");
	fd = fileno(file);
	if (fd < 0) {
		printf("Error opening file\n");
		return -1 ;
	}

	long poistion = ftell(file);
	if(poistion < 0) {
		printf("Error getting position\n");
		return -1;
	}
	printf("%ld = ftell(%d)\n", poistion, fd);

	ret = close(fd);
	printf("%d = close(%d)\n", ret, fd) ;
	return 0;
}
