#include "all_system.h"
#include <sys/time.h>

//Esta linea es para que el buffer sea de 1MB 1*MB = 1024*1024
#define BUFF_SIZE (1*MB)
// Se crea un buffer de 1MB, el buffer es un arreglo de caracteres de tamaño BUFF_SIZE
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
	// ret es el resultado de la operacion, fd es el file descriptor. ret significa return
	// fd es el file descriptor
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

	// memset es una funcion que llena un buffer con un caracter especifico, en este caso 'a'
	// se llena hasta que el tamaño del buffer sea BUFF_SIZE
	memset(buffer, 'a', BUFF_SIZE) ;
	
	fd = open(argv[1], O_RDWR);
	if (fd < 0) {
		printf("Error opening file\n");
		return -1 ;
	}
	printf("%d = open('%s', %o)\n", fd, argv[1], 00777) ;

	int fd_copy = dup(fd);
	
	if (fd_copy < 0) {
		printf("Error duplicating file descriptor\n");
		return -1 ;
	}
	printf("%d = dup(%d)\n", fd_copy, fd);

	// atoi convierte un string a un entero
	// long mb = atoi(argv[2]);
	// for (int i = 0; i < mb; i++)
	// {
	// 	// read es una funcion que lee un archivo, el primer argumento es el file descriptor
	// 	// el segundo argumento es el buffer donde se va a guardar la informacion leida
	// 	// el tercer argumento es el tamaño del buffer
	// 	ret = read(fd_copy, buffer, BUFF_SIZE);
	// 	printf("%d = read_%d(%d, %p, %lu)\n", ret, i, fd_copy, buffer, (unsigned long)BUFF_SIZE);
	// }

	ret = close(fd);
	printf("%d = close(%d)\n", ret, fd);
	printf("Closing copy\n");
	ret = close(fd_copy);
	printf("%d = close(%d)\n", ret, fd_copy);

	return 0;
}
