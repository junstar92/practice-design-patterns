#pragma once
#include <vector>
#include <memory>

template<typename T>
struct Specification
{
    virtual bool is_satisfied(T* item) {
        return true;
    }
};

template<typename T>
struct CompositeSpecification : Specification<T>
{
protected:
    std::vector<std::unique_ptr<Specification<T>>> specs;

    template<typename... Specs>
    CompositeSpecification(Specs... specs) {
        this->specs.reserve(sizeof...(Specs));
        (this->specs.push_back(std::make_unique<Specs>(std::move(specs))), ...);
    }
};

template<typename T>
struct AndSpecification : CompositeSpecification<T>
{
    template<typename... Specs>
    AndSpecification(Specs... specs) : CompositeSpecification<T>{specs...} {}

    bool is_satisfied(T* item) const {
        return std::all_of(this->specs.begin(), this->specs.end(), [](auto const& s) {
            return s->is_satisfied(item);
        });
    }
};