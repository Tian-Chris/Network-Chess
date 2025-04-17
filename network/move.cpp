#include <string>
#include <sstream>
#include <iostream>
#include "move.h"

std::string Move::serialize() const {
    return std::to_string(fromRow) + "," + std::to_string(fromCol) + "," +
            std::to_string(toRow) + "," + std::to_string(toCol) + "," +
            std::to_string(playerColor);
}

Move Move::deserialize(const std::string& data) {
    Move move;
    std::stringstream ss(data);
    std::string token;
    std::getline(ss, token, ','); move.fromRow = std::stoi(token);
    std::getline(ss, token, ','); move.fromCol = std::stoi(token);
    std::getline(ss, token, ','); move.toRow = std::stoi(token);
    std::getline(ss, token, ','); move.toCol = std::stoi(token);
    std::getline(ss, token, ','); move.playerColor = std::stoi(token);
    return move;
}