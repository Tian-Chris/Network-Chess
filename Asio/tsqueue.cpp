#ifndef TSQ_H
#define TSQ_H
#include <memory>
#include <vector>
#include <string>
#include <deque>
#include "message.h"

class tsqueue {
public:
    std::mutex myMutex;
    std::deque<Message> queue;
    std::condition_variable cvBlocking;
    std::mutex muxBlocking;

    //deletes copy constructor
    tsqueue(const tsqueue&) = delete;
    tsqueue()
    {
        
    }
    ~tsqueue() 
    { 
        clear(); 
    }

    Message& front()
    {
        std::scoped_lock lock(myMutex);
        return queue.front();
    }
    Message& back()
    {
        std::scoped_lock lock(myMutex);
        return queue.back();
    }

    // Removes and returns item from front of Queue
    void pop_front()
    {
        std::scoped_lock lock(myMutex);
        queue.pop_front();
    }

    void push_back(const Message& item)
    {
        std::scoped_lock lock(myMutex);
        queue.emplace_back(std::move(item));

        std::unique_lock<std::mutex> ul(muxBlocking);
        cvBlocking.notify_one();
    }
    void clear()
    {
        std::scoped_lock lock(myMutex);
        queue.clear();
    }
    bool empty()
    {
        std::scoped_lock lock(myMutex);
        return queue.empty();
    }

};
#endif