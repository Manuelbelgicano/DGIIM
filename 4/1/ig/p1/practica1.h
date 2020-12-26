// Nombre: Manuel, Apellidos: Gachs Ballegeer, DNI/pasaporte: 15473645G (DDGG IG curso 20-21)
/*
******************************************************************
 Archivo para la declaración de las clases de la práctica 1
 Manuel Gachs Ballegeer
// - Tetraedro
// - CuboColores
******************************************************************
*/
#ifndef IG_P1_HPP
#define IG_P1_HPP

#include "malla-ind.h"

class Tetraedro: public MallaInd {
public:
    Tetraedro(int sentido_altura,unsigned int tam);
};

class CuboColores: public MallaInd {
public:
    CuboColores();
};


#endif