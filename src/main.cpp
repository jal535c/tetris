#include "miniwin.h"		//obligado poner donde este el main
#include "game.h"
#include <cstdlib>
#include <time.h>


int main() {
	srand(time(0));		//para la semilla del rand de la piezas
	
	Game game; //= new Game();
	game.run();
	//delete game;
	
	return 0;
}