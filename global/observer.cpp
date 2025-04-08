#include "observer.h"

void InputReader::addObserver(Observer* observer) {
    observers.push_back(observer);
}

void InputReader::removeObserver(Observer* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void InputReader::handleInput() {};

void InputReader::notifyObservers(const std::string& input) {
    for (auto observer : observers) {
        observer->onInput(input);
    }
}

InputReader::InputReader() {

}
InputReader::~InputReader() {

}