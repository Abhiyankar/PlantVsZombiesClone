#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class Game
{
public:
	Game() {}
	Game(int width, int height);
	void Init();
	void Run();

private:
	SDL_Window* mWindow=nullptr;
	SDL_Renderer* mRenderer=nullptr;
	int mWidth;
	int mHeight;
};

