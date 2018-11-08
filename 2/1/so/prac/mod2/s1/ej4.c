/*
Define una macro en lenguaje C que tenga la misma funcionalidad que la macro S_ISREG(mode) usando para ello lod flags definidos en <sys/stat.h> para el campo st_mode de la struct stat, y comprueba que funciona en un programa simple.
*/
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

//Definicion de la macro
#define S_ISREG2(mode) ((mode & S_IFMT)==S_IFREG)

int main(int argc, char *argv[]) {
	//Comprobacion de argumentos
	if (argc<2) {
		printf("Error en el numero de argumentos\n");
		exit (EXIT_FAILURE);
	}
	
	//Obtencion de los datos del archivo
	struct stat atributos;
	if (lstat(argv[1],&atributos)==-1) {
		printf("Error %d en la operacion lstat\n",errno);
		exit (EXIT_FAILURE);
	}
	
	//Comprobacion si es regular
	if (S_ISREG2(atributos.st_mode))
		printf("El archivo %s es regular",argv[1]); 
	else
		printf("El archivo %s no es regular",argv[1]); 
	exit (EXIT_SUCCESS);
}
