#ifndef CHESS_LOGIC_H
#define CHESS_LOGIC_H

#include <vector>
#include <memory>
#include <cmath>

class Entity;

// Struct representing a chess move
struct Move {
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
};

// Enum representing chess piece types
enum Type {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

// Function declarations
bool checkMove(std::vector<std::vector<std::unique_ptr<Entity>>>& board, Move move, bool color);
bool isPathClear(std::vector<std::vector<std::unique_ptr<Entity>>>& board, int fromRow, int fromCol, int toRow, int toCol);
bool isValidMove(std::vector<std::vector<std::unique_ptr<Entity>>>& board, Move move, bool myColor);

#endif // CHESS_LOGIC_H
