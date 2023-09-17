#pragma once
#include <string>
#include <vector>
#include <mutex>
#include <observer.h>

template<typename T>
struct Observable
{
    void notify(T& source, std::string const& name) {
        std::vector<Observer<T>*> observers_copy;
        {
            std::lock_guard lock{mtx};
            observers_copy = observers;
        }
        for (auto obs : observers_copy) {
            if (obs)
                obs->field_changed(source, name);
        }
    }

    void subscribe(Observer<T>* observer) {
        std::scoped_lock lock{mtx};
        observers.push_back(observer);
    }

    void unsubscribe(Observer<T>* observer) {
        std::scoped_lock lock{mtx};
        // observers.erase(
        //     std::remove(observers.begin(), observers.end(), observer),
        //     observers.end()
        // );
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            *it = nullptr;
        }
    }

private:
    std::vector<Observer<T>*> observers;
    std::mutex mtx;
};