#ifndef UPGRADE_H
#define UPGRADE_H

#include "SDL.h"
#include "SDL_TTF.h"
#include "Graphics.h"
#include "Game.h"
#include "string"

using namespace std;

class Upgrade{
	private:
		Graphics graphics;
		Background background;
		Bullet bulletValRef;

	public:
		Upgrade()  { }
		~Upgrade() { }

		void upgradeMenu(Data &, Castle &);
		void drawUpdateMenu(Data &, Castle &);
		void Upgrade::updateStatsBar(Data &);
};

//***************************************************
// upgradeMenu
//***************************************************
void Upgrade::upgradeMenu(Data &data, Castle &castle) {
	bool shopping = true;
	SDL_Event event;
	background.reset();

	data.health = castle.setHealth(data.wallDefUpgrades);

	while (shopping) {
		drawUpdateMenu(data, castle);

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) { /* The different clickable events */

				/* Wall defense upgrades */
				if ((event.button.x < 173 && event.button.x > 108) && (event.button.y < 255 && event.button.y > 193)) {
					if(data.money >= castle.defInfo[data.wallDefUpgrades+1].cost && data.wallDefUpgrades < castle.totaldefenceUpgrades()) {
						data.money -= castle.defInfo[data.wallDefUpgrades+1].cost;
						++data.wallDefUpgrades;
						data.health = castle.setHealth(data.wallDefUpgrades);
					}
				/* Wall offense upgrades */
				} else if ((event.button.x < 173 && event.button.x > 108)  &&  (event.button.y < 366 && event.button.y > 303)) {
					if(data.money >= castle.offInfo[data.wallOffUpgrades+1].cost && data.wallOffUpgrades < castle.totalOffenceUpgrades()) {
						data.money -= castle.offInfo[data.wallOffUpgrades+1].cost;
						++data.wallOffUpgrades;
					}
				/* Bullet type upgrades */ 
				} else if ((event.button.x < 173 && event.button.x > 108)  &&  (event.button.y < 476 && event.button.y > 413)) {
					if(data.money >= bulletValRef.getCost(data.bulletUpgrades+1) && data.bulletUpgrades < bulletValRef.totalBulletUpgrades()) {
						data.money -= bulletValRef.getCost(data.bulletUpgrades+1);
						++data.bulletUpgrades;
					}
				/* Rate of fire upgrades */
				} else if ((event.button.x < 173 && event.button.x > 108)  &&  (event.button.y < 585 && event.button.y > 523)) {
					if(data.money >= bulletValRef.getRateOfFireCost(data.rateOfFire+1) && data.rateOfFire < bulletValRef.totalRateOfFireUpgrades()) {
						data.money -= bulletValRef.getRateOfFireCost(data.rateOfFire+1);
						++data.rateOfFire;
					}
				/* Exit the function */
				} else if ((event.button.x < 1204 && event.button.x > 988)  &&  (event.button.y < 650 && event.button.y > 590)) {
					shopping = false;
				} 
			} else if (event.type == SDL_QUIT) { /* event quit */
				SDL_Quit();
				exit(0);
			}
		}
	}
}

//***************************************************
// drawUpdateMenu
//***************************************************
void Upgrade::drawUpdateMenu(Data &data, Castle &castle) {
	const int 
		C1 = 255, 
		C2 = 48,
		BAR_WIDTH = 79,
		UPGRADE_WIDTH = 1138,
	    UPGRADE_HEIGHT = 599;


	background.display(Background::UPGRADE);

	graphics.displaySprite("Images/statsbar.bmp",0,0,0,0,1280,50);
	updateStatsBar(data); /* true denotes that you are calling it from this function */

	graphics.displaySprite("Images/upgrade_menu.bmp", 0, 0, GAME_WIDTH/2 - UPGRADE_WIDTH/2, GAME_HEIGHT/2 - UPGRADE_HEIGHT/2 + 15, UPGRADE_WIDTH, UPGRADE_HEIGHT);

	/* Draw text */
	graphics.drawText("Upgrades", 90, 90, 55, 255, 255, 255);
	graphics.drawText("Catagory", 40, 260, 145, 255, 255, 255);
	graphics.drawText("Cost", 40, 478, 145, 255, 255, 255);
	graphics.drawText("Progress", 40, 820, 145, 255, 255, 255);

	graphics.drawText("Buy", 40, 118, 206, 0, 0, 0);
	graphics.drawText("Buy", 40, 118, 316, 0, 0, 0);
	graphics.drawText("Buy", 40, 118, 426, 0, 0, 0);
	graphics.drawText("Buy", 40, 118, 535, 0, 0, 0);
	graphics.drawText("Castle Wall", 40, 247, 204, 0, 0, 0);
	graphics.drawText("Castle Defences", 40, 217, 316, 0, 0, 0);
	graphics.drawText("Bullets", 40, 269, 426, 0, 0, 0);
	graphics.drawText("Rate of Fire", 40, 242, 535, 0, 0, 0);
	graphics.drawText("Launch Wave", 40, 1015, 602, 0, 0, 0);
	
	if (data.wallDefUpgrades == castle.totaldefenceUpgrades()) {
		graphics.drawText("MAX", 40, 484, 206, 0, 0, 0);
	} else {
		graphics.drawText(to_string(castle.defInfo[data.wallDefUpgrades+1].cost).c_str(), 40, 487, 206, 0, 0, 0);
	}
	if (data.wallOffUpgrades == castle.totalOffenceUpgrades()) {
		graphics.drawText("MAX", 40, 484, 316, 0, 0, 0);
	} else {
		graphics.drawText(to_string(castle.offInfo[data.wallOffUpgrades+1].cost).c_str(), 40, 487, 316, 0, 0, 0);
	}
	if (data.bulletUpgrades == bulletValRef.totalBulletUpgrades()) {
		graphics.drawText("MAX", 40, 484, 426, 0, 0, 0);
	} else {
		graphics.drawText(to_string(bulletValRef.getCost(data.bulletUpgrades+1)).c_str(), 40, 487, 426, 0, 0, 0);
	}
	if (data.rateOfFire == bulletValRef.totalRateOfFireUpgrades()) {
		graphics.drawText("MAX", 40, 484, 535, 0, 0, 0);
	} else {
		graphics.drawText(to_string(bulletValRef.getRateOfFireCost(data.rateOfFire+1)).c_str(), 40, 487, 535, 0, 0, 0);
	}


	/* Draw upgrade progress squares and current upgrade names */
	for(int i = 0; i < data.wallDefUpgrades; ++i) { // wall upgrades
		graphics.displaySprite("Images/buy_cover.bmp", 0, 0, 610 + i * BAR_WIDTH, 204, 76, 41);
	}
	for(int i = 0; i < data.wallOffUpgrades; ++i) { // wall offensive upgrades
		graphics.displaySprite("Images/buy_cover.bmp", 0, 0, 610 + i * BAR_WIDTH, 314, 76, 41);
	}
	for(int i = 0; i < data.bulletUpgrades; ++i) { // bullet upgrades
		graphics.displaySprite("Images/buy_cover.bmp", 0, 0, 610 + i * BAR_WIDTH, 424, 76, 41);
	}
	for(int i = 0; i < data.rateOfFire; ++i) { // rate of fire
		graphics.displaySprite("Images/buy_cover.bmp", 0, 0, 610 + i * BAR_WIDTH, 534, 76, 41);
	}


	/* Draw upgrade names over purchased squares */

	/* Wall Defense */
	if (data.wallDefUpgrades >= 1) 	graphics.drawText("wood", 20, 610 + 20, 204 + 20, (data.wallDefUpgrades == 1 ? C1 : C2), (data.wallDefUpgrades == 1 ? C1 : C2), (data.wallDefUpgrades == 1 ? C1 : C2));
	if (data.wallDefUpgrades >= 2) 	graphics.drawText("brick", 20, 610 + BAR_WIDTH * 1 + 20, 204 + 20, (data.wallDefUpgrades == 2 ? C1 : C2), (data.wallDefUpgrades == 2 ? C1 : C2), (data.wallDefUpgrades == 2 ? C1 : C2));
	if (data.wallDefUpgrades >= 3) 	graphics.drawText("iron", 20, 610 + BAR_WIDTH * 2 + 20, 204 + 20, (data.wallDefUpgrades == 3 ? C1 : C2), (data.wallDefUpgrades == 3 ? C1 : C2), (data.wallDefUpgrades == 3 ? C1 : C2));
	if (data.wallDefUpgrades >= 4) 	graphics.drawText("steel", 20, 610 + BAR_WIDTH * 3 + 20, 204 + 20, (data.wallDefUpgrades == 4 ? C1 : C2), (data.wallDefUpgrades == 4 ? C1 : C2), (data.wallDefUpgrades == 4 ? C1 : C2));
	if (data.wallDefUpgrades >= 5) 	graphics.drawText("mithril", 20, 610 + BAR_WIDTH * 4 + 15, 204 + 20, (data.wallDefUpgrades == 5 ? C1 : C2), (data.wallDefUpgrades == 5 ? C1 : C2), (data.wallDefUpgrades == 5 ? C1 : C2));
	if (data.wallDefUpgrades >= 6) 	graphics.drawText("diamond", 20, 610 + BAR_WIDTH * 5 + 10, 204 + 20, (data.wallDefUpgrades == 6 ? C1 : C2), (data.wallDefUpgrades == 6 ? C1 : C2), (data.wallDefUpgrades == 6 ? C1 : C2));
	if (data.wallDefUpgrades >= 7)	graphics.drawText("lonsdaleite", 20, 610 + BAR_WIDTH * 6 + 2, 204 + 20, (data.wallDefUpgrades == 7 ? C1 : C2), (data.wallDefUpgrades == 7 ? C1 : C2), (data.wallDefUpgrades == 7 ? C1 : C2));

	/* Wall Offense */
	if (data.wallOffUpgrades >= 1) 	graphics.drawText("stakes", 20, 610 + 17, 314 + 20, (data.wallOffUpgrades == 1 ? C1 : C2), (data.wallOffUpgrades == 1 ? C1 : C2), (data.wallOffUpgrades == 1 ? C1 : C2));
	if (data.wallOffUpgrades >= 2) {graphics.drawText("barbed", 20, 610 + BAR_WIDTH * 1 + 16, 314 + 5, (data.wallOffUpgrades == 2 ? C1 : C2), (data.wallOffUpgrades == 2 ? C1 : C2), (data.wallOffUpgrades == 2 ? C1 : C2));
									graphics.drawText("wire", 20, 610 + BAR_WIDTH * 1 + 22, 314 + 20, (data.wallOffUpgrades == 2 ? C1 : C2), (data.wallOffUpgrades == 2 ? C1 : C2), (data.wallOffUpgrades == 2 ? C1 : C2));}
	if (data.wallOffUpgrades >= 3) 	graphics.drawText("spikes", 20, 610 + BAR_WIDTH * 2 + 18, 314 + 20, (data.wallOffUpgrades == 3 ? C1 : C2), (data.wallOffUpgrades == 3 ? C1 : C2), (data.wallOffUpgrades == 3 ? C1 : C2));
	if (data.wallOffUpgrades >= 4) {graphics.drawText("poison", 20, 610 + BAR_WIDTH * 3 + 15, 314 + 5, (data.wallOffUpgrades == 4 ? C1 : C2), (data.wallOffUpgrades == 4 ? C1 : C2), (data.wallOffUpgrades == 4 ? C1 : C2));
									graphics.drawText("spikes", 20, 610 + BAR_WIDTH * 3 + 17, 314 + 20, (data.wallOffUpgrades == 4 ? C1 : C2), (data.wallOffUpgrades == 4 ? C1 : C2), (data.wallOffUpgrades == 4 ? C1 : C2));}
	if (data.wallOffUpgrades >= 5) 	graphics.drawText("lava", 20, 610 + BAR_WIDTH * 4 + 25, 314 + 20, (data.wallOffUpgrades == 5 ? C1 : C2), (data.wallOffUpgrades == 5 ? C1 : C2), (data.wallOffUpgrades == 5 ? C1 : C2));
	if (data.wallOffUpgrades >= 6) {graphics.drawText("lava", 20, 610 + BAR_WIDTH * 5 + 25, 314 + 5, (data.wallOffUpgrades == 6 ? C1 : C2), (data.wallOffUpgrades == 6 ? C1 : C2), (data.wallOffUpgrades == 6 ? C1 : C2));
									graphics.drawText("and spikes", 20, 610 + BAR_WIDTH * 5 + 4, 314 + 20, (data.wallOffUpgrades == 6 ? C1 : C2), (data.wallOffUpgrades == 6 ? C1 : C2), (data.wallOffUpgrades == 6 ? C1 : C2));}
	if (data.wallOffUpgrades >= 7) {graphics.drawText("electric", 20, 610 + BAR_WIDTH * 6 + 11, 314 + 5, (data.wallOffUpgrades == 7 ? C1 : C2), (data.wallOffUpgrades == 7 ? C1 : C2), (data.wallOffUpgrades == 7 ? C1 : C2));
									graphics.drawText("fence", 20, 610 + BAR_WIDTH * 6 + 19, 314 + 20, (data.wallOffUpgrades == 7 ? C1 : C2), (data.wallOffUpgrades == 7 ? C1 : C2), (data.wallOffUpgrades == 7 ? C1 : C2));}

	/* Bullet Upgrades */
	if (data.bulletUpgrades >= 1) 	graphics.drawText("pea", 20, 610 + 26, 424 + 20, (data.bulletUpgrades == 1 ? C1 : C2), (data.bulletUpgrades == 1 ? C1 : C2), (data.bulletUpgrades == 1 ? C1 : C2));
	if (data.bulletUpgrades >= 2) 	graphics.drawText("rock", 20, 610 + BAR_WIDTH * 1 + 22, 424 + 20, (data.bulletUpgrades == 2 ? C1 : C2), (data.bulletUpgrades == 2 ? C1 : C2), (data.bulletUpgrades == 2 ? C1 : C2));
	if (data.bulletUpgrades >= 3) 	graphics.drawText("bullet", 20, 610 + BAR_WIDTH * 2 + 18, 424 + 20, (data.bulletUpgrades == 3 ? C1 : C2), (data.bulletUpgrades == 3 ? C1 : C2), (data.bulletUpgrades == 3 ? C1 : C2));
	if (data.bulletUpgrades >= 4) 	graphics.drawText("strong", 20, 610 + BAR_WIDTH * 3 + 15, 424 + 20, (data.bulletUpgrades == 4 ? C1 : C2), (data.bulletUpgrades == 4 ? C1 : C2), (data.bulletUpgrades == 4 ? C1 : C2));
	if (data.bulletUpgrades >= 5) 	graphics.drawText("large", 20, 610 + BAR_WIDTH * 4 + 22, 424 + 20, (data.bulletUpgrades == 5 ? C1 : C2), (data.bulletUpgrades == 5 ? C1 : C2), (data.bulletUpgrades == 5 ? C1 : C2));
	if (data.bulletUpgrades >= 6) 	graphics.drawText("uber", 20, 610 + BAR_WIDTH * 5 + 21, 424 + 20, (data.bulletUpgrades == 6 ? C1 : C2), (data.bulletUpgrades == 6 ? C1 : C2), (data.bulletUpgrades == 6 ? C1 : C2));
	if (data.bulletUpgrades >= 7)  {graphics.drawText("un-", 20, 610 + BAR_WIDTH * 6 + 25, 424 + 5, (data.bulletUpgrades == 7 ? C1 : C2), (data.bulletUpgrades == 7 ? C1 : C2), (data.bulletUpgrades == 7 ? C1 : C2));
									graphics.drawText("stoppable", 20, 610 + BAR_WIDTH * 6 + 6, 424 + 20, (data.bulletUpgrades == 7 ? C1 : C2), (data.bulletUpgrades == 7 ? C1 : C2), (data.bulletUpgrades == 7 ? C1 : C2));}

	/* Bullet Speed */
	if (data.rateOfFire >= 1) 	graphics.drawText("slow", 20, 610 + 22, 534 + 20, (data.rateOfFire == 1 ? C1 : C2), (data.rateOfFire == 1 ? C1 : C2), (data.rateOfFire == 1 ? C1 : C2));
	if (data.rateOfFire >= 2) 	graphics.drawText("fair", 20, 610 + BAR_WIDTH * 1 + 24, 534 + 20, (data.rateOfFire == 2 ? C1 : C2), (data.rateOfFire == 2 ? C1 : C2), (data.rateOfFire == 2 ? C1 : C2));
	if (data.rateOfFire >= 3) 	graphics.drawText("quick", 20, 610 + BAR_WIDTH * 2 + 20, 534 + 20, (data.rateOfFire == 3 ? C1 : C2), (data.rateOfFire == 3 ? C1 : C2), (data.rateOfFire == 3 ? C1 : C2));
	if (data.rateOfFire >= 4) 	graphics.drawText("fast", 20, 610 + BAR_WIDTH * 3 + 25, 534 + 20, (data.rateOfFire == 4 ? C1 : C2), (data.rateOfFire == 4 ? C1 : C2), (data.rateOfFire == 4 ? C1 : C2));
	if (data.rateOfFire >= 5)   graphics.drawText("light speed", 20, 610 + BAR_WIDTH * 4 + 1, 534 + 20, (data.rateOfFire == 5 ? C1 : C2), (data.rateOfFire == 5 ? C1 : C2), (data.rateOfFire == 5 ? C1 : C2));
	if (data.rateOfFire >= 6)  {graphics.drawText("ridiculous", 20, 610 + BAR_WIDTH * 5 + 4, 534 + 5, (data.rateOfFire == 6 ? C1 : C2), (data.rateOfFire == 6 ? C1 : C2), (data.rateOfFire == 6 ? C1 : C2));
								graphics.drawText("speed", 20, 610 + BAR_WIDTH * 5 + 18, 534 + 20, (data.rateOfFire == 6 ? C1 : C2), (data.rateOfFire == 6 ? C1 : C2), (data.rateOfFire == 6 ? C1 : C2));}
	if (data.rateOfFire >= 7)  {graphics.drawText("ludacris", 20, 610 + BAR_WIDTH * 6 + 11, 534 + 5, (data.rateOfFire == 7 ? C1 : C2), (data.rateOfFire == 7 ? C1 : C2), (data.rateOfFire == 7 ? C1 : C2));
								graphics.drawText("speed", 20, 610 + BAR_WIDTH * 6 + 18, 534 + 20, (data.rateOfFire == 7 ? C1 : C2), (data.rateOfFire == 7 ? C1 : C2), (data.rateOfFire == 7 ? C1 : C2));}
	
	graphics.flip();
}

//***************************************************
// updateStatsBar
//	Compleatly duplicated code from Game:: updateStatsBar (duplicate code is bad)
//  I have no idea how else this could be added 
//***************************************************
void Upgrade::updateStatsBar(Data &data) {

	//TODO - make xCoors static
	graphics.drawText("Wave: ", 35, 10, 3, 255, 255, 255); 
	graphics.drawText("Points: ", 35, 160, 3, 255, 255, 255); 
	graphics.drawText("Enemies Remaining: ", 35, 370, 3, 255, 255, 255); 
	graphics.drawText("Money: ", 35, 700, 3, 255, 255, 255); 
	graphics.drawText("Castle Health: ", 35, 880, 3, 255, 255, 255); 

	//pull data
	graphics.drawText(to_string(data.waveCount).c_str(), 35, 80, 3, 255, 255, 255); 
	graphics.drawText(to_string(data.points).c_str(), 35, 245, 3, 255, 255, 255); 
	graphics.drawText("~", 35, 600, 3, 255, 255, 255); 
	graphics.drawText(to_string(data.money).c_str(), 35, 790, 3, 255, 255, 255); 
	graphics.drawText(to_string(data.health).c_str(), 35, 1040, 3, 255, 255, 255); 
}


#endif