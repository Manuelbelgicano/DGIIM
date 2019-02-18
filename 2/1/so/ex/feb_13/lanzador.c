/**
 * Author: Manuel Gachs Ballegeer
 * File: lanzador.c
 */

#include<dirent.h>
#include<errno.h>
#include<fcntl.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/mman.h>
#include<sys/stat>
#include<sys/types>
#include<sys/wait>
#include<unistd.h>

#define ARCHIVO_FIFO "comsFIFO"

int main(int argc,char* argv[]) {
	if (argc!=3) {
		perror("Parámetros incorrectos");
		exit(EXIT_FAILURE);
	}

	char archivo1[256];
	char archivo2[256];
	strcpy(archivo1,argv[1]);
	strcpy(archivo2,argv[2]);
	
	pid_t hijo1;
	pid_t hijo2;
	hijo1 = fork();
	hijo2 = hijo1>0?fork:-1;

	int fd;
	char buffer[256];
	mknod(ARCHIVO_FIFO,S_IFIFO|0666,0);
	fd = open(ARCHIVO_FIFO,S_IRUSR,0400);

	if (hijo1==0)
		execl("./explorador","archivo1",NULL);
	else if (hijo2==0)
		execl("./explorador","archivo2",NULL);

	while (1) {
		read(fd,buffer,256);
		printf(buffer);
	}
}
