#include "SDL.h"
#include "Game.h"
#include "MainMenu.h"

int main(int argc, char **argv) {

	MainMenu mainMenu;

	mainMenu.showMainMenu();

    SDL_Quit();

    return 0;
}

