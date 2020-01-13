#pragma once
#pragma once
#include "Enemigo.hpp"
#include "Jugador.hpp"
#include "Recurso.hpp"
#include "Juego.hpp"
#include "Jugador.hpp"
class CtrlEnemigos {
	Enemigo* enemigos;
	int nEnemigos;
	int maxNumEnem;

	int temporizador;
	int minTiempoGen;
public:
	CtrlEnemigos() {
		this->maxNumEnem = 5;
		this->nEnemigos = 0;
		enemigos = new Enemigo[maxNumEnem];

		temporizador = 0;
		minTiempoGen = 100;//cada 2000 milisegundos se genera enemigos;

	}
	void actualizar(Jugador&jug) {
		//generarEnemigos();

		for (int i = 0; i < nEnemigos; i++) {
			enemigos[i].actualizar(jug);

		}
	}
	void generarEnemigos(DatosJuego *&datos,int nodoX,int nodoY) {
		temporizador++;
		if (temporizador>minTiempoGen && nEnemigos<maxNumEnem) {
			temporizador = 0;
			int numRandom = rand() % 5;
			if (numRandom <1) {
				int numLugar = rand() % 5;
				int x = nodoX;
				int y = nodoY;
				
				switch (numLugar) {
				case 1:
					y +=datos->alto;
					break;
				case 2:
					x -=datos->ancho;
					
					break;
				case 3:
					x += datos->ancho;
					break;
				case 4:
					y -= datos->alto;
					break;
				default:
					x +=datos->alto;
				}
				enemigos[nEnemigos].x = x;
				enemigos[nEnemigos].y = y;
				enemigos[nEnemigos].vida = 3;
				nEnemigos++;
				cout << "ZOMBIE GENERADO---" << nEnemigos<<enemigos[nEnemigos-1].vida << endl;
			}
		}
	}
	void colisionObstaculos(Recurso& recurso,Jugador&jug) {
			Enemigo* tmp;
		for (int i = 0; i < nEnemigos; i++) {
			//Colision con recursos del mapa
			tmp = &(enemigos[i]);
			float cx = tmp->x - recurso.x;
			float cy = tmp->y - recurso.y;
			float hip = sqrt(cx*cx + cy*cy);
			float radio = recurso.radio + tmp->radio;
			if (hip < radio) {
				float s = radio - hip;
				cx = cx / hip;
				cy = cy / hip;
				tmp->x += cx*s / 2;
				tmp->y += cy*s / 2;
			}
			//colision entre enemigos
			for (int j = i+1; j < nEnemigos; j++) {
				cx = enemigos[j].x - tmp->x;
			    cy = enemigos[j].y - tmp->y;
				hip = sqrt(cx*cx + cy*cy);
				radio = tmp->radio + enemigos[j].radio;
				if (hip < radio) {
					float s = radio - hip;
					cx = cx / hip;
					cy = cy / hip;
					enemigos[j].x += cx*s / 2;
					enemigos[j].y += cy*s / 2;
					tmp->x -= cx*s / 2;
					tmp->y -= cy*s / 2;
				}
			}
			//colision con flechas
			for (int z = 0; z < jug.nFlechas; z++) {
				if (jug.flechas[z]->distanciaHacia(tmp->x, tmp->y)<(tmp->radio*tmp->radio)) {
					jug.eliminarFlecha(z);
					z--;
					tmp->vida--;	
				}
				if (tmp->vida <= 0) {
					this->eliminarEnemigo(i);
					i--;
				}

			}
		}
		tmp = NULL;
		delete tmp;
	}
	void eliminarEnemigo(int i) {
		if (nEnemigos >= 1) {
			for (int j = i + 1; j < nEnemigos; j++) {
				enemigos[j - 1] = enemigos[j];
			}

			nEnemigos--;
		}

	}
	void pintar(DatosJuego* datos) {
		for (int i = 0; i < nEnemigos; i++) {
			datos->assets.getSpriteById(10)->setPosition(enemigos[i].x, enemigos[i].y);
			datos->assets.getSpriteById(10)->setRotation(enemigos[i].rotacion / 3.141516f * 180);
			datos->window.draw(*datos->assets.getSpriteById(10));
		}
	}
};