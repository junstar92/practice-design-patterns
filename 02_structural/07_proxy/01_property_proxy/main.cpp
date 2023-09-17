#include <iostream>

template<typename T>
struct Property
{
    T value;
    Property(T const initial_value) {
        *this = initial_value;
    }
    operator T() {
        return value;
    }
    T operator=(T new_value) {
        // perform some setter action
        return value = new_value;
    }
};

struct Creature
{
    Property<int> strength{10};
    Property<int> agility{5};
};

int main(int argc, char** argv)
{
    Creature creature;
    creature.agility = 20; // calls Property<int>::operator=
    auto x = creature.strength; // calls Property<int>::opreator T

    return 0;
}