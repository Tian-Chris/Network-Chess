#include "cell.h"

Cell::Cell() : brightness(1), position(0, 0), spriteType(0) {}
Cell::Cell(sf::Vector2f pos, int type) : position(pos), brightness(1), spriteType(type) {}