// Nombre: Manuel, Apellidos: Gachs Ballegeer, DNI/pasaporte: 15473645G (DDGG IG curso 20-21)
/*
******************************************************************
 Archivo para la implementación de las clases de la práctica 2
 Manuel Gachs Ballegeer
    - Cilindro 
    - Cono
    - Torso
******************************************************************
*/
#include "practica2.h"
#include <cmath>

using namespace std;

Cilindro::Cilindro(const int num_verts_per,const unsigned nperfiles) {
    assert(num_verts_per==4);
    ponerNombre("Cilindro");
    vector<Tupla3f> perfil = {{0,0,0},{1,0,0},{1,1,0},{0,1,0}};
    inicializar(perfil,nperfiles);
}

Cono::Cono(const int num_verts_per,const unsigned nperfiles) {
    assert(num_verts_per==3);
    ponerNombre("Cono");
    vector<Tupla3f> perfil = {{0,0,0},{1,0,0},{0,1,0}};
    inicializar(perfil,nperfiles);
}

Esfera::Esfera(const int num_verts_per,const unsigned nperfiles) {
    assert(num_verts_per==2);
    ponerNombre("Esfera");
    vector<Tupla3f> recta = {{0,-1,0},{0,0,0}};
    vector<Tupla3f> perfil = semicircunferencia(recta,nperfiles);
    inicializar(perfil,nperfiles);
}

vector<Tupla3f> Esfera::semicircunferencia(std::vector<Tupla3f> & recta,const unsigned nperfiles) {
    vector<Tupla3f> perfil;

    for (unsigned i=0;i<nperfiles;i++) {
        /* Rotación angulo a alrededor de Z desde el origen
        x' = cos(a)*x - sen(a)*y
        y' = sen(a)*x + cos(a)*y
        z' = z
        */
        float a = (PI*i)/(nperfiles-1);
        float x = recta[0][0];
        float y = recta[0][1];
        float z = recta[0][2];
        Tupla3f n_vertice(-sin(a)*y+cos(a)*x,cos(a)*y+sin(a)*x,z);
        perfil.push_back(n_vertice);
    }

    return perfil;
}