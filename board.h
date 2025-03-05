#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <queue>
#include "cell.h"

class Coord {
public:
    int x, y, length;
    Coord(int x = 0, int y = 0, int length = 0);
};

class Board {
public:
    std::vector<std::vector<Cell>> cellData;
    int x, y, length, height;

    Board(int width, int height);
    
    void darken();
    void checkVisible(int input, int strength);
    void bfs(std::queue<Coord>& searchSpace, int input, int xArray[], int yArray[], int strength);
    void createMapDark(int vision);
    void createMapLight();
    void move(int dx, int dy);
};

#endif // BOARD_H
