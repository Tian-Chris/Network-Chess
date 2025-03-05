#include "game.h"

//Constructor / Destructors
Game::Game() 
        : 
        //videoMode and aspectRatio
        videoMode({1280, 800}),
        aspectRatio(static_cast<float>(videoMode.size.x) / videoMode.size.y),

        //views
        viewStart(sf::FloatRect({0.f, 0.f},{1280.f, 800.f})),
        viewZoom(sf::FloatRect({0.f, 0.f}, {400.f * aspectRatio, 400.f})),
        viewDefault(sf::FloatRect({0.f, 0.f}, {200.f * aspectRatio, 200.f})),

        //map and sprite
        mapTexture("images/test.png"),
        map(mapTexture),

        //gridSize
        gridSize(15.f),

        //objects
        player({gridSize, gridSize})
{   
    this -> initVariable();
    this -> initWindow();
}

void Game::initVariable() 
{
    //windowptr
    this->window = nullptr;

    //view
    zoom = 0;

    //grid 
    initializeGrid();

    //map
    map.scale(sf::Vector2f(1, 1));
    map.setPosition(sf::Vector2f(0,0));

    //objects
    player.setOrigin({gridSize / 2.f, gridSize / 2.f});
}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(videoMode, "CTTSS");
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
            if (keyPressed->scancode == sf::Keyboard::Scan::Escape)
            {
                this -> window -> close();
            }
            if ((keyPressed->scancode == sf::Keyboard::Scan::Tab) && (zoom == 1))
            {
                this -> window -> setView(viewDefault);
                zoom = 0;
            }
            else if ((keyPressed->scancode == sf::Keyboard::Scan::Tab) && (zoom == 0))
            {
                this -> window -> setView(viewZoom);
                zoom = 1;
            }
            if (keyPressed->scancode == sf::Keyboard::Scan::W)
            {
                player.move({0.f, -gridSize});
                viewDefault.setCenter(player.getPosition()); 
                viewZoom.setCenter(player.getPosition());  
                this -> window -> setView(viewDefault);                  
            }
            if (keyPressed->scancode == sf::Keyboard::Scan::A)
            {
                player.move({-gridSize, 0.f});                    
                viewDefault.setCenter(player.getPosition()); 
                viewZoom.setCenter(player.getPosition());  
                this -> window -> setView(viewDefault);        
            }
            if (keyPressed->scancode == sf::Keyboard::Scan::S)
            {
                player.move({0.f, gridSize});
                viewDefault.setCenter(player.getPosition()); 
                viewZoom.setCenter(player.getPosition());  
                this -> window -> setView(viewDefault);                           
            }                
            if (keyPressed->scancode == sf::Keyboard::Scan::D)
            {
                player.move({gridSize, 0.f});
                viewDefault.setCenter(player.getPosition()); 
                viewZoom.setCenter(player.getPosition());  
                this -> window -> setView(viewDefault);                            
            }                                
        }
    }
}

//Update
void Game::update()
{
    this -> pollEvents();
}

void Game::render()
{
    this -> window -> clear(sf::Color::Blue);
    this -> window -> draw(map);
    this -> window -> draw(player);
    this -> drawGrid();
    this -> window -> display();
}

void Game::initializeGrid() {
    textures.resize(2);
    if (!textures[0].loadFromFile("images/grass.png") || !textures[1].loadFromFile("images/catbit.png")) {
        //cout << "Error: Could not load textures!" << std::endl;
        return;
    }

    // Resize grid
    grid.resize(20);
    for (int y = 0; y < 20; y++) {
        grid[y].resize(40, Cell(sf::Vector2f(0, 0), 0));  // Resize each row to 40 cells, each having default values
    }

    // Initialize cells and sprites
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 40; x++) {
            grid[y][x] = Cell(sf::Vector2f(x * 100.f, y * 100.f), 0);  // Random type (0 or 1)

            // Create sprite based on grid position and sprite type
            sf::Sprite sprite(textures[grid[y][x].spriteType]);
            sprite.setPosition(grid[y][x].position);
            sprites.push_back(sprite);  // Store sprite separately
        }
    }
}

void Game::drawGrid() {
    for (size_t i = 0; i < sprites.size(); i++) {
        this -> window -> draw(sprites[i]);
    }
}
