#pragma once
#include <iostream>
#include <string>
#include <string_view>

class PersonBuilder;
class Person
{
public:
    ~Person() {
        std::cout << "Person destroyed\n";
    }
    
    static PersonBuilder create();
    
    Person(Person&& other)
      : street_address{std::move(other.street_address)},
        post_code{std::move(other.post_code)},
        city{std::move(other.city)},
        company_name{std::move(other.company_name)},
        position{std::move(other.position)},
        annual_income{other.annual_income} {
        std::cout << "Person move ctor\n";
    }
    Person& operator=(Person&& other) {
        std::cout << "Person move assignment\n";
        if (this == &other) return *this;
        street_address = std::move(other.street_address);
        post_code = std::move(other.post_code);
        city = std::move(other.city);
        company_name = std::move(other.company_name);
        position = std::move(other.position);
        annual_income = other.annual_income;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, Person const& p) {
        return os
            << "street_address: " << p.street_address
            << " post_code: " << p.post_code
            << " city: " << p.city
            << " company_name: " << p.company_name
            << " position: " << p.position
            << " annual_income: " << p.annual_income;
    }

    friend class PersonBuilder;
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;

private:
    // address
    std::string street_address, post_code, city;
    // employment
    std::string company_name, position;
    int annual_income{0};

    Person() {
        std::cout << "Person created at " <<  this << "\n";
    }
};