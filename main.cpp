#include <iostream>
#include <fstream>
#include <cstdlib> 
#include "game.h"

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
