/*
Indica que tipor de jerarquias de procesos se generan mediante la ejecucion de cada uno de los siguientes
fragmentos de codigo. Comprueba tu solucion implementando un codigo para generar 20 procesos en cada caso, donde cada proceso imprima su PID y el del padre, PPID
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>

int main() {
	size_t numprocs = 20;
	pid_t pid = getpid();
	pid_t childpid;
	
	//Jerarquia de procesos tipo 1
	printf("\nJerarquia de procesos tipo 1:\n");
	for (size_t i=1;i<numprocs;i++) {
		if ((childpid=fork())<0) {
			printf("Error en la creacion del %d-esimo hijo: %s\n",i,strerror(errno));
			exit (EXIT_FAILURE);
		}
		
		if (childpid==0) {
			printf("Mi PID es: %d\tEl PID de mi padre es: %d\n",getpid(),getppid());
			exit (EXIT_SUCCESS);
		}
		wait(NULL);
	}
	
	//Jerarquia de procesos tipo 2
	if (getpid()==pid) {
		printf("\nJerarquia de procesos tipo 2:\n");
		for (size_t i=1;i<numprocs;i++) {
			if ((childpid=fork())<0) {
				printf("Error en la creacion del %d-esimo hijo: %s\n",i,strerror(errno));
				exit (EXIT_FAILURE);
			}
		
			if (childpid!=0) {
				printf("Mi PID es: %d\tEl PID de mi padre es: %d\n",getpid(),getppid());
				wait(NULL);
				exit (EXIT_SUCCESS);
			}
		}
	}
	
	exit (EXIT_SUCCESS);
}
