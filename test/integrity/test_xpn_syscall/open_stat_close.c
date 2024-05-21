#include "all_system.h"
#include <sys/time.h>

#include <sys/stat.h>

double get_time(void)
{
    struct timeval tp;
    struct timezone tzp;

    gettimeofday(&tp,&tzp);
    return((double) tp.tv_sec + .000001 * (double) tp.tv_usec);
}

int main ( int argc, char *argv[] )
{
	int	ret,fd,result;
	struct stat statbuf;

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

	result = stat(argv[1], &statbuf);
	if (result == -1)
	{
		printf("Error getting file status\n");
		return -1;
	}
	printf("%d = stat('%s', %p)\n", result, argv[1], &statbuf);

	result = stat64(argv[1], &statbuf);
	if (result == -1)
	{
		printf("Error getting file status\n");
		return -1;
	}
	printf("%d = stat64('%s', %p)\n", result, argv[1], &statbuf);

	result = lstat(argv[1], &statbuf);
	if (result == -1)
	{
		printf("Error getting file status\n");
		return -1;
	}
	printf("%d = lstat('%s', %p)\n", result, argv[1], &statbuf);

	result = lstat64(argv[1], &statbuf);
	if (result == -1)
	{
		printf("Error getting file status\n");
		return -1;
	}
	printf("%d = lstat64('%s', %p)\n", result, argv[1], &statbuf);

	fd = open(argv[1], O_RDWR);
	if (fd < 0) {
		printf("Error opening file\n");
		return -1 ;
	}

	result = fstat(fd, &statbuf);
	if(result == -1)
	{
		printf("Error getting file status\n");
		return -1;
	}
	printf("%d = fstat(%d, %p)\n", result, fd, &statbuf);
	printf("File size: %lld bytes\n", (long long)statbuf.st_size);
	printf("File permissions: %o\n", statbuf.st_mode & 0777);

	ret = close(fd);
	printf("%d = close(%d)\n", ret, fd) ;
	return 0;
}
