#pragma once
#include "Escena.hpp"
#include "EscenaPausa.hpp"
#include "Juego.hpp"
#include <iostream>
using namespace std;
class EscenaPerdiste:public Escena {
	Texture texturaFondo;
	Sprite imgFondo;

	Texture texturaTitulo;
	Sprite imgTitulo;
	DatosJuego* data;
	Clock tiempo;
	int tiempoActivo;
public:
	EscenaPerdiste(DatosJuego*data) {
		this->data = data;
		this->tiempoActivo = 2;
	}
	void init() {
		texturaFondo.loadFromFile("img/pausa_fondo.png");
		imgFondo.setTexture(this->texturaFondo);
		imgFondo.setOrigin(this->imgFondo.getGlobalBounds().width / 2, imgFondo.getGlobalBounds().height / 2);
		imgFondo.setPosition(this->data->ancho / 2, this->data->alto / 2);
		this->data->assets.redimencionarSprite(this->imgFondo, data->ancho, 210);

		texturaTitulo.loadFromFile("img/perdiste_titulo.png");
		imgTitulo.setTexture(texturaTitulo);
		imgTitulo.setOrigin(this->imgTitulo.getGlobalBounds().width / 2, imgTitulo.getGlobalBounds().height / 2);
		imgTitulo.setPosition(this->data->ancho / 2, this->data->alto / 2);
		data->window.draw(this->imgFondo);
		data->window.draw(this->imgTitulo);
		data->window.display();
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
			this->data->escenas.agregarEscena(new EscenaPausa(this->data,false), true);
		}
	}
	void dibujar(float dt) {

	}
};