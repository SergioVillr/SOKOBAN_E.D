#include "Opciones.h"
#include "Menu.h"


Opciones::~Opciones()
{

}

Opciones::Opciones(int ancho, int alto, string titu)
{
	vectorBotones = new Text[maximo];
	menuOpciones = new RenderWindow(VideoMode(ancho, alto),titu);
	texturaFondo = new Texture;
	basePantalla = new Sprite;

	texturaFondo->loadFromFile("resource/fondoOpciones.jpg");
	basePantalla->setTexture(*texturaFondo);
	basePantalla->setScale(((float)menuOpciones->getSize().x / basePantalla->getTexture()->getSize().x), ((float)menuOpciones->getSize().y / basePantalla->getTexture()->getSize().y));


	fuente = new Font();
	fuente->loadFromFile("fonts/PressStart2P-Regular.ttf");

	label = new Text();
	label->setFont(*fuente);
	label->setFillColor(Color(143,150,31));
	label->setString("OPCIONES");
	label->setCharacterSize(50);
	label->setPosition(300, 50);

	MenuSeleccionado = 0;

	//Boton guardar
	vectorBotones[0].setFont(*fuente);
	vectorBotones[0].setString("Guardar");
	vectorBotones[0].setFillColor(Color(celeste));
	vectorBotones[0].setPosition(350, 200);
	vectorBotones[0].setCharacterSize(40);

	//Boton cargar
	vectorBotones[1].setFont(*fuente);
	vectorBotones[1].setString("Cargar");
	vectorBotones[1].setFillColor(Color::White);
	vectorBotones[1].setPosition(350,270);
	vectorBotones[1].setCharacterSize(40);

	//Boton sonidos
	vectorBotones[2].setFont(*fuente);
	vectorBotones[2].setString("Sonidos");
	vectorBotones[2].setFillColor(Color::White);
	vectorBotones[2].setPosition(350, 340);
	vectorBotones[2].setCharacterSize(40);

	evento = new Event;
	gameloop();
}

void Opciones::gameloop()
{
	while (menuOpciones->isOpen())
	{
		ejecutar();
		dibujar();
	}
}

void Opciones::dibujar()
{
	menuOpciones->clear();
	menuOpciones->draw(*basePantalla);
	menuOpciones->draw(*label);
	for (int i = 0; i < maximo; i++)
	{
		menuOpciones->draw(vectorBotones[i]);
	}
	menuOpciones->display();
}

void Opciones::ejecutar()
{
	while (menuOpciones->pollEvent(*evento))
	{
		if (evento->type == Event::Closed)
		{
			menuOpciones->close();
			exit(1);
		}

		if (evento->key.code == Keyboard::Escape)// tecla presionada fue la tecla "ENTER"
		{
			Menu* devolver;
			menuOpciones->close();
			devolver = new Menu(960, 540, "SOKOBAN");
		}

		if (evento->type == Event::Closed)
		{
			menuOpciones->close();
			exit(1);
		}
		if (evento->type == Event::KeyReleased)
		{
			if (evento->key.code == Keyboard::Up)
			{
				moverArriba();
				break;
			}
			if (evento->key.code == Keyboard::Down)
			{
				moverAbajo();
				break;
			}
			if (evento->key.code == Keyboard::Return)// tecla presionada fue la tecla "ENTER"
			{
				int x = MenuPressed();
				if (x == 0)//guardar
				{
				
					
				}
				if (x == 1)//cargar
				{
					
				}
				if (x == 2)//sondio
				{

				}
			}
		}

	}
}

//metodos para moverse entre las opciones con las teclas de arriba y abajo del teclado
void Opciones::moverArriba()
{
	if (MenuSeleccionado - 1 >= 0)
	{
		vectorBotones[MenuSeleccionado].setFillColor(Color::White);
		MenuSeleccionado--;
		vectorBotones[MenuSeleccionado].setFillColor(Color(celeste));
	}
	else
	{
		if (MenuSeleccionado == 0)
		{
			vectorBotones[MenuSeleccionado].setFillColor(Color::White);
			MenuSeleccionado = 2;
		}
		vectorBotones[MenuSeleccionado].setFillColor(Color(celeste));
	}
}

void Opciones::moverAbajo()
{
	if (MenuSeleccionado + 1 <= maximo)
	{
		vectorBotones[MenuSeleccionado].setFillColor(Color::White);
		MenuSeleccionado++;
		if (MenuSeleccionado == maximo)
		{
			MenuSeleccionado = 0;
		}
		vectorBotones[MenuSeleccionado].setFillColor(Color(celeste));
	}
}

