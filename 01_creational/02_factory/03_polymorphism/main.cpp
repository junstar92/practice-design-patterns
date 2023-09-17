#include <iostream>
#include <wall_factory.h>

int main(int argc, char** argv)
{
    auto const partition = WallFactory::create_wall(WallType::partition, {0, 0}, {5000, 0}, 0, 4200);
    if (partition)
        std::cout << *partition << "\n";

    return 0;
}