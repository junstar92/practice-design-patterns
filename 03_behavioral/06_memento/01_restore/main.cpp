#include <iostream>

class Memento final
{
    int balance;

public:
    Memento(int balance) : balance{balance} {}

    friend class BankAccount;
};

class BankAccount
{
    int balance = 0;

public:
    explicit BankAccount(int const balance) : balance{balance} {}
    Memento deposit(int amount) {
        balance += amount;
        return {balance};
    }
    void restore(Memento const& m) {
        balance = m.balance;
    }

    friend std::ostream& operator<<(std::ostream& os, BankAccount const& obj) {
        return os << "balance: " << obj.balance;
    }
};

int main(int argc, char** argv)
{
    BankAccount ba{100};
    auto m1 = ba.deposit(50);
    auto m2 = ba.deposit(25);

    std::cout << ba << std::endl;

    // undo to m1
    ba.restore(m1);
    std::cout << ba << std::endl;

    // redo
    ba.restore(m2);
    std::cout << ba << std::endl;

    return 0;
}