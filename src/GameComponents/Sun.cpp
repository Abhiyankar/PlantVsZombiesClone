#include "Sun.h"


Sun::Sun(std::vector<SDL_Rect> src)
{
	srcRects = src;
}

void Sun::Update(float dT)
{
	Entity::Update(dT);
}
