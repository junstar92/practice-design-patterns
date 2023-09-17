#pragma once
#include <observable.h>

struct Person : Observable<Person>
{
    Person(int const age) : age{age} {}
    int get_age() const { return age; }
    void set_age(int const age) { 
        if (this->age == age) return;

        auto old_can_vote = get_can_vote(); // store old value
        this->age = age;
        notify(*this, "age");

        if (old_can_vote != get_can_vote()) // check value has changed
            notify(*this, "can_vote");
    }
    bool get_can_vote() const {
        // can_vote has no backing field and no setter
        // but this property can be chaged by set_age().
        return age >= 16;
    }

private:
    int age;
};

struct ConsolePersonObserver : Observer<Person>
{
    void field_changed(Person& source, std::string const& field_name) override {
        if (field_name == "age") {
            std::cout << "Person's age has changed to " << source.get_age() << ".\n";
        }
        else if (field_name == "can_vote") {
            std::cout << "Person's can_vote has changed to " << std::boolalpha << source.get_can_vote() << ".\n";
        }
    }
};