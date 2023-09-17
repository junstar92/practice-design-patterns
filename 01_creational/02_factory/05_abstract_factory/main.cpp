#include <iostream>
#include <drink_factory.h>

int main(int argc, char** argv)
{
    auto drink_factory1 = DrinkFactory();
    auto coffee = drink_factory1.make_drink("coffee");

    auto drink_factory2 = DrinkWithVolumnFactory();
    auto tea = drink_factory2.make_drink("tea");
    
    return 0;
}