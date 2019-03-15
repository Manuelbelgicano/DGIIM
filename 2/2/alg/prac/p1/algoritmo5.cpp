#include <iostream>
#include <ctime>
#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
using namespace std;

void heapsort(int T[], int num_elem);
void reajustar(int T[],int num_elem,int k);

void heapsort(int T[], int num_elem) {
	int i;
	for (i=num_elem/2;i>=0;i--)
	reajustar(T,num_elem,i);
	for (i=num_elem-1;i>=1;i--) {
		int aux = T[0];
		T[0] = T[i];
		T[i] = aux;
		reajustar(T,i,0);
	}
}

void reajustar(int T[],int num_elem,int k) {
	int j;
	int v;
	v = T[k];
	bool esAPO = false;
	while ((k<num_elem/2) && !esAPO) {
		j = k + k + 1;
		if ((j<(num_elem-1)) && (T[j]<T[j+1]))
			j++;
		if (v>=T[j])
			esAPO = true;
		T[k] = T[j];
		k = j;
	}
	T[k] = v;
}

int main(int argc,char* argv[]) {
	vector<unsigned long> tiempos;
	unsigned long t_result;
	chrono::time_point<std::chrono::high_resolution_clock> t0, t1;
	double suma=0;
	int M= atoi(argv[1]);
	int* v=new int[M];
	srand (time(NULL));

	for(int i=0;i<M;i++)
		v[i]=rand()%M;
	for(int i=0;i<15;i++) {
		t0 = chrono::high_resolution_clock::now();   
		heapsort(v,M);
		t1 = chrono::high_resolution_clock::now();
		t_result=chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
		tiempos.push_back(t_result);
	}
	for(unsigned int i=0;i<tiempos.size();i++)
		suma=suma+tiempos[i];
	double media=suma/tiempos.size();
	cout<<M<<" "<<media<<endl;
	delete [] v;
}
