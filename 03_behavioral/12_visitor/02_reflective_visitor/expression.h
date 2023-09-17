#pragma once
#include <string>
#include <sstream>

struct Expression
{
    virtual ~Expression() = default;
};

struct DoubleExpression : Expression
{
    double value;
    explicit DoubleExpression(double const value) : value{value} {}
};

struct AdditionExpression : Expression
{
    Expression *left, *right;
    AdditionExpression(Expression* const left, Expression* const right) : left{left}, right{right} {}
    ~AdditionExpression() {
        delete left;
        delete right;
    }
};

struct ExpressionPrinter
{
    void print(Expression* e) {
        if (auto de = dynamic_cast<DoubleExpression*>(e)) {
            oss << de->value;
        }
        else if (auto ae = dynamic_cast<AdditionExpression*>(e)) {
            oss << "(";
            print(ae->left);
            oss << "+";
            print(ae->right);
            oss << ")";
        }
    }

    std::string str() const { return oss.str(); }

private:
    std::ostringstream oss;
};