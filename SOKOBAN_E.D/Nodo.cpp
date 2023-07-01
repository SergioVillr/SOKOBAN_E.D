#include "Nodo.h"

Nodo::Nodo() {
	this->dato = 0;
	this->siguiente = NULL;
	this->anterior = NULL;
	this->arriba = NULL;
	this->abajo = NULL;
}

Nodo::Nodo(char dato, Nodo* siguiente, Nodo* anterior, Nodo* arriba, Nodo* abajo) {
	this->dato = dato;
	this->siguiente = siguiente;
	this->anterior = anterior;
	this->arriba = arriba;
	this->abajo = abajo;
}


void Nodo::setDato(char dato) {
	this->dato = dato;
}

void Nodo::setSig(Nodo* siguiente){
	this->siguiente = siguiente;
}

void Nodo::setAnt(Nodo* anterior){
	this->anterior = anterior;
}

void Nodo::setArriba(Nodo* arriba){
	this->arriba = arriba;
}

void Nodo::setAbajo(Nodo* abajo){
	this->abajo = abajo;
}

char Nodo::getDato()
{
	return dato;
}

Nodo* Nodo::getSig()
{
	return siguiente;
}

Nodo* Nodo::getAnt()
{
	return anterior;
}

Nodo* Nodo::getArriba()
{
	return arriba;
}

Nodo* Nodo::getAbajo()
{
	return abajo;
}

