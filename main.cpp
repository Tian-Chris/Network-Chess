#include "game.h"
#include "pch.h"

using namespace std;

int main()
{
    Game game;
    while (game.getWindowIsOpen())
    {
        game.update();
        game.render();
    }
}
