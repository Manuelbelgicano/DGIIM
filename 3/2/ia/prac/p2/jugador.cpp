#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <stack>

#include <queue>
#include <cmath>

/*  ------------------------------------------------
    ------      FUNCIONES DE LA PRÁCTICA      ------
    ------------------------------------------------*/

//--------------------------- COSTO UNIFORME --------------------------
// Estructura para el Coste Uniforme
struct nodo_coste {
    estado st;
    list<Action> secuencia;
    int coste;
    bool bikini = false;
    bool zapatillas = false;
};

// Comparador de dos nodo_coste para la cola con prioridad
struct compara_nodo_coste{
	bool operator()(const nodo_coste &a, const nodo_coste &b) const {
		return a.coste>b.coste;
	}
};

// Devuelve el coste de moverse por una casilla
int get_coste(unsigned char a,nodo_coste &c);

//------------------------------ NIVEL 2 ------------------------------
// Estructura para el A estrella
struct nodo_a {
    estado st;
    estado padre;
    int coste_g;
    int coste_h;
    int coste_f;
    bool bikini = false;
    bool zapatillas = false;
};

// Comparador de dos nodo_a para la cola con prioridad
struct compara_nodo_a{
	bool operator()(const nodo_a &a, const nodo_a &b) const {
		return a.coste_f>b.coste_f;
	}
};

// Determina si un nodo_a es el destino
bool es_destino(const nodo_a &a,const estado &s);

// Determina el coste de realizar un numero de giros dependiente de las orientaciones
int set_coste_giro(int coste_padre,int ori_p,int ori_h);

// Determina el coste 'G' de una casilla para A*
int set_coste_g(const nodo_a &padre,nodo_a &c,unsigned char a);

// Determina el coste 'H' de una casilla para A*
int set_coste_h(const nodo_a &c,const estado &destino);

// Determina el coste 'F' de una casilla para A*
int set_coste_f(const nodo_a &c);

// Determina si un nodo_a es valido (esta dentro del mapa)
bool es_valido(const nodo_a &a,int f,int c);

// Determina si el agente tiene un aldeano delante
bool aldeano_delante(const nodo_a &a,int x,int y,Sensores sensores);

// Determina la lista de acciones para ir de una casilla b a una a (adyacente)
list<Action> get_acciones(const estado &a,const estado &b);

// Calcula el porcentaje explorado del mapa (se presupone rectangular)
float explored_percent(vector<vector<unsigned char> > &mapa);

// Determina si un destino está justo delante
bool destino_delante(const estado &pos,const estado &destino);

// Este es el método principal que debe contener los 4 Comportamientos_Jugador
// que se piden en la práctica. Tiene como entrada la información de los
// sensores y devuelve la acción a realizar.
Action ComportamientoJugador::think(Sensores sensores) {
    int nivel = sensores.nivel;
    Action sigAccion;
    actual.fila = sensores.posF;
    actual.columna = sensores.posC;
    actual.orientacion = sensores.sentido;

    // Vemos si tiene zapatillas/bikini
    if (!bikini && mapaResultado[sensores.posF][sensores.posC]=='K')
        bikini = true;
    if (!zapatillas && mapaResultado[sensores.posF][sensores.posC]=='D')
        zapatillas = true;

    /* Nivel 2.
       Eventos que causan una replanificación
         - Nuevo destino
         - No existe plan hasta el destino
         - Ha colisionado con un muro o aldeano
         - Si el mapa está poco explorado, cada cierto número de acciones
         - Si queda poca batería, el nuevo destino será la recarga
         - Si tiene precipicios alrededor
    */
    if (nivel==4) {
        float tolerancia_exploracion_baja = 0.5;
        float tolerancia_exploracion_alta = 0.8;
        float tolerancia_bateria = 0.65;
        float bateria = sensores.bateria;
        float pc_bateria = bateria/3000;
        bool min_bateria = pc_bateria<0.2;
        estado destino_recarga = get_recargas();

        if (actual==destino_recarga && pc_bateria<tolerancia_bateria)
            recargando = true;
        else
            recargando = false;

        // Calculamos  el destino
        if (min_bateria || recargando) {
            if (destino_recarga.fila!=-1) {
                destino = destino_recarga;
            } else {
                destino.fila = sensores.destinoF;
                destino.columna = sensores.destinoC;
            }
        } else {
            destino.fila = sensores.destinoF;
            destino.columna = sensores.destinoC;
        }
        rellenaMapa(sensores); // Añadimos las casillas visibles al mapa
        float explorado = explored_percent(mapaResultado);
        //cout<<"Porcentaje de mapa explorado: "<<explorado<<endl;
        bool replan_explored = explorado<tolerancia_exploracion_baja;
        bool replan_explored_alta = explorado<tolerancia_exploracion_alta;

        // Si el destino esta justo delante
        if (destino_delante(actual,destino)) {
            plan_actual.clear();
            return actFORWARD;
        }

        // Eventos de replanificación
        if (destino_anterior!=destino) { // Nuevo destino
            coste_anterior = INT_MAX;
            destino_anterior = destino;
            hayplan = pathFinding(sensores.nivel,actual,destino,plan,sensores);
        } else if (!hayplan) { // No hay plan
            hayplan = pathFinding(sensores.nivel,actual,destino,plan,sensores);
        } else if (precipicios_alrededor(sensores) && replan_explored_alta) { // Precipicios alrededor
            coste_anterior = INT_MAX;
            hayplan = pathFinding(sensores.nivel,actual,destino,plan,sensores);
        } else if (sensores.colision) { // Choque con un aldeano/muro
            coste_anterior = INT_MAX;
            hayplan = pathFinding(sensores.nivel,actual,destino,plan,sensores);
        } else if (replan_explored && n_acciones%2==0) { // Mapa poco explorado
            hayplan = pathFinding(sensores.nivel,actual,destino,plan,sensores);
        } else if (replan_explored_alta && n_acciones%6==0) { // Mapa poco explorado 2
            hayplan = pathFinding(sensores.nivel,actual,destino,plan,sensores);
        } else {
            cout<<"No hace falta replanificar!\n";
        }

        // Lo añadimos si es mejor que el anterior
        if (coste_siguiente<coste_anterior) {
            cout<<"-------------\nNuevo plan!\n";
            plan_actual.clear();
            plan_actual.assign(plan.begin(),plan.end());
            coste_anterior = coste_siguiente;
        }
        cout<<"Tamaño del plan: "<<plan_actual.size()<<endl;
        PintaPlan(plan_actual);
		VisualizaPlan(actual, plan_actual);
    // Nivel 1
    } else {
        if (!hayplan) {
            destino.fila = sensores.destinoF;
            destino.columna = sensores.destinoC;
            hayplan = pathFinding(sensores.nivel,actual,destino,plan,sensores);
            plan_actual = plan;
        }
    }

    // Ejecutamos la acción
    if (hayplan && plan_actual.size()>0) {
        sigAccion = plan_actual.front();
        n_acciones++;
        plan_actual.erase(plan_actual.begin());
    } else {
        cout<<"No hay plan...\n";
        hayplan = false;
        sigAccion = actIDLE;
    }
    return sigAccion;
}

// Llama al algoritmo de busqueda que se usará en cada comportamiento del agente
// Level representa el comportamiento en el que fue iniciado el agente.
bool ComportamientoJugador::pathFinding (int level, const estado &origen, const estado &destino, list<Action> &plan,Sensores sensores){
	switch (level){
		case 1: cout << "Busqueda en profundad\n";
			      return pathFinding_Profundidad(origen,destino,plan);
						break;
		case 2: cout << "Busqueda en Anchura\n";
			      return pathFinding_Anchura(origen,destino,plan);
						break;
		case 3: cout << "Busqueda Costo Uniforme\n";
						return pathFinding_Costo_Uniforme(origen,destino,plan);
						break;
		case 4: cout << "Busqueda para el reto\n";
						return pathFinding_A_estrella(origen,destino,plan,sensores);
						break;
	}
	cout << "Comportamiento sin implementar\n";
	return false;
}

//---------------------- Implementación de la busqueda en profundidad ---------------------------

// Dado el código en carácter de una casilla del mapa dice si se puede
// pasar por ella sin riegos de morir o chocar.
bool EsObstaculo(unsigned char casilla){
	if (casilla=='P' or casilla=='M')
		return true;
	else
	  return false;
}

// Comprueba si la casilla que hay delante es un obstaculo. Si es un
// obstaculo devuelve true. Si no es un obstaculo, devuelve false y
// modifica st con la posición de la casilla del avance.
bool ComportamientoJugador::HayObstaculoDelante(estado &st){
	int fil=st.fila, col=st.columna;

  // calculo cual es la casilla de delante del agente
	switch (st.orientacion) {
		case 0: fil--; break;
		case 1: col++; break;
		case 2: fil++; break;
		case 3: col--; break;
	}

	// Compruebo que no me salgo fuera del rango del mapa
	if (fil<0 or fil>=mapaResultado.size()) return true;
	if (col<0 or col>=mapaResultado[0].size()) return true;

	// Miro si en esa casilla hay un obstaculo infranqueable
	if (!EsObstaculo(mapaResultado[fil][col])){
		// No hay obstaculo, actualizo el parámetro st poniendo la casilla de delante.
    st.fila = fil;
		st.columna = col;
		return false;
	}
	else{
	  return true;
	}
}

struct nodo{
	estado st;
	list<Action> secuencia;
};

struct ComparaEstados{
	bool operator()(const estado &a, const estado &n) const{
		if ((a.fila > n.fila) or (a.fila == n.fila and a.columna > n.columna) or
	      (a.fila == n.fila and a.columna == n.columna and a.orientacion > n.orientacion))
			return true;
		else
			return false;
	}
};

// Implementación de la búsqueda en profundidad.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
bool ComportamientoJugador::pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	stack<nodo> pila;											// Lista de Abiertos

  nodo current;
	current.st = origen;
	current.secuencia.empty();

	pila.push(current);

  while (!pila.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		pila.pop();
		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			pila.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			pila.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				pila.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la pila
		if (!pila.empty()){
			current = pila.top();
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}

// Sacar por la términal la secuencia del plan obtenido
void ComportamientoJugador::PintaPlan(list<Action> plan) {
	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			cout << "A ";
		}
		else if (*it == actTURN_R){
			cout << "D ";
		}
		else if (*it == actTURN_L){
			cout << "I ";
		}
		else {
			cout << "- ";
		}
		it++;
	}
	cout << endl;
}

void AnularMatriz(vector<vector<unsigned char> > &m){
	for (int i=0; i<m[0].size(); i++){
		for (int j=0; j<m.size(); j++){
			m[i][j]=0;
		}
	}
}

// Pinta sobre el mapa del juego el plan obtenido
void ComportamientoJugador::VisualizaPlan(const estado &st, const list<Action> &plan){
  AnularMatriz(mapaConPlan);
	estado cst = st;

	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			switch (cst.orientacion) {
				case 0: cst.fila--; break;
				case 1: cst.columna++; break;
				case 2: cst.fila++; break;
				case 3: cst.columna--; break;
			}
			mapaConPlan[cst.fila][cst.columna]=1;
		}
		else if (*it == actTURN_R){
			cst.orientacion = (cst.orientacion+1)%4;
		}
		else if (*it == actTURN_L){
			cst.orientacion = (cst.orientacion+3)%4;
		}
		it++;
	}
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}

/*  ------------------------------------------------
    ------     IMPLEMENTACION DE FUNCIONES    ------
    ------------------------------------------------*/

bool ComportamientoJugador::pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan) {
    //Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	queue<nodo> cola; // Lista de Abiertos

    nodo current;
	current.st = origen;
	current.secuencia.empty();

	cola.push(current);

    while (!cola.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		cola.pop();
		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			cola.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			cola.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				cola.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la cola
		if (!cola.empty()){
			current = cola.front();
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna) {
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
        // ver el plan en el mapa
        VisualizaPlan(origen, plan);
		return true;
	} else
		cout << "No encontrado plan\n";

	return false;
}

int get_coste(unsigned char a,nodo_coste &c) {
    int coste = 0;
    switch(a) {
        case 'A': // Agua
            coste = c.bikini?10:100;
            break;
        case 'B': // Bosque
            coste = c.zapatillas?5:50;
            break;
        case 'T': // Suelo arenoso
            coste = 2;
            break;
        default:
            coste = 1;
            break;
    }
    return coste;
}

bool ComportamientoJugador::pathFinding_Costo_Uniforme(const estado &origen, const estado &destino, list<Action> &plan) {
    //Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	priority_queue<nodo_coste,vector<nodo_coste>,compara_nodo_coste> cola; // Lista de Abiertos

    nodo_coste current;
	current.st = origen;
	current.coste = 0;
	current.secuencia.empty();
	current.bikini = bikini;
	current.zapatillas = zapatillas;

	cola.push(current);

    while (!cola.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		cola.pop();
		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo_coste hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
            hijoTurnR.coste += get_coste(mapaResultado[hijoTurnR.st.fila][hijoTurnR.st.columna],hijoTurnR);
			hijoTurnR.secuencia.push_back(actTURN_R);
			cola.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda
		nodo_coste hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
            hijoTurnL.coste += get_coste(mapaResultado[hijoTurnL.st.fila][hijoTurnL.st.columna],hijoTurnL);
			hijoTurnL.secuencia.push_back(actTURN_L);
			cola.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo_coste hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
                hijoForward.coste += get_coste(mapaResultado[hijoForward.st.fila][hijoForward.st.columna],hijoForward);
				hijoForward.secuencia.push_back(actFORWARD);
				cola.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la cola
		if (!cola.empty()){
			current = cola.top();
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna) {
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		cout<<"Coste del plan: "<<current.coste<<endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	} else
		cout << "No encontrado plan\n";

	return false;
}

float estado::d(const estado &x,const estado &y) const {
    int dist = (y.columna - x.columna) + (y.fila - x.fila);
    return abs(dist);
}

estado ComportamientoJugador::get_recargas() {
    // Escaneamos el mapa por las recargas
    for (size_t i=0;i<mapaResultado.size();i++)
        for (size_t j=0;j<mapaResultado[i].size();j++)
            if (mapaResultado[i][j]=='X') {
                estado rec;
                rec.fila = i;
                rec.columna = j;
                recargas.insert(rec);
            }
    // Escogemos el más cercano
    float dist_min = INT_MAX;
    estado cercana;
    cercana.fila = -1; // Si no encuentra nada, le damos un valor por defecto
    for (auto rec=recargas.begin();rec!=recargas.end();rec++)
        if ((*rec).d((*rec),actual)<dist_min) {
            dist_min = (*rec).d((*rec),actual);
            cercana = (*rec);
        }
    return cercana;
}

bool es_destino(const nodo_a &a,const estado &s) {
    bool destino = false;
    if (a.st.fila==s.fila && a.st.columna==s.columna)
        destino = true;

    return destino;
}

int set_coste_giro(int coste_padre,int ori_p,int ori_h) {
    int n_giros = abs(ori_h-ori_p);
    int aumento_coste = 0;
    if (n_giros<2)
        aumento_coste = coste_padre*n_giros;
    else
        aumento_coste = coste_padre;
    return aumento_coste;
}

int set_coste_g(const nodo_a &padre,nodo_a &c,unsigned char a) {
    int coste_g = 0;
    switch(a) {
        case 'A': // Agua
            coste_g = c.bikini?10:100;
            break;
        case 'B': // Bosque
            coste_g = c.zapatillas?5:50;
            break;
        case '?': // Si desconoce el terreno
            coste_g = 2;
            break;
        case 'T': // Suelo arenoso
            coste_g = 2;
            break;
        case 'K': // Encuentra el bikini
            coste_g = 1;
            c.bikini = true;
            break;
        case 'D': // Encuentra las zapatillas
            coste_g = 1;
            c.zapatillas = true;
            break;
        default:
            coste_g = 1;
            break;
    }
    coste_g += set_coste_giro(padre.coste_g,padre.st.orientacion,c.st.orientacion);
    return coste_g;
}

int set_coste_h(const nodo_a &c,const estado &destino) {
    int coste_h = destino.d(destino,c.st);
    return coste_h;
}

int set_coste_f(const nodo_a &c) {
    int coste_f = c.coste_g + c.coste_h;
    return coste_f;
}

bool es_valido(const nodo_a &a,int f,int c) {
    return a.st.fila<f && a.st.columna<c && a.st.fila>=0 && a.st.columna>=0;
}

bool aldeano_delante(const nodo_a &a,int x,int y,Sensores sensores) {
    return (a.st.fila==x && a.st.columna==y && sensores.terreno[2]=='a');
}

list<Action> get_acciones(const estado &a,const estado &b) {
    list<Action> plan;
    // Añadimos los giros
    int n_giros = a.orientacion - b.orientacion;
    if (abs(n_giros)==2) { // Orientación opuesta
        plan.push_back(actTURN_R);
        plan.push_back(actTURN_R);
    } else if (n_giros==-1 || n_giros==3) { // A la izquierda
        plan.push_back(actTURN_L);
    } else if  (n_giros==1 || n_giros==-3) {// A la derecha
        plan.push_back(actTURN_R);
    }
    // Nos movemos hacia delante
    plan.push_back(actFORWARD);

    return plan;
}

bool ComportamientoJugador::pathFinding_A_estrella(const estado &origen, const estado &destino, list<Action> &plan,Sensores sensores) {
    plan.clear();
    priority_queue<nodo_a,vector<nodo_a>,compara_nodo_a> abiertos; // Cola de abiertos
    int f = mapaResultado.size();
    int c = mapaResultado[0].size();
    int fil[4] = {-1,0,1,0};
    int col[4] = {0,1,0,-1};
    int x_aldeano = origen.fila + fil[origen.orientacion];
    int y_aldeano = origen.columna + col[origen.orientacion];

    nodo_a mapa[f][c];
    bool visitados[f][c] = {false};

    for (size_t i=0;i<f;i++)
        for (size_t j=0;j<c;j++) {
            mapa[i][j].st.fila = i;
            mapa[i][j].st.columna = j;
            mapa[i][j].coste_f = INT_MAX;
        }
    bool encontrado = false;

    nodo_a actual;
    actual.coste_g = 0;
    actual.st.orientacion = 0;
    mapa[origen.fila][origen.columna].st.orientacion = origen.orientacion;
    mapa[origen.fila][origen.columna].coste_g = set_coste_g(actual,mapa[origen.fila][origen.columna],mapaResultado[origen.fila][origen.columna]);
    mapa[origen.fila][origen.columna].coste_f = 0;
    mapa[origen.fila][origen.columna].bikini = bikini;
    mapa[origen.fila][origen.columna].zapatillas = zapatillas;
    abiertos.push(mapa[origen.fila][origen.columna]);

    while(!abiertos.empty() && !encontrado) {
        actual = abiertos.top();
        abiertos.pop();
        int x = actual.st.fila;
        int y = actual.st.columna;
        visitados[x][y] = true;
        // Creamos los hijos
        for (size_t i=0;i<4;i++) {
            nodo_a hijo;
            int n_x = x+fil[i];
            int n_y = y+col[i];
            hijo.st.fila = n_x;
            hijo.st.columna = n_y;
            hijo.st.orientacion = i;
            hijo.padre = actual.st;
            if (es_valido(hijo,f,c) && !EsObstaculo(mapaResultado[n_x][n_y]) && !aldeano_delante(hijo,x_aldeano,y_aldeano,sensores)) { // Es un hijo valido
                if (!visitados[x+fil[i]][y+col[i]]) { // No ha sido visitado
                    hijo.coste_g = set_coste_g(actual,hijo,mapaResultado[n_x][n_y]);
                    hijo.coste_h = set_coste_h(hijo,destino);
                    hijo.coste_f = set_coste_f(hijo) + actual.coste_f;
                    if (es_destino(hijo,destino)) { // Hemos llegado al destino
                        encontrado = true;
                        mapa[n_x][n_y] = hijo;
                    } else if (mapa[n_x][n_y].coste_f>hijo.coste_f) { // Es mejor camino
                        mapa[n_x][n_y] = hijo;
                        abiertos.push(mapa[n_x][n_y]);
                    }
                }
            }
        }
    }

    cout << "Terminada la busqueda\n";

    // Reconstruimos el camino
    if (!encontrado) {
        cout << "No encontrado plan\n";
        return false;
    }

    cout << "Cargando el plan\n";
    stack<nodo_a> camino;
    nodo_a nodo_camino = mapa[destino.fila][destino.columna];
    while(nodo_camino.st!=origen) {
        camino.push(nodo_camino);
        nodo_camino = mapa[nodo_camino.padre.fila][nodo_camino.padre.columna];
    }


    nodo_a anterior = mapa[origen.fila][origen.columna];
    while(!camino.empty()) {
        nodo_a siguiente = camino.top();
        camino.pop();
        list<Action> mov = get_acciones(siguiente.st,anterior.st);
        plan.insert(plan.end(),mov.begin(),mov.end());
        anterior = siguiente;
        coste_siguiente = siguiente.coste_f;
    }
    cout << "Longitud del plan: " << plan.size() << endl;
    cout<<"Coste del plan: "<<coste_siguiente<<endl;

    return true;
}

bool ComportamientoJugador::precipicios_alrededor(Sensores sensores) {
    bool precipicios = false;
    for (size_t i=1;i<9;i++)
        if (sensores.terreno[i]=='P')
            precipicios = true;

    return precipicios;
}

float explored_percent(vector<vector<unsigned char> > &mapa) {
    float total = mapa.size()*mapa[0].size();
    float explorado = 0;

    for (size_t i=0;i<mapa.size();i++)
        for (size_t j=0;j<mapa[i].size();j++)
            if (mapa[i][j]!='?')
                explorado++;
    float porciento = explorado/total;
    return porciento;
}

void ComportamientoJugador::rellenaMapa(Sensores sensores) {
    // Añadimos la casilla actual
    int f = sensores.posF;
    int c = sensores.posC;
    int top_f = mapaResultado.size();
    int top_c = mapaResultado[0].size();
    int ori = sensores.sentido;
    mapaResultado[f][c] = sensores.terreno[0];

    int eo_fil = ori - 2; // -1 este, 1 oeste
    int eo_col = 2 - ori; // 1 este, -1 oeste
    int ns_fil = ori - 1; // -1 norte, 1 sur
    int ns_col = ori - 1; // -1 norte, 1 sur

    int mult[4] = {1,1,-1,-1};
    int n = 0;
    int hilera = 1;

    // Añadimos  el resto de casillas visibles
    for (size_t i=1;i<16;i++) {
        // Primera hilera
        if (i<4) {
            n = i - 1;
            hilera = 1;
        } else if (i<9) { // Segunda hilera
            n = i - 4;
            hilera = 2;
        } else { // Tercera hilera
            n = i - 9;
            hilera = 3;
        }
        // Este - Oeste
        if (ori==1 || ori==3) {
            if (c+(eo_col*hilera)>=0 && c+(eo_col*hilera)<top_c) {
                if (f-hilera>=0 && f+hilera<top_f) {
                    mapaResultado[f+(eo_fil*hilera)+(mult[ori]*n)][c+(eo_col*hilera)] = sensores.terreno[i];
                }
            }
        } else { // Norte - Sur
            if (f+(ns_fil*hilera)>=0 && f+(ns_fil*hilera)<top_f) {
                if (c-hilera>=0 && c+hilera<top_c) {
                    mapaResultado[f+(ns_col*hilera)][c+(ns_col*hilera)+(mult[ori]*n)] = sensores.terreno[i];
                }
            }
        }
    }
}

bool destino_delante(const estado &pos,const estado &destino) {
    int x = pos.fila;
    int y = pos.columna;
    switch (pos.orientacion) {
		case 0: x--; break;
		case 1: y++; break;
		case 2: x++; break;
		case 3: y--; break;
    }

    bool delante = false;
    if (x==destino.fila && y==destino.columna)
        delante = true;
    return delante;
}
