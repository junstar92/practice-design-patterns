#include <iostream>
#include <expression.h>

int main(int argc, char** argv)
{
    // you can add lots of other different visitors, honoring OCP.
    auto e = new AdditionExpression{
        new DoubleExpression{1},
        new AdditionExpression{
            new DoubleExpression{2},
            new DoubleExpression{3}
        }
    };
    ExpressionPrinter ep;
    ep.visit(*e);
    std::cout << ep.str() << std::endl;

    delete e;

    return 0;
}