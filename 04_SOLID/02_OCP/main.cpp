#include <iostream>
#include <string>
#include <vector>

enum class Color { Red, Green, Blue };
enum class Size { Small, Medium, Large };
struct Product
{
    std::string name;
    Color color;
    Size size;
};

struct ProductFilter
{
    typedef std::vector<Product*> Items;

    ProductFilter::Items by_color(Items items, Color color) {
        Items result;
        for (auto& i : items) {
            if (i->color == color)
                result.push_back(i);
        }
        return result;
    }
    // 'by_size' feels like outright duplication.
    ProductFilter::Items by_size(Items items, Size size) {
        Items result;
        for (auto& i : items) {
            if (i->size == size)
                result.push_back(i);
        }
        return result;
    }
    ProductFilter::Items by_color_and_size(Items items, Color color, Size size) {
        Items result;
        for (auto& i : items) {
            if (i->color == color && i->size == size)
                result.push_back(i);
        }
        return result;
    }
};

// We want from this scenario is to enforce the OCP that
// states that a type is open for EXTENSION but closed for MODIFICATION.
// In other words, we want filtering that is extensible without having to modify it.
// To acheive this,
// first of all, we conceptually separate our filtering process into two parts: a filter and a specification
// - a filter: a process which takes all items and only returns some
// - a specification: the definition of a predicate to apply to a data element
template<typename T>
struct AndSpecification;
template<typename T>
struct Specification
{
    virtual bool is_satisfied(T* item) const = 0;
};

template<typename T>
struct Filter
{
    virtual std::vector<T*> filter(
        std::vector<T*> items,
        Specification<T> const& spec) const = 0;
};

struct BetterFilter : Filter<Product>
{
    std::vector<Product*> filter(
        std::vector<Product*> items,
        Specification<Product> const& spec) const override
    {
        std::vector<Product*> result;
        for (auto& p : items)
            if (spec.is_satisfied(p))
                result.push_back(p);
        return result;
    }
};

struct ColorSpecification : Specification<Product>
{
    Color color;
    explicit ColorSpecification(Color const color) : color{color} {}
    bool is_satisfied(Product* item) const override {
        return item->color == color;
    }
};

struct SizeSpecification : Specification<Product>
{   
    Size size;
    explicit SizeSpecification(Size const size) : size{size} {}
    bool is_satisfied(Product* item) const override {
        return item->size == size;
    }
};

template<typename T>
struct AndSpecification : Specification<T>
{
    Specification<T> const& first;
    Specification<T> const& second;
    AndSpecification(Specification<T> const& first, Specification<T> const& second) : first{first}, second{second} {}
    bool is_satisfied(T* item) const override {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

// post hoc addition of an operator vioates OCP (e.g., Specification<T>::operator&&(...))
// so, you can add an operator on the global scope
template<typename T>
AndSpecification<T> operator&&(Specification<T> const& first, Specification<T> const& second) {
    return { first, second };
}

int main(int argc, char** argv)
{
    // Open-Closed Principle (OCP)
    Product apple{ "Apple", Color::Green, Size::Small };
    Product tree{ "Tree", Color::Green, Size::Large };
    Product house{ "House", Color::Blue, Size::Large };
    std::vector<Product*> all{ &apple, &tree, &house };

    BetterFilter bf;
    ColorSpecification green(Color::Green);
    auto green_things = bf.filter(all, green);
    for (auto& x : green_things)
        std::cout << x->name << " is green\n";
    std::cout << "\n";

    // filtering by color and size
    SizeSpecification large{Size::Large};
    // AndSpecification<Product> green_and_larger{ green, large };
    auto big_green_things = bf.filter(all, green && large);
    for (auto& x : big_green_things)
        std::cout << x->name << " is large and green\n";
    
    return 0;
}