#include <iostream>
#include <contact.h>

int main(int argc, char** argv)
{
    // this is tedious
    // Contact john{ "John Doe", new Address{"123 East Dr", "London"} };
    // Contact jane{ "Jane Doe", new Address{"123 East Dr", "London"} };

    Contact worker{"", new Address{"123 East Dr", "London", 0}};
    Contact john{worker}; // or Contact john = worker;
    john.name = "John";
    john.address->suite = 123;

    Contact jane = worker;
    jane.name = "Jane";
    jane.address->suite = 125;

    std::cout << john << std::endl;
    std::cout << jane << std::endl;

    return 0;
}