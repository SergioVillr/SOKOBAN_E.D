
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