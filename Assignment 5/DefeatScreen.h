#ifndef DEFEATSCREEN_H
#define DEFEATSCREEN_H

#include "SDL.h"
#include "SDL_TTF.h"
#include "Graphics.h"
#include "Game.h"
#include "Data.h"
#include <string>

using namespace std;

class DefeatScreen{
public:

	DefeatScreen() {

	};

	void drawDefeatScreen(Data &data, bool &skipMenu){
		bool optionSelected = false;
		SDL_Event event;

		draw(data);

		//display end stats loop
		while (!optionSelected) {

			if (SDL_PollEvent(&event)) { //check for new event
				if (event.type == SDL_MOUSEBUTTONDOWN) {
					//If the left mouse button was pressed
					if (event.button.button == SDL_BUTTON_LEFT){
						if(event.button.x > 602 && event.button.x < 817 && event.button.y > 572 && event.button.y < 633) {
							skipMenu = true;
							data.resetData();
							data.waveCount = 0;
							optionSelected = true;
						}

						if(event.button.x > 910 && event.button.x < 1125 && event.button.y > 572 && event.button.y < 632) {
							optionSelected = true;
						}
						cout << event.button.x << " - " << event.button.y << endl;
					}
				}
			}

			//exit event
			if (event.type == SDL_QUIT) {
				exit(0);
			}
		}
	}

	void draw(const Data &data){

		const int UPGRADE_WIDTH = 1138;
		const int UPGRADE_HEIGHT = 599;
		//setup screen
		graphics.drawBackground("Images/bg.bmp");

		//display defeat screen .bmp
		graphics.displaySprite("Images/defeat_screen.bmp", 0, 0, GAME_WIDTH/2 - UPGRADE_WIDTH/2, GAME_HEIGHT/2 - UPGRADE_HEIGHT/2 + 15, UPGRADE_WIDTH, UPGRADE_HEIGHT);

		//write text
		graphics.drawText("Game Over", 90, 90, 55, 255, 255, 255);
		graphics.drawText("Defeat", 200, 650, 240, 100, 100, 100);
		graphics.drawText("Play Again", 55, 618, 575, 0, 0, 0);
		graphics.drawText("Main Menu", 55, 918, 575, 0, 0, 0);

		graphics.drawText("Stats", 55, 265, 170, 255, 255, 255);

		graphics.drawText("Waves Completed: ", 30, 160, 240, 255, 255, 255);  graphics.drawText(to_string(data.waveCount).c_str(), 30, 340, 240, 255, 255, 255);
		graphics.drawText("Enemies Killed: ", 30, 160, 270, 255, 255, 255);	  graphics.drawText(to_string(data.killedTotal).c_str(), 30, 340, 270, 255, 255, 255);
		graphics.drawText("Points Earned: ", 30, 160, 300, 255, 255, 255);	  graphics.drawText(to_string(data.points).c_str(), 30, 340, 300, 255, 255, 255);
		graphics.drawText("Cash Earned: ", 30, 160, 330, 255, 255, 255);	  graphics.drawText(to_string(data.moneyTotal).c_str(), 30, 340, 330, 255, 255, 255);

		//to_string("").c_str()
		graphics.flip();
	}

private:
	Graphics graphics;
};

#endif