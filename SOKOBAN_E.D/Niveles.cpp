#include "Niveles.h"
#include "Menu.h"

Niveles::~Niveles() {

}

Niveles::Niveles(int ancho, int alto, string titu)
{

	buffer.loadFromFile("resource/click.wav");
	click.setBuffer(buffer);

	pantallaNiveles = new RenderWindow(VideoMode(ancho, alto), titu);
	
	textureBackground = new Texture();
	spritePantalla = new Sprite();

	textureBackground->loadFromFile("resource/fondoOpciones.jpg");
	spritePantalla->setTexture(*textureBackground);
	spritePantalla->setScale(((float)pantallaNiveles->getSize().x / spritePantalla->getTexture()->getSize().x), ((float)pantallaNiveles->getSize().y / spritePantalla->getTexture()->getSize().y));

	fuente = new Font();
	fuente->loadFromFile("fonts/PressStart2P-Regular.ttf");

	nivelSeleccionado = 0;

	//Boton nivel 1
	vectorNiveles[0].setFont(*fuente);
	vectorNiveles[0].setString("Nivel 1");
	vectorNiveles[0].setFillColor(Color::Blue);
	vectorNiveles[0].setPosition(300, 100);
	vectorNiveles[0].setCharacterSize(40);

	//Boton nivel 2
	vectorNiveles[1].setFont(*fuente);
	vectorNiveles[1].setString("Nivel 2");
	vectorNiveles[1].setFillColor(Color::White);
	vectorNiveles[1].setPosition(300, 150);
	vectorNiveles[1].setCharacterSize(40);

	//Boton nivel 3
	vectorNiveles[2].setFont(*fuente);
	vectorNiveles[2].setString("Nivel 3");
	vectorNiveles[2].setFillColor(Color::White);
	vectorNiveles[2].setPosition(300, 200);
	vectorNiveles[2].setCharacterSize(40);

	//Boton nivel 4
	vectorNiveles[3].setFont(*fuente);
	vectorNiveles[3].setString("Nivel 4");
	vectorNiveles[3].setFillColor(Color::White);
	vectorNiveles[3].setPosition(300, 250);
	vectorNiveles[3].setCharacterSize(40);

	//Boton nivel 5
	vectorNiveles[4].setFont(*fuente);
	vectorNiveles[4].setString("Nivel 5");
	vectorNiveles[4].setFillColor(Color::White);
	vectorNiveles[4].setPosition(300, 300);
	vectorNiveles[4].setCharacterSize(40);

	evento = new Event;
	gameloopNiveles();
}

void Niveles::gameloopNiveles() {

	while (pantallaNiveles->isOpen()) {
	
		ejecutarBotones();
		dibujarBotones();
	}

}

void Niveles::dibujarBotones() {
	pantallaNiveles->clear();
	pantallaNiveles->draw(*spritePantalla);
	for (int i = 0; i < maximoBotones; i++)
	{
		pantallaNiveles->draw(vectorNiveles[i]);
	}
	pantallaNiveles->display();

}

void Niveles::ejecutarBotones() {
	while (pantallaNiveles->pollEvent(*evento))
	{
		if (evento->type == Event::Closed)
		{
			click.play();
			pantallaNiveles->close();
			exit(1);
		}
		if (evento->type == Event::KeyReleased)
		{
			if (evento->key.code == Keyboard::Escape)
			{
				click.play();
				Menu* atras;
				pantallaNiveles->close();
				atras = new Menu(960, 540, "SOKOBAN");
			}
			if (evento->key.code == Keyboard::Up)
			{
				click.play();
				moveArriba();
				break;
			}
			if (evento->key.code == Keyboard::Down)
			{
				click.play();
				moveAbajo();
				break;
			}
			if (evento->key.code == Keyboard::Return)// tecla presionada fue la tecla "ENTER"
			{
				click.play();
				int x = NivelPressed();
				if (x == 0)//nivel 1
				{
					pantallaNiveles->close();
					game = new Juego(1280, 720, "SOKOBAN","1");
					
				}
				if (x == 1)//nivel 2
				{
					pantallaNiveles->close();
					game = new Juego(1280, 720, "SOKOBAN","2");
					
				}
				if (x == 2)//nivel 3
				{
					pantallaNiveles->close();
					game = new Juego(1280, 720, "SOKOBAN","3");

				}
				if (x == 3)//nivel 4
				{
					pantallaNiveles->close();
					game = new Juego(1280, 720, "SOKOBAN","4");

				}
				if (x == 4)//nivel 5
				{
					pantallaNiveles->close();
					game = new Juego(1280, 720, "SOKOBAN","5");

				}
			}
		}

	}
}

//metodos para moverse entre las opciones con las teclas de arriba y abajo del teclado
void Niveles::moveArriba()
{
	if (nivelSeleccionado - 1 >= 0)
	{
		vectorNiveles[nivelSeleccionado].setFillColor(Color::White);

		nivelSeleccionado--;
		vectorNiveles[nivelSeleccionado].setFillColor(Color::Blue);
	}
	else
	{
		if (nivelSeleccionado == 0)
		{
			vectorNiveles[nivelSeleccionado].setFillColor(Color::White);
			nivelSeleccionado = 4;
		}
		vectorNiveles[nivelSeleccionado].setFillColor(Color::Blue);
	}
}

void Niveles::moveAbajo()
{
	if (nivelSeleccionado + 1 <= maximoBotones)
	{
		vectorNiveles[nivelSeleccionado].setFillColor(Color::White);
		nivelSeleccionado++;
		if (nivelSeleccionado == maximoBotones)
		{
			nivelSeleccionado = 0;
		}
		vectorNiveles[nivelSeleccionado].setFillColor(Color::Blue);
	}
}