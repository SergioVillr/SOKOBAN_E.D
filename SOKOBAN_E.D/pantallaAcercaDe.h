#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
using namespace sf;
using namespace std;

#define maximo 4//define la dimension del vector contenenedor de los botones del menu de opciones

class pantallaAcercaDe
{
private:
	RenderWindow* pantalla;//ventada que almacena el menu principal de la aplicacion
	Texture* texture;
	Sprite* base;

	Font* fuente;
	Text* label;
	Text* vectorBotones;

	Event* evento;
public:
	pantallaAcercaDe(int ancho, int alto, string titulo);
	void loop();
	void dibuja();
	void eventos();
};