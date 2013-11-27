#ifndef CASTLE_H
#define CASTLE_H

#include "SDL.h"
#include "SDL_TTF.h"
#include "Graphics.h"

static int SCREEN_WIDTH = 1280;
static int SCREEN_HEIGHT = 720;

static int CASTLE_WIDTH = 81;
static int CASTLE_HEIGHT = 628;

class Castle {
    
public:

    Castle() {
        
    };

	Graphics graphics;

	void drawCastle() {
        graphics.displaySprite("Images/castle.bmp",0,0,SCREEN_WIDTH-CASTLE_WIDTH,(SCREEN_HEIGHT-CASTLE_HEIGHT)/2,CASTLE_WIDTH,CASTLE_HEIGHT);
    }
};

#endif