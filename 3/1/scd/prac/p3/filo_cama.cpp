// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Práctica 3. Implementación de algoritmos distribuidos con MPI
//
// Archivo: filosofos-plantilla.cpp
// Implementación del problema de los filósofos con camaerero.
// Plantilla para completar.
//
// Historial:
// Actualizado a C++11 en Septiembre de 2017
// -----------------------------------------------------------------------------


#include <mpi.h>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <iostream>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

const int num_filosofos = 5;
const int num_procesos  = 2*num_filosofos+1;
const int id_camarero = 10;

const int etiq_sentarse = 0; // Etiqueta para sentarse
const int etiq_tomar = 1; // Etiqueta para los mensajes para adquirir un tenedor
const int etiq_dejar = 2; // Etiqueta para los mensajes para dejar un tenedor
const int etiq_levantarse = 3; // Etiqueta para levantarse

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

// ---------------------------------------------------------------------

void funcion_filosofos( int id ) {
	int peticion = id; // Valor que se pide
	int id_ten_izq = (id+1) % (num_procesos-1); //id. tenedor izq.
	int id_ten_der = (id+num_procesos-2) % (num_procesos-1); //id. tenedor der.
	
	while (true) {
		cout<<"\tFilósofo "<<id<<" solicita sentarse en la mesa"<<endl;
		MPI_Ssend(&peticion,1,MPI_INT,id_camarero,etiq_sentarse,MPI_COMM_WORLD);
		cout <<"Filósofo " <<id << " solicita ten. izq." <<id_ten_izq <<endl;
		MPI_Ssend(&peticion,1,MPI_INT,id_ten_izq,etiq_tomar,MPI_COMM_WORLD);
		cout <<"Filósofo " <<id <<" solicita ten. der." <<id_ten_der <<endl;
		MPI_Ssend(&peticion,1,MPI_INT,id_ten_der,etiq_tomar,MPI_COMM_WORLD);
		cout <<"Filósofo " <<id <<" comienza a comer" <<endl ;
		sleep_for( milliseconds( aleatorio<10,100>() ) );
		cout <<"Filósofo " <<id <<" suelta ten. izq. " <<id_ten_izq <<endl;
		MPI_Ssend(&peticion,1,MPI_INT,id_ten_izq,etiq_dejar,MPI_COMM_WORLD);
		cout<< "Filósofo " <<id <<" suelta ten. der. " <<id_ten_der <<endl;
		MPI_Ssend(&peticion,1,MPI_INT,id_ten_der,etiq_dejar,MPI_COMM_WORLD);
		MPI_Ssend(&peticion,1,MPI_INT,id_camarero,etiq_levantarse,MPI_COMM_WORLD);
		cout<<"\tFilósofo "<<id<<" se levanta de la mesa"<<endl;
		cout << "Filosofo " << id << " comienza a pensar" << endl;
		sleep_for( milliseconds( aleatorio<10,100>() ) );
	}
}
// ---------------------------------------------------------------------

void funcion_camarero() {
	int valor;
	int num_sentados = 0;
	MPI_Status estado;
	int etiq_valida;

	while (true) {
		if (num_sentados<4)
			etiq_valida = MPI_ANY_TAG;
		else
			etiq_valida = etiq_levantarse;
		
		MPI_Recv(&valor,1,MPI_INT,MPI_ANY_SOURCE,etiq_valida,MPI_COMM_WORLD,&estado);
		if (estado.MPI_TAG==etiq_sentarse) {
			num_sentados++;
			cout<<"\nCamarero sienta al filósofo "<<valor<<" en la mesa\n\n";
		} else {
			MPI_Recv(&valor,1,MPI_INT,MPI_ANY_SOURCE,etiq_levantarse,MPI_COMM_WORLD,&estado);
			num_sentados--;
		}
	}
}
// ---------------------------------------------------------------------

void funcion_tenedores( int id ) {
	int valor, id_filosofo;  // valor recibido, identificador del filósofo
	MPI_Status estado;       // metadatos de las dos recepciones

	while ( true ) {
		MPI_Recv(&valor,1,MPI_INT,MPI_ANY_SOURCE,etiq_tomar,MPI_COMM_WORLD,&estado);
		id_filosofo = estado.MPI_SOURCE;
		cout <<"\t\tTen. " <<id <<" ha sido cogido por filo. " <<id_filosofo <<endl;
		MPI_Recv(&valor,1,MPI_INT,id_filosofo,etiq_dejar,MPI_COMM_WORLD,&estado);
		cout <<"\t\tTen. "<< id<< " ha sido liberado por filo. " <<id_filosofo <<endl ;
	}
}
// ---------------------------------------------------------------------

int main( int argc, char** argv ) {
	int id_propio, num_procesos_actual ;

	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
	MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );

	if (num_procesos == num_procesos_actual) {
		// ejecutar la función correspondiente a 'id_propio'
		if (id_propio==id_camarero) {// Es el camarero
			funcion_camarero();
		}
		else if (id_propio % 2 == 0)          // si es par
			funcion_filosofos( id_propio); //   es un filósofo
		else                            // si es impar
			funcion_tenedores( id_propio ); //   es un tenedor
	} else {
		if ( id_propio == 0 ) {// solo el primero escribe error, indep. del rol
			cout << "el número de procesos esperados es:    " << num_procesos << endl
			<< "el número de procesos en ejecución es: " << num_procesos_actual << endl
			<< "(programa abortado)" << endl ;
		}
	}

	MPI_Finalize( );
	return 0;
}
// ---------------------------------------------------------------------
