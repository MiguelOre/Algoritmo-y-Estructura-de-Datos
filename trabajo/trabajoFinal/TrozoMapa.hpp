#pragma once
#include "Juego.hpp"
#include "PerlinNoise.hpp"
#include "Jugador.hpp"
#include "Enemigo.hpp"
#include "CtrlEnemigos.hpp"
#include "Recurso.hpp"
#include "EscenaBusqueda.hpp"
#include <string>
#include <sstream>
using namespace std;
struct Material {
	int x;
	int y;
	string tipo;

};
struct Portal {
	int x;
	int y;
	int rotacion = 0;
	int radio=70;
	void actualizar(Jugador&jug, DatosJuego* datos) {
		int cx = jug.px - this->x;
		int cy = jug.py - this->y;
		if (cx*cx + cy*cy < (this->radio)*(this->radio)) {
			datos->escenas.agregarEscena(new EscenaBusqueda(datos), false);
		}
		this->rotacion++;

	}
};

class TrozoMapa {
	DatosJuego* datos;
	Material* materiales;
	Recurso* obstaculos;

	int *vecTerreno;
	int *vecObstaculos;
	int nObstaculos;
	int costoRecurso = 4;

	int randMaxAgua;
	int randMaxArena;
	int randMaxTierra;
	int cantArboles;
	int cantManzanos;
	int cantRocas;
	int cantCactus;
public:
	int ancho;
	int alto;
	int x;
	int y;
	Portal portal;
	TrozoMapa(DatosJuego* datos, int x,int y, int randAgua,int randArena, int randTierra, int cantArboles, int cantManzanos, int cantCactus,int cantRocas) {
		this->datos=datos;
		this->x = x;
		this->y = y;
		portal.x = this->x + datos->ancho / 2;
		portal.y = this->y + datos->alto / 2;
		this->cantArboles = cantArboles;
		this->cantManzanos = cantManzanos;
		this->cantRocas = cantRocas;
		this->cantCactus = cantCactus;
		this->randMaxAgua = randAgua;
		this->randMaxArena = randArena+randAgua;
		this->randMaxTierra = randArena+randAgua+randTierra;

		this->ancho= datos->ancho / datos->M_SIZE;
		this->alto = datos->alto / datos->M_SIZE;
		vecObstaculos = new int[ancho*alto];
		vecTerreno = new int[ancho*alto];
		obstaculos = new Recurso[cantArboles+cantManzanos+cantRocas+40];
		materiales = new Material[ancho*alto];
		this->nObstaculos = 0;
		//////
		PerlinNoise color(5);
		float z=0.8;
		float fact=0.15;
		/////
		for (int i = 0; i < ancho*alto; i++) {
			int xx = this->x+(i%ancho)*datos->M_SIZE;
			int yy = this->y+(i/ancho)*datos->M_SIZE;
			int gen = color.noise((i%ancho+(this->x))*fact, (i / ancho+(this->y))*fact,z)*100;
			if (gen < randMaxAgua) {
				materiales[i].tipo = "agua";
				gen = 0;
			}
			else if (gen<randMaxArena) {
				materiales[i].tipo = "arena";
				gen = 1;
			}
			else if(gen<=randMaxTierra){
				materiales[i].tipo = "tierra";
				gen = 2;
			}
			//generarObstaculos(xx,yy,gen);
			materiales[i].x = xx;
			materiales[i].y = yy;
			vecTerreno[i] = gen;
		}

		generarObstaculos();
	}
	void generarObstaculos() {
		int aux = 0;
		bool forzarGen = false;
		for (int i = 0; i < cantArboles; i++) {
			int xx = this->x+(rand() % (this->ancho*datos->M_SIZE));
			int yy = this->y+ (rand() % (this->alto*datos->M_SIZE));
			if (coordEnMapa(xx, yy) == "tierra" || forzarGen) {
				obstaculos[nObstaculos].inic("arbol",xx,yy);
				nObstaculos++;
				if (forzarGen) { forzarGen = false; aux = 0; }
			}
			else {
				if (aux > 5) {forzarGen = true;}
				i--;
				aux++;
			}
		}
		aux = 0;
		forzarGen = false;
		for (int i = 0; i < cantManzanos; i++) {
			int xx = this->x+(rand() % (this->ancho*datos->M_SIZE));
			int yy = this->y+(rand() % (this->alto*datos->M_SIZE));
			if (coordEnMapa(xx, yy) == "tierra" || forzarGen) {
				obstaculos[nObstaculos].inic("manzano", xx, yy);
				nObstaculos++;
				if (forzarGen) { forzarGen = false; aux = 0; }
			}
			else {
				if (aux > 5) {forzarGen = true;}
				i--;
				aux++;
			}
		}
		forzarGen = false;
		aux = 0;
		for (int i = 0; i < cantRocas; i++) {
			int xx = this->x+(rand() % (this->ancho*datos->M_SIZE));
			int yy = this->y+(rand() % (this->alto*datos->M_SIZE));
			string tipoTerreno = coordEnMapa(xx, yy);
			if ( tipoTerreno== "tierra" || tipoTerreno=="arena"|| forzarGen) {
				obstaculos[nObstaculos].inic("roca", xx, yy);
				nObstaculos++;
				if (forzarGen) { forzarGen = false; aux = 0; }
			}
			else {
				if (aux > 3) {forzarGen = true;}
				i--;
				aux++;
			}
		}
		forzarGen = false;
		aux = 0;
		for (int i = 0; i < cantCactus; i++) {
			int xx = this->x + (rand() % (this->ancho*datos->M_SIZE));
			int yy = this->y + (rand() % (this->alto*datos->M_SIZE));
			string tipoTerreno = coordEnMapa(xx, yy);
			if (tipoTerreno == "arena" || forzarGen) {
				obstaculos[nObstaculos].inic("cactus", xx, yy);
				nObstaculos++;
				if (forzarGen) { forzarGen = false; aux = 0; }
			}
			else {
				if (aux > 5) { forzarGen = true; }
				i--;
				aux++;
			}
		}
	}
	///// cada frame
	void pintarTerreno() {
		Sprite* tmp;
		for (int i = 0; i < ancho*alto; i++) {
			
			if (this->materiales[i].tipo == "agua") {
				tmp=datos->assets.getSpriteById(0);
			}
			else if (materiales[i].tipo == "arena") {
				tmp = datos->assets.getSpriteById(1);
			}
			else if(materiales[i].tipo=="tierra"){
				tmp = datos->assets.getSpriteById(2);
			}
			tmp->setPosition(materiales[i].x,materiales[i].y);
			datos->window.draw(*tmp);
		}
		tmp = NULL;
		delete tmp;
		
	}
	void pintarObjetos() {
		Sprite* tmp;
		for (int i = 0; i < nObstaculos; i++) {
			if (this->obstaculos[i].tipo == "arbol") {
				tmp = datos->assets.getSpriteById(3);
			}
			else if (this->obstaculos[i].tipo == "roca") {
				tmp = datos->assets.getSpriteById(4);
			}
			else if (this->obstaculos[i].tipo == "cactus") {
				tmp = datos->assets.getSpriteById(5);
			}
			else if (this->obstaculos[i].tipo == "manzano") {
				tmp = datos->assets.getSpriteById(6);
			}
			else if (this->obstaculos[i].tipo == "bloqueMadera") {
				tmp = datos->assets.getSpriteById(8);//7 :manzana
			}
			else if (this->obstaculos[i].tipo == "bloqueRoca") {
				tmp = datos->assets.getSpriteById(9);
			}
			tmp->setPosition(obstaculos[i].x, obstaculos[i].y);
			datos->window.draw((*tmp));
		}
		tmp = datos->assets.getSpriteById(12);
		tmp->setPosition(this->portal.x,this->portal.y);
		tmp->setRotation(this->portal.rotacion);
		datos->window.draw(*tmp);
		tmp = NULL;
		delete tmp;
	}
	void actualizarColisiones(Jugador&jug,CtrlEnemigos * enemigos) {
		Recurso tmp;
		for (int i = 0; i < nObstaculos; i++) {
			tmp = obstaculos[i];
			float dx=jug.px-(tmp.x);
			float dy =jug.py-(tmp.y);
			float dist = sqrt(dx*dx + dy*dy);
			float area = tmp.radio + 38;
			if (dist < area) {
				float d=area - dist;
				dx = dx / dist;
				dy = dy / dist;
				jug.px += dx*d/2;
				jug.py += dy*d/2;
				//obstaculos[i].x -= dx*(d/2);
				//obstaculos[i].y -= dy*(d/2);
				if (tmp.tipo == "cactus") {
					jug.vx = dx*jug.velocidad*3;
					jug.vy = dy*jug.velocidad*3;
					jug.decrementarVida();
					if (jug.vida <= 0) {
						jug.vida = 0;
						break;
					}
				}
			}
			
			enemigos->colisionObstaculos(tmp,jug);
			
		}
		portal.actualizar(jug,datos);
	}
	void comprobarAreaAtaque(Jugador&jug) {
		if (jug.actuar) {
			if (jug.accion == 1) {
				for (int i = 0; i < nObstaculos; i++) {
					Recurso tmp = obstaculos[i];
					float dx = tmp.x - jug.px;
					float dy = tmp.y - jug.py;
					float dist = sqrt(dx*dx + dy*dy);
					float area = tmp.radio + 38;
					if (dist < (area + jug.areaAtaque)) {
						float rot = atan2(dy, dx) / 3.141516f * 180;
						if (rot >(jug.rotacion - 45) && rot < (jug.rotacion + 45)) {
							if (tmp.tipo == "arbol") { jug.colecMadera++; }
							else if (tmp.tipo == "roca") { jug.colecRoca++; }
							else if (tmp.tipo == "cactus") { jug.colecFruta++; }
							else if (tmp.tipo == "manzano") { jug.colecFruta++; jug.colecMadera++; }
							obstaculos[i].vida--;
						}
					}
					if (tmp.vida <= 0) {
						for (int j = i + 1; j < nObstaculos; j++) {
							obstaculos[j - 1] = obstaculos[j];
						}
						nObstaculos--;
						i--;
					}

				}
			}
			else if (jug.accion == 2) {
				//en jugador.hpp /realizarAccion()
			}
			else if(jug.accion==3 && jug.colecMadera>= costoRecurso){
				int dx=cos(jug.rotacion/180.0f*3.141516)*60;
				int dy=sin(jug.rotacion/180.0f*3.141516)*60;
				obstaculos[nObstaculos].inic("bloqueMadera", jug.px+dx, jug.py+dy);
				jug.colecMadera -= obstaculos[nObstaculos].costo;
				nObstaculos++;
				if(jug.colecMadera <costoRecurso){
					jug.accion = 1;
				}
			}
			else if (jug.accion == 4 && jug.colecRoca>= costoRecurso) {
				int dx = cos(jug.rotacion / 180.0f*3.141516) * 60;
				int dy = sin(jug.rotacion / 180.0f*3.141516) * 60;
				obstaculos[nObstaculos].inic("bloqueRoca", jug.px + dx, jug.py + dy);
				jug.colecRoca -= obstaculos[nObstaculos].costo;
				nObstaculos++;
				if (jug.colecRoca <costoRecurso) {
					jug.accion = 1;
				}
			}
		
		}

	}
	string coordEnMapa(float px,float py) {
		if ((px-this->x) < 0 || (py-this->y) < 0) {
			return "tierra";
		}
		if ((px - this->x) > (ancho*this->datos->M_SIZE) || (py - this->y) > (alto*this->datos->M_SIZE)) {
			return "tierra";
		}
		int xx = floor((px-this->x) / this->datos->M_SIZE);
		int yy = floor((py-this->y) / this->datos->M_SIZE);
		return this->materiales[yy*ancho + xx].tipo;
	}

	//guardado de datos
	void guardarTerreno(string nombreNodo) {
		stringstream arch;
		arch << "\"" << nombreNodo << "\": ";
		arch << "{\n";
		arch << "\"MatrizTerreno:\": ";
		arch << "\"{";
		for (int i = 0; i < this->ancho*alto;i++) {
			arch<< this->vecTerreno[i]<<",";
		}
		arch << "}\",\n";
		arch << "\"Recursos\": {\n";
		for (int i = 0; i < nObstaculos; i++) {
			arch << "\"recurso"<<i+1<<"\": {\n";
			arch << "\"x\": " << "\"" << obstaculos[i].x << "\",\n";
			arch << "\"y\": " << "\"" << obstaculos[i].y << "\",\n";
			arch << "\"tipo\": " <<"\""<< obstaculos[i].tipo<<"\",\n";
			arch << "\"radio\": " << "\"" << obstaculos[i].radio << "\",\n";
			arch << "},\n";
		}
		arch << "}\n}";
		string tmp = arch.str();
		this->datos->archGuardarNodos << tmp;
		//this->datos->archGuardarNodos.close();
	}
};