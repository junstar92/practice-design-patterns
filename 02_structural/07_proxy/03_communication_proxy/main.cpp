#include <iostream>
#include <string>

struct Pingable
{
    virtual ~Pingable() = default;
    virtual std::wstring ping(std::wstring const& message) = 0;
};

struct Pong : Pingable
{
    std::wstring ping(std::wstring const& message) override {
        return message + L" pong";
    }
};

void tryit(Pingable& pp)
{
    std::wcout << pp.ping(L"ping") << std::endl;
}

int main(int argc, char** argv)
{
    Pong pp;
    for (int i = 0; i < 3; i++)
        tryit(pp);

    return 0;
}