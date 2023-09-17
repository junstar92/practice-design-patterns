#include <iostream>
#include <person.h>
#include <person_builder.h>
#include <person_address_builder.h>
#include <person_job_builder.h>

int main(int argc, char** argv)
{
    // Composite Builder
    Person p = Person::create()
        .lives().at("123 London Road")
                .with_postcode("SW1 1GB")
                .in("London")
        .works().at("PragmSoft")
                .as_a("Consultant")
                .earning(10e6);
    std::cout << p << std::endl;
    return 0;
}