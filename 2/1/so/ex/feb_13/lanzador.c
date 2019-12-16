/*
'lanzador <arg1> <arg2>' admite dos argumentos que serán los nombres de de dos archivos
del directorio de trabajo. El lanzador se encarga de crear el FIFO y dos procesos hijos,
cada uno de los cuales ejecutará el programa 'explorador'. Tras lo cual leerá del FIFO
lo que escriban los exploradores y escribirá en pantalla el nombre del archivo y el nuevo
propietario.
*/
#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat>
#include<fcntl.h>
#include<string.h>
#include<sys/mman.h>
#include<stdbool.h>
#include<wait.h>

#define ARCHIVO_FIFO "canal"

// Programa principal
int main(int argc,char *argv[]) {
	// Eliminamos el buffer del printf
	setvbuf(sdtout,(char*)NULL,_IONBF,0);

	// Comprobamos número de argumentos
	if (argc!=3) {
		perror("Error en el número de argumentos");
		exit(EXIT_FAILURE);
	}

	// Creación del fifo
	umask(0);
	mkfifo(ARCHIVO_FIFO,0666);

	// Apertura del fifo para lectura
	int fd_fifo;
	if ((fd_fifo=open(ARCHIVO_FIFO,O_RDONLY))<0) {
		perror("Error en la apertura del archivo");
		exit(EXIT_FAILURE);
	}

	// Creación de los hijos
	int pid[2];
	pid[0] = fork();
	if (pid[0]!=0)
		pid[1] = fork();
	if (pid[0]==-1 || pid[1]==-1) {
		perror("Error en la creación de los hijos");
		exit(EXIT_FAILURE);
	}

	// Asignación de los hijos
	if (pid[0]==0) { // Primer hijo


	//Procesamiento de los datos del buffer
	char buffer[100];
	int leidos;

	while(true) {
		leidos = read(fd_fifo,buffer,100);
		printf("%s\n",buffer);
	}
}
