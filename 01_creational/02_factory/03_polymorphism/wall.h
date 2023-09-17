#pragma once
#include <ostream>
#include <memory>

class Point2D
{
public:
    int x, y;

    Point2D(int const x, int const y) : x{x}, y{y} {}

    friend std::ostream& operator<<(std::ostream& os, Point2D const& obj) {
        return os
            << "(" << obj.x
            << "," << obj.y << ")";
    }
};

class Wall
{
public:
    virtual ~Wall() = default;
    friend std::ostream& operator<<(std::ostream& os, Wall const& obj) {
        return os
            << "start: " << obj.start
            << " end: " << obj.end
            << " elevation: " << obj.elevation
            << " height: " << obj.height;
    }

    bool intersects(Wall const& other) const {
        return false;
    }

protected:
    Wall(Point2D const start, Point2D const end, int const elevation, int const height)
      : start{start}, end{end}, elevation{elevation}, height{height} {}
    
    friend class WallFactory;

private:
    Point2D start, end;
    int elevation;
    int height;
};