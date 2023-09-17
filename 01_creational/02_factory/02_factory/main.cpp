#include <iostream>
#include <wall_factory.h>

int main(int argc, char** argv)
{
    auto const partition = WallFactory::create_partition({2000, 0}, {2000, 4000}, 0, 2700);
    std::cout << *partition << "\n";

    return 0;
}