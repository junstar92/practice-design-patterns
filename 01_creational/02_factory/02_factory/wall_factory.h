#pragma once
#include <vector>
#include <solid_wall.h>

class WallFactory
{
public:
    static std::shared_ptr<SolidWall> create_main(Point2D start, Point2D end, int elevation, int height) {
        return std::make_shared<SolidWall>(start, end, elevation, height, 275, Material::aerated_concrete);
    }

    static std::shared_ptr<SolidWall> create_partition(Point2D start, Point2D end, int elevation, int height) {
        auto const this_wall = new SolidWall{start, end, elevation, height, 120, Material::brick};

        // ensure we don't intersect other walls
        for (auto const wall : walls) {
            if (auto p = wall.lock()) {
                if (this_wall->intersects(*p)) {
                    delete this_wall;
                    return {};
                }
            }
        }

        std::shared_ptr<SolidWall> ptr(this_wall);
        walls.push_back(ptr);
        return ptr;
    }

private:
    static std::vector<std::weak_ptr<Wall>> walls;
};