#pragma once
#include <string>
#include <sstream>

struct Expression
{
    virtual ~Expression() = default;
    virtual void print(std::ostringstream& oss) = 0;
};

struct DoubleExpression : Expression
{
    double value;
    explicit DoubleExpression(double const value) : value{value} {}

    void print(std::ostringstream& oss) override {
        oss << value;
    }
};

struct AdditionExpression : Expression
{
    Expression *left, *right;
    AdditionExpression(Expression* const left, Expression* const right) : left{left}, right{right} {}
    ~AdditionExpression() {
        delete left;
        delete right;
    }

    void print(std::ostringstream& oss) override {
        oss << "(";
        left->print(oss);
        oss << "+";
        right->print(oss);
        oss << ")";
    }
};