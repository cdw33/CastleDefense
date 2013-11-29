#ifndef GUN_H
#define GUN_H

#include "SDL.h"
#include "SDL_TTF.h"
#include "Graphics.h"
#include "Bullet.h"
#include <vector>


using namespace std;

static int GUN_WIDTH = 42;
static int GUN_HEIGHT = 13;

static int BULLET_START_X = SCREEN_WIDTH-CASTLE_WIDTH-GUN_WIDTH+10;
static int BULLET_START_Y = (SCREEN_HEIGHT-GUN_HEIGHT)/2;

class Gun {
    
public:
	vector<Bullet *> bullets;

    Gun(){
		const char* path[] = {
			"Images/Bullets/spitball.bmp",
			"Images/Bullets/pea.bmp",
			"Images/Bullets/rock.bmp",
			"Images/Bullets/bullet.bmp",
			"Images/Bullets/strong.bmp",
			"Images/Bullets/big.bmp",
			"Images/Bullets/through.bmp",
			"Images/Bullets/poison.bmp"
		};
	};

	const char* path[8];

	void drawGuns() {
        graphics.displaySprite("Images/cannon.bmp",0,0,SCREEN_WIDTH-CASTLE_WIDTH-GUN_WIDTH+10,(SCREEN_HEIGHT-GUN_HEIGHT)/2,GUN_WIDTH,GUN_HEIGHT);
    }

	
	// If fireGuns(int) is called in a function from Game.h, then you can pass in data.bulletUpgrades
	bool fireGuns(){

		if(bullets.size()==0) return false;
		
		for(int i=0; i<bullets.size(); i++){

			bullets[i]->x+=bullets[i]->deltaX;
			bullets[i]->y+=bullets[i]->deltaY;

			graphics.displaySprite("Images/bullet.bmp",0,0,bullets[i]->x,bullets[i]->y,BULLET_WIDTH, BULLET_HEIGHT);	//redraw bullet sprite
			
			//check if bullet is off the screen
			if(checkBulletLocale(bullets[i]->x,bullets[i]->y)){		
				bullets.erase(bullets.begin() + i); //delete bullet from vector
				
			}
		}
	}
	
	void createBullet(int mouseX, int mouseY){

		double angle = tan((BULLET_START_Y - mouseY) / (BULLET_START_X - mouseX));

		double bulletSpeed = .05; //increase for faster bullet (.01 - .1 seems to be a good range)

		if(mouseX > BULLET_START_X) mouseX = BULLET_START_X;

		double delta_x = ((mouseX - BULLET_START_X) + cos(angle))*bulletSpeed;
		double delta_y = ((mouseY - BULLET_START_Y) - sin(angle))*bulletSpeed;
		
		bullets.push_back(new Bullet(SCREEN_WIDTH-CASTLE_WIDTH-GUN_WIDTH, (SCREEN_HEIGHT-GUN_HEIGHT)/2, delta_x, delta_y, 1, 1));	//add new bullet to vectir
	}

	//Checks if bullet is off the screen
	bool checkBulletLocale(double curX, double curY){
		if (curX < 0 || curY < 0 || curY > 1024) return true;  //TODO fix static int SCREEN_WIDTH/SCREEN_HEIGHT

		else return false;
	}

private:
	Graphics graphics;
	
};

#endif