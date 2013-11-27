#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL.h"
#include "SDL_TTF.h" //TODO create displayTTF function

using namespace std;

class Graphics {
    
public:

    Graphics() {
        SDL_Init(SDL_INIT_VIDEO);

        screen = SDL_SetVideoMode(1280, 720, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);

        SDL_WM_SetCaption("Castle Defense", 0);
    };

    // ~Graphics();

	//TODO
    // Each call to loadBitmap() must have a corresponding call to closeBitmap().   
	//void closeBitmap(SDL_Surface* bitmap);

    void drawBackground(const char* bitmapFileName) {
        SDL_Surface* bitmap = SDL_LoadBMP(bitmapFileName);

        // Set the Background
        SDL_BlitSurface(bitmap, NULL, screen, NULL);

        SDL_Flip(screen);
    }

	//displays given sprite on screen
    void displaySprite(const char* bitmapFileName, int srcX, int srcY, int dstX, int dstY, int spriteWidth, int spriteHeight) {
		
        SDL_Surface* bitmap = SDL_LoadBMP(bitmapFileName);

        // set magenta to be the transparent color
		SDL_SetColorKey(bitmap, SDL_SRCCOLORKEY, SDL_MapRGB(bitmap->format, 255, 0, 255));

        // Part of the enemy that we want to draw
        SDL_Rect srcRect;
        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = spriteWidth;
        srcRect.h = spriteHeight;

        // Part of the screen we want to draw the sprite to
        SDL_Rect dstRect;
        dstRect.x = dstX;
        dstRect.y = dstY;
        dstRect.w = spriteWidth;
        dstRect.h = spriteHeight;

        SDL_BlitSurface(bitmap, &srcRect, screen, &dstRect);

        SDL_Flip(screen);

    }
	void closeBitmap(SDL_Surface* bitmap)
	{
		 SDL_FreeSurface(bitmap);
	}

	void clearScreen(){
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	}

private:
    
	SDL_Surface* screen;
};

#endif