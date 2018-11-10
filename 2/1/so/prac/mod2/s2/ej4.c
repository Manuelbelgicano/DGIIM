/*
Implementa de nuevo el programa buscar del ejercicio 3 utilizando la llamada al sistema nftw.
*/
#include<ftw.h>
#include<sys/types.h> 
#include<sys/stat.h> 
#include<fcntl.h> 
#include<unistd.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<errno.h> 
#include<string.h>

int xgrpoth = 0; //Contador de archivos regulares con permiso x para grupo y otros
int numbytes = 0; //Tamaño ocupado en bytes ocupado por los archivos

/**
 * @brief Imprime informacion sobre el archivo
 * @param pathname Ruta del archivo
 * @param stat Estructura stat del archivo
 * @param flags Flags
 * @param ftw Estructura FTW
 * @return Devuelve 0 en caso de éxito
 */
int infofile(const char *pathname, const struct stat *stat,int flags,struct FTW *ftw) {
	if (S_ISREG(stat->st_mode)) {
		printf("%s %d\n",pathname,stat->st_ino);
		numbytes += stat->st_size;
		if ((stat->st_mode & 011)==011)
				xgrpoth++;
	}
	
	return 0;
}

int main(int argc, char *argv[]) {
	//Asignacion del pathname
	char pathname[200];
	if (argc==1)
		strcpy(pathname,".");
	else if (argc==2)
		strcpy(pathname,argv[1]);
	else {
		printf("Error en el numero de argumentos\n");
		exit (EXIT_FAILURE);
	}
	
	//Ejecución del programa
	printf("Los i-nodos son:\n");
	if (nftw(pathname,infofile,10,0)!=0) {
		printf("Error en nftw");
		exit (EXIT_FAILURE);
	}
	printf("Hay %d archivos con permisos x para grupo y otros\n",xgrpoth);
	printf("Los archivos ocupan un total de %d bytes",numbytes);
	
	exit (EXIT_SUCCESS);
}
