/**
 * @file ej3.cpp
 * @author Manuel Gachs Ballegeer
 */

#include<iostream>
#include<list>

/**
 * @brief Agrupa los elementos de una lista dejando su suma
 * 	  Eficiencia O(n)
 * @param l Lista en la que se agrupan los elementos
 * @param n Tamaño de los grupos
 */
void juntalista(std::list<int> &l,int n);
/**
 * @brief Muestra una lista en pantalla
 * @param l Lista a mostrar
 */
void print(const std::list<int> &l);

int main() {
	std::list<int> lista = {1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6};
	int numero;

	std::cout<<"LISTA:\n";
	print(lista);
	std::cout<<"Tamaño de los grupos: ";
	std::cin>>numero;
	juntalista(lista,numero);
	std::cout<<"LISTA:\n";
	print(lista);
}

void juntalista(std::list<int> &l,int n) {
	int suma = 0;
	size_t tam = l.size();

	for (size_t i=0;i<tam;i++) {
		suma += l.front();
		l.pop_front();
		if ((i+1)%n==0 || (i+1)==tam) {
			l.push_back(suma);
			suma = 0;
		}
	}
}

void print(const std::list<int> &l) {
	std::list<int>::const_iterator it;

	for (it=l.cbegin();it!=l.cend();it++)
		std::cout<<*it<<" ";
	std::cout<<std::endl;
}
