#ifndef GAME_H
#define GAME_H
#include "../layers/layer.h"
#include "../entities/entities.h"
#include "../input/playerInput.h"
#include "../layers/lightMap.h"
#include "../ui/ui.h"

/**
 * @class Game
 * @brief Main game class that handles the game loop, window management, and game state.
 */
class Game {
public:
    Game();
    virtual ~Game();

    const bool getWindowIsOpen() const;
    void pollEvents();
    void update();
    virtual void render();
    void loadMap();
    void saveMap();
    void addEntity(); //unfinished
    void removeEntity(); //unfinished
    void loadEntity(); //unfinished
    void sendEntityList(); //unfinished
    void updateEntity(); //unfinishedd
    void drawMap();
    void drawEntities(); //uninished
    
    friend class PlayerInput;
    friend class Ui;
    PlayerInput playerInput;
    Ui Ui;

protected:
    //init
    virtual void initVariable();
    void initWindow();
    void initGrid(std::vector<std::string> myVect);
    void initEntities(const std::string& fileName); //unfinished

    //window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    float aspectRatio;

    //windowvect
    sf::Vector2f viewCoord;
    
    //layers
    std::vector<std::unique_ptr<Layer>> layers;
    std::vector<std::string> layerNames;
    LightMap light;

    //objects
    std::vector<std::unique_ptr<Entity>> entitiesList;
    Entity* player;

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

class StartMenu {
public:
    StartMenu();
    ~StartMenu();
    sf::VideoMode videoMode;
    sf::RenderWindow* window;
    sf::Font font;
    sf::Text text;

};

#endif