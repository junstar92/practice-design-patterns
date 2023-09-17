#pragma once
#include <vector>
#include <set>

struct Generator
{
    virtual std::vector<int> generate(int const count) const {
        std::vector<int> result(count);
        std::generate(result.begin(), result.end(), [&]() {
            return 1 + rand() % (count * count);
        });
        return result;
    }
};

struct UniqueGeneartor : Generator
{
    std::vector<int> generate(int const count) const override {
        std::vector<int> result;
        do {
            result = Generator::generate(count);
        } while (std::set<int>(result.begin(), result.end()).size() != result.size());
        return result;
    }
};