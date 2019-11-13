/**
 * @file barberia.cpp
 * @author Manuel Gachs Ballegeer
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <random> 
#include <chrono>
#include "HoareMonitor.h"

using namespace std;
using namespace HM;

mutex mtx;

//-------------------------------------------------------------------------------------------------
// Función para la creación de números aleatorios
template< int min, int max > int aleatorio() {
	static default_random_engine generador( (random_device())() );
	static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
	return distribucion_uniforme( generador );
}

//-------------------------------------------------------------------------------------------------
// Monitor de la barbería
class Barberia: public HoareMonitor {
private:
	CondVar barbero; // Espera del barbero
	CondVar cliente; // Espera de los clientes
	CondVar silla; // Espera del corte de pelo
public:
	// Constructor con el número de barberos
	Barberia();
	// Función del cliente 'i' para que le corten el pelo
	void cortarPelo(unsigned i);
	// Función del barbero para pasar al próximo cliente
	void siguienteCliente();
	// Función del barbero para acabar de cortar el pelo a un cliente
	void finCliente();
};

Barberia::Barberia() {
	barbero = newCondVar();
	cliente = newCondVar();
	silla = newCondVar();
}

void Barberia::cortarPelo(unsigned i) {
	if (!barbero.empty()) {// El barbero está dormido
		mtx.lock();
		cout<<"El cliente "<<i<<" llega a la barbería y despierta al barbero\n";
		mtx.unlock();
		barbero.signal();
	} else if (barbero.empty()) {// El barbero está ocupado
		mtx.lock();
		cout<<"El cliente "<<i<<" llega a la barbería y espera\n";
		mtx.unlock();
		cliente.wait();
	}

	// Cliente se corta el pelo
	mtx.lock();
	cout<<"El cliente "<<i<<" se corta el pelo\n";
	mtx.unlock();
	silla.wait();

	// Cliente se va de la barbería
	mtx.lock();
	cout<<"El cliente "<<i<<" sale de la barbería\n";
	mtx.unlock();
}

void Barberia::siguienteCliente() {
	if (cliente.empty()) { // No hay clientes esperando (se duerme)
		mtx.lock();
		cout<<"El barbero no tiene clientes y se va a dormir\n";
		mtx.unlock();
		barbero.wait();
	} else { // Barbero llama al siguiente cliente
		mtx.lock();
		cout<<"Barbero llama al siguiente cliente\n";
		mtx.unlock();
	}
	cliente.signal();
}

void Barberia::finCliente() {
	mtx.lock();
	cout<<"El barbero termina de pelar al cliente\n";
	mtx.unlock();
	silla.signal();
}

//-------------------------------------------------------------------------------------------------
// Función de cortar el pelo
void cortarPeloACliente() {
	chrono::milliseconds duracion( aleatorio<20,200>());
	mtx.lock();
	cout<<"\tBarbero cortando el pelo ("<<duracion.count()<<" ms)\n";
	mtx.unlock();
	this_thread::sleep_for(duracion);
}

//-------------------------------------------------------------------------------------------------
// Función de esperar fuera de la barbería
void esperarFueraBarberia() {
	chrono::milliseconds duracion( aleatorio<20,200>());
	this_thread::sleep_for(duracion);
}

//-------------------------------------------------------------------------------------------------
// Función del barbero
void funcion_hebra_barbero(MRef<Barberia> monitor) {
	while (true) {
		monitor->siguienteCliente();
		cortarPeloACliente();
		monitor->finCliente();
	}
}

//-------------------------------------------------------------------------------------------------
// Función del cliente
void funcion_hebra_cliente(MRef<Barberia> monitor,unsigned i) {
	while (true) {
		monitor->cortarPelo(i);
		esperarFueraBarberia();
	}
}

//-------------------------------------------------------------------------------------------------
// Función principal
int main() {
	unsigned num_clientes;
	MRef<Barberia> monitor = Create<Barberia>();
	
	cout<<"Introduce número de clientes: ";
	cin>>num_clientes;

	thread clientes[num_clientes];
	thread barbero(funcion_hebra_barbero,monitor);
	for (size_t i=0;i<num_clientes;i++)
		clientes[i] = thread (funcion_hebra_cliente,monitor,i);
	barbero.join();
	for (size_t i=0;i<num_clientes;i++)
		clientes[i].join();
}
