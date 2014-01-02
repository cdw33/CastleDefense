#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_TTF.h"

#include "Background.h"
#include "Bullet.h"
#include "Castle.h"
#include "Data.h"
#include "DefeatScreen.h"
#include "Enemy.h"
#include "Gun.h"
#include "Graphics.h"
#include "Upgrade.h"

#include <string>

using namespace std;

class Game {
	public:
		Background background;
		Bullet bulletValRef;
		Castle castle; 
		Data data;     
	    DefeatScreen defeat;
		Enemy enemy;
		Gun gun;
		Graphics graphics;
		Upgrade upgrade;

		int enemyCount;
    
		Game();
		void setupGame(); //initialize game screen
		void runGame();
		bool launchWave(int);
		void waveBonus(int);
		void upgradeMenu();
		void defeatDisplay(bool&);
		void clearObjects();
		void drawWave();
		void drawUpdateMenu();
		bool detectHit(double, double, int, int, int);
		void updateStatsBar();
};

//***************************************************
// Constructor
//***************************************************
Game::Game() {
	srand(time(0));
};

//***************************************************
// setupGame - initialize game screen
//***************************************************
void Game::setupGame() {
	background.display(Background::GAME);

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

	for(data.waveCount = 1; gameRunning; ++data.waveCount) {
		/* uncomment for more money for easy testing / game demonstration purposes
			data.money = 1000000;
		*/

		gameRunning = launchWave(data.waveCount);

		if (gameRunning) {
			upgradeMenu();
		} else {
			defeatDisplay(gameRunning); 
		}		             
	}					    
}

//***************************************************
// launchWave
//***************************************************
bool Game::launchWave(int waveNumber) { 
    SDL_Event event;
	bool gameRunning = true;
    bool fireBullet = false;
	bool roundWin = false;
	int lastShot = clock() - bulletValRef.getRateOfFire(data.rateOfFire);
	int startOfWave = clock();

	const int ENEMY_WAVE_RATE = 2;
	
	background.reset();
	data.health = castle.setHealth(data.wallDefUpgrades);
	enemy.generateSpawnTime(waveNumber, ENEMY_WAVE_RATE);	

	/* The following should be adjusted to match what is found in Enemy::generateSpawnTime */ 
	/* The enemyCount calculation has become Convoluted, but it is this way so that minion */
	/* spawn rates will scale as the wave number increases                                 */
	enemyCount = /*Minions ->*/(waveNumber < 7 ? waveNumber * 2 : (waveNumber + max(1.0,(waveNumber/3) + 0.0)) * ENEMY_WAVE_RATE) + /*Wizards ->*/max(0.0, (waveNumber/2 - 1)+0.0); 

	//game loop
    while (gameRunning) {
		drawWave();
		enemy.moveEnemy(data, castle.offInfo[data.wallOffUpgrades].damage);
		enemy.spawnEnemies(startOfWave, waveNumber);

        if (SDL_PollEvent(&event)) { //check for new event
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                //If the left mouse button was pressed
				if (event.button.button == SDL_BUTTON_LEFT && clock() - lastShot >= bulletValRef.getRateOfFire(data.rateOfFire)) {
					gun.createBullet(event.button.x, event.button.y, data.bulletUpgrades);
                    fireBullet = true;
					++data.shotsFired;
					lastShot = clock();
                }
            }
        }

        if (fireBullet) {				
			if (!gun.fireGuns(data.bulletUpgrades)) fireBullet = false;
			for(int i=0; i<gun.bullets.size();i++){
				if(detectHit(gun.bullets[i]->x,gun.bullets[i]->y, bulletValRef.getWidth(data.bulletUpgrades), bulletValRef.getHeight(data.bulletUpgrades), gun.bullets[i]->id)){
					if (bulletValRef.stopOnContact(data.bulletUpgrades)) {
						gun.deleteBullet(i);
					}
					--i; /* avoids skipping elements in the array if an element is deleted, and allows for an unstoppable bullet to damage more than one enemy per draw */
				}
			}
        }

		if (enemy.noEnemies() && enemy.noSpawns()) {
			gameRunning = false;
			roundWin = true;
			data.killed=0;
			waveBonus(waveNumber);
		} else if (data.health <= 0) {
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
// waveBonus
//***************************************************
void Game::waveBonus(int waveNumber) {
	data.addMoney(waveNumber * 5);

	/* The following statements allow the player to make purchases        */
	/*  after compleating certain waves as they would be short just a few */
	/*  dollars without this boost                                        */
	if (waveNumber == 1) {
		data.addMoney(3);
	} else if (waveNumber == 2) {
		data.addMoney(2);
	} else if (waveNumber == 4) {
		data.addMoney(1);
	} else if (waveNumber == 7) {
		data.addMoney(1);
	}

	/* Old bonus waveset */
	/*if (waveNumber >= 3) {
		data.addMoney(10);
	}else if (waveNumber >= 7) {
		data.addMoney(20);
	} else if (waveNumber >= 11) {
		data.addMoney(30);
	} else if (waveNumber >= 15) {
		data.addMoney(40);
	}*/
}

//***************************************************
// upgradeMenu
//***************************************************
void Game::upgradeMenu() {
	upgrade.upgradeMenu(data, castle);
}

//***************************************************
// defeatDisplay
//***************************************************
void Game::defeatDisplay(bool &skipMenu) {
	defeat.drawDefeatScreen(data, skipMenu);
}

//***************************************************
// clearObjects
//***************************************************
void Game::clearObjects() {
	gun.deleteBullets();
	enemy.deleteEnemies();
	enemy.deleteSpawnTimes();
}

//***************************************************
// drawWave
//***************************************************
void Game::drawWave() {
    //graphics.drawBackground("Images/bg_new_1.bmp"); //sets background
	background.display(Background::GAME);

	castle.drawCastle(data.wallDefUpgrades, data.wallOffUpgrades);	//places castle

	graphics.displaySprite("Images/statsbar.bmp",0,0,0,0,1280,50);

    enemy.drawEnemies();

    gun.drawGuns();

	updateStatsBar();
}

//***************************************************
// detectHit
//***************************************************
bool Game::detectHit(double x, double y, int width, int height, int id){
		if(enemy.detectHit(x, y, width, height, id, data)) return true;

		else return false;
}

//***************************************************
// updateStatsBar
//***************************************************
void Game::updateStatsBar(){

	//TODO - make xCoors static
	graphics.drawText("Wave: ", 35, 10, 3, 255, 255, 255); 
	graphics.drawText("Points: ", 35, 160, 3, 255, 255, 255); 
	graphics.drawText("Enemies Remaining: ", 35, 370, 3, 255, 255, 255); 
	graphics.drawText("Money: ", 35, 700, 3, 255, 255, 255); 
	graphics.drawText("Castle Health: ", 35, 880, 3, 255, 255, 255); 

	//pull data
	graphics.drawText(to_string(data.waveCount).c_str(), 35, 80, 3, 255, 255, 255); 
	graphics.drawText(to_string(data.points).c_str(), 35, 245, 3, 255, 255, 255); 
	graphics.drawText(to_string(enemyCount - data.killed).c_str(), 35, 600, 3, 255, 255, 255); 
	graphics.drawText(to_string(data.money).c_str(), 35, 790, 3, 255, 255, 255); 
	graphics.drawText(to_string(data.health).c_str(), 35, 1040, 3, 255, 255, 255); 
}


#endif