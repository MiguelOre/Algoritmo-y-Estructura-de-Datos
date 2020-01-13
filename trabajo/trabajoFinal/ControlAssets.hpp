#pragma once
#include <SFML\Graphics.hpp>
#include<SFML/Audio.hpp>
#include <string>
#include <iostream>
using namespace std;
using namespace sf;
class ControlAssets {
	SoundBuffer **buffers;
	Sound ** sonidos;
	Texture **texturas;
	Sprite**sprites;
	Font** fuentes;
	Text** textos;

	int nSonidos;
	int maxSonidos;

	int nSprites;
	int maxSprites;

	int nFuentes;
	int maxFuentes;

	int nTextos;
	int maxTextos;
public:
	ControlAssets() {
		maxSprites = 13;
		texturas = new Texture*[maxSprites];
		sprites = new Sprite*[maxSprites];
		nSprites = 0;

		maxSonidos = 6;
		buffers = new SoundBuffer*[maxSonidos];
		sonidos = new Sound*[maxSonidos];
		nSonidos = 0;

		maxFuentes = 3;
		fuentes = new Font*[maxFuentes];
		nFuentes = 0;

		maxTextos = 4;
		textos = new Text*[maxFuentes];
		nTextos =0 ;
	}
	~ControlAssets() {
		delete[] this->texturas;
	}
	void cargarSprite(string filename,int size=0, bool origen=false) {

		texturas[nSprites] = new Texture();
		texturas[nSprites]->loadFromFile(filename);
	
		sprites[nSprites] = new Sprite();
		sprites[nSprites]->setTexture(*(texturas[nSprites]));
		if (size != 0) {
			this->redimencionarSprite(*(sprites[nSprites]),size,size);
		}
		if (origen) {
			this->definirOrigen(*(sprites[nSprites]),sprites[nSprites]->getGlobalBounds().width/2, sprites[nSprites]->getGlobalBounds().height/2);
		}
		this->nSprites++;

	}
	void cargarSonido(string filename) {
		buffers[nSonidos] = new SoundBuffer();
		buffers[nSonidos]->loadFromFile(filename);
		sonidos[nSonidos] = new Sound();
		sonidos[nSonidos]->setBuffer(*(buffers[nSonidos]));
		nSonidos++;
	}
	void cargarFuente(string filename) {
		fuentes[nFuentes] = new Font();
		fuentes[nFuentes]->loadFromFile(filename);
		nFuentes++;

	}
	void crearTexto(int fuente,int size, Color color) {
		textos[nTextos] = new Text();
		textos[nTextos]->setFont(*(this->fuentes[fuente]));
		textos[nTextos]->setCharacterSize(size);
		nTextos++;
	}
	void confTexto(int i, string texto, int x=-1, int y=-1) {
		if (x != -1) {
			textos[i]->setPosition(x, y);
		}
		textos[i]->setString(texto);
	}
	void dibujarTexto(int i,RenderWindow &win) {
		win.draw(*(textos[i]));
	}
	Text* getTextById(int i) {
		return this->textos[i];
	}
	Font* getFontById(int i) {
		return this->fuentes[i];
	}
	Sound* getSoundById(int i) {
		return this->sonidos[i];
	}
	Sprite* getSpriteById(int i) {
		return this->sprites[i];
	}
	int spritesLength() {
		return this->nSprites;
	}
	//Utilidades sprite

	void redimencionarSprite(Sprite& sprite,int ancho,int alto) {
		sprite.setScale((ancho/sprite.getGlobalBounds().width), (alto/sprite.getGlobalBounds().height));
	}
	void definirOrigen(Sprite& sprite,int x,int y) {
		sprite.setOrigin(x,y);
	}
	void borrarDatos() {

	}
};