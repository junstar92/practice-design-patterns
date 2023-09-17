#include <iostream>
#include <string>
#include <memory>

struct Logger
{
    virtual ~Logger() = default;
    virtual void info(std::string const& s) = 0;
    virtual void warn(std::string const& s) = 0;
};

struct ConsoleLogger : Logger
{
    void info(std::string const& s) override {
        std::cout << "INFO: " << s << std::endl;
    }
    void warn(std::string const& s) override {
        std::cout << "WARNING!!! " << s << std::endl;
    }
};

struct NullLogger final : Logger
{
    void info(std::string const& s) override {}
    void warn(std::string const& s) override {}
};

struct OptionalLogger : Logger
{
    std::shared_ptr<Logger> impl;
    static std::shared_ptr<Logger> no_logging;

    OptionalLogger(std::shared_ptr<Logger> const& logger) : impl{logger} {}

    virtual void info(std::string const& s) override {
        if (impl) impl->info(s); //null check here
    }
    virtual void warn(std::string const& s) override {
        if (impl) impl->warn(s); // null check here
    }
};
// static instance of a null object
std::shared_ptr<Logger> OptionalLogger::no_logging{};

class BankAccount1
{
    std::shared_ptr<Logger> log;

public:
    std::string name;
    int balance = 0;

    BankAccount1(std::shared_ptr<Logger> const& logger, std::string const& name, int balance)
    : log{logger}, name{name}, balance{balance} {}

    void deposit(int amount) {
        balance += amount;
        log->info("Deposited $" + std::to_string(amount) + " to " + name + ", balance is now $" + std::to_string(balance));
    }
};

class BankAccount2
{
    std::shared_ptr<OptionalLogger> log;

public:
    std::string name;
    int balance = 0;

    BankAccount2(std::string const& name, int balance, std::shared_ptr<Logger> const& logger = OptionalLogger::no_logging)
    : log{std::make_shared<OptionalLogger>(logger)}, name{name}, balance{balance} {}

    void deposit(int amount) {
        balance += amount;
        log->info("Deposited $" + std::to_string(amount) + " to " + name + ", balance is now $" + std::to_string(balance));
    }
};

int main(int argc, char** argv)
{
    auto null_logger = std::make_shared<NullLogger>();
    BankAccount1 ba1{null_logger, "account 1", 1000}; // shared_ptr is not a null object
    ba1.deposit(100);

    BankAccount2 ba2{"account 2", 2000}; // using implicit null object
    ba2.deposit(100);

    return 0;
}