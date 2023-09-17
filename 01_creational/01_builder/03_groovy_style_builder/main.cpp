#include <iostream>
#include <html.h>

int main(int argc, char** argv)
{
    // Groovy-Style Builder
    std::cout << 
        P{
            IMG{ "http://pokemon.com/pikachu.png" }
        }
        << std::endl;

    return 0;
}