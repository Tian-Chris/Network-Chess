#include "game/game.h"
#include "global/button.h"
#include "global/pch.h"
#include "network/network.h"
 
using namespace std;

enum class state {
    TitleScreen,
    IPInput,
    GameServer,
    GameClient,
    Exit
};

int main()
{
    state myState = state::TitleScreen;
    while(1)
    {
        //for start menu
        if(myState == state::TitleScreen)
        {
            Button button1("images/grass.png", "images/wall.png", "Server", {50.f, 50.f});
            Button button2("images/grass.png", "images/wall.png", "Client", {200.f, 50.f});
            StartMenu StartMenu;
            while(StartMenu.window->isOpen())
            {
                while (const std::optional event = StartMenu.window -> pollEvent())
                {
                    // "close requested" event: we close the window
                    if (event->is<sf::Event::Closed>())
                    {
                        StartMenu.window -> close();
                        myState = state::Exit;
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
                        myState = state::GameServer; 
                    }
                    if(button2.getVar() == true)
                    {
                        StartMenu.window -> close();
                        myState = state::GameClient; //should instead go to IPinputting 
                    }
                    StartMenu.window->display();
                }
            }
        }

        if(myState == state::IPInput) {}
        
        if(myState == state::GameClient) {
            GameClient game;
            
            while (game.getWindowIsOpen())
            {
                game.update();
                game.render();
            }
            myState = state::TitleScreen;
        }

        if(myState == state::GameServer)
        {
            Game game;
            while (game.getWindowIsOpen())
            {
                game.update();
                game.render();
            }
            myState = state::TitleScreen;
        }
        if(myState == state::Exit) {
            return 1;
        }
    }
}
