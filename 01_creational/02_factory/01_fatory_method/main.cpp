#include <iostream>
#include <solid_wall.h>

int main(int argc, char** argv)
{
    const auto main_wall = SolidWall::create_main({0,0}, {0,3000}, 2700, 3000);
    if (main_wall)
        std::cout << *main_wall << std::endl;
    else
        std::cout << "Main wall not created\n";

    return 0;
}