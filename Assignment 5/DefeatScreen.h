#ifndef DEFEATSCREEN_H
#define DEFEATSCREEN_H

#include "SDL.h"
#include "SDL_TTF.h"
#include "Graphics.h"
#include "Game.h"
#include "Data.h"
#include <string>

using namespace std;

class DefeatScreen {
public:

	DefeatScreen()  { };
	~DefeatScreen() { };

	string getPercentage(int num, int den) {
		string percentage = to_string(100.0*max(1,num)/max(1,den));
		percentage.erase(percentage.begin()+4, percentage.end());
		percentage.append("%");

		return percentage;
	}

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
					}
				}
			}

			//exit event
			if (event.type == SDL_QUIT) {
				exit(0);
			}
		}
	}

	void displayQuote() {
		static bool 
			lastPick = -1;
		static int
			choice = -1;
		const int 
			COUNT = 11,
			SIZE_QUOTE = 35,
			SIZE_SIG = SIZE_QUOTE - 5,
			START_X = 155,
			START_Y_1 = 475,
			START_Y_2 = START_Y_1 + SIZE_QUOTE,
			START_Y_3 = START_Y_2 + SIZE_QUOTE,
			START_Y_4 = START_Y_3 + SIZE_QUOTE,
			R = 255,
			G = 255,
			B = 255;

		/* Ensure that same quote is not displayed twice in a row */
		do { 
			choice = rand()%COUNT;	
		} while (choice == lastPick);
		lastPick = choice;

		if (choice == 0) {
			graphics.drawText("If you learn from defeat,", SIZE_QUOTE, START_X, START_Y_2, R, G, B);
			graphics.drawText("you haven't really lost.", SIZE_QUOTE, START_X, START_Y_3, R, G, B);
			graphics.drawText(" - Zig Ziglar", SIZE_SIG, START_X, START_Y_4, R, G, B);
		} else if (choice == 1) {
			graphics.drawText("Defeat is not the worst of", SIZE_QUOTE, START_X, START_Y_1, R, G, B);
			graphics.drawText("failures. Not to have tried", SIZE_QUOTE, START_X, START_Y_2, R, G, B);
			graphics.drawText("is the true failure.", SIZE_QUOTE, START_X, START_Y_3, R, G, B);
			graphics.drawText(" - George Woodberry", SIZE_SIG, START_X, START_Y_4, R, G, B);
		} else if (choice == 2) {
			graphics.drawText("Opportunity often comes", SIZE_QUOTE, START_X, START_Y_1, R, G, B);
			graphics.drawText("disguised in the form of", SIZE_QUOTE, START_X, START_Y_2, R, G, B);
			graphics.drawText("misfortune.", SIZE_QUOTE, START_X, START_Y_3, R, G, B);
			graphics.drawText(" - Napoleon Hill", SIZE_SIG, START_X, START_Y_4, R, G, B);
		} else if (choice == 3) {
			graphics.drawText("Once we have a war there is ", SIZE_QUOTE, START_X, START_Y_1, R, G, B);
			graphics.drawText("only one thing to do. It", SIZE_QUOTE, START_X, START_Y_2, R, G, B);
			graphics.drawText("must be won.", SIZE_QUOTE, START_X, START_Y_3, R, G, B);
			graphics.drawText(" - Ernest Hemingway", SIZE_SIG, START_X, START_Y_4, R, G, B);
		} else if (choice == 4) {
			graphics.drawText("We should not allow the", SIZE_QUOTE, START_X, START_Y_2, R, G, B);
			graphics.drawText("problem to defeat us.", SIZE_QUOTE, START_X, START_Y_3, R, G, B);
			graphics.drawText(" - Abdul Kalam", SIZE_SIG, START_X, START_Y_4, R, G, B);
		} else if (choice == 5) {
			graphics.drawText("You could have avoided this.", SIZE_QUOTE, START_X, START_Y_2, R, G, B);
			graphics.drawText(" - Anonymous", SIZE_SIG, START_X, START_Y_3, R, G, B);
		} else if (choice == 6) {
			graphics.drawText("The secret is learning how ", SIZE_QUOTE, START_X, START_Y_2, R, G, B);
			graphics.drawText("not to loose.", SIZE_QUOTE, START_X, START_Y_3, R, G, B);
			graphics.drawText(" - Anonymous", SIZE_SIG, START_X, START_Y_4, R, G, B);
		} else if (choice == 7) {
			graphics.drawText("When defeat comes, accept it", SIZE_QUOTE, START_X, START_Y_1, R, G, B);
			graphics.drawText("as a signal that your plans", SIZE_QUOTE, START_X, START_Y_2, R, G, B);
			graphics.drawText("are not sound.", SIZE_QUOTE, START_X, START_Y_3, R, G, B);
			graphics.drawText(" - Napoleon Hill", SIZE_SIG, START_X, START_Y_4, R, G, B);
		} else if (choice == 8) {
			graphics.drawText("Never confuse a single", SIZE_QUOTE, START_X, START_Y_2, R, G, B);
			graphics.drawText("defeat with a final defeat.", SIZE_QUOTE, START_X, START_Y_3, R, G, B);
			graphics.drawText(" - F Scott Fitzgerald", SIZE_SIG, START_X, START_Y_4, R, G, B);
		} else if (choice == 9) {
			graphics.drawText("It is not a field of a few acres", SIZE_QUOTE, START_X, START_Y_1, R, G, B);
			graphics.drawText("of ground, but a cause that", SIZE_QUOTE, START_X, START_Y_2, R, G, B);
			graphics.drawText("we are defending.", SIZE_QUOTE, START_X, START_Y_3, R, G, B);
			graphics.drawText(" - Thomas Paine", SIZE_SIG, START_X, START_Y_4, R, G, B);
		} else {
			graphics.drawText("If you live long enough,", SIZE_QUOTE, START_X, START_Y_1, R, G, B);
			graphics.drawText("you'll see that every victory", SIZE_QUOTE, START_X, START_Y_2, R, G, B);
			graphics.drawText("turns into a defeat.", SIZE_QUOTE, START_X, START_Y_3, R, G, B);
			graphics.drawText(" - Simone de Beauvoir ", SIZE_SIG, START_X, START_Y_4, R, G, B);
		}
	}

	void draw(const Data &data){

		const int UPGRADE_WIDTH = 1138;
		const int UPGRADE_HEIGHT = 599;
		//setup screen
		background.display(Background::DEFEAT);

		//display defeat screen .bmp
		graphics.displaySprite("Images/defeat_screen.bmp", 0, 0, GAME_WIDTH/2 - UPGRADE_WIDTH/2, GAME_HEIGHT/2 - UPGRADE_HEIGHT/2 + 15, UPGRADE_WIDTH, UPGRADE_HEIGHT);

		//write text
		graphics.drawText("Game Over", 90, 90, 55, 255, 255, 255);
		graphics.drawText("Defeat", 200, 650, 240, 100, 100, 100);
		graphics.drawText("Play Again", 55, 618, 575, 0, 0, 0);
		graphics.drawText("Main Menu", 55, 918, 575, 0, 0, 0);

		graphics.drawText("Stats", 55, 265, 170, 255, 255, 255);

		graphics.drawText("Waves Completed: ", 30, 160, 240, 255, 255, 255);  graphics.drawText(to_string(data.waveCount-1).c_str(), 30, 340, 240, 255, 255, 255);
		graphics.drawText("Enemies Killed: ", 30, 160, 270, 255, 255, 255);	  graphics.drawText(to_string(data.killedTotal).c_str(), 30, 340, 270, 255, 255, 255);
		graphics.drawText("Points Earned: ", 30, 160, 300, 255, 255, 255);	  graphics.drawText(to_string(data.points).c_str(), 30, 340, 300, 255, 255, 255);
		graphics.drawText("Cash Earned: ", 30, 160, 330, 255, 255, 255);	  graphics.drawText(to_string(data.moneyTotal).c_str(), 30, 340, 330, 255, 255, 255);
		graphics.drawText("Accuracy: ", 30, 160, 360, 255, 255, 255);		  graphics.drawText(getPercentage(data.shotsHit, data.shotsFired).c_str(), 30, 340, 360, 255, 255, 255);

		displayQuote();

		graphics.flip();
	}

private:
	Background background;
	Graphics graphics;
};

#endif