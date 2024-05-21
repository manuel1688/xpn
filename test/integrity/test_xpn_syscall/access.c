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
	int	result;
	
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

	result = access(argv[1], F_OK);
	if (result < 0) {
		printf("Error F_OK accessing file\n");
		return -1 ;
	}
	printf("%d = access('%s', F_OK)\n", result, argv[1]);

	result = access(argv[1], R_OK);
	if (result < 0) {
		printf("Error R_OK accessing file\n");
		return -1 ;
	}
	printf("%d = access('%s', R_OK)\n", result, argv[1]);

	result = access(argv[1], W_OK);
	if (result < 0) {
		printf("Error W_OK accessing file\n");
		return -1 ;
	}
	printf("%d = access('%s', W_OK)\n", result, argv[1]);

	result = access(argv[1], X_OK);
	if (result < 0) {
		printf("Error W_OK accessing file\n");
		return -1 ;
	}
	printf("%d = access('%s', X_OK)\n", result, argv[1]);
	return 0;
}
