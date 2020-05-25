#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include <list>

#include <set>
#include <vector>
#include <climits>
#include <cmath>

struct estado {
  int fila;
  int columna;
  int orientacion;
    // Calcula la distancia entre dos casillas
    float d(const estado &x,const estado &y) const;
    // Compara dos estados (fila y columna)
    bool operator==(const estado &a) {
        return a.fila==fila && a.columna==columna;
    }
    bool operator!=(const estado &a) {
        return a.fila!=fila || a.columna!=columna;
    }
};

// Devuelve la casilla que tiene el agente delante
estado delante(const estado &e);

// Función comparadora para el set de recargas
struct compara_recargas {
    bool operator()(const estado& a, const estado& b) {
        return a.fila<b.fila;
    }
};

class ComportamientoJugador : public Comportamiento {
  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size) {
      // Inicializar Variables de Estado
      fil = col = 99;
      brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
      destino.fila = -1;
      destino.columna = -1;
      destino.orientacion = -1;
      hayplan=false;

      // Variables costo uniforme
      zapatillas = false;
      bikini = false;

      // Variables nivel 2
      destino_anterior.fila = -1;
      destino_anterior.columna = -1;
      n_acciones = 0;
      coste_anterior = INT_MAX;
      coste_siguiente = 0;
      recargando = false;
    }
    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR) {
      // Inicializar Variables de Estado
      fil = col = 99;
      brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
      destino.fila = -1;
      destino.columna = -1;
      destino.orientacion = -1;
      hayplan=false;

      // Variables costo uniforme
      zapatillas = false;
      bikini = false;

      // Variables nivel 2
      destino_anterior.fila = -1;
      destino_anterior.columna = -1;
      n_acciones = 0;
      coste_anterior = INT_MAX;
      coste_siguiente = 0;
      recargando = false;
    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    void VisualizaPlan(const estado &st, const list<Action> &plan);
    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}

  private:
    // Declarar Variables de Estado
    int fil, col, brujula;
    estado actual, destino;
    list<Action> plan;
    bool hayplan;

    // Variables costo uniforme
    bool zapatillas;
    bool bikini;

    // Variables para el nivel 2
    estado destino_anterior;
    int n_acciones;
    int coste_anterior;
    int coste_siguiente;
    list<Action> plan_actual;
    set<estado,compara_recargas> recargas;
    bool recargando;

    // Métodos privados de la clase
    bool pathFinding(int level, const estado &origen, const estado &destino, list<Action> &plan,Sensores sensores);
    bool pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_Costo_Uniforme(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_A_estrella(const estado &origen, const estado &destino, list<Action> &plan,Sensores sensores);

    void PintaPlan(list<Action> plan);
    bool HayObstaculoDelante(estado &st);

    // Rellena las casillas visibles por el agente en el mapaResultado
    void rellenaMapa(Sensores sensores);
    // Busca las recargas del mapa explorado y devuelve la más cercana
    estado get_recargas();
    // Determina si el jugador tiene precipicios a su  alrededor
    bool precipicios_alrededor(Sensores sensores);

};

#endif
