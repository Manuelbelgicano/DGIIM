// Nombre: Manuel, Apellidos: Gachs Ballegeer, DNI/pasaporte: 15473645G (DDGG IG curso 20-21)
/*
******************************************************************
 Archivo para la implementación de las clases de la práctica 3
 Manuel Gachs Ballegeer
******************************************************************
*/
#include "modelo-jer.h"
#include "practica3.h"
#include "matrices-tr.h"

// ******************************************************************
// Clase Pie
Pie::Pie() {
    ponerNombre("Pie");
    NodoGrafoEscena * falange = new NodoGrafoEscena();
    falange->agregar(MAT_Escalado(0.7,0.5,1));
    falange->agregar(new Dedo());

    agregar(new Palma(10));
    agregar(falange);
    agregar(MAT_Rotacion(30.0,{0,1,0}));
    agregar(falange);
    agregar(MAT_Rotacion(30.0,{0,1,0}));
    agregar(falange);
}

// ******************************************************************
// Clase Pico
Pico::Pico() {
    ponerNombre("Pico");
    agregar(MAT_Escalado(1,0.4,1));
    agregar(new MedioPico());
    agregar(MAT_Escalado(1,-1,1));
    agregar(new MedioPico());
}

// ******************************************************************
// Clase Cara
Cara::Cara() {
    ponerNombre("Cara");
    NodoGrafoEscena * boca = new NodoGrafoEscena();
    boca->agregar(MAT_Traslacion(0,0.7,0.8));
    boca->agregar(new Pico());

    NodoGrafoEscena * cabeza_frontal = new NodoGrafoEscena();
    cabeza_frontal->agregar(MAT_Escalado(3.5,1.4,1));
    cabeza_frontal->agregar(new CabezaFrontal());

    NodoGrafoEscena * ojo_izq = new NodoGrafoEscena();
    ojo_izq->agregar(MAT_Escalado(0.2,0.2,0.2));
    ojo_izq->agregar(new Ojo(15));
    
    agregar(cabeza_frontal);
    agregar(boca);
    agregar(MAT_Traslacion(0.425,0.8,0.5));
    agregar(ojo_izq);
    agregar(MAT_Traslacion(-0.85,0,0));
    agregar(ojo_izq);
}

// ******************************************************************
// Clase Craneo
Craneo::Craneo(Matriz4f * &rotacion) {
    ponerNombre("Craneo");
    unsigned i = agregar(MAT_Rotacion(0,{0,1,0}));
    agregar(new Cara());
    agregar(MAT_Traslacion(0,-0.2475,-0.9));
    agregar(MAT_Escalado(3.5,1.65,3));
    agregar(new CabezaPosterior());

    rotacion = leerPtrMatriz(i);
}

// ******************************************************************
// Clase CuelloFinal
CuelloFinal::CuelloFinal() {
    ponerNombre("Cuello");
    NodoGrafoEscena * extension = new NodoGrafoEscena();
    extension->agregar(MAT_Traslacion(0,1,0.5));
    extension->agregar(MAT_Escalado(0.5,1,0.5));
    extension->agregar(new CuelloExtension());

    agregar(extension);
    agregar(MAT_Traslacion(0,2,0));
    agregar(MAT_Escalado(3.5,1.4,5));
    agregar(new Cuello());
}

// ******************************************************************
// Clase Cabeza
Cabeza::Cabeza(Matriz4f * &rotacion) {
    ponerNombre("Cabeza");
    agregar(new Craneo(rotacion));
    agregar(MAT_Traslacion(0,-3.32,-0.875));
    agregar(MAT_Escalado(1,1,0.6));
    agregar(new CuelloFinal());
}

// ******************************************************************
// Clase Tronco
Tronco::Tronco() {
    NodoGrafoEscena * brazo = new NodoGrafoEscena();
    brazo->agregar(MAT_Rotacion(5.0,{0,0,1}));
    brazo->agregar(MAT_Traslacion(0.4,0.4,0));
    brazo->agregar(MAT_Rotacion(90.0,{0,1,0}));
    brazo->agregar(new Ala());

    NodoGrafoEscena * alas = new NodoGrafoEscena();
    alas->agregar(brazo);
    alas->agregar(MAT_Rotacion(180.0,{0,1,0}));
    alas->agregar(brazo);

    NodoGrafoEscena * tronco_frente = new NodoGrafoEscena();
    tronco_frente->agregar(MAT_Escalado(1.65,1.2,1));
    tronco_frente->agregar(MAT_Traslacion(0,0.18,0.3));
    tronco_frente->agregar(new Barriga(10));

    agregar(alas);
    agregar(tronco_frente);    
    agregar(MAT_Escalado(2,1.5,2));
    agregar(MAT_Traslacion(0,0,-0.45));
    agregar(new Torso());
}

// ******************************************************************
// Clase C (Pingüino)
C::C(const float h_inicial,const float alfa_inicial, const float beta_inicial) {
    NodoGrafoEscena * pie = new NodoGrafoEscena();
    pie->agregar(MAT_Rotacion(-30.0,{0,1,0}));
    pie->agregar(new Pie());

    NodoGrafoEscena * pies = new NodoGrafoEscena();
    pies->agregar(MAT_Traslacion(1.5,0,1));
    pies->agregar(pie);
    pies->agregar(MAT_Traslacion(-3,0,0));
    pies->agregar(pie);

    NodoGrafoEscena * cuerpo = new NodoGrafoEscena();
    cuerpo->agregar(MAT_Escalado(4,4,4));
    cuerpo->agregar(new Tronco());

    NodoGrafoEscena * tren_superior = new NodoGrafoEscena();
    tren_superior->agregar(MAT_Traslacion(0,6,0.5));
    tren_superior->agregar(MAT_Escalado(1.2,1.2,1.2));
    unsigned j = tren_superior->agregar(MAT_Traslacion(0,h_inicial,0));
    tren_superior->agregar(new Cabeza(pm_rot_alfa));

    unsigned i = agregar(MAT_Rotacion(beta_inicial,{0,1,0}));
    agregar(MAT_Traslacion(-4,0,0));
    agregar(pies);
    agregar(tren_superior);
    agregar(cuerpo);

    pm_tras_y = tren_superior->leerPtrMatriz(j);
    pm_rot_beta = leerPtrMatriz(i);
}

void C::fijarH(const float nuevo_h) {
    *pm_tras_y = MAT_Traslacion(0,0.4*nuevo_h,0.5*nuevo_h);
}

void C::fijarAlfa(const float nuevo_alfa) {
    *pm_rot_alfa = MAT_Rotacion(nuevo_alfa,{0,1,0});
}

void C::fijarBeta(const float nuevo_beta) {
    *pm_rot_beta = MAT_Rotacion(nuevo_beta,{0,1,0});
}

unsigned C::leerNumParametros() const {
    return 3;
}

void C::actualizarEstadoParametro(const unsigned iParam,const float t_sec) {
    unsigned n = leerNumParametros();
    assert(iParam<n);

    switch(iParam) {
        case 0:
            fijarBeta(20*t_sec);
            break;
        case 1:
            fijarH(fabs(sin(2*t_sec)));
            break;
        case 2:
            fijarAlfa(30*sin(2*t_sec));
            break;
    }
}