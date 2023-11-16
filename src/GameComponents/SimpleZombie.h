#pragma once

#include "Zombie.h"

class SimpleZombie :
    public Zombie
{
public:
    SimpleZombie() {};

    SimpleZombie(std::vector<SDL_Rect> idle, std::vector<SDL_Rect> attackFull, std::vector<SDL_Rect> walkFull, std::vector<SDL_Rect> walkHalf, std::vector<SDL_Rect> attackHalf);
    void changeState(int state) override;
    void Update(float dT) override;
    bool checkCollision(const SDL_Rect& A) override;
    inline void setXVelocity(float xVel) override { xVelocity = xVel; }
    inline void setYVelocity(float yVel) { yVelocity = yVel; }
    inline void setLane(int l) { lane = l; }
    inline int getLane() { return lane; }
    inline void setCanMove(bool move) { canMove = move; }
    void restoreAttackToWalk();
    void takeDamage(int damage) override;
    int currentState = 0;
    bool canFire = false;
    bool isColliding = false;
    bool canMove = true;

private:
    std::vector<SDL_Rect> idleSrcRectsFull;
    std::vector<SDL_Rect> attackSrcRectsFull;
    std::vector<SDL_Rect> walkSrcRectsFull;
    std::vector<SDL_Rect> walkSrcRectsHalf;
    std::vector<SDL_Rect> attackSrcRectsHalf;

    float totalTime = 0;
    float time = 0.8f;
    float xVelocity = 0.0f;
    float yVelocity = 0.0f;
    int lane = 0;
};

