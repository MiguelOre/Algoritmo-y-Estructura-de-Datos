#pragma once
#include "Escena.hpp"
#include "Juego.hpp"
#include "Mundo.hpp"
#include "EscenaPausa.hpp"
#include <iostream>
using namespace std;
class EscenaJuego :public Escena {
	Texture texBtnMenu;
	Sprite imgBtnMenu;

	Texture texBtnBanner;
	Sprite imgBtnBanner;
	DatosJuego* data;
	Mundo* mundo;
public:
	EscenaJuego(DatosJuego*data) {
		this->data = data;
		mundo = new Mundo(data);
	}
	void init() {
		this->texBtnMenu.loadFromFile("img/juego/gui/btn_menu.png");
		this->imgBtnMenu.setTexture(texBtnMenu);
		this->imgBtnMenu.setPosition(10, 10);
		this->imgBtnMenu.setScale(0.5, 0.5);

		this->texBtnBanner.loadFromFile("img/juego/gui/banner.png");
		this->imgBtnBanner.setTexture(texBtnBanner);
		this->imgBtnBanner.setOrigin(this->imgBtnBanner.getGlobalBounds().width / 2, this->imgBtnBanner.getGlobalBounds().height / 2);
		this->imgBtnBanner.setPosition(this->data->ancho / 2, this->data->alto - this->imgBtnBanner.getGlobalBounds().height - 20);

		this->data->assets.cargarSprite("img/juego/material_agua.jpg");
		this->data->assets.cargarSprite("img/juego/material_arena.jpg");
		this->data->assets.cargarSprite("img/juego/material_tierra.jpg");
		this->data->assets.cargarSprite("img/juego/colisionable_arbol.png", 0, true);
		this->data->assets.cargarSprite("img/juego/colisionable_roca.png", 0, true);
		this->data->assets.cargarSprite("img/juego/colisionable_cactus.png", 0, true);
		this->data->assets.cargarSprite("img/juego/colisionable_manzanal.png", 0, true);
		this->data->assets.cargarSprite("img/juego/manzana.png", 0, true);
		this->data->assets.cargarSprite("img/juego/colisionable_bloqueMadera.png", 0, true);
		this->data->assets.cargarSprite("img/juego/colisionable_bloqueRoca.png", 0, true);
		this->data->assets.cargarSprite("img/juego/enemigo.png", 0, true);
		this->data->assets.cargarSprite("img/juego/flecha.png", 0, true);
		this->data->assets.cargarSprite("img/juego/portal.png", 0, true);

		this->data->assets.cargarSonido("audio/juego/pasos_agua01.wav");
		this->data->assets.cargarSonido("audio/juego/pasos_arena02.wav");
		this->data->assets.cargarSonido("audio/juego/pasos_tierra01.wav");
		this->data->assets.cargarSonido("audio/juego/jugador_ataque.wav");
		this->data->assets.cargarSonido("audio/juego/jugador_comer2.wav");
		this->data->assets.cargarSonido("audio/juego/flecha_lanzamiento.wav");
		this->data->assets.getSoundById(3)->setVolume(40);
		this->data->assets.cargarFuente("fuente/juego/fuente-normal.ttf");

		this->data->assets.crearTexto(0, 25, Color::White);//indice fuente, tamaño, color
		this->data->assets.crearTexto(0, 25, Color::White);

		this->data->assets.confTexto(0, "label: ", 100, 10);//index texto, mensaje, posX, posY
		this->data->assets.confTexto(1, "contador", 225, 10);//index texto, mensaje, posX, posY
	}

	void manejadorInput() {
		Event ev;
		while (this->data->window.pollEvent(ev)) {
			if (ev.type == Event::Closed) {
				this->data->window.close();
			}
			if (ev.type == Event::KeyPressed) {	
				mundo->manejadorEventoTeclado(ev.key.code,true);
			}
			if (ev.type == Event::KeyReleased) {
				mundo->manejadorEventoTeclado(ev.key.code, false);
			}
			if (ev.type == Event::MouseButtonPressed) {
				mundo->manejadorEventoMouse(true);
			}
			else if (ev.type == Event::MouseButtonReleased) {
				mundo->manejadorEventoMouse(false);
			}
			if (this->data->inputs.spriteMouseClick(this->imgBtnMenu, this->data->window)) {
				this->data->escenas.agregarEscena(new EscenaPausa(this->data,true), false);
			}
		}
	}
	void actualizar(float dt) {
		this->mundo->actualizarMundo();

	}
	void dibujar(float dt) {
		this->data->window.clear();
		this->mundo->pintarMundo();//cambia de vista al mundo y lo deja en vista por defecto

		this->dibujarGui();
		this->data->window.display();
	}
	void dibujarGui() {
		this->data->window.draw(this->imgBtnBanner);
		this->data->window.draw(this->imgBtnMenu);
	}
	//getters setters
	void transportarJugador(bool nuevoLugar=true) {
		this->mundo->teletranspJugador(nuevoLugar);
	}
	void busquedaNodos(string categoria,bool criterio) {
		this->mundo->busquedaNodos(categoria,criterio);
	}
	//REINICIAR ESTADOS
	void reiniciarEscena(string obj) {
		if (obj == "jugador") { this->mundo->reiniciarJugador(); };
	}
	////Guardado de datos
	void guardarEscena() {
		this->mundo->guardarJuego();
	}
};