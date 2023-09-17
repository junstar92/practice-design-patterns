#include <iostream>
#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
#include <memory>

struct Token
{
    enum Type { integer, plus, minus, lparen, rparen } type;
    std::string text;

    explicit Token(Type type, std::string_view text)
    : type{type}, text{text} {}

    friend std::ostream& operator<<(std::ostream& os, Token const& obj) {
        return os
            << "`" << obj.text << "`";
    }
};

std::vector<Token> lex(std::string_view input)
{
    std::vector<Token> ret;

    for (int i = 0; i < input.size(); i++) {
        switch (input[i])
        {
            case '+':
                ret.emplace_back(Token::plus, "+");
                break;
            case '-':
                ret.emplace_back(Token::minus, "-");
                break;
            case '(':
                ret.emplace_back(Token::lparen, "(");
                break;
            case ')':
                ret.emplace_back(Token::rparen, ")");
                break;
            default:
                // number
                std::ostringstream oss;
                oss << input[i];
                for (int j = i + 1; j < input.size(); j++) {
                    if (std::isdigit(input[j])) {
                        oss << input[j];
                        i++;
                    }
                    else {
                        ret.push_back(Token{Token::integer, oss.str()});
                        break;
                    }
                }
        }
    }

    return ret;
}

struct Element
{
    virtual int eval() const = 0;
};

struct Integer : Element
{
    int value;

    explicit Integer(int const value) : value{value} {}
    int eval() const override {
        return value;
    }
};

struct BinaryOperation : Element
{
    enum Type { addition, subtraction } type;
    std::shared_ptr<Element> lhs, rhs;

    int eval() const override {
        if (type == addition) {
            return lhs->eval() + rhs->eval();
        }
        return lhs->eval() - rhs->eval();
    }
};

std::shared_ptr<Element> parse(std::vector<Token> const& tokens)
{
    auto result = std::make_unique<BinaryOperation>();
    bool have_lhs = false;
    for (size_t i = 0; i < tokens.size(); i++) {
        auto token = tokens[i];
        switch (token.type)
        {
            case Token::integer:
            {
                int value = std::stoi(token.text);
                auto integer = std::make_shared<Integer>(value);
                if (!have_lhs) {
                    result->lhs = integer;
                    have_lhs = true;
                }
                else {
                    result->rhs = integer;
                }
            }
                break;
            
            case Token::plus:
                result->type = BinaryOperation::addition;
                break;
            
            case Token::minus:
                result->type = BinaryOperation::subtraction;
                break;
            
            case Token::lparen:
            {
                int j = i;
                for (; j < tokens.size(); j++)
                    if (tokens[j].type == Token::rparen)
                        break;
                
                std::vector<Token> subexpression(&tokens[i+1], &tokens[j]);
                auto element = parse(subexpression);
                if (!have_lhs) {
                    result->lhs = element;
                    have_lhs = true;
                }
                else {
                    result->rhs = element;
                }
                i = j;
            }
                break;
        }
    }
    return result;
}

int main(int argc, char** argv)
{
    std::string input{"(13-4)-(12+1)"};
    auto tokens = lex(input);

    for (auto& t : tokens)
        std::cout << t << "   ";
    std::cout << std::endl;

    try {
        auto parsed = parse(tokens);
        std::cout << input << " = " << parsed->eval() << std::endl;
    }
    catch (std::exception const& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}