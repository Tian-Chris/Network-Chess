#include "tsqueue.h"

// Default constructor
tsqueue::tsqueue() {}

// Destructor
tsqueue::~tsqueue() {
    clear();
}

// Access the front element
Message& tsqueue::front() {
    std::scoped_lock lock(myMutex);
    return queue.front();
}

// Access the back element
Message& tsqueue::back() {
    std::scoped_lock lock(myMutex);
    return queue.back();
}

// Pop the front element
void tsqueue::pop_front() {
    std::scoped_lock lock(myMutex);
    queue.pop_front();
}

// Push an element to the back
void tsqueue::push_back(const Message& item) {
    std::scoped_lock lock(myMutex);
    queue.emplace_back(item);

    std::unique_lock<std::mutex> ul(muxBlocking);
    cvBlocking.notify_one();
}

// Clear the queue
void tsqueue::clear() {
    std::scoped_lock lock(myMutex);
    queue.clear();
}

// Check if the queue is empty
bool tsqueue::empty() {
    std::scoped_lock lock(myMutex);
    return queue.empty();
}
