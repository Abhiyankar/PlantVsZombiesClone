#include "Bullet.h"

void Bullet::LoadImages(SDL_Renderer* renderer, const char* filepath, std::vector<SDL_Rect> rects, int totalImages, bool colorKey, Uint8 r, Uint8 g, Uint8 b)
{
	image = nullptr;
	image = LoadTexture(renderer, filepath, colorKey, r, g, b);
	for (int i = 0; i < totalImages; i++)
	{
		srcRect.push_back(rects[i]);
	}
}

void Bullet::Init()
{

}

void Bullet::Draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, image, &srcRect[0], &destRect);
}

void Bullet::Update(float dT)
{
	destRect.x += xVelocity*dT;
}

void Bullet::setDestRect(int x, int y, int w, int h)
{
	destRect = { x,y,w,h };
}

bool Bullet::checkCollision(const SDL_Rect& A)
{
	if (isCollided(getDestRect(), A))
	{
		isColliding = true;
	}
	else
	{
		isColliding = false;
	}
	return isColliding;
}

