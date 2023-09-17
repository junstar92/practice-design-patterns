#include <iostream>
#include <html.h>

int main(int argc, char** argv)
{
    // Fluent HTML Builder
    HtmlBuilder fluent_builder("ul");
    fluent_builder.add_child("li", "hello")
        .add_child("li", "world");
    std::cout << fluent_builder.str() << std::endl;

    return 0;
}