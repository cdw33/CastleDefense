#include "Graphics.h"

Graphics::Graphics(int windowWidth, int windowHeight,
                         const char* windowTitle,
                         int bgR, int bgG, int bgB)
{
   SDL_Init(SDL_INIT_VIDEO);

   TTF_Init();

   m_screen = SDL_SetVideoMode(windowWidth, windowHeight, 
                               0, SDL_HWSURFACE | SDL_DOUBLEBUF);

   SDL_WM_SetCaption(windowTitle, 0);

   setBackgroundColor(bgR, bgG, bgB);
}

Graphics::~Graphics()
{
   TTF_Quit();
   SDL_Quit();
}

SDL_Surface* Graphics::loadBitmap(const char* bitmapFileName, 
                                     int transparentRed, int transparentGreen, int transparentBlue)
{
   SDL_Surface* bitmap = SDL_LoadBMP(bitmapFileName);

   SDL_SetColorKey(bitmap, 
                   SDL_SRCCOLORKEY, 
                   SDL_MapRGB(bitmap->format, transparentRed, transparentGreen, transparentBlue));

   return bitmap;
}

void Graphics::closeBitmap(SDL_Surface* bitmap)
{
   SDL_FreeSurface(bitmap);
}

void Graphics::startScene()
{
   // Clear the screen
   SDL_FillRect(m_screen, 
                NULL, 
                SDL_MapRGB(m_screen->format, m_backgroundColorRed, 
                                             m_backgroundColorGreen, 
                                             m_backgroundColorBlue));
}

// This just displays the scene.
void Graphics::endScene()
{
   SDL_Flip(m_screen);
}

void Graphics::drawSprite(SDL_Surface* imageSurface,
                             int srcX, int srcY, 
                             int dstX, int dstY,
                             int width, int height)
{
   SDL_Rect srcRect;
   srcRect.x = srcX;
   srcRect.y = srcY;
   srcRect.w = width;
   srcRect.h = height;

   SDL_Rect dstRect;
   dstRect.x = dstX;
   dstRect.y = dstY;
   dstRect.w = width;
   dstRect.h = height;

   SDL_BlitSurface(imageSurface, &srcRect, m_screen, &dstRect);
}

void Graphics::drawText(const char* string,
                           int size,
                           int x, int y,
                           int fR, int fG, int fB,
                           int bR, int bG, int bB)
{
   TTF_Font* font = TTF_OpenFont("ARIAL.TTF", size);

   SDL_Color foregroundColor = { fR, fG, fB }; 
   SDL_Color backgroundColor = { bR, bG, bB };

   SDL_Surface* textSurface = TTF_RenderText_Shaded(font, string, 
                                                    foregroundColor, backgroundColor);

   SDL_Rect textLocation = { x, y, 0, 0 };

   SDL_BlitSurface(textSurface, NULL, m_screen, &textLocation);

   SDL_FreeSurface(textSurface);

   TTF_CloseFont(font);
}

void Graphics::setBackgroundColor(int r, int g, int b)
{
   m_backgroundColorRed = r;
   m_backgroundColorGreen = g;
   m_backgroundColorBlue = b;
}