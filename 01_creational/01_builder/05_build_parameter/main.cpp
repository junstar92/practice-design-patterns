#include <iostream>
#include <email.h>

int main(int argc, char** argv)
{
    // Builder Parameter
    MailService ms;
    ms.send_email([](auto& eb) {
        eb.from("foo@bar.com")
            .to("bar@baz.com")
            .subject("hello")
            .body("Hello, how are you?");
    });

    return 0;
}