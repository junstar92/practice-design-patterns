#pragma once
#include <person.h>

class PersonAddressBuilder;
class PersonJobBuilder;
class PersonBuilderBase
{
public:
    operator Person() const {
        return std::move(person);
    }

    // builder facets
    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;

protected:
    Person& person;
    explicit PersonBuilderBase(Person& person) : person{person} {
        std::cout << "PersonBuilderBase ctor, " << &person << std::endl;
    }
};

class PersonBuilder : public PersonBuilderBase
{
public:
    PersonBuilder() : PersonBuilderBase{p} {
        std::cout << "PersonBuilder ctor\n";
    }

private:
    Person p;
};