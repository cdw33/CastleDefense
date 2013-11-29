#include "SDL.h"
#include "Game.h"
#include "MainMenu.h"

int main(int argc, char **argv) {

	//should run main menu class from here
	//

	//Game game;
	MainMenu mainMenu;	//change to MainMenu once implemented

	//game.setupGame();
	//game.runGame();
	mainMenu.showMainMenu();

    SDL_Quit();

    return 0;
}

