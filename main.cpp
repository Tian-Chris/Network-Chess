#include "header/game.h"
#include "header/button.h"
#include "header/pch.h"
#include "Asio/client.h"
using namespace std;

enum class network {
    server,
    client
};

int main()
{
    //this is the start menu
    network networkMode; // will be set to server or client then create a server or client
    StartMenu StartMenu;
    Button button1("images/grass.png", "images/wall.png", "Server", {50.f, 50.f});
    Button button2("images/grass.png", "images/wall.png", "Client", {200.f, 50.f});

    while(StartMenu.window->isOpen())
    {
        while (const std::optional event = StartMenu.window -> pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
            {
                StartMenu.window -> close();
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(*StartMenu.window);
                button1.checkClick(localPosition);
                button2.checkClick(localPosition);
            }
            
            StartMenu.window->clear(sf::Color::Black);

            button1.draw([&](const sf::Drawable& drawable, const sf::RenderStates& states){StartMenu.window->draw(drawable, states);});
            button2.draw([&](const sf::Drawable& drawable, const sf::RenderStates& states){StartMenu.window->draw(drawable, states);});
            // Draw the text
            //StartMenu.window->draw(StartMenu.text);

            // Display the contents of the window
            if(button1.getVar() == true)
            {
                StartMenu.window -> close();
                networkMode = network::server;
            }
            if(button2.getVar() == true)
            {
                StartMenu.window -> close();
                networkMode = network::client;
            }
            StartMenu.window->display();
        }
    }
    
    
    //this is the game
    Game game;
    while (game.getWindowIsOpen())
    {
        game.update();
        game.render();
    }
    return 1;
}
