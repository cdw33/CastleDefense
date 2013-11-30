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

using namespace std;

class Game {
	public:
		Graphics graphics;
		Enemy enemy;
		Castle castle; // now holds variables specific to the type of wall being used ( health cap, offensive castle stats, .bmp path location )
		Gun gun;
		Data data;     // holds game variables
    
		Game();
		void setupGame(); //initialize game screen
		void runGame();
		bool launchWave(int);
		void upgradeMenu();
		void defeatDisplay();
		void draw();
		bool detectHit(double, double, int, int);
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
		gameRunning = launchWave( i ); // return false if player looses wave, wave money bonus can be added if all enemies are killed in a wave
										
		if ( gameRunning ) {
			upgradeMenu(); 
		} else {
			defeatDisplay(); // We could do something simple like dispaly a screen that says "You Have Lost" - while displaying final player stats.
		}		             // The only interaction the player has with this screen is to press a "Continue" button which ends that function, subsequently this
	}					     // would return them to the main menue function
}

//***************************************************
// launchWave
//***************************************************
bool Game::launchWave(int waveNumber) { // difficulty by wave number still needs implimented, so does attacking, and win / loss conditions
	bool gameRunning = true;
    bool fireBullet = false;
	Bullet valRef;
    SDL_Event event;
	
	data.health = castle.setHealth(data.wallDefUpgrades);

	for(int i=0; i<5; i++){
		enemy.createEnemy(1,1);
	}

	//game loop
    while (gameRunning) {
		graphics.clearScreen();
		draw();
		enemy.moveEnemy();
        if (SDL_PollEvent(&event)) { //check for new event
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                //If the left mouse button was pressed
                if (event.button.button == SDL_BUTTON_LEFT) {
					gun.createBullet(event.button.x, event.button.y, data.bulletUpgrades);
                    fireBullet = true;
                }
            }
        }

        if (fireBullet) {				
			if (!gun.fireGuns(data.bulletUpgrades)) fireBullet = false;
			for(int i=0; i<gun.bullets.size();i++){
				if(detectHit(gun.bullets[i]->x,gun.bullets[i]->y, valRef.getWidth(data.bulletUpgrades), valRef.getHeight(data.bulletUpgrades))){
					enemy.deleteEnemy(i);
				}
			}
        }

        //exit event
        if (event.type == SDL_QUIT) {
            gameRunning = false;
        }

		graphics.flip();
    }

	return true;
}

//***************************************************
// upgradeMenu
//***************************************************
void Game::upgradeMenu() {
	bool shopping = true;
	Bullet bulletValRef;
	SDL_Event event;
	const int NEED_VAL = 0;

	while (shopping) {
		graphics.clearScreen();
		//display upgradeMenu .bmp
		draw();

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) { /* The different clickable events */

				/* Wall defense upgrades */
				if ((event.button.x < NEED_VAL && event.button.x > NEED_VAL) && (event.button.y < NEED_VAL && event.button.y > NEED_VAL)) {
					if(data.money >= castle.defInfo[data.wallDefUpgrades].cost && data.wallDefUpgrades <= castle.totaldefenceUpgrades()) {
						data.money -= castle.defInfo[data.wallDefUpgrades].cost;
						++data.wallDefUpgrades;
					}
				/* Wall offense upgrades */
				} else if ((event.button.x < NEED_VAL && event.button.x > NEED_VAL)  &&  (event.button.y < NEED_VAL && event.button.y > NEED_VAL)) {
					if(data.money >= castle.offInfo[data.wallOffUpgrades].cost && data.wallOffUpgrades <= castle.totalOffenceUpgrades()) {
						data.money -= castle.offInfo[data.wallOffUpgrades].cost;
						++data.wallOffUpgrades;
					}
				/* Bullet type upgrades */ 
				} else if ((event.button.x < NEED_VAL && event.button.x > NEED_VAL)  &&  (event.button.y < NEED_VAL && event.button.y > NEED_VAL)) {
					if(data.money >= bulletValRef.getCost(data.bulletUpgrades) && data.bulletUpgrades <= bulletValRef.totalBulletUpgrades()) {
						data.money -= bulletValRef.getCost(data.bulletUpgrades);
						++data.bulletUpgrades;
					}
				/* Rate of fire upgrades */
				} else if ((event.button.x < NEED_VAL && event.button.x > NEED_VAL)  &&  (event.button.y < NEED_VAL && event.button.y > NEED_VAL)) {
					// Need to find a place to keep rate of fire incremental values
				/* Exit the function */
				} else if ((event.button.x < NEED_VAL && event.button.x > NEED_VAL)  &&  (event.button.y < NEED_VAL && event.button.y > NEED_VAL)) {
					shopping = false; /* Ends function to launch next wave */
				} 
			}
		}
	}
}

//***************************************************
// defeatDisplay
//***************************************************
void Game::defeatDisplay() {

}

//***************************************************
// draw
//***************************************************
void Game::draw() {
    graphics.drawBackground("Images/bg.bmp"); //sets background

	castle.drawCastle(data.wallDefUpgrades, data.wallOffUpgrades);	//places castle

	graphics.displaySprite("Images/statsbar.bmp",0,0,0,0,1280,50);

    enemy.drawEnemies();

    gun.drawGuns();
}

//***************************************************
// detectHit
//***************************************************
bool Game::detectHit(double x, double y, int width, int height){
	return enemy.detectHit(x,y,width,height, data.bulletUpgrades);
}

#endif