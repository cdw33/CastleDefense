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
    Gun() {};

	vector<Bullet *> bullets;
	Bullet bulletValRef; // needed to access bulletData struct values

	void drawGuns() {
        graphics.displaySprite("Images/cannon.bmp",0,0,SCREEN_WIDTH-CASTLE_WIDTH-GUN_WIDTH+10,STATBAR_HEIGHT+(((SCREEN_HEIGHT - STATBAR_HEIGHT)/2)-(GUN_HEIGHT/2)),GUN_WIDTH,GUN_HEIGHT);
    }

	bool fireGuns(const int bulletUpgrades){

		if(bullets.size()==0) return false;
		
		for(int i=0; i<bullets.size(); i++){
			double 
				run = bullets[i]->deltaX - bullets[i]->x,
				rise = bullets[i]->deltaY - bullets[i]->y,
				length = sqrt(rise*rise + run*run),
				unitX = run / max(1.0, length),
				unitY = rise / max(1.0, length);
		
			bullets[i]->x += unitX * bullets[i]->speed;
			bullets[i]->y += unitY * bullets[i]->speed;

			//check if bullet is off the screen
			if(checkBulletLocale(bullets[i]->x,bullets[i]->y)) {		
				deleteBullet(i); //delete bullet from vector
			} else {
				graphics.displaySprite(bulletValRef.getPath(bulletUpgrades),0,0,bullets[i]->x,bullets[i]->y, bulletValRef.getWidth(bulletUpgrades), bulletValRef.getHeight(bulletUpgrades));	//redraw bullet sprite
			}
		}
	}
	
	void createBullet(int mouseX, int mouseY, const int bulletUpgrades){
		if(mouseX > BULLET_START_X) mouseX = BULLET_START_X;

		/* Move the mouse click outside the screen, so the bullet continues to travel past where the user clicked */
		mouseX += (mouseX - BULLET_START_X) * 1000;
		mouseY += (mouseY - BULLET_START_Y) * 1000;

		bullets.push_back(new Bullet(BULLET_START_X, BULLET_START_Y, mouseX, mouseY, bulletUpgrades));	//add new bullet to vector
	}

	//Checks if bullet is off the screen
	bool checkBulletLocale(double curX, double curY){
		if (curX < -10 || curY < STATBAR_HEIGHT || curY > 1024) return true; 
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