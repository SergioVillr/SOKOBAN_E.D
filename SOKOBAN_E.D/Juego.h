#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "ListaOrtogonal.h"


using namespace sf;
using namespace std;

class Juego
{
	private:
		RenderWindow* pantallaJuego;
	
		Nodo* head;
		ListaOrtogonal* obj;

		Texture* texturaFondo;
		Sprite* fondoPantalla;
		Event* evento;
		Font* fuente;
		Text* label1;

		Texture* Tmuros;
		Sprite* Smuro;

		Texture* Tpiso;
		Sprite* Spiso;

		Texture* Tpersonaje;
		Sprite* Spersonaje;

		int partidaG;

	public:
		Juego(int ancho, int alto, string titu, string nivel);
		Juego(int ancho, int alto, string titu,int Pguardada);
		void gameloop(string nivel);
		void dibujar();
		void ejecutar();

		void crearGrid(string nivel);
		void actualizaMapa(char caracter, float x, float y, Texture* Tmuros, Sprite* Smuro);
		void cargaMapa(Nodo* head);
		void cargaBaseMapa(char caracter, float x, float y, Texture* Tmuros, Sprite* Smuro);

		void MoverArriba();
		void moverAbajo();
		void moverDerecha();
		void moverIzquierda();

		void Guardar();

		~Juego();


};
