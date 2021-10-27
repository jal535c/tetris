#ifndef __TABLERO_H__
#define __TABLERO_H__


#include "global.h"
class Pieza;			//debo incluir pieza, por las referencias, sino da error de tipos. Probar forward declaration


struct Tablero {
private:	
	int casilla[COLUMNAS][FILAS];				//matriz de int (en realidad son colores)

public:
	Tablero();
	void vaciar();
	void pintar();
	void incrusta_pieza(const Pieza& P);		//de Pieza usa el metodo posicion() y el atributo micolor
	bool colision(const Pieza& P);				//de Pieza usa el metodo posicion()
	bool fila_llena(int fila);
	void colapsa(int fila);
	int cuenta_lineas();
};


#endif