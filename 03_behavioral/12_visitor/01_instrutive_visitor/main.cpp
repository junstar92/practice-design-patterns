#include <iostream>
#include <expression.h>

int main(int argc, char** argv)
{
    // this is not good. 
    auto e = new AdditionExpression{
        new DoubleExpression{1},
        new AdditionExpression{
            new DoubleExpression{2},
            new DoubleExpression{3}
        }
    };
    std::ostringstream oss;
    e->print(oss);
    std::cout << oss.str() << std::endl;

    delete e;

    return 0;
}