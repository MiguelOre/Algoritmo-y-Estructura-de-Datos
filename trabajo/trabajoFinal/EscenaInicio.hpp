#pragma once
#include "Escena.hpp"
#include "Juego.hpp"
#include "EscenaMenu.hpp"
#include <iostream>
using namespace std;
class EscenaInicio :public Escena {
	Texture texturaFondo;
	Sprite imgFondo;
	DatosJuego* data;
	Clock tiempo;
	int tiempoActivo;
public:
	EscenaInicio(DatosJuego*data) {
		this->data = data;
		this->tiempoActivo = 0;
	}
	void init() {
		texturaFondo.loadFromFile("img/splash.jpg");
		imgFondo.setTexture(this->texturaFondo);
		this->data->assets.redimencionarSprite(this->imgFondo,data->ancho,data->alto);
	}
	void manejadorInput() {
		Event ev;
		while (this->data->window.pollEvent(ev)) {
			if (ev.type == Event::Closed) {
				this->data->window.close();
			}
		}
	}
	void actualizar(float dt) {
		if (tiempo.getElapsedTime().asSeconds() > this->tiempoActivo) {
			this->data->escenas.agregarEscena(new EscenaMenu(this->data),true);
		}
	}
	void dibujar(float dt) {
		/* 
		data->window.clear();
		data->window.draw(this->imgFondo);
		data->window.display();*/
	}
};