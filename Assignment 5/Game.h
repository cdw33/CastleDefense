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

    //graphics.drawBackground("Images/bg_new_1.bmp"); //sets background
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
	vector<int> spawnTime;
	bool gameRunning = true;
    bool fireBullet = false;
	bool roundWin = false;
	int lastShot = clock() - bulletValRef.getRateOfFire(data.rateOfFire);
	int startOfWave = clock();

	const int ENEMIES_PER_WAVE = 5;
	
	background.reset();
	enemyCount = waveNumber * ENEMIES_PER_WAVE;
	data.health = castle.setHealth(data.wallDefUpgrades);
	enemy.generateSpawnTime(spawnTime, waveNumber, ENEMIES_PER_WAVE);	

	//game loop
    while (gameRunning) {
		drawWave();
		enemy.moveEnemy(data, castle.offInfo[data.wallOffUpgrades].damage);

		while(spawnTime.size() != 0 && spawnTime[spawnTime.size()-1] < clock() - startOfWave) {
			spawnTime.erase(spawnTime.begin() + spawnTime.size() - 1);
			enemy.createEnemy(1 + waveNumber, 1 + waveNumber/4, (rand()%2 ? 3 : 4) + waveNumber/5, 1000); /* Damage, hp, speed, attack rate (in ms) */ /* <- speed increases every 5 rounds */
		}

        if (SDL_PollEvent(&event)) { //check for new event
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                //If the left mouse button was pressed
				if (event.button.button == SDL_BUTTON_LEFT && clock() - lastShot >= bulletValRef.getRateOfFire(data.rateOfFire)) {
					gun.createBullet(event.button.x, event.button.y, data.bulletUpgrades);
                    fireBullet = true;
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
				}
			}
        }

		if (enemy.noEnemies() && spawnTime.size() == 0) {
			gameRunning = false;
			roundWin = true;
			data.killed=0;
			data.addMoney(waveNumber * 5);
			if(waveNumber >= 3) {
				data.addMoney(20);
			}
			if(waveNumber >= 7) {
				data.addMoney(35);
			}
			if(waveNumber >= 11) {
				data.addMoney(60);
			}
			if(waveNumber >= 15) {
				data.addMoney(90);
			}
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