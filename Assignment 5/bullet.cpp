#include "bullet.h"
#include <SDL.h>

void bullet::Shoot(SDL_Surface* screen, SDL_Surface* gun)
{
    Bullets.push_back(new bullet());
}


void bullet::DrawBullets()
{
    //for (int i=0; i<Bullets.size(); i++)
    //{
        //do stuff here
    //}
}
