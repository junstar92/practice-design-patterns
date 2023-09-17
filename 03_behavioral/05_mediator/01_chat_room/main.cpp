#include <iostream>
#include <chatroom.h>

int main(int argc, char** argv)
{
    ChatRoom room;

    Person john{"john"};
    Person jane{"jane"};
    room.join(&john);
    room.join(&jane);
    john.say("hi jane");
    jane.say("oh, hey john");

    Person simon("simon");
    room.join(&simon);
    simon.say("hi everyone!");

    jane.pm("simon", "glad you could join us, simon");

    return 0;
}