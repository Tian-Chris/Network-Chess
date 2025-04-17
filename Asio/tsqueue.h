#ifndef TSQ_H
#define TSQ_H

#include <memory>
#include <vector>
#include <string>
#include <deque>
#include <mutex>
#include <condition_variable>
#include "message.h"  // Assuming message.h defines the Message class

class tsqueue {
public:
    tsqueue(const tsqueue&) = delete;

    tsqueue();
    ~tsqueue();
    Message& front();
    Message& back();

    //does not return front element
    void pop_front();
    void push_back(const Message& item);
    void clear();
    bool empty();

    // Mutex to protect access to the queue
    std::mutex myMutex;

    // Queue to store the messages
    std::deque<Message> queue;

    // Condition variable for blocking operations
    std::condition_variable cvBlocking;

    // Mutex for the blocking condition variable
    std::mutex muxBlocking;
    
};

#endif // TSQ_H
