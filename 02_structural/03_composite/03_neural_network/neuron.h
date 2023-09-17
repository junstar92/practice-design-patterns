#pragma once
#include <iostream>
#include <vector>

struct Neuron;

template<typename Self>
struct SomeNeurons
{
    template<typename T>
    void connect_to(T& other);
};

struct Neuron : SomeNeurons<Neuron>
{
    std::vector<Neuron*> in, out;
    unsigned int id;

    Neuron() {
        static int id = 1;
        this->id = id++;
    }

    Neuron* begin() { return this; }
    Neuron* end() { return this + 1; }

    friend std::ostream& operator<<(std::ostream& os, Neuron const& obj) {
        for (Neuron* n : obj.in) {
            os << n->id << "\t-->\t[" << obj.id << "]\n";
        }
        for (Neuron* n : obj.out) {
            os << "[" << obj.id << "]\t-->\t" << n->id << "\n";
        }
        return os;
    }
};

struct NeuronLayer : std::vector<Neuron>, SomeNeurons<NeuronLayer>
{
    NeuronLayer(int count) {
        while (count-- > 0) {
            emplace_back(Neuron{});
        }
    }

    friend std::ostream& operator<<(std::ostream& os, NeuronLayer const& obj) {
        for (auto& n : obj) os << n;
        return os;
    }
};

template<typename Self>
template<typename T>
void SomeNeurons<Self>::connect_to(T& other)
{
    for (Neuron& from : *static_cast<Self*>(this)) {
        for (Neuron& to : other) {
            from.out.push_back(&to);
            to.in.push_back(&from);
        }
    }
}