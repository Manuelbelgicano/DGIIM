/*
Este ejercicio se basa en la idea de utilizar varios procesos para realizar partes de una computación en
paralelo. Para ello, deberá construir un programa que siga el esquema de computación maestro-esclavo, en
el cual existen varios procesos trabajadores (esclavos) idénticos y un único proceso que reparte trabajo
y reúne resultados (maestro). Cada esclavo es capaz de realizar una computación que le asigne el maestro 
y enviar a este último los resultados para que sean mostrados en pantalla por el maestro.
El programa esclavo tiene como argumentos el extremo inferior y superior del intervalo sobre  el que buscará
números primos. Para identificar un número primo utiliza el siguiente método concreto: un número n es primo
si no es divisible por ningún k tal que 2 < k <= sqrt(n), donde sqrt corresponde a la función de cálculo de
la raíz cuadrada (consulte dicha función en el manual). El esclavo envía al maestro cada primo encontrado
como un dato entero (4 bytes) que escribe en la salida estándar, la cuál se tiene que encontrar 
redireccionada a un cauce sin nombre. Los dos cauces sin nombre necesarios, cada uno para comunicar cada
esclavo con el maestro, los creará el maestro inicialmente. Una vez que un esclavo haya calculado y enviado
(uno a uno) al maestro todos los primos en su correspondiente intervalo terminará.
*/

/*------------------------------------------------------------------------------------------------------
--------------------------------------------PROGRAMA ESCLAVO--------------------------------------------
--------------------------------------------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<math.h>

/**
 * @brief Comprueba si un numero es primo
 * @param num Numero
 * @return Devuelve 0 si es primo y un numero positivo si lo es. 
*/
int es_primo(int num);

int main(int argc,char *argv[]) {
	//Transformacion a numeros enteros
	int min = atoi(argv[1]);
	int max = atoi(argv[2]);
	
	//Busqueda de primos
	for (int i=min;i<=max;i++) {
		if (es_primo(i)==0)
			write(STDOUT_FILENO,&i,sizeof(int));
	}
	
	exit (EXIT_SUCCESS);
}

int es_primo(int num) {
	int max = sqrt(num);
	int primo = 0;
	
	for (int i=2;i<max && primo==0;i++)
		if (num%i==0)
			primo = i;
	return primo;		
}
