/**
 * @file test.cpp
 * @author Manuel Gacchs Ballegeer
 */

#include<iostream>
#include<list>

int orden(const std::list<int> &l) {
    std::list<int>::const_iterator it = l.cbegin();
    int aux = l.front();
    bool ordenada = true;
    bool ascendente = true;
    
    it++;
    for (it;it!=l.cend() && ordenada;it1++) {
        if (aux<*it1 && ascendente)
            aux = *it1;
        else if (aux>*it1) {
            aux = *it1;
            ascendente = false;
        } else 
            ordenada = false;
    }
    
    if (ordenada)
        return ascendente?1:2;
    else
        return 0;
}

int main() {
	std::list<int> l1 = {1,2,3,4,5,6,7,8,10};
	std::list<int> l2 = {11,9,7,6,5,4,3,2,1};
	std::list<int> l3 = {1,2,0,5,3,2,6,7,87};
	int l01,l02,l03;

	l01 = orden(l1);
	l02 = orden(l2);
	l03 = orden(l3);

	std::cout<<l01<<"-"<<l02<<"-"<<l03<<std::endl;

	return 0;
}

