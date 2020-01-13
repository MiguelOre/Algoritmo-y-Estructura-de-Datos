#include "Juego.hpp"
#include "EscenaInicio.hpp"
Juego::Juego() {
	this->data->window.create(VideoMode(1300,900),"Juego");
	this->data->window.setFramerateLimit(60);
	this->data->escenas.agregarEscena(new EscenaInicio(this->data),false);
	this->data->ancho = data->window.getSize().x;
	this->data->alto = data->window.getSize().y;
	this->ejecutar();
}
Juego::~Juego() {
	//delete this->data;
}
void Juego::ejecutar() {
	while (this->data->window.isOpen()) {
		
		data->escenas.actuzalizarStackEscenas();
		data->escenas.getActiveScene()->manejadorInput();
		data->escenas.getActiveScene()->actualizar(0.16);
		data->escenas.getActiveScene()->dibujar(0.16);
	}
}