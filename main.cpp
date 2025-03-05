#include <iostream>
#include <fstream>
#include <cstdlib> 
#include "game.h"
#include "cell.h"
using namespace std;

int main()
{
    sf::Texture grassTexture("images/grass.png");
    Cell grass(grassTexture,{0.f, 0.f});
    
    Game game;
    while (game.getWindowIsOpen())
    {
        
        game.update();
        game.render();
    }
}