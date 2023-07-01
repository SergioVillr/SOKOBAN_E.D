#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

using namespace sf;
using namespace std;

class Nodo
{
protected:
	char dato;
	Nodo* siguiente;
	Nodo* anterior;
	Nodo* arriba;
	Nodo* abajo;
	
public:
	Nodo();
	Nodo(char,Nodo *,Nodo *,Nodo *,Nodo *);
	void setDato(char dato);
	void setSig(Nodo* siguiente);
	void setAnt(Nodo* anterior);
	void setArriba(Nodo* arriba);
	void setAbajo(Nodo* abajo);
	char getDato();
	Nodo* getSig();
	Nodo* getAnt();
	Nodo* getArriba();
	Nodo* getAbajo();
};