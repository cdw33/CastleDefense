#ifndef BULLET_H
#define BULLET_H

#include "SDL.h"
#include "SDL_TTF.h"
#include "Graphics.h"
#include <vector>
#include <iostream>

using namespace std;

static int BULLET_WIDTH = 10;
static int BULLET_HEIGHT = 10;
const double BASE_DAMAGE = 2;
const double TOTAL_SPEED_UPGRADES = 7;

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