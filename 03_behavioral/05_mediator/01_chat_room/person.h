#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <iostream>

struct ChatRoom;

struct Person
{
    std::string name;
    ChatRoom* room{nullptr};
    std::vector<std::string> chat_log;

    Person(std::string_view name);
    void recieve(std::string const& origin, std::string const& message);
    void say(std::string const& message) const;
    void pm(std::string const& who, std::string const& message) const;
};