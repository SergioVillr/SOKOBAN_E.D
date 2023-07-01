# SOKOBAN_con Estructuras de Datos
Proyecto del curso de Estructuras de Datos, Universidad Nacional

El juego consiste en un rompecabezas de longitud variable en el cuál un personaje debe arrastrar las cajas hasta el lugar correcto.
Una vez colocadas todas las cajas en el lugar especificado, el jugador gana y avanza hasta el siguiente nivel.
Como regla general, el personaje solamente puede mover una caja a la vez, las cajas no pueden atravesar paredes ni otros obstáculos. 
Se alcanza el final del nivel una vez que todas las cajas se hayan acomodado correctamente.

Caracteristicas del programa:

El programa fue desarrollado en C++ utilizando Visual Studio 2019 Community.

Se utilizo estructuras de datos dinámicas para la creación del tablero (listas 
enlazadas). Con la idea de simular un “grid”, el cuál es muy utilizado en los juegos de 
video tipo 2D. Es decir, el objetivo es crear una “matriz” con listas enlazadas.


El nivel finaliza cuando el jugador mueva las cajas a todas las posiciones. Para llevar 
la cuenta de las cajas que están en la posición final, se utiliza una pila (stack) utilizando 
la STL.

La interfaz grafica  se trabajo con la librería SFML

Imagenes de la interfaz final del juego

MENU
[![Menu.png](https://i.postimg.cc/QCcPvkcH/Menu.png)](https://postimg.cc/H8sByMZg)


