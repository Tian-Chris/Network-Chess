#ifndef GAME_H
#define GAME_H
#include "layer.h"
#include "entities.h"
#include "playerInput.h"


class Game {
public:
    //Constructor / Desctructor
    Game();
    virtual ~Game();

    //Accessors
    const bool getWindowIsOpen() const;

    //update
    void pollEvents();
    void update();
    void render();

    
    //handlesinput
    friend class PlayerInput;
    PlayerInput playerInput;

private:
    //window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    float aspectRatio;

    //grid
    float gridSize;
    // std::vector<std::vector<Cell>> grid;
    // std::vector<sf::Texture> textures;  // Store different textures here
    // std::vector<sf::Sprite> sprites;
    // void drawGrid(); 
    std::unique_ptr<Layer> backgroundLayer;
    std::unique_ptr<Layer> obstacleLayer;

    //init
    void initVariable();
    void initWindow();
    void initializeGrid();

    //objects
    Entity player;

    //views
    sf::View viewStart;
    sf::View viewDefault;
    sf::View viewZoom;
    int currentView;
    int zoom;
};

enum ViewMode {
    Default = 0,   // Default view
    Zoom = 1,  // Zoomed-out view
    Full = 2, //entire map
};

#endif