#include <iostream>
#include <iomanip>
#include <chrono>
#include <future>
#include <vector>
#include <cmath>

using namespace std ;
using namespace std::chrono;

const long m = 1024l*1024l*1024l, n = 4;
const long tam = m/n;

// -----------------------------------------------------------------------------
double f(double x) {
	return 4.0/(1.0+x*x);
}

// -----------------------------------------------------------------------------
double calcular_integral_secuencial() {
	double suma = 0.0;
	for(long i=0;i<m;i++)
		suma += f((i+double(0.5))/m);
	return suma/m;
}

// -----------------------------------------------------------------------------
double funcion_hebra(long i) {
	double valor_min = 0 + tam*(i-1); // Mínimo valor de la muestra
	double valor_max = 0 + tam*i; // Máximo valor de la muestra
	double suma = 0.0; // Valor aproximado de la suma para la muestra
	for (long i=valor_min;i<valor_max;i++)
		suma += f((i+double(0.5))/m);

	return suma/tam;
}

// -----------------------------------------------------------------------------
double calcular_integral_concurrente() {
	future<double> futuros[n];
	double suma_total = 0.0;
	for (size_t i=0;i<n;i++) {
		futuros[i] = async(launch::async,funcion_hebra,i+1); // Calculamos la suma para cada bloque
	}
	for (size_t i=0;i<n;i++)
		suma_total += futuros[i].get(); // Sumamos los resultados parciales

	return suma_total/n;
}
// -----------------------------------------------------------------------------

int main() {
	time_point<steady_clock> inicio_sec  = steady_clock::now() ;
	const double             result_sec  = calcular_integral_secuencial(  );
	time_point<steady_clock> fin_sec     = steady_clock::now() ;
	double x = sin(0.4567);
	time_point<steady_clock> inicio_conc = steady_clock::now() ;
	const double             result_conc = calcular_integral_concurrente(  );
	time_point<steady_clock> fin_conc    = steady_clock::now() ;
	duration<float,milli>    tiempo_sec  = fin_sec  - inicio_sec ,
        tiempo_conc = fin_conc - inicio_conc ;
	const float              porc        = 100.0*tiempo_conc.count()/tiempo_sec.count() ;
	constexpr double pi = 3.14159265358979323846l ;
	  cout << "Número de muestras (m)   : " << m << endl
	<< "Número de hebras (n)     : " << n << endl
        << setprecision(18)
        << "Valor de PI              : " << pi << endl
        << "Resultado secuencial     : " << result_sec  << endl
        << "Resultado concurrente    : " << result_conc << endl
        << setprecision(5)
        << "Tiempo secuencial        : " << tiempo_sec.count()  << " milisegundos. " << endl
        << "Tiempo concurrente       : " << tiempo_conc.count() << " milisegundos. " << endl
        << setprecision(4)
        << "Porcentaje t.conc/t.sec. : " << porc << "%" << endl;
}
