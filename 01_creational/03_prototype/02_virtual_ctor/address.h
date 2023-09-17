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

    virtual Address* clone() {
        return new Address{street, city, suite};
    }
};

class ExtendedAddress : public Address
{
public:
    std::string country, postcode;

    ExtendedAddress(std::string_view street, std::string_view city, int const suite, std::string_view country, std::string_view postcode)
     : Address(street, city, suite), country{country}, postcode{postcode} {}
    
    ExtendedAddress* clone() override {
        return new ExtendedAddress(*this); // new ExtendedAddress(street, city, suite, country, postcode);
    }
};