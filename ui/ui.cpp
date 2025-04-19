#include "../global/pch.h"
#include "ui.h"
#include "../global/globals.h"
#include "../game/game.h"


Ui::Ui(Game* game): 
        healthbar("../../images/hpFull.png", 10, {16,0}),
        inventory("../../images/inventory.png", 10, {16,200}),
        myWindow(nullptr),
        inputCatcher(this),
        game(game),
        mode(mode::gameBoard)
{
    hp = 10;
}

void Ui::SetWindow(sf::RenderWindow* window)
{
    myWindow = window;
}

//update healthbar
void Ui::UpdateHealth()
{
    if(hp == 10)
    {
        healthbar.reset("../../images/hpFull.png");
    }
    else if(hp == 0)
    {
        healthbar.reset("../../images/hpEmpty.png");
    }
}

void Ui::SetPosition(sf::Vector2f input)
{
    healthbar.sprite.setPosition(input - sf::Vector2f(9.5 * gridSize, 5 * gridSize));
    inventory.sprite.setPosition(input - sf::Vector2f(4.5 * gridSize, 5 * gridSize));
}

void Ui::DrawInventory()
{
    if(mode == mode::inventory)
    {
        myWindow -> draw(inventory.sprite);
    }
}

//mode
mode Ui::getMode()
{
    return mode;
}


//input reader constructor
InputCatcher::InputCatcher(Ui* myUi): myUi(myUi)
{

}

void InputCatcher::onInput(const std::string& input)
{
    myUi -> onInput(input);
}

//hangles input into logic
void Ui::onInput(const std::string& input)
{
    if(getMode() == mode::gameBoard)
    {
        //player movement
        if(input == "w")
        {
            if(checkValidMove(game->player->getY() - 1, game->player->getX()))
            {
                game->player->move('w');
                // game->viewDefault.setCenter(game->player->sprite.getPosition() + sf::Vector2f(gridSize / 2.f, gridSize / 2.f)); 
                // game->viewZoom.setCenter(game->player->sprite.getPosition() + sf::Vector2f(gridSize / 2.f, gridSize / 2.f));  
                // game->window->setView(game->viewDefault);    
            }
        }
        if(input == "a")
        {
            if(checkValidMove(game->player->getY(), game->player->getX() - 1))
            {
                game->player->move('a');
                // game->viewDefault.setCenter(game->player->sprite.getPosition() + sf::Vector2f(gridSize / 2.f, gridSize / 2.f)); 
                // game->viewZoom.setCenter(game->player->sprite.getPosition() + sf::Vector2f(gridSize / 2.f, gridSize / 2.f));  
                // game->window->setView(game->viewDefault);  
            }
        }
        if(input == "d")
        {
            if(checkValidMove(game->player->getY(), game->player->getX() + 1))
            {
                game->player->move('d');
                // game->viewDefault.setCenter(game->player->sprite.getPosition() + sf::Vector2f(gridSize / 2.f, gridSize / 2.f)); 
                // game->viewZoom.setCenter(game->player->sprite.getPosition() + sf::Vector2f(gridSize / 2.f, gridSize / 2.f));  
                // game->window->setView(game->viewDefault); 
            }
        }
        if(input == "s")
        {
            if(checkValidMove(game->player->getY() + 1, game->player->getX()))
            {
                game->player->move('s');
                // game->viewDefault.setCenter(game->player->sprite.getPosition() + sf::Vector2f(gridSize / 2.f, gridSize / 2.f)); 
                // game->viewZoom.setCenter(game->player->sprite.getPosition() + sf::Vector2f(gridSize / 2.f, gridSize / 2.f));  
                // game->window->setView(game->viewDefault);     
            }
        }
        //change mode
        if(input == "Tab")
        {
            mode = mode::inventory;
        }
        if(input == "Esc")
        {
            mode = mode::settings;
        }
    }
    else if(getMode() == mode::inventory)
    {
        if(input == "Tab")
        {
            mode = mode::gameBoard;
        }
    }
    
}

//place this elsewhere
int Ui::checkValidMove(int y, int x)
{
    // Check if the pointer is not null
    if (game->layers[1]->getCellName(y, x) == "Error: Ptr is nullptr") {
        return 1;
    }
    else
    {
        string spriteType = game->layers[1]->getCellName(y, x);
        
        // Check if the spriteType is not empty cell
        if (spriteType == "Empty") {
            return 1;  // valid move (either empty cell or nullptr)
        }
    }

    return 0;  // invalid move (non-empty cell)
}
