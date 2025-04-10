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

    /**
     * @brief Checks if the window is still open.
     * @return True if the window is open, false otherwise.
     */
    const bool getWindowIsOpen() const;

    /**
     * @brief Polls for input events (keyboard, mouse, etc.).
     */
    void pollEvents();

    /**
     * @brief Updates the game state.
     */
    void update();

    /**
     * @brief Renders the game objects to the window.
     */
    void render();

    /**
     * @brief Adds an entity to the game (unfinished).
     */
    void addEntity(); //unfinished

    /**
     * @brief Removes an entity from the game (unfinished).
     */
    void removeEntity(); //unfinished

    /**
     * @brief Loads the game map (unfinished).
     */
    void loadMap(); //unfinished

    /**
     * @brief Saves the game map (unfinished).
     */
    void saveMap();

    /**
     * @brief Loads the entity list (unfinished).
     */
    void loadEntityList(); //unfinished

    /**
     * @brief Loads a specific entity (unfinished).
     */
    void loadEntity(); //unfinished

    /**
     * @brief Sends the entity list (unfinished).
     */
    void sendEntityList(); //unfinished

    /**
     * @brief Updates the entity state (unfinished).
     */
    void updateEntity(); //unfinishedd

    /**
     * @brief draws map
     */
    void drawMap();

    /**
     * @brief draws entities. Unfinished
     */
    void drawEntities(); //uninished
    
    //handlesinput
    /**
     * @brief Handles player input.
     */
    friend class PlayerInput;

    /**
     * @brief Handles UI interactions.
     */
    friend class Ui;

    /**
     * @brief Handles player input.
     */
    PlayerInput playerInput;
    //UI
    Ui Ui;

protected:
    //init
    /**
     * @brief Initializes game variables.
     */
    void initVariable();

    /**
     * @brief Initializes the game window.
     */
    void initWindow();

    /**
     * @brief Initializes the game grid.
     */
    void initializeGrid();

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
    Entity player;
    Entity zombie;

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