#include <iostream>
#include <employ_factory.h>

int main(int argc, char** argv)
{
    auto john = EmployeeFactory::NewAuxOfficeEmployee("John", 123);
    auto jane = EmployeeFactory::NewMainOfficeEmployee("Jane", 125);

    std::cout << *john << "\n"
         << *jane << "\n"; // note the stars here

    return 0;
}