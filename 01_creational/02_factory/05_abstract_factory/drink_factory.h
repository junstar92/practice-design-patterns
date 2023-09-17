#pragma once
#include <string>
#include <string_view>
#include <map>
#include <functional>
#include <coffee_factory.h>
#include <tea_factory.h>

class DrinkFactory
{
public:
    DrinkFactory() {
        hot_factories["coffee"] = std::make_unique<CoffeeFactory>();
        hot_factories["tea"] = std::make_unique<TeaFactory>();
    }

    std::unique_ptr<HotDrink> make_drink(std::string_view name) {
        auto drink = hot_factories[name]->make();
        drink->prepare(200);
        return drink;
    }

private:
    std::map<std::string_view, std::unique_ptr<HotDrinkFactory>> hot_factories;
};

// functional factory
// - A class that knows how to create objects
// - A function that, when called, creates an object
class DrinkWithVolumnFactory
{
public:
    DrinkWithVolumnFactory() {
        hot_factories["coffee"] = [] {
            auto coffee = std::make_unique<Coffee>();
            coffee->prepare(200);
            return coffee;
        };
        hot_factories["tea"] = [] {
            auto tea = std::make_unique<Tea>();
            tea->prepare(150);
            return tea;
        };
    }

    std::unique_ptr<HotDrink> make_drink(std::string_view name) {
        return hot_factories[name]();
    }

private:
    std::map<std::string_view, std::function<std::unique_ptr<HotDrink>()>> hot_factories;
};