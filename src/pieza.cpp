#include "pieza.h"
#include <cstdlib>
#include "miniwin.h"
//#include <global.h>

/*
const Coord perifs[7][3] = {		//coordenadas de los bloques perifericos
	{ {1,0}, {0,1}, {1,1} },		//cuadrado, azul
	{ {1,0}, {-1,1}, {0,1} },		//s, cian
	{ {0,1}, {1,1}, {-1,0} },		//2, naranja
	{ {0,1}, {0,-1}, {1,1} },		//L, magenta
	{ {0,1}, {0,-1}, {-1,1} },		//Lr, amarillo
	{ {-1,0}, {1,0}, {0,1} },		//T, verde
	{ {0,1}, {0,-1}, {0,2} },		//palo, rojo
};
*/

void cuadrado(int x, int y) {
	miniwin::rectangulo_lleno(190+20+ 1+x*TAM, 
								20+ 1+y*TAM, 
								190+20+ x*TAM+TAM, 
								20+ y*TAM+TAM);	//+1 es para ver la separacion entre los 4 cuadrados
}


Pieza::Pieza()
{
	set_pieza_nueva();
}


Coord Pieza::getCoordSquare(int n) const {	//le paso el cuadrado (0 origen, 1-3 perifs) y me devuelve su posicion
	Coord ret = { orig.x, orig.y };		//le asigno el cuadrado referencia
	if (n!=0) {
		ret.x += perif[n-1].x;
		ret.y += perif[n-1].y;
	}
	return ret;
}

void Pieza::pinta_pieza() {		//pone color y pinta 4 cuadrados
	miniwin::color(micolor);
	for (int i=0; i<NUMC; i++) {
		Coord c = getCoordSquare(i);
		cuadrado(c.x, c.y);
	}
}


Coord rota_derecha_c(const Coord& c, Pieza* P) {		//formula para rotar: intercambia x e y, cambia signo a x
	if (P->id == 0) {		//el cuadrado no rota
		Coord ret = { c.x, c.y };
		return ret;
	}

	if (P->id == 6) {		//el palo solo rota 90º
		if (c.y==0) {
			Coord ret = { c.y, -c.x };
			return ret;		
		} else {
			Coord ret = { -c.y, c.x };
			return ret;		
		}
	}

	if ((P->id == 1 || P->id==2) && P->hori==1) {		//la s y el 2 solo cambian de horizontal a vertical, no rotan
		Coord ret = { c.y, -c.x };
		return ret;		
	} else if ((P->id == 1 || P->id==2) && P->hori==0) {
		Coord ret = { -c.y, c.x };
		return ret;		
	}

	Coord ret = { c.y, -c.x };		//realmente rota a izquierdas
	return ret;
}


void Pieza::rota_derecha() {
	for (int i = 0; i<NUMC-1; i++) {
		perif[i] = rota_derecha_c(perif[i], this);
	}

	if (hori == 1)
		hori=0;
	else if (hori == 0)
		hori=1;
}


Coord simetrico(const Coord& c) {		//formula para el simetrico: x = -x, y = y
	Coord ret = { -c.x, c.y };
	return ret;
}


void Pieza::espejo() {
	for (int i = 0; i<NUMC-1; i++) {
		perif[i] = simetrico(perif[i]);
	}
}


void Pieza::set_pieza_nueva() {
	orig.x = 13; 		//posicion de salida
	orig.y = 1;
	
	//micolor = 1 + rand()%6;

	int r = rand()%NUMP;		//pieza al azar (entre 0 y 6), elijo una fila de mi matriz perifs de patrones
	id = r;
	hori=1;

	micolor = colores[r];

	for (int i=0; i<NUMC-1; i++) {
		perif[i] = perifs[r][i];		//relleno mis coordenadas con mi patron
	}
}


void Pieza::set_pieza_hold(int id) {
	orig.x = 13;
	orig.y = 16;

	for (int i=0; i<NUMC-1; i++) {
		perif[i] = perifs[id][i];
	}

	micolor = colores[id];

	this->id = id;
	hori = 1;
}