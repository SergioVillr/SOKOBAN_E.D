
#include "Menu.h"
#include "pantallaAcercaDe.h"



pantallaAcercaDe::pantallaAcercaDe(int ancho, int alto, string titulo)
{
	pantalla = new RenderWindow(VideoMode(ancho, alto), titulo);//creamos la pantalla del menu principal

	texture = new Texture;// se crea la textura
	base = new Sprite;// se crea la base de la pantalla
	texture->loadFromFile("resource/fondoMenuPrincipal.jpg");
	base->setTexture(*texture);
	base->setScale(((float)pantalla->getSize().x / base->getTexture()->getSize().x), ((float)pantalla->getSize().y / base->getTexture()->getSize().y));
	evento = new Event;

	fuente = new Font();
	fuente->loadFromFile("fonts/PressStart2P-Regular.ttf");

	vectorBotones = new Text[maximo];

	vectorBotones[0].setFont(*fuente);
	vectorBotones[0].setString("Desarrolladores:");
	vectorBotones[0].setFillColor(Color::White);
	vectorBotones[0].setPosition(150, 125);
	vectorBotones[0].setCharacterSize(30);

	vectorBotones[1].setFont(*fuente);
	vectorBotones[1].setString("Juan Altamirano Granados");
	vectorBotones[1].setFillColor(Color::Magenta);
	vectorBotones[1].setPosition(150, 175);
	vectorBotones[1].setCharacterSize(30);

	//Boton opciones
	vectorBotones[2].setFont(*fuente);
	vectorBotones[2].setString("Damian Cordero Fallas");
	vectorBotones[2].setFillColor(Color::Green);
	vectorBotones[2].setPosition(150, 225);
	vectorBotones[2].setCharacterSize(30);

	//Boton acercade
	vectorBotones[3].setFont(*fuente);
	vectorBotones[3].setString("Sergio Villanueva Rios");
	vectorBotones[3].setFillColor(Color::Yellow);
	vectorBotones[3].setPosition(150, 275);
	vectorBotones[3].setCharacterSize(30);

	loop();
}

void pantallaAcercaDe::loop()
{
	while (pantalla->isOpen())
	{
		eventos();
		dibuja();
	}
}

void pantallaAcercaDe::dibuja()
{
	pantalla->clear();
	pantalla->draw(*base);

	for (int i = 0;i < maximo; i++)
	{
		pantalla->draw(vectorBotones[i]);
	}
	pantalla->display();

}



void pantallaAcercaDe::eventos()
{
	while (pantalla->pollEvent(*evento))
	{
		if (evento->type == Event::Closed)
		{
			pantalla->close();
			exit(1);
		}
		if (evento->type == Event::KeyReleased)
		{
			if (evento->key.code == Keyboard::Escape)// tecla presionada fue la tecla "ENTER"
			{
				Menu* devolver;
				pantalla->close();
				devolver = new Menu(960, 540, "SOKOBAN");
			}
		}

	}
}