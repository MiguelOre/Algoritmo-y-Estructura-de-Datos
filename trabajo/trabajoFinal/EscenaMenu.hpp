#pragma once
#include "Escena.hpp"
#include "Juego.hpp"
#include "EscenaJuego.hpp"
class EscenaMenu :public Escena {
	Texture texFondo;
	Texture texBotonIniciar;
	Texture texBotonSalir;
	Texture texBotonCargar;

	Sprite imgFondo;
	Sprite imgBotonIniciar;
	Sprite imgBotonSalir;
	Sprite imgBotonCargar;
	DatosJuego* datos;

public:
	EscenaMenu(DatosJuego*datos) {
		this->datos = datos;
	}
	void init() {
		texFondo.loadFromFile("img/menu_fondo.png");
		this->imgFondo.setTexture(texFondo);
		this->datos->assets.redimencionarSprite(this->imgFondo, this->datos->ancho, this->datos->alto);

		this->texBotonIniciar.loadFromFile("img/boton_iniciar.png");
		this->imgBotonIniciar.setTexture(this->texBotonIniciar);
		imgBotonIniciar.setOrigin(imgBotonIniciar.getGlobalBounds().width / 2, imgBotonIniciar.getGlobalBounds().height / 2);
		imgBotonIniciar.setPosition(this->datos->ancho / 2, 159);

		this->texBotonCargar.loadFromFile("img/boton_cargar.png");
		this->imgBotonCargar.setTexture(this->texBotonCargar);
		imgBotonCargar.setOrigin(imgBotonCargar.getGlobalBounds().width / 2, imgBotonCargar.getGlobalBounds().height / 2);
		imgBotonCargar.setPosition(this->datos->ancho / 2, 375);

		this->texBotonSalir.loadFromFile("img/boton_salir.png");
		this->imgBotonSalir.setTexture(texBotonSalir);
		this->imgBotonSalir.setPosition(300, 300);
		imgBotonSalir.setOrigin(imgBotonSalir.getGlobalBounds().width / 2, imgBotonSalir.getGlobalBounds().height / 2);
		imgBotonSalir.setPosition(this->datos->ancho / 2, 591);
	}
	void manejadorInput() {
		Event ev;
		while (this->datos->window.pollEvent(ev)) {
			if (ev.type == Event::Closed) {
				this->datos->window.close();
			}
			if (this->datos->inputs.spriteMouseClick(this->imgBotonIniciar, datos->window, true)) {
				//datos->escenaJuego = new EscenaJuego(this->datos);
				this->datos->escenas.agregarEscena(new EscenaJuego(this->datos), true);
			}if (this->datos->inputs.spriteMouseClick(this->imgBotonCargar, datos->window, true)) {
				cout << "Cargar JUEGO-----";
			}
			if (this->datos->inputs.spriteMouseClick(this->imgBotonSalir, datos->window, true)) {
				datos->window.close();
			}

		}
	}
	void actualizar(float dt) {

	}
	void dibujar(float dt) {
		datos->window.clear();
		datos->window.draw(this->imgFondo);
		datos->window.draw(this->imgBotonIniciar);
		datos->window.draw(this->imgBotonCargar);
		datos->window.draw(this->imgBotonSalir);
		datos->window.display();
	}
};