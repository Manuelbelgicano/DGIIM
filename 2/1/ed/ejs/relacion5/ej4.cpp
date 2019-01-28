/**
 * @file ej4.cpp
 * @author Manuel Gachs Ballegeer
 */

#include<iostream>
#include<list>
#include<vector>

/**
 * @brief Ordena los elementos de una lista en bloques
 * @param l Lista que se va a ordenar
 * @param m Tamaño de los bloques
 */
void ordenag(std::list<int> &l,int m);
/**
 * @brief Muestra una lista en pantalla
 * @param l Lista que se muestra
 */
void print(const std::list<int> &l);

int main() {
	std::list<int> lista = {9,8,7,6,8,7,6,5,7,6,5,4,6,5,4,3,5,4,3,2,4,3,2,1};
	int numero;

	std::cout<<"LISTA: ";
	print(lista);
	std::cout<<"Tamaño de los bloques: ";
	std::cin>>numero;
	ordenag(lista,numero);
	std::cout<<"LISTA: ";
	print(lista);

	return 0;
}

void ordenag(std::list<int> &l,int m) {
	size_t tam = l.size();
	int min;
	size_t pos;
	int aux;
	std::vector<int> bloque;

	for (size_t i=0;i<tam;i++) {
		aux = l.front();
		l.pop_front();
		bloque.push_back(aux);

		if ((i+1)%m==0 || (1+i)==tam) {
			for (size_t j=0;j<bloque.size();j++) {
				min = bloque[j];
				for (size_t k=j+1;k<bloque.size();k++)
					if (bloque[k]<min) {
						min = bloque[k];
						pos = k;
					}
				if (min!=bloque[j]) {
					bloque[j] += bloque[pos];
					bloque[pos] = bloque[j] - bloque[pos];
					bloque[j] -= bloque[pos];
				}
				l.push_back(bloque[j]);
			}
			bloque.clear();
		}
	}
}

void print(const std::list<int> &l) {
	std::list<int>::const_iterator it;

	for (it=l.cbegin();it!=l.cend();it++)
		std::cout<<*it<<" ";
	std::cout<<std::endl;
}
