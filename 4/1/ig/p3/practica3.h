// Nombre: Manuel, Apellidos: Gachs Ballegeer, DNI/pasaporte: 15473645G (DDGG IG curso 20-21)
/*
******************************************************************
Archivo para la declaración de las figuras auxiliares para la práctica 3
Manuel Gachs Ballegeer
******************************************************************
*/
#ifndef IG_P3_HPP
#define IG_P3_HPP

#include "malla-revol.h"
#include "malla-ind.h"
#include "practica2.h"
#include "practica1.h"

class Dedo: public MallaInd {
public:
    Dedo();
};

class Palma: public MallaRevol {
public:
    Palma(unsigned nperfiles);
};

class Torso: public MallaInd {
public:
    Torso();
};

class Ala: public MallaInd {
public:
    Ala();
};

class Barriga: public MallaRevol {
public:
    Barriga(unsigned nperfiles);
};

class CuelloExtension: public Cubo {
public:
    CuelloExtension();
};

class Cuello: public MallaInd {
public:
    Cuello();
};

class CabezaPosterior: public MallaInd {
public:
    CabezaPosterior();
};

class CabezaFrontal: public MallaInd {
public:
    CabezaFrontal();
};

class Ojo: public Esfera {
public:
    Ojo(unsigned nperfiles);
};

class MedioPico: public Tetraedro {
public:
    MedioPico();
};

#endif