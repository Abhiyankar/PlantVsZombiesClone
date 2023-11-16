#pragma once

#include "SDL.h"
#include "../Utils/Utils.h"
#include <vector>

class Bullet
{
public:
	Bullet() {};
	void LoadImages(SDL_Renderer* renderer, const char* filepath, std::vector<SDL_Rect> rects, int totalImages, bool colorKey = false, Uint8 r = 0xFF, Uint8 g = 0xFF, Uint8 b = 0xFF);
	void Init();
	void Draw(SDL_Renderer* renderer);
	virtual void Update(float dT);
	void setDestRect(int x, int y, int w, int h);
	inline SDL_Rect getDestRect() { return destRect; }
	bool checkCollision(const SDL_Rect& A);
	bool isColliding = false;

private:
	SDL_Texture* image;
	std::vector<SDL_Rect> srcRect;
	SDL_Rect destRect;
	float xVelocity = 100;
	float yVelocity = 0;
};

