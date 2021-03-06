#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
  #include <omp.h>
#else
   #define omp_get_thread_num() 0
#endif

int main(int argc, char **argv) { 
  int i, n=200,chunk,a[n],suma=0;
   if(argc < 3)     {
      fprintf(stderr,"\nFalta iteraciones o chunk \n");
      exit(-1);
     }
   n = atoi(argv[1]); if (n>200) n=200; chunk = atoi(argv[2]); 

   for (i=0; i<n; i++)       a[i] = i;
	omp_sched_t kind;
	int modifier;
	omp_get_schedule(&kind, &modifier);
 	printf("Fuera de parallel:\n\tdyn-var: %d\n\tnthreads-var: %d\n\tthread-limit-var: %d\n\trun-sched-var: %s-%d\n",omp_get_dynamic(),omp_get_max_threads(),omp_get_thread_limit(),kind,modifier);
	#pragma omp parallel 
	{
	omp_sched_t kind2;
	int modifier2;
	#pragma omp master
	omp_get_schedule(&kind2, &modifier2);
 	printf("Fuera de parallel:\n\tdyn-var: %d\n\tnthreads-var: %d\n\tthread-limit-var: %d\n\trun-sched-var: %s-%d\n",omp_get_dynamic(),omp_get_max_threads(),omp_get_thread_limit(),kind2,modifier2);
	}
	return(0);
}

