#include <iostream>
#include <person.h>

int main(int argc, char** argv)
{
    Person p{14};
    ConsolePersonObserver cpo;
    p.subscribe(&cpo);
    p.set_age(15);
    p.set_age(16);

    return 0;
}