#include "chessLogic.h"
#include "vector"
#include "../entities/entities.h"


bool checkMove(std::vector<std::vector<std::unique_ptr<Entity>>>& board, Move move, bool performMove) {
    Entity* piece = board[move.fromRow][move.fromCol].get();

    if (piece == nullptr) {
        std::cerr << "Error at checkMove: No piece at the starting position (" << move.fromRow << ", " << move.fromCol << ")" << std::endl;
        return false;
    }
    if (board[move.toRow][move.toCol] != nullptr && board[move.toRow][move.toCol]->getColor() == move.playerColor) {
        return false;
    }
    if (!isValidMove(board, move)) {
        return false;
    }

    auto temp = std::move(board[move.toRow][move.toCol]);
    board[move.toRow][move.toCol] = std::move(board[move.fromRow][move.fromCol]);
    board[move.fromRow][move.fromCol] = nullptr;

    bool kingCheck = isKingInCheck(board, move.playerColor);

    board[move.fromRow][move.fromCol] = std::move(board[move.toRow][move.toCol]);
    board[move.toRow][move.toCol] = std::move(temp);
    if (kingCheck) {
        return false;
    }

    if(performMove)
    {
        board[move.fromRow][move.fromCol]->setPosition(move.toCol, move.toRow); // Sets x, y position
        board[move.toRow][move.toCol] = std::move(board[move.fromRow][move.fromCol]);
        board[move.fromRow][move.fromCol] = nullptr;
    }
    return true;
}

bool isPathClear(std::vector<std::vector<std::unique_ptr<Entity>>>& board, int fromRow, int fromCol, int toRow, int toCol) {
    int dRow = (toRow - fromRow) == 0 ? 0 : (toRow - fromRow) / abs(toRow - fromRow);
    int dCol = (toCol - fromCol) == 0 ? 0 : (toCol - fromCol) / abs(toCol - fromCol);

    int r = fromRow + dRow;
    int c = fromCol + dCol;

    while (r != toRow || c != toCol) {
        if (board[r][c] != nullptr) 
        {
            //std::cout << board[r][c]->getName() << std::endl;
            //std::cout << "Path is blocked at (" << r << ", " << c << ")" << std::endl;
            return false;
        }
        r += dRow;
        c += dCol;
    }
    return true;
}

bool isValidMove(std::vector<std::vector<std::unique_ptr<Entity>>>& board, Move move) {

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
                if (isPathClear(board, move.fromRow, move.fromCol, move.toRow, move.toCol)) {
                    return true;
                }
            }
            break;
        }
        case ROOK: {
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
        case QUEEN: {
            if (abs(move.toCol - move.fromCol) == abs(move.toRow - move.fromRow)) {
                if (isPathClear(board, move.fromRow, move.fromCol, move.toRow, move.toCol)) {
                    return true;
                }
            }
            else if (move.fromRow == move.toRow) {
                if (isPathClear(board, move.fromRow, move.fromCol, move.toRow, move.toCol)) {
                    return true;
                }
            }
            else if (move.fromCol == move.toCol) {
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

bool isKingInCheck(std::vector<std::vector<std::unique_ptr<Entity>>>& board, bool kingColor) {
    //kinda wasteful
    int kingRow = -1, kingCol = -1;
    for (int row = 0; row < board.size(); ++row) {
        for (int col = 0; col < board[row].size(); ++col) {
            if (board[row][col] != nullptr && board[row][col]->getType() == KING && board[row][col]->getColor() == kingColor) {
                kingRow = row;
                kingCol = col;
                break;
            }
        }
    }

    if (kingRow == -1 || kingCol == -1) {
        std::cerr << "Error: King not found on the board!" << std::endl;
        return false;
    }

    for (int row = 0; row < board.size(); ++row) {
        for (int col = 0; col < board[row].size(); ++col) {
            if (board[row][col] != nullptr && board[row][col]->getColor() != kingColor) {
                Move move = {row, col, kingRow, kingCol, kingColor};
                if (isValidMove(board, move)) {
                    return true; 
                }
            }
        }
    }

    return false; 
}
bool isKingInCheckmate(std::vector<std::vector<std::unique_ptr<Entity>>>& board, bool kingColor) {
    if (!isKingInCheck(board, kingColor)) {
        return false;
    }

    int kingRow = -1, kingCol = -1;
    for (int row = 0; row < board.size(); ++row) {
        for (int col = 0; col < board[row].size(); ++col) {
            if (board[row][col] != nullptr && board[row][col]->getType() == KING && board[row][col]->getColor() == kingColor) {
                kingRow = row;
                kingCol = col;
                break;
            }
        }
    }

    //checkif king can escape
    for (int dRow = -1; dRow <= 1; ++dRow) {
        for (int dCol = -1; dCol <= 1; ++dCol) {
            if (dRow == 0 && dCol == 0) 
            {
                continue;
            }
            int newRow = kingRow + dRow;
            int newCol = kingCol + dCol;

            if (newRow >= 0 && newRow < board.size() && newCol >= 0 && newCol < board[newRow].size()) {
                Move move = {kingRow, kingCol, newRow, newCol, kingColor};
                if (checkMove(board, move, false)) {
                    return false; 
                }
            }
        }
    }

    // Check all other pieces.
    for (int row = 0; row < board.size(); ++row) {
        for (int col = 0; col < board[row].size(); ++col) {
            if (board[row][col] != nullptr && board[row][col]->getColor() == kingColor) {
                for (int targetRow = 0; targetRow < board.size(); ++targetRow) {
                    for (int targetCol = 0; targetCol < board[targetRow].size(); ++targetCol) {
                        Move move = {row, col, targetRow, targetCol, kingColor};
                        if (checkMove(board, move, false)) {
                            return false; 
                        }
                    }
                }
            }
        }
    }

    return true; 
}