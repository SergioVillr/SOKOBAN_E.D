#include "Juego.h"
#include "Niveles.h"


Juego::~Juego()
{
}

Juego::Juego(int ancho, int alto, string titu, string nivel)
{
	Nivel = nivel;
	pantallaJuego = new RenderWindow(VideoMode(ancho, alto), titu);

	texturaFondo = new Texture;
	fondoPantalla = new Sprite;
	texturaFondo->loadFromFile("resource/fondoLadrillos.jpg");
	fondoPantalla->setTexture(*texturaFondo);
	fondoPantalla->setScale(((float)pantallaJuego->getSize().x / fondoPantalla->getTexture()->getSize().x), ((float)pantallaJuego->getSize().y / fondoPantalla->getTexture()->getSize().y));

	evento = new Event;

	fuente = new Font();
	fuente->loadFromFile("fonts/PressStart2P-Regular.ttf");


	label1 = new Text();
	label1->setFont(*fuente);
	label1->setFillColor(Color::White);
	label1->setString("JUGANDO...");
	label1->setCharacterSize(40);
	label1->setPosition(300, 100);

	gameloop(nivel);
}

void Juego::gameloop(string nivel)
{
	if (nivel == '6')
	{
		borrarRep();
		crearGrid(nivel);
		crearGridCopia(nivel);
		while (pantallaJuego->isOpen())
		{
			ejecutar();
		}
	}
	else
	{
		borrarRep();
		crearGrid(nivel);
		crearGridCopia(nivel);
		while (pantallaJuego->isOpen())
		{
			ejecutar();
		}
	}
}


void Juego::ejecutar()
{
	while (pantallaJuego->pollEvent(*evento) && pila.size()!=2)
	{
		if (evento->type == Event::Closed)
		{
			pantallaJuego->close();
			exit(1);
		}
		if(evento->type == Event::KeyReleased)
		{
			if (evento->key.code == Keyboard::Escape)
			{
				Niveles* atras;
				pantallaJuego->close();
				atras = new Niveles(960, 540, "SOKOBAN");
			}
			if (evento->key.code == Keyboard::W || evento->key.code == Keyboard::Up)
			{
				int num = evento->key.code;
				MoverArriba(num);
			}
			if (evento->key.code == Keyboard::D || evento->key.code == Keyboard::Right)
			{
				int num = evento->key.code;
				moverDerecha(num);
			}
			if (evento->key.code == Keyboard::S || evento->key.code == Keyboard::Down)
			{
				int num = evento->key.code;
				moverAbajo(num);
			}
			if (evento->key.code == Keyboard::A || evento->key.code == Keyboard::Left)
			{
				int num = evento->key.code;
				moverIzquierda(num);
			}
			if (evento->key.code == Keyboard::R)
			{
				verRepeticion();
			}
			if (evento->key.code == Keyboard::G)
			{
				Guardar();
			}
			if (evento->key.code == Keyboard::BackSpace) {
				pantallaJuego->close();
				Juego* game = new Juego(1280, 720, "SOKOBAN", Nivel);
			}
			if(evento->key.code == Keyboard::Space) {
				pantallaJuego->close();
				int nu = atoi(Nivel.c_str());
				nu = nu + 1;
				Nivel = to_string(nu);
				Juego* game = new Juego(1280, 720, "SOKOBAN", Nivel);
			}
		}
	}
	if (pila.size() == 2) {
		while (pantallaJuego->pollEvent(*evento) && pila.size()==2)
		{
			if (evento->type == Event::Closed)
			{
				pantallaJuego->close();
				exit(1);
			}
			if (evento->type == Event::KeyReleased)
			{
				if (evento->key.code == Keyboard::Escape)
				{
					Niveles* atras;
					pantallaJuego->close();
					atras = new Niveles(960, 540, "SOKOBAN");
				}
				if (evento->key.code == Keyboard::R)
				{
					verRepeticion();
				}
				if (evento->key.code == Keyboard::G)
				{
					Guardar();
				}
				if (evento->key.code == Keyboard::BackSpace) {
					pantallaJuego->close();
					Juego* game = new Juego(1280, 720, "SOKOBAN", Nivel);
				}
				if (evento->key.code == Keyboard::Space) {
					pantallaJuego->close();
					int nu = atoi(Nivel.c_str());
					nu = nu + 1;
					Nivel = to_string(nu);
					Juego* game = new Juego(1280, 720, "SOKOBAN", Nivel);
				}
			}
		}
	}

}

void Juego::crearGrid(string nivel)
{
	pantallaJuego->draw(*fondoPantalla);
	if (nivel == '6')
	{
		obj = new ListaOrtogonal();
		obj->cargarNivelGuardado();
		obj->cargarLista(9, 9, head);
		cargaMapa(head);
	}
	else
	{
		obj = new ListaOrtogonal();
		obj->cargarNivel(nivel);
		obj->cargarLista(9, 9, head);
		cargaMapa(head);
	}

	pantallaJuego->display();
}

void Juego::actualizaMapa(char caracter, float x, float y, Texture* Tmuros, Sprite* Smuro) {
	
	//$ cajas
	if (caracter == '$') {
		IntRect posicion(128, 256, 128, 128);
		Smuro->setTextureRect(posicion);
	}

	//@ personaje
	if (caracter == '@') {
		IntRect posicion(0, 640, 128, 128);
		Smuro->setTextureRect(posicion);
	}
	if (caracter == 'X') {
		IntRect posicion(0, 640, 128, 128);
		Smuro->setTextureRect(posicion);
	}

	Smuro->setPosition(x, y);
	pantallaJuego->draw(*Smuro);
}

void Juego::cargaBaseMapa(char caracter, float x, float y, Texture* Tmuros, Sprite* Smuro) {

	IntRect posicion(1408, 768, 128, 128);
	Smuro->setTextureRect(posicion);
	Smuro->setPosition(x, y);
	pantallaJuego->draw(*Smuro);

	//# paredes
	if (caracter == '#') {
		IntRect posicion(1152, 768, 128, 128);
		Smuro->setTextureRect(posicion);
	}
	//. metas
	if (caracter == '.') {
		IntRect posicion(1408, 896, 128, 128);
		Smuro->setTextureRect(posicion);
	}
	if (caracter == 'M') {
		IntRect posicion(512, 256, 128, 128);
		Smuro->setTextureRect(posicion);
	}
	Smuro->setPosition(x, y);
	pantallaJuego->draw(*Smuro);
}

void Juego::cargaMapa(Nodo* head) {

	texturaFondo->loadFromFile("resource/fondoLadrillos.jpg");
	fondoPantalla->setTexture(*texturaFondo);
	fondoPantalla->setScale(((float)pantallaJuego->getSize().x / fondoPantalla->getTexture()->getSize().x), ((float)pantallaJuego->getSize().y / fondoPantalla->getTexture()->getSize().y));
	pantallaJuego->draw(*fondoPantalla);

	Tmuros = new Texture();
	Smuro = new Sprite;

	Tmuros->loadFromFile("resource/1.png");
	Smuro->setTexture(*Tmuros);
	Smuro->setScale(800.f / Smuro->getTexture()->getSize().x, 400.f / Smuro->getTexture()->getSize().y);

	Nodo* aux1 = NULL, * aux2 = NULL, * aux3 = NULL ;

	float x = 200;
	float y = 50;
	if (head != NULL)
	{
		aux1 = head;
		while (aux1 != NULL)
		{
			aux2 = aux1;
			while (aux2 != NULL)
			{
				cargaBaseMapa(aux2->getDato(), x, y, Tmuros, Smuro);
				actualizaMapa(aux2->getDato(), x, y, Tmuros, Smuro);
				
				aux2 = aux2->getSig();
				x = x + 62;
			}
			x = 200;
			aux1 = aux1->getAbajo();
			y = y + 50;
		}
	}
}

void Juego::MoverArriba(int num)
{

	Nodo* p = NULL, * q = NULL,*actual = NULL, *arriba = NULL;
	if (head != NULL)
	{
		p = head;
		while (p != NULL)
		{
			q = p;
			while (q != NULL)
			{
				if (q->getDato() == '@')
				{
					actual = q;
				}
				if (q->getDato() == 'X')
				{
					actual = q;
				}
				q = q->getSig();
			}
			p = p->getAbajo();
		}
	}
	else
		cout << "Lista vacia...";

	arriba = actual->getArriba();

	//=============ARRIBA CON CAJA====================//
	if (actual->getDato() == 'X' && arriba->getDato() == '$' && (arriba->getArriba()->getDato() == '0' || arriba->getArriba()->getDato() == '.')) {    //Si personaje tiene arriba caja y hay espacio...
		arriba->setDato('@');
		arriba->getArriba()->setDato('$');
		actual->setDato('.');
		repeticion.push_back(num);
	}
	else if (arriba->getDato() == '$' && arriba->getArriba()->getDato() == '0') {    //Si personaje tiene arriba caja y hay espacio...
		arriba->setDato('@');
		arriba->getArriba()->setDato('$');
		actual->setDato('0');
		repeticion.push_back(num);
	}
	else if (arriba->getDato() == '$' && arriba->getArriba()->getDato() == '.') {    //Si personaje tiene arriba caja y siguiente es meta...
		arriba->setDato('@');
		arriba->getArriba()->setDato('M');
		actual->setDato('0');
		repeticion.push_back(num);
		pila.push('M');
	}
	else if (arriba->getDato() == 'M' && arriba->getArriba()->getDato() == '0') {    //Si personaje tiene arriba caja en meta y siguiente es vacío...
		arriba->setDato('X');
		arriba->getArriba()->setDato('$');
		actual->setDato('0');
		repeticion.push_back(num);
		pila.pop();
	}
	//=============ARRIBA SIN CAJA====================//
	else if (actual->getDato() == 'X' && arriba->getDato() != '#') {//Si personaje está en meta pero arriba hay muro no suba...
		arriba->setDato('@');
		actual->setDato('.');
		repeticion.push_back(num);
	}
	else if (arriba->getDato() == '0') {			//Si arriba de personaje es vacío
		arriba->setDato(actual->getDato());
		actual->setDato('0');
		repeticion.push_back(num);
	}
	else if (arriba->getDato() == '.') {    //Si arriba de personaje hay meta setea X para saber que está sobre...
		arriba->setDato('X');
		actual->setDato('0');
		repeticion.push_back(num);
	}

	cargaMapa(head);
	pantallaJuego->display();
}

void Juego::moverDerecha(int num)
{

	Nodo* p = NULL, * q = NULL, * actual = NULL, * derecha = NULL;
	if (head != NULL)
	{
		p = head;
		while (p != NULL)
		{
			q = p;
			while (q != NULL)
			{
				if (q->getDato() == '@')
				{
					actual = q;
				}
				if (q->getDato() == 'X')
				{
					actual = q;
				}
				q = q->getSig();
			}
			p = p->getAbajo();
		}
	}
	else
		cout << "Lista vacia...";

	derecha = actual->getSig();

	//=============ARRIBA CON CAJA====================//
	if (derecha->getDato() == '$' && derecha->getSig()->getDato() == '0' && actual->getDato() == 'X') {    //Si personaje tiene arriba caja y hay espacio...
		derecha->setDato('@');
		derecha->getSig()->setDato('$');
		actual->setDato('.');
		repeticion.push_back(num);
	}
	else if (derecha->getDato() == '$' && derecha->getSig()->getDato() == '0') {    //Si personaje tiene arriba caja y hay espacio...
		derecha->setDato('@');
		derecha->getSig()->setDato('$');
		actual->setDato('0');
		repeticion.push_back(num);
	}
	else if (derecha->getDato() == '$' && derecha->getSig()->getDato() == '.') {    //Si personaje tiene arriba caja y siguiente es meta...
		derecha->setDato('@');
		derecha->getSig()->setDato('M');
		actual->setDato('0');
		repeticion.push_back(num);
		pila.push('M');
	}
	else if (derecha->getDato() == 'M' && derecha->getSig()->getDato() == '0') {    //Si personaje tiene arriba caja y siguiente es meta...
		derecha->setDato('X');
		derecha->getSig()->setDato('$');
		actual->setDato('0');
		repeticion.push_back(num);
		pila.pop();
	}
	//=============ARRIBA SIN CAJA====================//
	else if (actual->getDato() == 'X' && derecha->getDato() != '#') {//Si personaje está en meta pero arriba hay muro no suba...
		derecha->setDato('@');
		actual->setDato('.');
		repeticion.push_back(num);
	}
	else if (derecha->getDato() == '0') {			//Si arriba de personaje es vacío
		derecha->setDato(actual->getDato());
		actual->setDato('0');
		repeticion.push_back(num);
	}
	else if (derecha->getDato() == '.') {    //Si arriba de personaje hay meta setea X para saber que está sobre...
		derecha->setDato('X');
		actual->setDato('0');
		repeticion.push_back(num);
	}


	cargaMapa(head);
	pantallaJuego->display();
}

void Juego::moverIzquierda(int num)
{

	Nodo* p = NULL, * q = NULL, * actual = NULL, * izquierda = NULL;
	if (head != NULL)
	{
		p = head;
		while (p != NULL)
		{
			q = p;
			while (q != NULL)
			{
				if (q->getDato() == '@')
				{
					actual = q;
				}
				if (q->getDato() == 'X')
				{
					actual = q;
				}
				q = q->getSig();
			}
			p = p->getAbajo();
		}
	}
	else
		cout << "Lista vacia...";

	izquierda = actual->getAnt();

	//=============IZQUIERDA CON CAJA====================//
	if (izquierda->getDato() == '$' && izquierda->getAnt()->getDato() == '0' && actual->getDato() == 'X') {    //Si personaje tiene IZQUIERDA caja y hay espacio...
		izquierda->setDato('@');
		izquierda->getAnt()->setDato('$');
		actual->setDato('.');
		repeticion.push_back(num);
	}
	else if (izquierda->getDato() == '$' && izquierda->getAnt()->getDato() == '0') {    //Si personaje tiene IZQUIERDA caja y hay espacio...
		izquierda->setDato('@');
		izquierda->getAnt()->setDato('$');
		actual->setDato('0');
		repeticion.push_back(num);
	}
	else if (izquierda->getDato() == '$' && izquierda->getAnt()->getDato() == '.') {    //Si personaje tiene IZQUIERDA caja y siguiente es meta...
		izquierda->setDato('@');
		izquierda->getAnt()->setDato('M');
		actual->setDato('0');
		repeticion.push_back(num);
		pila.push('M');
	}
	else if (izquierda->getDato() == 'M' && izquierda->getAnt()->getDato() == '0') {    //Si personaje tiene IZQUIERDA caja y siguiente es meta...
		izquierda->setDato('X');
		izquierda->getAnt()->setDato('$');
		actual->setDato('0');
		repeticion.push_back(num);
		pila.pop();
	}
	//=============IZQUIERDA SIN CAJA====================//
	else if (actual->getDato() == 'X' && izquierda->getDato() != '#') {//Si personaje está en meta pero IZQUIERDA hay muro no avence...
		izquierda->setDato('@');
		actual->setDato('.');
		repeticion.push_back(num);
	}
	else if (izquierda->getDato() == '0') {			//Si IZQUIERDA de personaje es vacío
		izquierda->setDato(actual->getDato());
		actual->setDato('0');
		repeticion.push_back(num);
	}
	else if (izquierda->getDato() == '.') {    //Si IZQUIERDA de personaje hay meta setea X para saber que está sobre...
		izquierda->setDato('X');
		actual->setDato('0');
		repeticion.push_back(num);
	}

	cargaMapa(head);
	pantallaJuego->display();
}



void Juego::moverAbajo(int num)
{

	Nodo* p = NULL, * q = NULL, * actual = NULL, * Abajo = NULL;
	if (head != NULL)
	{
		p = head;
		while (p != NULL)
		{
			q = p;
			while (q != NULL)
			{
				if (q->getDato() == '@')
				{
					actual = q;
				}
				if (q->getDato() == 'X')
				{
					actual = q;
				}
				q = q->getSig();
			}
			p = p->getAbajo();
		}
	}
	else
		cout << "Lista vacia...";

	Abajo = actual->getAbajo();

	//=============ARRIBA CON CAJA====================//
	if (Abajo->getDato() == '$' && Abajo->getAbajo()->getDato() == '0' && actual->getDato() == 'X') {    //Si personaje tiene Abajo caja y hay espacio...
		Abajo->setDato('@');
		Abajo->getAbajo()->setDato('$');
		actual->setDato('.');
		repeticion.push_back(num);
	}
	else if (Abajo->getDato() == '$' && Abajo->getAbajo()->getDato() == '0') {    //Si personaje tiene Abajo caja y hay espacio...
		Abajo->setDato('@');
		Abajo->getAbajo()->setDato('$');
		actual->setDato('0');
		repeticion.push_back(num);
	}
	else if (Abajo->getDato() == '$' && Abajo->getAbajo()->getDato() == '.') {    //Si personaje tiene Abajo caja y siguiente es meta...
		Abajo->setDato('@');
		Abajo->getAbajo()->setDato('M');
		actual->setDato('0');
		repeticion.push_back(num);
		pila.push('M');
	}
	else if (Abajo->getDato() == 'M' && Abajo->getAbajo()->getDato() == '0') {    //Si personaje tiene Abajo caja y siguiente es meta...
		Abajo->setDato('X');
		Abajo->getAbajo()->setDato('$');
		actual->setDato('0');
		repeticion.push_back(num);
		pila.pop();
	}
	//=============ARRIBA SIN CAJA====================//
	else if (actual->getDato() == 'X' && Abajo->getDato() != '#') {//Si Abajo está en meta pero arriba hay muro no suba...
		Abajo->setDato('@');
		actual->setDato('.');
		repeticion.push_back(num);
	}
	else if (Abajo->getDato() == '0') {            //Si Abajo de personaje es vacío
		Abajo->setDato(actual->getDato());
		actual->setDato('0');
		repeticion.push_back(num);
	}
	else if (Abajo->getDato() == '.') {    //Si Abajo de personaje hay meta setea X para saber que está sobre...
		Abajo->setDato('X');
		actual->setDato('0');
		repeticion.push_back(num);
	}

	cargaMapa(head);
	pantallaJuego->display();
}

void Juego::moverRep(int num)
{
	if (num == 22 || num == 73)
	{
		Nodo* p = NULL, * q = NULL, * actual = NULL, * arriba = NULL;
		if (head2 != NULL)
		{
			p = head2;
			while (p != NULL)
			{
				q = p;
				while (q != NULL)
				{
					if (q->getDato() == '@')
					{
						actual = q;
					}
					if (q->getDato() == 'X')
					{
						actual = q;
					}
					q = q->getSig();
				}
				p = p->getAbajo();
			}
		}
		else
			cout << "Lista vacia...";

		arriba = actual->getArriba();

		//=============ARRIBA CON CAJA====================//
		if (arriba->getDato() == '$' && arriba->getArriba()->getDato() == '0' && actual->getDato() == 'X') {    //Si personaje tiene arriba caja y hay espacio...
			arriba->setDato('@');
			arriba->getArriba()->setDato('$');
			actual->setDato('.');
		}
		else if (arriba->getDato() == '$' && arriba->getArriba()->getDato() == '0') {    //Si personaje tiene arriba caja y hay espacio...
			arriba->setDato('@');
			arriba->getArriba()->setDato('$');
			actual->setDato('0');
		}
		else if (arriba->getDato() == '$' && arriba->getArriba()->getDato() == '.') {    //Si personaje tiene arriba caja y siguiente es meta...
			arriba->setDato('@');
			arriba->getArriba()->setDato('M');
			actual->setDato('0');
		}
		else if (arriba->getDato() == 'M' && arriba->getArriba()->getDato() == '0') {    //Si personaje tiene arriba caja y siguiente es meta...
			arriba->setDato('X');
			arriba->getArriba()->setDato('$');
			actual->setDato('0');
		}
		//=============ARRIBA SIN CAJA====================//
		else if (actual->getDato() == 'X' && arriba->getDato() != '#') {//Si personaje está en meta pero arriba hay muro no suba...
			arriba->setDato('@');
			actual->setDato('.');
		}
		else if (arriba->getDato() == '0') {			//Si arriba de personaje es vacío
			arriba->setDato(actual->getDato());
			actual->setDato('0');
		}
		else if (arriba->getDato() == '.') {    //Si arriba de personaje hay meta setea X para saber que está sobre...
			arriba->setDato('X');
			actual->setDato('0');
		}

		cargaMapa(head2);
		pantallaJuego->display();
	}
	else if(num == 3 || num == 72)
	{

		Nodo* p = NULL, * q = NULL, * actual = NULL, * derecha = NULL;
		if (head2 != NULL)
		{
			p = head2;
			while (p != NULL)
			{
				q = p;
				while (q != NULL)
				{
					if (q->getDato() == '@')
					{
						actual = q;
					}
					if (q->getDato() == 'X')
					{
						actual = q;
					}
					q = q->getSig();
				}
				p = p->getAbajo();
			}
		}
		else
			cout << "Lista vacia...";

		derecha = actual->getSig();

		//=============ARRIBA CON CAJA====================//
		if (derecha->getDato() == '$' && derecha->getSig()->getDato() == '0' && actual->getDato() == 'X') {    //Si personaje tiene arriba caja y hay espacio...
			derecha->setDato('@');
			derecha->getSig()->setDato('$');
			actual->setDato('.');
		}
		else if (derecha->getDato() == '$' && derecha->getSig()->getDato() == '0') {    //Si personaje tiene arriba caja y hay espacio...
			derecha->setDato('@');
			derecha->getSig()->setDato('$');
			actual->setDato('0');
		}
		else if (derecha->getDato() == '$' && derecha->getSig()->getDato() == '.') {    //Si personaje tiene arriba caja y siguiente es meta...
			derecha->setDato('@');
			derecha->getSig()->setDato('M');
			actual->setDato('0');
		}
		else if (derecha->getDato() == 'M' && derecha->getSig()->getDato() == '0') {    //Si personaje tiene arriba caja y siguiente es meta...
			derecha->setDato('X');
			derecha->getSig()->setDato('$');
			actual->setDato('0');
		}
		//=============ARRIBA SIN CAJA====================//
		else if (actual->getDato() == 'X' && derecha->getDato() != '#') {//Si personaje está en meta pero arriba hay muro no suba...
			derecha->setDato('@');
			actual->setDato('.');
		}
		else if (derecha->getDato() == '0') {			//Si arriba de personaje es vacío
			derecha->setDato(actual->getDato());
			actual->setDato('0');
		}
		else if (derecha->getDato() == '.') {    //Si arriba de personaje hay meta setea X para saber que está sobre...
			derecha->setDato('X');
			actual->setDato('0');
		}

		cargaMapa(head2);
		pantallaJuego->display();
	}
	else if(num == 0 || num == 71)
	{
		

		Nodo* p = NULL, * q = NULL, * actual = NULL, * izquierda = NULL;
		if (head2 != NULL)
		{
			p = head2;
			while (p != NULL)
			{
				q = p;
				while (q != NULL)
				{
					if (q->getDato() == '@')
					{
						actual = q;
					}
					if (q->getDato() == 'X')
					{
						actual = q;
					}
					q = q->getSig();
				}
				p = p->getAbajo();
			}
		}
		else
			cout << "Lista vacia...";

		izquierda = actual->getAnt();

		//=============IZQUIERDA CON CAJA====================//
		if (izquierda->getDato() == '$' && izquierda->getAnt()->getDato() == '0' && actual->getDato() == 'X') {    //Si personaje tiene IZQUIERDA caja y hay espacio...
			izquierda->setDato('@');
			izquierda->getAnt()->setDato('$');
			actual->setDato('.');
		}
		else if (izquierda->getDato() == '$' && izquierda->getAnt()->getDato() == '0') {    //Si personaje tiene IZQUIERDA caja y hay espacio...
			izquierda->setDato('@');
			izquierda->getAnt()->setDato('$');
			actual->setDato('0');
		}
		else if (izquierda->getDato() == '$' && izquierda->getAnt()->getDato() == '.') {    //Si personaje tiene IZQUIERDA caja y siguiente es meta...
			izquierda->setDato('@');
			izquierda->getAnt()->setDato('M');
			actual->setDato('0');
		}
		else if (izquierda->getDato() == 'M' && izquierda->getAnt()->getDato() == '0') {    //Si personaje tiene IZQUIERDA caja y siguiente es meta...
			izquierda->setDato('X');
			izquierda->getAnt()->setDato('$');
			actual->setDato('0');
		}
		//=============IZQUIERDA SIN CAJA====================//
		else if (actual->getDato() == 'X' && izquierda->getDato() != '#') {//Si personaje está en meta pero IZQUIERDA hay muro no avence...
			izquierda->setDato('@');
			actual->setDato('.');
		}
		else if (izquierda->getDato() == '0') {			//Si IZQUIERDA de personaje es vacío
			izquierda->setDato(actual->getDato());
			actual->setDato('0');
		}
		else if (izquierda->getDato() == '.') {    //Si IZQUIERDA de personaje hay meta setea X para saber que está sobre...
			izquierda->setDato('X');
			actual->setDato('0');
		}

		cargaMapa(head2);
		pantallaJuego->display();

	}
	else if(num == 18 || num == 74)
	{

		Nodo* p = NULL, * q = NULL, * actual = NULL, * Abajo = NULL;
		if (head2 != NULL)
		{
			p = head2;
			while (p != NULL)
			{
				q = p;
				while (q != NULL)
				{
					if (q->getDato() == '@')
					{
						actual = q;
					}
					if (q->getDato() == 'X')
					{
						actual = q;
					}
					q = q->getSig();
				}
				p = p->getAbajo();
			}
		}
		else
			cout << "Lista vacia...";

		Abajo = actual->getAbajo();

		//=============ARRIBA CON CAJA====================//
		if (Abajo->getDato() == '$' && Abajo->getAbajo()->getDato() == '0' && actual->getDato() == 'X') {    //Si personaje tiene Abajo caja y hay espacio...
			Abajo->setDato('@');
			Abajo->getAbajo()->setDato('$');
			actual->setDato('.');
		}
		else if (Abajo->getDato() == '$' && Abajo->getAbajo()->getDato() == '0') {    //Si personaje tiene Abajo caja y hay espacio...
			Abajo->setDato('@');
			Abajo->getAbajo()->setDato('$');
			actual->setDato('0');
		}
		else if (Abajo->getDato() == '$' && Abajo->getAbajo()->getDato() == '.') {    //Si personaje tiene Abajo caja y siguiente es meta...
			Abajo->setDato('@');
			Abajo->getAbajo()->setDato('M');
			actual->setDato('0');
		}
		else if (Abajo->getDato() == 'M' && Abajo->getAbajo()->getDato() == '0') {    //Si personaje tiene Abajo caja y siguiente es meta...
			Abajo->setDato('X');
			Abajo->getAbajo()->setDato('$');
			actual->setDato('0');
		}
		//=============ARRIBA SIN CAJA====================//
		else if (actual->getDato() == 'X' && Abajo->getDato() != '#') {//Si Abajo está en meta pero arriba hay muro no suba...
			Abajo->setDato('@');
			actual->setDato('.');
		}
		else if (Abajo->getDato() == '0') {            //Si Abajo de personaje es vacío
			Abajo->setDato(actual->getDato());
			actual->setDato('0');
		}
		else if (Abajo->getDato() == '.') {    //Si Abajo de personaje hay meta setea X para saber que está sobre...
			Abajo->setDato('X');
			actual->setDato('0');
		}

		cargaMapa(head2);
		pantallaJuego->display();
	}
}

void Juego::Guardar()
{
	ofstream archivo;
	char l;
	archivo.open("Guardar/Guardar.txt", ios::out);

	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo";
		exit(1);
	}
	Nodo* p = NULL, * q = NULL, * actual = NULL, * izquierda = NULL;
	if (head != NULL)
	{
		p = head;
		while (p != NULL)
		{
			q = p;
			while (q != NULL)
			{
				if (q->getDato() != NULL)
				{
					actual = q;
					l = actual->getDato();
					archivo << l;
				}
				q = q->getSig();
			}
			archivo << endl;
			p = p->getAbajo();
		}
		archivo.close();
	}
	else
		cout << "Lista vacia...";



}

void Juego::crearGridCopia(string nivel)
{
	pantallaJuego->draw(*fondoPantalla);

	obj = new ListaOrtogonal();
	obj->cargarNivel(nivel);
	obj->cargarLista(9, 9, head2);
	cargaMapa(head2);
}

void Juego::verRepeticion()
{
	pantallaJuego->clear();
	Time delay = milliseconds(1);
	cargaMapa(head2);
	pantallaJuego->display();
	for (int i : rep()) {
		sleep(delay);
		moverRep(i);
	}
}

void Juego::borrarRep() {
	repeticion.clear();
}

vector<char> Juego::rep()
{
	return repeticion;
}

void Juego::verPila() {
	cout << pila.size();
	
}