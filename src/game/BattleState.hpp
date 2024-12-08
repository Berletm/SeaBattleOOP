#ifndef BATTLE_STATE_HPP_
#define BATTLE_STATE_HPP_

#include "game utils/CLIGameInput.hpp"
#include "Game.hpp"

enum class Turn{BOT, HUMAN};

class BattleState final: public GameState {
private:
    Turn current_turn;
public:
    inline explicit BattleState(Game& game): GameState(game) {
        game.output.log_msg("Now start battle!");
        current_turn = Turn::HUMAN;
    }

    void SwitchTurn();

    Turn GetTurn();

    void NextRound();

    void PlayerMove();

    void UseSpell();

    void BotMove();

    void DoStateJob();
};

#endif