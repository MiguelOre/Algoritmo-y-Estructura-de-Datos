#pragma once
#include "Mapa.hpp"
#include "Juego.hpp"
#include "Jugador.hpp"
#include "TrozoMapa.hpp"
#include "EscenaPerdiste.hpp";
#include "Enemigo.hpp";
#include "CtrlEnemigos.hpp"
#include <fstream>

class Mundo {
	DatosJuego* datos;
	Mapa* mapa;
	CtrlEnemigos * enemigos;
	Jugador jug;
public:
	Mundo(DatosJuego* datos) {
		this->datos = datos;
		mapa = new Mapa(datos,jug);
		enemigos = new CtrlEnemigos();

	}
	void manejadorEventoTeclado(Keyboard::Key key,bool estado) {
		if (key == Keyboard::A) { jug.izquierda = estado; }
		if (key == Keyboard::D) { jug.derecha = estado; }
		if (key == Keyboard::W) { jug.arriba = estado; }
		if (key == Keyboard::S) { jug.abajo = estado; }

		if (key == Keyboard::Num1) { jug.accion = 1; }
		else if (key == Keyboard::Num2) { jug.colecFruta >0 ? jug.accion = 2: jug.accion=1; }
		else if (key == Keyboard::Num3) { jug.colecMadera>=4 ?jug.accion = 3: jug.accion = 1; }
		else if (key == Keyboard::Num4) { jug.colecRoca>= 4 ?jug.accion = 4: jug.accion = 1; }
		else if (key == Keyboard::Num5) { jug.accion = 5; };
	}
	void manejadorEventoMouse(bool estado) {
		jug.teclaAtacar = estado;
	}
	void actualizarMundo() {
		jug.actualizar(this->datos,this->mapa->nodoActivo->dato->x, this->mapa->nodoActivo->dato->y);
		string tipoMaterial=mapa->ActualizarNodosActivos(jug,enemigos);
		enemigos->generarEnemigos(this->datos,this->mapa->nodoActivo->x,this->mapa->nodoActivo->y);
		enemigos->actualizar(jug);
		//sonidos pasos
		if (jug.medirDist > 50) {
			int sonido;
			if (tipoMaterial == "agua") {
				jug.velocidad = jug.minVel;
				sonido = 0;
			}
			else if (tipoMaterial == "arena") {
				jug.velocidad = jug.maxVel;
				sonido = 1;
			}
			else if (tipoMaterial == "tierra") {
				jug.velocidad = jug.maxVel;
				sonido = 2;
			}
				//cout << jug.px <<" , "<<jug.py<<endl;
			
			this->datos->assets.getSoundById(sonido)->setPitch(0.8f + (rand() % 10) / 22.0f);
			this->datos->assets.getSoundById(sonido)->play();
			jug.medirDist = 0;
		}

	}
	void pintarMundo() {
		View vista(FloatRect(0,0,this->datos->ancho,this->datos->alto));
		vista.setCenter(jug.px,jug.py);
		datos->window.setView(vista);

		mapa->pintarMapa(jug);
		enemigos->pintar(this->datos);
		

		//GUI **dibuja solo textos;
		View vistaGui = this->datos->window.getDefaultView();
		this->datos->window.setView(vistaGui);

		int posY = 10;
		int despY = 25;
		
		this->datos->assets.confTexto(0, "Madera:", 100, posY);
		this->datos->assets.dibujarTexto(0, this->datos->window);//Madera:
		this->datos->assets.confTexto(0, "Piedra:", 100, posY += despY);
		this->datos->assets.dibujarTexto(0, this->datos->window);//Madera:
		this->datos->assets.confTexto(0, "Manzanas:",100, posY += despY);
		this->datos->assets.dibujarTexto(0, this->datos->window);//Madera:
		this->datos->assets.confTexto(0, "Vida:", 100, posY += despY);
		this->datos->assets.dibujarTexto(0, this->datos->window);//Madera:
		posY = 10;
		this->datos->assets.confTexto(1, to_string(jug.colecMadera),225,posY);
		this->datos->assets.dibujarTexto(1, this->datos->window);
		this->datos->assets.confTexto(1, to_string(jug.colecRoca),225, posY += despY);
		this->datos->assets.dibujarTexto(1, this->datos->window);
		this->datos->assets.confTexto(1, to_string(jug.colecFruta), 225, posY += despY);
		this->datos->assets.dibujarTexto(1, this->datos->window);
		this->datos->assets.confTexto(1, to_string(jug.vida), 225, posY += despY);
		this->datos->assets.dibujarTexto(1, this->datos->window);
		
		if (jug.vida == 0) { this->datos->window.display(); this->datos->escenas.agregarEscena(new EscenaPerdiste(this->datos),false); };
	}
	void teletranspJugador(int trasladar=true) {
		if (trasladar) {
			this->jug.px = this->mapa->nodoActivo->x + (datos->ancho / 2) - 65;
			this->jug.py = this->mapa->nodoActivo->y + (datos->alto / 2) - 65;
		}else {
			jug.px -= jug.vx * 10;
			jug.py -= jug.vy * 10;
		}
		jug.vx = 0;
		jug.vy = 0;
		jug.izquierda = false;
		jug.derecha = false;
		jug.arriba = false;
		jug.abajo = false;
	}
	void busquedaNodos(string categoria, bool criterio) {
		this->mapa->ordenarMatrizNodos(categoria,criterio);
	}
	//REiniciar estados
	void reiniciarJugador() {
		jug.reiniciarEstado(this->mapa->nodoActivo->x,this->mapa->nodoActivo->y);
		
	}
	//Guardar datos
	void guardarJuego() {
		this->datos->archGuardarMapa.open("datosJuego.json",ios::trunc);
		this->datos->archGuardarNodos.open("datosNodos.json", ios::trunc);
		this->mapa->guardarDatos();
	}
};