/*
Recorrer el directorio pasado como argumento, de modo que para los archivos 
regulares:
		1)Añadir los permisos rwx para otros.
		2)Mostrar el nombre completo de la ruta y el nº de inodo por pantalla
		3)En el directorio home del usuario crear un archivo con el mismo nombre,
	      con los mismos permisos (antes de modificarlos) y vacío.	
(Aclaración: se puede obtener el directorio con: char *home = getenv("HOME"))
*/

#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>

int main(int argc, char *argv[]) {
	if (argc!=2) {
		perror("Error en el número de argumentos");
		exit(EXIT_FAILURE);
	}
	// Variables
	DIR *directorio;
	struct dirent *archivo;
	struct stat atrib;
	char *home = getenv("HOME");
	char nombre_archivo[200];
	int fd;
	int perm;
	int permisos_antiguos;

	// Abrimos el directorio
	if ((directorio=opendir(argv[1]))==NULL) {
		perror("Error en la apertura del directorio");
		exit(EXIT_FAILURE);
	}

	// Recorremos el directorio
	while ((archivo=readdir(directorio))!=NULL) {
		// Guardamos el nombre del archivo
		sprintf(nombre_archivo,"%s/%s",argv[1],archivo->d_name);

		// Comprobamos que tengan el bit de usuario activado
		lstat(nombre_archivo,&atrib);
		if (S_ISREG(atrib.st_mode)) {
			// Cambiamos los permisos de rwx para otros
			permisos_antiguos = atrib.st_mode;
			if ((perm=chmod(nombre_archivo,atrib.st_mode|0007))==-1) {
				perror("Error modificando los permisos");
				exit(EXIT_FAILURE);
			}

			// Imprimimos por pantalla el nombre del archivo y su nº de i-nodo
			printf("Archivo: %s\nNº i-nodo: %d\n",nombre_archivo,archivo->d_ino);

			// Creamos en la carpeta HOME un archivo con el mismo nombre y permisos que antes
			sprintf(nombre_archivo,"%s/%s",home,archivo->d_name);
			if ((fd=open(nombre_archivo,O_CREAT))<0) {
				perror("Error en la creación del archivo");
				exit(EXIT_FAILURE);
			}
			if ((perm=fchmod(fd,permisos_antiguos))==-1) {
				perror("Error modificando los permisos");
				exit(EXIT_FAILURE);
			}
			if (close(fd)==-1) {
				perror("Error cerrando el archivo");
				exit(EXIT_FAILURE);
			}
		}
	}

	// Cerramos el directorio
	if (closedir(directorio)==-1) {
		perror("Error cerrando el directorio");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
