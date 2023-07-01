#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
using namespace sf;
using namespace std;

class pantallaAcercaDe
{
private:
	RenderWindow* pantalla;//ventada que almacena el menu principal de la aplicacion
	Texture* texture;
	Sprite* base;
	Event* evento;
public:
	pantallaAcercaDe(int ancho, int alto, string titulo);
	void loop();
	void dibuja();
	void eventos();
};