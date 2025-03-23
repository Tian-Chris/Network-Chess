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

        //initializes Ui
        Ui(this),
        //object that handles input
        playerInput()
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

    //Initializes Ui and adds Ui observer to Subject
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




//Start Menu
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

//button

// class Button {
//     public:
//         Button (sf::Image* normal,sf::Image* clicked,std::string,sf::Vector2f location);
//         void checkClick (sf::Vector2f);
//         void setState(bool);
//         void setText(std::string);
//         bool getVar();
//         sf::Sprite* getSprite();
//         sf::String * getText();
//     private:
//         sf::Sprite normal;
//         sf::Sprite clicked;
//         sf::Sprite* currentSpr;
//         sf::String String;
//         bool current;
//     };
    
//     Button::Button(sf::Image* normal,sf::Image* clicked,std::string words,sf::Vector2f location) {
//         this->normal.SetImage(*normal);
//         this->clicked.SetImage(*clicked);
//         this->currentSpr=&this->normal;
//         current =false;
//         this->normal.SetPosition(location);
//         this->clicked.SetPosition(location);
//         String.SetText(words);
//         String.SetPosition(location.x+3,location.y+3);
//         String.SetSize(14);
//     }
//     void Button::checkClick (sf::Vector2f mousePos) {
//         if (mousePos.x>currentSpr->GetPosition().x && mousePos.x<(currentSpr->GetPosition().x + currentSpr->GetSize().x)) {
//             if(mousePos.y>currentSpr->GetPosition().y && mousePos.y<(currentSpr->GetPosition().y + currentSpr->GetSize().y)) {
//                 setState(!current);
//             }
//         }
//     }
//     void Button::setState(bool which) {
//         current = which;
//         if (current) {
//             currentSpr=&clicked;
//             return;
//         }
//         currentSpr=&normal;
//     }
//     void Button::setText(std::string words) {
//         String.SetText(words);
//     }
//     bool Button::getVar() {
//         return current;
//     }
//     sf::Sprite* Button::getSprite() {
//         return currentSpr;
//     }
    
//     sf::String * Button::getText() {
//         return &String;
//     }