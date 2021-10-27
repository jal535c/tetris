#ifndef __GLOBAL_H__
#define __GLOBAL_H__


const int TAM=25;	//tamaño de cada cuadrado, 25 pixeles

const int FILAS=20;		//tamaño del tablero en cuadrados, 
const int COLUMNAS=10;	//el tablero es un array que tiene en cada posicion el color, negro=0=vacio

const int NUMC = 4;		//numero de cuadraditos de cada pieza
const int NUMP = 7;	//numero de piezas


void cuadrado(int , int );		//funcion usada por Pieza y Tablero. La funcion rota_derecha_c solo la usa Pieza


struct Coord {
	int x, y;
};

/*
typedef struct {

} Coord;
*/

extern const Coord perifs[7][3];
extern const int colores[7];


extern const int puntos_limite[6];
extern const int tics_nivel[6];
					

#endif