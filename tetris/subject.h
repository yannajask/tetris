#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <memory>

class Observer;

class Subject {
    private:
        std::vector<std::shared_ptr<Observer>> observers;

    public:
        virtual ~Subject() = default;

        void attach(std::shared_ptr<Observer> observer);
        void detach(std::shared_ptr<Observer> observer);
        void notifyObservers();
        virtual char getState(int x, int y) const = 0;
};

#endif
