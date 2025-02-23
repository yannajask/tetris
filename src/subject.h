#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <memory>

class Observer;

class Subject {
    private:
        std::vector<Observer*> observers;

    public:
        virtual ~Subject() = default;

        void attach(Observer *observer);
        void detach(Observer *observer);
        void notifyObservers();
        virtual char getState(int x, int y) const = 0;
};

#endif
