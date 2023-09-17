#include <iostream>
#include <html.h>

int main(int argc, char** argv)
{
    // Simple HTML Builder
    HtmlBuilder simple_builder{"ul"};
    simple_builder.add_child("li", "hello");
    simple_builder.add_child("li", "world");
    std::cout << simple_builder.str() << std::endl;

    return 0;
}