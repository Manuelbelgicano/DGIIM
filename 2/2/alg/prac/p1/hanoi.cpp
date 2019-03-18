/**
   @file Resolución del problema de las Torres de Hanoi
*/
#include <iostream>
#include<chrono>
#include <ctime>
#include<vector>
using namespace std;
/**
   @brief Resuelve el problema de las Torres de Hanoi
   @param M: número de discos. M > 1.
   @param i: número de columna en que están los discos.
             i es un valor de {1, 2, 3}. i != j.
   @param j: número de columna a que se llevan los discos.
             j es un valor de {1, 2, 3}. j != i.

   Esta función imprime en la salida estándar la secuencia de 
   movimientos necesarios para desplazar los M discos de la
   columna i a la j, observando la restricción de que ningún
   disco se puede situar sobre otro de tamaño menor. Utiliza
   una única columna auxiliar.
*/

void hanoi (int M, int i, int j) {
	if (M > 0) {
		hanoi(M-1, i, 6-i-j);
		hanoi (M-1, 6-i-j, j);
	}
}

int main(int agcv,char* argv[]) {
	vector<unsigned long> tiempos;
	chrono::time_point<chrono::high_resolution_clock> t0,t1;
	int M = atoi(argv[1]);
	for (size_t i=0;i<15;i++){
		t0 = chrono::high_resolution_clock::now();
		hanoi(M, 1, 2);
		t1 = chrono::high_resolution_clock::now();
		unsigned long tfinal = chrono::duration_cast<chrono::microseconds>(t1-t0).count();
		tiempos.push_back(tfinal);
	}

	unsigned long media = 0;
	for (size_t i=0;i<tiempos.size();i++)
		media += tiempos[i];
	media = media/tiempos.size();
	cout<<M<<" "<<media<<endl;
	return 0;
}
