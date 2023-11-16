#pragma once

#include "SDL.h"

class Environment
{
public:
	Environment() {}
	Environment(SDL_Renderer* renderer, const char* filepath, int x, int y, int w, int h, bool colorKey = false, Uint8 r = 0xFF, Uint8 g = 0xFF, Uint8 b = 0xFF);
	void Init(SDL_Renderer* renderer, const char* filepath, int x, int y, int w, int h, bool colorKey = false, Uint8 r = 0xFF, Uint8 g = 0xFF, Uint8 b = 0xFF);
	void SimpleDraw(SDL_Renderer* renderer);
	void Draw(SDL_Renderer* renderer);
	void setDestRect(int x, int y, int w, int h);
	inline SDL_Rect getDestRect() { return destRect; }

private:
	SDL_Texture* image=nullptr;
	SDL_Rect srcRect;
	SDL_Rect destRect;
};

