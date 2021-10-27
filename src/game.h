#ifndef __GAME_H__
#define __GAME_H__


#include "pieza.h"
#include "tablero.h"
#include <string>


class Game {
private:
	Pieza P;
	Pieza sig;
	Pieza hold, aux;
	Tablero T;

	int tic;

	int puntos;
	int nivel;
	int reserva;	//controla las veces que pulso la tecla z

public:
	Game();
	~Game();
	void run();

	void update();
	void draw();

	std::string a_string(int puntos);
	void game_over(std::string text);
	void pinta_interfaz();
};


#endif