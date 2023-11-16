#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <iostream>
#include "src/Game.h"

int main()
{
    Game game(447*2, 192*2);
    game.Init();
    game.Run();

    return 0;
}