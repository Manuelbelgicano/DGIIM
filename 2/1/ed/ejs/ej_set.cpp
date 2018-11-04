/**
 * @file ej_set.cpp
 * @author Manuel Gachs Ballegeer
 */

#include <iostream>
#include <set>
#include <string>

/*
Trabajar con conjuntos de tipo char
 - Union de conjuntos
 - Interseccion de conjuntos
 - Complementos de conjuntos
 - Intercambio de conjuntos
 - Borrado de conjuntos
 - Búsqueda de elementos de un conjunto
*/

//Funciones auxiliares
void show(const std::set<char>& a); //Muestra datos del conjunto
std::set<char> operator+(const std::set<char>& a, const std::set<char>& b); //Union de conjuntos
std::set<char> operator*(const std::set<char>& a, const std::set<char>& b); //Interseccion de conjuntos
std::set<char> operator/(const std::set<char>& a, const std::set<char>& b); //Diferencia de conjuntos

//Programa principal
int main() {
	//Cadenas de caracteres conformantes de los conjuntos
	std::string s1 = "Celia Aparicio del Val";
	std::string s2 = "Manuel Gachs Ballegeer";
	
	//Primer conjunto
	std::set<char> c1(s1.begin(),s1.end());
	std::cout<<"Primer conjunto:\n";
	show(c1);
	
	//Segundo conjunto
	std::set<char> c2(s2.begin(),s2.end());
	std::cout<<"Segundo conjunto:\n";
	show(c2);
	
	//Union de conjuntos
	std::set<char> un = c1 + c2;
	std::cout<<"Union de los conjuntos (un):\n";
	show(un);
	
	//Interseccion de conjuntos
	std::set<char> in = c1*c2;
	std::cout<<"Interseccion de los conjuntos (in):\n";
	show(in);
	
	//Diferencia de conjuntos
	std::set<char> di = c1/c2;
	std::cout<<"Complemento de los conjuntos (di):\n";
	show(di);
	
	//Intercambio y borrado de conjuntos
	std::cout<<"Intercambio \"in\" con \"di\":\n";
	di.swap(in);
	in.clear();
	show(di);
	std::cout<<"Vaciado de \"in\":\n";
	if (in.empty())
		std::cout<<"El conjunto \"in\" esta vacio\n";
	else
		std::cout<<"Eres tontisimo\n"; //jeje	
	
	//Veamos si esta la letra de la eleccion en los conjuntos
	char letra = 'x';
	std::cout<<"Introduce una letra: ";
	std::cin>>letra;
	if (c1.count(letra)!=0)
		std::cout<<"La letra "<<letra<<" esta en el primer conjunto\n";
	else
		std::cout<<"La letra "<<letra<<" no esta en el primer conjunto\n";
	if (c2.count(letra)!=0)
		std::cout<<"La letra "<<letra<<" esta en el segundo conjunto\n";
	else
		std::cout<<"La letra "<<letra<<" no esta en el segundo conjunto\n";

	return 0;	
}

//Implementacion de las funciones
void show(const std::set<char>& a) {
	std::cout<<"Tamaño del conjunto: "<<a.size()<<std::endl;
	std::cout<<"Elementos del conjunto:\n\t";
	for (std::set<char>::iterator i=a.begin();i!=a.end();++i)
		std::cout<<*i<<" ";
	std::cout<<std::endl;
}

std::set<char> operator+(const std::set<char>& a, const std::set<char>& b) {
	std::set<char> un;
	un.insert(a.begin(),a.end());
	un.insert(b.begin(),b.end());
	return un;
}

std::set<char> operator*(const std::set<char>& a, const std::set<char>& b) {
	std::set<char> in;
	for (std::set<char>::iterator i=a.begin();i!=a.end();++i)
		if (b.find(*i)!=b.end())
			in.insert(*i);
	return in;
}

std::set<char> operator/(const std::set<char>& a, const std::set<char>& b) {
	std::set<char> di;
	for (std::set<char>::iterator i=a.begin();i!=a.end();i++)
		if (b.find(*i)==b.end())
			di.insert(*i);
	return di;
}
