#include <iostream>

enum class CreatureAbility { strength, agility };

struct CreatureCommand
{
    enum Action { set, increaseBy, decreaseBy } action;
    CreatureAbility ability;
    int amount;
};

struct CreatureQuery
{
    CreatureAbility ability;
};

class Creature
{
    int strength, agility;

public:
    Creature(int strength, int agility)
    : strength{strength}, agility{agility} {}

    void process_command(CreatureCommand const& cc) {
        int *ability;
        switch (cc.ability) {
            case CreatureAbility::strength:
                ability = &strength;
                break;
            case CreatureAbility::agility:
                ability = &agility;
                break;
        }
        switch (cc.action)
        {
            case CreatureCommand::set:
                *ability = cc.amount;
                break;
            case CreatureCommand::increaseBy:
                *ability += cc.amount;
                break;
            case CreatureCommand::decreaseBy:
                *ability -= cc.amount;
                break;
        }
    }
    int process_query(CreatureQuery const& q) const {
        switch (q.ability)
        {
            case CreatureAbility::strength: return strength;
            case CreatureAbility::agility: return agility;
        }
        return 0;
    }

    void set_strength(int value) {
        process_command(CreatureCommand{
            CreatureCommand::set, CreatureAbility::strength, value
        });
    }
    void increase_strength(int value) {
        process_command(CreatureCommand{
            CreatureCommand::increaseBy, CreatureAbility::strength, value
        });
    }
    void decrease_strength(int value) {
        process_command(CreatureCommand{
            CreatureCommand::decreaseBy, CreatureAbility::strength, value
        });
    }
    int get_strength() const {
        return process_query(CreatureQuery{CreatureAbility::strength});
    }

    void set_agility(int value) {
        process_command(CreatureCommand{
            CreatureCommand::set, CreatureAbility::agility, value
        });
    }
    void increase_agility(int value) {
        process_command(CreatureCommand{
            CreatureCommand::increaseBy, CreatureAbility::agility, value
        });
    }
    void decrease_agility(int value) {
        process_command(CreatureCommand{
            CreatureCommand::decreaseBy, CreatureAbility::agility, value
        });
    }
    int get_agility() const {
        return process_query(CreatureQuery{CreatureAbility::agility});
    }

    friend std::ostream& operator<<(std::ostream& os, Creature const& obj) {
        return os
            << "strength: " << obj.get_strength()
            << " agility: " << obj.get_agility();

    }
};

int main(int argc, char** argv)
{
    Creature c{10, 10};

    std::cout << c << std::endl;

    c.increase_strength(20);
    c.decrease_agility(5);

    std::cout << c << std::endl;

    return 0;
}