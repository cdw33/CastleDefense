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

class Bullet {
    
public:

    Bullet(double newX, double newY, double newDeltaX, double newDeltaY, double newDamage, double newSpeed) {
        x=newX;
		y=newY;
		damage=newDamage;
		speed=newSpeed;
		deltaX=newDeltaX;
		deltaY=newDeltaY;
    };

	double x,y,damage,speed,deltaX,deltaY,oldX,oldY;


private:
	
};

#endif