#include <iostream>
#include <string>

struct Creature
{
    std::string name;
    int attack, defense;

    Creature(std::string const& name, int const attack, int const defense)
    : name{name}, attack{attack}, defense{defense} {}

    friend std::ostream& operator<<(std::ostream& os, Creature const& obj) {
        return os
            << "name: " << obj.name
            << " attack: " << obj.attack
            << " defense: " << obj.defense;
    }
};

class CreatureModifier
{
    CreatureModifier* next{nullptr};

protected:
    Creature& creature; // alternative: pointer or shared_ptr

public:
    explicit CreatureModifier(Creature& creature) : creature{creature} {}
    virtual ~CreatureModifier() = default;

    void add(CreatureModifier* cm) {
        if (next) next->add(cm);
        else next = cm;
    }

    virtual void handle() {
        if (next) next->handle();
    }
};

class DoubleAttackModifier : public CreatureModifier
{
public:
    explicit DoubleAttackModifier(Creature& creature) : CreatureModifier(creature) {}

    void handle() override {
        creature.attack *= 2;
        CreatureModifier::handle();
    }
};

class IncreaseDefenseModifier : public CreatureModifier
{
public:
    explicit IncreaseDefenseModifier(Creature& creature) : CreatureModifier(creature) {}

    void handle() override {
        if (creature.attack <= 2) creature.defense += 1;
        CreatureModifier::handle();
    }
};

class NoBonusesModifier : public CreatureModifier
{
public:
    explicit NoBonusesModifier(Creature& creature) : CreatureModifier(creature) {}

    void handle() override {
        // do nothing
    }
};

int main(int argc, char** argv)
{
    Creature goblin{"Goblin", 1, 1};
    CreatureModifier root{goblin};
    DoubleAttackModifier r1{goblin};
    DoubleAttackModifier r1_2{goblin};
    IncreaseDefenseModifier r2{goblin};

    // NoBonusesModifier r3{goblin};
    // root.add(&r3);
    root.add(&r1);
    root.add(&r1_2);
    root.add(&r2);

    root.handle();

    std::cout << goblin << std::endl;

    return 0;
}