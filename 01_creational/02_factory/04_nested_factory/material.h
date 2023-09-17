#pragma once
#include <ostream>

enum class Material
{
    brick,
    aerated_concrete,
    drywall
};

inline std::ostream& operator<<(std::ostream& os, Material material)
{
    switch (material)
    {
    case Material::brick: return os << "brick";
    case Material::aerated_concrete: return os << "aerated concrete";
    case Material::drywall: return os << "drywall";
    default: return os;
    }
}