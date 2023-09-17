#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <functional>

class MailService
{
    class Email
    {
    public:
        std::string from, to, subject, body;
    };

public:
    class EmailBuilder
    {
    public:
        explicit EmailBuilder(Email& email) : email(email) {}
        EmailBuilder& from(std::string_view from) {
            email.from = from;
            return *this;
        }
        EmailBuilder& to(std::string_view to) {
            email.to = to;
            return *this;
        }
        EmailBuilder& subject(std::string_view subject) {
            email.subject = subject;
            return *this;
        }
        EmailBuilder& body(std::string_view body) {
            email.body = body;
            return *this;
        }

    private:
        Email& email;
    };

    void send_email(std::function<void(EmailBuilder&)> builder) {
        Email email;
        EmailBuilder b{email};
        builder(b);
        send_email_impl(email);
    }

private:
    void send_email_impl(Email const& email) {
        // actually send the email
        std::cout << "Sending email from " << email.from << "\n"
            << "to: " << email.to << "\n"
            << "subj: " << email.subject << "\n"
            << "body: " << email.body << "\n";
    }
};