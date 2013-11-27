#ifndef ENEMY_H
#define ENEMY_H

#include "SDL.h"
#include "SDL_TTF.h"

class Enemy {
   
public:

    Enemy() {
        
    };

	Graphics graphics;

	void drawEnemies() {
        graphics.displaySprite("Images/enemy.bmp",0,0,100,100,71,64);
    }

	void moveEnemy(){

	}

};

#endif