#include "Menu.h"
#include "Juego.h"

Menu::~Menu()
{

}

Menu::Menu(int ancho, int alto, string titulo)
{
	fps = 60;
	menuPrincipal = new RenderWindow(VideoMode(ancho, alto), titulo);//creamos la pantalla del menu principal
	menuPrincipal->setFramerateLimit(fps);//se limita los fps a la pantalla

	texturaFondo = new Texture;// se crea la textura
	basePantalla = new Sprite;// se crea la base de la pantalla
	texturaFondo->loadFromFile("resource/fondoMenuPrincipal.jpg");
	basePantalla->setTexture(*texturaFondo);
	basePantalla->setScale(((float)menuPrincipal->getSize().x / basePantalla->getTexture()->getSize().x),((float)menuPrincipal->getSize().y / basePantalla->getTexture()->getSize().y));
	
	fuente = new Font();
	fuente->loadFromFile("fonts/PressStart2P-Regular.ttf");  

	MenuSeleccionado = 0;

	//Boton jugar
	vectorBotones[0].setFont(*fuente);
	vectorBotones[0].setString("Jugar");
	vectorBotones[0].setFillColor(Color::Blue);
	vectorBotones[0].setPosition(300, 100);
	vectorBotones[0].setCharacterSize(40);

	//Boton opciones
	vectorBotones[1].setFont(*fuente);
	vectorBotones[1].setString("Opciones");
	vectorBotones[1].setFillColor(Color::White);
	vectorBotones[1].setPosition(300, 150);
	vectorBotones[1].setCharacterSize(40);

	//Boton acercade
	vectorBotones[2].setFont(*fuente);
	vectorBotones[2].setString("Acerca de");
	vectorBotones[2].setFillColor(Color::White);
	vectorBotones[2].setPosition(300, 200);
	vectorBotones[2].setCharacterSize(40);

	//Boton de cargar partida
	vectorBotones[3].setFont(*fuente);
	vectorBotones[3].setString("Cargar Juego");
	vectorBotones[3].setFillColor(Color::White);
	vectorBotones[3].setPosition(300, 250);
	vectorBotones[3].setCharacterSize(40);

	//Boton de salir
	vectorBotones[4].setFont(*fuente);
	vectorBotones[4].setString("Salir");
	vectorBotones[4].setFillColor(Color::White);
	vectorBotones[4].setPosition(300, 300);
	vectorBotones[4].setCharacterSize(40);

	evento = new Event;
	gameloop();
}

void Menu:: gameloop()
{
	while (menuPrincipal->isOpen())
	{
		ejecutarEventos();
		dibujar();
	}
}

void Menu::dibujar()
{
	menuPrincipal->clear();
	menuPrincipal->draw(*basePantalla);
	for (int i = 0;i < Max_menu; i++)
	{
		menuPrincipal->draw(vectorBotones[i]);
	}
	menuPrincipal->display();
}



void Menu::ejecutarEventos()
{
	while (menuPrincipal->pollEvent(*evento))
	{
		if (evento->type == Event::Closed)
		{
			menuPrincipal->close();
			exit(1);
		}
		if (evento->type == Event::KeyReleased)
		{
			if (evento->key.code == Keyboard::Up)
			{
				MoverArriba();
				break;
			}
			if (evento->key.code == Keyboard::Down)
			{
				Moverabajo();
				break;
			}
			if (evento->key.code == Keyboard::Return)// tecla presionada fue la tecla "ENTER"
			{
				int x = MenuPressed();
				if (x == 0)//ingresa a la pantalla de juego
				{
					menuPrincipal->close();
					niveles = new Niveles(960, 540, "SOKOBAN");
				}
				if (x == 1)// ingresa a la pantalla de opciones
				{
					menuPrincipal->close();
					options = new Opciones(960, 540, "SOKOBAN");
				}
				if (x == 2) 
				{
					menuPrincipal->close();
					info = new pantallaAcercaDe(960, 540, "SOKOBAN");
				}
				if (x == 3)
				{
					menuPrincipal->close();
					game = new Juego(1280, 720, "SOKOBAN", "6");
				}
				if (x == 4)
				{
					menuPrincipal->close();
					exit(1);
				}
			}
		}
	
	}
}



//metodos para moverse entre las opciones con las teclas de arriba y abajo del teclado
void Menu::MoverArriba()
{
	if (MenuSeleccionado - 1 >= 0)
	{
		vectorBotones[MenuSeleccionado].setFillColor(Color::White);

		MenuSeleccionado--;
		vectorBotones[MenuSeleccionado].setFillColor(Color::Blue);
	}
	else
	{
		if (MenuSeleccionado == 0)
		{
			vectorBotones[MenuSeleccionado].setFillColor(Color::White);
			MenuSeleccionado = 3;
		}
		vectorBotones[MenuSeleccionado].setFillColor(Color::Blue);
	}
}

void Menu::Moverabajo()
{
	if (MenuSeleccionado + 1 <= Max_menu)
	{
		vectorBotones[MenuSeleccionado].setFillColor(Color::White);
		MenuSeleccionado++;
		if (MenuSeleccionado == Max_menu)
		{
			MenuSeleccionado = 0;
		}
		vectorBotones[MenuSeleccionado].setFillColor(Color::Blue);
	}
}


