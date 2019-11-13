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

const unsigned tipos = 2; // Tipos de clientes
const unsigned num_clientes = 6; // Número de clientes

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
	unsigned tipo_a_cortar; // Tipo de cliente que cortar
	CondVar barbero; // Espera del barbero
	CondVar cliente[tipos]; // Espera para los clientes de cada tipo
	CondVar silla; // Espera del corte de pelo
public:
	// Constructor con el número de barberos
	Barberia(unsigned tipo_inicial);
	// Función del cliente 'i' para que le corten el pelo
	void cortarPelo(unsigned i,unsigned tipo);
	// Función del barbero para pasar al próximo cliente
	void siguienteCliente();
	// Función del barbero para acabar de cortar el pelo a un cliente
	void finCliente();
};

Barberia::Barberia(unsigned tipo_inicial) {
	tipo_a_cortar = tipo_inicial;
	barbero = newCondVar();
	for (size_t i=0;i<tipos;i++)
		cliente[i] = newCondVar();
	silla = newCondVar();
}

void Barberia::cortarPelo(unsigned i,unsigned tipo) {
	if (!barbero.empty() && tipo==tipo_a_cortar) {// El barbero está dormido y es del tipo correcto
		mtx.lock();
		cout<<"El cliente "<<i<<" (tipo "<<tipo<<") llega a la barbería y despierta al barbero\n";
		mtx.unlock();
		barbero.signal();
	} else if (barbero.empty()) {// El barbero está ocupado
		mtx.lock();
		cout<<"El cliente "<<i<<" (tipo "<<tipo<<") llega a la barbería y espera (barbero ocupado)\n";
		mtx.unlock();
		cliente[tipo].wait();
	} else if (tipo!=tipo_a_cortar) {//El barbero está dormido pero no es del tipo correcto
		mtx.lock();
		cout<<"El cliente "<<i<<" (tipo "<<tipo<<") llega a la barbería y espera (tipo incorrecto)\n";
		mtx.unlock();
		cliente[tipo].wait();
	}

	// Cliente se corta el pelo
	mtx.lock();
	cout<<"\tEl cliente "<<i<<" (tipo "<<tipo<<") se está cortando el pelo\n";
	mtx.unlock();
	silla.wait();

	// Cliente se va de la barbería
	mtx.lock();
	cout<<"El cliente "<<i<<" (tipo "<<tipo<<") sale de la barbería\n";
	mtx.unlock();
}

void Barberia::siguienteCliente() {
	if (cliente[tipo_a_cortar].empty()) { // No hay clientes esperando (se duerme)
		mtx.lock();
		cout<<"El barbero no tiene clientes del tipo "<<tipo_a_cortar<<" y se va a dormir\n";
		mtx.unlock();
		barbero.wait();
	} else { // Barbero llama al siguiente cliente
		mtx.lock();
		cout<<"Barbero llama al siguiente cliente de tipo "<<tipo_a_cortar<<endl;
		mtx.unlock();
	}
	cliente[tipo_a_cortar].signal();
}

void Barberia::finCliente() {
	mtx.lock();
	cout<<"El barbero termina de pelar al cliente\n";
	mtx.unlock();
	if (tipo_a_cortar==0) // Cambia el tipo de cliente a cortar
		tipo_a_cortar = 1;
	else
		tipo_a_cortar = 0;
	silla.signal();
}

//-------------------------------------------------------------------------------------------------
// Función de cortar el pelo
void cortarPeloACliente() {
	chrono::milliseconds duracion( aleatorio<20,200>());
	mtx.lock();
	cout<<"Barbero cortando el pelo ("<<duracion.count()<<" ms)\n";
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
void funcion_hebra_cliente(MRef<Barberia> monitor,unsigned i,unsigned tipo) {
	while (true) {
		monitor->cortarPelo(i,tipo);
		esperarFueraBarberia();
	}
}

//-------------------------------------------------------------------------------------------------
// Función principal
int main() {
	MRef<Barberia> monitor = Create<Barberia>(0);
	thread clientes[num_clientes];
	thread barbero(funcion_hebra_barbero,monitor);

	for (size_t i=0;i<num_clientes;i++)
		if (i%2==0)
			clientes[i] = thread (funcion_hebra_cliente,monitor,i,1);
		else
			clientes[i] = thread (funcion_hebra_cliente,monitor,i,0);
	barbero.join();
	for (size_t i=0;i<num_clientes;i++)
		clientes[i].join();
}
