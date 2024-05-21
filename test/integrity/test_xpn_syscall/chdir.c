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
		printf(" %s /tmp/expand/P1/dir_nuevo 2\n", argv[0]);
		printf("\n") ;
		return -1 ;
	}	

	result = chdir(argv[1]);
	if(result < 0) {
		printf("Error: %d = chdir('%s')\n", result, argv[1]);
		return -1 ;
	}
	printf("%d = chdir('%s')\n", result, argv[1]);
	return 0;
}
