#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "HoareMonitor.h"

using namespace std;
using namespace HM;

mutex mtx;

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
// Clase Monitor del programa
class Estanco: public HoareMonitor {
private:
	int mostrador; // Mostrador del estanco
	static const unsigned fumadores = 3;  // Número de fumadores
	CondVar estanquero; // Cola para el estanquero
	CondVar cola_fumadores[fumadores]; // Cola para los fumadores
public:
	// Constructor
	Estanco();
	// Función del estanquero para producir un ingrediente 'i'
	unsigned producirIngrediente();
	// Función del estanquero para poner un ingrediente 'i' en el mostrador
	void ponerIngrediente(unsigned i);
	// Función del estanquero para poner esperar a que un fumador recoja un ingrediente
	void esperarRecogidaIngrediente();
	// Función de los fumadores para recoger un ingrediente 'i'
	void obtenerIngrediente(int i);
};

Estanco::Estanco() {
	mostrador = -1;
	estanquero = newCondVar();
	for (size_t i=0;i<fumadores;i++)
		cola_fumadores[i] = newCondVar();
}

unsigned Estanco::producirIngrediente() {
	chrono::milliseconds duracion_producir(aleatorio<20,200>());
	this_thread::sleep_for(duracion_producir);
	return aleatorio<0,2>();
}

void Estanco::ponerIngrediente(unsigned i) {
	mostrador = i;
	mtx.lock();
	cout<<"Estanquero pone el ingrediente "<<i<<" en el mostrador\n";
	mtx.unlock();
	cola_fumadores[i].signal();
}

void Estanco::esperarRecogidaIngrediente() {
	if(mostrador!=-1)
		estanquero.wait();
}

void Estanco::obtenerIngrediente(int i) {
	if(mostrador!=i)
		cola_fumadores[i].wait();
	mtx.lock();
	cout<<"Fumador "<<i<<" coge el ingrediente del mostrador\n";
	mtx.unlock();
	mostrador = -1;
	estanquero.signal();
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
// función que ejecuta la hebra del estanquero

void funcion_hebra_estanquero(MRef<Estanco> monitor) {
	unsigned ingrediente;
	while(true) {
		ingrediente = monitor->producirIngrediente();
		monitor->ponerIngrediente(ingrediente);
		monitor->esperarRecogidaIngrediente();
	}
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador
void  funcion_hebra_fumador(MRef<Estanco> monitor, int num_fumador) {
	while(true) {
		monitor->obtenerIngrediente(num_fumador);
		fumar(num_fumador);
	}
}

//----------------------------------------------------------------------

int main() {
	MRef<Estanco> monitor = Create<Estanco>();
	thread fumadores[3];
	thread estanquero(funcion_hebra_estanquero,monitor);
	for (size_t i=0;i<3;i++)
		fumadores[i] = thread (funcion_hebra_fumador,monitor,i);
	estanquero.join();
	for (size_t i=0;i<3;i++)
		fumadores[i].join();
}
