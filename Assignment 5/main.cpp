#include "SDL.h"
#include "Game.h"


int main(int argc, char **argv) {

	//should run main menu class from here
	//

	Game game;

	game.setupGame();
	game.runGame();

    SDL_Quit();

    return 0;
}

