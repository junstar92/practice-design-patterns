#pragma once
#include <vector>
#include <numeric>

struct Verifier
{
    bool verify(std::vector<std::vector<int>> array) const {
        if (array.empty()) return false;
        auto expected = std::accumulate(array[0].begin(), array[0].end(), 0);

        return std::all_of(array.begin(), array.end(), [&](auto& inner) {
            return std::accumulate(inner.begin(), inner.end(), 0) == expected;
        }) && [&]() {
            for (int i = 0; i < array[0].size(); i++) {
                int sum = 0;
                for (int j = 0; j < array.size(); j++) {
                    sum += array[j][i];
                }
                if (sum != expected) return false;
            }
            int d1 = 0, d2 = 0;
            for (int i = 0; i < array.size(); i++) {
                d1 += array[i][i];
                d2 += array[i][array.size() - i - 1];
            }
            if (d1 != expected || d2 != expected) return false;
            return true;
        }();
    }
};