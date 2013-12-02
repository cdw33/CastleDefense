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

		drawMainMenu();
		//game loop
        while (!optionSelected) {

            if (SDL_PollEvent(&event)) { //check for new event
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    //If the left mouse button was pressed
                    if (event.button.button == SDL_BUTTON_LEFT){
						game.setupGame();
						game.runGame(); 
						drawMainMenu();
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
		graphics.drawText("Castle Defense", 180, 250, 80, 180, 180, 180); 

		//push buttons
		graphics.displaySprite("Images/MMbutton.bmp", 0, 0, 500, 300, 330, 67);
		graphics.displaySprite("Images/MMbutton.bmp", 0, 0, 500, 400, 330, 67);
		graphics.displaySprite("Images/MMbutton.bmp", 0, 0, 500, 500, 330, 67);


		//display text
		graphics.drawText("New Game", 60, 570, 300, 0, 0, 0);
		graphics.drawText("About", 80, 250, 260, 0, 0, 0);
		graphics.drawText("Exit", 80, 250, 260, 0, 0, 0);


		graphics.flip(); 
}


private:
	Graphics graphics;
	Game game;  
};

#endif