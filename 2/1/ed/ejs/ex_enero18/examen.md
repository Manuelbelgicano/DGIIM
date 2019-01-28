1. Supongamos que tenemos una clase Liga que almacena los resultados de enfrentamientos en una liga de baloncesto:

```c++
struct enfrentamiento{
	unsigned char eq1,eq2; // códigos de los equipos enfrentados
	unsigned int puntos_eq1, puntos_eq2; //puntos por cada equipo
};
class liga{
private:
	std::list<enfrentamiento> res;
...
};
```

- Implementa un método que dado un código de equipo obtenga el número de enfrentamientos que ha ganado.

```c++
unsigned int get_num_ganados(unsigned char eq) {
    std::list<enfrentamiento>::iterator it;
    unsigned int aux = 0;
    
    for (it=res.begin();it!=res.end();it++) {
        if (*it.eq1==eq)
            if (*it.puntos_eq1>*it.puntos_eq2)
                aux++;
        else if (*it.eq2==eq)
            if (*it.puntos_eq2>*it.puntos_eq1)
                aux++;
    }
    return aux;
}
```

- Implementa la clase iterator dentro de la clase Liga que permita recorrer los enfrentamientos en los que el resultado ha sido el empate. Implementar los métodos begin() y end().

```c++
class Liga {
...
class iterator {
private:
    std::list<enfrentamiento>::iterator it;
    std::list<enfrentamiento>::iterator end;
public:
    iterator() {}
    ~iterator() {}
    enfrentamiento& operator*() {return *it;}
    iterator& operator++() {
        ++it;
        while (*it.puntos_eq1!=*it.puntos_eq2 && it!=end)
            ++it;
        return it;
    }
    iterator& operator=(const iterator &_it) {
        it = _it.it;
        end = _it.end;
        return *this;
    }
    bool operator==(const iterator &_it) const {return it==_it.it;}
    bool operator!=(const iterator &_it) const {return !(*this==_it);}
};
    iterator& begin() {
        Liga::iterator it;
        it.it = res.begin();
        it.end = res.end();
        while (*it.puntos_eq1!=*it.puntos_eq2 && it.it!=it.end)
            ++it;
        return it;
    }
    iterator& end() {
        Liga::iterator it;
        it.it = res.end();
        it.end = res.end();
        return it;
    }
};
```

**2.** Implementa una función `int orden(const list<int> &l);` que devuelva 1 si L está ordenada de forma ascendente de principio a fin, 2 si lo está de forma descendente y 0 si no está ordenada de ninguna forma.

```c++
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
```

