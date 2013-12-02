#ifndef GUN_H
#define GUN_H

#include "SDL.h"
#include "SDL_TTF.h"
#include "Graphics.h"
#include "Bullet.h"
#include "Enemy.h"
#include <vector>


using namespace std;

static int GUN_WIDTH = 42;
static int GUN_HEIGHT = 13;

static int BULLET_START_X = SCREEN_WIDTH-CASTLE_WIDTH-GUN_WIDTH+10;
static int BULLET_START_Y = STATBAR_HEIGHT + (GAME_HEIGHT-GUN_HEIGHT)/2;

class Gun {
    
public:
    Gun() {

	}

	vector<Bullet *> bullets;
	Bullet bulletValRef; // needed to access bulletData struct values

	void drawGuns() {//
        graphics.displaySprite("Images/cannon.bmp",0,0,SCREEN_WIDTH-CASTLE_WIDTH-GUN_WIDTH+10,STATBAR_HEIGHT+(((SCREEN_HEIGHT - STATBAR_HEIGHT)/2)-(GUN_HEIGHT/2)),GUN_WIDTH,GUN_HEIGHT);
    }

	bool fireGuns(const int bulletUpgrades){

		if(bullets.size()==0) return false;
		
		for(int i=0; i<bullets.size(); i++){

			bullets[i]->x+=bullets[i]->deltaX;
			bullets[i]->y+=bullets[i]->deltaY;

			//check if bullet is off the screen
			if(checkBulletLocale(bullets[i]->x,bullets[i]->y)) {		
				deleteBullet(i); //delete bullet from vector
			}
			else //graphics.displaySprite("Images/Bullets/bullet.bmp",0,0,bullets[i]->x,bullets[i]->y, BULLET_WIDTH, BULLET_HEIGHT);	//redraw bullet sprite
				graphics.displaySprite(bulletValRef.getPath(bulletUpgrades),0,0,bullets[i]->x,bullets[i]->y, bulletValRef.getWidth(bulletUpgrades), bulletValRef.getHeight(bulletUpgrades));	//redraw bullet sprite
		}
	}
	
	void createBullet(int mouseX, int mouseY, const int bulletUpgrades){
		Bullet bulletValRef;

		if(mouseX > BULLET_START_X) mouseX = BULLET_START_X+1;

		double angle = tan((BULLET_START_Y - mouseY) / max(BULLET_START_X - mouseX, 1));

		double bulletSpeed = .01 * bulletValRef.getSpeed(bulletUpgrades); //increase for faster bullet (.01 - .1 seems to be a good range)

		if(mouseX > BULLET_START_X) mouseX = BULLET_START_X;

		double delta_x = ((mouseX - BULLET_START_X) + cos(angle))*bulletSpeed;
		double delta_y = ((mouseY - BULLET_START_Y) - sin(angle))*bulletSpeed;
		
		bullets.push_back(new Bullet(BULLET_START_X, BULLET_START_Y, delta_x, delta_y, bulletUpgrades));	//add new bullet to vector
	}

	//Checks if bullet is off the screen
	bool checkBulletLocale(double curX, double curY){
		if (curX < 0 || curY < STATBAR_HEIGHT || curY > 1024) return true;  //TODO fix static int SCREEN_WIDTH/SCREEN_HEIGHT

		else return false;
	}

	void deleteBullet(int i){
		bullets.erase(bullets.begin() + i); //delete bullet from vector
	}

	void deleteBullets() {
		bullets.erase(bullets.begin(), bullets.begin() + bullets.size());
	}

private:
	Graphics graphics;
	
};

#endif