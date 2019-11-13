/**
 * @file prodcons.cpp
 * @author Manuel Gachs Ballegeer
 */

#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "HoareMonitor.h"

using namespace std;
using namespace HM;

mutex mtx;
int tam_total; // Número total de items que se producen / leen

//-------------------------------------------------------------------------------------------------
// Función generadora de números aleatorios
template<int min,int max> int aleatorio() {
	static default_random_engine generador((random_device())());
	static uniform_int_distribution<int> distribucion_uniforme(min,max);
	return distribucion_uniforme(generador);
}

//-------------------------------------------------------------------------------------------------
// Función que produce un dato
int producir_dato() {
	static int contador = 0 ;
	this_thread::sleep_for(std::chrono::milliseconds(aleatorio<20,100>()));
	return contador++;
}

//-------------------------------------------------------------------------------------------------
// Función que consume un dato
void consumir_dato() {
	this_thread::sleep_for(std::chrono::milliseconds(aleatorio<20,100>()));
}

//-------------------------------------------------------------------------------------------------
// Monitor del productor-consumidor
class Monitor: public HoareMonitor {
private:
	int total; // Número de items a producir
	int producidos; // Número de items producidos
	int pila[20] = {0}; // Buffer
	unsigned indice; // Indice de la pila
	const static unsigned tam_vec = 20; // Tamaño de la pila
	CondVar libres; // Semáforo productor
	CondVar ocupadas; // Semáforo consumidor
public:
	// Constructor
	Monitor(int num);
	// Función para consumir
	void consumir();
	// Función para producir
	void producir();
};

Monitor::Monitor(int num) {
	total = num;
	producidos = 0;
	indice = 0;
	libres = newCondVar();
	ocupadas = newCondVar();
}

void Monitor::consumir() {
	if (indice==0) // Si la pila está vacía espera
		ocupadas.wait();
	indice--;
	int dato = pila[indice];
	pila[indice] = 0;
	mtx.lock();
	cout<<"Se consume el dato: "<<dato<<endl;
	mtx.unlock();
}

void Monitor::producir() {
	if ((indice+1)==tam_vec) // Si la pila está llena espera
		libres.wait();
	int dato = producir_dato();
	mtx.lock();
	cout<<"Se produce el dato: "<<dato<<endl;
	mtx.unlock();
	pila[indice] = dato;
	indice++;
	ocupadas.signal();
}

//-------------------------------------------------------------------------------------------------
// Función de la hebra productora
void  funcion_hebra_productora(MRef<Monitor> monitor,unsigned k,unsigned j) {
	for (size_t i=0;i<k;i++)
		monitor->producir();
	cout<<"\tTermina hebra productora número "<<j<<endl;
}

//-------------------------------------------------------------------------------------------------
// Función de la hebra consumidora
void funcion_hebra_consumidora(MRef<Monitor> monitor,unsigned k,unsigned j) {
	for (size_t i=0;i<k;i++)
		monitor->consumir();
	cout<<"\tTermina hebra consumidora número "<<j<<endl;
}

//-------------------------------------------------------------------------------------------------
// Programa principal
int main() {
	cout<<"--------------------------------------------------------"<<std::endl;
	cout<<"Problema de los productores-consumidores (solución LIFO)."<<std::endl;
	cout<<"--------------------------------------------------------"<<std::endl<<std::flush;

	unsigned num_prod;
	unsigned num_cons;
	cout<<"Introduce el número de items: ";
	cin>>tam_total;
	cout<<"Introduce el número de productores y de consumidores: ";
	cin>>num_prod>>num_cons;
	
	unsigned cacho_p = tam_total/num_prod;
	unsigned cacho_c = tam_total/num_prod;
	thread productores[num_prod];
	thread consumidores[num_cons];
	MRef<Monitor> monitor = Create<Monitor>(tam_total);

	for (size_t i=0;i<num_prod;i++) {
		if ((i+1)==num_prod)
			cacho_p = tam_total - (i * cacho_p);
		productores[i] = thread (funcion_hebra_productora,monitor,cacho_p,i);
	}
	for (size_t i=0;i<num_cons;i++) {
		if ((i+1)==num_cons)
			cacho_c = tam_total - (i * cacho_c);
		productores[i] = thread (funcion_hebra_consumidora,monitor,cacho_c,i);
	}
	for (size_t i=0;i<num_prod;i++)
		productores[i].join();
	for (size_t i=0;i<num_cons;i++)
		consumidores[i].join();
}
