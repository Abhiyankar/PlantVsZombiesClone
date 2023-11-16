#include "Peashooter.h"
#include <iostream>

Peashooter::Peashooter(std::vector<SDL_Rect> idle, std::vector<SDL_Rect> attack)
{
	idleSrcRects = idle;
	attackSrcRects = attack;
	peaBulletCoordinates.push_back(SDL_Rect{ 77,41,12,14 });
	peaBulletCoordinates.push_back(SDL_Rect{ 88,41,12,14 });
	peaBulletCoordinates.push_back(SDL_Rect{ 99,38,15,19 });
}

void Peashooter::changeState(int state)
{
	currentState = state;
	if (currentState == 0)
	{
		setSourceRects(idleSrcRects);
		setTotalFrames(8);
		setCurrentAnimIndex(0);
	}
	else if (currentState == 1)
	{
		setSourceRects(attackSrcRects);
		setTotalFrames(3);
		setCurrentAnimIndex(0);
		totalTime = 0;
	}
}

void Peashooter::Update(float dT)
{
	totalTime += dT;
	//std::cout << "Peashooter Update" << std::endl;
	if (totalTime > time)
	{
		if (currentState == 1)
		{
			changeState(0);
		}
	}

	if (currentState == 0)
	{
		totalTime2 += dT;
	}

	if (totalTime2 > timeToNextFire)
	{
		canFire = true;
		totalTime2 = 0;
	}

	

	Entity::Update(dT);
}

void Peashooter::Fire(std::vector<Bullet>& bullets, SDL_Renderer* rend)
{
	if (canFire == true && inRange)
	{
		changeState(1);
		canFire = false;
		Bullet bul;
		bul.LoadImages(rend, "graphics/PeaShooter.png", peaBulletCoordinates, 3, true, 0x75, 0x65, 0xFF);
		bul.setDestRect(getDestRect().x+getDestRect().w, getDestRect().y+3, 16, 16);
		std::cout << "Shot Fired" << std::endl;
		bullets.push_back(bul);
	}
}

void Peashooter::takeDamage(int damage)
{
	if (health - damage <= 0)
	{
		isAlive = false;
	}
	health -= damage;
}
