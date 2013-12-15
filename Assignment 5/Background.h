#ifndef Background_H
#define Background_H

#include "Graphics.h"

class Background {
	private:
		Graphics graphics; 
		string* skyPath;
		bool down;
		int skyIndex,
			skyPos_1,
			skyPos_2,
			lastMove;
		static const int BG_WIDTH = 1280,
			BG_HEIGHT = 720,
			SKY_WIDTH = 1280,
			SKY_HEIGHT = 138,
			SKY_START = 0,
			TICKS_PER_MOVE = 0,
			DAY_DELAY = -150,
			SLIDE_COUNT = 8,
			SUN_DOWN_Y = -50,
			SUN_DOWN_X = 100,
			SUN_down_Y = SKY_HEIGHT - 50,
			SUN_down_X = 1000;
		
		void moveSky();
		void movePlanets();
		void moveEnemies();

	public:
		static const enum calledFrom {MAIN, GAME, UPGRADE, DEFEAT};

		Background(int = 0);
		~Background();
		void display(int);
		void reset();
};

Background::Background(int i) {
	reset();

	skyPath = new string[SLIDE_COUNT];
		skyPath[0] = "Images/Background/sky_1.bmp";
		skyPath[1] = "Images/Background/sky_2.bmp";
		skyPath[2] = "Images/Background/sky_3.bmp";
		skyPath[3] = "Images/Background/sky_4.bmp";
		skyPath[4] = "Images/Background/sky_5.bmp";
		skyPath[5] = "Images/Background/sky_6.bmp";
		skyPath[6] = "Images/Background/sky_7.bmp";
		skyPath[7] = "Images/Background/sky_8.bmp";
}

Background::~Background() {
	delete [] skyPath;
}

/* Game::launchWave cannot use moveSky() and movePlanets() because it too computationally expensive */
void Background::display(int from) {
	if (from == MAIN) {
		moveSky();
		movePlanets();
		graphics.displaySprite("Images/Background/bg_default.bmp",0,0,0,0,BG_WIDTH,BG_HEIGHT);
		moveEnemies();
	} else if (from == GAME) {
		graphics.drawBackground("Images/Background/bg_game.bmp");
	} else if (from == UPGRADE) {
		graphics.displaySprite("Images/Background/sky_7.bmp", 0, 0, 0, 0, SKY_WIDTH, SKY_HEIGHT);
		graphics.displaySprite("Images/Background/bg_upgrade.bmp",0,0,0,0,BG_WIDTH,BG_HEIGHT);
	} else if (from == DEFEAT) {
		graphics.displaySprite("Images/Background/sky_defeat.bmp", 0, 0, 0, 0, SKY_WIDTH, SKY_HEIGHT);
		graphics.displaySprite("Images/Background/bg_defeat.bmp",0,0,0,0,BG_WIDTH,BG_HEIGHT);
	}
}

void Background::moveSky() {	
	if (down) {
		graphics.displaySprite(skyPath[skyIndex].c_str(), 0, 0 - (lastMove == TICKS_PER_MOVE ? ++skyPos_1 : skyPos_1), 0, 0, SKY_WIDTH, SKY_HEIGHT);
		graphics.displaySprite(skyPath[skyIndex+1].c_str(), 0, 0 - (lastMove == TICKS_PER_MOVE ? ++skyPos_2 : skyPos_2), 0, 0, SKY_WIDTH, SKY_HEIGHT);

		lastMove = (lastMove == TICKS_PER_MOVE ? 0 : lastMove + 1);

		if (skyPos_2 == 0) {
			++skyIndex;
			if (skyIndex == SLIDE_COUNT-1) {
				down = false;
				lastMove = DAY_DELAY;
			} else {
				skyPos_1 = 0;
				skyPos_2 = -SKY_HEIGHT;
			}
		} 
	} else {
		graphics.displaySprite(skyPath[skyIndex-1].c_str(), 0, 0 - (lastMove == TICKS_PER_MOVE ? --skyPos_1 : skyPos_1), 0, 0, SKY_WIDTH, SKY_HEIGHT);
		graphics.displaySprite(skyPath[skyIndex].c_str(), 0, 0 - (lastMove == TICKS_PER_MOVE ? --skyPos_2 : skyPos_2), 0, 0, SKY_WIDTH, SKY_HEIGHT);

		lastMove = (lastMove == TICKS_PER_MOVE ? 0 : lastMove + 1);

		if (skyPos_2 == -SKY_HEIGHT) {
			--skyIndex;
			if (skyIndex == 0) {
				down = true;
				lastMove = DAY_DELAY;
			} else {
				skyPos_1 = SKY_HEIGHT;
				skyPos_2 = 0;
			}
		}
	}
}

void Background::movePlanets() {
	static int sunX, sunY;
	static bool flag = true, move = true;

	if(skyIndex >= 2 && skyIndex <= 4) { //Sun Movement
		if (down) {
			if (flag) {
				sunX = SUN_DOWN_X;
				sunY = SUN_DOWN_Y;
				flag = false;
			}
		
			if (move) {
				++sunY;
				move = false;
			} else {
				move = true;
			}
		} else { //(!down)
			if(!flag) {
				sunX = SUN_down_X;
				sunY = SUN_down_Y;
				flag = true;
			}
			if (move) {
				--sunY;
				move = false;
			} else {
				move = true;
			}
		}
		graphics.displaySprite("Images/Background/sun.bmp",0,0,sunX,sunY,56,51);
	} else if(skyIndex == 7) { //Moon movement
	
	}
}

void Background::moveEnemies() {

}

void Background::reset() {
	down = true;
	lastMove = -25;
	skyIndex = 0;
	skyPos_1 = 0;
	skyPos_2 = -SKY_HEIGHT;
}

#endif