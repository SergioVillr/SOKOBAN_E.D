#include "ListaOrtogonal.h"
ListaOrtogonal::ListaOrtogonal() {
	vec = new char[(fil * col)];
}

void ListaOrtogonal::cargarLista(int n, int m, Nodo*& head)
{
	Nodo* p = NULL, * q = NULL, * r = NULL;
	int i, j, k = 0;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
		{
			p = new Nodo();
			p->setDato(vec[k]);
			p->setSig(NULL);
			p->setAbajo(NULL);
			if (j == 1)
			{
				p->setAnt(NULL);
				if (head == NULL) {
					head = p;
				}
				q = p;
			}
			else
			{
				p->setAnt(q);;
				q->setSig(p);
				q = p;
			}
			if (i == 1)
			{
				p->setArriba(NULL);
				q = p;

			}
			else
			{
				p->setArriba(r);
				r->setAbajo(p);
				r = r->getSig();
			}
			k++;
		}
		r = head;
		while (r->getAbajo() != NULL)
			r = r->getAbajo();
	}
}

void ListaOrtogonal::desplegar(Nodo* head)
{
	Nodo* p = NULL, * q = NULL;
	if (head != NULL)
	{
		p = head;
		while (p != NULL)
		{
			q = p;
			while (q != NULL)
			{
				cout << q->getDato() << " ";
				q = q->getSig();
			}
			cout << endl;
			p = p->getAbajo();
		}
	}
	else
		cout << "Lista vacia...";
}

void ListaOrtogonal::cargarNivel(string lvlName)
{
	FILE* archivo;
    char caracter;
    int i = 0;
	string direccion;
	if (lvlName == '6')
	{
		string direccion = "Guardar/Guardar.txt";
		archivo = fopen(direccion.c_str(), "r");
	}
	else
	{
		string direccion = "Mapas/Nivel" + lvlName + ".txt";
		archivo = fopen(direccion.c_str(), "r");
	}

    if (archivo == NULL) {
        printf("\nError de apertura del archivo. \n\n");
    }
    else {
        while (feof(archivo) == 0) {
            caracter = fgetc(archivo);
            if (caracter != EOF)
            {
				if (caracter != '\n') {
					vec[i] = caracter;
					i++;
				}
				else {
					cout << endl;
				}
            }
        }
    }
    cout << "\n";

}

void ListaOrtogonal::cargarVec()
{
	for (int i = 0;i < 16;i++) {
		cout << vec[i];
	}
}

void ListaOrtogonal::cargarNivelGuardado()
{
	FILE* archivo;
	char caracter;
	int i = 0;

	string direccion = "Guardar/Guardar.txt";


	archivo = fopen(direccion.c_str(), "r");

	if (archivo == NULL) {
		printf("\nError de apertura del archivo. \n\n");
	}
	else {
		while (feof(archivo) == 0) {
			caracter = fgetc(archivo);
			if (caracter != EOF)
			{
				if (caracter != '\n') {
					vec[i] = caracter;
					i++;
				}
				else {
					cout << endl;
				}
			}
		}
	}
	cout << "\n";

}
