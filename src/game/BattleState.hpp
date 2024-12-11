#ifndef BATTLE_STATE_HPP_
#define BATTLE_STATE_HPP_

#include "GameState.hpp"

class Game;

enum class Turn{BOT, HUMAN};

class BattleState final: public GameState {
private:
    Turn current_turn;
public:
    explicit BattleState(Game& game) noexcept(true);

    void SwitchTurn();

    Turn GetTurn();

    void NextRound();

    void PlayerMove();

    void UseSpell();

    void BotMove();

    void DoStateJob();
};

#endif