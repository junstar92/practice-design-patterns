#include <iostream>
#include <person.h>

int main(int argc, char** argv)
{
    Person* p = new Person("Jane");

    p->greet();

    delete p;

    return 0;
}