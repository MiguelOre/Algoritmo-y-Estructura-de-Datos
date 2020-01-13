#pragma once
#include "Escena.hpp";
#include <string>
#include "Juego.hpp"
class EscenaPausa:public Escena {
	Texture texFondo;
	Texture texTitulo;
	Texture texBtnContinuar;
	Texture texBtnGuardar;
	Texture texBtnSalir;

	Sprite imgFondo;
	Sprite imgTitulo;
	Sprite imgBtnContinuar;
	Sprite imgBtnGuardar;
	Sprite imgBtnSalir;
	DatosJuego* datos;

	//Pausa o gameover
	bool escenaPausa;
public:
	EscenaPausa(DatosJuego* datos,bool escenaPausa=true) {
		this->datos = datos;
		this->escenaPausa= escenaPausa;
	}
	void init() {
		texFondo.loadFromFile("img/pausa_fondo.png");
		texTitulo.loadFromFile("img/pausa_titulo.png");
		texBtnContinuar.loadFromFile("img/boton_continuar.png");
		texBtnGuardar.loadFromFile("img/boton_guardar.png");
		texBtnSalir.loadFromFile("img/boton_salir.png");

		imgFondo.setTexture(texFondo);
		imgTitulo.setTexture(texTitulo);
		imgBtnContinuar.setTexture(texBtnContinuar);
		imgBtnGuardar.setTexture(texBtnGuardar);
		imgBtnSalir.setTexture(texBtnSalir);

		this->datos->assets.redimencionarSprite(imgFondo, this->datos->ancho, this->datos->ancho);

		this->datos->assets.definirOrigen(imgTitulo,imgTitulo.getGlobalBounds().width/2,imgTitulo.getGlobalBounds().height/2);
		this->datos->assets.definirOrigen(imgBtnContinuar, imgBtnContinuar.getGlobalBounds().width / 2, imgBtnContinuar.getGlobalBounds().height / 2);
		this->datos->assets.definirOrigen(imgBtnGuardar, imgBtnGuardar.getGlobalBounds().width / 2, imgBtnGuardar.getGlobalBounds().height / 2);
		this->datos->assets.definirOrigen(imgBtnSalir, imgBtnSalir.getGlobalBounds().width / 2, imgBtnSalir.getGlobalBounds().height / 2);

		imgFondo.setPosition(0,0);
		imgTitulo.setPosition(this->datos->ancho / 2,100);
		imgBtnContinuar.setPosition(this->datos->ancho / 2, 250);
		imgBtnGuardar.setPosition(this->datos->ancho / 2, 420);
		imgBtnSalir.setPosition(this->datos->ancho / 2, 590);

		//Dubujar escena
		this->datos->window.draw(imgFondo);
		if (this->escenaPausa) {
			this->datos->window.draw(imgTitulo);
		}
		this->datos->window.draw(imgBtnContinuar);
		this->datos->window.draw(imgBtnGuardar);
		this->datos->window.draw(imgBtnSalir);
		this->datos->window.display();
	}
	void manejadorInput() {
		Event ev;
		while (this->datos->window.pollEvent(ev)) {
			if (ev.type == Event::Closed) {
				this->datos->window.close();
			}
			else if (this->datos->inputs.spriteMouseClick(this->imgBtnContinuar, this->datos->window,true)) {
				cout << this->datos->escenas.nEscenas;
				if (!this->escenaPausa) {
					this->datos->escenas.getGameScene()->reiniciarEscena("jugador");
				}
				this->datos->escenas.eliminarEscena();
			}
			else if (this->datos->inputs.spriteMouseClick(this->imgBtnGuardar, this->datos->window, true)) {
				this->datos->escenas.getGameScene()->guardarEscena();
			}
			else if (this->datos->inputs.spriteMouseClick(this->imgBtnSalir, this->datos->window,true)) {
				
				this->datos->window.close();
			}

		}
	}
	void actualizar() {

	}
	void dibujar() {

	}
};