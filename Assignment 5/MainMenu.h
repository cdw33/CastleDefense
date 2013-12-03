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
						if ((event.button.x < 830 && event.button.x > 500) && (event.button.y < 367 && event.button.y > 300)) {
							game.setupGame();
							game.runGame(); 
							drawMainMenu();
						}
						if ((event.button.x < 830 && event.button.x > 500 ) && (event.button.y < 467 && event.button.y > 400)) {
							//open about page
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




private:
	Graphics graphics;
	Game game;  
};

#endif