#include <iostream>
#include <string>
#include <memory>

struct ILogger
{
    virtual ~ILogger() = default;
    virtual void log(std::string const& s) = 0;
};
struct ConsoleLogger : ILogger
{
    ConsoleLogger() {}
    void log(std::string const& s) override {
        std::cout << "LOG: " << s << std::endl;
    }
};
class Reporting
{
    // it depends on abstract interface.
    // `Reporting` should not depend on a concrete `ConsoleLogger`, but can depend on an ILogger interface.
    ILogger& logger;

public:
    Reporting(ILogger& logger) : logger{logger} {}
    void prepare_report() {
        // logger.log_info("Preparing the report");
        // ...
    }
};

// Let's consider an example of a car which has an engine, but also needs to write to a log.
struct Engine
{
    float volume{5};
    int horse_power{400};

    friend std::ostream& operator<<(std::ostream& os, Engine const& obj) {
        return os
            << "volumn: " << obj.volume
            << " horse_power: " << obj.horse_power;
    }
};

struct Car
{
    // it also depends on abstract interface and can use null object for testing...
    std::unique_ptr<Engine> engine;
    std::shared_ptr<ILogger> logger;
    Car(std::unique_ptr<Engine>& engine, std::shared_ptr<ILogger> const& logger) : engine{std::move(engine)}, logger{logger}
    {
        logger->log("making a car");
    }

    friend std::ostream& operator<<(std::ostream& os, Car const& obj) {
        return os << "car with engine: " << *obj.engine;
    }
};


int main(int argc, char** argv)
{
    // Dependency Inversion Principle (DIP)
    // : High-level modules should not depend on low-level modules. Both should depend on abstractions.
    // Abstractions should not depend on details. Details should depend on abstractions.
    auto engine = std::make_unique<Engine>();
    auto logger = std::make_shared<ConsoleLogger>();
    auto car = Car{engine, logger};

    return 0;
}