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
Semaphore estanquero = 1; // Semáforo del estanquero

//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------

template< int min, int max > int aleatorio()
{
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

    cout << "Fumador " << num_fumador << "  :"
          << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_fumar' milisegundos
   this_thread::sleep_for( duracion_fumar );

   // informa de que ha terminado de fumar

    cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;

}

// Función que produce un ingrediente
int producir() {
	chrono::milliseconds duracion_producir(aleatorio<20,200>());
	this_thread::sleep_for(duracion_producir);
	return aleatorio<0,2>();
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del estanquero

void funcion_hebra_estanquero() {
	int i;
	while(true) {
		estanquero.sem_wait(); // Se bloquea si ya ha producido un ingrediente
		i = aleatorio<0,2>();
		cout<<"Estanquero pone el ingrediente "<<i<<" en el mostrador\n";
		fumador[i].sem_signal(); // Desbloquea al fumador que necesita el ingrediente i
	}
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador
void  funcion_hebra_fumador(int num_fumador) {
	while(true) {
		fumador[num_fumador].sem_wait(); // Espera a tener el ingrediente que necesita
		cout<<"Fumador "<<num_fumador<<" coge el ingrediente del mostrador\n";
		estanquero.sem_signal(); // Desbloquea al estanquero para que vuelva a producir
		fumar(num_fumador);
	}
}

//----------------------------------------------------------------------

int main() {
	thread fumadores[3];
	thread estanquero(funcion_hebra_estanquero);
	for (size_t i=0;i<3;i++)
		fumadores[i] = thread (funcion_hebra_fumador,i);
	estanquero.join();
	for (size_t i=0;i<3;i++)
		fumadores[i].join();
}
