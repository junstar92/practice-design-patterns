#include <iostream>
#include <string>

template<typename TFrom, typename TTo>
class Converter
{
public:
    virtual TTo convert(TFrom const& from) = 0;
    virtual TFrom convert_back(TTo const& to) = 0;
};

class IntToStringConverter : Converter<int, std::string>
{
public:
    std::string convert(int const& from) override {
        return std::to_string(from);
    }

    int convert_back(std::string const& to) override {
        int result;
        try {
            result = std::stoi(to);
        }
        catch(...) {
            return std::numeric_limits<int>::min();
        }
        return result;
    }
};

int main(int argc, char** argv)
{
    IntToStringConverter converter;
    std::cout << converter.convert(123) << "\n";            // 123
    std::cout << converter.convert_back("456") << "\n";     // 456
    std::cout << converter.convert_back("xyz") << "\n";     // -2147483648

    return 0;
}