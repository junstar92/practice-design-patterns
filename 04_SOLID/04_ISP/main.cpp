#include <iostream>
#include <vector>

struct Document
{
};
// This is a problem. The reason it is a problem is that some implementer of this interface
// might not need scanning or faxing, just printing.
struct IMachine
{
    virtual void print(std::vector<Document*> docs) = 0;
    virtual void fax(std::vector<Document*> docs) = 0;
    virtual void scan(std::vector<Document*> docs) = 0;
};

// So what ISP suggests is you aplit up interfaces so that implementers can pick and choose
// depending on their needs.
struct IPrinter
{
    virtual void print(std::vector<Document*> docs) = 0;
};
struct IScanner
{
    virtual void scan(std::vector<Document*> docs) = 0;
};

struct Printer : IPrinter
{
    void print(std::vector<Document*> docs) override {}
};
struct Scanner : IScanner
{
    void scan(std::vector<Document*> docs) override {}
};

struct IMachine2 : IPrinter, IScanner
{
};

struct Machine : IMachine2
{
    IPrinter& printer;
    IScanner& scanner;
    
    Machine(IPrinter& printer, IScanner& scanner) : printer{printer}, scanner{scanner} {}

    void print(std::vector<Document*> docs) override {
        printer.print(docs);
    }
    void scan(std::vector<Document*> docs) override {
        scanner.scan(docs);
    }
};

struct MyFavoritePrinter;

int main(int argc, char** argv)
{
    // Inteface Segregation Principle (ISP)
    Printer printer;
    Scanner scanner;
    Machine m{printer, scanner};
    m.print({});
    m.scan({});

    return 0;
}