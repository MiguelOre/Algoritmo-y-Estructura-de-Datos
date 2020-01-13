#pragma once
#include <string>
using namespace std;
class Escena {
public:
	virtual void init() {};
	virtual void manejadorInput() {}
	virtual void actualizar(float dt) {};
	virtual void dibujar(float dt) {};
	virtual void pause() {}
	virtual void resumen() {}
	//EscenaJuego
	virtual void guardarEscena() {}
	virtual void reiniciarEscena(string obj){}
	virtual void transportarJugador(bool nuevoLugar=true) {}
	virtual void busquedaNodos(string categoria,bool criterio) {}
};