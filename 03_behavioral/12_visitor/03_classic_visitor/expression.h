#pragma once
#include <string>
#include <sstream>

struct DoubleExpression;
struct AdditionExpression;
struct ExpressionVisitor
{
    virtual void visit(DoubleExpression* de) = 0;
    virtual void visit(AdditionExpression* ae) = 0;
};

struct Expression
{
    virtual ~Expression() = default;
    virtual void accept(ExpressionVisitor* visitor) = 0;
};

struct DoubleExpression : Expression
{
    double value;
    explicit DoubleExpression(double const value) : value{value} {}

    void accept(ExpressionVisitor* visitor) override {
        visitor->visit(this);
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

    void accept(ExpressionVisitor* visitor) override {
        visitor->visit(this);
    }
};

struct ExpressionPrinter : ExpressionVisitor
{
    void visit(DoubleExpression* de) override {
        oss << de->value;
    }
    void visit(AdditionExpression* ae) override {
        oss << "(";
        ae->left->accept(this);
        oss << "+";
        ae->right->accept(this);
        oss << ")";
    }

    std::string str() const { return oss.str(); }

private:
    std::ostringstream oss;
};

struct ExpressionEvaluator : ExpressionVisitor
{
    double result;
    void visit(DoubleExpression* de) override {
        result = de->value;
    }
    void visit(AdditionExpression* ae) override {
        ae->left->accept(this);
        auto temp = result;
        ae->right->accept(this);
        result += temp;
    }
};