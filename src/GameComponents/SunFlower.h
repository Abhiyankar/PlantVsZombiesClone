#pragma once
#include "Plant.h"

class SunFlower :
    public Plant
{
public:
    SunFlower() {};

    SunFlower(std::vector<SDL_Rect> idle, std::vector<SDL_Rect> produce);
    void changeState(int state) override;
    void Update(float dT) override;
    int currentState = 0;
    inline bool getIsAlive() { return isAlive; }
    inline bool getCanProduce() { return canProduce; }
    inline void setCanProduce(bool canPro) { canProduce = canPro; }
    void takeDamage(int damage);
    void manualReset();
    inline int getHealth() { return health; }

private:
    std::vector<SDL_Rect> idleSrcRects;
    std::vector<SDL_Rect> produceSrcRects;
    float totalTime = 0.0f;
    float timeTillNextSun = 3.0f;
    float resetBackToIdle = 1.0f;
    int health = 100;
    bool isAlive = true;
    bool canProduce = false;
};

