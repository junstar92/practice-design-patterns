#include <iostream>
#include <string>
#include <string_view>
#include <functional>
#include <type_traits>

struct Logger
{
    std::function<void()> func;
    std::string name;

    Logger(std::function<void()> const& func, std::string_view name) : func{func}, name{name} {}
    void operator()() const {
        std::cout << "Entering " << name << "\n";
        func();
        std::cout << "Exiting " << name << "\n";
    }
};


template<typename Func>
struct Logger2
{
    Func func;
    std::string name;

    Logger2(Func const& func, std::string_view name) : func{func}, name{name} {}
    void operator()() const {
        std::cout << "Entering " << name << "\n";
        func();
        std::cout << "Exiting " << name << "\n";
    }
};

template<typename Func>
auto make_logger2(Func func, std::string_view name)
{
    return Logger2<Func>{func, name};
}

double add(double a, double b)
{
    std::cout << a << "+" << b << "=" << (a + b) << std::endl;
    return a + b;
}

// base template
template<typename>
struct Logger3;

// patial specialization for Logger3
template<typename R, typename... Args>
struct Logger3<R(Args...)>
{
    std::function<R(Args...)> func;
    std::string name;

    Logger3(std::function<R(Args...)> func, std::string_view name) : func{func}, name{name} {}
    R operator()(Args... args) {
        std::cout << "Entering " << name << std::endl;
        R result = func(args...);
        std::cout << "Exiting " << name << std::endl;
        return result;
    }
};

template<typename R, typename... Args>
auto make_logger3(R(*func)(Args...), std::string_view name)
{
    return Logger3<R(Args...)>(
        std::function<R(Args...)>(func), name
    );
}

int main(int argc, char** argv)
{
    Logger([]() {
        std::cout << "Hello\n";
    }, "HelloFunction")();

    auto call = make_logger2([]() {
        std::cout << "Hello!\n";
    }, "HelloFunction2");
    call();

    auto logged_add = make_logger3(add, "Add");
    auto result = logged_add(2, 3);
    std::cout << "result = " << result << std::endl;

    return 0;
}