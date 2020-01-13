#pragma once
struct Recurso {
	int x; int y;
	int radio = 20;
	int vida;
	int valor = 0;
	string tipo;//arbol, roca,cactus,manzano // bloqueMadera, bloquePiedra
				//bloques
	int costo = 5;
	void inic(string tipo, int x, int y) {
		this->x = x;
		this->y = y;
		this->tipo = tipo;
		if (tipo == "arbol") {
			this->radio = 30;
			this->valor = 1;
			this->vida = 10;
		}
		else if (tipo == "roca") {
			this->radio = 40;
			this->valor = 1;
			this->vida = 20;
		}
		else if (tipo == "cactus") {
			this->radio = 23;
			this->valor = 1;
			this->vida = 5;
		}
		else if (tipo == "manzano") {
			this->radio = 30;
			this->valor = 1;
			this->vida = 12;
		}
		else if (tipo == "bloqueMadera") {
			this->radio = 20;
			this->valor = 1;
			this->vida = 5;
		}
		else if (tipo == "bloqueRoca") {
			this->radio = 20;
			this->valor = 1;
			this->vida = 10;
		}
	}
};