#pragma once
#include <vector>
#include <wall.h>
#include <solid_wall.h>

enum class WallType
{
    basic,
    main,
    partition
};

class WallFactory
{
public:
    static std::shared_ptr<Wall> create_wall(WallType type, Point2D start, Point2D end, int elevation, int height) {
        switch (type)
        {
        case WallType::main:
            return std::make_shared<SolidWall>(start, end, elevation, height, 375, Material::aerated_concrete);
        case WallType::partition:
            return std::make_shared<SolidWall>(start, end, elevation, height, 120, Material::brick);
        case WallType::basic:
            return std::shared_ptr<Wall>{new Wall(start, end, elevation, height)};
        }
        return {};
    }

private:
    static std::vector<std::weak_ptr<Wall>> walls;
};