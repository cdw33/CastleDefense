#ifndef BULLET_H
#define BULLET_H

#include "SDL.h"
#include "SDL_TTF.h"
#include "Graphics.h"
#include <vector>
#include <iostream>

using namespace std;

const double BASE_DAMAGE = 2;
const double TOTAL_SPEED_UPGRADES = 7;

//bullet sprite dimensions for hit detection
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

class Bullet { 
	public:
		/*Bullet(double newX, double newY, double newDeltaX, double newDeltaY, double newDamage, double newSpeed) {
			x=newX;
			y=newY;
			damage=newDamage;
			speed=newSpeed;
			deltaX=newDeltaX;
			deltaY=newDeltaY;
		};
		*/

		Bullet(double newX, double newY, double newDeltaX, double newDeltaY, int bulletUpgrades, int bulletSpeed) {
			x = newX;
			y = newY;
			deltaX = newDeltaX;
			deltaY = newDeltaY;

			/*Sample data, more finite input may work better */
			damage = 1 + bulletUpgrades * BASE_DAMAGE;
			speed = 1.2 - bulletSpeed / TOTAL_SPEED_UPGRADES;
			stopOnContact = (bulletUpgrades < 6 ? true : false);
			poison = (bulletUpgrades == 7 ? true : false);
		};

		double x,y,damage,speed,deltaX,deltaY;
		bool stopOnContact, poison;

	private:
	
};

#endif