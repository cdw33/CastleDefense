#ifndef MAINMENU_H
#define MAINMENU_H

#include "SDL.h"
#include "SDL_TTF.h"
#include "Graphics.h"
#include "Game.h"

using namespace std;

class MainMenu {
public:

    MainMenu()  { }
	~MainMenu() { }

    //initialize Main menu
	void showMainMenu() {
		bool optionSelected = false;
		SDL_Event event;

		
		//game loop
        while (!optionSelected) {
			drawMainMenu();
            if (SDL_PollEvent(&event)) { //check for new event
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    //If the left mouse button was pressed
                    if (event.button.button == SDL_BUTTON_LEFT){
						if ((event.button.x < 830 && event.button.x > 500) && (event.button.y < 367 && event.button.y > 300)) {
							game.setupGame();
							game.runGame(); 
							background.reset();
							drawMainMenu();
						}
						if ((event.button.x < 830 && event.button.x > 500 ) && (event.button.y < 467 && event.button.y > 400)) {
							aboutLoop();
						}
						if ((event.button.x < 830 && event.button.x > 500 ) && (event.button.y < 567 && event.button.y > 500)) {
							event.type = SDL_QUIT;
						}
                    }
                }
            }

            //exit event
            if (event.type == SDL_QUIT) {
                optionSelected = true;
            }
        }
	}

void drawMainMenu(){
	//setup screen
	background.display(Background::MAIN);

	//write Title
	graphics.drawText("Castle Defense", 179, 252, 90, 255, 255, 255);
	graphics.drawText("Castle Defense", 182, 245, 90, 0, 0, 0); 
	graphics.drawText("Castle Defense", 180, 250, 90, 180, 180, 180); 

	//push buttons
	graphics.displaySprite("Images/MMbutton.bmp", 0, 0, 500, 300, 330, 67);
	graphics.displaySprite("Images/MMbutton.bmp", 0, 0, 500, 400, 330, 67);
	graphics.displaySprite("Images/MMbutton.bmp", 0, 0, 500, 500, 330, 67);


	//display text
	graphics.drawText("New Game", 60, 570, 300, 0, 0, 0);
	graphics.drawText("About", 60, 610, 400, 0, 0, 0);
	graphics.drawText("Exit", 60, 630, 500, 0, 0, 0);


	graphics.flip(); 
}

void drawAbout() {
	/* draw background */
	background.display(Background::MAIN);
	graphics.displaySprite("Images/about.bmp", 0, 0, 260, 75, 761, 567);

	/* draw text */
	graphics.drawText("About", 85, 268, 70, 0, 0, 0);
	graphics.drawText("Back", 50, 862, 585, 0, 0, 0);
	graphics.drawText("Fight off the hord armies!", 50, 330, 160, 0, 0, 0);
	
	const int SIZE = 32;
	graphics.drawText("- Stop the approaching enemies as they near",     SIZE, 360, 207, 0, 0, 0);
	graphics.drawText("    your base",                                   SIZE, 360, 239, 0, 0, 0);
	graphics.drawText("- Click anywhere on the screen to fire a bullet", SIZE, 360, 271, 0, 0, 0);
	graphics.drawText("- The further you click from the castle, the",    SIZE, 360, 303, 0, 0, 0);
	graphics.drawText("    faster your bullet travels",                  SIZE, 360, 335, 0, 0, 0);
	graphics.drawText("- Enemies get stronger and more plentiful as",    SIZE, 360, 367, 0, 0, 0);
	graphics.drawText("    the wave count increases",                    SIZE, 360, 399, 0, 0, 0);
	graphics.drawText("- Purchase upgrades at the end of each wave to",  SIZE, 360, 431, 0, 0, 0);
	graphics.drawText("    increase your chances of survival",           SIZE, 360, 463, 0, 0, 0);
	graphics.drawText("- Stay alive for as long as you can!",            SIZE, 360, 495, 0, 0, 0);

	/* Old about menu text
	graphics.drawText("-Stay alive for as long as you can.", 40, 360, 250, 0, 0, 0);
	graphics.drawText("-Don't forget to upgrade bullets.", 40, 360, 300, 0, 0, 0);
	graphics.drawText("-enemies get stronger and more plentiful", 40, 360, 350, 0, 0, 0);
	graphics.drawText("as the wave count increases", 40, 385, 385, 0, 0, 0);
	*/

	/* authors */
	graphics.drawText("Creators:", 30, 300, 540, 0, 0, 0);
	graphics.drawText("-Aaron Battershell", 30, 300, 560, 0, 0, 0);
	graphics.drawText("-Christopher Wilson", 30, 300, 580, 0, 0, 0);
	graphics.drawText("-Cory Boveington", 30, 300, 600, 0, 0, 0);

	graphics.flip();
}

void aboutLoop() {
	bool done = false;
	SDL_Event event;

    while (!done) {
		drawAbout();
		if (SDL_PollEvent(&event)) { //check for new event
			if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT){
					if ((event.button.x < 1009 && event.button.x > 784 ) && (event.button.y < 627 && event.button.y > 586)) {
						done = true;
					}
				}
			}
		} else if (event.type == SDL_QUIT) {
                SDL_Quit();
				exit(0);
        }
	}
}

private:
	Background background;
	Graphics graphics;
	Game game;  
};

#endif