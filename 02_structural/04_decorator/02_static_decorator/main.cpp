#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
#include <type_traits>

struct Shape
{
    virtual std::string str() const = 0;
};

struct Circle : Shape
{
    float radius;

    explicit Circle(float const radius) : radius{radius} {}
    void resize(float const factor) { radius *= factor; }
    std::string str() const override {
        std::ostringstream oss;
        oss << "A circle of radius " << radius;
        return oss.str();
    }
};

struct Square : Shape
{
    float side;

    Square() {}
    explicit Square(float const side) : side{side} {}
    void resize(float const side) { this->side = side; }
    std::string str() const override {
        std::ostringstream oss;
        oss << "A square with side " << side;
        return oss.str();
    }
};

// static decorator
template<typename T>
struct ColoredShape : T
{
    static_assert(std::is_base_of_v<Shape, T>, "Template argument must be a Shape");

    std::string color;

    template<typename... Args>
    ColoredShape(std::string_view color, Args... args) : T{std::forward<Args>(args)...}, color{color} {}

    std::string str() const override {
        std::ostringstream oss;
        oss << T::str() << " has the color " << color;
        return oss.str();
    }

    void make_dark() {
        if (auto constexpr dark = "dark"; !color.starts_with(dark))
            color.insert(0, dark);
    }
};

template<typename T>
struct TransparentShape : T
{
    static_assert(std::is_base_of_v<Shape, T>, "Template argument must be a Shape");

    uint8_t transparency;

    template<typename... Args>
    TransparentShape(uint8_t const transparency, Args... args) : T{std::forward<Args>(args)...}, transparency{transparency} {}

    std::string str() const override {
        std::ostringstream oss;
        oss << T::str() << " has "
            << static_cast<float>(transparency) / 255.f * 100.f
            << "% transparency";
        return oss.str();
    }
};


int main(int argc, char** argv)
{
    ColoredShape<TransparentShape<Square>> square{"blue", (uint8_t)255};
    square.side = 2;
    square.transparency = (uint8_t)127;
    std::cout << square.str() << std::endl;
    square.resize(25);
    std::cout << square.str() << std::endl;

    ColoredShape<TransparentShape<Square>> sq{"red", (uint8_t)51, 5.f};
    std::cout << sq.str() << std::endl;

    ColoredShape<TransparentShape<ColoredShape<Circle>>> circle{"red", (uint8_t)255, "blue", 3.f};
    std::cout << circle.str() << std::endl;

    return 0;
}