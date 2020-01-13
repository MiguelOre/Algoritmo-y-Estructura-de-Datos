#pragma once
#include "Escena.hpp";
#include <iostream>
#include <Windows.h>
using namespace std;
class ControlEscenas {
public:
	Escena** escenas;
	Escena* nuevaEscena;
	bool eliminando = false;
	bool agregando = false;
	bool reemplazando;
	int nEscenas = 0;//cantidad de escenas creadas
	ControlEscenas() {
		this->escenas = new Escena*[4];
	}
	~ControlEscenas() {
		delete nuevaEscena;
		for (int i = 0; i < this->nEscenas; i++) {
			delete this->escenas[i];
		}
		delete[] this->escenas;
	}
	void agregarEscena(Escena* nuevaEscena, bool reemplazar) {
		this->agregando = true;
		this->reemplazando = reemplazar;
		this->nuevaEscena = nuevaEscena;


	}
	void eliminarEscena() {
		this->eliminando = true;
		cout << "PRUEVA nnnn";
	}
	void actuzalizarStackEscenas() {
		if (this->eliminando && this->nEscenas>0) {
			delete this->escenas[nEscenas - 1];

			this->nEscenas--;
			if (this->nEscenas>0) {
				this->escenas[this->nEscenas - 1]->resumen();
			}
			this->eliminando = false;
		}
		if (this->agregando) {
			if (this->nEscenas > 0) {
				if (this->reemplazando) {
					delete this->escenas[this->nEscenas - 1];
					this->nEscenas--;
				}
				else {
					this->escenas[this->nEscenas - 1]->pause();
				}
			}
			this->nEscenas++;
			this->escenas[this->nEscenas - 1] = this->nuevaEscena;
			this->escenas[this->nEscenas - 1]->init();
			this->agregando = false;
		}

	}
	Escena* &getActiveScene() {
		if (this->nEscenas > 0) {
			return this->escenas[this->nEscenas - 1];
		}
		else {
			cout << "ERROR---------- ARREGLO ESCENAS VACIO";
		}
	}
	Escena* &getGameScene() {
		if (nEscenas > 1) {
			return this->escenas[nEscenas - 2];
		}
		else {
			cout << "Solo hay una escena-------------------";////borrarrr------------------------
		}
	}

	
};