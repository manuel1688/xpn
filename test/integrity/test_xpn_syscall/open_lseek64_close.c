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
	int	ret,fd1;
	double t_bc,t_ac,t_bw,t_aw;

	if (argc < 3)
	{
		printf("\n");
		printf(" Usage: %s <full path> <megabytes to read>\n", argv[0]);
		printf("\n");
		printf(" Example:");
		printf(" %s /tmp/expand/test_1 2\n", argv[0]);
		printf("\n");
		return -1;
	}	

	memset(buffer, 'a', BUFF_SIZE);
	t_bc = get_time();
	
	fd1 = open(argv[1], O_RDWR);
	if (fd1 < 0) {
		printf("Error opening file\n");
		return -1 ;
	}
	printf("%d = open('%s', %o)\n", fd1, argv[1], 00777);

	t_bw = get_time(); 

	off_t offset = lseek64(fd1, 0, SEEK_SET);
	if (offset == -1) {
		printf("Error seeking file\n");
		return -1;
	}
	printf("%ld = lseek64(%d, 0, %d)\n", offset, fd1, SEEK_SET);

	long mb = atoi(argv[2]);
	for (int i = 0; i < mb; i++)
	{
		ret = read(fd1, buffer, BUFF_SIZE);
		printf("%d = read_%d(%d, %p, %lu)\n", ret, i, fd1, buffer, (unsigned long)BUFF_SIZE);
	}

	t_aw = get_time() - t_bw;

	ret = close(fd1);
	printf("%d = close(%d)\n", ret, fd1);

	t_ac = get_time() - t_bc;

	printf("Bytes (KiB); Total time (ms); Read time (ms)\n");
	printf("%f;%f;%f\n", ((double)mb * (double)BUFF_SIZE) / ((double)KB), t_ac * 1000, t_aw * 1000);
	return 0;
}
