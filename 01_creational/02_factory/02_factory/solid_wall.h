#pragma once
#include <wall.h>
#include <material.h>

class SolidWall : public Wall
{
public:
    SolidWall(Point2D const start, Point2D const end, int const elevation, int const height, int const width, Material const material)
    :  Wall{start, end, elevation, height}, width{width}, material{material}
    {
        if (elevation < 0 && material == Material::aerated_concrete) {
            throw std::invalid_argument("elevation");
        }
        if (width < 120 && material == Material::brick) {
            throw std::invalid_argument("width");
        }
    }

    friend std::ostream& operator<<(std::ostream& os, SolidWall const& obj) {
        return os
            << static_cast<Wall const&>(obj)
            << " width: " << obj.width
            << " material: " << obj.material;
    }

private:
    int width;
    Material material;
};