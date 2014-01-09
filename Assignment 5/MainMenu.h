#ifndef MAINMENU_H
#define MAINMENU_H

#include "SDL.h"
#include "SDL_TTF.h"
#include "Graphics.h"
#include "Game.h"
#include "Highscore.h"

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
						} else if ((event.button.x < 830 && event.button.x > 500) && (event.button.y < 467 && event.button.y > 400)) {
							highscoreLoop();
						} else if ((event.button.x < 830 && event.button.x > 500) && (event.button.y < 567 && event.button.y > 500)) {
							aboutLoop();
						} else if ((event.button.x < 830 && event.button.x > 500) && (event.button.y < 667 && event.button.y > 600)) {
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
		graphics.displaySprite("Images/MMbutton.bmp", 0, 0, 500, 600, 330, 67);

		//display text
		graphics.drawText("New Game", 60, 570, 300, 0, 0, 0);
		graphics.drawText("High Scores", 60, 552, 402, 0, 0, 0);
		graphics.drawText("About", 60, 610, 502, 0, 0, 0);
		graphics.drawText("Exit", 60, 630, 602, 0, 0, 0);

		graphics.flip(); 
	}

	void aboutLoop() {
		bool done = false;
		SDL_Event event;

		while (!done) {
			drawAbout();
			if (SDL_PollEvent(&event)) { //check for new event
				if (event.type == SDL_MOUSEBUTTONDOWN) {
					if (event.button.button == SDL_BUTTON_LEFT) {
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

	void drawAbout() {
		/* draw background */
		background.display(Background::MAIN);
		graphics.displaySprite("Images/about.bmp", 0, 0, 260, 75, 761, 567);

		/* draw text */
		graphics.drawText("About", 85, 268, 70, 0, 0, 0);
		graphics.drawText("Back", 50, 862, 585, 0, 0, 0);
		graphics.drawText("Fight off the hord armies!", 50, 330, 160, 0, 0, 0);
	
		const int SIZE = 35;
		graphics.drawText("- Stop the approaching enemies as they near your base",   SIZE, 360, 210, 0, 0, 0);
		graphics.drawText("- Click anywhere on the screen to fire a bullet",         SIZE, 360, 247, 0, 0, 0);
		graphics.drawText("- Enemies get stronger and more plentiful as the wave",   SIZE, 360, 280, 0, 0, 0);
		graphics.drawText("  count increases",                                       SIZE, 360, 312, 0, 0, 0);
		graphics.drawText("- Purchase upgrades at the end of each wave to increase", SIZE, 360, 347, 0, 0, 0);
		graphics.drawText("  your chances of survival",                              SIZE, 360, 379, 0, 0, 0);
		graphics.drawText("- Pit yourself against endless waves of enemies to",      SIZE, 360, 414, 0, 0, 0);
		graphics.drawText("  achieve a high score",                                  SIZE, 360, 449, 0, 0, 0);
		graphics.drawText("- Stay alive for as long as you can!",                    SIZE, 360, 484, 0, 0, 0);

		/* authors */
		graphics.drawText("Creators:", 30, 300, 540, 0, 0, 0);
		graphics.drawText("-Aaron Battershell", 30, 300, 560, 0, 0, 0);
		graphics.drawText("-Christopher Wilson", 30, 300, 580, 0, 0, 0);
		graphics.drawText("-Cory Boveington", 30, 300, 600, 0, 0, 0);

		graphics.flip();
	}

	void highscoreLoop() {
		bool done = false;
		SDL_Event event;

		while (!done) {
			drawHighscore();
			if (SDL_PollEvent(&event)) { //check for new event
				if (event.type == SDL_MOUSEBUTTONDOWN) {
					if (event.button.button == SDL_BUTTON_LEFT) {
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

	void drawHighscore() {
		const int SIZE = 35;
		const vector<entree> highscoreList = highscore.getHighscores();

		/* draw background */
		background.display(Background::MAIN);
		graphics.displaySprite("Images/about.bmp", 0, 0, 260, 75, 761, 567);

		/* draw text */
		graphics.drawText("High Scores", 85, 270, 74, 0, 0, 0);
		graphics.drawText("Back", 50, 862, 585, 0, 0, 0);
		graphics.drawText("Name                 Wave     Score", SIZE + 15, 330, 160, 0, 0, 0);

		/* display highscores */
		for (int i = 0; i < highscore.getCap(); ++i) {   
			graphics.drawText(to_string(i+1).c_str(),                    SIZE, 336, 210 + SIZE * i, 0, 0, 0);
			graphics.drawText(": ",                                      SIZE, 351, 210 + SIZE * i, 0, 0, 0);
			graphics.drawText((highscoreList[i].name).c_str(),           SIZE, 365, 210 + SIZE * i, 0, 0, 0); 

			graphics.drawText(to_string(highscoreList[i].wave).c_str(),  SIZE, 595, 210 + SIZE * i, 0, 0, 0);
			graphics.drawText(to_string(highscoreList[i].score).c_str(), SIZE, 726, 210 + SIZE * i, 0, 0, 0);
		}

		graphics.flip();
	}

private:
	Highscore highscore;
	Background background;
	Graphics graphics;
	Game game;  
};

#endif