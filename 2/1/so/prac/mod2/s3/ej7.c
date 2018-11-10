/*
Escribe un programa que acepte como argumentos el nombre de un programa, sus argumentos si los tiene,
y opcionalmente una cadena "bg". Nuestro programa debera ejecutar el programa pasado como argumento en
"foreground" si no se especifica la cadena "bg" y en "background" en caso contrario.
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#include<malloc.h>
#include<string.h>

int main(int argc,char *argv[]) {
	//Comprobacion numero de argumentos y existencia cadena "bg"
	if (argc<2) {
		printf("Error en el numero de argumentos\n");
		exit (EXIT_FAILURE);
	}
	unsigned int bg = 1;
	if (strcmp("bg",argv[argc-1])==0)
		bg = 0;
	
	//Copiamos los argumentos
	unsigned int cont = 0;
	char pathname[100];
	strcpy(pathname,argv[1]);
	int nargs = bg==1?(argc-1):(argc-2);
	char *args[nargs+1];
	for (int i=2;i<nargs+1;i++) {
		args[i] = argv[i];
		cont++;
	}
	
	//Realizamos el programa
	pid_t pid;
	int estado;
	if ((pid=fork())==-1) {
		printf("Error en el fork: %s\n",strerror(errno));
		exit (EXIT_FAILURE);
	} else if (pid==0) {
		if (execv(pathname,args)==-1) {
			printf("Error en la ejecucion de exec: %d\n",strerror(errno));
			exit (EXIT_FAILURE);
		}
		exit (EXIT_SUCCESS);
	} else {
		if (bg==1) {
			wait(&estado);
			printf("El hijo ha terminado la ejecucion con salida %d\n",estado>>8);
		}
	}
	
	exit (EXIT_SUCCESS);
}
