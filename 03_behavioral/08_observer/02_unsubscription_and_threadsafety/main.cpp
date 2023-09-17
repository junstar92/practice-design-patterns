#include <iostream>
#include <person.h>

int main(int argc, char** argv)
{
    Person p{14};
    ConsolePersonObserver cpo;
    p.subscribe(&cpo);
    p.set_age(15);
    p.set_age(16);

    p.unsubscribe(&cpo);
    p.set_age(17);

    Person p2{15};
    TrafficAdministration ta;
    p.subscribe(&ta);
    p.set_age(16);
    p.set_age(17);

    return 0;
}