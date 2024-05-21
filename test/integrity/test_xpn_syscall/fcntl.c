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
	int	result = -1;
	
	if (argc < 3)
	{
		printf("\n") ;
		printf(" Usage: %s <full path> <megabytes to read>\n", argv[0]) ;
		printf("\n") ;
		printf(" Example:") ;
		printf(" %s /tmp/expand/P1/demo.txt 2\n", argv[0]);
		printf("\n") ;
		return -1 ;
	}	

	result = fcntl(0, F_SETFL, O_NONBLOCK);
	if(result < 0) {
		printf("Error: %d = fcntl('%s')\n", result, argv[1]);
		return -1 ;
	}
	printf("%d = fcntl('%s')\n", result, argv[1]);

    // flags |= O_NONBLOCK;

    // if (fcntl(fd, F_SETFL, flags) < 0) {
    //     perror("fcntl");
    //     return -1;
    // }
	return 0;
	
}
