#ifndef ENEMY_H
#define ENEMY_H

#include "SDL.h"
#include "SDL_TTF.h"
#include <ctime>

struct Enemies{
	double xCoor, yCoor, damage, hp;

};

class Enemy {
   
public:

	vector<Enemies *> enemies;

    Enemy() {
        srand(time(0));
    };

	Graphics graphics;

	void drawEnemies() {
		for(int i=0; i<enemies.size(); i++){
			graphics.displaySprite("Images/enemy.bmp",0,0,enemies[i]->xCoor,enemies[i]->yCoor,71,64);
		}
    }

	void moveEnemy(){
		for(int i=0; i<enemies.size(); i++){
			enemies[i]->xCoor+=1;
		}
	}

	void createEnemy(double damage, double hp){	
		enemies.push_back(new Enemies());	//add new enemy to vector
		enemies[enemies.size()-1]->xCoor=0;
		enemies[enemies.size()-1]->yCoor=rand()%720;
	}

};

#endif