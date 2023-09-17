#pragma once
#include <memory>
#include <hot_drink.h>

struct HotDrinkFactory
{
    virtual ~HotDrinkFactory() = default;
    virtual std::unique_ptr<HotDrink> make() const = 0;
};