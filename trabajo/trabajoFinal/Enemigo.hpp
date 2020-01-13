#pragma once
#include "Jugador.hpp"
struct Enemigo {
	float x; float y;
	float dx, dy;
	int radio = 25;
	float rotacion;
	int vida=5;
	int vel;
	Enemigo() {
		dx = 0;
		dy = 0;
		vida = 1;
		vel = 1.5;
	}
	void actualizar(Jugador& jug) {
		int cx = jug.px - this->x;
		int cy = jug.py - this->y;
		float dist = fabs(cx*cx + cy*cy);
		this->rotacion = atan2(cy, cx);

		dx = cos(this->rotacion);
		dy = sin(this->rotacion);
		if (dist > 10) {
			this->x += dx;
			this->y += dy;
		}
		if (dist < (this->radio)*(this->radio)) {
			jug.decrementarVida();
		}


	}
};