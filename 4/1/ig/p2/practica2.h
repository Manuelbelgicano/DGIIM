// Nombre: Manuel, Apellidos: Gachs Ballegeer, DNI/pasaporte: 15473645G (DDGG IG curso 20-21)
/*
******************************************************************
Archivo para la declaración de las clases de la práctica 2
Manuel Gachs Ballegeer
    - Cilindro
    - Cono
    - Esfera
******************************************************************
*/
#ifndef IG_P2_HPP
#define IG_P2_HPP

#include "malla-revol.h"

class Cilindro: public MallaRevol {
public:
    // Constructor: crea el perfil original y llama a inicializar
    // la base tiene el centro en el origen, el radio y la altura son 1
    Cilindro(const int num_verts_per,const unsigned nperfiles);
};

class Cono: public MallaRevol {
public:
    // Constructor: crea el perfil original y llama a inicializar
    // la base tiene el centro en el origen, el radio y altura son 1
    Cono(const int num_verts_per,const unsigned nperfiles);
};

class Esfera: public MallaRevol {
public:
    // Constructor: crea el perfil original y llama a inicializar
    // La esfera tiene el centro en el origen, el radio es la unidad
    Esfera(const int num_verts_per,const unsigned nperfiles);
private:
    std::vector<Tupla3f> semicircunferencia(std::vector<Tupla3f> & recta,const unsigned nperfiles);
};

#endif