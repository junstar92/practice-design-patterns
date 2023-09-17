#include <chatroom.h>
#include <algorithm>

void ChatRoom::join(Person* p)
{
    std::string join_msg = p->name + " joins the chat";
    broadcast("room", join_msg);
    p->room = this;
    people.push_back(p);
}

void ChatRoom::broadcast(std::string const& origin, std::string const& message)
{
    for (auto p : people) {
        if (p->name != origin)
            p->recieve(origin, message);
    }
}

void ChatRoom::message(std::string const& origin, std::string const& who, std::string const& message)
{
    auto target = std::find_if(people.begin(), people.end(), [&who](Person const* p) {
        return p->name == who;
    });
    if (target != people.end()) {
        (*target)->recieve(origin, message);
    }
}