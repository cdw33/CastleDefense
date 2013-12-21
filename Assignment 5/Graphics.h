#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL.h"
#include "SDL_TTF.h"
#include <iostream>
#include <ctime>

using namespace std;

class Graphics {
private:
    SDL_Surface* screen;
	int lastRefresh;

public:

    Graphics() {
		lastRefresh = clock();

        SDL_Init(SDL_INIT_VIDEO);

		screen = SDL_SetVideoMode(1280, 720, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);

        SDL_WM_SetCaption("Castle Defense", 0);

        TTF_Init();
    };

    ~Graphics() {
        TTF_Quit();
        SDL_Quit();
    };

    // REMEMBER:
    // Each call to loadBitmap() must have a corresponding call to closeBitmap().
    void drawBackground(const char* bitmapFileName) {
        SDL_Surface* bitmap = SDL_LoadBMP(bitmapFileName);

        // Set the Background
        SDL_BlitSurface(bitmap, NULL, screen, NULL);

        closeBitmap(bitmap);
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

        closeBitmap(bitmap);
    }

    void drawText(const char* string, int size, int x, int y, int fR, int fG, int fB) {
        TTF_Font* font = TTF_OpenFont("Ardagh.ttf", size);

        SDL_Color foregroundColor = {fR, fG, fB};

        SDL_Surface* textSurface = TTF_RenderText_Blended(font, string,
                foregroundColor);

		SDL_SetColorKey(textSurface, SDL_SRCCOLORKEY, SDL_MapRGB(textSurface->format, 255, 0, 255));

        SDL_Rect textLocation = {x, y, 0, 0};

        SDL_BlitSurface(textSurface, NULL, screen, &textLocation);

        SDL_FreeSurface(textSurface);  //crashing program

        TTF_CloseFont(font);
    }

    void closeBitmap(SDL_Surface* bitmap) {
        SDL_FreeSurface(bitmap);
    }

    void clearScreen() {
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    }

    void flip() {
        SDL_Flip(screen);
    }

	void setFps(int fps = 30) {
		int rate = 1000 / fps;

		while(clock() < lastRefresh + rate);
		lastRefresh = clock();
	}
};

#endif