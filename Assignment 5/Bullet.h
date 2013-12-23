#ifndef BULLET_H
#define BULLET_H

#include "SDL.h"
#include "SDL_TTF.h"
#include "Graphics.h"
#include <vector>
#include <ctime>
#include <iostream>

using namespace std;

struct bulletData {
	const char* path;
	int damage, speed, cost, width, height; /* "speed" denotes the rate a bullet travels through space */
	bool goThrough;
};

/* Indicies of bulletData accessed by the bulletUpgrades variable found in data.h */
bulletData bulletInfo[8] = { /*Image path, damage, speed, cost, width, height, goThrough*/
	{ "Images/Bullets/spitball.bmp", 1,  2, 10,   9,  8,  0},
	{ "Images/Bullets/pea.bmp"     , 2,  2, 20,   8,  8,  0},
	{ "Images/Bullets/rock.bmp"    , 4,  3, 50,   10, 10, 0},
	{ "Images/Bullets/bullet.bmp"  , 5,  4, 100,  21, 12, 0},
	{ "Images/Bullets/strong.bmp"  , 6,  4, 200,  24, 14, 0},
	{ "Images/Bullets/big.bmp"     , 7,  5, 400,  34, 14, 0},
	{ "Images/Bullets/uber.bmp"    , 8,  5, 800,  34, 19, 0},
	{ "Images/Bullets/through.bmp" , 9,  6, 1000, 34, 19, 1}
};

/* Indices accessed by the rateOfFire variable found in data.h */
int rateOfFireList[8] = { 1200, 900, 750, 500, 400, 300, 200, 100 }; 
int rateOfFireCost[8] = { 10, 20, 50, 100, 200, 400, 800, 1000 }; 

class Bullet { 
	public:
		int id;
		double x,y,damage,speed,deltaX,deltaY;
		static const int BULLET_UPGRADES = 7;    /* 0 based indexing */
		static const int FIRE_RATE_UPGRADES = 7; /* 0 based indexing */

		Bullet(){};
		Bullet(double newX, double newY, double newDeltaX, double newDeltaY, int bulletUpgrades) {
			if(!stopOnContact(bulletUpgrades)) {
				srand(time(0));
				id = rand() % 1000000;
			} else {
				id = 0;
			}

			x = newX;
			y = newY;
			deltaX = newDeltaX;
			deltaY = newDeltaY;

			damage = bulletInfo[bulletUpgrades].damage;
			speed = bulletInfo[bulletUpgrades].speed;
		};

		const char* getPath(int bulletUpgrades) { return bulletInfo[bulletUpgrades].path; }
		int getDamage(int bulletUpgrades) { return bulletInfo[bulletUpgrades].damage; }
		int getSpeed(int bulletUpgrades) { return bulletInfo[bulletUpgrades].speed; }
		int getCost(int bulletUpgrades) { return bulletInfo[bulletUpgrades].cost; }
		int getWidth(int bulletUpgrades) { return bulletInfo[bulletUpgrades].width; }
		int getHeight(int bulletUpgrades) { return bulletInfo[bulletUpgrades].height; }
		bool stopOnContact(int bulletUpgrades)  { return !bulletInfo[bulletUpgrades].goThrough; }
		static const int totalBulletUpgrades() { return BULLET_UPGRADES; }
		
		int getRateOfFire(int fireUpdates) { return rateOfFireList[fireUpdates]; }
		int getRateOfFireCost(int fireUpdates) { return rateOfFireCost[fireUpdates]; }
		static const int totalRateOfFireUpgrades() { return FIRE_RATE_UPGRADES; }

	private:
	
};

#endif