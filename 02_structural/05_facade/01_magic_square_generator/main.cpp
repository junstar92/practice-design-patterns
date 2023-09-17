#include <iostream>
#include <generator.h>
#include <splitter.h>
#include <verifier.h>

template<typename G = Generator, typename S = Splitter, typename V = Verifier>
struct MagicSquareGenerator
{
    std::vector<std::vector<int>> generate(int size) {
        G g;
        S s;
        V v;
        std::vector<std::vector<int>> square;

        do {
            square.clear();
            for (int i = 0; i < size; i++)
                square.emplace_back(g.generate(size));
        } while (!v.verify(s.split(square)));

        return square;
    }
};

int main(int argc, char** argv)
{
    srand(time(NULL));
    int size = 3;
    if (argc > 1) size = std::stoi(argv[1]);

    // really impractical implementation... just for demonstrating pacade pattern.
    MagicSquareGenerator<UniqueGeneartor> gen;
    auto square = gen.generate(size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << square[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}