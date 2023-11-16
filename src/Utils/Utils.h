#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <string>

SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* filepath, bool setColorKey = false, Uint8 r = 0xFF, Uint8 g = 0xFF, Uint8 b = 0xFF);
bool isCollided(const SDL_Rect &A, const SDL_Rect &B);
bool isCollidedPointAndRect(const int x, const int y, const SDL_Rect& rect);
float calculateDistance(int x1, int y1, int x2, int y2);