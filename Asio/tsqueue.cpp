#include "tsqueue.h"

tsqueue::tsqueue() {}
tsqueue::~tsqueue() {
    clear();
}

Message& tsqueue::front() {
    std::scoped_lock lock(myMutex);
    return queue.front();
}

Message& tsqueue::back() {
    std::scoped_lock lock(myMutex);
    return queue.back();
}

void tsqueue::pop_front() {
    std::scoped_lock lock(myMutex);
    queue.pop_front();
}

void tsqueue::push_back(const Message& item) {
    std::scoped_lock lock(myMutex);
    queue.emplace_back(item);

    std::unique_lock<std::mutex> ul(muxBlocking);
    cvBlocking.notify_one();
}

void tsqueue::clear() {
    std::scoped_lock lock(myMutex);
    queue.clear();
}

bool tsqueue::empty() {
    std::scoped_lock lock(myMutex);
    return queue.empty();
}
