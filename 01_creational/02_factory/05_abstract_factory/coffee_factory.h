#pragma once
#include <hot_drink.h>
#include <hot_drink_factory.h>

struct CoffeeFactory : HotDrinkFactory
{
    std::unique_ptr<HotDrink> make() const override {
        return std::make_unique<Coffee>();
    }
};