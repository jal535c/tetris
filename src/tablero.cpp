#include "tablero.h"
#include "pieza.h"
#include "miniwin.h"


Tablero::Tablero()
{
	vaciar();
}


void Tablero::vaciar() {		//rellena todo el tablero de negro
	for (int i=0; i<COLUMNAS; i++)
		for (int j=0; j<FILAS; j++)
			casilla[i][j] = miniwin::NEGRO;		//negro = 0 = casilla vacia
}


void Tablero::pintar() {		//es como refresca. Yo tengo en T los colores, pero ahora tengo k pintar
	for (int i=0; i<COLUMNAS; i++) { 
		for (int j=0; j<FILAS; j++) {
			miniwin::color(casilla[i][j]);
			cuadrado(i, j);		
		}
	}
}


void Tablero::incrusta_pieza(const Pieza& P) {		//mete las coordenadas de la pieza en el tablero
	for (int i=0; i<NUMC; i++) {
		Coord c = P.getCoordSquare(i);
		casilla[c.x][c.y] = P.micolor;
	}
}


bool Tablero::colision(const Pieza& P) {		//me indica si hay colision
	for (int i=0; i<NUMC; i++) {
		Coord c = P.getCoordSquare(i);

		
		if (c.x < 0 || c.x >= COLUMNAS)		//comprobar limites con ventana
			return true;

		if (c.y < 0 || c.y >= FILAS)
			return true;

		
		if (casilla[c.x][c.y] != miniwin::NEGRO)		//comprobar con basurilla
			return true;
	}

	return false;
}


bool Tablero::fila_llena(int fila) {		//para saber si hay una fila completa ninguna casilla debe ser negra
	for (int i=0; i< COLUMNAS; i++) {
		if (casilla[i][fila] == miniwin::NEGRO) 
			return false;
	}
	return true;
}


void Tablero::colapsa(int fila) {		//cuando hay linea, la basurilla debe bajar
	for (int j=fila; j>0; j--) {
		for (int i=0; i<COLUMNAS; i++) {
			casilla[i][j] = casilla[i][j-1];					//debo poner en la k estoy lo k halla en la anterior
		}
	}
	
	for (int i=0; i<COLUMNAS; i++) {		//vaciar la fila 0, ponerla negra
		casilla[i][0] = miniwin::NEGRO;
	}
}


int Tablero::cuenta_lineas() {		//y si hago 2 lineas a la vez? debo quitar todas las lineas k haga
	int fila = FILAS-1;
	int cont=0;			//el contador es para k me den mas puntos si hago varias lineas

	while (fila>=0) {
		if (fila_llena(fila)) {
			colapsa(fila);
			cont++;
		} else {
			fila--;
		}
	}

	return cont;		
}

