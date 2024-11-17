#ifndef BATTLE_STATE_HPP_
#define BATTLE_STATE_HPP_

#include "GameInput.hpp"
#include "Game.hpp"

class BattleState final: public GameState {
private:
    enum class Turn{BOT, HUMAN};
    Turn current_turn;
public:
    inline explicit BattleState(Game& game): GameState(game) {
        std::cout << "Now start battle!" << std::endl;
        current_turn = Turn::HUMAN;
    }

    void SwitchTurn();

    void NextRound();

    void operator<<(GameInput msg);
};

#endif