#pragma once
#include <vector>
#include <string>
#include <person.h>

struct ChatRoom
{
    std::vector<Person*> people;

    void join(Person* p);
    void broadcast(std::string const& origin, std::string const& message);
    void message(std::string const& origin, std::string const& who, std::string const& message);
};