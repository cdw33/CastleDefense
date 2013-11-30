#ifndef BULLET_H
#define BULLET_H

#include "SDL.h"
#include "SDL_TTF.h"
#include "Graphics.h"
#include <vector>
#include <iostream>

using namespace std;

/*bullet sprite dimensions for hit detection
static int BULLET_BIG_WIDTH = 34;
static int BULLET_BIG_HEIGHT = 19;
static int BULLET_WIDTH = 21;
static int BULLET_HEIGHT = 12;
static int BULLET_PEA_WIDTH = 8;
static int BULLET_PEA_HEIGHT = 8;
static int BULLET_POISON_WIDTH = 34;
static int BULLET_POISON_HEIGHT = 19;
static int BULLET_ROCK_WIDTH = 10;
static int BULLET_ROCK_HEIGHT = 10;
static int BULLET_SPITBALL_WIDTH = 9;
static int BULLET_SPITBALL_HEIGHT = 8;
static int BULLET_STRONG_WIDTH = 24;
static int BULLET_STRONG_HEIGHT = 14;
static int BULLET_THROUGH_WIDTH = 34;
static int BULLET_THROUGH_HEIGHT = 19;
*/

struct bulletData {
	const char* path;
	int damage, speed, cost, width, height;
};

bulletData bulletInfo[8] = { /*Sample data, real input needed for damage, speed, and cost */
	{ "Images/Bullets/spitball.bmp", 1, 1, 1, 9, 8 },
	{ "Images/Bullets/pea.bmp"     , 1, 1, 1, 8, 8 },
	{ "Images/Bullets/rock.bmp"    , 1, 1, 1, 10, 10 },
	{ "Images/Bullets/bullet.bmp"  , 1, 1, 1, 21, 12 },
	{ "Images/Bullets/strong.bmp"  , 1, 1, 1, 24, 14 },
	{ "Images/Bullets/big.bmp"     , 1, 1, 1, 34, 14 },
	{ "Images/Bullets/through.bmp" , 1, 1, 1, 34, 19 },
	{ "Images/Bullets/poison.bmp"  , 1, 1, 1, 34, 19 }
};

class Bullet { 
	public:
		double x,y,damage,speed,deltaX,deltaY;
		bool stopOnContact, poison;
		static const int BULLET_UPGRADES = 7; /* 0 based indexing */

		Bullet(){};
		Bullet(double newX, double newY, double newDeltaX, double newDeltaY, int bulletUpgrades) {
			x = newX;
			y = newY;
			deltaX = newDeltaX;
			deltaY = newDeltaY;

			damage = bulletInfo[bulletUpgrades].damage;
			speed = bulletInfo[bulletUpgrades].speed;      /* This assumes speed is distance traveled per cycle */
			stopOnContact = (bulletUpgrades < 6 ? true : false);
			poison = (bulletUpgrades == 7 ? true : false);
		};

		const char* getPath(int bulletUpgrades) { return bulletInfo[bulletUpgrades].path; }
		int getDamage(int bulletUpgrades) { return bulletInfo[bulletUpgrades].damage; }
		int getSpeed(int bulletUpgrades) { return bulletInfo[bulletUpgrades].speed; }
		int getCost(int bulletUpgrades) { return bulletInfo[bulletUpgrades].cost; }
		int getWidth(int bulletUpgrades) { return bulletInfo[bulletUpgrades].width; }
		int getHeight(int bulletUpgrades) { return bulletInfo[bulletUpgrades].height; }
		static const int totalBulletUpgrades() { return BULLET_UPGRADES; }
		
	private:
	
};

#endif