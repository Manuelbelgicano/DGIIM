/*
Haz una modificacion al anterior programa (ejercicio 4) en la que el proceso padre espera primero a los hijos creados en orden impar y despues a los hijos pares.
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>

int main() {
	pid_t pid[5];
	pid_t hijo;
	setvbuf(stdout,(char*)NULL,_IONBF,0);
	
	//Creacion de los 5 hijos
	for (size_t i=0;i<5;i++) {
		if ((pid[i]=fork())==-1){
			printf("Error en fork\n");
			exit (EXIT_FAILURE);
		}
		if (pid[i]==0) {
			hijo = getpid();
			printf("Soy el hijo %d\n",hijo);
			exit (EXIT_SUCCESS);
		}		
	}
	
	//Esperamos los hijos impares
	for (int i=4;i>-1;i--) {
		pid = wait(NULL);
		printf("Acaba de finalizar mi hijo %d\n",pid);
		printf("Solo me quedan %d hijos vivos\n",i);
	}
}
