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
    // Mutex to protect access to the queue
    std::mutex myMutex;

    // Queue to store the messages
    std::deque<Message> queue;

    // Condition variable for blocking operations
    std::condition_variable cvBlocking;

    // Mutex for the blocking condition variable
    std::mutex muxBlocking;

    // Deleted copy constructor
    tsqueue(const tsqueue&) = delete;

    // Default constructor
    tsqueue();

    // Destructor
    ~tsqueue();

    // Access front element
    Message& front();

    // Access back element
    Message& back();

    // Pop the front element
    void pop_front();

    // Push back an element
    void push_back(const Message& item);

    // Clear the queue
    void clear();

    // Check if the queue is empty
    bool empty();
};

#endif // TSQ_H
