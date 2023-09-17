#include <iostream>

// naive implementation
class Game
{
public:
    explicit Game(int number_of_players) : number_of_players{number_of_players}{}
    void run() {
        start();
        while (!have_winner())
            take_turn();
        std::cout << "Player " << get_winner() << " wins.\n";
    }

protected:
    virtual void start() = 0;
    virtual bool have_winner() = 0;
    virtual void take_turn() = 0;
    virtual int get_winner() = 0;

    int current_player{};
    int number_of_players{};
};

class Chess : public Game
{
public:
    explicit Chess() : Game{2} {}

protected:
    void start() override {
        std::cout << "Starting a game of chess with " << number_of_players << " players" << std::endl;
    }
    bool have_winner() override { return turns == max_turns; }
    void take_turn() override {
        std::cout << "Turn " << turns << " taken by player " << current_player << std::endl;
        turns++;
        current_player = (current_player + 1) % number_of_players;
    }
    int get_winner() override { return current_player; }

private:
    int turns{};
    int max_turns{10};
};

// implementation using template methods
struct GameState
{
    int current_player, winning_player;
    int number_of_players;
};

template<typename FnStartAction, typename FnTakeTurnAction, typename FnHaveWinnerAction>
void run_game(GameState initial_state, FnStartAction start_action, FnTakeTurnAction take_turn_action, FnHaveWinnerAction have_winner_action)
{
    GameState state = initial_state;
    start_action(state);
    while (!have_winner_action(state)) {
        take_turn_action(state);
    }
    std::cout << "Player " << state.winning_player << " wins.\n";
}

int main(int argc, char** argv)
{
    // naive game simulation
    Chess chess;
    chess.run();

    // using template methods
    int turn{0}, max_turns{10};
    GameState state{0, -1, 2};

    auto start = [](GameState& s) {
        std::cout << "Starting a game of chess with " << s.number_of_players << " players" << std::endl;
    };
    auto take_turn = [&turn](GameState& s) {
        std::cout << "Turn " << turn++ << " taken by player " << s.current_player << std::endl;
        s.current_player = (s.current_player + 1) % s.number_of_players;
        s.winning_player = s.current_player;  
    };
    auto have_winner = [&turn, &max_turns](GameState& s) {
        return turn == max_turns;
    };
    run_game(state, start, take_turn, have_winner);

    return 0;
}