#ifndef __PIEZA_H__
#define __PIEZA_H__


#include "global.h"
//#include <vector>

//void cuadrado(int , int );

/*
struct Coord {
	int x, y;
};
*/

struct Pieza {
	Coord orig;					//bloque original, pieza base
	Coord perif[NUMC-1];		//los 3 bloques perifericos, relativos al original
	//std::vector<Coord> perif;
	int micolor;

	int id;			//para identificar la pieza (el cuadrado no rota)
	int hori;	

	//int numc;		//numero de cuadrados que tiene la pieza

	Pieza();
	void pinta_pieza();
	void rota_derecha();
	Coord getCoordSquare(int n) const;	//le paso un cuadrado (0 central, de 1 a 3 periferico) y me devuelve su coordenada
	void set_pieza_nueva();				//elije pieza al azar

	void set_pieza_hold(int id);
	void espejo();
};


#endif