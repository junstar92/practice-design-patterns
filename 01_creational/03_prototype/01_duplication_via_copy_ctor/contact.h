#pragma once
#include <address.h>

class Contact
{
public:
    std::string name;
    Address* address;

    Contact(std::string_view name, Address* address) : name{name}, address{address} {}
    Contact(Contact const& other) : name{other.name}, address{new Address{*other.address}} {}
    Contact& operator=(Contact const& other) {
        if (this == &other) return *this;
        name = other.name;
        address = other.address;
        return *this;
    }
    ~Contact() { delete address; }

    friend std::ostream& operator<<(std::ostream& os, Contact const& obj) {
        return os
            << "name: " << obj.name
            << " works at " << *obj.address;
    }
};