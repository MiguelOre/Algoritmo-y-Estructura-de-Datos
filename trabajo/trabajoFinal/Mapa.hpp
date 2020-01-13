#pragma once
#include "NodoMapa.hpp"
#include "Juego.hpp";
#include "Jugador.hpp"
#include "CtrlEnemigos.hpp"
#include <fstream>
#include <sstream>
#include <functional>
class Mapa {
	DatosJuego* datos;
	int nNodos;
	int nNodosMatriz;
	int anchoNodo;
	int altoNodo;
public:
	NodoMapa* inicio;
	NodoMapa* nodoActivo;
	Mapa(DatosJuego * datos,Jugador&jug) {
		this->datos = datos;
		this->inicio = nullptr;
		this->nNodos = 0;
		anchoNodo = (datos->ancho / datos->M_SIZE)*datos->M_SIZE;
		altoNodo = (datos->alto / datos->M_SIZE)*datos->M_SIZE;
		this->crearNodoInicial(0,0);
		this->generarAreaNodos(this->inicio);
		this->crearNnodos(8);
		this->inicAreaActiva();
		this->inicio = this->inicio->prev->left;
		jug.reiniciarEstado(this->nodoActivo->x+(datos->ancho/2)-65,this->nodoActivo->y + (datos->alto / 2) - 65);
	}
	void crearNodoInicial(int x,int y) {
		this->inicio = new NodoMapa(x,y);
		this->inicio->id = nNodos;
	//	cout << this->nNodos;//borrar;	
		this->nNodos++;
		//cout << x<<","<<y<<endl;
	}
	void crearNodoAdelante(NodoMapa* obj, int x, int y) {
		NodoMapa* tmp = new NodoMapa(x,y);
		tmp->prev = obj;
		obj->next = tmp;
		tmp->id = nNodos;
		//cout << this->nNodos;//borrar;
		tmp = NULL;
		delete tmp;
		this->nNodos++;
		//cout << x << "," << y << endl;
	}
	void crearNodoAtras(NodoMapa* obj,int x,int y) {
		NodoMapa* tmp = new NodoMapa(x, y);
		tmp->next = obj;
		obj->prev = tmp;
		tmp->id = nNodos;
		//cout << this->nNodos;//borrar;
		tmp = NULL;
		delete tmp;
		this->nNodos++;
		//cout << x << "," << y << endl;
	}
	void crearNodoIzquierda(NodoMapa* obj,int x,int y) {
		NodoMapa* tmp = new NodoMapa(x, y);
		tmp->right = obj;
		obj->left = tmp;
		tmp->id = nNodos;
		//cout << this->nNodos;//borrar;
		tmp = NULL;
		delete tmp;
		this->nNodos++;
		//cout << x << "," << y << endl;
	}
	void crearNodoDerecha(NodoMapa* obj,int x,int y) {
		NodoMapa* tmp = new NodoMapa(x, y);
		tmp->left = obj;
		obj->right = tmp;

		tmp->id = nNodos;
		//cout << this->nNodos;//borrar;
		tmp = NULL;
		delete tmp;
		this->nNodos++;
		//cout << x << "," << y << endl;
	}
	void pintarMapa(Jugador &jug) {

		this->nodoActivo->dato->pintarTerreno();
		this->nodoActivo->next->dato->pintarTerreno();
		this->nodoActivo->prev->dato->pintarTerreno();
		this->nodoActivo->right->dato->pintarTerreno();
		this->nodoActivo->left->dato->pintarTerreno();
		this->nodoActivo->prev->left->dato->pintarTerreno();
		this->nodoActivo->prev->right->dato->pintarTerreno();
		this->nodoActivo->next->left->dato->pintarTerreno();
		this->nodoActivo->next->right->dato->pintarTerreno();

		jug.pintar(this->datos);

		this->nodoActivo->dato->pintarObjetos();
		this->nodoActivo->next->dato->pintarObjetos();
		this->nodoActivo->prev->dato->pintarObjetos();
		this->nodoActivo->right->dato->pintarObjetos();
		this->nodoActivo->left->dato->pintarObjetos();
		this->nodoActivo->prev->left->dato->pintarObjetos();
		this->nodoActivo->prev->right->dato->pintarObjetos();
		this->nodoActivo->next->left->dato->pintarObjetos();
		this->nodoActivo->next->right->dato->pintarObjetos();
	}
	string ActualizarNodosActivos(Jugador &jug,CtrlEnemigos* enemigos) {

		//fin colisiones
		if (jug.px < this->nodoActivo->x) {
			this->nodoActivo = this->nodoActivo->left;
		}
		else if (jug.px > this->nodoActivo->x + anchoNodo) {
			this->nodoActivo = this->nodoActivo->right;
		}
		else if (jug.py<this->nodoActivo->y) {
			this->nodoActivo = this->nodoActivo->prev;
		}
		else if (jug.py > this->nodoActivo->y + altoNodo) {
			this->nodoActivo = this->nodoActivo->next;
		}
		this->generarAreaNodos();
		this->inicAreaActiva();
		this->nodoActivo->dato->actualizarColisiones(jug,enemigos);
		this->nodoActivo->left->dato->actualizarColisiones(jug, enemigos);
		this->nodoActivo->right->dato->actualizarColisiones(jug, enemigos);
		this->nodoActivo->prev->dato->actualizarColisiones(jug, enemigos);
		this->nodoActivo->next->dato->actualizarColisiones(jug, enemigos);
		string tipoMaterial = this->nodoActivo->dato->coordEnMapa((jug.px), (jug.py));
		this->nodoActivo->dato->comprobarAreaAtaque(jug);
		return tipoMaterial;
	}
	void generarAreaNodos(NodoMapa* nodo = nullptr) {
		if (nodo == nullptr) {
			nodo = nodoActivo;
		}
		if (nodo->prev == nullptr) {
			int xx = nodo->x;
			int yy = nodo->y - this->altoNodo;
			this->crearNodoAtras(nodo, xx, yy);
		}
		if (nodo->next == nullptr) {
			int xx = nodo->x;
			int yy = nodo->y + this->altoNodo;
			this->crearNodoAdelante(nodo, xx, yy);
		}
		if (nodo->left == nullptr) {
			int xx = nodo->x - this->anchoNodo;
			int yy = nodo->y;
			this->crearNodoIzquierda(nodo, xx, yy);
		}
		if (nodo->right == nullptr) {
			int xx = nodo->x + this->anchoNodo;
			int yy = nodo->y;
			this->crearNodoDerecha(nodo, xx, yy);
		}

		if (nodo->prev->left == nullptr) {
			int xx = nodo->prev->x - this->anchoNodo;
			int yy = nodo->prev->y;
			this->crearNodoIzquierda(nodo->prev, xx, yy);

			nodo->prev->left->next = nodo->left;
			nodo->left->prev = nodo->prev->left;
		}
		if (nodo->prev->right == nullptr) {
			int xx = nodo->prev->x + this->anchoNodo;
			int yy = nodo->prev->y;
			this->crearNodoDerecha(nodo->prev, xx, yy);
			nodo->prev->right->next = nodo->right;
			nodo->right->prev = nodo->prev->right;
		}
		if (nodo->next->left == nullptr) {
			int xx = nodo->next->x - this->anchoNodo;
			int yy = nodo->next->y;
			this->crearNodoIzquierda(nodo->next, xx, yy);
			nodo->next->left->prev = nodo->left;
			nodo->left->next = nodo->next->left;
		}if (nodo->next->right == nullptr) {
			int xx = nodo->next->x + this->anchoNodo;
			int yy = nodo->next->y;
			this->crearNodoDerecha(nodo->next, xx, yy);
			nodo->next->right->prev = nodo->right;
			nodo->right->next = nodo->next->right;
		}

	}
	void inicAreaActiva() {
		if (!this->nodoActivo->datoIniciado) { this->nodoActivo->inicializarDato(datos); }
		if (!this->nodoActivo->prev->datoIniciado) { this->nodoActivo->prev->inicializarDato(datos); }
		if (!this->nodoActivo->next->datoIniciado) { this->nodoActivo->next->inicializarDato(datos); }
		if (!this->nodoActivo->left->datoIniciado) { this->nodoActivo->left->inicializarDato(datos); }
		if (!this->nodoActivo->right->datoIniciado) { this->nodoActivo->right->inicializarDato(datos); }
		if (!this->nodoActivo->prev->left->datoIniciado) { this->nodoActivo->prev->left->inicializarDato(datos); }
		if (!this->nodoActivo->prev->right->datoIniciado) { this->nodoActivo->prev->right->inicializarDato(datos); }
		if (!this->nodoActivo->next->left->datoIniciado) { this->nodoActivo->next->left->inicializarDato(datos); }
		if (!this->nodoActivo->next->right->datoIniciado) { this->nodoActivo->next->right->inicializarDato(datos); }
	}

	void crearNnodos(int cant) {
		cant = cant - 3;
		NodoMapa* auxFila=this->inicio;
		NodoMapa* auxColumna=this->inicio;
		int pMedio = cant / 2;
		for (int i = 1; i <= (cant+1); i++) {
			for (int j = 1; j <= cant; j++) {
				auxFila = auxFila->right;
				generarAreaNodos(auxFila);
				if (j ==pMedio && i==pMedio+1) {
					this->nodoActivo = auxFila;		
				}
			}
			if (i < (cant+1)) {
				auxColumna = auxColumna->next;
				auxFila = auxColumna;
				generarAreaNodos(auxFila);
			}
		}
		nNodosMatriz = nNodos;
		cout << "cantidad nodos GENERADOS: "<<nNodosMatriz<<endl;
	}
	NodoMapa** obtenerVector(int cantNodos) {

		int contadorNodos = 0;
		NodoMapa** vec = new NodoMapa*[cantNodos];
		NodoMapa* auxColumna = this->inicio;
		NodoMapa* auxFila = this->inicio;
		while (auxColumna != nullptr || auxFila != nullptr) {
			if (auxColumna == nullptr) {
				if (auxFila != nullptr) {
					auxFila = auxFila->right;
					auxColumna = auxFila;
				}
			}
			else {
				if (contadorNodos >= cantNodos) { break; }
				vec[contadorNodos] = auxColumna;
				contadorNodos++;
				auxColumna = auxColumna->next;
			}
		}
		return vec;
	}
	int particionRight(NodoMapa** vect,int p,int right, function<bool(NodoMapa*, NodoMapa*,bool)>operacion,bool criterio=true) {
		NodoMapa* pivote = vect[right];
		int i = p - 1;
		for (int j = p; j <= right - 1; j++) {
			if (operacion(vect[j], pivote,criterio)) {
				i++;		
				NodoMapa *tmp= vect[j];
				vect[j] = vect[i];
				vect[i] = tmp;
			}
		}
		NodoMapa*tmp = vect[i+1];
		vect[i + 1] = vect[right];
		vect[right] = tmp;
		return i + 1;
	}
	void quickSort(NodoMapa** vect, int left, int right, function<bool(NodoMapa*, NodoMapa*,bool)>operacion,bool criterio) {
		if (right <= left) { return; }
		int p = particionRight(vect, left, right,operacion,criterio);
		quickSort(vect,left,p-1,operacion,criterio);
		quickSort(vect,p+1,right,operacion,criterio);
	}

	NodoMapa* buscarNodoXid(int id) {
		NodoMapa* nodoBuscado = nullptr;
		NodoMapa* auxColumna = this->inicio;
		NodoMapa* auxFila = this->inicio;
		while (auxColumna != nullptr || auxFila != nullptr) {
			if (auxColumna == nullptr) {
				if (auxFila != nullptr) {
					auxFila = auxFila->right;
					auxColumna = auxFila;
				}
			}
			else {
				if (auxColumna->id == id) { 
					this->nodoActivo=auxColumna;
					this->generarAreaNodos(this->nodoActivo);
					this->inicAreaActiva();
					break; }
				auxColumna = auxColumna->next;
			}
		}
		return nodoBuscado;
	}
	void ordenarMatrizNodos(string categoria, bool criterio) {
		auto compArboles = [](NodoMapa* elem1,  NodoMapa* elem2, bool ordenCreciente) {
			if (ordenCreciente) {return elem1->cantArboles < elem2->cantArboles;
			}else{ return elem1->cantArboles > elem2->cantArboles; }
		};
		auto compManzanos = [](NodoMapa* elem1, NodoMapa* elem2, bool ordenCreciente) {
			if (ordenCreciente) {return elem1->cantManzanos < elem2->cantManzanos;}
			else { return elem1->cantManzanos > elem2->cantManzanos; }
		};
		auto compRocas= [](NodoMapa* elem1, NodoMapa* elem2, bool ordenCreciente) {
			if (ordenCreciente) {return elem1->cantRocas < elem2->cantRocas;}
			else { return elem1->cantRocas > elem2->cantRocas; }
		};
		auto compAgua = [](NodoMapa* elem1, NodoMapa* elem2, bool ordenCreciente) {
			if (ordenCreciente) {return elem1->porcAgua < elem2->porcAgua;}
			else { return elem1->porcAgua > elem2->porcAgua; }
		};
		auto compArena = [](NodoMapa* elem1, NodoMapa* elem2, bool ordenCreciente) {
			if (ordenCreciente) {return elem1->porcArena < elem2->porcArena;
			}else { return elem1->porcArena > elem2->porcArena; }
		};
		auto compTierra = [](NodoMapa* elem1, NodoMapa* elem2, bool ordenCreciente) {
			if (ordenCreciente) {return elem1->porcTierra < elem2->porcTierra;}
			else { return elem1->porcTierra > elem2->porcTierra; }
		};
		NodoMapa** vect = obtenerVector(nNodosMatriz);
		if(categoria=="arbol"){ quickSort(vect, 0, nNodosMatriz - 1,compArboles,criterio); }
		else if(categoria=="manzano"){ quickSort(vect, 0, nNodosMatriz - 1, compManzanos, criterio); }
		else if (categoria == "roca") { quickSort(vect, 0, nNodosMatriz - 1, compRocas, criterio); }
		else if (categoria == "agua") { quickSort(vect, 0, nNodosMatriz - 1, compAgua, criterio); }
		else if (categoria == "arena") { quickSort(vect, 0, nNodosMatriz - 1, compArena, criterio); }
		else if (categoria == "tierra") { quickSort(vect, 0, nNodosMatriz - 1, compTierra, criterio); }
		buscarNodoXid(vect[0]->id);
	}

	void guardarDatos() {
		stringstream arch;
		arch << "{\n";
		arch << " \"MatrizNodos\": \"{";
		NodoMapa* aux = this->inicio;
		while (aux->prev != nullptr || aux->left != nullptr) {
			if (aux->prev != nullptr) {
				aux = aux->prev;
			}
			else if (aux->left != nullptr) {
				aux = aux->left;
			}
		}
		NodoMapa*  j = aux;
		while (aux!=nullptr || j!=nullptr) {
			if (aux == nullptr) {
				if (j != nullptr) {
					j = j->right;
					aux = j;
				}
			}
			else {
				////
				string nombreSeccion = "DatosNodo" + to_string(aux->id);
				
				int estado = 0;
				if (aux->datoIniciado) { estado=1; aux->dato->guardarTerreno(nombreSeccion);}
				arch << estado<<",";
				aux = aux->next;
			}
		}
		arch << "}\",\n";
		////hacer algo
		arch << "\n}";
		string tmp=arch.str();
		this->datos->archGuardarMapa << tmp;
		this->datos->archGuardarMapa.close();
		this->datos->archGuardarNodos.close();
	}
};