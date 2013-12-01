#ifndef DEFEATSCREEN_H
#define DEFEATSCREEN_H

#include "SDL.h"
#include "SDL_TTF.h"
#include "Graphics.h"
#include "Game.h"
#include "Data.h"

using namespace std;

class DefeatScreen{
public:

	DefeatScreen() {

	};

	void drawDefeatScreen(){
		bool optionSelected = false;
		SDL_Event event;

		draw();

        //display end stats loop
        while (!optionSelected) {

            if (SDL_PollEvent(&event)) { //check for new event
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    //If the left mouse button was pressed
                    if (event.button.button == SDL_BUTTON_LEFT){
						optionSelected = true;
                    }
                }
            }

            //exit event
            if (event.type == SDL_QUIT) {
                exit(0);
            }
        }

		

	}

	void draw(){
		//setup screen
		graphics.drawBackground("Images/bg.bmp");

		//write text
		graphics.drawText("Defeat Test Page", 80, 250, 100, 0, 0, 0);
		graphics.drawText("Click Anywhere to", 80, 250, 180, 0, 0, 0);
		graphics.drawText("Return to Main Menu", 80, 250, 260, 0, 0, 0);

		graphics.flip();
	}

private:
	Graphics graphics;
};

#endif