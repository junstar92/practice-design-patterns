#include <iostream>
#include <address.h>
#include <contact.h>

int main(int argc, char** argv)
{
    ExtendedAddress ea{"123 West Dr", "London", 123, "UK", "SW101EG"};
    Address& a = ea;
    auto cloned = a.clone();
    std::cout << a << "(" << &a << ")" << std::endl;
    std::cout << *cloned << "(" << &cloned << ")" << std::endl;

    delete cloned;

    return 0;
}