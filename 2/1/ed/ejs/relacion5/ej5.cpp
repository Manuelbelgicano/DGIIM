/**
 * @file ej5.cpp
 * @author Manuel Gachs Ballegeer
 */

#include<iostream>
#include<list>

/**
 * @brief Calcula la distancia entre el valor mínimo y el máximo en una lista.
 * 	  En caso de existir dos mínimos se toma como la primera ocurrencia del mismo.
 * 	  En caso de existir dos máximos se toma la última ocurrencia del mismo.
 * @param l Lista en la que se quiere calcular
 * @return La distancia entre los dos valores
 */
int dminmax(std::list<int> &l);
/**
 * @brief Muestra una lista en pantalla
 * @param l Lista que se muestra
 */
void print(const std::list<int> &l);

int main() {
	std::list<int> lista1 = {9,3,5,7,6,4,5,8,9,0,6,3,0};
	std::list<int> lista2 = {1,5,8,9,5,3,1,2,3,4,6,7,10};

	std::cout<<"LISTA 1ª: ";
	print(lista1);
	std::cout<<"La distancia es: "<<dminmax(lista1);
	std::cout<<"\nLISTA 2ª: ";
	print(lista2);
	std::cout<<"La distancia es: "<<dminmax(lista2)<<std::endl;

	return 0;
}

int dminmax(std::list<int> &l) {
	std::list<int>::iterator it;
	int max = l.back();
	int min = l.front();
	size_t pos = 0;
	size_t p_max = l.size()-1;
	size_t p_min = 0;

	for (it=l.begin();it!=l.end();it++) {
		if ((*it)<min) {
			min = *it;
			p_min = pos;
		} else if ((*it)>=max) {
			max = *it;
			p_max = pos;
		}
		pos++;
	}
	return p_max-p_min;
}

void print(const std::list<int> &l) {
	std::list<int>::const_iterator it;

	for (it=l.cbegin();it!=l.cend();it++)
		std::cout<<*it<<" ";
	std::cout<<std::endl;
}
