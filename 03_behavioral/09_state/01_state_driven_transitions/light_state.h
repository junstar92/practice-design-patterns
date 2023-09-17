#pragma once
#include <iostream>

class LightSwitch;
struct State
{
    virtual void on(LightSwitch* ls) {
        std::cout << "Light is already on\n";
    }
    virtual void off(LightSwitch* ls) {
        std::cout << "Light is already off\n";
    }
};

struct OnState : State
{
    OnState() { std::cout << "Light turned on\n"; }
    inline void off(LightSwitch* ls) override;
};

struct OffState : State
{
    OffState() { std::cout << "Light turned off\n"; }
    inline void on(LightSwitch* ls) override;
};

class LightSwitch
{
    State* state;

public:
    LightSwitch() {
        state = new OffState();
    }
    void set_state(State* state) {
        this->state = state;
    }
    void on() { state->on(this); }
    void off() { state->off(this); }
};

void OnState::off(LightSwitch* ls)
{
    std::cout << "Switching light off...\n";
    ls->set_state(new OffState());
    delete this;
}

void OffState::on(LightSwitch* ls)
{
    std::cout << "Switching light on...\n";
    ls->set_state(new OnState());
    delete this;
}