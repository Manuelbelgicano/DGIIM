// Nombre: Manuel, Apellidos: Gachs Ballegeer, DNI/pasaporte: 15473645G (DDGG IG curso 20-21)
/*
******************************************************************
 Archivo para la implementación de las clases auxiliares de la práctica 3
 Manuel Gachs Ballegeer
******************************************************************
*/
#include "practica3.h"

using namespace std;

// Colores
Tupla3f naranja(0.968627,0.552941,0.074510);
Tupla3f naranja_palma(0.976471,0.709804,0.360784);
Tupla3f negro(0,0,0);
Tupla3f blanco(1,1,1);
Tupla3f gris(0.478431,0.478431,0.478431);

Dedo::Dedo(): MallaInd("Dedo") {
    ponerColor(naranja);
    vertices = {
        {0,0,0},        // 0
        {-0.2,0,0.8},   // 1
        {0,0,1},        // 2
        {0.2,0,0.8},    // 3
        {0,0.4,0.8}     // 4
    };
    triangulos = {
        // Base
        {0,1,2},
        {0,2,3},
        // Caras laterales
        {0,1,4},
        {1,2,4},
        {0,4,3},
        {4,2,3}
    };
}

Palma::Palma(unsigned nperfiles) {
    ponerNombre("Palma");
    ponerColor(naranja_palma);
    vector<Tupla3f> perfil = {{0,0,0},{0,0,1}};
    inicializar(perfil,nperfiles,PI/3);
}

Torso::Torso(): MallaInd("Torso") {
    ponerColor(negro);
    vertices = {
        {0,0,0},        // 0
        {-0.2,0,0.6},   // 1
        {-0.15,1,0.6},  // 2
        {-0.15,1,0.4},  // 3
        {0.15,1,0.4},   // 4
        {0.15,1,0.6},   // 5
        {0.2,0,0.6}     // 6
    };
    triangulos = {
        {0,1,6},    // Base
        // Caras laterales
        {1,3,2},
        {1,0,3},
        {0,3,4},
        {6,4,5},
        {6,0,4},
        {1,5,2},
        {1,6,5},
        // Tapa superior
        {2,4,3},
        {2,5,4}
    };
}

Ala::Ala(): MallaInd("Ala") {
    vertices = {
        {0,1,0},        // 0
        {-0.25,0.2,0},   // 1
        {-0.1,0.2,0.2}, // 2
        {-0.15,0,0},    // 3
        {0.15,0,0},     // 4
        {0.1,0.2,0.2},  // 5
        {0.25,0.2,0}    // 6
    };
    triangulos = {
        // Caras frontales
        {0,1,2},
        {0,2,5},
        {0,5,6},
        {3,2,1},
        {3,5,2},
        {3,4,5},
        {4,6,5},
        // Caras posteriores
        {0,1,6},
        {3,6,1},
        {3,4,6}
    };
    col_ver = {negro,negro,gris,gris,gris,gris,negro};
}

Barriga::Barriga(unsigned nperfiles) {
    ponerNombre("Barriga");
    ponerColor(blanco);
    vector<Tupla3f> perfil = {{-0.05,0,0},{-0.15,0.1,0},{-0.1,0.8,0},{-0.05,1,0}};
    inicializar(perfil,nperfiles);
}

CuelloExtension::CuelloExtension(): Cubo() {
    ponerColor(negro);
    ponerNombre("Extensión del cuello");
}

Cuello::Cuello(): MallaInd("Cuello") {
    ponerColor(negro);
    vertices = {
        {-0.15,0.8,0},  // 0
        {-0.15,0,0},    // 1
        {-0.15,0,0.2},  // 2
        {-0.15,1,0.4},  // 3
        {0.15,1,0.4},   // 4
        {0.15,0,0.2},   // 5
        {0.15,0,0},     // 6
        {0.15,0.8,0}    // 7
    };
    triangulos = {
        // Base
        {1,2,5},
        {1,5,6},
        // Caras laterales
        {1,3,0},
        {1,2,3},
        {2,4,3},
        {2,5,4},
        {6,4,5},
        {6,7,4},
        {6,7,0},
        {6,0,1},
        // Tapa
        {0,3,4},
        {0,4,7}
    };
}

CabezaPosterior::CabezaPosterior(): MallaInd("Cabeza Posterior") {
    ponerColor(negro);
    vertices = {
        {-0.15,0,0},        // 0
        {-0.15,0.15,0.3},   // 1
        {0.15,0.15,0.3},    // 2
        {0.15,0,0},         // 3
        {0.15,1,0.3},       // 4
        {-0.15,1,0.3}       // 5
    };
    triangulos = {
        // Base
        {0,1,2},
        {0,2,3},
        // Caras
        {0,1,5},
        {1,4,5},
        {1,2,4},
        {2,3,4},
        {0,3,5},
        {3,4,5}
    };
}

CabezaFrontal::CabezaFrontal(): MallaInd("Cabeza Frontal") {
    vertices = {
        {-0.15,0,0},        // 0
        {-0.15,0.15,1},     // 1
        {-0.15,0.8,1},      // 2
        {-0.15,1,0},        // 3
        {0.15,1,0},         // 4
        {0.15,0.8,1},       // 5
        {0.15,0.15,1},      // 6
        {0.15,0,0}          // 7
    };
    triangulos = {
        // Base
        {0,6,1},
        {0,7,6},
        // Caras laterales
        {1,5,2},
        {1,6,5},
        {6,4,5},
        {6,7,4},
        {0,7,4},
        {0,4,3},
        {0,2,3},
        {0,1,2},
        // Tapa
        {2,5,4},
        {2,4,3}
    };
    col_ver = {negro,gris,gris,negro,negro,gris,gris,negro};
}

Ojo::Ojo(unsigned nperfiles): Esfera(2,nperfiles) {
    ponerNombre("Ojo");
    ponerColor(blanco);
}

MedioPico::MedioPico(): Tetraedro(1,2) {
    ponerNombre("Medio Pico");
    ponerColor(naranja);
}