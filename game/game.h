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
    void render();
    void loadMap();
    void saveMap();
    void addEntity(); //unfinished
    void removeEntity(); //unfinished
    void loadEntity(); //unfinished
    void sendEntityList(); //unfinished
    void updateEntity(); //unfinishedd
    void drawMap();
    void drawSelected();
    void drawEntities(); 
    bool getColor() const { return color; }
    bool setColor() {color = !(color);}
    
    friend class PlayerInput;
    friend class Ui;
    PlayerInput playerInput;
    bool mousePressed = false;
    bool color = true; //false = black true = white

protected:
    void initVariable();
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

    //objects
    Entity* player;
    void setPlayer(Entity* newPlayer) {
        player = newPlayer;
    }
    Entity* getPlayer() {
        return player;
    }
    std::vector<std::vector<std::unique_ptr<Entity>>> entitiesList;

    //views
    sf::View viewChess;
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