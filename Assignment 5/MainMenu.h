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

		//setup screen
		graphics.drawBackground("Images/bg.bmp");

		//write text
		graphics.drawText("Castle Defense", 80, 250, 100, 0, 0, 0);   
		graphics.drawText("Main Menu Test Page", 80, 250, 180, 0, 0, 0);
		graphics.drawText("Click Anywhere to Start", 80, 250, 260, 0, 0, 0);


		graphics.flip();

        //game loop
        while (!optionSelected) {

            if (SDL_PollEvent(&event)) { //check for new event
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    //If the left mouse button was pressed
                    if (event.button.button == SDL_BUTTON_LEFT){
						game.setupGame();
						game.runGame(); 
						optionSelected = true;
                    }
                }
            }

           

            //exit event
            if (event.type == SDL_QUIT) {
                optionSelected = true;
            }
        }

		

	}


private:
	Graphics graphics;
	Game game;  
};

#endif