#ifndef MESSAGE_H
#define MESSAGE_H
#include <memory>
#include <vector>
#include <string>

class Message {
public:
    Message(std::vector<std::string>& myVect) 
    {
        message = myVect;
    }

    Message()
    {

    }
    
    void setMessage(std::vector<std::string>& input)
    {
        message = input;
    }

    void setSize(uint32_t inputSize)
    {
        size = inputSize;
    }

    uint32_t getSize()
    {
        return size;
    }


    uint32_t size = 0;
    std::vector<std::string> message;
};
#endif
