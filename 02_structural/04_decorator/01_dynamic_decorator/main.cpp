#include <iostream>
#include <string>
#include <string_view>
#include <sstream>

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
    std::string str() const override {
        std::ostringstream oss;
        oss << "A square with side " << side;
        return oss.str();
    }
};

// dynamic decorator
struct ColoredShape : Shape
{
    Shape& shape;
    std::string color;

    ColoredShape(Shape& shape, std::string_view color) : shape{shape}, color{color} {}

    std::string str() const override {
        std::ostringstream oss;
        oss << shape.str() << " has the color " << color;
        return oss.str();
    }

    void make_dark() {
        if (auto constexpr dark = "dark"; !color.starts_with(dark))
            color.insert(0, dark);
    }
};

struct TransparentShape : Shape
{
    Shape& shape;
    uint8_t transparency;

    TransparentShape(Shape& shape, uint8_t const transparency) : shape{shape}, transparency{transparency} {}

    std::string str() const override {
        std::ostringstream oss;
        oss << shape.str() << " has "
            << static_cast<float>(transparency) / 255.f * 100.f
            << "% transparency";
        return oss.str();
    }
};


int main(int argc, char** argv)
{
    Circle circle{0.5f};
    ColoredShape redCircle{circle, "red"};
    std::cout << redCircle.str() << std::endl;

    redCircle.make_dark();
    std::cout << redCircle.str() << std::endl;

    Square square{3};
    TransparentShape demiSquare{square, 85};
    std::cout << demiSquare.str() << std::endl;

    Circle c{23};
    ColoredShape cs{c, "green"};
    TransparentShape myCircle{cs, 64};
    std::cout << myCircle.str() << std::endl;

    // this is impossible
    // auto s = TransparentShape{ColoredShape{Circle{23}, "green"}, 64};

    // this is impossible, too
    // Circle c2{3};
    // ColoredShape redCircle2{c2, "red"};
    // redCircle2.resize(2); // won't compile

    return 0;
}