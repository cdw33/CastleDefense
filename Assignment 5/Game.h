#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_TTF.h"
#include "Graphics.h"
#include "Enemy.h"
#include "Castle.h"
#include "Bullet.h"
#include "Gun.h"

using namespace std;

class Game {
public:

    Game() {

    };

    Graphics graphics;
    Enemy enemy;
    Castle castle;
    Gun gun;

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
        int mouseX;
        int mouseY;
        SDL_Event event;

        //game loop
        while (gameRunning) {
            //draw();
            if (SDL_PollEvent(&event)) { //check for new event
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    //If the left mouse button was pressed
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        mouseX = event.button.x;
                        mouseY = event.button.y;
						gun.createBullet(mouseX, mouseY);
                        fireBullet = true;
                    }
                }
            }

            if (fireBullet) {
                
				
                //draw();
				
                if (!gun.fireGuns()) fireBullet = false;
            }

            //exit event
            if (event.type == SDL_QUIT) {
                gameRunning = false;
            }
        }
    }

    void draw() {

        graphics.clearScreen();

        graphics.drawBackground("Images/bg.bmp"); //sets background

        castle.drawCastle();	//places castle

        enemy.drawEnemies();

        gun.drawGuns();
    }
};

#endif