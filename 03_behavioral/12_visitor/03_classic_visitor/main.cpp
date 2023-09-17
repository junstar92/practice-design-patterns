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
    ExpressionPrinter printer;
    ExpressionEvaluator evaluator;
    printer.visit(e);
    evaluator.visit(e);
    std::cout << printer.str() << " = " << evaluator.result << std::endl;

    delete e;

    return 0;
}