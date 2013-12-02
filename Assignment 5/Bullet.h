#ifndef BULLET_H
#define BULLET_H

#include "SDL.h"
#include "SDL_TTF.h"
#include "Graphics.h"
#include <vector>
#include <iostream>

using namespace std;

struct bulletData {
	const char* path;
	int damage, speed, cost, width, height; /* "speed" denotes the rate a bullet travels through space */
	bool goThrough, poison;
};

/* Indicies of bulletData accessed by the bulletUpgrades variable found in data.h */
bulletData bulletInfo[8] = { /*Sample data, real input needed for damage, speed, and cost */
	{ "Images/Bullets/spitball.bmp", 1,  1, 10,  9,  8,  0, 0},
	{ "Images/Bullets/pea.bmp"     , 2,  2, 20,  8,  8,  0, 0},
	{ "Images/Bullets/rock.bmp"    , 4,  3, 30,  10, 10, 0, 0},
	{ "Images/Bullets/bullet.bmp"  , 8,  4, 50,  21, 12, 0, 0},
	{ "Images/Bullets/strong.bmp"  , 16, 5, 70, 24, 14, 0, 0},
	{ "Images/Bullets/big.bmp"     , 32, 6, 90, 34, 14, 0, 0},
	{ "Images/Bullets/through.bmp" , 50, 7, 110, 34, 19, 1, 0},
	{ "Images/Bullets/poison.bmp"  , 50, 8, 130, 34, 19, 1, 1}
};

int rateOfFireList[8] = { 1200, 900, 750, 450, 200, 100, 50, 20 }; /* Indices accessed by the rateOfFire variable found in data.h */
int rateOfFireCost[8] = { 10, 20, 30, 50, 70, 90, 110, 130}; 

class Bullet { 
	public:
		double x,y,damage,speed,deltaX,deltaY;
		static const int BULLET_UPGRADES = 7; /* 0 based indexing */
		static const int FIRE_RATE_UPGRADES = 7; /* 0 based indexing */
		static const int DAMAGE_OVER_TIME = 1000 * 60; /* 1 second per cycle for poison*/
		static const int DAMAGE_PER_CYCLE = 10;

		Bullet(){};
		Bullet(double newX, double newY, double newDeltaX, double newDeltaY, int bulletUpgrades) {
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
		bool damageOverTime(int bulletUpgrades) { return bulletInfo[bulletUpgrades].poison; }
		static const int totalBulletUpgrades() { return BULLET_UPGRADES; }
		
		int getRateOfFire(int fireUpdates) { return rateOfFireList[fireUpdates]; }
		int getRateOfFireCost(int fireUpdates) { return rateOfFireCost[fireUpdates]; }
		static const int totalRateOfFireUpgrades() { return FIRE_RATE_UPGRADES; }

	private:
	
};

#endif