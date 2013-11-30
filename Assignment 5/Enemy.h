#ifndef ENEMY_H
#define ENEMY_H

#include "SDL.h"
#include "SDL_TTF.h"
#include <ctime>

static int GHOST_HEIGHT = 64;
static int GHOST_WIDTH = 71;



struct Enemies{
	double xCoor, yCoor, damage, hp;

};

class Enemy { //TODO - attacking the base needs to be handeled
   
public:

    Enemy() {
        srand(time(0));
    };

	Graphics graphics;

	void drawEnemies() {
		for(int i=0; i<enemies.size(); i++){
			graphics.displaySprite("Images/Enemies/ghost.bmp",0,0,enemies[i]->xCoor,enemies[i]->yCoor,GHOST_WIDTH,GHOST_HEIGHT);
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

	bool detectHit(double bulletX, double bulletY, int bulletWidth, int bulletHeight, const int bulletUpgrades) {
		Bullet bulletValRef;
		//if bullet is in the same area as enemy
		for(int i=0; i<enemies.size(); i++){
			if (bulletY + /*BULLET_HEIGHT*/ bulletValRef.getHeight(bulletUpgrades) > enemies[i]->yCoor && bulletY < enemies[i]->yCoor + GHOST_HEIGHT && bulletX < enemies[i]->xCoor + (GHOST_WIDTH)) return true;
		}

		return false;
	}

	void deleteEnemy(int i){
		enemies.erase(enemies.begin() + i);
	}

	bool noEnemies() {
		return enemies.size() == 0;
	}

private:
	vector<Enemies *> enemies;

};

#endif