#include "SimpleZombie.h"
#include <iostream>

SimpleZombie::SimpleZombie(std::vector<SDL_Rect> idle, std::vector<SDL_Rect> attackFull, std::vector<SDL_Rect> walkFull, std::vector<SDL_Rect> walkHalf, std::vector<SDL_Rect> attackHalf)
{
	idleSrcRectsFull = idle;
	attackSrcRectsFull = attackFull;
	walkSrcRectsFull = walkFull;
	walkSrcRectsHalf = walkHalf;
	attackSrcRectsHalf = attackHalf;
}

void SimpleZombie::changeState(int state)
{
	currentState = state;
	if (currentState == 0)
	{
		setSourceRects(idleSrcRectsFull);
		setTotalFrames(3);
		setCurrentAnimIndex(0);
	}
	else if (currentState == 1)
	{
		setSourceRects(walkSrcRectsFull);
		setTotalFrames(7);
		setCurrentAnimIndex(0);
	}
	else if (currentState == 2)
	{
		setSourceRects(attackSrcRectsFull);
		setTotalFrames(7);
		setCurrentAnimIndex(0);
	}
}

void SimpleZombie::Update(float dT)
{

	if (isColliding == false && canMove)
	{
		setDestRect(getDestRect().x + (xVelocity * dT * dT), getDestRect().y, getDestRect().w, getDestRect().h);
	}
	Entity::Update(dT);
}

bool SimpleZombie::checkCollision(const SDL_Rect& A)
{
	if (isCollided(getDestRect(), A))
	{
		isColliding = true;
		//std::cout << "Collided with the plant" << std::endl;
		changeState(2);
		setCanMove(false);
		setXVelocity(0);
		return true;
	}
	else if(!isCollided(getDestRect(), A))
	{
		isColliding = false;
		setCanMove(true);
		setXVelocity(-0.1f);
		changeState(1);
		return false;
	}
}

void SimpleZombie::restoreAttackToWalk()
{
	isColliding = false;
	setCanMove(true);
	setXVelocity(-0.1f);
	changeState(1);
}

void SimpleZombie::takeDamage(int damage)
{
	if (health - damage <= 0)
	{
		isAlive = false;
	}
	health -= damage;
}
