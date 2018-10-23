#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
/*
Implementa un programa que realice la siguiente funcionalidad. El programa
acepta como argumento el nombre de un archivo (pathname), lo abre y lo lee en bloques de
tamaño 80 Bytes, y crea un nuevo archivo de salida, salida.txt, en el que debe aparecer la
siguiente información:
Bloque 1
// Aquí van los primeros 80 Bytes del archivo pasado como argumento.
Bloque 2
// Aquí van los siguientes 80 Bytes del archivo pasado como argumento.
...
*/

int main (int argc, char *argv[]) {

	int fd;
	//Apertura del archivo
	if (argc>1) {
		fd = open(argv[1]);
		if (fd<0) {
			printf("\nError %n en open.",errno);
			perror("\nError en la apertura del archivo");
			exit(EXIT_FAILURE);
		}
	else
		char[20] filename;
		fgets(filename,20,stdin);
		fd = open(filename);
		if (fd<0) {
			printf("\nError %n en open.",errno);
			perror("\nError en la apertura del archivo");
			exit(EXIT_FAILURE);
		}
	//Tamaño del archivo
	int filesize = lseek(fd,0,SEEK_END);
	if (filesize<0) {
		printf("\nError %n en lseek.",errno);
		exit(EXIT_FAILURE);
	}
	int aux = lseek(fd,0,SEEK_SET);
	if (aux!=0) {
		printf("\nError %n en lseek.",errno);
		exit(EXIT_FAILURE);
	} 
	//Lectura por bloques
	int blockcount = 1;
	int bytecount = 80;
	while (bytecount<filesize) {
		printf("\nBloque %d:\n",blockcount);
		read(fd,bytecount);
		blockcount++;
		bytecount += 80;
	}
	return EXIT_SUCCESS;		
}
