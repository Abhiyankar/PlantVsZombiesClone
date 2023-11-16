#include "Environment.h"
#include "../Utils/Utils.h"

Environment::Environment(SDL_Renderer* renderer, const char* filepath, int x, int y, int w, int h, bool colorKey, Uint8 r, Uint8 g, Uint8 b)
{
	image = LoadTexture(renderer, filepath, colorKey, r, g, b);
	srcRect = { x,y,w,h };
}

void Environment::Init(SDL_Renderer* renderer, const char* filepath, int x, int y, int w, int h, bool colorKey, Uint8 r, Uint8 g, Uint8 b)
{
	image = LoadTexture(renderer, filepath, colorKey, r, g, b);
	srcRect = { x,y,w,h };
}

void Environment::SimpleDraw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, image, &srcRect, NULL);
}

void Environment::Draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, image, &srcRect, &destRect);
}

void Environment::setDestRect(int x, int y, int w, int h)
{
	destRect = { x,y,w,h };
}
