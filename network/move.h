#ifndef MOVE_H
#define MOVE_H

#include <string>

struct Move {
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
    bool playerColor; // true for white, false for black

    std::string serialize() const;

    static Move deserialize(const std::string& data);
};

#endif
