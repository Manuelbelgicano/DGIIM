#include <stdio.h>
#include <omp.h>

int main() {
   int i, n = 7;
   int a[n], suma;

   for (i=0; i<n; i++)
      a[i] = i;
  suma = 1;
#pragma omp parallel private(suma)
{
   #pragma omp for 	
   for (i=0; i<n; i++)
   {
       suma = suma + a[i];
       printf(
        "thread %d suma a[%d] / ", omp_get_thread_num(), i);
   } 
   printf(
   "\n* thread %d suma= %d", omp_get_thread_num(), suma);
}
	printf("\n* suma fuera de parallel= %d\n", suma); 

   return 0;
}

