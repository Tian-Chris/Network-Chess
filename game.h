#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "cell.h"

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

private:
    //window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    float aspectRatio;

    //grid
    float gridSize;
    std::vector<std::vector<Cell>> grid;
    std::vector<sf::Texture> textures;  // Store different textures here
    std::vector<sf::Sprite> sprites;
    void drawGrid(); 

    //init
    void initVariable();
    void initWindow();
    void initializeGrid();

    //objects
    sf::Texture mapTexture;
    sf::Sprite map;
    sf::RectangleShape player;

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