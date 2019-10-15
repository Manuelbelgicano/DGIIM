#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "Semaphore.h"

using namespace std;
using namespace SEM;

const int num_items = 40;   // número de items
const int tam_vec = 10;   // tamaño del buffer
unsigned cont_prod[num_items] = {0}; // contadores de verificación: producidos
unsigned cont_cons[num_items] = {0}; // contadores de verificación: consumidos

Semaphore libres = tam_vec; // Semáforo del productor
Semaphore ocupadas = 0; // Semáforo del consumidor
int cola[tam_vec] = {0}; // Buffer
unsigned primera_libre = 0; // Primera posición libre para la escritura
unsigned primera_ocupada = 0; // Primera posición ocupada para la lectura

template<int min,int max> int aleatorio() {
	static default_random_engine generador((random_device())());
	static uniform_int_distribution<int> distribucion_uniforme(min,max);
	return distribucion_uniforme(generador);
}

int producir_dato() {
	static int contador = 0 ;
	this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
	cout << "producido: " << contador << endl << flush ;
	cont_prod[contador]++;
	
	return contador++;
}

void consumir_dato( unsigned dato )
{
   assert( dato < num_items );
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "                  consumido: " << dato << endl ;

}


//----------------------------------------------------------------------

void test_contadores()
{
   bool ok = true ;
   cout << "comprobando contadores ...." ;
   for( unsigned i = 0 ; i < num_items ; i++ )
   {  if ( cont_prod[i] != 1 )
      {  cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {  cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

//----------------------------------------------------------------------

void  funcion_hebra_productora() {
	for(unsigned i=0;i<num_items;i++) {
		int dato = producir_dato();
		libres.sem_wait(); // Espera si no hay posiciones libres
		cola[primera_libre] = dato;
		if (primera_libre==(tam_vec-1))
			primera_libre = 0;
		else
			primera_libre++;
		ocupadas.sem_signal(); // Aumenta el número de datos que se pueden leer en uno
	}
	cout<<"Productora terminada\n";
}

//----------------------------------------------------------------------

void funcion_hebra_consumidora() {
	for(unsigned i=0;i<num_items;i++) {
		int dato;
		ocupadas.sem_wait(); // Espera si no hay datos escritos
		dato = cola[primera_ocupada];
		cola[primera_ocupada] = 0;
		if (primera_ocupada==(tam_vec-1))
			primera_ocupada = 0;
		else
			primera_ocupada++;
		libres.sem_signal(); // Aumenta el número de datos que puede ser escritos en uno
		consumir_dato(dato);
	}
	cout<<"Consumidora terminada\n";
}
//----------------------------------------------------------------------

int main()
{
   cout << "--------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (solución FIFO)." << endl
        << "--------------------------------------------------------" << endl
        << flush ;

   thread hebra_productora ( funcion_hebra_productora ),
          hebra_consumidora( funcion_hebra_consumidora );

   hebra_productora.join() ;
   hebra_consumidora.join() ;

   test_contadores();
}
