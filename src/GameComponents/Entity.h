#pragma once

#include "SDL.h"
#include "../Utils/Utils.h"
#include <vector>

class Entity
{
public:
	Entity() {};
	void LoadImages(SDL_Renderer* renderer, const char* filepath, std::vector<SDL_Rect> rects, int totalImages, bool colorKey = false, Uint8 r = 0xFF, Uint8 g = 0xFF, Uint8 b = 0xFF);
	void Init();
	void Draw(SDL_Renderer* renderer);
	virtual void Update(float dT);
	void setDestRect(int x, int y, int w, int h);
	inline SDL_Rect getDestRect() { return destRect; }
	inline void setCurrentAnimIndex(int currentIndex) { currentAnimIndex = currentIndex; }
	inline void setTotalFrames(int total) { totalFrames = total; }
	inline void setSourceRects(std::vector<SDL_Rect> src) { srcRect = src; }
	virtual void changeState(int state) = 0;

private:
	SDL_Texture* image;
	std::vector<SDL_Rect> srcRect;
	SDL_Rect destRect;
	int currentAnimIndex = 0;
	int totalFrames = 8;
	float timeElapsed = 0;
	float timer = 0.2f;
};

