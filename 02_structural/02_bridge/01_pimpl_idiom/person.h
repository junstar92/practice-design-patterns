#pragma once
#include <string>

struct Person
{
    std::string name;
    void greet();

    Person(std::string const& name);
    ~Person();

    class PersonImpl; // forward-declaration to keep a pointer
    PersonImpl* impl;
};