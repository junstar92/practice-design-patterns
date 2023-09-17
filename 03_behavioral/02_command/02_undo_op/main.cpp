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

    bool withdraw(int amount) {
        if (balance - amount >= overdraft_limit) {
            balance -= amount;
            std::cout << "withdraw " << amount << ", balance is now " << balance << std::endl;
            return true;
        }
        return false;
    }
};

struct Command
{
    virtual ~Command() = default;
    virtual void call() = 0;
    virtual void undo() = 0;
};

struct BankAccountCommand : Command
{
    BankAccount& account;
    enum Action { deposit, withdraw } action;
    int amount;
    bool withdrawal_succeeded;

    BankAccountCommand(BankAccount& account, Action const action, int const amount)
    : account{account}, action{action}, amount{amount}, withdrawal_succeeded{false} {}

    void call() override {
        switch (action)
        {
        case deposit:
            account.deposit(amount);
            break;
        case withdraw:
            withdrawal_succeeded = account.withdraw(amount);
            break;
        }
    }

    void undo() override {
        switch (action)
        {
        case withdraw:
            if (withdrawal_succeeded)
                account.deposit(amount);
            break;
        case deposit:
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
    cmd.undo();

    return 0;
}