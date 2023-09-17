#pragma once
#include <string>
#include <vector>
#include <observer.h>

template<typename T>
struct Observable
{
    void notify(T& source, std::string const& name) {
        for (auto obs : observers) {
            obs->field_changed(source, name);
        }
    }

    void subscribe(Observer<T>* observer) {
        observers.push_back(observer);
    }

private:
    std::vector<Observer<T>*> observers;
};