#pragma once
#include <string>
#include <string_view>
#include <iostream>

class Address
{
public:
    std::string street, city;
    int suite;

    Address(std::string_view street, std::string_view city, int const suite)
     : street{street}, city{city}, suite{suite} {}
    
    friend std::ostream& operator<<(std::ostream& os, Address const& obj) {
        return os
            << "street: " << obj.street
            << " city: " << obj.city
            << " suite: " << obj.suite;
    }
};