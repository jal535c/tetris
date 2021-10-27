#include "miniwin.h"
#include "game.h"
#include "global.h"
#include <sstream>


Game::Game() 
{
	miniwin::vredimensiona(220+200 + TAM*COLUMNAS, 40 + TAM*FILAS);		//ventana mas grande
	
	tic = 0;
	puntos = 0;
	nivel = 0;

	reserva = 0;

	T.vaciar();
	sig.set_pieza_nueva();
	P.set_pieza_nueva();
		
	P.orig.x = 5;

	hold.set_pieza_nueva();
	hold.orig.y = 16;
	hold.micolor = 0;		//la pinta de negro, la primera vez no veo la reserva

	aux = P;

	draw();
}


Game::~Game() {
	miniwin::vcierra();
}


void Game::run() {
	int t = miniwin::tecla();
	while (t != miniwin::ESCAPE) {
		
		Pieza copia = P;	//copia la actual, update de la actual y si hay colision vuelvo al backup

		if (t == miniwin::NINGUNA  &&  tic>tics_nivel[nivel]) {		//para controlar la velocidad de bajada
			tic = 0;
			t = miniwin::ABAJO;
		}


		if (t == miniwin::ABAJO) 			P.orig.y++;
		else if (t == miniwin::ARRIBA) 		P.rota_derecha();
		else if (t == miniwin::DERECHA) 	P.orig.x++;
		else if (t == miniwin::IZQUIERDA) 	P.orig.x--;
		else if (t == miniwin::ESPACIO) 	P.espejo();

		if (t == int('N'))		//huevo de pascua
			nivel++;


		if (t == int('Z') && reserva==1) {	//la uso (intercambia la de reserva y la principal una vez)
			aux = P;
			
			P = hold;
			P.orig.x = 5;
			P.orig.y = 1;

			hold.set_pieza_hold(aux.id);
			//hold = aux;
			//hold.orig.x = 12;
			//hold.orig.y = 14;

			reserva = 2;
		}
				
		if (t == int('Z') && reserva==0) {		//la guardo la primera vez
			hold.set_pieza_hold(P.id);
			//hold.orig.x = 12;
			//hold.orig.y = 14;

			P = sig;
			P.orig.x = 5;
			sig.set_pieza_nueva(); 	 //vuelvo a usar el objeto P 

			reserva = 2;
		}

		
		if (T.colision(P)) {	//hay colision? actualicé las posiciones, pero si hay colision vuelvo a poner las antiguas
			P = copia;
			if (t == miniwin::ABAJO) {		//si bajando hay colison incrusta basurilla, no con los laterales
				T.incrusta_pieza(P);
				int cont = T.cuenta_lineas();
				puntos += cont * cont;

				if (puntos >= 100) {
					game_over("YOU WIN");
					return;
				}


				if (puntos >= puntos_limite[nivel])
					nivel++;


				P = sig;
				P.orig.x = 5;
				sig.set_pieza_nueva(); 	 //vuelvo a usar el objeto P 

				if (reserva != 0)	//por si no guardo la primera pieza
					reserva = 1;

				if (T.colision(P)) {
					game_over("GAME OVER");
					return;			//sale del run, tambien vale exit(0)
				}
			}
		}


		if (t != miniwin::NINGUNA) {
			draw();		
		}
				
		miniwin::espera(30);
		tic++;
		t = miniwin::tecla();
	}
}


void Game::update() {
	
}


void Game::draw() {
	miniwin::borra();
	
	T.pintar();
	
	pinta_interfaz();

	sig.pinta_pieza();
	P.pinta_pieza();
	hold.pinta_pieza();

	miniwin::refresca();	
}


void Game::pinta_interfaz() {
	const int ancho = TAM*COLUMNAS;
	const int alto = TAM*FILAS;

	miniwin::color_rgb(128, 128, 128);
	miniwin::linea(190+20, 20, 190+20, 20+alto);
	miniwin::linea(190+20, 20+alto, 190+20+ancho, 20+alto);
	miniwin::linea(190+20+ancho, 20+alto, 190+20+ancho, 20);

	miniwin::texto(190+40+ancho, 20, "Pieza siguiente");
	miniwin::texto(190+40+ancho, 150, "Nivel");
	miniwin::texto(190+40+ancho, 250, "Puntos");
	miniwin::texto(190+40+ancho, 380, "Pieza reserva");

	miniwin::texto(30, 20, "TETRIS");
	miniwin::texto(30, 80, "<- ->: mover la pieza");
	miniwin::texto(30, 120, "Abajo: bajar la pieza");
	miniwin::texto(30, 160, "Arriba: rotar la pieza");
	miniwin::texto(30, 200, "Z: guardar o usar reserva");
	miniwin::texto(30, 280, "1 linea: 1 punto");
	miniwin::texto(30, 320, "2 lineas: 4 puntos");
	miniwin::texto(30, 360, "3 lineas: 9 puntos");
	miniwin::texto(30, 400, "4 lineas: 16 puntos");

	miniwin::color(miniwin::BLANCO);
	miniwin::texto(190+40+ancho, 270, a_string(puntos));		//muestra los puntos
	miniwin::texto(190+40+ancho, 170, a_string(nivel + 1));		//muestra el nivel, pero los niveles empiezan en 1
}


std::string Game::a_string(int puntos) {
	std::stringstream sout;
	sout << puntos;
	return sout.str();
}


void Game::game_over(std::string text) {
	miniwin::color(miniwin::BLANCO);
	miniwin::texto(320, 240, text);
	miniwin::refresca();
	miniwin::espera(3000);		//espera 2seg
	//miniwin::vcierra();		//segmentation fault
}