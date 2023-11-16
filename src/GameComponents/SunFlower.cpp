#include "SunFlower.h"

SunFlower::SunFlower(std::vector<SDL_Rect> idle, std::vector<SDL_Rect> produce)
{
	idleSrcRects = idle;
	produceSrcRects = produce;
}

void SunFlower::changeState(int state)
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
		setSourceRects(produceSrcRects);
		setTotalFrames(1);
		setCurrentAnimIndex(0);
		totalTime = 0;
	}
}

void SunFlower::Update(float dT)
{
	if (currentState == 0)
	{
		totalTime += dT;
	}
	if (totalTime > timeTillNextSun)
	{
		changeState(1);
		canProduce = true;
		totalTime = 0;
	}
	if (currentState == 1)
	{
		totalTime += dT;
		if (totalTime > resetBackToIdle)
		{
			changeState(0);
			totalTime = 0;
		}
	}

	Entity::Update(dT);
}

void SunFlower::manualReset()
{
	changeState(0);
	totalTime = 0;
	canProduce = false;
}

void SunFlower::takeDamage(int damage)
{
	if (health - damage <= 0)
	{
		isAlive = false;
	}
	health -= damage;
}
