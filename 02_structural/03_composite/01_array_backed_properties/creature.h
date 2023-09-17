#pragma once
#include <array>
#include <numeric>

class Creature1
{
public:
    int get_strength() const { return strength; }
    void set_strength(int strength) { this->strength = strength; }
    int get_agility() const { return agility; }
    void set_agility(int agility) { this->agility = agility; }
    int get_intelligence() const { return intelligence; }
    void set_intelligence(int intelligence) { this->intelligence = intelligence; }

    int sum() const { return strength + agility + intelligence; }
    double average() const { return sum() / 3.0; }
    int max() const { return std::max(std::max(strength, agility), intelligence); }

private:
    int strength, agility, intelligence;
};

class Creature2
{
public:
    int get_strength() const { return abilities[str]; }
    void set_strength(int strength) { abilities[str] = strength; }
    int get_agility() const { return abilities[agl]; }
    void set_agility(int agility) { abilities[agl] = agility; }
    int get_intelligence() const { return abilities[intl]; }
    void set_intelligence(int intelligence) { abilities[intl] = intelligence; }

    int sum() const { return std::accumulate(abilities.begin(), abilities.end(), 0); }
    double average() const { return sum() / (double)count; }
    int max() const { return *std::max_element(abilities.begin(), abilities.end()); }

private:
    enum Abilities { str, agl, intl, count };
    std::array<int, count> abilities;
};