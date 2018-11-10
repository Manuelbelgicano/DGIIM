/*
Implementa un programa que lance cinco procesos hijo. Cada uno de ellos se identificara en la salida
estandar, mostrando un mensaje del tipo "Soy el hijo PID". El proceso padre tendra que esperar la
finalizacion de todos sus hijos y cada vez que detecte la finalizacion de uno de sus hijos escribira
en la salida estandar un mensaje.
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>

int main() {
	pid_t pid;
	pid_t hijo;
	setvbuf(stdout,(char*)NULL,_IONBF,0);
	
	//Creacion de los 5 hijos
	for (size_t i=0;i<5;i++) {
		if ((pid=fork())==-1){
			printf("Error en fork\n");
			exit (EXIT_FAILURE);
		}
		if (pid==0) {
			hijo = getpid();
			printf("Soy el hijo %d\n",hijo);
			exit (EXIT_SUCCESS);
		}		
	}
	
	//Esperamos los 5 hijos
	for (int i=4;i>-1;i--) {
		pid = wait(NULL);
		printf("Acaba de finalizar mi hijo %d\n",pid);
		printf("Solo me quedan %d hijos vivos\n",i);
	}
}
