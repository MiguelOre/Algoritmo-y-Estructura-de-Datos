#pragma once

#include "Juego.hpp"

struct Flecha {
	float x;
	float y;
	float dx;
	float dy;
	float direccion;
	float velocidad = 11;

	int vida=50;
	bool borrar = false;
	Flecha(int x,int y,int dir) {
		this->x = x;
		this->y = y;
		this->direccion = dir/180.0f*3.141516;
		this->dx = cos(this->direccion)*velocidad;
		this->dy = sin(this->direccion)*velocidad;
	}
	void actualizar() {
		this->vida--;
		this->x += dx;
		this->y += dy;
		if (vida < 0) {
			borrar = true;
		}
	}
	void pintar(Sprite* img,RenderWindow&win) {

		img->setPosition(this->x, this->y);
		img->setRotation((this->direccion / 3.1415160f) * 180);
		win.draw((*img));
	}
	int  distanciaHacia(int x,int y) {
		int cx=this->x-x;
		int cy=this->y-y;
		return  fabs(cx*cx + cy*cy);

	}
};

struct Jugador {
	Texture texJugador;
	Sprite imgJugador;

	Texture texBrazos;
	Sprite imgBrazos;

	Texture texSostener;
	Sprite imgSostener;

	Texture texArco;
	Sprite imgArco;

	bool izquierda;
	bool derecha;
	bool arriba;
	bool abajo;

	float px, py;
	float vx, vy;
	float ax, ay;

	float maxVel = 3;
	float minVel = 1;
	float velocidad = maxVel;
	float friccion = 0.94;
	int rotacion = 0;
	int radio = 75;


	int accion=1;

	bool teclaAtacar = false;//tecla ataque precionado
	bool actuar;  //ataque (1 frame)

	int timerCoolDown = 0; 
	int coolDown = 25; 
	int areaAtaque = 30;

	int medirDist = 0; //para ejecucion de sonidos


	//contador objetos coleccionables
	int colecMadera = 300;
	int colecRoca = 300;
	int colecFruta = 10;

	//gestionan el decremento de vida
	int vida = 5;
	int tempDecVida = 0;
	int maxTiempoDec = 30;
	//gestionan flechas
	Flecha ** flechas;
	int nFlechas;
	RenderTexture renderJugador;
	Jugador() {
		renderJugador.create(140, 140);	
		flechas = new Flecha*[10];
		nFlechas = 0;
		texJugador.loadFromFile("img/juego/jugador.png");
		imgJugador.setTexture(texJugador);
		imgJugador.setOrigin(imgJugador.getGlobalBounds().width / 2, imgJugador.getGlobalBounds().height / 2);
		imgJugador.setPosition(40, 70);

		texBrazos.loadFromFile("img/juego/jugador_brazos.png");
		imgBrazos.setTexture(texBrazos);
		imgBrazos.setOrigin(0, imgBrazos.getGlobalBounds().height / 2);
		imgBrazos.setPosition(32, 70);

		texSostener.loadFromFile("img/juego/jugador_brazos-sostener.png");
		imgSostener.setTexture(texSostener);
		imgSostener.setOrigin(0, imgSostener.getGlobalBounds().height / 2);
		imgSostener.setPosition(32, 70);

		texArco.loadFromFile("img/juego/jugador_arco.png");
		imgArco.setTexture(texArco);
		imgArco.setOrigin(0, imgSostener.getGlobalBounds().height / 2);
		imgArco.setPosition(40, 70);
	}
	void reiniciarEstado(int px,int py) {
		this->izquierda = false;
		this->derecha = false;
		this->arriba = false;
		this->abajo = false;
		this->actuar = false;
		this->vida = 5;
		this->colecFruta = 0;
		this->colecMadera = 0;
		this->colecRoca = 0;
		this->px = px;
		this->py = py;
		this->vx = 0;
		this->vy = 0;
		this->ax = 0;
		this->ay = 0;
	}
	void actualizar(DatosJuego* datos,int nodoX, int nodoY) {
		this->px += this->vx;
		this->py += this->vy;
		this->vx += this->ax;
		this->vy += this->ay;	
		int cx= Mouse::getPosition(datos->window).x-datos->ancho/2;
		int cy= Mouse::getPosition(datos->window).y-datos->alto/2;
		this->rotacion = atan2(cy,cx) / 3.141516f * 180;

		if (velocidad == minVel) {
			if (vx != 0 || vy != 0) { medirDist += abs(vx * 2); medirDist += abs(vy * 2); }
		}
		else {
			if (vx != 0 || vy != 0) { medirDist += abs(vx); medirDist += abs(vy); }//temporizador para reproducir sonidos de pasos
		}

		if (this->izquierda) { this->vx = -1; }
		else if (this->derecha) { this->vx = 1; }

		if (this->arriba) { this->vy = -1; }
		else if (this->abajo) { this->vy = 1; }
		float dist = sqrt(vx*vx + vy*vy);
		if (dist != 0) {
			if (this->izquierda) { this->vx = (this->vx / dist)*velocidad; }
			else if (this->derecha) { this->vx = (this->vx / dist)*velocidad; }
			if (this->arriba) { this->vy = (this->vy / dist)*velocidad; }
			else if (this->abajo) { this->vy = (this->vy / dist)*velocidad; }

		}
		this->vx *= this->friccion;
		this->vy *= this->friccion;
		//ataque
		if (timerCoolDown <= coolDown+10) {
			timerCoolDown++;
		}
		if (actuar) {
			actuar = false;
		}
		if (teclaAtacar) {
			if (timerCoolDown > coolDown) {
				this->actuar= true;
				this->realizarAccion(datos);
				timerCoolDown = 0;
			}
		}
		//temporizador descrementar vida
		if (tempDecVida <= maxTiempoDec) {
			this->tempDecVida++;
		}
		//flechas
		for (int i = 0; i < nFlechas; i++) {
			flechas[i]->actualizar();
			if (flechas[i]->borrar) {
				this->eliminarFlecha(i);
			}
		}
	}
	void realizarAccion(DatosJuego* datos) {	
		if (this->accion == 1) {
			//accion de destruir obstaculo en: TrozoMapa.hpp		
			datos->assets.getSoundById(3)->setPitch(0.8f + (rand() % 10) / 22.0f);
			datos->assets.getSoundById(3)->play();
		}
		else if (this->accion==2) {
			if (this->colecFruta > 0) {
				this->colecFruta--;
				this->vida++;			
				datos->assets.getSoundById(4)->setPitch(0.8f + (rand() % 10) / 22.0f);
				datos->assets.getSoundById(4)->play();
				if (colecFruta == 0) { this->accion = 1; }
			}
		}
		else if (this->accion == 5) {
			if (colecMadera > 0 && colecRoca > 0) {
				this->colecMadera--;
				this->colecRoca--;
				this->flechas[nFlechas] = new Flecha(this->px,this->py,this->rotacion);
				this->nFlechas++;
				datos->assets.getSoundById(5)->setPitch(1 + (rand() % 10) / 22.0f);
				datos->assets.getSoundById(5)->play();
				if (colecRoca == 0) { this->accion = 1; }
			}
		}

	}
	void pintar(DatosJuego* datos) {
		Sprite* tmpFlecha = datos->assets.getSpriteById(11);
		for (int i = 0; i < nFlechas; i++) {
			flechas[i]->pintar(tmpFlecha,datos->window);
		}
		tmpFlecha = NULL;
		delete tmpFlecha;
		//DibujarJugador
		renderJugador.clear(Color::Transparent);
		Sprite *tmp;
		if (this->accion==1) {
			renderJugador.draw(this->imgBrazos);
		}
		else if (this->accion == 2) {
			tmp = datos->assets.getSpriteById(7);
			tmp->setPosition(80, 70);
			renderJugador.draw(this->imgSostener);
			renderJugador.draw(*tmp);
		}
		else if (this->accion == 3) {
			tmp=datos->assets.getSpriteById(8);
			tmp->setPosition(100,70);
			renderJugador.draw(this->imgSostener);
			renderJugador.draw(*tmp);
		}
		else if (this->accion == 4) {
			tmp = datos->assets.getSpriteById(9);
			tmp->setPosition(100, 70);
			renderJugador.draw(this->imgSostener);
			renderJugador.draw(*tmp);
		}
		else if (this->accion == 5) {
			renderJugador.draw(this->imgSostener);
			renderJugador.draw(this->imgArco);
		}
		renderJugador.draw(imgJugador);
		//renderJugador.display();
		//dibujar en ventana
		const Texture& textura = renderJugador.getTexture();
		Sprite sprite(textura);
		sprite.setOrigin(40, 70);
		sprite.setPosition(this->px, this->py);
		sprite.setRotation(this->rotacion);
		datos->window.draw(sprite);
	}
	void eliminarFlecha(int i) {
		delete flechas[i];
		for (int j = i+1; j < nFlechas; j++) {
			flechas[j - 1] = flechas[j];
		}
		flechas[nFlechas - 1] = NULL;
		delete flechas[nFlechas - 1];
		nFlechas--;
	}
	void decrementarVida() {
		if (tempDecVida >= maxTiempoDec) {
			tempDecVida = 0;
			this->vida--;
		}
	}
};