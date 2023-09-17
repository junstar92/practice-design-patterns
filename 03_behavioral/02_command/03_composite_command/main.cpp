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
    bool succeeded;
    virtual ~Command() = default;
    virtual void call() = 0;
    virtual void undo() = 0;
};

struct BankAccountCommand : Command
{
    BankAccount& account;
    enum Action { deposit, withdraw } action;
    int amount;

    BankAccountCommand(BankAccount& account, Action const action, int const amount)
    : account{account}, action{action}, amount{amount} {
        succeeded = false;
    }

    void call() override {
        switch (action)
        {
        case deposit:
            account.deposit(amount);
            succeeded = true;
            break;
        case withdraw:
            succeeded = account.withdraw(amount);
            break;
        }
    }

    void undo() override {
        if (!succeeded) return;
        switch (action)
        {
        case withdraw:
            if (succeeded)
                account.deposit(amount);
            break;
        case deposit:
            account.withdraw(amount);
            break;
        }
    }
};

struct CompositeBankAccountCommand : std::vector<BankAccountCommand>, Command
{
    CompositeBankAccountCommand(std::initializer_list<value_type> const& items) : std::vector<BankAccountCommand>(items) {}

    void call() override {
        for (auto& cmd : *this)
            cmd.call();
    }

    void undo() override {
        for (auto it = rbegin(); it != rend(); it++)
            it->undo();
    }
};

struct MoneyTransferCommand : CompositeBankAccountCommand
{
    MoneyTransferCommand(BankAccount& from, BankAccount& to, int amount)
    : CompositeBankAccountCommand{
        BankAccountCommand{from, BankAccountCommand::withdraw, amount},
        BankAccountCommand{to, BankAccountCommand::deposit, amount}} {}
    
    void call() override {
        bool ok = true;
        for (auto& cmd : *this) {
            if (ok) {
                cmd.call();
                ok = cmd.succeeded;
            }
            else {
                cmd.succeeded = false;
            }
        }
    }
};

int main(int argc, char** argv)
{
    BankAccount ba;
    CompositeBankAccountCommand commands{
        BankAccountCommand{ba, BankAccountCommand::deposit, 100},
        BankAccountCommand{ba, BankAccountCommand::withdraw, 200}
    };

    std::cout << ba.balance << std::endl;

    commands.call();

    std::cout << ba.balance << std::endl;

    commands.undo();

    std::cout << ba.balance << std::endl;

    return 0;
}