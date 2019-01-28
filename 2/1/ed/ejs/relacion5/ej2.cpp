/**
 * @file ej2.cpp
 * @author Manuel Gachs Ballegeer
 */

#include<iostream>
#include<list>

/**
 * @brief Traslada los primeros n elementos de una lista al final
 * @param l Lista con la que se trabaja
 * @param n Número de elementos a trasladar
 */
void rotalista(std::list<int> &l,int n);
/**
 * @brief Muestra una lista en pantalla
 * @param l Lista que se muestra
 */
void print(const std::list<int> &l);

int main() {
	std::list<int> lista = {1,9,2,8,3,7,4,6,5};
	int numero;

	std::cout<<"LISTA:\n";
	print(lista);
	std::cout<<"Número de elementos a trasladar: ";
	std::cin>>numero;
	rotalista(lista,numero);
	std::cout<<"LISTA:\n";
	print(lista);

	return 0;
}

void rotalista(std::list<int> &l,int n) {
	int aux;

	for (size_t i=0;i<n;i++) {
		aux = l.front();
		l.pop_front();
		l.push_back(aux);
	}
}

void print(const std::list<int> &l) {
	std::list<int>::const_iterator it;

	for (it=l.cbegin();it!=l.cend();it++)
		std::cout<<*it<<" ";
	std::cout<<std::endl;
}
