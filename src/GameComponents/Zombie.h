#pragma once
#include "Entity.h"

class Zombie :
    public Entity
{
public:
    //Zombie() {};
    virtual bool checkCollision(const SDL_Rect& A) = 0;
    virtual void setXVelocity(float xVel) = 0;
    virtual void takeDamage(int damage) = 0;
    inline bool getIsAlive() { return isAlive; }
    bool isAlive = true;
    int health = 100;
};

