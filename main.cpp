#include "header/game.h"
#include "header/pch.h"

using namespace std;

int main()
{
    StartMenu StartMenu;
    while(StartMenu.window->isOpen())
    {
        while (const std::optional event = StartMenu.window -> pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
            {
                StartMenu.window -> close();
            }
            StartMenu.window->clear(sf::Color::Black);

            // Draw the text
            StartMenu.window->draw(StartMenu.text);

            // Display the contents of the window
            StartMenu.window->display();
        }
    }
    
    Game game;
    while (game.getWindowIsOpen())
    {
        game.update();
        game.render();
    }
    return 1;
}
