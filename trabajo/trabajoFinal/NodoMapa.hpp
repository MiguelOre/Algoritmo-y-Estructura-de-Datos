#pragma once
#include "TrozoMapa.hpp";
#include "Juego.hpp";
class NodoMapa {
public:
	NodoMapa* next;
	NodoMapa* prev;
	NodoMapa* left;
	NodoMapa*right;
	TrozoMapa * dato;

	int id;
	bool datoIniciado;

	int porcAgua;
	int porcArena;
	int porcTierra;
	int cantArboles;
	int cantManzanos;
	int cantRocas;
	int cantCactus;

	int x;
	int y;
	int alto;
	int ancho;
	NodoMapa(int x, int y) {
		this->datoIniciado = false;
		this->next = nullptr;
		this->prev = nullptr;
		this->left = nullptr;
		this->right = nullptr;
		this->x = x;
		this->y = y;
		
		//generar info trozo mapa
		this->porcAgua = rand() % 60;
		this->porcArena = rand() % (101 - porcAgua);
		this->porcTierra = 100 - (porcAgua + porcArena);
		if (porcTierra > 10) {
			int aux = porcTierra / 3;
			if (aux > 0) { this->cantArboles = rand() % aux; }
			else { cantArboles = 0; }
			if (aux > 0) { this->cantManzanos = rand() % aux; }
			else { cantManzanos = 0; }
			if (aux > 0) { this->cantRocas = rand() % aux; }
			else { this->cantRocas = 0; };	
		}else{ cantArboles = 0; cantManzanos = 0; this->cantRocas = 0;}

		if ((porcArena / 4) > 0) { this->cantCactus = rand() % (porcArena / 4); }
		else { cantCactus = 0; }

		
		cout << cantArboles << " " << cantManzanos << " "<<cantRocas << " " << porcAgua << " " << porcArena << " " << porcTierra << endl;

	}
	void inicializarDato(DatosJuego * datos) {
		this->datoIniciado = true;
		this->dato = new TrozoMapa(datos,this->x,this->y, porcAgua,porcArena,porcTierra,cantArboles,cantManzanos,cantCactus,cantRocas);
	}
};