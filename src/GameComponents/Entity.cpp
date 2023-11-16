#include "Entity.h"
#include <iostream>

void Entity::LoadImages(SDL_Renderer* renderer, const char* filepath, std::vector<SDL_Rect> rects, int totalImages, bool colorKey, Uint8 r, Uint8 g, Uint8 b)
{
	image = nullptr;
	image = LoadTexture(renderer, filepath, colorKey, r, g, b);
	for (int i = 0; i < totalImages; i++)
	{
		srcRect.push_back(rects[i]);
	}
}

void Entity::Init()
{
}

void Entity::Draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, image, &srcRect[currentAnimIndex], &destRect);
}

void Entity::Update(float dT)
{
	timeElapsed += dT;
	if (timeElapsed > timer)
	{
		timeElapsed = 0;
		currentAnimIndex++;
		if (currentAnimIndex >= totalFrames)
		{
			currentAnimIndex = 0;
		}
	}
}

void Entity::setDestRect(int x, int y, int w, int h)
{
	destRect = { x,y,w,h };
}
