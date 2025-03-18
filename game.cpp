#include "header/pch.h"
#include "header/game.h"
#include "header/cell.h"
#include "header/globals.h"


//Constructor / Destructors
Game::Game() 
        : 
        //videoMode and aspectRatio
        videoMode({1280, 800}),
        aspectRatio(static_cast<float>(videoMode.size.x) / videoMode.size.y),

        //views
        viewStart(sf::FloatRect({0.f, 0.f},{1280.f, 800.f})),
        viewZoom(sf::FloatRect({0.f, 0.f}, {800.f * aspectRatio, 800.f})),
        viewDefault(sf::FloatRect({0.f, 0.f}, {400.f * aspectRatio, 400.f})),

        //gridSize
        //gridSize(50.f),
        light(1280, 800),

        //objects
        player("images/player.png", 10, sf::Vector2f({gridSize, gridSize})),
        zombie("images/enemy.png", 10, sf::Vector2f({128, 128})),

        //object that handles input
        playerInput(this)
{   
    this -> initVariable();
    this -> initWindow();
}

void Game::initVariable() 
{
    // window pointer
    this->window = nullptr;

    // view
    zoom = 0;
    // grid 
    initializeGrid();

    playerInput.inputReader.addObserver(&Ui.inputCatcher);

    // Center the view **once** on the middle of the player
    viewDefault.setCenter(player.sprite.getPosition() + sf::Vector2f(gridSize / 2.f, gridSize / 2.f));
    viewZoom.setCenter(viewDefault.getCenter());
    viewCoord = {640.f, 400.f};
}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(videoMode, "CTTSS");
    this->window->setView(viewDefault);

    //set ui ptr
    Ui.SetWindow(window);
}

Game::~Game()
{
    delete this -> window;
}

//Accessors
const bool Game::getWindowIsOpen() const
{
    return this->window->isOpen();
}

void Game::pollEvents()
{
    this -> window -> setKeyRepeatEnabled(false);
    while (const std::optional event = this -> window -> pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            this -> window -> close();

        //keyboard inputs
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            playerInput.handleKeyPress(*keyPressed); // Call the input class which handles all button presses from now on
        }
    }

    viewCoord = player.sprite.getPosition();
    light.drawSource(sf::Vector2f(static_cast<float>(player.getX() * gridSize), static_cast<float>(player.getY() * gridSize)), 200.f);
    Ui.SetPosition(viewCoord);
}

//Update
void Game::update()
{
    this -> pollEvents();
}

void Game::render()
{
    sf::Sprite lightSprite(light.texture.getTexture());
    this -> window -> clear(sf::Color::Blue);
    backgroundLayer -> draw(*window); 
    obstacleLayer -> draw(*window); 
    this -> window -> draw(player.sprite);
    this -> window -> draw(zombie.sprite);
    this -> window -> draw(lightSprite, sf::BlendMultiply);
    this -> window -> draw(Ui.healthbar.sprite);
    Ui.DrawInventory();
    this -> window -> display();
}

void Game::initializeGrid() {
    // Create the map layer
    backgroundLayer = std::make_unique<Layer>("background.txt", gridSize);
    obstacleLayer = std::make_unique<Layer>("obstacles.txt", gridSize);
}

