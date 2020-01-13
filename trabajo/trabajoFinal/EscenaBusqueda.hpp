#pragma once
#include <SFML\Graphics.hpp>
#include "Escena.hpp"
#include "Juego.hpp"
#include "EscenaJuego.hpp"
#include <iostream>
using namespace std;
using namespace sf;
struct BotonIr {

};
class EscenaBusqueda:public Escena {
	Texture texFondo;
	Sprite imgFondo;

	Texture texBtnCriterio;
	Sprite imgBtnCriterio;

	Texture texBtnVolver;
	Sprite imgBtnVolver;

	Sprite* iconoArbol;
	Sprite* iconoManzano;
	Sprite * iconoRoca;
	Sprite* iconoAgua;
	Sprite *iconoArena;
	Sprite * iconoTierra;

	Text texto;
	DatosJuego *datos;

	bool criterioBusqueda;
public:
	EscenaBusqueda(DatosJuego*datos) {
		this->datos = datos;
		criterioBusqueda = false;
		texto.setFont(*datos->assets.getFontById(0));
		texto.setStyle(Text::Bold);
		texto.setCharacterSize(23);
		texto.setPosition(613, 212);
		texto.setFillColor(Color::White);
		texto.setString("Mayor");
	}
	void init() {
		texFondo.loadFromFile("img/busqueda_fondo.png");
		texBtnVolver.loadFromFile("img/btn_volver.png");
		texBtnCriterio.loadFromFile("img/btn_criterio.png");

		imgFondo.setTexture(texFondo);
		imgBtnVolver.setTexture(texBtnVolver);
		imgBtnCriterio.setTexture(texBtnCriterio);
		this->iconoAgua = datos->assets.getSpriteById(0);
		this->iconoArena = datos->assets.getSpriteById(1);
		this->iconoTierra = datos->assets.getSpriteById(2);
		this->iconoArbol = datos->assets.getSpriteById(3);
		this->iconoManzano = datos->assets.getSpriteById(6);
		this->iconoRoca = datos->assets.getSpriteById(4);
		iconoAgua->setPosition(450, 471);
		iconoArena->setPosition(620, 471);
		iconoTierra->setPosition(794, 471);
		iconoArbol->setPosition(580+70,309+70);
		iconoManzano->setPosition(428+52, 327+52);
		iconoRoca->setPosition(775+48, 334+45);
		imgBtnCriterio.setPosition(591, 197);
		imgBtnVolver.setPosition(32, 735);
		this->dibujarUnaVez();
	}
	void dibujarUnaVez() {
		datos->window.clear();
		datos->window.draw(imgFondo);
		datos->window.draw(*datos->assets.getSpriteById(0));
		datos->window.draw(*datos->assets.getSpriteById(1));
		datos->window.draw(*datos->assets.getSpriteById(2));
		datos->window.draw(*datos->assets.getSpriteById(3));
		datos->window.draw(*datos->assets.getSpriteById(6));
		datos->window.draw(*datos->assets.getSpriteById(4));
		datos->window.draw(imgBtnCriterio);
		datos->window.draw(imgBtnVolver);
		datos->window.draw(texto);
		datos->window.display();
	}
	void manejadorInput() {
		Event ev;
		while (datos->window.pollEvent(ev)) {
			if (ev.type == Event::Closed) {
				datos->window.close();
			}
			else if (datos->inputs.spriteMouseClick(imgBtnVolver,datos->window)) {
				datos->escenas.getGameScene()->transportarJugador(false);
				datos->escenas.eliminarEscena();
			}
			else if (datos->inputs.spriteMouseClick(imgBtnCriterio, datos->window)) {
				if (this->criterioBusqueda) {
					criterioBusqueda = false;
					texto.setString("Mayor");
					dibujarUnaVez();
				}
				else {
					criterioBusqueda = true;
					texto.setString("Menor");
					dibujarUnaVez();
				}
			}
			else if (datos->inputs.spriteMouseClick(*iconoAgua, datos->window)) {
				datos->escenas.getGameScene()->busquedaNodos("agua",criterioBusqueda);
				datos->escenas.getGameScene()->transportarJugador(true);
				datos->escenas.eliminarEscena();
			}
			else if (datos->inputs.spriteMouseClick(*iconoArena, datos->window)) {
				datos->escenas.getGameScene()->busquedaNodos("arena", criterioBusqueda);
				datos->escenas.getGameScene()->transportarJugador(true);
				datos->escenas.eliminarEscena();
			}
			else if (datos->inputs.spriteMouseClick(*iconoTierra, datos->window)) {
				datos->escenas.getGameScene()->busquedaNodos("tierra", criterioBusqueda);
				datos->escenas.getGameScene()->transportarJugador(true);
				datos->escenas.eliminarEscena();
			}
			else if (datos->inputs.spriteMouseClick(*iconoArbol, datos->window,true)) {
				datos->escenas.getGameScene()->busquedaNodos("arbol", criterioBusqueda);
				datos->escenas.getGameScene()->transportarJugador(true);
				datos->escenas.eliminarEscena();
			}
			else if (datos->inputs.spriteMouseClick(*iconoManzano, datos->window,true)) {
				datos->escenas.getGameScene()->busquedaNodos("manzano", criterioBusqueda);
				datos->escenas.getGameScene()->transportarJugador(true);
				datos->escenas.eliminarEscena();
			}
			else if (datos->inputs.spriteMouseClick(*iconoRoca, datos->window,true)) {
				datos->escenas.getGameScene()->busquedaNodos("roca", criterioBusqueda);
				datos->escenas.getGameScene()->transportarJugador(true);
				datos->escenas.eliminarEscena();
			}
		}
	}
	void actualizar() {

	}
	void dibujar() {

	}
};