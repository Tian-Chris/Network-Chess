#ifndef UI_H
#define UI_H
//#include "header/observer.h"
#include "../entities/entities.h"
#include "../global/observer.h"

class Ui;
class Game;

enum class mode {
    gameBoard,
    inventory,
    titleScreen,
    settings
};

class InputCatcher : public Observer {
    public:
        InputCatcher(Ui* myUi);
        void onInput(const std::string& input) override;
        Ui* myUi;
};

class Ui {
public:
    Ui(Game* game);
    
    void UpdateHealth();
    void SetPosition(sf::Vector2f input);
    void DrawInventory();
    void SetWindow(sf::RenderWindow* window);
    void SetMode(mode input);
    mode getMode();
    void onInput(const std::string& input);
    int checkValidMove(int y, int x);

    sf::RenderWindow* myWindow;
    Entity healthbar;
    Entity inventory;
    InputCatcher inputCatcher;
    Game* game;  // Pointer to a Game object
    
private:
    int hp;
    mode mode;
};

#endif