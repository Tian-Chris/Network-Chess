#include "game.h"
#include "../global/pch.h"
#include "../layers/cell.h"
#include "../global/globals.h"

// Constructor
Game::Game()        : 
    //videoMode and aspectRatio
    videoMode({1280, 800}),
    aspectRatio(static_cast<float>(videoMode.size.x) / videoMode.size.y),
    viewChess(sf::FloatRect({0.f, 0.f}, {256.f * aspectRatio, 256.f})),
    playerInput(this),
    player(nullptr)

{
    this -> initVariable();
    this -> initWindow();
}

Game::~Game()
{
    delete this->window;
}

void Game::initVariable() {
    this->window = nullptr;

    std::vector<std::string> myVect = {"chessBoard"};
    initGrid(myVect);
    initEntities("chessEntities.txt");
}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(videoMode, "CTTSS");
    this->window->setView(viewChess);

}

void Game::initGrid(std::vector<std::string> myVect) {
    layerNames = myVect;
    // Create the map layer
    for (const auto& name : layerNames) {
        layers.push_back(std::make_unique<Layer>(name + ".txt", gridSize));
    }
}

void Game::initEntities(const std::string& fileName) {
    entitiesList.resize(8);

    // Resize each row to hold 8 columns
    for (auto& row : entitiesList) {
        row.resize(8); // No need to pass nullptr; default initialization works
    }
    
    std::string fullName = "text/" + fileName;
    std::ifstream file(fullName);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::string entityName, imageName;
        int x, y;

        // Read the entity name, image file name, and coordinates
        if (!(stream >> entityName >> imageName >> x >> y)) {
            std::cerr << "Error: Malformed line in " << fileName << ": " << line << std::endl;
            continue;
        }

        // Create a new Entity object
        auto entityPtr = std::make_unique<Entity>("images/" + imageName, sf::Vector2f(x * gridSize, y * gridSize), x, y, entityName);

        // Store the entity in the vector
        entitiesList[x][y] = std::move(entityPtr);
    }

    std::cout << "Entities loaded from " << fileName << ": " << entitiesList.size() << " entities." << std::endl;
}

//Accessors
const bool Game::getWindowIsOpen() const
{
    return this->window->isOpen();
}

void Game::pollEvents()
{
    this->window->setKeyRepeatEnabled(false);
    while (const std::optional<sf::Event> event = this->window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            this->window->close();

        //keyboard inputs
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            playerInput.handleKeyPress(*keyPressed); // Call the input class which handles all button presses from now on
        }
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mousePressed == false)
        {
            mousePressed = true;
            playerInput.handleMouseClick(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), viewChess));
        }
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false)
        {
            mousePressed = false;
        }
    }
}

//Update
void Game::update()
{
    this->pollEvents();
}

void Game::render() {
    this->window->clear(sf::Color::White);
    drawMap();
    drawSelected();
    drawEntities();
    this->window->display();
}

void Game::drawMap() {
    for (const auto& layerPtr : layers) {
        if (layerPtr) { // Ensure the pointer is valid
            layerPtr->draw(*window);
        }
    }
}

void Game::drawSelected() {
    sf::Texture texture;
    if (!texture.loadFromFile("images/selected.png")) {
        throw std::runtime_error("Failed to load texture: images/selected.png");
    }
    sf::Sprite sprite(texture);
    if (player != nullptr) {
        sprite.setPosition({player->getX() * 32.f, player->getY() * 32.f});
        this->window->draw(sprite);
        cout << "drawSelected: x:" << player->getX() << endl;
        cout << "drawSelected: y: " << player->getY() << endl; 
    }
}

void Game::drawEntities() {
    for (int y = 0; y < entitiesList.size(); ++y) {
        for(int x = 0; x < entitiesList[y].size(); ++x) {
            if (entitiesList[x][y] != nullptr) {
                this->window->draw(entitiesList[x][y]->sprite);
            }
        }
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
