#pragma once
#include <SFML\Graphics.hpp>
#include "ControlEscenas.hpp"
#include "ControlAssets.hpp"
#include "ControlEntradas.hpp"
#include <fstream>
using namespace sf;
struct DatosJuego {
	ControlEscenas escenas;
	ControlAssets assets;
	ControlEntradas inputs;
	RenderWindow window;
	
	int ancho;
	int alto;

	int altoMapa;
	int anchoMapa;

	int M_SIZE = 60;

	ofstream archGuardarMapa;
	ofstream archGuardarNodos;
	
	ifstream archCargarDatos;
	ifstream archCargarNodos;

};
class Juego {
	DatosJuego *data = new DatosJuego();
	float spf;
	Clock reloj;
public:
	Juego();
	~Juego();
	void ejecutar();
};