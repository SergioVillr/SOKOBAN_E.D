#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <cstdio>
#include <sstream>
#include "Nodo.h"

#pragma warning(disable:4996)

using namespace std;
#define fil 9
#define col 9

class ListaOrtogonal
{
private:
	char* vec;
public:
	ListaOrtogonal();
	void cargarLista(int n, int m, Nodo*&);
	void desplegar(Nodo*);
	void cargarNivel(string lvlName);
	void cargarNivelGuardado();
	void cargarVec();

};

