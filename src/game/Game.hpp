#ifndef GAME_HPP_
#define GAME_HPP_

#include <nlohmann/json.hpp>
#include "GameState.hpp"

using json = nlohmann::json;

class Game {
private:
    bool is_running;

protected:
    friend class GameState;

    GameInput input;

    Player bot;
    HumanPlayer player;
    GameState* current_state;
public:
    explicit Game();
    ~Game();

    void Play();
    void ChangeState(GameState* new_state);
    bool IsRunning();
    void Quit();

private:
    void StartNewGame();
};

#endif