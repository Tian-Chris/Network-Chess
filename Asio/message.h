#ifndef MESSAGE_H
#define MESSAGE_H
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>


class Message {
public:
    Message(const std::vector<char>& myVect) 
    {
        message = myVect;
    }

    Message() = default;
    
    void setMessage(const std::vector<char>& input)
    {
        message = input;
    }

    void setSize(uint32_t inputSize)
    {
        size = inputSize;
    }

    void setType(uint32_t inputSize)
    {
        type = inputSize;
    }

    uint32_t getSize() const
    {
        return size;
    }

    uint32_t getType() const
    {
        return type;
    }

    void readFile(std::string filename)
    {
        std::ifstream file("../../text/" + filename);
        if (!file) {
            std::cerr << "Failed to open file.\n";
            return;
        }
    
        std::vector<char> contents;
        char c;

        while (file.get(c)) {
            contents.push_back(c);
        }
    
        setSize(contents.size());
        setMessage(contents);
    }

    uint32_t size = 0;
    uint32_t type = 0;
    std::vector<char> message;

};
    
    #endif
