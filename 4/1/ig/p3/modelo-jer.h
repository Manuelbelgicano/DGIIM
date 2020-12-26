// Nombre: Manuel, Apellidos: Gachs Ballegeer, DNI/pasaporte: 15473645G (DDGG IG curso 20-21)
/*
******************************************************************
Archivo para la declaración de las clases de la práctica 3
Manuel Gachs Ballegeer
******************************************************************
*/

#ifndef IG_MOD_JER_HPP
#define IG_MOD_JER_HPP

#include "grafo-escena.h"

class Pie: public NodoGrafoEscena {
public:
    Pie();
};

class Pico: public NodoGrafoEscena {
public:
    Pico();
};

class Cara: public NodoGrafoEscena {
public:
    Cara();
};

// Craneo: Movimiento lateral rotatorio (gira la cabeza)
class Craneo: public NodoGrafoEscena {
public:
    Craneo(Matriz4f * &rotacion);
};

class CuelloFinal: public NodoGrafoEscena {
public:
    CuelloFinal();
};

// Cabeza: Movimiento vertical (estira el cuello)
class Cabeza: public NodoGrafoEscena {
public:
    Cabeza(Matriz4f * &rotacion);
};

class Tronco: public NodoGrafoEscena {
public:
    Tronco();
};

// Pingüino: Movimiento rotatorio horizontal (gira en circulos)
class C: public NodoGrafoEscena {
public:
    C(const float h_inicial,const float alfa_inicial, const float beta_inicial);
    void fijarH(const float nuevo_h);
    void fijarAlfa(const float nuevo_alfa);
    void fijarBeta(const float nuevo_beta);
    unsigned leerNumParametros() const;
protected:
    void actualizarEstadoParametro(const unsigned iParam,const float t_sec);
    Matriz4f * pm_rot_beta = nullptr;
    Matriz4f * pm_tras_y = nullptr;
    Matriz4f * pm_rot_alfa = nullptr;
};

#endif