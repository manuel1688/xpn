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
	size_t n;
	double t_br,t_ar,t_bo,t_ao;

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

	memset(buffer, 'a', BUFF_SIZE) ;
	t_bo = get_time();

	fd = open(argv[1], O_RDWR);
	if (fd < 0) {
		printf("Error opening file\n");
		return -1 ;
	}
	
	printf("%d = open('%s', %o)\n", fd, argv[1], 00777);

	FILE *file = fdopen(fd, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

	printf("%d = fdopen('%d','%s')\n", fd,fd,"r+");
	t_ao = get_time() - t_bo;

	t_br = get_time(); 

	long mb = atoi(argv[2]);
	for (int i = 0; i < mb; i++)
	{
		n = fread(buffer, 1, BUFF_SIZE, file);
		printf("%lu = fread_%d(%d, %p, %lu)\n", n, i, fd, buffer, (unsigned long)BUFF_SIZE);
	}

    ret = fclose(file);  
	printf("%d = fclose(%d)\n", ret, fd) ;

	t_ar = get_time() - t_br;

	printf("Bytes (KiB); Open time (ms); Read time (ms)\n");
	printf("%f;%f;%f\n", ((double)mb * (double)BUFF_SIZE) / ((double)KB), t_ao * 1000, t_ar * 1000);
    return 0;
}
