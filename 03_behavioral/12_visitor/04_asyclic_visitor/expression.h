#pragma once
#include <string>
#include <sstream>

template<typename Visitable>
struct Visitor
{
    virtual void visit(Visitable& obj) = 0;
};

struct VisitorBase
{
    virtual ~VisitorBase() = default;
};

struct Expression
{
    virtual ~Expression() = default;

    virtual void accept(VisitorBase& obj) {
        using EV = Visitor<Expression>;
        if (auto ev = dynamic_cast<EV*>(&obj)) {
            ev->visit(*this);
        }
    }
};

struct DoubleExpression : Expression
{
    double value;

    DoubleExpression(double const value) : value{value} {}

    virtual void accept(VisitorBase& obj) {
        using DEV = Visitor<DoubleExpression>;
        if (auto dev = dynamic_cast<DEV*>(&obj)) {
            dev->visit(*this);
        }
    }
};

struct AdditionExpression : Expression
{
    Expression *left, *right;

    AdditionExpression(Expression* const left, Expression* const right) : left{left},  right{right} {}
    ~AdditionExpression() {
        delete left;
        delete right;
    }

    virtual void accept(VisitorBase& obj) {
        using AEV = Visitor<AdditionExpression>;
        if (auto aev = dynamic_cast<AEV*>(&obj)) {
            aev->visit(*this);
        }
    }
};

struct ExpressionPrinter : VisitorBase, Visitor<DoubleExpression>, Visitor<AdditionExpression>
{
    void visit(DoubleExpression& obj) override {
        oss << obj.value;
    }
    void visit(AdditionExpression& obj) override {
        oss << "(";
        obj.left->accept(*this);
        oss << "+";
        obj.right->accept(*this);
        oss << ")";
    }
    std::string str() { return oss.str(); }

private:
    std::ostringstream oss;
};