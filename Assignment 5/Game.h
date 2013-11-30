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

    Game() {

    };

    Graphics graphics;
    Enemy enemy;
    Castle castle; // now holds variables specific to the type of wall being used ( health cap, current health, offensive castle stats, .bmp path location )
    Gun gun;
	Data data;     // holds game variables

    //initialize game screen

    void setupGame() {

        graphics.drawBackground("Images/bg.bmp"); //sets background

        castle.drawCastle(); //places castle

        gun.drawGuns();

        enemy.drawEnemies(); //testing
    }

    void runGame() {
        bool gameRunning = true;
        bool fireBullet = false;
        SDL_Event event;

		/***********************************************************
		// For the actual game loop, what do you guys think of :
		
		// move fireBullet, mouseX, mouseY, event to a function called launchWave
		bool stillPlaying = true;
		bool gameRunning = true;

		while(stillPlaying) {
			stillPlaying = launchMainMenu();

			if( stillPlaying ) { // For if the player plays more than one game in a row
				resetData(); // resets values in data
			}

			for(int i = 1; stillPlaying && gameRunning; ++i) {
				gameRunning = launchWave( i ); // return false if player looses wave
											   // wave money bonus can be added if all enemies are killed in a wave
				if ( gameRunning ) {
					upgradeMenu(); 
				} else {
					defeatDisplay(); // We could do something simple like dispaly a screen that says "You Have Lost" - while displaying final player stats.
					                 // The only interaction the player has with this screen is to press a "Continue" button which ends that function, subsequently this
									 // would return them to the main menue function
				}
			}
		}
		************************************************************/

        //game loop
		for(int i=0; i<5; i++){
			enemy.createEnemy(1,1);
		}

        while (gameRunning) {
			graphics.clearScreen();
			draw();
			enemy.moveEnemy();
            if (SDL_PollEvent(&event)) { //check for new event
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    //If the left mouse button was pressed
                    if (event.button.button == SDL_BUTTON_LEFT) {
						gun.createBullet(event.button.x, event.button.y);
                        fireBullet = true;
                    }
                }
            }

            if (fireBullet) {				
                if (!gun.fireGuns()) fireBullet = false;
				for(int i=0; i<gun.bullets.size();i++){
					if(detectHit(gun.bullets[i]->x,gun.bullets[i]->y,BULLET_WIDTH, BULLET_HEIGHT)){
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
    }

    void draw() {
        graphics.drawBackground("Images/bg.bmp"); //sets background

		castle.drawCastle(data.wallDefUpgrades, data.wallOffUpgrades);	//places castle

		graphics.displaySprite("Images/statsbar.bmp",0,0,0,0,1280,50);

        enemy.drawEnemies();

        gun.drawGuns();
    }

	bool detectHit(double x, double y, int width, int height){
		if(enemy.detectHit(x,y,width,height)) return true;

		else return false;
	}
};

#endif