#pragma once

#include "SDL.h"
#include "../Utils/Utils.h"
#include "Entity.h"
#include <vector>

class Sun
	: public Entity
{
public:
	Sun() {};
	Sun(std::vector<SDL_Rect> src);
	inline void changeState(int state) override {}
	void Update(float dT) override;

private:
	std::vector<SDL_Rect> srcRects;
	SDL_Rect destRect;
};

