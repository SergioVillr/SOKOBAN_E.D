#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#define maximo 3//define la dimension del vector contenenedor de los botones del menu de opciones
#define celeste 63,191,191

using namespace sf;
using namespace std;

class Opciones{

private:

	int MenuSeleccionado;
	RenderWindow* menuOpciones;
	Texture* texturaFondo;
	Sprite* basePantalla;
	Event* evento;
	Font* fuente;
	Text* label;
	Text* vectorBotones;
	
public:
	Opciones(int ancho, int alto, string titu);
	void gameloop();
	void dibujar();
	void ejecutar();
	void moverAbajo();
	void moverArriba();
	~Opciones();

	int MenuPressed()
	{
		return MenuSeleccionado;
	}
};