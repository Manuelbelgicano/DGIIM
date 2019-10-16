#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "Semaphore.h"

using namespace std ;
using namespace SEM ;

Semaphore fumador[3] = {0,0,0}; // Semáforos de los fumadores
Semaphore ingrediente_recogido = 1; // Semáforo del estanquero

Semaphore estanquero[2] = {0,0}; // Semáforos de los estanqueros
Semaphore gestor_libre = 1; // Semáforo del gestor

mutex mtx; // Cerrojo para las salidad

//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------

template< int min, int max > int aleatorio() {
	static default_random_engine generador( (random_device())() );
	static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
	return distribucion_uniforme( generador );
}

//-------------------------------------------------------------------------
// Función que simula la acción de fumar, como un retardo aleatoria de la hebra

void fumar(int num_fumador) {

	// calcular milisegundos aleatorios de duración de la acción de fumar)
	chrono::milliseconds duracion_fumar( aleatorio<20,200>() );

	// informa de que comienza a fumar

	mtx.lock();
	cout << "Fumador " << num_fumador << "  :" 
	<< " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;
	mtx.unlock();

	// espera bloqueada un tiempo igual a ''duracion_fumar' milisegundos
	this_thread::sleep_for( duracion_fumar );

	// informa de que ha terminado de fumar
	mtx.lock();
	cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;
	mtx.unlock();
}

//----------------------------------------------------------------------
// Función que produce un ingrediente
int producir() {
	chrono::milliseconds duracion_producir(aleatorio<20,200>());
	this_thread::sleep_for(duracion_producir);
	return aleatorio<0,2>();
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del estanquero
void funcion_hebra_estanquero(int num_estanquero) {
	int i;
	unsigned contador = 0;
	while(true) {
		estanquero[num_estanquero].sem_wait(); // Se bloquea si el gestor no le da paso
		for (size_t j=0;j<5;j++) {
			ingrediente_recogido.sem_wait(); // Se bloquea si ya ha producido un ingrediente
			i = producir();
			mtx.lock();
			cout<<"Estanquero número "<<num_estanquero<<" pone el ingrediente "
			<<i<<" en el mostrador (iteración nº "<<j+1<<")\n";
			mtx.unlock();
			fumador[i].sem_signal(); // Desbloquea al fumador que necesita el ingrediente i
		}
		gestor_libre.sem_signal(); // Desbloquea al gestor para que elija un estanquero
	}
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador
void  funcion_hebra_fumador(int num_fumador) {
	while(true) {
		fumador[num_fumador].sem_wait(); // Espera a tener el ingrediente que necesita
		mtx.lock();
		cout<<"Fumador "<<num_fumador<<" coge el ingrediente del mostrador\n";
		mtx.unlock();
		ingrediente_recogido.sem_signal(); // Desbloquea al estanquero para que vuelva a producir
		fumar(num_fumador);
	}
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del gestor central
void funcion_hebra_gestor() {
	int eleccion = 0;
	while(true) {
		gestor_libre.sem_wait(); // Se bloquea si el estanquero seleccionado todavía está trabajando
		eleccion = aleatorio<0,1>();
		mtx.lock();
		cout<<"\n\tEl gestor elige al estanquero número "<<eleccion<<" para producir ingredientes\n\n";
		mtx.unlock();
		estanquero[eleccion].sem_signal(); // Desbloquea al estanquero elección
	}
}

int main() {
	thread fumadores[3];
	thread estanqueros[2];
	thread gestor(funcion_hebra_gestor);
	for (size_t i=0;i<3;i++)
		fumadores[i] = thread (funcion_hebra_fumador,i);
	for (size_t i=0;i<2;i++)
		estanqueros[i] = thread (funcion_hebra_estanquero,i);
	gestor.join();
	for (size_t i=0;i<3;i++)
		fumadores[i].join();
	for (size_t i=0;i<2;i++)
		estanqueros[i].join();
}
