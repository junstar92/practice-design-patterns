#include <iostream>
#include <string>

enum class State
{
    locked,
    failed,
    unlocked
};

int main(int argc, char** argv)
{
    std::string const code{"1274"};
    auto state{State::locked};
    std::string entry;

    while (true)
    {
        switch (state)
        {
        case State::locked:
            {
                entry += (char)getchar();
                getchar(); // consume return

                if (entry == code) {
                    state = State::unlocked;
                    break;
                }
                if (!code.starts_with(entry)) {
                    state = State::failed;
                }
            }
            break;
        
        case State::failed:
            std::cout << "FAILED\n";
            return 1;
        
        case State::unlocked:
            std::cout << "UNLOCKED\n";
            return 0;
        }
    }

    return 0;
}