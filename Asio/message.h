#ifndef MESSAGE_H
#define MESSAGE_H
#include <memory>
#include <vector>
#include <string>

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

    uint32_t getSize() const
    {
        return size;
    }

    uint32_t size = 0;
    std::vector<char> message;
};
    
    #endif
