#include "chessLogic.h"
#include "vector"
#include "../entities/entities.h"


bool checkMove(std::vector<std::vector<std::unique_ptr<Entity>>>& board, Move move, bool color) {
    Entity* piece = board[move.fromRow][move.fromCol].get();

    // // Check if the piece exists
    // if (piece == nullptr) {
    //     std::cerr << "Error at checkmove: No piece at the starting position (" << move.fromRow << ", " << move.fromCol << ")" << std::endl;
    //     return false;
    // }
    
    if (board[move.toRow][move.toCol] != nullptr && board[move.toRow][move.toCol]->getColor() == color) {
        return false;
    }

    if (!isValidMove(board, move, color)) {
        return false;
    }

    board[move.fromRow][move.fromCol]->setPosition(move.toCol, move.toRow); //sets x, y position
    board[move.toRow][move.toCol] = std::move(board[move.fromRow][move.fromCol]);
    board[move.fromRow][move.fromCol] = nullptr;
    return true;
}

bool isPathClear(std::vector<std::vector<std::unique_ptr<Entity>>>& board, int fromRow, int fromCol, int toRow, int toCol) {
    int dRow = (toRow - fromRow) == 0 ? 0 : (toRow - fromRow) / abs(toRow - fromRow);
    int dCol = (toCol - fromCol) == 0 ? 0 : (toCol - fromCol) / abs(toCol - fromCol);

    int r = fromRow + dRow;
    int c = fromCol + dCol;

    while (r != toRow || c != toCol) {
        if (board[r][c] != nullptr) return false;
        r += dRow;
        c += dCol;
    }
    return true;
}

bool isValidMove(std::vector<std::vector<std::unique_ptr<Entity>>>& board, Move move, bool myColor) {

    Entity* piece = board[move.fromRow][move.fromCol].get();

    // // Check if the piece exists
    // if (piece == nullptr) {
    //     std::cerr << "Error: No piece at the starting position (" << move.fromRow << ", " << move.fromCol << ")" << std::endl;
    //     return false;
    // }
    switch (piece->getType()) {
        case PAWN: {
            int direction = (piece->getColor() == false) ? 1 : -1;
            if (move.toRow == move.fromRow + direction && move.toCol == move.fromCol && board[move.toRow][move.toCol] == nullptr) {
                return true;
            }
            if (move.toRow == move.fromRow + direction && abs(move.toCol - move.fromCol) == 1 && 
                board[move.toRow][move.toCol] != nullptr && board[move.toRow][move.toCol]->getColor() != piece->getColor()) {
                return true;
            }
            if ((piece->getColor() == false && move.fromRow == 1 && move.toRow == 3 && move.toCol == move.fromCol && 
                 board[2][move.fromCol] == nullptr && board[3][move.fromCol] == nullptr) ||
                (piece->getColor() == true && move.fromRow == 6 && move.toRow == 4 && move.toCol == move.fromCol &&
                 board[4][move.fromCol] == nullptr && board[5][move.fromCol] == nullptr)) {
                return true;
            }
            break;
        }
        case KNIGHT: {
            if ((abs(move.toRow - move.fromRow) == 2 && abs(move.toCol - move.fromCol) == 1) ||
                (abs(move.toRow - move.fromRow) == 1 && abs(move.toCol - move.fromCol) == 2)) {
                return true;
            }
            break;
        }
        case BISHOP: {
            if (abs(move.toCol - move.fromCol) == abs(move.toRow - move.fromRow)) {
                if (isPathClear(board, move.fromCol, move.fromRow, move.toCol, move.toRow)) {
                    return true;
                }
            }
            break;
        }
        case ROOK: {
            if (move.fromRow == move.toRow) {
                if (isPathClear(board, move.fromCol, move.fromRow, move.toCol, move.toRow)) {
                    return true;
                }
            }
            if (move.fromCol == move.toCol) {
                if (isPathClear(board, move.fromCol, move.fromRow, move.toCol, move.toRow)) {
                    return true;
                }
            }
            break;
        }
        case QUEEN: {
            if (abs(move.toCol - move.fromCol) == abs(move.toRow - move.fromRow)) {
                if (isPathClear(board, move.fromCol, move.fromRow, move.toCol, move.toRow)) {
                    return true;
                }
            }
            if (move.fromRow == move.toRow) {
                if (isPathClear(board, move.fromRow, move.fromCol, move.toRow, move.toCol)) {
                    return true;
                }
            }
            if (move.fromCol == move.toCol) {
                if (isPathClear(board, move.fromRow, move.fromCol, move.toRow, move.toCol)) {
                    return true;
                }
            }
            break;
        }
        case KING: {
            if (abs(move.toRow - move.fromRow) <= 1 && abs(move.toCol - move.fromCol) <= 1) {
                return true;
            }
            break;
        }
        default:
            break;
    }

    return false;
}