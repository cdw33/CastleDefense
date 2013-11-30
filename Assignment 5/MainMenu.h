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
		graphics.displaySprite("Images/MM_Placeholder.bmp",0,0,350,300,505,120);	//main menu placeholder text

		//not working
		graphics.drawText("Castle Defense\nMain Menu Test Page\nClick Anywhere to Start", 12, 250, 100, 255, 255, 255, 255, 255, 255);

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