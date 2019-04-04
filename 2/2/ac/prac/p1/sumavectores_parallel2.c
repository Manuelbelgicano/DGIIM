#include <stdlib.h> // biblioteca con funciones atoi(), malloc() y free()
#include <stdio.h> // biblioteca donde se encuentra la función printf()
#include <omp.h>
#define MAX 33554432	//=2^25

int main(int argc, char *argv[]){
	double t1, t2, ncgt;
	//Leer argumento de entrada (nº de componentes del vector)
	if (argc<2){
		printf("Faltan nº componentes del vector\n");
		exit(-1);
	}
	unsigned int N = atoi(argv[1]);
	if (N>MAX) 
		N = MAX;
	//Inicializar vectores
	int seccion = N/4; 
	double v1[N], v2[N], v3[N];
	#pragma omp parallel
	{
	#pragma omp sections
	{
	#pragma omp section
	for(int i=0; i<seccion; i++) {
		v1[i] = N*1.0+i*0.1;
		v2[i] = N*2.0-i*1.0;
	}
	#pragma omp section
	for(int i=seccion; i<2*seccion; i++) {
		v1[i] = N*1.0+i*0.1;
		v2[i] = N*2.0-i*1.0;
	}
	#pragma omp section
	for(int i=2*seccion; i<3*seccion; i++) {
		v1[i] = N*1.0+i*0.1;
		v2[i] = N*2.0-i*1.0;
	}
	#pragma omp section
	for(int i=3*seccion; i<N; i++) {
		v1[i] = N*1.0+i*0.1;
		v2[i] = N*2.0-i*1.0;
	}
	}
	//Calcular suma de vectores
	#pragma omp single
	t1 = omp_get_wtime();
	#pragma omp sections
	{
	#pragma omp section
	for(int i=0; i<seccion; i++)
		v3[i] = v1[i] + v2[i];
	#pragma omp section
	for(int i=seccion; i<2*seccion; i++)
		v3[i] = v1[i] + v2[i];
	#pragma omp section
	for(int i=2*seccion; i<3*seccion; i++)
		v3[i] = v1[i] + v2[i];
	#pragma omp section
	for(int i=3*seccion; i<N; i++)
		v3[i] = v1[i] + v2[i];
	}
	}
	t2 = omp_get_wtime();
	ncgt = t2 -t1;
	//Imprimir resultado de la suma y el tiempo de ejecución
	int end = N-1;
	printf("Tiempo(seg.):%11.9f\tTamaño Vectores:%u\n",ncgt,N);
	printf("Sumas:\n\tv3[0] = v1[0] + v2[0]\n\t%f = %f + %f",v3[0],v1[0],v2[0]);
	printf("\n\tv3[%d] = v1[%d] + v2[%d]\n\t%f = %f + %f \n",end,end,end,v3[end],v1[end],v2[end]);
	return 0;
}
