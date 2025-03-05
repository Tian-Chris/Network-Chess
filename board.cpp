#include "board.h"

Coord::Coord(int x, int y, int length) : x(x), y(y), length(length) {}

Board::Board(int width, int height) : length(width), height(height), x(0), y(0) {
    cellData = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width, Cell("#00ff00")));
}

void Board::darken() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length; j++) {
            cellData[i][j].visible = 0;
        }
    }
}

void Board::checkVisible(int input, int strength) {
    std::queue<Coord> searchSpace;
    searchSpace.push(Coord(x, y, 0));
    int xArray[4] = {0, 1, 0, -1};
    int yArray[4] = {1, 0, -1, 0};

    bfs(searchSpace, input, xArray, yArray, strength);
}

void Board::bfs(std::queue<Coord>& searchSpace, int input, int xArray[], int yArray[], int strength) {
    while (!searchSpace.empty()) {
        Coord current = searchSpace.front();
        searchSpace.pop();

        if (current.length >= input) return;

        int newLength = current.length + 1;
        for (int t = 0; t < 4; t++) {
            int newX = xArray[t] + current.x;
            int newY = yArray[t] + current.y;

            if (newY >= 0 && newY < height && newX >= 0 && newX < length) {
                if (cellData[newY][newX].checked == 0) {
                    cellData[newY][newX].visible = strength;
                    searchSpace.push(Coord(newX, newY, newLength));
                }
            }
        }
    }
}

void Board::createMapDark(int vision) {
    darken();
    checkVisible(vision, 0.5);
    checkVisible(vision - 2, 1);
    createMapLight();
}

void Board::createMapLight() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length; j++) {
            cellData[i][j].setColor();
        }
    }
}

void Board::move(int dx, int dy) {
    if (cellData[y + dy][x + dx].type == "Ground") {
        cellData[y][x].type = "Ground";
        cellData[y][x].color = "#00ff00";
        x += dx;
        y += dy;
        cellData[y][x].type = "Token";
        cellData[y][x].color = "#ffff00";
    }
}
