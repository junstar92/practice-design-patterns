#include <iostream>
#include <neuron.h>

int main(int argc, char** argv)
{
    Neuron n1, n2;
    n1.connect_to(n2);

    std::cout << n1 << n2 << std::endl;

    NeuronLayer layer1{5};
    Neuron n3;
    layer1.connect_to(n3);

    std::cout << "Neuron " << n3.id << std::endl << n3 << std::endl;
    std::cout << "Layer " << std::endl << layer1 << std::endl;

    NeuronLayer layer2{2}, layer3{3};
    layer2.connect_to(layer3);
    std::cout << "Layer 2" << std::endl << layer2;
    std::cout << "Layer 3" << std::endl << layer3;
    

    return 0;
}