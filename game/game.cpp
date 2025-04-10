#include "../global/pch.h"
#include "game.h"
#include "../layers/cell.h"
#include "../global/globals.h"


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

        //initializes Ui
        Ui(this),
        //object that handles input
        playerInput()
        //myServer(12345)

{   
    //std::cout << "Server started on port 12345" << std::endl;
    //myServer.Start();
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

    //Initializes Ui and adds Ui observer to Subject
    //playerInput.inputReader.addObserver(&Ui.inputCatcher);

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
    //Ui.SetWindow(window);
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
    //Ui.SetPosition(viewCoord);
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
    drawMap();
    this -> window -> draw(player.sprite);
    this -> window -> draw(zombie.sprite);
    this -> window -> draw(lightSprite, sf::BlendMultiply);
    //this -> window -> draw(Ui.healthbar.sprite);
    //Ui.DrawInventory();
    this -> window -> display();
    saveMap();
}
void Game::drawMap() {
    for (const auto& layerPtr : layers) {
        if (layerPtr) { // Ensure the pointer is valid
            layerPtr->draw(*window);
        }
    }
}

void Game::drawEntities() {
    //unfinished
}

void Game::initializeGrid() {
    layerNames = {"background", "obstacles"};
    // Create the map layer
    for (const auto& name : layerNames) {
        layers.push_back(std::make_unique<Layer>(name + ".txt", gridSize));
    }
}

void Game::saveMap() {
    for (const auto& layerPtr : layers) {
        if (layerPtr) {
            layerPtr->saveLayer(layerPtr->getLayerName() + "Test.txt");
        }
    }
}


void Game::loadMap() {
    for (const auto& layerPtr : layers) {
        if (layerPtr) {
            layerPtr->loadFromFile(layerPtr->getLayerName() + ".txt");
        }
    }
}

// Start Menu
StartMenu::StartMenu(): videoMode({1280, 800}),
                        font("text/Arial.ttf"),
                        text(font)
{
    this->window = new sf::RenderWindow(videoMode, "CTTSS");
    text.setString("Start");  // Set the text string
    text.setCharacterSize(50);  // Set the text size
    text.setFillColor(sf::Color::White);  // Set the text color
    text.setPosition({300.f, 250.f});  // Set position in the window
}

StartMenu::~StartMenu()
{
    delete window;
}


