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
	size_t n;
	double t_bc,t_ac,t_bw,t_aw;

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
	t_bc = get_time();
	FILE *file = fopen(argv[1], "r+");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fd1 = fileno(file);
	printf("%d = fopen('%s','%s')\n", fd1, argv[1],"r+");

	t_bw = get_time(); 

	long mb = atoi(argv[2]);
	for (int i = 0; i < mb; i++)
	{
		n = fread(buffer, 1, BUFF_SIZE, file);
		printf("%lu = fread_%d(%d, %p, %lu)\n", n, i, fd1, buffer, (unsigned long)BUFF_SIZE);
	}

	t_aw = get_time() - t_bw;

    ret = fclose(file);  
	printf("%d = fclose(%d)\n", ret, fd1) ;

	t_ac = get_time() - t_bc;

	printf("Bytes (KiB); Total time (ms); Read time (ms)\n") ;
	printf("%f;%f;%f\n", ((double)mb * (double)BUFF_SIZE) / ((double)KB), t_ac * 1000, t_aw * 1000) ;
    return 0;
}
