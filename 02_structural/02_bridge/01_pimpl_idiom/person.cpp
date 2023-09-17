#include <iostream>
#include <person.h>

struct Person::PersonImpl
{
    void greet(Person* p);
};

void Person::PersonImpl::greet(Person* p)
{
    std::cout << "hello " << p->name.c_str();
}

Person::Person(std::string const& name) : name{name}, impl{new PersonImpl} {}
Person::~Person() { delete impl; }

void Person::greet()
{
    impl->greet(this);
}