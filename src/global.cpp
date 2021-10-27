#include "global.h"


const Coord perifs[7][3] = {		//coordenadas de los bloques perifericos
	{ {1,0},  {0,1},  {1,1}  },		//cuadrado, azul
	{ {1,0},  {-1,1}, {0,1}  },		//s, cian
	{ {0,1},  {1,1},  {-1,0} },		//2, naranja
	{ {1,0},  {-1,0}, {-1,1}  },		//L, magenta
	{ {-1,0},  {1,0}, {1,1} },		//Lr, amarillo
	{ {-1,0}, {1,0},  {0,1}  },		//T, verde
	{ {-2,0}, {-1,0}, {1,0}  }		//palo, rojo	
};


const int colores[7] = { 
	3, 6, 8, 5, 4, 2, 1
};


const int puntos_limite[6] = {		//tabla con los puntos necesarios para cambiar de nivel
	30, 55, 75, 90, 95, 100			//al terminar nivel 10 debe aparecer mensaje de you win (falta)
	//200, 220, 240, 260, 400
};


const int tics_nivel[6] = {		//tabla con los tics que espera en cada nivel
	33, 24, 16, 10, 6, 4
	
};