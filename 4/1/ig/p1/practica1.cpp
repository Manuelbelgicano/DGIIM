// Nombre: Manuel, Apellidos: Gachs Ballegeer, DNI/pasaporte: 15473645G (DDGG IG curso 20-21)
/*
******************************************************************
 Archivo para la implementación de las clases de la práctica 1
 Manuel Gachs Ballegeer
// - Tetraedro
// - CuboColores
/*****************************************************************
*/
#include "practica1.h"
#include <cmath>



Tetraedro::Tetraedro(int sentido_altura,unsigned int tam) : MallaInd("Tetraedro") {
    // Color
    Tupla3f color(0.0,1.0,0.0);
    // Vectores para construir el tetraedro
    vertices = {
        {-0.5,0,0},     // 0
        {0.5,0,0},      // 1
        {0,1,0},        // 2
        {0,0,1}         // 3
    };
    triangulos = {{0,1,2},{0,1,3},{0,2,3},{1,2,3}};
    ponerColor(color);
}

CuboColores::CuboColores() :  MallaInd("CuboColores") {
    vertices = {
        { -1.0, -1.0, -1.0 }, // 0
        { -1.0, -1.0, +1.0 }, // 1
        { -1.0, +1.0, -1.0 }, // 2
        { -1.0, +1.0, +1.0 }, // 3
        { +1.0, -1.0, -1.0 }, // 4
        { +1.0, -1.0, +1.0 }, // 5
        { +1.0, +1.0, -1.0 }, // 6
        { +1.0, +1.0, +1.0 }, // 7
      };

    col_ver = {
        {0.0,0.0,0.0},
        {0.0,0.0,1.0},
        {0.0,1.0,0.0},
        {0.0,1.0,1.0},
        {1.0,0.0,0.0},
        {1.0,0.0,1.0},
        {1.0,1.0,0.0},
        {1.0,1.0,1.0},
    };

    triangulos = {  
        {0,1,3}, {0,3,2}, // X-
        {4,7,5}, {4,6,7}, // X+ (+4)

        {0,5,1}, {0,4,5}, // Y-
        {2,3,7}, {2,7,6}, // Y+ (+2)

        {0,6,4}, {0,2,6}, // Z-
        {1,5,7}, {1,7,3}  // Z+ (+1)
    };
    

}