#pragma once
#include <vector>
#include <functional>
#include <iostream>

template <class T>
inline void hash_combine(std::size_t &seed, const T &v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

struct Point
{
    int x, y;

    friend size_t hash_value(Point const& obj) {
        size_t seed = 0x725C686F;
        hash_combine(seed, obj.x);
        hash_combine(seed, obj.y);
        return seed;
    }

    friend std::ostream& operator<<(std::ostream& os, Point const& obj) {
        return os
            << "(" << obj.x << "," << obj.y << ")";
    }
};

struct Line
{
    Point start, end;

    friend size_t hash_value(Line const& obj) {
        size_t seed = 0x719E6B16;
        hash_combine(seed, obj.start);
        hash_combine(seed, obj.end);
        return seed;
    }

    friend std::ostream& operator<<(std::ostream& os, Line const& obj) {
        return os
            << "(" << obj.start << ") - (" << obj.end << ")";
    }
};

template <>
struct std::hash<Point>
{
    inline size_t operator()(const Point &v) const
    {
        size_t seed = 0;
        ::hash_combine(seed, v.x);
        ::hash_combine(seed, v.y);
        return seed;
    }
};

template <>
struct std::hash<Line>
{
    inline size_t operator()(const Line &v) const
    {
        size_t seed = 0;
        ::hash_combine(seed, v.start);
        ::hash_combine(seed, v.end);
        return seed;
    }
};

struct VectorObject
{
    virtual std::vector<Line>::iterator begin() = 0;
    virtual std::vector<Line>::iterator end() = 0;
};

struct VectorRectangle : VectorObject
{
    VectorRectangle(int x, int y, int width, int height) {
        lines.emplace_back(Line{ Point{x, y}, Point{x + width, y}});
        lines.emplace_back(Line{ Point{x + width, y}, Point{x + width, y + height} });
        lines.emplace_back(Line{ Point{x, y}, Point{x, y + height}});
        lines.emplace_back(Line{ Point{x, y + height}, Point{x + width, y + height} });
    }

    std::vector<Line>::iterator begin() override {
        return lines.begin();
    }
    std::vector<Line>::iterator end() override {
        return lines.end();
    }

private:
    std::vector<Line> lines;
};