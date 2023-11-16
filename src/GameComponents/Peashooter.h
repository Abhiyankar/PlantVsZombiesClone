#pragma once
#include "Plant.h"
#include "Bullet.h"

class Peashooter :
    public Plant
{
public:
    Peashooter() {};

    Peashooter(std::vector<SDL_Rect> idle, std::vector<SDL_Rect> attack);
    void changeState(int state) override;
    void Update(float dT) override;
    int currentState = 0;
    bool canFire = true;
    void Fire(std::vector<Bullet> &bullets, SDL_Renderer* rend);
    inline void setInRange(bool isInRange) { inRange = isInRange; }
    inline bool getInRange() { return inRange; }
    inline bool getIsAlive() { return isAlive; }
    void takeDamage(int damage);
    inline int getHealth() { return health; }

private:
    std::vector<SDL_Rect> idleSrcRects;
    std::vector<SDL_Rect> attackSrcRects;
    float totalTime = 0;
    float time = 0.8f;
    float totalTime2 = 0;
    float timeToNextFire = 4.0f;
    std::vector<SDL_Rect> peaBulletCoordinates;
    bool inRange = false;
    int health = 100;
    bool isAlive = true;
};

