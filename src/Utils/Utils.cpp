#include "Utils.h"
#include<iostream>
#include <cmath>

SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* filepath, bool setColorKey, Uint8 r, Uint8 g, Uint8 b)
{
    if (setColorKey==false)
    {
        return IMG_LoadTexture(renderer, filepath);
    }

    SDL_Surface* loadedSurface = IMG_Load(filepath);
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, r, g, b));
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    return newTexture;
}

bool isCollided(const SDL_Rect& A, const SDL_Rect& B)
{
    if (A.x < B.x + B.w &&
        A.x + A.w > B.x &&
        A.y < B.y + B.h &&
        A.y + A.h > B.y)
    {
        return true;
    }
    return false;
}

bool isCollidedPointAndRect(const int x, const int y, const SDL_Rect& rect)
{
    if (x >= rect.x &&
        x <= rect.x + rect.w &&
        y >= rect.y &&
        y <= rect.y + rect.h)
    {
        return true;
    }

    return false;
}

float calculateDistance(int x1, int y1, int x2, int y2)
{
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}

