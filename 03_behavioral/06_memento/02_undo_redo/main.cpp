#include <iostream>
#include <vector>
#include <memory>

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
    std::vector<std::shared_ptr<Memento>> changes;
    int current;

public:
    explicit BankAccount(int const balance): balance{balance} {
        changes.emplace_back(std::make_shared<Memento>(balance));
        current = 0;
    }

    std::shared_ptr<Memento> deposit(int amount) {
        balance += amount;
        auto m = std::make_shared<Memento>(balance);
        changes.push_back(m);
        ++current;
        return m;
    }
    void restore(std::shared_ptr<Memento> const& m) {
        if (m) {
            balance = m->balance;
            changes.push_back(m);
            current = changes.size() - 1;
        }
    }
    std::shared_ptr<Memento> undo() {
        if (current > 0) {
            --current;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
        return {};
    }
    std::shared_ptr<Memento> redo() {
        if (current + 1 < changes.size()) {
            ++current;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
        return {};
    }

    friend std::ostream& operator<<(std::ostream& os, BankAccount const& obj) {
        return os << "balance: " << obj.balance;
    }
};

int main(int argc, char** argv)
{
    BankAccount ba{100};
    ba.deposit(50);
    ba.deposit(25);
    std::cout << ba << std::endl;

    ba.undo();
    std::cout << "Undo 1: " << ba << std::endl;

    ba.undo();
    std::cout << "Undo 2: " << ba << std::endl;

    ba.redo();
    std::cout << "Redo 2: " << ba << std::endl;

    ba.undo();
    std::cout << "Undo 2: " << ba << std::endl;

    return 0;
}