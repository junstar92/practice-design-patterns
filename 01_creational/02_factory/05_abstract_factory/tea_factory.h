#pragma once
#include <hot_drink.h>
#include <hot_drink_factory.h>

struct TeaFactory : HotDrinkFactory
{
    std::unique_ptr<HotDrink> make() const override {
        return std::make_unique<Tea>();
    }
};