#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <cstdio>
#include <sstream>
#include "ListaOrtogonal.h"
#include <vector>
#include <time.h>
#include <cstdlib>
#include <string>
#include <stack>



using namespace sf;
using namespace std;

class Juego
{
	private:
		RenderWindow* pantallaJuego;
	
		Nodo* head;
		Nodo* head2;
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

		string Nivel;

		int partidaG;

		vector<char> repeticion;
		stack<char>pila;

	public:
		Juego(int ancho, int alto, string titu, string nivel);
		void gameloop(string nivel);
		void ejecutar();

		void crearGrid(string nivel);
		void crearGridCopia(string nivel);
		void actualizaMapa(char caracter, float x, float y, Texture* Tmuros, Sprite* Smuro);
		void cargaMapa(Nodo* head);
		void cargaBaseMapa(char caracter, float x, float y, Texture* Tmuros, Sprite* Smuro);

		void MoverArriba(int num);
		void moverAbajo(int num);
		void moverDerecha(int num);
		void moverIzquierda(int num);

		void Guardar();

		void moverRep(int num);
		void borrarRep();
		void verRepeticion();
		vector<char> rep();

		void verPila();

		~Juego();


};
