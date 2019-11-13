#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "HoareMonitor.h"

using namespace std;
using namespace HM;

const int num_items = 40;   // número de items
const int num_prod = 4; // Número de productores
const int num_cons = 2; // Número de consumidores
const int tam_vec = 10; // tamaño del buffer
unsigned cont_prod[num_items] = {0}; // contadores de verificación: producidos
unsigned cont_cons[num_items] = {0}; // contadores de verificación: consumidos
mutex mtx;

// Función generadora de números aleatorios
template<int min,int max> int aleatorio() {
	static default_random_engine generador((random_device())());
	static uniform_int_distribution<int> distribucion_uniforme(min,max);
	return distribucion_uniforme(generador);
}

// Función que produce un dato
int producir_dato() {
	static int contador = 0 ;
	this_thread::sleep_for(chrono::milliseconds(aleatorio<20,100>()));
	mtx.lock();
	cout<<"producido: "<<contador<<endl<<flush;
	mtx.unlock();
	cont_prod[contador]++;
	
	return contador++;
}

// Función que consume un dato
void consumir_dato(unsigned dato) {
	assert(dato<num_items);
	cont_cons[dato]++;
	this_thread::sleep_for(chrono::milliseconds(aleatorio<20,100>()));
	mtx.lock();
	cout<<"\tconsumido: "<<dato<<endl;
	mtx.unlock();
}

// Función que comprueba el correcto funcionamiento del programa
void test_contadores() {
	bool ok = true;
	cout<<"Comprobando contadores ...\n";
	for (size_t i=0;i<num_items;i++) {  
		if (cont_prod[i]!=1) {
			cout<<"ERROR: valor "<<i<<" producido "<<cont_prod[i]<<" veces."<<endl;
			ok = false;
		}
		if (cont_cons[i]!=1) {
			cout<<"ERROR: valor "<<i<<" consumido "<<cont_cons[i]<<" veces."<<endl;
			ok = false;
		}
	}
	if (ok)
		cout<<endl<<flush<<"Solución (aparentemente) correcta."<<endl<<flush;
}

// Monitor
class Monitor: public HoareMonitor {
private:
	const static unsigned tam_cola = 10; // Tamaño de la cola
	int cola[tam_cola] = {0}; // Buffer
	unsigned pos_libres; // Posiciones libres de la cola
	unsigned primera_libre; // Primera posición libre para la escritura
	unsigned primera_ocupada; // Primera posición ocupada para la lectura
	CondVar libres; // Cola del productor
	CondVar ocupadas; // Cola del consumidor
public:
	// Constructor
	Monitor();
	// Función para leer un dato
	int leer();
	// Función para escribir dato
	void escribir(int dato);
};

Monitor::Monitor() {
	pos_libres = tam_cola;
	primera_libre = 0;
	primera_ocupada = 0;
	libres = newCondVar();
	ocupadas = newCondVar();
}

int Monitor::leer() {
	if (pos_libres==tam_cola) // Si no hay posiciones ocupadas
		ocupadas.wait();
	int dato = cola[primera_ocupada];
	pos_libres++;
	if (primera_ocupada==(tam_cola-1))
		primera_ocupada = 0;
	else
		primera_ocupada++;
	libres.signal(); // Indica a los productores que hay una posición libre
	return dato;
}

void Monitor::escribir(int dato) {
	if (pos_libres<=0) // Si todas las posiciones están ocupadas
		libres.wait();
	cola[primera_libre] = dato;
	pos_libres--;
	if (primera_libre==(tam_cola-1))
		primera_libre = 0;
	else
		primera_libre++;
	ocupadas.signal(); // Indica a los consumidores que hay una pos libre
}

// Función de la hebra productora
void  funcion_hebra_productora(MRef<Monitor> monitor,int bloque,unsigned h) {
	for (size_t i=0;i<bloque;i++) {
		int dato = producir_dato();
		monitor->escribir(dato);
	}
	mtx.lock();
	cout<<"\t\tTermina hebra productora número: "<<h<<endl;
	mtx.unlock();
}

// Función de la hebra consumidora
void funcion_hebra_consumidora(MRef<Monitor> monitor,int bloque,unsigned h) {
	for (size_t i=0;i<bloque;i++) {
		int dato = monitor->leer();
		consumir_dato(dato);
	}
	mtx.lock();
	cout<<"\t\tTermina hebra consumidora número: "<<h<<endl;
	mtx.unlock();
}

// Programa principal
int main() {
	cout<<"--------------------------------------------------------"<<endl;
	cout<<"Problema de los productores-consumidores (solución FIFO)."<<endl;
	cout<<"--------------------------------------------------------"<<endl<<flush;

	MRef<Monitor> monitor = Create<Monitor>();
	thread productoras[num_prod];
	thread consumidoras[num_cons];

	for (size_t i=0;i<num_prod;i++)
		productoras[i] = thread (funcion_hebra_productora,monitor,num_items/num_prod,i);
	for (size_t i=0;i<num_cons;i++)
		consumidoras[i] = thread (funcion_hebra_consumidora,monitor,num_items/num_cons,i);

	for (size_t i=0;i<num_prod;i++)
		productoras[i].join();
	for (size_t i=0;i<num_cons;i++)
		consumidoras[i].join();
	
	cout<<"--------------------------------------------------------"<<endl;
	test_contadores();
}
