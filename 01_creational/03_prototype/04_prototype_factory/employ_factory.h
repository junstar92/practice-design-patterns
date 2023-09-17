#pragma once
#include <contact.h>
#include <memory>

class EmployeeFactory
{
public:
    static std::unique_ptr<Contact> NewMainOfficeEmployee(std::string_view name, int const suite) {
        return NewEmployee(name, suite, main);
    }

    static std::unique_ptr<Contact> NewAuxOfficeEmployee(std::string_view name, int const suite) {
        return NewEmployee(name, suite, aux);
    }

private:
    static Contact main;
    static Contact aux;

    static std::unique_ptr<Contact> NewEmployee(std::string_view name, int const suite, Contact const& proto) {
        auto result = std::make_unique<Contact>(proto);
        result->name = name;
        result->address->suite = suite;
        return result;
    }
};