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
	double t_bc,t_ac,t_bw,t_aw;

	if (argc < 3)
	{
		printf("\n") ;
		printf(" Usage: %s <full path> <megabytes to read>\n", argv[0]);
		printf("\n") ;
		printf(" Example:") ;
		printf(" %s /tmp/expand/test_1 2\n", argv[0]);
		printf("\n") ;
		return -1 ;
	}	

	memset(buffer, 'a', BUFF_SIZE);

	fd = __open_2(argv[1], O_RDWR);
	if (fd < 0) {
		printf("Error opening file\n");
		return -1 ;
	}
	printf("%d = __open_2('%s', %o)\n", fd, argv[1], 00777);

	long mb = atoi(argv[2]) ;
	for (int i = 0; i < mb; i++)
	{
		ret = read(fd, buffer, BUFF_SIZE);
		printf("%d = read_%d(%d, %p, %lu)\n", ret, i, fd, buffer, (unsigned long)BUFF_SIZE);
	}

	ret = close(fd);
	printf("%d = close(%d)\n", ret, fd) ;
	return 0;
}
