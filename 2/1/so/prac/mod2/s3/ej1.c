/*
Implementa un programa en C que tenga como argumento un numero entero. Este programa debe crear un proceso
hijo que se encargara de comprobar si dicho numero es un numero par o impar e informara al usuario con un 
mensaje que se enviara por la salida estandar. A su vez, el proceso padre comprobara si ese numero es
divisible por 4, e informara si lo es o no usando igualmente la salida estandar.
*/
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc,char *argv[]) {
	//Comprobacion de parametros de entrada
	if (argc!=2) {
		printf("Error en el numero de argumentos\n");
		exit (EXIT_FAILURE);
	}
	
	//Ejecucion del programa
	int num = strtol(argv[1],NULL,10);
	pid_t pid = fork();
	if (pid<0) {
		printf("Error en fork\n");
		exit (EXIT_FAILURE);
	} else if (pid==0) {
		if (num%2==0)
			printf("El numero %d es par\n",num);
		else
			printf("El numero %d no es par\n",num);
	} else {
		if (num%4==0)
			printf("El numero %d es divisible por 4\n",num);
		else
			printf("El numero %d no es divisible por 4\n",num);
	}
	
	exit (EXIT_SUCCESS);
}
