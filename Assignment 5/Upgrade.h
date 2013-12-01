#ifndef UPGRADE_H
#define UPGRADE_H

#include "SDL.h"
#include "SDL_TTF.h"
#include "Graphics.h"
#include "Game.h"

using namespace std;

class Upgrade{
public:

	Upgrade() {

	};

	void drawUpgradeScreen(){
				//setup screen
		graphics.drawBackground("Images/bg.bmp");

		//write text  
		graphics.drawText("Upgrade Test Page", 80, 250, 180, 0, 0, 0);
		graphics.drawText("Click Anywhere to Continue", 80, 250, 260, 0, 0, 0);


		graphics.flip();
	}


private:
	Graphics graphics;
};

#endif