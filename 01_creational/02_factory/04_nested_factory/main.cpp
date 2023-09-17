#include <iostream>
#include <wall.h>

int main(int argc, char** argv)
{
    auto basic = Wall::factory.create({0, 0}, {5000, 0}, 3, 3000);
    std::cout << *basic << "\n";

    return 0;
}