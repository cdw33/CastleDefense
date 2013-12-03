#ifndef MAINMENU_H
#define MAINMENU_H

#include "SDL.h"
#include "SDL_TTF.h"
#include "Graphics.h"
#include "Game.h"

using namespace std;

class MainMenu {
public:

    MainMenu() {

    };

    //initialize Main menu
	void showMainMenu(){
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
							drawMainMenu();
						}
						if ((event.button.x < 830 && event.button.x > 500 ) && (event.button.y < 467 && event.button.y > 400)) {
							drawAbout();
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
		graphics.drawBackground("Images/bg.bmp");

		

		//write Title
		graphics.drawText("Castle Defense", 179, 252, 80, 255, 255, 255);
		graphics.drawText("Castle Defense", 182, 245, 80, 0, 0, 0); 
		graphics.drawText("Castle Defense", 180, 250, 80, 180, 180, 180); 

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
	graphics.drawBackground("Images/bg.bmp");
	graphics.displaySprite("Images/about.bmp", 0, 0, 260, 75, 761, 567);

	/* draw text */
	graphics.drawText("About", 85, 268, 70, 0, 0, 0);
	graphics.drawText("Back", 50, 862, 585, 0, 0, 0);
	graphics.drawText("Fight off the ghost armies!", 50, 330, 200, 0, 0, 0);
	graphics.drawText("-Stay alive for as long as you can.", 40, 360, 250, 0, 0, 0);
	graphics.drawText("-Don't forget to upgrade bullets.", 40, 360, 300, 0, 0, 0);
	graphics.drawText("-enemies get stronger and more plentiful", 40, 360, 350, 0, 0, 0);
	graphics.drawText("as the wave count increases", 40, 385, 385, 0, 0, 0);

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
		if (SDL_PollEvent(&event)) { //check for new event
			if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT){
					printf("location -> x: %i  y: %i\n", event.button.x, event.button.y);
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
	Graphics graphics;
	Game game;  
};

#endif