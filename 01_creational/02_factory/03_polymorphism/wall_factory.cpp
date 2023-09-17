#include <iostream>
#include <vector>
#include <memory>
#include "wall_factory.h"

std::vector<std::weak_ptr<Wall>> WallFactory::walls{};