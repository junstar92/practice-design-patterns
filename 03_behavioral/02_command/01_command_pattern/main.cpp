#include <iostream>
#include <vector>
#include <string>

struct BankAccount
{
    int balance{0};
    int overdraft_limit{-500};

    void deposit(int amount) {
        balance += amount;
        std::cout << "deposited " << amount << ", balance is now " << balance << std::endl;
    }

    void withdraw(int amount) {
        if (balance - amount >= overdraft_limit) {
            balance -= amount;
            std::cout << "withdraw " << amount << ", balance is now " << balance << std::endl;
        }
    }
};

struct Command
{
    virtual ~Command() = default;
    virtual void call() const = 0;
};

struct BankAccountCommand : Command
{
    BankAccount& account;
    enum Action { deposit, withdraw } action;
    int amount;

    BankAccountCommand(BankAccount& account, Action const action, int const amount)
    : account{account}, action{action}, amount{amount} {}

    void call() const override {
        switch (action)
        {
        case deposit:
            account.deposit(amount);
            break;
        case withdraw:
            account.withdraw(amount);
            break;
        }
    }
};

int main(int argc, char** argv)
{
    BankAccount ba;
    BankAccountCommand cmd{ba, BankAccountCommand::deposit, 100};
    cmd.call();

    return 0;
}