#include <iostream>
#include <expression.h>

int main(int argc, char** argv)
{
    // seperating expression with visitor
    // But, this is not good, too.
    // When a new element gets added, you can keep using ExpressionPrinter without modification.
    // It will just skip over any element of the new type...
    auto e = new AdditionExpression{
        new DoubleExpression{1},
        new AdditionExpression{
            new DoubleExpression{2},
            new DoubleExpression{3}
        }
    };
    ExpressionPrinter ep;
    ep.print(e);
    std::cout << ep.str() << std::endl;

    delete e;

    return 0;
}