#include "header/cell.h"
#include "header/pch.h"

Cell::Cell() : brightness(1), position(0.f, 0.f), spriteType(-1) {}
Cell::Cell(sf::Vector2f pos, int type) : position(pos), brightness(1), spriteType(type) {}