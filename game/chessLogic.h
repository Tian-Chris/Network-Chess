#ifndef CHESS_LOGIC_H
#define CHESS_LOGIC_H

#include <vector>
#include <memory>
#include <cmath>
#include "../network/move.h"
class Entity;
class Move;

enum Type {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

bool checkMove(std::vector<std::vector<std::unique_ptr<Entity>>>& board, Move move, bool performMove);
bool isPathClear(std::vector<std::vector<std::unique_ptr<Entity>>>& board, int fromRow, int fromCol, int toRow, int toCol);
bool isValidMove(std::vector<std::vector<std::unique_ptr<Entity>>>& board, Move move);
bool isKingInCheck(std::vector<std::vector<std::unique_ptr<Entity>>>& board, bool kingColor);
bool isKingInCheckmate(std::vector<std::vector<std::unique_ptr<Entity>>>& board, bool kingColor);
#endif 
