#include <iostream>
#include <string>
#include <variant>

struct AddressPrinter
{
    void operator()(std::string const& house_name) const {
        std::cout << "A house called " << house_name << std::endl;
    }
    void operator()(int const house_number) const {
        std::cout << "House number: " << house_number << std::endl;
    }
};

int main(int argc, char** argv)
{
    std::variant<std::string, int> house;
    house = "ABCD";
    // house = 221;

    AddressPrinter ap;
    std::visit(ap, house);

    // or Using lambda
    std::visit([](auto& arg) {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, std::string>) {
            std::cout << "A house called " << arg.c_str() << std::endl;
        }
        else {
            std::cout << "House number " << arg << std::endl;
        }
    }, house);

    return 0;
}