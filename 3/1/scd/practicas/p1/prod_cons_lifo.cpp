/**
 * @file prod_cons_lifo.cpp
 */

#include <iostream>
#include <cassert>
#include <thread>
#include <atomic>
#include <random>
#include "Semaphore.h"

const int num_items = 40;   // número de items
const int tam_vec = 10;   // tamaño del buffer
unsigned cont_prod[num_items] = {0}; // contadores de verificación: producidos
unsigned cont_cons[num_items] = {0}; // contadores de verificación: consumidos

int pila[tam_vec] = {0}; // Buffer
std::atomic<int> primera_libre; // Posición de la pila
SEM::Semaphore libres = tam_vec; // Semáforo del productor
SEM::Semaphore ocupadas = 0;  // Semáforo del consumidor

// Función generadora de números aleatorios
template<int min,int max> int aleatorio() {
	static std::default_random_engine generador((std::random_device())());
	static std::uniform_int_distribution<int> distribucion_uniforme(min,max);
	return distribucion_uniforme(generador);
}

// Función que produce un dato
int producir_dato() {
	static int contador = 0 ;
	std::this_thread::sleep_for(std::chrono::milliseconds(aleatorio<20,100>()));
	std::cout<<"producido: "<<contador<<std::endl<<std::flush;
	cont_prod[contador]++;
	
	return contador++;
}

// Función que consume un dato
void consumir_dato(unsigned dato) {
	assert(dato<num_items);
	cont_cons[dato]++;
	std::this_thread::sleep_for(std::chrono::milliseconds(aleatorio<20,100>()));
	std::cout<<"\tconsumido: "<<dato<<std::endl;
}

// Función que comprueba el correcto funcionamiento del programa
void test_contadores() {
	bool ok = true;
	std::cout<<"Comprobando contadores ...\n";
	for (size_t i=0;i<num_items;i++) {  
		if (cont_prod[i]!=1) {
			std::cout<<"ERROR: valor "<<i<<" producido "<<cont_prod[i]<<" veces."<<std::endl;
			ok = false;
		}
		if (cont_cons[i]!=1) {
			std::cout<<"ERROR: valor "<<i<<" consumido "<<cont_cons[i]<<" veces."<<std::endl;
			ok = false;
		}
	}
	if (ok)
		std::cout<<std::endl<<std::flush<<"Solución (aparentemente) correcta."<<std::endl<<std::flush;
}

// Función de la hebra productora
void  funcion_hebra_productora() {
	for (size_t i=0;i<num_items;i++) {
		int dato = producir_dato();
		libres.sem_wait(); // Espera si no quedan posiciones libres en la pila
		pila[primera_libre] = dato;
		primera_libre++;
		ocupadas.sem_signal(); // Da paso al consumidor para que consuma un dato
	}
	std::cout<<"Termina hebra productora\n";
}

// Función de la hebra consumidora
void funcion_hebra_consumidora() {
	for (size_t i=0;i<num_items;i++) {
		ocupadas.sem_wait(); // Espera si no se puede consumir ningún valor
		primera_libre--;
		int dato = pila[primera_libre];
		pila[primera_libre] = 0;
		libres.sem_signal(); // Da paso al productor para que producza un nuevo dato
		consumir_dato(dato);
	}
	std::cout<<"Termina hebra consumidora\n";
}

// Programa principal
int main() {
	std::cout<<"--------------------------------------------------------"<<std::endl;
	std::cout<<"Problema de los productores-consumidores (solución LIFO)."<<std::endl;
	std::cout<<"--------------------------------------------------------"<<std::endl<<std::flush;

	primera_libre = 0;
	std::thread hebra_productora(funcion_hebra_productora),hebra_consumidora(funcion_hebra_consumidora);
	hebra_productora.join();
	hebra_consumidora.join();
	test_contadores();
}
