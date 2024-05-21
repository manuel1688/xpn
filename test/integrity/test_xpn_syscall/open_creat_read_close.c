#include "all_system.h"
#include <sys/time.h>



#define KB  (1024)

#define BUFF_SIZE (1*MB)
char buffer[BUFF_SIZE] ; 


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

	int mode = 00777;

	// a nivel de open_at solo se activa si se usa O_CREAT en el segundo argumento.
	fd = open(argv[1], O_CREAT, mode);
	if (fd < 0) {
		printf("Error opening file\n");
		return -1 ;
	}
	printf("%d = open('%s', O_RDWR, %d)\n", fd, argv[1], mode);

	ret = close(fd);
	printf("%d = close(%d)\n", ret, fd) ;

	return 0;
}
