#include <iostream>

class Rectangle
{
protected:
    int width, height;

public:
    Rectangle(int const width, int const height) : width{width}, height{height} {}

    int get_width() const { return width; }
    virtual void set_width(int const width) { this->width = width; }
    int get_height() const { return height; }
    virtual void set_height(int const height) { this->height = height; }
    int area() const { return width * height; }
};

// Derived class `Square` breaks LSP.
class Square : public Rectangle
{
public:
    Square(int size) : Rectangle(size, size) {}

    void set_width(int const width) override {
        this->width = height = width;
    }
    void set_height(int const height) override {
        this->height = width = height;
    }
};

int main(int argc, char** argv)
{
    // Liskov Substitution Principle (LSP)
    // that if an interface takes an object of type `Parent`,
    // it should equally take an object of type `Child` without anything breaking.

    auto process = [](Rectangle& r) {
        int w = r.get_width();
        r.set_height(10);
        std::cout << "expected area = " << (w * 10)
            << ", got " << r.area() << std::endl;
    };
    Rectangle r{3,4};
    process(r); // expected area = 30, got 30

    Square sq{5};
    process(sq); // expected area = 50, got 100

    return 0;
}