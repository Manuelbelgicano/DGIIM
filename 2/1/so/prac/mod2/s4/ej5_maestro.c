/*
Este ejercicio se basa en la idea de utilizar varios procesos para realizar partes de una computación en
paralelo. Para ello, deberá construir un programa que siga el esquema de computación maestro-esclavo, en
el cual existen varios procesos trabajadores (esclavos) idénticos y un único proceso que reparte trabajo
y reúne resultados (maestro). Cada esclavo es capaz de realizar una computación que le asigne el maestro 
y enviar a este último los resultados para que sean mostrados en pantalla por el maestro.
El intervalo de números naturales donde calcular los número primos se pasará como argumento al programa 
maestro. El maestro creará dos procesos esclavos y dividirá el intervalo en dos subintervalos de igual
tamaño pasando cada subintervalo como argumento a cada programa esclavo. Por ejemplo, si al maestro le
proporcionamos el intervalo entre 1000 y 2000, entonces un esclavo debe calcular y devolver los números
primos comprendidos en el subintervalo entre 1000 y 1500, y el otro esclavo entre 1501 y 2000. El maestro creará dos cauces sin nombre y se encargará de su redirección para comunicarse con los procesos esclavos.   
El maestro irá recibiendo y mostrando en pantalla (también uno a uno) los números primos calculados por 
los esclavos en orden creciente. 
*/

/*------------------------------------------------------------------------------------------------------
--------------------------------------------PROGRAMA MAESTRO--------------------------------------------
--------------------------------------------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main(int argc,char *argv[]) {
	//Comprobacion parametros iniciales
	if (argc!=3) {
		printf("Error en el numero de argumentos\n");
		exit (EXIT_FAILURE);
	}
	int min = strtol(argv[1],NULL,10);
	int max = strtol(argv[2],NULL,10);
	if (max<=min) {
		printf("Error en los argumentos: El intervalo es imposible\n");
		exit (EXIT_FAILURE);
	}
	//Creacion argumentos para los esclavos
	char min_e1[20], max_e1[20];
	sprintf(min_e1,"%d",min);
	sprintf(max_e1,"%d",min+(max-min)/2);
	char min_e2[20], max_e2[20];
	sprintf(min_e2,"%d",min+((max-min)/2)+1);
	sprintf(max_e2,"%d",max);
	
	//Creacion de los cauces y esclavos
	int fd1[2];
	int fd2[2];
	pipe(fd1);
	pipe(fd2);
	pid_t esclavo1;
	pid_t esclavo2;
	int num;
	
	//Primer esclavo
	if ((esclavo1=fork())<0) {
		printf("Error %d en el fork\n",errno);
		exit (EXIT_FAILURE);
	} else if (esclavo1==0) {
		close(fd1[0]);
		dup2(fd1[1],STDOUT_FILENO);
		if (execl("./esclavo","esclavo",min_e1,max_e1,NULL)==-1) {
			printf("Error en la ejecucion del primer esclavo\n");
			exit (EXIT_FAILURE);
		}
	} else {
		printf("\nNumeros primos del intervalo %d-%d\n",min,min+(max-min)/2);
		close(fd1[1]);
		while (read(fd1[0],&num,sizeof(int)))
			printf("%d ",num);
	}
	
	//Segundo esclavo
	if ((esclavo2=fork())<0) {
		printf("Error %d en el fork\n",errno);
		exit (EXIT_FAILURE);
	} else if (esclavo2==0) {
		close(fd2[0]);
		dup2(fd2[1],STDOUT_FILENO);
		if (execl("./esclavo","esclavo",min_e2,max_e2,NULL)==-1) {
			printf("Error en la ejecucion del segundo esclavo\n");
			exit (EXIT_FAILURE);
		}
	} else {
		printf("\nNumeros primos del intervalo %d-%d\n",min+((max-min)/2)+1,max);
		close(fd2[1]);
		while (read(fd2[0],&num,sizeof(int)))
			printf("%d ",num);
	}
	
	exit (EXIT_SUCCESS);
}
