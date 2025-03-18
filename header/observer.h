// Observer.h
#ifndef OBSERVER_H
#define OBSERVER_H
#include <vector>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onInput(const std::string& input) = 0;
};
    
class Subject {
public:
    virtual void addObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers(const std::string& input) = 0;

    std::vector<Observer*> observers;
};

//subject for input
class InputReader : public Subject {
public:
    InputReader();
    ~InputReader();

    void addObserver(Observer* observer) override;
    void removeObserver(Observer* observer) override;
    void handleInput();
    void notifyObservers(const std::string& input) override;
};


#endif // OBSERVER_H
