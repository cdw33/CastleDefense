#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_TTF.h"

#include "Bullet.h"
#include "Castle.h"
#include "Data.h"
#include "Enemy.h"
#include "Gun.h"
#include "Graphics.h"
#include "Upgrade.h"
#include "DefeatScreen.h"

#include <string>

using namespace std;

class Game {
	public:
		Graphics graphics;
		Enemy enemy;
		Castle castle; // now holds variables specific to the type of wall being used ( health cap, offensive castle stats, .bmp path location )
		Gun gun;
		Data data;     // holds game variables
		Upgrade upgrade;
	    DefeatScreen defeat;
    
		Game();
		void setupGame(); //initialize game screen
		void runGame();
		bool launchWave(int);
		void upgradeMenu();
		void defeatDisplay();
		void clearObjects();
		void drawWave();
		void drawUpdateMenu();
		bool detectHit(double, double, int, int);
		void updateStatsBar();
};

//***************************************************
// Constructor
//***************************************************
Game::Game() {

};

//***************************************************
// setupGame - initialize game screen
//***************************************************
void Game::setupGame() {

    graphics.drawBackground("Images/bg.bmp"); //sets background

    castle.drawCastle(); //places castle

    gun.drawGuns();

    enemy.drawEnemies(); //testing
}

//***************************************************
// runGame
//***************************************************
void Game::runGame() {
	bool gameRunning = true;
	data.resetData();

	for(int i = 1; gameRunning; ++i) {
		gameRunning = launchWave(i); // return false if player looses wave, wave money bonus can be added if all enemies are killed in a wave
		if(data.waveCount == 1) gameRunning = false;					
		if (gameRunning) {
			upgradeMenu(); /* no way to exit yet */
			data.waveCount++;
		} else {
			defeatDisplay(); // We could do something simple like dispaly a screen that says "You Have Lost" - while displaying final player stats.
		}		             // The only interaction the player has with this screen is to press a "Continue" button which ends that function, subsequently this
	}					     // would return them to the main menue function
}

//***************************************************
// launchWave
//***************************************************
bool Game::launchWave(int waveNumber) { // difficulty by wave number still needs implimented, so does enemy spawning, and win / loss conditions
	Bullet valRef;
    SDL_Event event;
	bool gameRunning = true;
    bool fireBullet = false;
	bool roundWin = false;
	int lastShot = clock() - valRef.getRateOfFire(data.rateOfFire);
	
	data.health = castle.setHealth(data.wallDefUpgrades);

	for(int i=0; i<5*waveNumber; i++){ // enemies need scattered
		enemy.createEnemy(1,1,3);
	}

	//game loop
    while (gameRunning) {
		graphics.clearScreen();
		drawWave();
		enemy.moveEnemy();
        if (SDL_PollEvent(&event)) { //check for new event
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                //If the left mouse button was pressed
				if (event.button.button == SDL_BUTTON_LEFT && clock() - lastShot >= valRef.getRateOfFire(data.rateOfFire)) {
					gun.createBullet(event.button.x, event.button.y, data.bulletUpgrades);
                    fireBullet = true;
					lastShot = clock();
                }
            }
        }

        if (fireBullet) {				
			if (!gun.fireGuns(data.bulletUpgrades)) fireBullet = false;
			for(int i=0; i<gun.bullets.size();i++){
				if(detectHit(gun.bullets[i]->x,gun.bullets[i]->y, valRef.getWidth(data.bulletUpgrades), valRef.getHeight(data.bulletUpgrades))){
					gun.deleteBullet(i);
				}
			}
        }


		if (enemy.noEnemies()) {
			gameRunning = false;
			roundWin = true;
			data.money += waveNumber * 5; /* wave bonus */
		} else if (data.health == 0) {
			gameRunning = false;
			roundWin = false;
		} else if (event.type == SDL_QUIT) { /* event quit */
			SDL_Quit();
			exit(0);
        }

		graphics.flip();
    }

	clearObjects();
	return (roundWin ? true : false);
}

//***************************************************
// upgradeMenu
//***************************************************
void Game::upgradeMenu() {
	bool shopping = true;
	Bullet bulletValRef;
	SDL_Event event;
	const int NEED_VAL = -100;

	while (shopping) {
		drawUpdateMenu();

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) { /* The different clickable events */

				//printf("Location ->  x: %i   y: %i \n", event.button.x, event.button.y);

				/* Wall defense upgrades */
				if ((event.button.x < NEED_VAL && event.button.x > NEED_VAL) && (event.button.y < NEED_VAL && event.button.y > NEED_VAL)) {
					if(data.money >= castle.defInfo[data.wallDefUpgrades].cost && data.wallDefUpgrades < castle.totaldefenceUpgrades()) {
						data.money -= castle.defInfo[data.wallDefUpgrades].cost;
						++data.wallDefUpgrades;
					}
				/* Wall offense upgrades */
				} else if ((event.button.x < NEED_VAL && event.button.x > NEED_VAL)  &&  (event.button.y < NEED_VAL && event.button.y > NEED_VAL)) {
					if(data.money >= castle.offInfo[data.wallOffUpgrades].cost && data.wallOffUpgrades < castle.totalOffenceUpgrades()) {
						data.money -= castle.offInfo[data.wallOffUpgrades].cost;
						++data.wallOffUpgrades;
					}
				/* Bullet type upgrades */ 
				} else if ((event.button.x < NEED_VAL && event.button.x > NEED_VAL)  &&  (event.button.y < NEED_VAL && event.button.y > NEED_VAL)) {
					if(data.money >= bulletValRef.getCost(data.bulletUpgrades) && data.bulletUpgrades < bulletValRef.totalBulletUpgrades()) {
						data.money -= bulletValRef.getCost(data.bulletUpgrades);
						++data.bulletUpgrades;
					}
				/* Rate of fire upgrades */
				} else if ((event.button.x < NEED_VAL && event.button.x > NEED_VAL)  &&  (event.button.y < NEED_VAL && event.button.y > NEED_VAL)) {
					if(data.money >= bulletValRef.getRateOfFire(data.rateOfFire) && data.rateOfFire < bulletValRef.totalRateOfFireUpgrades()) {
						data.money -= bulletValRef.getRateOfFireCost(data.rateOfFire);
						++data.rateOfFire;
					}				
				/* Exit the function */
				} else if ((event.button.x < NEED_VAL && event.button.x > NEED_VAL)  &&  (event.button.y < NEED_VAL && event.button.y > NEED_VAL)) {
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
// defeatDisplay
//***************************************************
void Game::defeatDisplay() {
	defeat.drawDefeatScreen();
}

//***************************************************
// clearObjects
//***************************************************
void Game::clearObjects() {
	gun.deleteBullets();
	enemy.deleteEnemies();
}

//***************************************************
// drawWave
//***************************************************
void Game::drawWave() {
    graphics.drawBackground("Images/bg.bmp"); //sets background

	castle.drawCastle(data.wallDefUpgrades, data.wallOffUpgrades);	//places castle

	graphics.displaySprite("Images/statsbar.bmp",0,0,0,0,1280,50);

    enemy.drawEnemies();

    gun.drawGuns();

	updateStatsBar();
}

//***************************************************
// drawUpdateMenu
//***************************************************
void Game::drawUpdateMenu() {
	const int BAR_WIDTH = 79;
	const int UPGRADE_WIDTH = 1138;
	const int UPGRADE_HEIGHT = 599;

	graphics.drawBackground("Images/bg.bmp");

	graphics.displaySprite("Images/statsbar.bmp",0,0,0,0,1280,50);
	updateStatsBar();

	graphics.displaySprite("Images/upgrade_menu.bmp", 0, 0, GAME_WIDTH/2 - UPGRADE_WIDTH/2, GAME_HEIGHT/2 - UPGRADE_HEIGHT/2 + 15, UPGRADE_WIDTH, UPGRADE_HEIGHT);

	/* Draw text */
	graphics.drawText("Upgrades", 90, 90, 55, 255, 255, 255);
	graphics.drawText("Buy", 40, 118, 206, 0, 0, 0);
	graphics.drawText("Buy", 40, 118, 316, 0, 0, 0);
	graphics.drawText("Buy", 40, 118, 426, 0, 0, 0);
	graphics.drawText("Buy", 40, 118, 535, 0, 0, 0);
	graphics.drawText("Castle Wall", 40, 247, 204, 0, 0, 0);
	graphics.drawText("Castle Defences", 40, 217, 316, 0, 0, 0);
	graphics.drawText("Bullets", 40, 269, 426, 0, 0, 0);
	graphics.drawText("Rate of Fire", 40, 242, 535, 0, 0, 0);
	//graphics.drawText("anInteger", 40, 100, 100, 0, 0, 0);
	//graphics.drawText("anInteger", 40, 100, 100, 0, 0, 0);
	//graphics.drawText("anInteger", 40, 100, 100, 0, 0, 0);
	//graphics.drawText("anInteger", 40, 100, 100, 0, 0, 0);
	graphics.drawText("Launch Wave", 40, 1015, 602, 0, 0, 0);
	
	data.wallDefUpgrades = 7;
	data.wallOffUpgrades = 7;
	data.bulletUpgrades = 7;
	data.rateOfFire = 7;

	/* Draw upgrade progress squares */
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

	graphics.flip();
}

//***************************************************
// detectHit
//***************************************************
bool Game::detectHit(double x, double y, int width, int height){
		if(enemy.detectHit(x,y,width,height,data.bulletUpgrades)) return true;

		else return false;
}

//***************************************************
// updateStatsBar
//***************************************************
void Game::updateStatsBar(){

	//TODO - make xCoors static
	graphics.drawText("Wave: ", 35, 10, 3, 255, 255, 255); 
	graphics.drawText("Points: ", 35, 160, 3, 255, 255, 255); 
	graphics.drawText("Enemies Killed: ", 35, 370, 3, 255, 255, 255); 
	graphics.drawText("Enemies Remaining: ", 35, 700, 3, 255, 255, 255); 
	graphics.drawText("Money: ", 35, 1080, 3, 255, 255, 255); 


	//debugging data
	graphics.drawText(to_string(data.waveCount).c_str(), 35, 80, 3, 255, 255, 255); 
	graphics.drawText("584", 35, 245, 3, 255, 255, 255); 
	graphics.drawText("125", 35, 540, 3, 255, 255, 255); 
	graphics.drawText("654", 35, 930, 3, 255, 255, 255); 
	graphics.drawText("545", 35, 1170, 3, 255, 255, 255); 


}


#endif